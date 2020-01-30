%{
int flag = 0;
%}

%%

[a-zA-Z]			;
\n {return;}
[^a-zA-Z]	{flag = 1;}

%%

int main(){
	extern FILE *yyin;
	yyin = fopen("input_2.txt", "r");
yylex();
printf("Does any other character occurs: %d\n", flag);
return 0;
}
