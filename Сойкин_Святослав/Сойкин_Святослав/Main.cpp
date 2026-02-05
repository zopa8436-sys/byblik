#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"

// Main entry point
int main() {
    init(L"Практика - Магазин Игр");
    App app("games.csv");

    // Commands
    enum Commands : int {
        CMD_INIT = 1001,
        CMD_ADD,
        CMD_EDIT,
        CMD_REMOVE,
        CMD_SORT_ID,
        CMD_SORT_YEAR_DESC,
        CMD_SORT_PRICE_ASC,
        CMD_SORT_SOLD_DESC,
        CMD_FILTER_PRICE,
        CMD_FILTER_YEAR,
        CMD_FILTER_OS,
        CMD_SAVE,
        CMD_LOAD
    };

    // Items
    vector<MenuItem> items = {
        MenuItem(CMD_INIT, "Формирование коллекции"),
        MenuItem(CMD_ADD, "Добавление игры"),
        MenuItem(CMD_EDIT, "Редактирование игры по ID"),
        MenuItem(CMD_REMOVE, "Удаление игры по ID"),
        MenuItem(CMD_SORT_ID, "Упорядочивание по ID"),
        MenuItem(CMD_SORT_YEAR_DESC, "Упорядочивание по убыванию года"),
        MenuItem(CMD_SORT_PRICE_ASC, "Упорядочивание по возрастанию цены"),
        MenuItem(CMD_SORT_SOLD_DESC, "Упорядочивание по убыванию проданных копий"),
        MenuItem(CMD_FILTER_PRICE, "Выборка по диапазону цены"),
        MenuItem(CMD_FILTER_YEAR, "Выборка по году издания"),
        MenuItem(CMD_FILTER_OS, "Выборка по ОС"),
        MenuItem(CMD_SAVE, "Сохранение в файл"),
        MenuItem(CMD_LOAD, "Загрузка из файла"),
        MenuItem(Menu::CMD_QUIT, "Выход")
    };

    Menu mainMenu(COORD{ 5, 5 }, items, infoColor, hintColor);

    while (true) {
        try {
            cout << color(mainColor) << cls;
            showNavBarMessage(hintColor, acctColor, "  Магазин Игр  |  ~Esc~ ~F10~ Выход");
            int cmd = mainMenu.navigate();
            cout << color(mainColor) << cls;
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
            case CMD_INIT:
                app.initCollection();
                break;
            case CMD_ADD:
                app.addGame();
                break;
            case CMD_EDIT:
                app.editGame();
                break;
            case CMD_REMOVE:
                app.removeGame();
                break;
            case CMD_SORT_ID:
                app.sortById();
                break;
            case CMD_SORT_YEAR_DESC:
                app.sortByYearDesc();
                break;
            case CMD_SORT_PRICE_ASC:
                app.sortByPriceAsc();
                break;
            case CMD_SORT_SOLD_DESC:
                app.sortBySoldDesc();
                break;
            case CMD_FILTER_PRICE:
                app.filterByPriceRange();
                break;
            case CMD_FILTER_YEAR:
                app.filterByYear();
                break;
            case CMD_FILTER_OS:
                app.filterByOs();
                break;
            case CMD_SAVE:
                app.saveStore();
                break;
            case CMD_LOAD:
                app.loadStore();
                break;
            }
            getKey("");
        }
        catch (exception& ex) {
            cout << color(mainColor) << cls;
            showNavBarMessage(hintColor, "  Ошибка, нажмите клавишу...");
            int width = 64;
            ostringstream oss;
            oss << "\n\n\n\n" << left
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << "    [Ошибка]" << "\n"
                << "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << " " << "\n" << right;
            showMessage(oss.str().c_str(), errColor, mainColor);
            getKey("");
        }
    }

    cls();
    return 0;
}