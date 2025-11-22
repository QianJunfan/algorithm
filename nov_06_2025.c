/*
 */


/* 0017 - letter combinations of a phone number (dfs)
 *      - from https://github.com/qianjunfan
 */
#include <stdlib.h>

const char *map[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void backtrack(const char *digits, int index, char *path, char ***result, int *size)
{
        if (digits[index] == '\0') {
                (*size)++;

                *result = realloc(*result, (*size) * sizeof(char *));

                (*result)[(*size) - 1] = strdup(path);

                return;
        }

        const char *letters = map[digits[index] - '0'];

        for (int i = 0; letters[i] != '\0'; i++) {
                path[index] = letters[i];
                backtrack(digits, index + 1, path, result, size);
        }
}

char **letterCombinations(char *digits, int *size)
{
        *size = 0;
        int len = strlen(digits);
        if (len == 0)
                return NULL;
       
        char **result = NULL;

        char path[len + 1];

        path[len] = '\0';

        backtrack(digits, 0, path, &result, size);

        return result;
}

/* 0018 - 4sum
 *      - from https://github.com/qianjunfan
 */
#include <stdio.h>
#include <stdlib.h>

static int compare_ints_asc(const void *a, const void *b)
{
	const int val_a = *(const int *)a;
	const int val_b = *(const int *)b;

	if (val_a < val_b)
		return -1;
	if (val_a > val_b)
		return 1;
	return 0;
}

int **four_sum(int *nums, int size, int target, int *ret_size,
	       int **col_sizes)
{
	int capacity = 10;
	int **result = NULL;
	int i, j, left, right;
	long long target_ll = (long long)target;

	*ret_size = 0;
	if (size < 4) {
		*col_sizes = NULL;
		return NULL;
	}

	result = (int **)malloc(sizeof(int *) * capacity);
	if (!result) {
		*col_sizes = NULL;
		return NULL;
	}

	qsort(nums, size, sizeof(int), compare_ints_asc);

	for (i = 0; i < size - 3; i++) {
		if (i > 0 && nums[i] == nums[i-1])
			continue;

		if ((long long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target_ll)
			break;

		for (j = i + 1; j < size - 2; j++) {
			if (j > i + 1 && nums[j] == nums[j-1])
				continue;

			left = j + 1;
			right = size - 1;

			while (left < right) {
				long long sum = (long long)nums[i] + nums[j] +
						nums[left] + nums[right];

				if (sum == target_ll) {
					if (*ret_size == capacity) {
						capacity *= 2;
						result = (int **)realloc(result,
								sizeof(int *) * capacity);
						if (!result)
							goto free_on_error;
					}

					result[*ret_size] = (int *)malloc(sizeof(int) * 4);
					if (!result[*ret_size])
						goto free_on_error;

					result[*ret_size][0] = nums[i];
					result[*ret_size][1] = nums[j];
					result[*ret_size][2] = nums[left];
					result[*ret_size][3] = nums[right];
					
					(*ret_size)++;

					left++;
					right--;

					while (left < right && nums[left] == nums[left - 1])
						left++;
					while (left < right && nums[right] == nums[right + 1])
						right--;
				} else if (sum < target_ll) {
					left++;
				} else {
					right--;
				}
			}
		}
	}
	
	if (*ret_size > 0) {
		*col_sizes = (int *)malloc(sizeof(int) * (*ret_size));
		if (!*col_sizes)
			goto free_on_error;

		for (i = 0; i < *ret_size; i++)
			(*col_sizes)[i] = 4;
	} else {
		free(result);
		result = NULL;
		*col_sizes = NULL;
	}

	return result;

free_on_error:
	for (i = 0; i < *ret_size; i++)
		free(result[i]);
	free(result);
	*ret_size = 0;
	*col_sizes = NULL;

	return NULL;
}



































