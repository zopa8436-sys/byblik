#pragma once
#include "pch.h"
#include "Store.h"
#include <ostream>

// Класс приложения для управления магазином игр
class App {
private:
    Store store_;  // Объект магазина
    string filename_;  // Имя файла

public:
    App(const string& filename = "games.csv");

    // Вывод информации о магазине и его коллекции игр
    void printStore(ostream& os = cout) const;

    // Инициализация коллекции игр с использованием фабрики
    void initCollection();

    // Добавление новой игры в коллекцию магазина
    void addGame();

    // Редактирование существующей игры по ID
    void editGame();

    // Удаление игры из коллекции по ID
    void removeGame();

    // Сортировка коллекции игр по возрастанию ID
    void sortById();

    // Сортировка коллекции игр по убыванию года выпуска
    void sortByYearDesc();

    // Сортировка коллекции игр по возрастанию цены
    void sortByPriceAsc();

    // Сортировка коллекции игр по убыванию количества проданных копий
    void sortBySoldDesc();

    // Фильтрация игр по диапазону цен
    void filterByPriceRange();

    // Фильтрация игр по году выпуска
    void filterByYear();

    // Фильтрация игр по операционной системе
    void filterByOs();

    // Сохранение данных магазина в CSV файл
    void saveStore();

    // Загрузка данных магазина из CSV файла
    void loadStore();
};