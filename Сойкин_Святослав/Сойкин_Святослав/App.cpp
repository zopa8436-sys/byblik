#include "pch.h"
#include "App.h"
#include "Utils.h"
#include "GameFactory.h"
#include <algorithm>
#include <iostream>

// Конструктор
App::App(const string & filename) : store_(filename), filename_(filename) {}

// Вспомогательная функция для вывода коллекции игр в табличном формате
void showAsTable(const vector<Game>& games, ostream& os = cout) {
    os << Game::header();
    int row = 1;
    for (const auto& game : games) {
        os << game.toTableRow(row++) << "\n";
    }
    os << Game::footer();
}

// Вывод информации о магазине и его коллекции игр
void App::printStore(ostream& os) const {
    store_.print(os);
}

// Инициализация коллекции игр с использованием фабрики
void App::initCollection() {
    if (store_.games().empty()) {
        store_ = Store(filename_);
    }
    cout << cls << "Коллекция сформирована.\n";
    printStore();
}

// Добавление новой игры в коллекцию магазина
void App::addGame() {
    printStore();
    int nextId = store_.games().empty() ? 1 : max_element(store_.games().begin(), store_.games().end(),
        [](const Game& a, const Game& b) { return a.id() < b.id(); })->id() + 1;

    Game newGame = GameFactory::create(nextId);
    store_.addGame(newGame);

    cout << cls << "Игра добавлена: " << newGame.toString() << "\n";
    printStore();
}

// Редактирование существующей игры по ID
void App::editGame() {
    printStore();
    cout << "Введите ID: ";
    int id = getInt();
    getKey("Нажмите для редактирования...");

    store_.editGame(id);
    cout << cls << "Игра отредактирована.\n";
    printStore();
}

// Удаление игры из коллекции по ID
void App::removeGame() {
    printStore();
    cout << "Введите ID: ";
    int id = getInt();
    getKey("Нажмите для удаления...");

    store_.removeGame(id);
    cout << cls << "Игра удалена.\n";
    printStore();
}

// Сортировка коллекции игр по возрастанию ID
void App::sortById() {
    printStore();
    getKey("Нажмите для сортировки по ID...");

    store_.sortById();
    cout << cls << "Отсортировано по ID.\n";
    printStore();
}

// Сортировка коллекции игр по убыванию года выпуска
void App::sortByYearDesc() {
    printStore();
    getKey("Нажмите для сортировки по году...");

    store_.sortByYearDesc();
    cout << cls << "Отсортировано по убыванию года.\n";
    printStore();
}

// Сортировка коллекции игр по возрастанию цены
void App::sortByPriceAsc() {
    printStore();
    getKey("Нажмите для сортировки по цене...");

    store_.sortByPriceAsc();
    cout << cls << "Отсортировано по возрастанию цены.\n";
    printStore();
}

// Сортировка коллекции игр по убыванию количества проданных копий
void App::sortBySoldDesc() {
    printStore();
    getKey("Нажмите для сортировки по продажам...");

    store_.sortBySoldDesc();
    cout << cls << "Отсортировано по убыванию продаж.\n";
    printStore();
}

// Фильтрация игр по диапазону цен
void App::filterByPriceRange() {
    printStore();
    cout << "Введите минимальную цену: ";
    double minPriceD = 0.0; cin >> minPriceD;
    cout << "Введите максимальную цену: ";
    double maxPriceD = 0.0; cin >> maxPriceD;
    int minPrice = static_cast<int>(minPriceD * 100);
    int maxPrice = static_cast<int>(maxPriceD * 100);
    getKey("Нажмите для фильтра...");

    vector<Game> filtered = store_.findByPriceRange(minPrice, maxPrice);
    cout << cls << "Отфильтровано по диапазону цены (" << minPriceD << "-" << maxPriceD << "):\n";
    if (filtered.empty()) {
        cout << "Игры не найдены.\n";
    }
    else {
        showAsTable(filtered);
    }
}

// Фильтрация игр по году выпуска
void App::filterByYear() {
    printStore();
    cout << "Введите год: ";
    int year = getInt();
    getKey("Нажмите для фильтра...");

    vector<Game> filtered = store_.findByYear(year);
    cout << cls << "Отфильтровано по году " << year << ":\n";
    if (filtered.empty()) {
        cout << "Игры не найдены.\n";
    }
    else {
        showAsTable(filtered);
    }
}

// Фильтрация игр по операционной системе
void App::filterByOs() {
    printStore();
    string os;
    cout << "Введите ОС (например, Windows): ";
    getline(cin >> ws, os);
    getKey("Нажмите для фильтра...");

    vector<Game> filtered = store_.findByOs(os);
    cout << cls << "Отфильтровано по ОС " << os << ":\n";
    if (filtered.empty()) {
        cout << "Игры не найдены.\n";
    }
    else {
        showAsTable(filtered);
    }
}

// Сохранение данных магазина в CSV файл
void App::saveStore() {
    printStore();
    getKey("Нажмите для сохранения...");
    store_.saveToCSV(filename_);
    cout << cls << "Магазин сохранен.\n";
    printStore();
}

// Загрузка данных магазина из CSV файла
void App::loadStore() {
    if (store_.loadFromCSV(filename_)) {
        cout << cls << "Магазин загружен.\n";
        printStore();
    }
    else {
        cout << "Ошибка загрузки.\n";
    }
}