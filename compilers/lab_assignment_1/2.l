%{

	int positive_count = 0;
	int negative_count = 0;
	int positive_fraction_count = 0;
	int negative_fraction_count = 0;

%}

%%
	
[-][0 - 9]*[.][0-9]+[ ] {negative_fraction_count++;}
[+]?[0-9]*[.][0-9]+[ ] {positive_fraction_count++;}
[-][0-9]+[ ] {negative_count++;}
[+]?[0-9]+[ ] {positive_count++;}
[-][0 - 9]*[.][0-9]+[\n] {negative_fraction_count++; return;}
[+]?[0-9]*[.][0-9]+[\n] {positive_fraction_count++; return;}
[-][0-9]+[\n] {negative_count++; return;}
[+]?[0-9]+[\n] {positive_count++; return;}
\n {return;}

%%

int main(){
	extern FILE *yyin;
	yyin = fopen("input_2.txt", "r");
	yylex();
	printf("Number of positive intergers : %d \nNumber of negative integers : %d\nNumber of positive fractions : %d\nNumber of negative fractions : %d\n", positive_count, negative_count, positive_fraction_count, negative_fraction_count);
	return 0;
}
