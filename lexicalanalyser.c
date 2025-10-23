#include <stdio.h>
#include <ctype.h>
#include <string.h>
int isKeyword(char word[]) {
char keywords[4][10] = {"int", "float", "if", "else"};
for (int i = 0; i < 4; i++) {
if (strcmp(word, keywords[i]) == 0)
return 1;

}
return 0;
}
int main() {
char ch, word[20];
int i = 0;
// Counters for each token type
int keywordCount = 0;
int identifierCount = 0;
int numberCount = 0;
int operatorCount = 0;
int specialCount = 0;

FILE *fp = fopen("input.c", "r");
if (fp == NULL) {
printf("Error opening file.\n");
return 1;
}
while ((ch = fgetc(fp)) != EOF) {
if (isalpha(ch)) {
word[i++] = ch;
while (isalnum(ch = fgetc(fp))) {
word[i++] = ch;
}
word[i] = '\0';
i = 0;
ungetc(ch, fp);
if (isKeyword(word)) {
printf("[Keyword] %s\n", word);
keywordCount++;
} else {
printf("[Identifier] %s\n", word);
identifierCount++;
}

}
else if (isdigit(ch)) {
word[i++] = ch;
while (isdigit(ch = fgetc(fp))) {
word[i++] = ch;

}
word[i] = '\0';
i = 0;
ungetc(ch, fp);
printf("[Number]%sln", word);
numberCount++;
}
else if (ch == '+' || ch == '-' || ch == '=') {
printf("[Operator] %cln", ch);
operatorCount++;
}
else if (ch == ';' || ch == 'C' || ch == ')') {
printf("[Special] %cln", ch);
specialCount++;
}
else if (ch == ' ' || ch == '\n')
{

}
continue;
}

fclose(fp);
// Print the counts
printf("InToken counts:\n");
printf("Keywords: %d\n",
keywordCount);
printf("Identifiers: %d\n",
identifierCount);
printf("Numbers: %d\n",
numberCount);
printf("Operators: %d\n",
operatorCount);
printf("Special: %d\n",
specialCount);
return 0;
}

// input.c
// int main() {
// float num = 3.14;
// int count = 10;
// if (count > 0)
// count = count - 1;
// }
