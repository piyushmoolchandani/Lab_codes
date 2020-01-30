%{
	int vowel_count = 0;
	int consonent_count = 0;
%}

%%
[aeiouAEIOU] {vowel_count++;}
[a-zA-Z] {consonent_count++;}
\n {return;} 
. {};
%%

int yywrap(){	
}

int main(){
	extern FILE *yyin;
	yyin = fopen("input_1.txt", "r");
	extern FILE *yyout;
	yyout = fopen("output_1.txt", "w");
	yylex();
	fprintf(yyout, "Number of vowels : %d, number of consonents : %d\n", vowel_count, consonent_count);
	return 0;
}
