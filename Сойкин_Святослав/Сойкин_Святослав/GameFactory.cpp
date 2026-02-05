#include "pch.h"
#include "GameFactory.h"
#include "Utils.h"

// Статические коллекции данных для случайной генерации игровых объектов
static vector<string> names = {
    "The Witcher 3", "Cyberpunk 2077", "GTA V", "Minecraft", "Fortnite", "Among Us", "Doom Eternal",
    "Assassin's Creed", "FIFA 23", "Call of Duty", "The Legend of Zelda", "Super Mario"
};

static vector<string> oses = { "Windows", "Linux", "macOS", "PlayStation", "Xbox" };

static vector<string> genres = { "RPG", "Action", "Adventure", "Shooter", "Sports", "Strategy" };

static vector<string> publishers = { "CD Projekt", "Rockstar", "EA", "Activision", "Nintendo", "Bethesda" };

static vector<string> developers = { "CD Projekt RED", "Rockstar Games", "Mojang", "Epic Games", "id Software", "Ubisoft" };

static vector<string> ages = { "3+", "7+", "12+", "16+", "18+" };

// Создание одного игрового объекта со случайными характеристиками
Game GameFactory::create(int id) {
    string title = names[getRand(0, names.size() - 1)];
    string os = oses[getRand(0, oses.size() - 1)];
    int current = getCurrentYear();
    int year = current - getRand(0, 20);  // Год выпуска в пределах последних 20 лет
    string genre = genres[getRand(0, genres.size() - 1)];
    string publisher = publishers[getRand(0, publishers.size() - 1)];
    string developer = developers[getRand(0, developers.size() - 1)];
    int soldCopies = getRand(10000, 10000000);  // Количество продаж от 10k до 10M
    bool multiplayer = getRand(0, 1) != 0;
    string ageCategory = ages[getRand(0, ages.size() - 1)];
    int priceCents = getRand(1000, 10000);  // Цена от 10 до 100 в центах

    return Game(id, title, os, year, genre, publisher, developer, soldCopies, multiplayer, ageCategory, priceCents);
}

// Создание коллекции игровых объектов заданного размера
vector<Game> GameFactory::createVector(int n, int startId) {
    vector<Game> games(n);
    int id = startId;
    generate(games.begin(), games.end(), [&id]() { return create(id++); });
    return games;
}