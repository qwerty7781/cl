%{
include <stdio.h>

int lines=0 ,words=0, chars=0;
int in_word=0; //Flag to track if inside a word 
extern FILE*yyin;
%}
%%

\n { lines++; chars++; in_word=0; }
[\t]+ {chars+= yyleng; in_word=0;}

[a-zA-Z0-9]+   {
    chars +=yyleng;
    if(!in_word){ words++; in_word=1;}
}
.{chars++;in_word=0;}

%%

int main(){
    yyin=fopen("input.txt",r);
    if(!yyin){
        perror("Could not open input.txt");
        return 1;
    }
    yylex();
    
    printf("Lines=%d\nWords=%d\nCharacters=%d\n",lines,words,chars);
    
    fclose(yyin);
    return 0;
}


//input.txt

//int a=10;
//float b=a+5.5;
//return b;
