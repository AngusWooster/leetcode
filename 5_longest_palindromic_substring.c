#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
/****************************************************************
*   Constraints:
*   1 <= s.length <= 1000
*   s consist of only digits and English letters.
****************************************************************/
/****************************************************************
*   for exmple : "babbad"
*   dyanmic program as below: (x axis: END / y axis: START)
*   1. first step:
*               END POS
*                 0   1   2   3   4
*   START POS   +---+---+---+---+---+
*             0 | 1 | X | X | X | X |
*               +---+---+---+---+---+
*             1 | X | 1 | X | X | X |
*               +---+---+---+---+---+
*             2 | X | X | 1 | X | X |
*               +---+---+---+---+---+
*             3 | X | X | X | 1 | X |
*               +---+---+---+---+---+
*             4 | X | X | X | X | 1 |
*               +---+---+---+---+---+
*   2. second step: (set as true, if two letter are same)
*               END POS
*                 0   1   2   3   4
*   START POS   +---+---+---+---+---+
*             0 | 1 | 0 | X | X | X |
*               +---+---+---+---+---+
*             1 | X | 1 | 0 | X | X |
*               +---+---+---+---+---+
*             2 | X | X | 1 | 1 | X |
*               +---+---+---+---+---+
*             3 | X | X | X | 1 | 0 |
*               +---+---+---+---+---+
*             4 | X | X | X | X | 1 |
*               +---+---+---+---+---+
*   3. keep continue to finish it
*   4. find the longest palindrome
****************************************************************/
bool is_palindrome(char *s, int start, int end)
{
    bool res = false;
    while(1) {
        if (s[start]!= s[end]) {
            break;
        }
        if (start == end || start >= end) {
            res = true;
            break;
        }
        start++;
        end--;
    }
    return res;
}

char * longestPalindrome(char * s){
    char *out = NULL;
    bool **p_dp = NULL;
    int str_len = strlen(s);

    out = (char*)calloc(str_len+1, sizeof(char));

    if (str_len == 1) {
        out[0] = s[0];
        goto finish;
    }

    /* init dynamic program */
    p_dp = (bool**) calloc(str_len, sizeof(bool*));
    for (int i = 0; i < str_len; i++) {
        p_dp[i] = (bool*) calloc(str_len, sizeof(bool));
        p_dp[i][i] = true;
    }
    /* set dynamic program */
    for (int start = 0, end = 1; start <= (str_len - 2); start++, end++) {
        if (s[start] == s[end]) {
            p_dp[start][end] = true;
        }
    }
    for (int i = 2; i < str_len; i++) {
        for (int start = 0, end = i; start <= (str_len - 1 - i); start++, end++) {
            if (s[start] == s[end] && p_dp[start+1][end-1]) {
                p_dp[start][end] = true;
            }
        }
    }

    /* find the longest palindrome */
    for (int i = str_len; i > 0; i--) {
        for (int start = 0, end = i-1; end < (str_len); start++, end++) {
            if (p_dp[start][end]) {
#if DEBUG
                printf("hit: %d, %d\n", start, end);
#endif
                memcpy(out, s+start, end-start+1);
                goto finish;
            }
        }
    }

finish:
#if DEBUG
    printf("out = %s\n", out);
#endif
    free(p_dp);
    return out;
}

int main(int argc, char* argv[])
{
    char *out = NULL;
    if (argc == 2)
        out = longestPalindrome(argv[1]);

    if (out) {
        printf("out = %s\n", out);
    }
    return 0;
}