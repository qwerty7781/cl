#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i = 0;
int error = 0;

void E();
void Edash();
void T();
void Tdash();
void F();

void match(char expected) {
    if (input[i] == expected)
        i++;
    else
        error = 1;
}

void E() {
    T();
    Edash();
}

void Edash() {
    if (input[i] == '+') {
        i++;
        T();
        Edash();
    }
    // ε-production → do nothing
}

void T() {
    F();
    Tdash();
}

void Tdash() {
    if (input[i] == '*') {
        i++;
        F();
        Tdash();
    }
    // ε-production → do nothing
}

void F() {
    if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')')
            i++;
        else
            error = 1;
    } else if (isalpha(input[i])) { // id
        i++;
    } else {
        error = 1;
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    E();

    if (input[i] == '\0' && error == 0)
        printf(" Accepted: The input is syntactically correct.\n");
    else
        printf(" Rejected: Invalid syntax.\n");

    return 0;
}
//a+b*c   ==   valid
//+a    ==   invalid
