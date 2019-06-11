#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hesaplayici(int a, int b, int c){
    switch(c){
        case 43:
            return a+b;
        case 45:
            return a-b;
        case 42:
            return a*b;
        case 47:
            return a/b;
        case 37:
            return a%b;
    }
}
int get_int(char *str){
  int i = 0, sonuc = 0;

  while(str[i] != 37 && str[i] != 42 && str[i] != 43 && str[i] != 45 && str[i] != 47 && str[i] != 0 && str[i] != 32 && str[i] != 41 ){
    sonuc = 10*sonuc + (str[i]-48);
    i++;
  }
  return sonuc;
}
int get_int_len(char* str){
  int i = 0;

  while(str[i] != 37 && str[i] != 42 && str[i] != 43 && str[i] != 45 && str[i] != 47 && str[i] != 0 && str[i] != 32 && str[i] != 41)
    i++;

  return i;
}
int expr_eval(char *str){
    int RESULT, i;
    int* value, value_index = 0;
    int *final = (int *) malloc(sizeof(int));
    char *stack = (char *) malloc(sizeof(char));
    int final_len = 1, final_index = 0;
    int stack_len = 1, stack_index = 0;
    char *chr_temp;
    int *int_temp;

    while( *str != '\0'){

        if (*str == ' '){
            str++;
            continue;
        }
        else{
            if ((*str > 47) && (*str < 58)){
                final = (int *) realloc(final, sizeof(int)*(++final_len));
                final[final_index++] = get_int(str);
                str += get_int_len(str);
                continue;
            }
            if ((*str == '+') || (*str == '-')){
                if ((stack[stack_len-2] == '+') || (stack[stack_len-2] == '-') || (stack[stack_len-2] == '*') || (stack[stack_len-2] == '/') || (stack[stack_len-2] == '%')){
                    final = (int *) realloc(final, sizeof(int)*(++final_len));
                    final[final_index++] = stack[stack_len-2];
                    stack[stack_len-2] = '\0';
                    if (stack_len != 2){
                        if ( (stack[stack_len-3] == '+') || (stack[stack_len-3] == '-') ){
                          final = (int *) realloc(final, sizeof(int)*(++final_len));
                          final[final_index++] = stack[stack_len-3];
                          stack = (char *) realloc(stack, sizeof(char)*(--stack_len));
                          stack[stack_len-2] = *str;
                          stack_index--;
                        }
                        else{
                            stack = (char *) realloc(stack, sizeof(char)*(--stack_len));
                            stack[stack_len-1] = *str;
                        }
                    }
                    else
                        stack[0] = *str;
                    str++;
                    continue;
                }
                stack = (char*) realloc(stack, sizeof(char)*(++stack_len));
                stack[stack_index++] = *str;
            }
            if ((*str == '*') || (*str == '/') || (*str == '%')){
                if ((stack[stack_len-2] == '*') || (stack[stack_len-2] == '/') || (stack[stack_len-2] == '%')){
                    final = (int *) realloc(final, sizeof(int)*(++final_len));
                    final[final_index++] = stack[stack_len-2];
                    stack[stack_len-2] = '\0';
                    if (stack_len != 2){
                        if ( (stack[stack_len-3] == '*') || (stack[stack_len-3] == '/') || (stack[stack_len-3] == '%') ){
                          final = (int *) realloc(final, sizeof(int)*(++final_len));
                          final[final_index++] = stack[stack_len-3];
                          stack = (char *) realloc(stack, sizeof(char)*(--stack_len));
                          stack[stack_len-2] = *str;
                          stack_index--;
                        }
                        else{
                            stack = (char *) realloc(stack, sizeof(char)*(--stack_len));
                            stack[stack_len-1] = *str;
                        }
                    }
                    else
                        stack[0] = *str;

                    str++;
                    continue;
                }
                stack = (char*) realloc(stack, sizeof(char)*(++stack_len));
                stack[stack_index++] = *str;
            }
            if (*str == '('){
                stack = (char*) realloc(stack, sizeof(char)*(++stack_len));
                stack[stack_index++] = *str;
            }
            if (*str == ')'){
                chr_temp = stack+stack_len-2;
                while (*chr_temp != '('){
                    final = (int *) realloc(final, sizeof(int)*(++final_len));
                    final[final_index++] = *chr_temp;
                    chr_temp--;
                    stack_index--;
                    stack[stack_len-2] = '\0';
                    stack = (char*) realloc(stack, sizeof(char)*(--stack_len));
                }
                stack_index--;
                stack[stack_len-2] = '\0';
                stack = (char*) realloc(stack, sizeof(char)*(--stack_len));
            }
        }
        str++;
    }
    stack_len--;
    while(stack_len){
        chr_temp = stack+stack_len-1;
        if (*chr_temp != ' '){
            final = (int *) realloc(final, sizeof(int)*(++final_len));
            final[final_index++] = *chr_temp;
            chr_temp--;
            stack = (char*) realloc(stack, sizeof(char)*(--stack_len));
        }
    }
    free(stack);
    final[final_index] = '\0';
    value = (int *) malloc(final_len*sizeof(int));
    int_temp = final;
    final_len--;
    i=0;
    while(final_len){
        if ( (int_temp[i] == '+') || (int_temp[i] == '-') || (int_temp[i] == '*') || (int_temp[i] == '/') || (int_temp[i] == '%') ){
            value[value_index-2] = hesaplayici(value[value_index-2], value[value_index-1], int_temp[i]);
            value_index--;}
        else
            value[value_index++] = int_temp[i];
        i++;
        final_len--;
    }
    free(final);
    RESULT = value[0];
    free(value);
    return RESULT;
}
