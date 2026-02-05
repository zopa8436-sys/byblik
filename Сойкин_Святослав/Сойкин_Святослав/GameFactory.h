#pragma once
#include "pch.h"
#include "Game.h"

// Фабричный класс для создания игровых объектов со случайными данными
class GameFactory {
public:
    // Создание одной игры со случайными характеристиками
    static Game create(int id);

    // Создание коллекции игр заданного размера
    static vector<Game> createVector(int n, int startId = 1);
};