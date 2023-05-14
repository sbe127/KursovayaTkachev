#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

int bin_search(const std::vector<int>& a, int elem, int& compares) {
    int left = 0;
    int right = a.size() - 1;
    while (left < right) {
        int m = (left + right) / 2;
        if (a[m] > elem) {
            left = m + 1;
        }
        else {
            right = m;
        }
        compares++;
    }
    if (a[left] != elem) {
        return a.size();
    }
    return left;
}

int linear_search(const std::vector<int>& a, int elem, int& compares) {
    for (int i = 0; i < a.size(); i++) {
        compares++;
        if (a[i] == elem) {
            return i;
        }
    }
    return a.size();
}

std::vector<int> generate_sorted_array(int size) {
    std::vector<int> ans;
    if (size < 1) {
        return ans;
    }
    std::ofstream data("input_" + std::to_string(size) + "sorted.txt");
    int last = std::rand();
    data << last << ' ';
    for (int i = 1; i < size; i++) {
        last += std::abs(std::rand());
        data << last << ' ';
    }
    data.close();
    std::ifstream fin("input_" + std::to_string(size) + "sorted.txt");
    int elem;
    while (fin >> elem) {
        ans.push_back(elem);
    }
    return ans;
}

std::vector<int> generate_random_array(int size) {
    std::vector<int> ans;
    if (size < 1) {
        return ans;
    }
    std::ofstream data("input_" + std::to_string(size) + "unsorted.txt");
    for (int i = 0; i < size; i++) {
        data << std::rand() << ' ';
    }
    data.close();
    std::ifstream fin("input_" + std::to_string(size) + "unsorted.txt");
    int elem;
    while (fin >> elem) {
        ans.push_back(elem);
    }
    return ans;
}

int main() {
    std::srand(std::clock());
    while (true) {
        std::cout << "Enter 1 if you want to test searcher on sorted array\n";
        std::cout << "Enter 2 if you want to test searcher on unsorted array with a lot of searches\n";
        std::cout << "Enter 0 if you want exit\n";
        int type;
        std::cin >> type;
        if (type == 1) {
            //=======Sorted array (1 search)===========
            std::cout << "Enter the size of array\n";
            int size;
            std::cin >> size;
            std::vector<int> a = generate_sorted_array(size);
            std::cout << "Enter the index of elements which you want to found\n";
            std::cout << "Enter random number if you want to search not existed element\n";
            int ind;
            std::cin >> ind;
            int elem;
            if (ind < 0 || ind > size) {
                ind = -1;
                elem = -100000000;
            }
            else {
                elem = a[ind];
            }
            int compares = 0;
            std::ofstream fout("output_" + std::to_string(size) + "sorted.txt");
            auto start_time = std::clock();
            int bin_search_ind = bin_search(a, elem, compares);
            fout << "Sorted array search\n";
            fout << "Bin search\n";
            fout << "Time: " << std::clock() - start_time << " ms" << '\n';
            fout << "Compares : " << compares << '\n' << '\n';
            start_time = std::clock();
            compares = 0;
            linear_search(a, elem, compares);
            fout << "Linear search\n";
            fout << "Time: " << std::clock() - start_time << " ms" << '\n';
            fout << "Compares : " << compares << '\n' << '\n';
        }
        else if (type == 2) {
            //========Unsorted array (a lot of searches)===========
            std::cout << "Enter the size of array\n";
            int size;
            std::cin >> size;
            std::vector<int> a = generate_random_array(size);
            int searchesAmount;
            std::cout << "Enter a lot of searches to found\n";
            std::cin >> searchesAmount;

            int compares = 0;
            auto start_time = std::clock();
            for (int i = 0; i < searchesAmount; i++) {
                int ind = std::rand() % size + 1;
                int elem;
                if (ind == size) {
                    elem = -1000000000;
                }
                else {
                    elem = a[ind];
                }
                linear_search(a, elem, compares);
            }
            std::ofstream fout("output_" + std::to_string(size) + "unsorted.txt");
            fout << "Random array search\n";
            fout << "Linear search\n";
            fout << "Time: " << std::clock() - start_time << " ms" << '\n';
            fout << "Compares : " << compares << '\n' << '\n';
            start_time = std::clock();
            compares = 0;
            std::sort(a.begin(), a.end());
            for (int i = 0; i < searchesAmount; i++) {
                int ind = std::rand() % size + 1;
                int elem;
                if (ind == size) {
                    elem = -1000000000;
                }
                else {
                    elem = a[ind];
                }
                bin_search(a, elem, compares);
            }
            fout << "Bin search\n";
            fout << "Time: " << std::clock() - start_time << " ms" << '\n';
            fout << "Compares : " << compares << '\n' << '\n';
        }
        else {
            break;
        }

    }

}