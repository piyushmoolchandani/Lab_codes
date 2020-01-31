%{
int flag = 0;
%}

%%

[a-zA-Z]			;
\n {return;}
[^a-zA-Z]	{flag = 1; printf("%s", yytext);}

%%

int main(){
	extern FILE *yyin;
	yyin = fopen("input_3.txt", "r");
yylex();
if (flag)
	printf("is/are the character(s) occuring other than alphabets.\n" );
else
	printf("No extra character occurs.\n");
return 0;
}
