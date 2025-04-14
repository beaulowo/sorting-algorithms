#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

vector<int> readInput(const string& filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<int> data(n);
    for (int i = 0; i < n; ++i)
        fin >> data[i];
    return data;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

void cocktailShakerSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0, end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./cocktail_test <input_file>" << endl;
        return 1;
    }

    vector<int> original = readInput(argv[1]);
    double total = 0.0;

    for (int i = 0; i < 10; ++i) {
        vector<int> data = original;
        auto start = high_resolution_clock::now();
        cocktailShakerSort(data);
        auto end = high_resolution_clock::now();
        double ms = duration<double, milli>(end - start).count();
        cout << "Run #" << i + 1 << ": " << fixed << setprecision(3) << ms << " ms" << endl;
        total += ms;
    }

    cout << "Average Execution Time (10 runs): " << fixed << setprecision(4) << total / 10.0 << " ms" << endl;

    vector<int> check = original;
    cocktailShakerSort(check);
    cout << "Final Result: " << (isSorted(check) ? "Sorted" : "Not sorted") << endl;

    return 0;
}
