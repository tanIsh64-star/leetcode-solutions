class Solution {
public:
    class Fenwick {
    public:
        int n;
        vector<long long> bit;

        Fenwick(int n) {
            this->n = n;
            bit.assign(n + 1, 0);
        }

        void add(int i, long long val) {
            i++;
            while (i <= n) {
                bit[i] += val;
                i += i & -i;
            }
        }

        long long query(int i) {
            long long sum = 0;

            while (i > 0) {
                sum += bit[i];
                i -= i & -i;
            }

            return sum;
        }

        int kth(long long k) {
            int idx = 0;
            int step = 1;

            while (step * 2 <= n)
                step *= 2;

            while (step) {
                int next = idx + step;

                if (next <= n && bit[next] < k) {
                    idx = next;
                    k -= bit[next];
                }

                step /= 2;
            }

            return idx;
        }
    };

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());

        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();

        auto getPos = [&](int v) {
            return lower_bound(vals.begin(), vals.end(), v)
                   - vals.begin();
        };

        Fenwick cnt(m), sum(m);

        long long windowSum = 0;

        auto update = [&](int v, int delta) {
            int p = getPos(v);
            cnt.add(p, delta);
            sum.add(p, 1LL * v * delta);
        };

        for (int i = 0; i < x; i++) {
            update(nums[i], 1);
            windowSum += nums[i];
        }

        vector<long long> cost;

        for (int i = 0; i <= n - x; i++) {

            int medianPos = cnt.kth((x + 1) / 2);
            long long median = vals[medianPos];

            long long leftCount = cnt.query(medianPos + 1);
            long long leftSum = sum.query(medianPos + 1);

            long long rightCount = x - leftCount;
            long long rightSum = windowSum - leftSum;

            long long operations =
                median * leftCount - leftSum +
                rightSum - median * rightCount;

            cost.push_back(operations);

            if (i < n - x) {
                update(nums[i], -1);
                windowSum -= nums[i];

                update(nums[i + x], 1);
                windowSum += nums[i + x];
            }
        }

        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0);

        for (int j = 1; j <= k; j++) {

            vector<long long> curr(n + 1, INF);

            for (int i = 1; i <= n; i++) {

                curr[i] = curr[i - 1];

                if (i >= x) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev = curr;
        }

        return prev[n];
    }
};