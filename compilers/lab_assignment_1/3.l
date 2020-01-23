%{
	int flag = 0;
%}

%%
	[a-zA-Z]	;
	[	{flag = 1};
\n {return;}
%%

int main(){
	printf("Enter the string: ");
	yylex();
	printf("Does any other character occurs: %d", flag);
	return 0;
}
