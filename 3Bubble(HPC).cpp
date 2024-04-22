#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// Sequential bubble sort implementation
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel bubble sort implementation
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    // Initialize input data
    vector<int> data = {5, 1, 4, 2, 8, 3, 7, 6};

    // Perform sequential bubble sort and measure time
    auto startSequential = chrono::high_resolution_clock::now();
    bubbleSortSequential(data);
    auto endSequential = chrono::high_resolution_clock::now();
    chrono::duration<double> timeSequential = endSequential - startSequential;

    // Reset data for parallel sorting
    data = {5, 1, 4, 2, 8, 3, 7, 6};

    // Perform parallel bubble sort and measure time
    auto startParallel = chrono::high_resolution_clock::now();
    bubbleSortParallel(data);
    auto endParallel = chrono::high_resolution_clock::now();
    chrono::duration<double> timeParallel = endParallel - startParallel;

    // Output sorted array
    cout << "Sequential Sorted Array: ";
    for (int i : data) {
        cout << i << " ";
    }
    cout << endl;

    cout << "Parallel Sorted Array: ";
    for (int i : data) {
        cout << i << " ";
    }
    cout << endl;

    // Output sorting times
    cout << "Sequential Bubble Sort Time: " << timeSequential.count() << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << timeParallel.count() << " seconds" << endl;

    return 0;
}
