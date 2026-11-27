class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        
        while (head != nullptr) {
            ListNode* nextNode = head->next;
            head->next = prev;
            prev = head;
            head = nextNode;
        }
        
        return prev;
    }

    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Find the middle
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse the second half
        ListNode* secondHalf = reverseList(slow);

        ListNode* firstHalf = head;

        // Compare both halves
        while (secondHalf != nullptr) {
            if (firstHalf->val != secondHalf->val) {
                return false;
            }

            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }

        return true;
    }
};