/* leetcode 4 - median of two sorted arrays
 * Jan 24, 2026
 */

using namespace std;

/* merge */
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
        int s = nums1.size() + nums2.size();
        vector<int> r(s);

        merge(nums1.begin(), nums1.end(),
              nums2.begin(), nums2.end(),
              r.begin());

        if (s % 2 != 0)
                return (double)r[s / 2];
        else
                return (double)(r[s / 2] + r[s / 2 - 1]) / 2.0;

        return 0.0;
} 


/* no merging */
double findMedianSortedArrays(vector<int>& n1, vector<int>& n2)
{
        
}
