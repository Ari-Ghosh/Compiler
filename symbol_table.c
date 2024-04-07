#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main() {
    int x = 0, n, i = 0, j = 0;
    void *mypointer, *Symbol_address[5];
    char ch, First_Search, Symbol_Array2[15], Symbol_Array3[15], c;

    printf("Input the expression :");

    while ((c = getchar()) != '\n') {
        Symbol_Array2[i] = c;
        i++; 
    }
    n = i - 1;

    printf("Given Expression:");

    for (i = 0; i <= n; i++) {
        printf("%c", Symbol_Array2[i]);
    }
    printf("\nSymbol Table display\n");
    printf("Symbol \t addr \t type");

    while (j <= n) {
        c = Symbol_Array2[j];

        if (isalpha((unsigned char)c)) {
            mypointer = malloc(sizeof(char));
            if (mypointer == NULL) {
                printf("Memory allocation failed");
                return 1;
            }
            Symbol_address[x] = mypointer;
            Symbol_Array3[x] = c;
            printf("\n%c \t %p \t identifier\n", c, mypointer);
            x++;
            j++;
        } else {
            ch = c;
            if (ch == '+' || ch == '-' || ch == '*' || ch == '=' || ch == '/' || ch == '%') {
                mypointer = malloc(sizeof(char));
                if (mypointer == NULL) {
                    printf("Memory allocation failed");
                    return 1;
                }
                Symbol_address[x] = mypointer;
                Symbol_Array3[x] = ch;
                printf("\n %c \t %p \t operator\n", ch, mypointer);
                x++;
                j++;
            }
        }
    }
    return 0;
}
