#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <locale>

class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() <= 1) return;
        std::vector<int> left(array.begin(), array.begin() + array.size() / 2);
        std::vector<int> right(array.begin() + array.size() / 2, array.end());

        std::thread leftThread([&]() { Sort(left); });
        std::thread rightThread([&]() { Sort(right); });

        leftThread.join();
        rightThread.join();

        Merge(array, left, right);
    }

private:
    void Merge(std::vector<int>& array, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            array[k++] = left[i++];
        }
        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::vector<int> array(10);
    std::cout << "Введите 10 целых чисел:" << std::endl;
    for (int& num : array) {
        std::cin >> num;
    }

    MergeSort mergeSort;
    std::thread mergeSortThread([&]() { mergeSort.Sort(array); });
    mergeSortThread.join();

    std::cout << "Отсортированный массив:" << std::endl;
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
