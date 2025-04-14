#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void merge(vector<pair<int, int>>& arr, int left, int mid, int right) {
    vector<pair<int, int>> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<pair<int, int>> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i].first < rightArr[j].first ||
            (leftArr[i].first == rightArr[j].first && leftArr[i].second <= rightArr[j].second)) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<pair<int, int>>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
        cerr << "Usage: ./merge_test <input_file>\n";
        return 1;
    }

    string filename = argv[1];
    vector<int> values = readInput(filename);
    int n = values.size();

    double totalTime = 0.0;
    vector<pair<int, int>> arr;

    for (int trial = 1; trial <= 10; ++trial) {
        arr.clear();
        for (int i = 0; i < n; ++i) arr.emplace_back(values[i], i);

        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, n - 1);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1000.0;
        totalTime += duration;
        cout << "Run #" << trial << ": " << duration << " ms" << endl;
    }

    double avgTime = totalTime / 10.0;
    cout << fixed << setprecision(4) << "Average Execution Time (10 runs): " << avgTime << " ms" << endl;
    cout << "Stability: " << (isStable(arr) ? "Stable ✔️" : "Not stable ❌") << endl;

    return 0;
}
