%{
	#include<string.h>
	
	void substring(char * string, char * pointer, int position, int length);
	void copy_string(char * destination, char * source);
	
	char * temp;
	int flag;
	int brackets;
	
	typedef struct loop_data{
		char * condition;
		int flag;
		int brackets;
		struct loop_data * next;
	}loop_data;
	
	struct loop_data * create_node(char * s, int n);
	int is_empty(struct loop_data * root);
	void push(struct loop_data ** root, char * s, int n);
	char * read_condition(struct loop_data * root);
	int read_flag(struct loop_data * root);
	int read_brackets(struct loop_data * root);
	void pop(struct loop_data ** root);
	void update(struct loop_data ** root, char * s, int n, int b);
	
	struct loop_data * root = NULL;
%}

for for

%%

[^\n\t ;]*{for} {
	printf("0 %s\n", yytext);
	push(&root, " ", 1);
}

[(][^;\n)]* {
	//printf("%s", "yo bro 1\n");
	if (read_flag(root) == 1){
		printf("1 %s\n", yytext);
		substring(yytext, temp, 1, strlen(yytext) - 1);
		update(&root, temp, 2, read_brackets(root));
		fprintf(yyout, "{%s;\n", temp);
	}
	else{
		printf("-1 %s\n", yytext);
		fprintf(yyout, "%s", yytext);
	}
}

[;][^;)\n]* {
	//printf("%s", "yo bro 2\n");
	if (read_flag(root) == 2){
		printf("2 %s\n", yytext);
		if (yyleng == 1){
			fprintf(yyout, "%s%s ", "while(", "1");
			update(&root, "1", 3, read_brackets(root));
		}
		else{
			substring(yytext, temp, 1, strlen(yytext) - 1);
			update(&root, temp, 3, read_brackets(root));
			fprintf(yyout, "%s%s ", "while(", temp);
		}
	}
	else if (read_flag(root) == 3){
		printf("3 %s\n", yytext);
		substring(yytext, temp, 1, strlen(yytext) - 1);
		update(&root, temp, 4, read_brackets(root));
	}
	else{
		printf("-23 %s\n", yytext);
		fprintf(yyout, "%s", yytext);
	}
}

[{] {
	update(&root, read_condition(root), read_flag(root), read_brackets(root) + 1);
	fprintf(yyout, "%s", yytext);
}

[}] {
	update(&root, read_condition(root), read_flag(root), read_brackets(root) - 1);
	if (read_flag(root) == 4 && !read_brackets(root)){
		printf("5 %s\n", yytext);
		fprintf(yyout, "%s;\n}}", read_condition(root));
		pop(&root);
	}
	else{
	    printf("-5 %s\n", yytext);
		fprintf(yyout, "%s", yytext);
	}
}

.   {
	printf("6 %s\n", yytext);
	fprintf(yyout, "%s", yytext);	
}

%%

int yywrap(){}

void substring(char *string, char * pointer, int position, int length){
   int c;
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position);
      string++;
   }
   *(pointer+c) = '\0';
}

void copy_string(char * destination, char * source){
	int n = strlen(source);
	for (int i = 0; i < n; i++)
		*(destination + i) = *(source + i);
	*(destination + n) = '\0';
}

struct loop_data * create_node(char * s, int n){
	struct loop_data * new_node = (struct loop_data *)malloc(sizeof(struct loop_data));
	new_node -> condition = (char *)malloc(sizeof(char) * strlen(s));
	copy_string(new_node -> condition, s);
	new_node -> flag = n;
	new_node -> brackets = 0;
	new_node -> next = NULL;
	return new_node;
}

int is_empty(struct loop_data * root){
	return !root;
}

void push(struct loop_data ** root, char * s, int n){
	struct loop_data * new_node = create_node(s, n);
	new_node -> next = *root;
	new_node -> flag = n;
	*root = new_node;
}

void pop(struct loop_data ** root){
	if (is_empty(*root))
		return;
	loop_data * temp = *root;
	*root = (*root) -> next;
	free(temp);
	return;
}

char * read_condition(struct loop_data * root){
	if (is_empty(root))
		return "";
	return root -> condition;
}

int read_flag(struct loop_data * root){
	if (is_empty(root))
		return -1;
	return root -> flag;
}
	

int read_brackets(struct loop_data * root){
	if (is_empty(root))
		return -1;
	return root -> brackets;
}

void update(struct loop_data ** root, char * s, int n, int b){
	copy_string((*root) -> condition, s);
	(*root) -> flag = n;
	(*root) -> brackets = b;
}

int main(){
	extern FILE *yyin;
	yyin = fopen("input_1.c", "r");
	extern FILE *yyout;
	yyout = fopen("output_1.c", "w");
	temp = (char *)malloc(1000 * sizeof(char));
	push(&root, "{", 0);
	yylex();
	return 0;
}
