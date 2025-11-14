#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Dish {
    std::string name;
    std::string type;
    double price;
};

void saveResults(const std::string& text) {
    std::ofstream out("output.txt", std::ios::app);
    out << text << "\n";
    out.close();
}

void addDish() {
    std::ofstream file("menu.txt", std::ios::app);

    while (true) {
        Dish d;
        std::cout << "Введите название блюда (пустая строка — остановка): ";
        std::getline(std::cin, d.name);
        if (d.name.empty()) break;

        std::cout << "Введите тип (Закуски / Основные блюда / Десерты / Напитки / Для детей): ";
        std::getline(std::cin, d.type);

        std::cout << "Введите цену: ";
        std::cin >> d.price;
        std::cin.ignore();

        file << d.name << ";" << d.type << ";" << d.price << "\n";
    }

    file.close();
    saveResults("Добавление блюд завершено.");
}

std::vector<Dish> loadDishes() {
    std::vector<Dish> dishes;
    std::ifstream file("menu.txt");

    std::string line;
    while (std::getline(file, line)) {
        Dish d;
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);

        d.name = line.substr(0, p1);
        d.type = line.substr(p1 + 1, p2 - p1 - 1);
        d.price = stod(line.substr(p2 + 1));

        dishes.push_back(d);
    }

    return dishes;
}

void searchDish() {
    std::cout << "Введите название блюда для поиска: ";
    std::string query;
    std::getline(std::cin, query);

    auto dishes = loadDishes();

    for (auto &d : dishes) {
        if (d.name == query) {
            std::cout << "Найдено: " << d.name << ", " << d.type << ", " << d.price << "\n";
            saveResults("Найдено блюдо: " + d.name);
            return;
        }
    }
    std::cout << "Блюдо не найдено.\n";
    saveResults("Блюдо не найдено: " + query);
}

void sortDishes() {
    auto dishes = loadDishes();

    int choice;
    std::cout << "Сортировать по:\n1 — типу\n2 — цене\nВыбор: ";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        std::sort(dishes.begin(), dishes.end(), [](Dish &a, Dish &b) {
            return a.type < b.type;
        });
        saveResults("Сортировка выполнена по типу.");
    } else {
        std::sort(dishes.begin(), dishes.end(), [](Dish &a, Dish &b) {
            return a.price < b.price;
        });
        saveResults("Сортировка выполнена по цене.");
    }

    std::ofstream file("menu.txt", std::ios::trunc);
    for (auto &d : dishes) {
        file << d.name << ";" << d.type << ";" << d.price << "\n";
    }
    file.close();

    std::cout << "Сортировка выполнена!\n";
}

void filterPrice() {
    std::cout << "Введите максимальную цену: ";
    double maxPrice;
    std::cin >> maxPrice;
    std::cin.ignore();

    auto dishes = loadDishes();

    std::cout << "Блюда дешевле или равные " << maxPrice << ":\n";

    std::string results;
    for (auto &d : dishes) {
        if (d.price <= maxPrice) {
            std::cout << d.name << " — " << d.type << " — " << d.price << "\n";
            results += d.name + "\n";
        }
    }

    saveResults("Вывод блюд по цене завершён.");
}

int main() {

    int choice;

    do {
        std::cout << "\n====== МЕНЮ ======\n";
        std::cout << "1 — Добавить блюда\n";
        std::cout << "2 — Поиск блюда\n";
        std::cout << "3 — Сортировка блюд\n";
        std::cout << "4 — Вывод по цене\n";
        std::cout << "0 — Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: addDish(); break;
            case 2: searchDish(); break;
            case 3: sortDishes(); break;
            case 4: filterPrice(); break;
            case 0: std::cout << "Выход...\n"; break;
            default: std::cout << "Неверный ввод.\n"; 
        }

    } while (choice != 0);

    return 0;
}