#include <iostream>
#include "WeatherData.h"
#include "Bst.h"

using namespace std;

// Function declarations
void testFunctionPointers();
void testWeatherData();
void testMapWrapper();

void testFunctionPointers() {
    cout << "=== Testing BST with Function Pointers ===" << endl;

    Bst<int> intTree;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int val : values) {
        intTree.insert(val);
    }

    cout << "In-order with function pointer: ";
    intTree.inOrder([](const int& val) {
        cout << val << " ";
    });
    cout << endl;

    vector<int> collected;
    intTree.inOrder([](const int& val, void* context) {
        vector<int>* vec = static_cast<vector<int>*>(context);
        if (val > 40) {
            vec->push_back(val);
        }
    }, &collected);

    cout << "Collected values > 40: ";
    for (int val : collected) {
        cout << val << " ";
    }
    cout << endl;
}

void testWeatherData() {
    cout << "\n=== Testing Weather Data Collection ===" << endl;

    WeatherDataCollection collection;

    collection.addWeatherRecord(WeatherRecord(Date(15, 1, 2021), 5.2, 25.3, 450.0));
    collection.addWeatherRecord(WeatherRecord(Date(16, 1, 2021), 4.8, 24.8, 420.0));
    collection.addWeatherRecord(WeatherRecord(Date(15, 2, 2021), 6.1, 23.5, 380.0));

    cout << "Total records: " << collection.getTotalRecords() << endl;

    double corr = collection.calculateSPCC(1, "S_T");
    cout << "S_T correlation for January: " << corr << endl;

    collection.displayAllData();
}

void testMapWrapper() {
    cout << "\n=== Testing Custom Map Wrapper ===" << endl;

    Map<int, string> myMap;
    myMap.insert(1, "January");
    myMap.insert(2, "February");
    myMap.insert(3, "March");

    cout << "Map size: " << myMap.size() << endl;
    cout << "Key 2: " << myMap.at(2) << endl;
    cout << "Contains key 4: " << (myMap.contains(4) ? "Yes" : "No") << endl;
}

int main() {
    cout << "ICT283 Lab 10 - Assignment 2 Preparation" << endl;
    cout << "========================================" << endl;

    testFunctionPointers();
    testWeatherData();
    testMapWrapper();

    cout << "\n=== Testing BST Pass Semantics ===" << endl;
    Bst<int> original;
    original.insert(10);
    original.insert(20);

    Bst<int> copy = original;
    cout << "Original size: " << original.size() << endl;
    cout << "Copy size: " << copy.size() << endl;

    auto modifyTree = [](Bst<int>& tree) {
        tree.insert(30);
    };
    modifyTree(original);
    cout << "After modification, original size: " << original.size() << endl;

    auto readTree = [](const Bst<int>& tree) {
        cout << "Tree contents: ";
        tree.inOrder();
        cout << endl;
    };
    readTree(original);

    return 0;
}
