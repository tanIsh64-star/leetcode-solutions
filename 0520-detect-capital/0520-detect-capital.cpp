class Solution {
public:
    bool detectCapitalUse(string word) {
        int count = 0;

        for (char c : word) {
            if (c >= 'A' && c <= 'Z') {
                count++;
            }
        }

        return count == 0 ||
               count == word.length() ||
               (count == 1 && word[0] >= 'A' && word[0] <= 'Z');
    }
};