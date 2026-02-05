#pragma once
#include "pch.h"
#include "Game.h"

// Класс для управления магазином компьютерных игр
class Store {
    string name_;      // Название магазина
    string address_;   // Адрес магазина
    vector<Game> games_; // Коллекция игр в магазине

public:
    Store();  // Конструктор по умолчанию
    Store(const string& filename);  // Конструктор с загрузкой данных из файла

    // Геттеры для доступа к данным магазина
    const string& name() const;
    const string& address() const;
    const vector<Game>& games() const;

    // Методы управления коллекцией игр
    void addGame(const Game& game);  // Добавление игры в коллекцию
    void editGame(int id);  // Редактирование игры по ID
    void removeGame(int id);  // Удаление игры по ID

    // Методы сортировки коллекции игр
    void sortById();  // Сортировка по возрастанию ID
    void sortByYearDesc();  // Сортировка по убыванию года выпуска
    void sortByPriceAsc();  // Сортировка по возрастанию цены
    void sortBySoldDesc();  // Сортировка по убыванию количества продаж

    // Методы поиска/фильтрации коллекции игр
    vector<Game> findByPriceRange(int minPrice, int maxPrice) const;  // Поиск по диапазону цен (в центах)
    vector<Game> findByYear(int year) const;  // Поиск по году выпуска
    vector<Game> findByOs(const string& os) const;  // Поиск по операционной системе

    // Вывод информации о магазине и его коллекции
    void print(ostream& os = cout) const;

    // Методы работы с файлами
    bool loadFromCSV(const string& filename);  // Загрузка данных из CSV файла
    void saveToCSV(const string& filename) const;  // Сохранение данных в CSV файл
};