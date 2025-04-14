#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10) return 11;
    return (gap < 1) ? 1 : gap;
}

void combSort(vector<pair<int, int>>& arr) {
    int n = arr.size();
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

vector<pair<int, int>> readInput(const string& filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<pair<int, int>> data(n);
    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        data[i] = {x, i};
    }
    return data;
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./comb_test <input_file>\n";
        return 1;
    }

    string file = argv[1];
    double total = 0.0;

    vector<pair<int, int>> original = readInput(file);

    for (int i = 0; i < 10; ++i) {
        vector<pair<int, int>> data = original;
        auto start = high_resolution_clock::now();
        combSort(data);
        auto end = high_resolution_clock::now();
        double t = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << t << " ms\n";
        total += t;
    }

    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << total / 10.0 << " ms\n";

    vector<pair<int, int>> check = original;
    combSort(check);
    cout << "Stability: " << (isStable(check) ? "Stable" : "Not stable") << endl;

    return 0;
}
