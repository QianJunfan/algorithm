/* Jan 02, 2026
 * Study Sorting Algorithms
 */

/* $ learn 3 $ better bubble sorting (review) */
void better_bubble_sort(int *arr, int n)
{
	for (int i = 0; i < n - 1; i++) {
		int flg = 0;
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flg = 1;
			}
		}

		if (!flg)
			break;
	}
}

/* $ learn 4 $ selection sorting */
void selection_sort(int *arr, int n)
{
	int ptr;
	int tmp;

	for (int i = 0; i < n; i++) {
		ptr = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[ptr])
				ptr = j;
		}

		if (ptr != i) {
			tmp = arr[i];
			arr[i] = arr[ptr];
			arr[ptr] = tmp;
		}
	}
}

/* $ learn 5 $ insertion sorting */
void insertion_sort(int *arr, int n)
{
	for (int i = 1; i < n; i++) {
		int item = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > item) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = item;
	}
}

/* $ learn 6 $ merge sorting */
static void merge(int *arr, int *w, int l, int m, int r)
{
	int i = l;
	int j = m + 1;
	int k = l;

	while (i <= m && j <= r) {
		if (arr[i] <= arr[j])
			w[k++] = arr[i++];
		else if (arr[j] <= arr[i])
			w[k++] = arr[j++];
	}
	
	while (i <= m)
		w[k++] = arr[i++];

	while (j <= r)
		w[k++] = arr[j++];
	
	for (int p = l; p <= r; p++)
		arr[p] = w[p];
}

/* Use 'l + (r - l) / 2' instead of '(l + r) / 2'
 * to avoid potential integer overflow
 */

static void sort(int *arr, int *w, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2; // To avoid potential integer overflow

		sort(arr, w, l, m);
		sort(arr, w, m + 1, r);
		merge(arr, w, l, m, r);
	}
}

void mearge_sort(int *arr, int n)
{
	int *tmp = malloc(sizeof(int) * n);

	if (tmp) {
		sort(arr, tmp, l, r);
		free(tmp);
	}
}

/* Quick Sort is an In-place sorting algorithm, meaning it doesn't need a large
 * temporary array like Merge Sort.Although it doesn't use extra arrays, it 
 * requires space for the recursion stack. 
 *
 * Each time the function calls itself, it consumes some memory. 
 * On average, this depth is 'log n'.
 */

/* $ learn 7 $ quick sorting */
static void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int partition(int *arr, int l, int r)
{
	int p = arr[r];
	int i = l - 1;
	int j = l;
	
	while (j <= r - 1) {
		if (arr[j] < p) {
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}

	swap(&arr[i + 1], &arr[r]);

	return i + 1;
}

void quick_sort(int *arr, int l, int r)
{
	if (l < r) {
		int p = partition(arr, l, r);
		
		quick_sort(arr, l, p - 1);
		quick_sort(arr, p + 1, r);
	}
}

/* Oh, by the way, Happy 2026! */
