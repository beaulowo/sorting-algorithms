#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

const int RUN = 32;

void insertionSort(vector<pair<int, int>>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        auto temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j].first > temp.first) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(vector<pair<int, int>>& arr, int l, int m, int r) {
    vector<pair<int, int>> left(arr.begin() + l, arr.begin() + m + 1);
    vector<pair<int, int>> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i].first < right[j].first ||
           (left[i].first == right[j].first && left[i].second <= right[j].second)) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void timSort(vector<pair<int, int>>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min(i + RUN - 1, n - 1));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), n - 1);
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

bool isSorted(const vector<pair<int, int>>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1].first > arr[i].first)
            return false;
    }
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./tim_test <input_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    int n;
    fin >> n;
    vector<pair<int, int>> original(n);
    for (int i = 0; i < n; ++i) {
        int val;
        fin >> val;
        original[i] = {val, i};
    }

    double total = 0.0;
    for (int i = 0; i < 10; ++i) {
        vector<pair<int, int>> arr = original;
        auto start = high_resolution_clock::now();
        timSort(arr);
        auto end = high_resolution_clock::now();
        double ms = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << ms << " ms" << endl;
        total += ms;
    }

    vector<pair<int, int>> arr = original;
    timSort(arr);
    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << total / 10.0 << " ms" << endl;
    cout << "Stability: " << (isStable(arr) ? "Stable" : "Not stable") << endl;

    return 0;
}
