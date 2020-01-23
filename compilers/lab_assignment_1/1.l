%{
	int vowel_count = 0;
	int consonent_count = 0;
%}

%%
[aeiouAEIOU] {vowel_count++;}
[a-zA-Z] {consonent_count++;}
\n {return;} 
%%

int yywrap(){	
}

int main(){
	printf("Enter the string: ");
	yylex();
	printf("Number of vowels : %d, number of consonents : %d\n", vowel_count, consonent_count);
	return 0;
}
