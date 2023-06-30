#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Lo1As.cpp"
#include "Lo2As.cpp"
#include "Lo3As.cpp"
#include "Lo4As.cpp"

int main() {
    int choice = 0;
    while (choice != -1)
    {
        //setlocale(LC_ALL, "rus");
        system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода   
    start:
        system("cls");
        // Отображение меню
        std::cout << "Организация ЭВМ и вычислительных систем" << std::endl;
        std::cout << "1. Lab1" << std::endl;
        std::cout << "2. Lab2" << std::endl;
        std::cout << "3. Lab3" << std::endl;
        std::cout << "4. Lab4" << std::endl;
        std::cout << "5. Выход" << std::endl;
        std::cout << "Выберите действие:" << std::endl;
        std::cin >> choice;
        //Проверяем выбор пользователя
        while (choice < 1 || choice > 5) {
            std::cout << "Выберите действие:" << std::endl;
            std::cin >> choice;
        }
        system("cls");

        // Выполняем выбранную операцию
        switch (choice) {
        case 1:
            Lo1As();
            goto start;
        case 2:
            Lo2As();
            goto start; 
        case 3:
            Lo3As();
            goto start;
        case 4:
            Lo4As();
            goto start;
        case 5:
            // Выход
            choice = -1;
        }
    }
    return 0;
}