class Solution {
public:
    string toGoatLatin(string sentence) {
        stringstream ss(sentence);
        string word, ans;
        int count = 1;

        while (ss >> word) {
            char first = word[0];

            bool vowel = (first == 'a' || first == 'e' ||
                          first == 'i' || first == 'o' ||
                          first == 'u' || first == 'A' ||
                          first == 'E' || first == 'I' ||
                          first == 'O' || first == 'U');

            if (!vowel) {
                word = word.substr(1) + first;
            }

            word += "ma";

            for (int i = 0; i < count; i++) {
                word += 'a';
            }

            if (!ans.empty())
                ans += " ";

            ans += word;
            count++; 
        }

        return ans;
    }
};