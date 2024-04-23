#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// Merge function to merge two sorted subarrays
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Sequential merge sort implementation
void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel merge sort implementation
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);
            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    // Initialize input data
    vector<int> data = {5, 1, 4, 2, 8, 3, 7, 6};

    // Copy input data for sequential sorting
    vector<int> dataSequential = data;

    // Perform sequential merge sort and measure time
    auto startSequential = chrono::high_resolution_clock::now();
    mergeSortSequential(dataSequential, 0, dataSequential.size() - 1);
    auto endSequential = chrono::high_resolution_clock::now();
    chrono::duration<double> timeSequential = endSequential - startSequential;

    // Reset data for parallel sorting
    vector<int> dataParallel = data;

    // Perform parallel merge sort and measure time
    auto startParallel = chrono::high_resolution_clock::now();
    mergeSortParallel(dataParallel, 0, dataParallel.size() - 1);
    auto endParallel = chrono::high_resolution_clock::now();
    chrono::duration<double> timeParallel = endParallel - startParallel;

    // Output sorted arrays
    cout << "Sequential Sorted Array: ";
    for (int i : dataSequential) {
        cout << i << " ";
    }
    cout << endl;

    cout << "Parallel Sorted Array: ";
    for (int i : dataParallel) {
        cout << i << " ";
    }
    cout << endl;

    // Output sorting times
    cout << "Sequential Merge Sort Time: " << timeSequential.count() << " seconds" << endl;
    cout << "Parallel Merge Sort Time: " << timeParallel.count() << " seconds" << endl;

    return 0;
}
