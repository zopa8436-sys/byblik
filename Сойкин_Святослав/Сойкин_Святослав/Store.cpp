#include "pch.h"
#include "Store.h"
#include "GameFactory.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

// Конструктор по умолчанию с базовыми значениями названия и адреса магазина
Store::Store() : name_("Game Store"), address_("г. Москва, ул. Ленина, д. 10") {}

// Конструктор с загрузкой данных из CSV файла
Store::Store(const string& filename) : name_("Game Store"), address_("г. Москва, ул. Ленина, д. 10") {
    if (!loadFromCSV(filename)) {
        // При неудачной загрузке создается новая коллекция с помощью фабрики
        games_ = GameFactory::createVector(12);
        saveToCSV(filename);  // Попытка сохранения
    }
}

// Геттеры для доступа к приватным полям класса
const string& Store::name() const { return name_; }
const string& Store::address() const { return address_; }
const vector<Game>& Store::games() const { return games_; }

// Добавление новой игры в коллекцию магазина
void Store::addGame(const Game& game) {
    games_.push_back(game);  // Добавление игры в конец вектора
}

// Редактирование существующей игры по её идентификатору
void Store::editGame(int id) {
    auto it = find_if(games_.begin(), games_.end(), [id](const Game& g) { return g.id() == id; });
    if (it == games_.end()) {
        throw runtime_error("Игра с таким ID не найдена");
    }
    // Замена найденной игры на новую с тем же ID
    Game newGame = GameFactory::create(id);
    *it = newGame;
}

// Удаление игры из коллекции по её идентификатору
void Store::removeGame(int id) {
    auto it = remove_if(games_.begin(), games_.end(), [id](const Game& g) { return g.id() == id; });
    if (it != games_.end()) {
        games_.erase(it, games_.end());  // Удаление перемещённых элементов
    }
}

// Сортировка коллекции игр по возрастанию идентификатора
void Store::sortById() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.id() < b.id(); });
}

// Сортировка коллекции игр по убыванию года выпуска
void Store::sortByYearDesc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.year() > b.year(); });
}

// Сортировка коллекции игр по возрастанию цены
void Store::sortByPriceAsc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.price() < b.price(); });
}

// Сортировка коллекции игр по убыванию количества проданных копий
void Store::sortBySoldDesc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.soldCopies() > b.soldCopies(); });
}

// Поиск игр по диапазону цен
vector<Game> Store::findByPriceRange(int minPrice, int maxPrice) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [minPrice, maxPrice](const Game& g) { return g.price() >= minPrice && g.price() <= maxPrice; });
    return result;
}

// Поиск игр по году выпуска
vector<Game> Store::findByYear(int year) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [year](const Game& g) { return g.year() == year; });
    return result;
}

// Поиск игр по операционной системе
vector<Game> Store::findByOs(const string& os) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [os](const Game& g) { return g.os() == os; });
    return result;
}

// Вывод информации о магазине и его коллекции
void Store::print(ostream& os) const {
    os << "Магазин: " << name_ << ", Адрес: " << address_ << "\n";
    os << Game::header();
    int row = 1;
    for (const auto& game : games_) {
        os << game.toTableRow(row++) << "\n";
    }
    os << Game::footer();
}

// Загрузка данных из CSV файла
bool Store::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    if (!getline(file, line)) {
        file.close();
        return false;
    }

    istringstream iss(line);
    getline(iss, name_, ';');
    getline(iss, address_, ';');
    games_.clear();

    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        int id, year;
        int soldCopies;
        double priceDouble;
        string title, os, genre, publisher, developer, players, ageCategory;

        if (!getline(iss, token, ';')) continue;
        id = atoi(token.c_str());
        getline(iss, title, ';');
        getline(iss, os, ';');
        getline(iss, token, ';'); year = atoi(token.c_str());
        getline(iss, genre, ';');
        getline(iss, publisher, ';');
        getline(iss, developer, ';');
        getline(iss, token, ';'); soldCopies = atoi(token.c_str());
        getline(iss, players, ';');
        getline(iss, ageCategory, ';');
        getline(iss, token, ';'); priceDouble = atof(token.c_str());

        int priceCents = static_cast<int>(priceDouble * 100);
        bool multiplayer = (players == "Multiplayer");

        try {
            games_.emplace_back(id, title, os, year, genre, publisher, developer, soldCopies, multiplayer, ageCategory, priceCents);
        }
        catch (...) {
            // Игнор ошибок
        }
    }
    file.close();
    return true;
}

// Сохранение данных магазина в CSV файл
void Store::saveToCSV(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        throw runtime_error("Ошибка открытия файла для записи");
    }
    // Запись информации о магазине
    file << name_ << ";" << address_ << "\n";
    // Запись данных об играх
    for (const auto& game : games_) {
        file << game.id() << ";" << game.title() << ";" << game.os() << ";" << game.year() << ";" << game.genre() << ";"
            << game.publisher() << ";" << game.developer() << ";" << game.soldCopies() << ";" << (game.multiplayer() ? "Multiplayer" : "Singleplayer") << ";"
            << game.ageCategory() << ";" << (game.price() / 100.0) << "\n";
    }
    file.close();
}