/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    uint32_t c = 0;
    struct ListNode* node = NULL;
    
    struct ListNode** pp_input_list = NULL;
    struct ListNode** pp_node = &node;
    
    if (l1 == NULL && l2 == NULL) {
        goto finish;
    }
    *pp_node = (struct ListNode*) calloc(1, sizeof(struct ListNode));
    
    while(1) {

        (*pp_node)->val += c;
        c = 0;
        
        pp_input_list = &l1;
        if ((*pp_input_list) != NULL) {
            (*pp_node)->val += (*pp_input_list)->val;
            (*pp_input_list) = (*pp_input_list)->next;
        }
        pp_input_list = &l2;
        if ((*pp_input_list) != NULL) {
            (*pp_node)->val += (*pp_input_list)->val;
            (*pp_input_list) = (*pp_input_list)->next;
        }
        
        c = (*pp_node)->val / 10;
        (*pp_node)->val = (*pp_node)->val % 10;
        pp_node = &((*pp_node)->next);
        
        if (l1 != NULL || l2 != NULL) {
            *pp_node = (struct ListNode*) calloc(1, sizeof(struct ListNode));
        }
        else {
            if (c) {
                *pp_node = (struct ListNode*) calloc(1, sizeof(struct ListNode));
                (*pp_node)->val = c;
            }
            break;
        }
        
    }
    
finish:
    return node;
}