#include <iostream>
#include "btree.h"

void runTests() {
    // Тест 1: Вставка уникальных элементов
    std::cout << "Test 1: Вставка уникальных элементов\n";
    {
        BTree tree(2); // Минимальная степень t = 2
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);

        if (tree.size() != 5) {
            std::cout << "Test 1 Failed: Expected size = 5, Got size = " << tree.size() << "\n";
        } else {
            std::cout << "Test 1 Passed\n";
        }
    }
    {
        BTree tree(2); // Минимальная степень t = 2
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);

        if (tree.size() != 5) {
            std::cout << "Test 1 Failed: Expected size = 5, Got size = " << tree.size() << "\n";
        } else {
            std::cout << "Test 1 Passed\n";
        }
    }

    // Тест 2: Вставка одинаковых элементов
    {
        BTree tree(2);
        tree.insert(10);
        tree.insert(10);
        tree.insert(10);

        if (tree.size() != 1) {
            std::cout << "Test 2 Failed: Expected size = 1, Got size = " << tree.size() << "\n";
        } else {
            std::cout << "Test 2 Passed\n";
        }
    }

    // Тест 3: Сумма ключей дерева
    {
        BTree tree(2);
        tree.insert(5);
        tree.insert(15);
        tree.insert(25);
        tree.insert(35);

        int64_t expectedSum = 5 + 15 + 25 + 35;
        if (tree.sum() != expectedSum) {
            std::cout << "Test 3 Failed: Expected sum = " << expectedSum << ", Got sum = " << tree.sum() << "\n";
        } else {
            std::cout << "Test 3 Passed\n";
        }
    }

    // Тест 4: Проверка корректности структуры дерева после сплита корня
    {
        BTree tree(2);
        for (int i = 1; i <= 10; ++i) {
            tree.insert(i);
        }

        if (tree.size() != 10) {
            std::cout << "Test 4 Failed: Expected size = 10, Got size = " << tree.size() << "\n";
        } else {
            std::cout << "Test 4 Passed\n";
        }
    }

    // Тест 5: Пустое дерево
    {
        BTree tree(2);

        if (tree.size() != 0 || tree.sum() != 0) {
            std::cout << "Test 5 Failed: Expected size = 0 and sum = 0\n";
        } else {
            std::cout << "Test 5 Passed\n";
        }
    }

    // Тест 6: Дерево с минимальной степенью 2 и большим количеством узлов
    {
        BTree tree(2);
        for (int i = 1; i <= 50; ++i) {
            tree.insert(i);
        }

        int64_t expectedSum = 50 * (50 + 1) / 2; // Сумма арифметической прогрессии
        if (tree.size() != 50 || tree.sum() != expectedSum) {
            std::cout << "Test 6 Failed: Expected size = 50, sum = " << expectedSum << "\n";
        } else {
            std::cout << "Test 6 Passed\n";
        }
    }

    // Тест 7: Дерево с отрицательными ключами
    {
        BTree tree(2);
        for (int i = -25; i <= 25; ++i) {
            tree.insert(i);
        }

        int64_t expectedSum = 0; // Сумма чисел от -25 до 25 равна 0
        if (tree.size() != 51 || tree.sum() != expectedSum) {
            std::cout << "Test 7 Failed: Expected size = 51, sum = " << expectedSum << "\n";
        } else {
            std::cout << "Test 7 Passed\n";
        }
    }
}

int main() {
    runTests();
    return 0;
}