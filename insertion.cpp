#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void insertionSort(vector<pair<int, int>>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        auto key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].first > key.first) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
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

vector<int> readInput(const string& filename) {
    ifstream in(filename);
    int n;
    in >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        in >> arr[i];
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./insertion_test <input_file>\n";
        return 1;
    }

    string filename = argv[1];
    vector<int> values = readInput(filename);
    int n = values.size();
    double total_time = 0.0;

    vector<pair<int, int>> arr;

    for (int i = 0; i < 10; ++i) {
        arr.clear();
        for (int j = 0; j < n; ++j)
            arr.emplace_back(values[j], j);

        auto start = high_resolution_clock::now();
        insertionSort(arr);
        auto end = high_resolution_clock::now();

        double ms = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << ms << " ms" << endl;
        total_time += ms;
    }

    double average = total_time / 10.0;
    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << average << " ms" << endl;
    cout << "Stability: " << (isStable(arr) ? "Stable" : "Not stable") << endl;

    return 0;
}
