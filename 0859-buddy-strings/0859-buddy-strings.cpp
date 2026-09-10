class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.size() != goal.size())
            return false;

        if (s == goal) {
            vector<int> count(26, 0);

            for (char c : s) {
                count[c - 'a']++;

                if (count[c - 'a'] >= 2)
                    return true;
            }

            return false;
        }

        vector<int> diff;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != goal[i]) {
                diff.push_back(i);
            }
        }

        if (diff.size() != 2)
            return false;

        int i = diff[0];
        int j = diff[1];

        return s[i] == goal[j] &&
               s[j] == goal[i];
    }
};