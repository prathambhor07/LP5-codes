#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {
    // Initialize input data
    vector<int> data = {5, 1, 4, 2, 8, 3, 7, 6};

    // Initialize variables for min, max, sum, and average
    int min_value = data[0];
    int max_value = data[0];
    int sum = 0;

    // Start performance measurement for min operation
    auto startMin = chrono::high_resolution_clock::now();
    // Find min value
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] < min_value) {
            min_value = data[i];
        }
    }
    // End performance measurement for min operation
    auto endMin = chrono::high_resolution_clock::now();
    chrono::duration<double> timeMin = endMin - startMin;

    // Start performance measurement for max operation
    auto startMax = chrono::high_resolution_clock::now();
    // Find max value
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] > max_value) {
            max_value = data[i];
        }
    }
    // End performance measurement for max operation
    auto endMax = chrono::high_resolution_clock::now();
    chrono::duration<double> timeMax = endMax - startMax;

    // Start performance measurement for sum operation
    auto startSum = chrono::high_resolution_clock::now();
    // Calculate sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    // End performance measurement for sum operation
    auto endSum = chrono::high_resolution_clock::now();
    chrono::duration<double> timeSum = endSum - startSum;

    // Start performance measurement for average operation
    auto startAvg = chrono::high_resolution_clock::now();
    // Calculate average
    double average = static_cast<double>(sum) / data.size();
    // End performance measurement for average operation
    auto endAvg = chrono::high_resolution_clock::now();
    chrono::duration<double> timeAvg = endAvg - startAvg;

    // Output results and performance measures
    cout << "Minimum: " << min_value << endl;
    cout << "Time taken for finding minimum: " << timeMin.count() << " seconds" << endl;
    cout << "Maximum: " << max_value << endl;
    cout << "Time taken for finding maximum: " << timeMax.count() << " seconds" << endl;
    cout << "Sum: " << sum << endl;
    cout << "Time taken for calculating sum: " << timeSum.count() << " seconds" << endl;
    cout << "Average: " << average << endl;
    cout << "Time taken for calculating average: " << timeAvg.count() << " seconds" << endl;


    return 0;
}
