//============================================================================
// Name        : Assignment_10.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Heap Sort 
//============================================================================
#include <iostream>
#include<vector>
using namespace std;

void heapify(vector<int> &arr, int n, int index) {
    while (index < n) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(arr[index], arr[largest]);
            index = largest;  // Move down the tree
        } else {
            break;  // No further violation
        }
    }
}


void heapsort(vector<int> &arr, int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void print(vector<int> &arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    // cin >> n;

    vector<int> arr = {2,4,7,1};
    n=arr.size();

    // for (int i = 0; i < n; i++) {
    //     cin >> arr[i];
    // }

    heapsort(arr, n);

    print(arr, n);

    return 0;
}
