#include "pch.h"
#include "Store.h"
#include "GameFactory.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cmath>

// ����������� �� ��������� � �������� ���������� �������� � ������ ��������
Store::Store() : name_("Game Store"), address_("�. ������, ��. ������, �. 10") {}

// ����������� � ��������� ������ �� CSV �����
Store::Store(const string& filename) : name_("Game Store"), address_("�. ������, ��. ������, �. 10") {
    if (!loadFromCSV(filename)) {
        // ��� ��������� �������� ��������� ����� ��������� � ������� �������
        games_ = GameFactory::createVector(12);
        saveToCSV(filename);  // ������� ����������
    }
}

// ������� ��� ������� � ��������� ����� ������
const string& Store::name() const { return name_; }
const string& Store::address() const { return address_; }
const vector<Game>& Store::games() const { return games_; }

// ���������� ����� ���� � ��������� ��������
void Store::addGame(const Game& game) {
    games_.push_back(game);  // ���������� ���� � ����� �������
}

// �������������� ������������ ���� �� � ��������������
void Store::editGame(int id) {
    auto it = find_if(games_.begin(), games_.end(), [id](const Game& g) { return g.id() == id; });
    if (it == games_.end()) {
        throw runtime_error("���� � ����� ID �� �������");
    }
    // ������ ��������� ���� �� ����� � ��� �� ID
    Game newGame = GameFactory::create(id);
    *it = newGame;
}

// �������� ���� �� ��������� �� � ��������������
void Store::removeGame(int id) {
    auto it = remove_if(games_.begin(), games_.end(), [id](const Game& g) { return g.id() == id; });
    if (it != games_.end()) {
        games_.erase(it, games_.end());  // �������� ������������ ���������
    }
}

// ���������� ��������� ��� �� ����������� ��������������
void Store::sortById() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.id() < b.id(); });
}

// ���������� ��������� ��� �� �������� ���� �������
void Store::sortByYearDesc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.year() > b.year(); });
}

// ���������� ��������� ��� �� ����������� ����
void Store::sortByPriceAsc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.price() < b.price(); });
}

// ���������� ��������� ��� �� �������� ���������� ��������� �����
void Store::sortBySoldDesc() {
    sort(games_.begin(), games_.end(), [](const Game& a, const Game& b) { return a.soldCopies() > b.soldCopies(); });
}

// ����� ��� �� ��������� ���
vector<Game> Store::findByPriceRange(int minPrice, int maxPrice) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [minPrice, maxPrice](const Game& g) { return g.price() >= minPrice && g.price() <= maxPrice; });
    return result;
}

// ����� ��� �� ���� �������
vector<Game> Store::findByYear(int year) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [year](const Game& g) { return g.year() == year; });
    return result;
}

// ����� ��� �� ������������ �������
vector<Game> Store::findByOs(const string& os) const {
    vector<Game> result;
    copy_if(games_.begin(), games_.end(), back_inserter(result),
        [os](const Game& g) { return g.os() == os; });
    return result;
}

// ����� ���������� � �������� � ��� ���������
void Store::print(ostream& os) const {
    os << "�������: " << name_ << ", �����: " << address_ << "\n";
    os << Game::header();
    int row = 1;
    for (const auto& game : games_) {
        os << game.toTableRow(row++) << "\n";
    }
    os << Game::footer();
}

// �������� ������ �� CSV �����
bool Store::loadFromCSV(const string& filename) {
    // Базовая проверка открытия файла
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Вспомогательный парсер строки CSV с учетом кавычек и экранирования ""
    auto splitCSV = [](const string& line) {
        vector<string> fields;
        string cur;
        bool inQuotes = false;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '"') {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                    cur.push_back('"');
                    ++i; // пропускаем экранированную кавычку
                }
                else {
                    inQuotes = !inQuotes;
                }
            }
            else if (c == ';' && !inQuotes) {
                fields.push_back(cur);
                cur.clear();
            }
            else {
                cur.push_back(c);
            }
        }
        fields.push_back(cur);
        return fields;
    };

    string line;
    // Читаем заголовок (имя магазина и адрес)
    if (!getline(file, line)) {
        file.close();
        return false;
    }
    auto header = splitCSV(line);
    if (header.size() >= 1) name_ = header[0];
    if (header.size() >= 2) address_ = header[1];

    games_.clear();

    while (getline(file, line)) {
        if (line.empty()) continue;
        auto f = splitCSV(line);
        // Ожидаем 11 полей: id,title,os,year,genre,publisher,developer,soldCopies,players,ageCategory,price
        if (f.size() < 11) continue;
        try {
            int id = stoi(f[0]);
            string title = f[1];
            string os = f[2];
            int year = stoi(f[3]);
            string genre = f[4];
            string publisher = f[5];
            string developer = f[6];
            int soldCopies = stoi(f[7]);
            string players = f[8];
            string ageCategory = f[9];
            double priceDouble = stod(f[10]);

            int priceCents = static_cast<int>(std::lround(priceDouble * 100.0));
            bool multiplayer = (players == "Multiplayer");

            games_.emplace_back(id, title, os, year, genre, publisher, developer, soldCopies, multiplayer, ageCategory, priceCents);
        }
        catch (...) {
            // Игнорируем некорректные строки, продолжаем читать остальные
            continue;
        }
    }
    file.close();
    return true;
}

// ���������� ������ �������� � CSV ����
void Store::saveToCSV(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        throw runtime_error("������ �������� ����� ��� ������");
    }
    // ������ ���������� � ��������
    file << name_ << ";" << address_ << "\n";
    // ������ ������ �� �����
    for (const auto& game : games_) {
        file << game.id() << ";" << game.title() << ";" << game.os() << ";" << game.year() << ";" << game.genre() << ";"
            << game.publisher() << ";" << game.developer() << ";" << game.soldCopies() << ";" << (game.multiplayer() ? "Multiplayer" : "Singleplayer") << ";"
            << game.ageCategory() << ";" << (game.price() / 100.0) << "\n";
    }
    file.close();
}