/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void swap_node(struct ListNode *p_n1, struct ListNode *p_n2)
{ 
    p_n1->next = p_n2->next;
    p_n2->next = p_n1; 
    
    if(p_n1->next != NULL && p_n1->next->next != NULL) {
        p_n1->next = p_n1->next->next;
    }
}

struct ListNode* swapPairs(struct ListNode* head){
    struct ListNode* p_next_pos = head;
    struct ListNode* p_n1, *p_n2;
    
    if (p_next_pos != NULL && p_next_pos->next != NULL) {
        head = head->next;
        while (p_next_pos->next != NULL) {
            p_n1 = p_next_pos;
            p_n2 = p_next_pos->next;
            p_next_pos = p_next_pos->next->next;
            swap_node(p_n1, p_n2);
            
            
            if (p_next_pos == NULL)
                break;
        }
    }
    return head;
}