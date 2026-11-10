%{
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*    { printf("%s : Valid identifier\n", yytext); }
[^ \t\n]+                 { printf("%s : Invalid identifier\n", yytext); }
[ \t]                     ;
\n                        { return 0; }
%%

int main() {
    printf("Enter a name: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
