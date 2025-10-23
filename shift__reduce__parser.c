#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTOK 100
#define TOKLEN 16

char tokens[MAXTOK][TOKLEN]; // token list
int ntokens = 0;

char stack_[MAXTOK][TOKLEN];
int top = -1;

// helpers
void push_token(const char *t) {
    top++;
    strncpy(stack_[top], t, TOKLEN-1);
    stack_[top][TOKLEN-1] = '\0';
}

void pop_n_push(int n, const char *t) {
    // pop n tokens and push t
    top -= n;
    push_token(t);
}

void print_stack_input(int curTokIndex) {
    // print stack
    printf("$");
    if (top >= 0) {
        for (int i = 0; i <= top; ++i) {
            printf("%s", stack_[i]);
        }
    }
    printf("\t");

    // print remaining input
    printf("");
    for (int i = curTokIndex; i < ntokens; ++i) {
        printf("%s", tokens[i]);
    }
    printf("$");
}

// attempt one reduction; returns 1 if a reduction happened
int try_reduce() {
    // Rule: E -> id
    if (top >= 0 && strcmp(stack_[top], "id") == 0) {
        pop_n_push(1, "E");
        printf("\tReduce: E -> id\n");
        return 1;
    }

    // Rule: E -> ( E )
    if (top >= 2 && strcmp(stack_[top], ")") == 0 &&
        strcmp(stack_[top-1], "E") == 0 &&
        strcmp(stack_[top-2], "(") == 0) {
        pop_n_push(3, "E");
        printf("\tReduce: E -> (E)\n");
        return 1;
    }

    // Rule: E -> E + E
    if (top >= 2 && strcmp(stack_[top], "E") == 0 &&
        strcmp(stack_[top-1], "+") == 0 &&
        strcmp(stack_[top-2], "E") == 0) {
        pop_n_push(3, "E");
        printf("\tReduce: E -> E + E\n");
        return 1;
    }

    // Rule: E -> E * E
    if (top >= 2 && strcmp(stack_[top], "E") == 0 &&
        strcmp(stack_[top-1], "*") == 0 &&
        strcmp(stack_[top-2], "E") == 0) {
        pop_n_push(3, "E");
        printf("\tReduce: E -> E * E\n");
        return 1;
    }

    return 0; // no reduction
}

int main() {
    char input[256];
    printf("Enter input (use 'id' for identifiers, e.g. id+id*(id+id)): ");
    if (!fgets(input, sizeof(input), stdin)) return 0;

    // trim newline
    input[strcspn(input, "\n")] = '\0';

    // tokenize input into tokens array: "id", "+", "*", "(", ")"
    ntokens = 0;
    int i = 0, L = strlen(input);
    while (i < L) {
        if (input[i] == ' ') { i++; continue; }
        if (input[i] == '+' || input[i] == '*' || input[i] == '(' || input[i] == ')') {
            tokens[ntokens][0] = input[i];
            tokens[ntokens][1] = '\0';
            ntokens++;
            i++;
        } else if (i+1 < L && input[i] == 'i' && input[i+1] == 'd') {
            strcpy(tokens[ntokens], "id");
            ntokens++;
            i += 2;
        } else {
            // unknown character or malformed token
            printf("Error: unknown token starting at '%c'\n", input[i]);
            return 0;
        }
    }

    printf("\nStack\t\tInput\t\tAction\n");
    printf("-----------------------------------------------------\n");

    int cur = 0;
    while (cur < ntokens) {
        // SHIFT
        push_token(tokens[cur]);
        print_stack_input(cur+1);
        printf("\tShift\n");

        // AFTER SHIFT: repeatedly try reductions until none apply
        while (try_reduce()) {
            // print current state after reduction
            print_stack_input(cur+1);
            // a reduction message has already been printed inside try_reduce
            // but print newline only if not already handled
        }

        cur++;
    }

    // after input consumed, try to reduce remaining stack fully
    int reduced;
    do {
        reduced = try_reduce();
        if (reduced) {
            print_stack_input(ntokens);
            // reduction message printed inside try_reduce
        }
    } while (reduced);

    // acceptance check
    if (top == 0 && strcmp(stack_[top], "E") == 0 && ntokens > 0) {
        printf("\n✅ Accepted: The input is syntactically correct.\n");
    } else {
        printf("\n❌ Rejected: Invalid syntax.\n");
    }

    return 0;
}
// id+id*id  ==    valid
//id**id == invalid
