#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int partition(vector<pair<int, int>>& arr, int low, int high) {
    int pivot = arr[high].first;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].first <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<pair<int, int>>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<pair<int, int>>& arr) {
    quickSort(arr, 0, arr.size() - 1);
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
        cerr << "Usage: ./quick_test <input_file>\n";
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
        quickSort(arr);
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
    quickSort(arr);
    cout << "Stability: " << (isStable(arr) ? "Stable" : "Not stable") << endl;

    return 0;
}
