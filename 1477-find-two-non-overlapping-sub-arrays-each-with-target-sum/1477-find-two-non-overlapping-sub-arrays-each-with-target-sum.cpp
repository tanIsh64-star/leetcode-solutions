class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n + 1, INF);

        int left = 0;
        int sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            if (sum == target) {
                int len = right - left + 1;

                // Combine current subarray with
                // the best non-overlapping one before it.
                if (best[left] != INF) {
                    ans = min(ans, best[left] + len);
                }

                best[right + 1] = min(best[right], len);
            } 
            else {
                best[right + 1] = best[right];
            }
        }

        return ans == INF ? -1 : ans;
    }
};