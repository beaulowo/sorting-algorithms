#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void bubbleSort(vector<pair<int, int>>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].first > arr[j + 1].first) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

bool isSorted(const vector<pair<int, int>>& arr) {
    for (int i = 1; i < arr.size(); ++i)
        if (arr[i - 1].first > arr[i].first) return false;
    return true;
}

bool isStable(const vector<pair<int, int>>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i - 1].first == arr[i].first &&
            arr[i - 1].second > arr[i].second)
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int n;
    inFile >> n;
    vector<int> values(n);
    for (int i = 0; i < n; ++i) inFile >> values[i];
    inFile.close();

    double totalTime = 0.0;
    vector<pair<int, int>> arr;

    for (int trial = 1; trial <= 10; ++trial) {
        arr.clear();
        for (int i = 0; i < n; ++i) arr.emplace_back(values[i], i);

        auto start = high_resolution_clock::now();
        bubbleSort(arr);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1000.0;
        totalTime += duration;
        cout << "Run #" << trial << ": " << duration << " ms" << endl;
    }

    double avgTime = totalTime / 10.0;
    cout << fixed << setprecision(4) << "Average Execution Time (10 runs): " << avgTime << " ms" << endl;
    cout << "Stability: " << (isStable(arr) ? "Stable" : "Not stable") << endl;

    return 0;
}
