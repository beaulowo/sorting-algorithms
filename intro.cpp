#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

const int INSERTION_SORT_THRESHOLD = 16;

void insertionSort(vector<pair<int, int>>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        auto key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j].first > key.first) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void heapSort(vector<pair<int, int>>& arr, int left, int right) {
    make_heap(arr.begin() + left, arr.begin() + right + 1);
    sort_heap(arr.begin() + left, arr.begin() + right + 1);
}

int partition(vector<pair<int, int>>& arr, int low, int high) {
    auto pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j].first < pivot.first) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void introsortUtil(vector<pair<int, int>>& arr, int begin, int end, int depthLimit) {
    int size = end - begin + 1;
    if (size < INSERTION_SORT_THRESHOLD) {
        insertionSort(arr, begin, end);
        return;
    }
    if (depthLimit == 0) {
        heapSort(arr, begin, end);
        return;
    }
    int pivot = partition(arr, begin, end);
    introsortUtil(arr, begin, pivot - 1, depthLimit - 1);
    introsortUtil(arr, pivot + 1, end, depthLimit - 1);
}

void introSort(vector<pair<int, int>>& arr) {
    int depthLimit = 2 * log(arr.size());
    introsortUtil(arr, 0, arr.size() - 1, depthLimit);
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

vector<pair<int, int>> readInput(const string& filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        int value;
        fin >> value;
        arr[i] = {value, i};
    }
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./intro_test <input_file>\n";
        return 1;
    }

    string file = argv[1];
    vector<pair<int, int>> original = readInput(file);
    double total = 0.0;

    for (int i = 0; i < 10; ++i) {
        vector<pair<int, int>> data = original;
        auto start = high_resolution_clock::now();
        introSort(data);
        auto end = high_resolution_clock::now();
        double t = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << t << " ms\n";
        total += t;
    }

    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << total / 10.0 << " ms\n";

    vector<pair<int, int>> check = original;
    introSort(check);
    cout << "Stability: " << (isStable(check) ? "Stable" : "Not stable") << endl;

    return 0;
}
