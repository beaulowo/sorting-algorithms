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

void combSort(vector<int>& arr) {
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

vector<int> readInput(const string& filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<int> data(n);
    for (int i = 0; i < n; ++i) fin >> data[i];
    return data;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./comb_test <input_file>\n";
        return 1;
    }

    string file = argv[1];
    double total = 0.0;

    for (int i = 0; i < 10; ++i) {
        vector<int> data = readInput(file);
        auto start = high_resolution_clock::now();
        combSort(data);
        auto end = high_resolution_clock::now();
        double t = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << t << " ms\n";
        total += t;
    }

    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << total / 10.0 << " ms\n";

    vector<int> check = readInput(file);
    combSort(check);
    cout << "Final Result: " << (isSorted(check) ? "Sorted" : "Not sorted") << endl;

    return 0;
}
