#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int items_num_get(char *s, int left, int right)
{
    int items = 0;
    printf("right = %d\n", right);
    while(left < right && (s[left] == '*' || s[right] == '*')) {
        if (s[left] != '|')
            left++;
        if (s[right] != '|')
            right--;
    }
    while(left < right && s[left+1] == '|') {
        left++;
    }
    while(left < right && s[right-1] == '|') {
        right--;
    }
    printf("left = %d, right = %d\n", left, right);

    if (left < right) {
        for (int i = left; i < right; i++) {
            if (s[i] == '*') {
                items++;
            }
        }
    }
    return items;
}


int main(int argc, char* argv[])
{
    char *s = "**|**|||||***|*||";
    int items = 0;

    items = items_num_get(s, 0, strlen(s)-1);
    printf("items = %d\n", items);
    return 0;
}