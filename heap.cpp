#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void heapify(vector<pair<int, int>>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].first > arr[largest].first)
        largest = left;
    if (right < n && arr[right].first > arr[largest].first)
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<pair<int, int>>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

bool isSorted(const vector<pair<int, int>>& arr) {
    for (int i = 1; i < arr.size(); ++i)
        if (arr[i - 1].first > arr[i].first) return false;
    return true;
}

bool isStable(const vector<pair<int, int>>& sorted) {
    for (int i = 1; i < sorted.size(); ++i) {
        if (sorted[i - 1].first == sorted[i].first &&
            sorted[i - 1].second > sorted[i].second)
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
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    string filename = argv[1];
    vector<int> values = readInput(filename);
    int n = values.size();

    double totalTime = 0.0;
    vector<pair<int, int>> arr;

    for (int trial = 1; trial <= 10; ++trial) {
        arr.clear();
        for (int i = 0; i < n; ++i) arr.emplace_back(values[i], i); // (값, 인덱스)

        auto start = high_resolution_clock::now();
        heapSort(arr);
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
