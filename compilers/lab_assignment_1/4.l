%{
    #include<string.h>
    int is_c_keyword(char * s);
%}

%%

[a-zA-Z]+ { if (is_c_keyword(yytext)) printf("%s: Keyword\n", yytext);}
[a - z A - Z _][a - z A - Z 0 - 9 _]* {printf("%s: Identifier\n", yytext)};
[^a-zA-Z_] {printf("%s: Neither keyword nor identifier\n");} 
\n {return;}

%%

int is_c_keyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "auto") || !strcmp(str, "const") 
        || !strcmp(str, "while") || !strcmp(str, "do") ||  !strcmp(str, "for") || !strcmp(str, "signed")
        || !strcmp(str, "break") ||  !strcmp(str, "case") || !strcmp(str, "default") || !strcmp(str, "enum")
        ||  !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "register") || !strcmp(str, "volatile")
        || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "extern") || !strcmp(str, "union")
        || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return 1; 
    return 0; 
} 

int yywrap(){}

int main(){
    printf("Enter the string: ");
    yylex();
    return;
}