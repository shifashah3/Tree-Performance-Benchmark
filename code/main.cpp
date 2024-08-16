#include "avl.hpp"
#include "scapegoat.hpp"
#include "RBT.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    AVL avl_tree;
    ScapeGoatTree scapegoat;
    RedBlackTree RBT;

    std::ifstream file("data3.txt");

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string word;
    auto start_insert = std::chrono::steady_clock::now();
    while (file >> word)
    {
        avl_tree.insert(word);
    }

    auto end_insert = std::chrono::steady_clock::now();

    std::cout << "AVL Insertion took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_insert - start_insert).count()
              << " microseconds" << std::endl;

    // Rewind the file cursor to the beginning of the file
    file.clear(); // Clear any error flags
    file.seekg(0, std::ios::beg);

    auto start_insert2 = std::chrono::steady_clock::now();

    while (file >> word)
    {
        scapegoat.insert(word);
    }
    auto end_insert2 = std::chrono::steady_clock::now();
    std::cout << "Scapegoat Insertion took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_insert2 - start_insert2).count()
              << " microseconds" << std::endl;

     // Rewind the file cursor to the beginning of the file
    file.clear(); // Clear any error flags
    file.seekg(0, std::ios::beg);

    auto start_insert3 = std::chrono::steady_clock::now();

    while (file >> word)
    {
        RBT.insert(word);
    }
    auto end_insert3 = std::chrono::steady_clock::now();
    file.close();

    std::cout << "RedBlack Insertion took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_insert3 - start_insert3).count()
              << " microseconds" << std::endl;

    // Search
    std::string input1;
    std::cout << "Enter a word to search" << std::endl;
    std::cin >> input1;
    auto start_search = std::chrono::steady_clock::now();
    bool found = avl_tree.search(input1);
    auto end_search = std::chrono::steady_clock::now();
    if (found)
    {
        std::cout << "Word found and AVL search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search - start_search).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and AVL search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search - start_search).count()
                  << " microseconds" << std::endl;
    }

    auto start_search2 = std::chrono::steady_clock::now();
    bool found2 = scapegoat.search(input1);
    auto end_search2 = std::chrono::steady_clock::now();
    if (found2)
    {
        std::cout << "Word found and ScapeGoat search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search2 - start_search2).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and ScapeGoat search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search2 - start_search2).count()
                  << " microseconds" << std::endl;
    }

    auto start_search3 = std::chrono::steady_clock::now();
    bool found3 = RBT.searchTree(input1);
    auto end_search3 = std::chrono::steady_clock::now();
    if (found3)
    {
        std::cout << "Word found and RedBlack search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search3 - start_search3).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and RedBlack search took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_search3 - start_search3).count()
                  << " microseconds" << std::endl;
    }

    // Deletion
    std::string input2;
    std::cout << "Enter a word to delete" << std::endl;
    std::cin >> input2;
    auto start_delete = std::chrono::steady_clock::now();
    bool deleted = avl_tree.remove(input2);
    auto end_delete = std::chrono::steady_clock::now();
    if (deleted)
    {
        std::cout << "Word deleted and AVL delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete - start_delete).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and AVL delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete - start_delete).count()
                  << " microseconds" << std::endl;
    }

    auto start_delete2 = std::chrono::steady_clock::now();
    bool deleted2 = scapegoat.deleteNode(input2);
    auto end_delete2 = std::chrono::steady_clock::now();
    if (deleted2)
    {
        std::cout << "Word deleted and ScapeGoat delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete2 - start_delete2).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and ScapeGoat delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete2 - start_delete2).count()
                  << " microseconds" << std::endl;
    }

    auto start_delete3 = std::chrono::steady_clock::now();
    bool deleted3 = RBT.deleteNode(input2);
    auto end_delete3 = std::chrono::steady_clock::now();
    if (deleted3)
    {
        std::cout << "Word deleted and RedBlack delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete3 - start_delete3).count()
                  << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Word not found and RedBlack delete took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end_delete3 - start_delete3).count()
                  << " microseconds" << std::endl;
    }

    file.close();

    return 0;
}
