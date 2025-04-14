#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       
    int left = 2 * i + 1;   
    int right = 2 * i + 2;   

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int n;
    inFile >> n;
    vector<int> original(n);
    for (int i = 0; i < n; ++i) inFile >> original[i];
    inFile.close();

    double totalTime = 0.0;
    vector<int> arr;

    for (int trial = 1; trial <= 10; ++trial) {
        arr = original;

        auto start = high_resolution_clock::now();
        heapSort(arr);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1000.0;
        totalTime += duration;
        cout << "Run #" << trial << ": " << duration << " ms" << endl;
    }

    double avgTime = totalTime / 10.0;
    cout << fixed << setprecision(4) << "Average Execution Time (10 runs): " << avgTime << " ms" << endl;

    cout << "Final Result: " << (isSorted(arr) ? "Sorted" : "Not sorted") << endl;

    return 0;
}
