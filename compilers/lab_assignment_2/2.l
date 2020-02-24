%{ 
#include<stdio.h>
#include<string.h>
int flag = 0;
%} 

key auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|continue|for|signed|void|do|if|static|while|default|goto|sizeof|volatile|const|float|short|unsigned

%%

[#].* {fprintf(yyout,"%s",yytext);}
["].*["] {fprintf(yyout,"%s",yytext);}
{key}	 {fprintf(yyout,"%s<KW>",yytext);}
[a-zA-Z_][a-zA-Z0-9_]*[ ]*[(]	{fprintf(yyout,"%s",yytext);}
[a-zA-Z_][a-zA-Z0-9_]*		{fprintf(yyout,"%s<ID>",yytext);}
.				{fprintf(yyout,"%s",yytext);}

%%

int yywrap(){} 

// driver code 
int main()
{ 
	yyin = fopen("input", "r");
	yyout = fopen("Output.txt", "w");
	yylex();
	return 0; 
}
