class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;

        // Give every litter cell a bit number.
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                }
                else if (classroom[r][c] == 'L') {
                    id[r][c] = litterCount++;
                }
            }
        }

        // No litter to collect.
        if (litterCount == 0)
            return 0;

        int fullMask = (1 << litterCount) - 1;

        /*
            State:
            row, col, remaining energy, remaining litter mask
        */

        queue<array<int, 4>> q;

        // Start with all litter uncollected.
        q.push({sr, sc, energy, fullMask});

        /*
            visited[row][col][energy][mask]
        */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        visited[sr][sc][energy][fullMask] = true;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                auto [r, c, currEnergy, mask] = q.front();
                q.pop();

                // All litter collected.
                if (mask == 0)
                    return moves;

                // No energy left, so we cannot move.
                if (currEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid.
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle.
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Reset area.
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    // Collect litter.
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];

                        newMask &= ~(1 << bit);
                    }

                    // State already visited.
                    if (visited[nr][nc][newEnergy][newMask])
                        continue;

                    visited[nr][nc][newEnergy][newMask] = true;

                    q.push({
                        nr,
                        nc,
                        newEnergy,
                        newMask
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};