#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    char letter_num;
    char* letters;
} tele_button_t;

tele_button_t tele_button[8] = {
    {.letter_num = 3, .letters="abc"},   /*'2'*/
    {.letter_num = 3, .letters="def"},   /*'3'*/
    {.letter_num = 3, .letters="ghi"},   /*'4'*/
    {.letter_num = 3, .letters="jkl"},   /*'5'*/
    {.letter_num = 3, .letters="mno"},   /*'6'*/
    {.letter_num = 4, .letters="pqrs"},   /*'7'*/
    {.letter_num = 3, .letters="tuv"},   /*'8'*/
    {.letter_num = 4, .letters="wxyz"}    /*'9'*/
};

tele_button_t* tele_button_get(char num)
{
    int idx = (num - 0x30)-2;
    if (idx < 8) {
        return &tele_button[idx];
    }
    return NULL;
}

typedef struct tele_button_hdl {
    tele_button_t **pp_tele_button;
    int num;
} tele_button_hdl_t;


void show(tele_button_t **pp_tele_button, char*tmp, char **out, int *out_idx, int num, int total_num)
{
    if (num == total_num) {
        return;
    } else {
        int i = 0;
        for (;i < pp_tele_button[num]->letter_num; i++) {

            tmp[num] = pp_tele_button[num]->letters[i];
            // printf("%c", out[idx][num]);
            show(pp_tele_button, tmp, out, out_idx, num+1, total_num);
            if ((num+1) == total_num) {
                strcpy(out[(*out_idx)], tmp);
#if (DEBUG)
                printf("s = %s\n", out[*out_idx]);
#endif
                (*out_idx)++;
            }
        }
    }
}

char ** letterCombinations(char * digits, int* returnSize){
    char **pp_output = NULL;
    char *p_tmp = NULL;
    tele_button_hdl_t tele_button_hdl = {.num = 0, .pp_tele_button = NULL};

    for (tele_button_hdl.num = 0; digits[tele_button_hdl.num] != '\0'; tele_button_hdl.num++) {
        tele_button_hdl.pp_tele_button = (tele_button_t**) realloc (tele_button_hdl.pp_tele_button, (tele_button_hdl.num + 1) * sizeof(tele_button_t*));
        tele_button_hdl.pp_tele_button[tele_button_hdl.num] = tele_button_get(digits[tele_button_hdl.num]);
#if (DEBUG)
        printf("tele_button_hdl.num = %d, %d\n", tele_button_hdl.num, tele_button_hdl.pp_tele_button[0]->letter_num);
#endif
    }

    if (tele_button_hdl.num == 0) {
        *returnSize = 0;
        goto finish;
    }
    *returnSize = 1;
    for (int i = 0; i < tele_button_hdl.num; i++) {
        *returnSize *= tele_button_hdl.pp_tele_button[i]->letter_num;
    }
    pp_output = (char**) malloc(sizeof(char*) * (*returnSize));
    for (int i = 0; i < (*returnSize); i++) {
        pp_output[i] = (char*) calloc((tele_button_hdl.num + 1), sizeof(char));
    }
    p_tmp = (char*) calloc((tele_button_hdl.num + 1), sizeof(char));

    int out_idx = 0;
    show(tele_button_hdl.pp_tele_button,
         p_tmp,
         pp_output,
         &out_idx,
         0,
         tele_button_hdl.num);
#if (DEBUG)
    for (int i = 0; i < (*returnSize); i++) {
        printf("res(%d)= %s\n", i, pp_output[i]);
    }
#endif
finish:
    return pp_output;
}


int main(int argc, char* argv[])
{
    int size = -1;

    // printf("argc = %s\n", argv[1]);
    if (argc == 2)
        letterCombinations(argv[1], &size);

    printf("size = %d\n", size);
    return 0;
}