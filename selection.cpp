#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void selectionSort(vector<pair<int, int>>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].first < arr[minIdx].first)
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

bool isSorted(const vector<pair<int, int>>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1].first > arr[i].first) return false;
    return true;
}

bool isStable(const vector<pair<int, int>>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
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
        cerr << "Usage: ./selection_test <input_file>\n";
        return 1;
    }

    string filename = argv[1];
    vector<int> input = readInput(filename);
    int n = input.size();
    double total_time = 0.0;

    for (int i = 0; i < 10; ++i) {
        vector<pair<int, int>> arr(n);
        for (int j = 0; j < n; ++j)
            arr[j] = {input[j], j};

        auto start = high_resolution_clock::now();
        selectionSort(arr);
        auto end = high_resolution_clock::now();

        double ms = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << ms << " ms" << endl;
        total_time += ms;
    }

    double average = total_time / 10.0;
    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << average << " ms" << endl;

    vector<pair<int, int>> arr(n);
    for (int j = 0; j < n; ++j)
        arr[j] = {input[j], j};
    selectionSort(arr);
    cout << "Stability: " << (isStable(arr) ? "Stable" : "Not stable") << endl;

    return 0;
}
