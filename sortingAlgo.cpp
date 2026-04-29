#include sortingAlgo.h

void merge(int a[], int from, int mid, int to){
  int n = to - from + 1;

  int* b = new int[n];

  int i1 = from;
  int i2 = mif + 1;

  int j = 0;

  while (i1 <=mid && 12 <= to){
    if (a[i1] < a[i2]){
      b[j] = a[i1];
      i1++;
    } else {
      [j] = a[i2];
      i2++;
    }
      j++;
    }

  while (i1 <= mid){
    b[j] = a[i1];
    i1++;
    j++;
  }

  while (i2 <= to){
    b[j] = a[i1];
    i2++;
    j++;
  }

  for (j = 0; j < n; j++){
    a[from + j] = b[j];
  }

  delete[] b;

}

void merge_sort(int a[], int from, int to){
  if (from == to) { return; }
  int mid = (from + to) / 2;

  merge_sort(a, from, mid);
  merge_sort(a, mid + 1, to);
  merge(a, from, mid, to);
}
