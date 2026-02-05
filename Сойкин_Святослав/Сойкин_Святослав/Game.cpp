#include "pch.h"
#include "Game.h"
#include "Utils.h"
#include <iomanip>
#include <sstream>

// Конструктор по умолчанию
Game::Game() : Game(0, "Unknown", "Windows", getCurrentYear(), "Action", "Unknown", "Unknown", 100000, false, "3+", 1000) {}

// Основной конструктор с валидацией входных параметров
Game::Game(int id, const string& title, const string& os, int year, const string& genre, const string& publisher,
    const string& developer, int soldCopies, bool multiplayer, const string& ageCategory, int price)
    : id_(id), title_(title), os_(os), genre_(genre), publisher_(publisher), developer_(developer),
    soldCopies_(soldCopies), multiplayer_(multiplayer), ageCategory_(ageCategory), price_(price) {
    setYear(year);
    setSoldCopies(soldCopies);
    setPrice(price);
}

// Геттеры для доступа к приватным полям класса
int Game::id() const { return id_; }
const string& Game::title() const { return title_; }
const string& Game::os() const { return os_; }
int Game::year() const { return year_; }
const string& Game::genre() const { return genre_; }
const string& Game::publisher() const { return publisher_; }
const string& Game::developer() const { return developer_; }
int Game::soldCopies() const { return soldCopies_; }
bool Game::multiplayer() const { return multiplayer_; }
const string& Game::ageCategory() const { return ageCategory_; }
int Game::price() const { return price_; }

// Сеттер для года выпуска с проверкой допустимости значения
void Game::setYear(int value) {
    if (value < 1900 || value > getCurrentYear()) {
        throw runtime_error("Недопустимый год издания");
    }
    year_ = value;
}

// Сеттер для количества проданных копий с проверкой на отрицательные значения
void Game::setSoldCopies(int value) {
    if (value < 0) {
        throw runtime_error("Количество проданных копий не может быть отрицательным");
    }
    soldCopies_ = value;
}

// Сеттер для цены с проверкой на положительное значение
void Game::setPrice(int value) {
    if (value <= 0) {
        throw runtime_error("Цена не может быть нулевой или отрицательной");
    }
    price_ = value;
}

// Строковое представление объекта
string Game::toString() const {
    ostringstream oss;
    oss << "ID:" << id_ << " Title:" << title_ << " OS:" << os_ << " Year:" << year_
        << " Genre:" << genre_ << " Pub:" << publisher_ << " Dev:" << developer_
        << " Sold:" << soldCopies_ << " Players:" << (multiplayer_ ? "Multi" : "Single")
        << " Age:" << ageCategory_ << " Price:" << (price_ / 100.0);
    return oss.str();
}

// Форматирование строки для табличного вывода
string Game::toTableRow(int row) const {
    ostringstream oss;
    // Уменьшенные ширины колонок для компактности
    vector<int> colWidths = { 2, 2, 13, 5, 2, 6, 8, 8, 6, 6, 3, 4 };
    oss << "\t| " << setw(colWidths[0]) << right << row << " | "
        << setw(colWidths[1]) << right << id_ << " | "
        << setw(colWidths[2]) << left << title_.substr(0, colWidths[2]) << " | "
        << setw(colWidths[3]) << left << os_.substr(0, colWidths[3]) << " | "
        << setw(colWidths[4]) << right << year_ << " | "
        << setw(colWidths[5]) << left << genre_.substr(0, colWidths[5]) << " | "
        << setw(colWidths[6]) << left << publisher_.substr(0, colWidths[6]) << " | "
        << setw(colWidths[7]) << left << developer_.substr(0, colWidths[7]) << " | "
        << setw(colWidths[8]) << right << soldCopies_ << " | "
        << setw(colWidths[9]) << left << (multiplayer_ ? "Multi" : "Single") << " | "
        << setw(colWidths[10]) << left << ageCategory_ << " | "
        << setw(colWidths[11]) << right << fixed << setprecision(2) << (price_ / 100.0) << " |";
    return oss.str();
}

// Шапка таблицы
string Game::header() {
    return "\t+----+----+---------------+-------+------+--------+----------+----------+--------+--------+-----+-------+\n"
           "\t| №  | ID | Название      |  ОС   | Год  | Жанр   | Издатель | Разраб.  |Проданно| Игроки |Возр.| Цена  |\n"
           "\t+----+----+---------------+-------+------+--------+----------+----------+--------+--------+-----+-------+\n";
}

// Подвал таблицы
string Game::footer() {
    return "\t+----+----+---------------+-------+------+--------+----------+----------+--------+--------+-----+-------+\n";
}