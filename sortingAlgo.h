#ifndef "SORTINGALGO_H"
#define "SORTINGALGO_H"
/**
 *  @brief Merges two adjacent rangs in an array (merge)
 *  @param from; the start of the first range
 *  @param mid; the end of the first range
 *  @param to; the end of the second range
 */
void merge(int a[], int from, int mid, int to);

/**
 *  @brief sorts the elements in a range of an array
 *  @param from; start o the range to sort
 *  @param to; end of the range to sort
 */
void merge_sort(int a[], int from, int to);

#endif
