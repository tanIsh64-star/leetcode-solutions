class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            int rowMax = 0;
            int colMax = 0;

            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0)
                    ans++;

                rowMax = max(rowMax, grid[i][j]);
                colMax = max(colMax, grid[j][i]);
            }

            ans += rowMax + colMax;
        }

        return ans;
    }
};