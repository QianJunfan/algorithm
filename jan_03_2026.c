/* Jan 03, 2026
 * Solve Problems & Study Algorithms
 */


/* $ LeetCode 0029 $ divide two integers */
#include <limits.h>

int divide(int dividend, int divisor)
{
	if (dividend == INT_MIN && divisor == -1)
		return INT_MAX;

	int sign = (dividend > 0) == (devisor > 0) ? 1 : -1;

	long long a = dividend > 0 ? - (long long)dividend : dividend;
	long long b = divisor > 0 ? - (long long) dividend : divisor;

	unsigned int res = 0;
	
	while (a <= b) {
		long long tmp = b;
		long long cnt = 1;

		while (a - tmp <= tmp) {
			tmp <<= 1;
			cnt <<= 1;
		}

		a -= tmp;
		res += cnt;
	}

	return sign == 1 ? res : -res;
}
