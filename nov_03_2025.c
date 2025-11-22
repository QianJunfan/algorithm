/*
 */

 
/* 0053 - maximum subarray
 *      - from https://github.com/qianjunfan
 */

int maxSubArray(int *nums, int size)
{
	int max   = nums[0];
	int cur   = nums[0];

	for (int i = 1; i < size; i++) {
		int tmp = nums[i];

		if (cur + tmp > tmp)
			cur += tmp;
		else
			cur = tmp;

		if (cur > max)
			max = cur;
	}

	return max;
}


/* 0036 - valid sodoku
 *      - from https://github.com/qianjunfan
 */

#include <stdbool.h>

void init(int *map)
{
	for(int i = 0; i < 9; i++)
		map[i] = 0;
}

bool check(int *map, int val)
{
	if (val >= '1' && val <= '9')
		if (map[val - 49] == 0) {
			map[val - 49] = 1;
			return true;
		} else {
			return false;
		}

	return true;
};

bool isValidSudoku(char **board, int rsize, int *csize)
{
	int map[9];

	for (int r = 0; r < 9; r++) {
		init(map);
		for (int c = 0; c < 9; c++)
			if(!check(map, board[r][c]))
				return false;
	}

	for (int c = 0; c < 9; c++) {
		init(map);
		for (int r = 0; r < 9; r++)
			if (!check(map, board[r][c]))
                		return false;
	}

	
	for (int offset_r = 0; offset_r < 9; offset_r += 3) {
		for (int offset_c = 0; offset_c < 9; offset_c += 3) {
			init(map);
			for (int r = offset_r; r < offset_r + 3; r++) {
				for (int c = offset_c; c < offset_c + 3; c++)
					if (!check(map, board[r][c]))
						return false;
			}
		}

	}

	return true;
}



/* 0011 - container with most water
 *      - from https://github.com/qianjunfan
 *      - time limit exceeded
 */

#define min(a, b) ((a) < (b) ? (a) : (b))

int maxArea_tle(int *height, int size)
{
	int max    = 0;
	int cur    = 0;

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			int h   = min(height[i], height[j]);
			int w   = j - i;
			int cur = w * h;
			if (cur > max)
				max = cur; 
		} 
	}

	return max;
}

/* 0011 - container with most water
 *      - from https://github.com/qianjunfan
 *      - double pointer
 */

#define min(a, b) ((a) < (b) ? (a) : (b))

int maxArea(int *height, int size)
{
	int l = 0;
	int r = size - 1;
	int max = 0;
	int cur = 0;
	while (l < r) {
		int val_l = height[l];
		int val_r = height[r];
		
		int w = r - l;
		int h = min(val_l, val_r);
		
		if (val_l < val_r)
			l++;
		else
			r--;
	
		cur = w * h;
		if (cur > max)
			max = cur;
	}	

	return max;
}


/* 0015 - 3sum
 *      - from https://github.com/qianjunfan
 *      - time limit exceeded
 */

#include <stdlib.h>

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int **threeSum(int *nums, int size, int *return_size, int **return_col_size)
{
	int **result = (int **)malloc(10000 * sizeof(int *));

	*return_size = 0;

	*return_col_size = malloc(10000 * sizeof(int *));

	qsort(nums, size, sizeof(int), compare);	
	for (int i = 0; i < size; i++) {
		if (i > 0 && nums[i] == nums[i - 1])
            		continue;
		for (int j = i + 1; j < size; j++) {
			if (j > 0 && nums[j] == nums[j - 1])
				continue;
			int target = 0 - nums[i] - nums[j];
			for (int k = i + 1; k < size; k++) {
				if (nums[k] == target) {
					result[*return_size]    = (int *)malloc(3 * sizeof(int));
					result[*return_size][0] = nums[i];
					result[*return_size][1] = nums[j];
					result[*return_size][2] = nums[k];
					return_col_size[*return_size] = 3;
					(*return_size)++;
					while (k > 0 && nums[k] == nums[k+1] && k <= size)
						k++;
					break;
				}
				if (nums[k] > target)
					break;		
			}
		}
	}

	return result;
}


