class Solution {
public:
    set<string> solve(string s, int l, int r) {
        set<string> result;

        // Split by commas at the current level
        vector<pair<int, int>> parts;
        int start = l;
        int balance = 0;

        for (int i = l; i <= r; i++) {
            if (s[i] == '{') {
                balance++;
            } 
            else if (s[i] == '}') {
                balance--;
            } 
            else if (s[i] == ',' && balance == 0) {
                parts.push_back({start, i - 1});
                start = i + 1;
            }
        }

        parts.push_back({start, r});

        // If there is a top-level comma, take UNION
        if (parts.size() > 1) {
            for (auto [a, b] : parts) {
                set<string> temp = solve(s, a, b);
                result.insert(temp.begin(), temp.end());
            }

            return result;
        }

        // No comma -> concatenation
        set<string> current = {""};

        int i = l;

        while (i <= r) {

            if (s[i] >= 'a' && s[i] <= 'z') {
                set<string> next;

                for (string x : current) {
                    next.insert(x + s[i]);
                }

                current = next;
                i++;
            }

            else if (s[i] == '{') {
                int j = i;
                int balance = 0;

                while (j <= r) {
                    if (s[j] == '{')
                        balance++;
                    else if (s[j] == '}')
                        balance--;

                    if (balance == 0)
                        break;

                    j++;
                }

                // Evaluate inside {}
                set<string> inside = solve(s, i + 1, j - 1);

                // Cartesian product for concatenation
                set<string> next;

                for (string a : current) {
                    for (string b : inside) {
                        next.insert(a + b);
                    }
                }

                current = next;

                i = j + 1;
            }
        }

        return current;
    }

    vector<string> braceExpansionII(string expression) {
        set<string> ans = solve(expression, 0, expression.size() - 1);

        return vector<string>(ans.begin(), ans.end());
    }
};