#include sortingAlgo.h
#include <vector>

// Merge function
void merge(std::vector<int>& a, int from, int mid, int to) {
    int n = to - from + 1;
    std::vector<int> b(n);

    int i1 = from;
    int i2 = mid + 1;
    int j = 0;

    while (i1 <= mid && i2 <= to) {
        if (a[i1] < a[i2]) {
            b[j] = a[i1];
            i1++;
        } else {
            b[j] = a[i2];
            i2++;
        }
        j++;
    }

    while (i1 <= mid) {
        b[j] = a[i1];
        i1++;
        j++;
    }

    while (i2 <= to) {
        b[j] = a[i2];  // fixed
        i2++;
        j++;
    }

    for (int k = 0; k < n; k++) {
        a[from + k] = b[k];
    }
}

// Recursive merge sort
void merge_sort(std::vector<int>& a, int from, int to) {
    if (from >= to) return;

    int mid = (from + to) / 2;

    merge_sort(a, from, mid);
    merge_sort(a, mid + 1, to);
    merge(a, from, mid, to);
}