/* 0015 - 3sum
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int threeSum(int *nums, int size, int *r_size, int **c_size)
{
	int **result = (int **)malloc(size * sizeof(int *));
	*c_size      = (int *)malloc(size * sizeof(int));
	*r_size      = 0;
	int capa     = size;

	qsort(nums, size, sizeof(int), compare);	
	for (int i = 0; i < size - 2; i++) {
		if (i > 0 && nums[i] == nums[i-1])
			continue;
		int target = 0 - nums[i];
		int l = i + 1;
		int r = size - 1;

		while (l < r) {
			int sum = nums[l] + nums[r];
			if (sum == target) {
				if (*r_size >= capa) {
					capa   *= 2;
					result  = (int **)realloc(result, capa * sizeof(int *));
					*c_size = (int *)realloc(*c_size, capa * sizeof(int)); 
				}
				result[*r_size]    = (int *)malloc(3 * sizeof(int));
				result[*r_size][0] = nums[i];
				result[*r_size][1] = nums[l];
				result[*r_size][2] = nums[r];
				(*c_size)[*r_size] = 3;
				(*r_size)++;
				
				while (l < r && nums[l] == nums[l + 1])
					l++;
				while (l < r && nums[r] == nums[r - 1])
					r--;
				l++;
				r--;
			} else if (sum < target) {
				l++;
			} else if (sum > target) {
				r--;
			}
		}
	}

	return result;	
}

/* 0016 - 3sum closest
 *      - from https://github.com/qianjunfan
 */
#include <stdlib.h>
#define abs(x) ((x) > 0 ? (x) : -(x))

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}



int threeSumClosest(int *nums, int size, int target)
{
	int min    = abs(target - nums[0] - nums[1] - nums[2]);
	int result = nums[0] + nums[1] + nums[2];

	qsort(nums, size, sizeof(int), compare);	
	
	for (int i = 0; i < size; i++) {
		if (i > 0 && nums[i] == nums[i-1])
			continue;
		int l   = i + 1;
		int r   = size - 1;
		
		while (l < r) {
			int sum = nums[i] + nums[l] + nums[r];
			int dif = abs(target - sum);

			if (dif < min) {
				min = dif;
				result = sum;
			}

			if (sum < target)
				l++;
			else if (sum > target)
				r--;
			else if (sum == target)
				return sum;
		}
	}

	return result;
}


/* 0012 - integer to roman
 *      - from https://github.com/qianjunfan
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void build(char* dest, int n, char ch_x, char ch_v, char ch_i)
{
	char *src = (char *)malloc(10 * sizeof(char));
	if (n == 5) {
		src[0] = ch_v;
		src[1] = '\0';
	}
	if (n == 9) {
		src[0] = ch_i;
		src[1] = ch_x;
		src[2] = '\0';
	}

	if (n > 5 && n <= 8) {
		src[0] = ch_v;
		int i = 1; 
		while (i < n - 5) {
			src[i] = ch_i; 
			i++;
		}

		src[i] = '\0';
	}	
	
	if (n <= 3) {
		int i = 0;
		while(i < n) {
			src[i] = ch_i;
			i++;
		}

		src[i] = '\0';
	}

	if (n == 4) {
		src[0] = ch_i;
		src[1] = ch_v;
		src[2] = '\n';
	}
	

	strcat(dest, src);
	free(src);
}

char *intToRoman(int n) {
	int n_1000 =  n / 1000;
	int n_100  = (n / 100) % 10;
	int n_10   = (n / 10 ) % 10;
	int n_1    =  n % 10;
	
	char *result = (char *)malloc(14 * sizeof(char));
	result[0] = '\0';


    	for (int i = 0; i < n_1000; i++)
        	strcat(result, "M");
    	build(result, n_100, 'M', 'D', 'C');
    	build(result, n_10, 'C', 'L', 'X');
    
	build(result, n_1, 'X', 'V', 'I');
	
	return result;
}

