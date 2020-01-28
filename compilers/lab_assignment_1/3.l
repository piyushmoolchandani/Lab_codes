%{
int flag = 0;
%}

%%

[a-zA-Z]			;
\n {return;}
[^a-zA-Z]	{flag = 1;}

%%

int main(){
printf("Enter the string: ");
yylex();
printf("Does any other character occurs: %d\n", flag);
return 0;
}
