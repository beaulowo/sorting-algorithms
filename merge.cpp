#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    vector<int> arr;
    int value;
    while (inFile >> value) arr.push_back(value);
    inFile.close();

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<microseconds>(end - start).count() / 1000.0; // ms 단위
    cout << "Execution time: " << duration << " ms" << endl;

    if (isSorted(arr)) cout << "Result: Sorted" << endl;
    else cout << "Result: Not Sorted" << endl;

    return 0;
}
