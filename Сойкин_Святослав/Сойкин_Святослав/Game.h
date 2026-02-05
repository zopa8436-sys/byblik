#pragma once
#include "pch.h"
#include <stdexcept>
#include <string>

// Класс для хранения и управления информацией о компьютерной игре
class Game {
    int id_;                // Уникальный идентификатор игры
    string title_;     // Название игры
    string os_;        // Поддерживаемые операционные системы
    int year_;              // Год выпуска игры
    string genre_;     // Жанровая принадлежность игры
    string publisher_; // Издатель игры
    string developer_; // Разработчик игры
    int soldCopies_;        // Количество проданных копий
    bool multiplayer_;      // Режим игры (true для Multiplayer)
    string ageCategory_; // Возрастное ограничение
    int price_;             // Цена в центах

public:
    // Конструктор по умолчанию
    Game();

    // Основной конструктор с параметрами
    Game(int id, const string& title, const string& os, int year, const string& genre, const string& publisher,
        const string& developer, int soldCopies, bool multiplayer, const string& ageCategory, int price);

    // Геттеры для доступа к приватным полям класса
    int id() const;
    const string& title() const;
    const string& os() const;
    int year() const;
    const string& genre() const;
    const string& publisher() const;
    const string& developer() const;
    int soldCopies() const;
    bool multiplayer() const;
    const string& ageCategory() const;
    int price() const;  // in cents

    // Сеттеры с проверкой валидности входных данных
    void setYear(int value);
    void setSoldCopies(int value);
    void setPrice(int value);

    // Методы для форматированного вывода информации об игре
    string toString() const;  // Строковое представление объекта
    string toTableRow(int row) const;  // Форматирование строки для табличного вывода

    // Статические методы для отрисовки структуры таблицы
    static string header();  // Шапка таблицы как string
    static string footer();  // Подвал таблицы как string
};