pattern01.l(LEX)

%{
#include<stdio.h>
#include"y.tab.h"
%}

%%
1 {return NUM1;}
0 {return NUM0;}
\n {return 0;}
. ;
%%

int yywrap(){
	return 1;
}



pattern01(YACC)

%{
#include<stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUM1 NUM0;

%%
S : E
  ;
  
E : NUM0 E NUM1	
  | NUM0 NUM1
%%

int main(){
	printf("Enter the expression:\n");
	if(yyparse() == 0){
		printf("valid Expression");
	}
	else{
		printf("invalid Expression");
	}
}

void yyerror(const char *s){
	printf("syntax error : \n%s",s);
}


ouptut

pranav@laptop:~/compilerlab$ lex pattern01.l
pranav@laptop:~/compilerlab$ yacc -d pattern01.y
pranav@laptop:~/compilerlab$ gcc lex.yy.c y.tab.c
pranav@laptop:~/compilerlab$ ./a.out
Enter the expression:
00001111
valid Expressionpranav@laptop:~/compilerlab$ ./a.out
Enter the expression:
0011111
syntax error :
syntax errorinvalid Expressionpranav@laptop:~/compilerlab$
