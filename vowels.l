%{
#include<stdio.h>
int vowels=0;
int consonants=0;
%}
%%
[aeiouAEIOU]{vowels++;}
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]{consonants++;}
.|\n               { }
%%
int main()
{
    yylex();
    printf("Total Vowels:%d\n",vowels);
    printf("Total consonants:%d\n",consonants);
    return 0;
}
//input.txt

//this is abc test abc  
