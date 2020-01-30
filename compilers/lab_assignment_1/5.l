%{
    int length;
%}

%%

[a-z A-Z]+ {
    length = yyleng;
    if (length >= 3 and length <= 5)
        printf("%s ", yytext);
}

/* 
Function yywrap is called by lex when input is exhausted. 
When the end of the file is reached the return value of yywrap() is checked. 
If it is non-zero, scanning terminates and if it is 0 scanning continues with next input file 
*/

yywrap(){}

int main(){
    printf("Enter input string: ");
    yylex();
    return 0;
}