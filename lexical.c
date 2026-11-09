#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    int ch, i, j = 0;
    char buffer[30];
    char operators[] = "+-*/%=";
    char filename[100];
    FILE *fp;

    printf("Enter the file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open file '%s'\n", filename);
        return 1;
    }

    printf("\n%-20s%-20s\n", "Token", "Type");
    printf("----------------------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {

        /* Ignore spaces, tabs and newlines */
        if (isspace(ch))
            continue;

        /* Check for operators */
        for (i = 0; i < 6; i++) {
            if (ch == operators[i]) {
                printf("%-20c%-20s\n", ch, "Operator");
                break;
            }
        }

        /* Check for special characters */
        if (ch == ';' || ch == ',' || ch == '{' || ch == '}' ||
            ch == '(' || ch == ')') {
            printf("%-20c%-20s\n", ch, "Special Character");
        }

        /* Identifier or keyword */
        if (isalpha(ch)) {
            buffer[j++] = ch;
            ch = fgetc(fp);

            while (isalnum(ch)) {
                buffer[j++] = ch;
                ch = fgetc(fp);
            }

            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer))
                printf("%-20s%-20s\n", buffer, "Keyword");
            else
                printf("%-20s%-20s\n", buffer, "Identifier");

            ungetc(ch, fp);
        }

        /* Constant (number) */
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            ch = fgetc(fp);

            while (isdigit(ch)) {
                buffer[j++] = ch;
                ch = fgetc(fp);
            }

            buffer[j] = '\0';
            j = 0;

            printf("%-20s%-20s\n", buffer, "Constant");
            ungetc(ch, fp);
        }
    }

    fclose(fp);
    return 0;
}



output

input.c

int a = 10;
float b;

enter Filename:input.c
Token                Type
int                  identifier
a                    identifier
=                    operator
10                   constants
;                    special charcter
float                identifier
b                    identifier
;                    special charcter
