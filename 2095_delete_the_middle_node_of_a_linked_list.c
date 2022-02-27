/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define IS_NULL(x) ((x) == (void*)0)

struct ListNode* deleteMiddle(struct ListNode* head){
    struct ListNode* p_mid_node = NULL;
    struct ListNode* p_prev_mid_node = NULL;
    struct ListNode* p_two_step = head;
    struct ListNode* p_one_step = head;
    unsigned int node_cnt = 1;
    
    if (head == NULL)
        goto finish;
    
    if (IS_NULL(p_one_step->next)) {
        head = NULL;
        goto finish;
    }
    
    
    while(1) {
        p_prev_mid_node = p_one_step;
        p_one_step = p_one_step->next;
        node_cnt++;

        if (IS_NULL(p_two_step->next)) {
            p_mid_node = p_one_step->next;
            break; 
        }
        p_two_step = p_two_step->next;
        if (IS_NULL(p_two_step->next)) {
            p_mid_node = p_one_step;
            break; 
        }
        p_two_step = p_two_step->next;
        if (IS_NULL(p_two_step->next)) {
            p_mid_node = p_one_step;
            break; 
        }

    }
    
    p_prev_mid_node->next = p_mid_node->next;
    
    
finish:
    return head;
}