%{
    int length;
%}

%%

[a-zA-Z]+ {
    length = yyleng;
    if (length >= 3 && length <= 5)
        	puts(yytext);
     else
     		printf("");
}
 \n {return;}
%%
 
// Function yywrap is called by lex when input is exhausted. 
// When the end of the file is reached the return value of yywrap() is checked. 
// If it is non-zero, scanning terminates and if it is 0 scanning continues with next input file 

yywrap(){}

int main(){
    printf("Enter input string: ");
    yylex();
    return 0;
}
