/* Definition section */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    int line_num = 0;
    int comment_num = 0;
    int comm = 0;
    char temp[100];
    
%}

/*Add comment condition*/
%x COMMENT

/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
str [\40-\176]

id {letter}+({letter}|{digit})*
inumber {digit}+
fnumber ({digit}*\.{digit}+)
string \"{str}*\"
comment1 "//"{str}*
comment2 ("/*"{str}*"*/")

/* Rules section */
%%

"+"         { printf("%-8s \t %s\n", yytext, "ADD"); }
"-"         { printf("%-8s \t %s\n", yytext, "SUB"); }
"*"         { printf("%-8s \t %s\n", yytext, "MUL"); }
"/"         { printf("%-8s \t %s\n", yytext, "QUO"); }
"%"         { printf("%-8s \t %s\n", yytext, "REM"); }
"++"        { printf("%-8s \t %s\n", yytext, "INC"); }
"--"        { printf("%-8s \t %s\n", yytext, "DEC"); }
">"         { printf("%-8s \t %s\n", yytext, "GTR"); }
"<"         { printf("%-8s \t %s\n", yytext, "LSS"); }
">="        { printf("%-8s \t %s\n", yytext, "GEQ"); }
"<="        { printf("%-8s \t %s\n", yytext, "LEQ"); }
"=="        { printf("%-8s \t %s\n", yytext, "EQL"); }
"!="        { printf("%-8s \t %s\n", yytext, "NEQ"); }
"="         { printf("%-8s \t %s\n", yytext, "ASSIGN"); }
"+="        { printf("%-8s \t %s\n", yytext, "ADD_ASSIGN"); }
"-="        { printf("%-8s \t %s\n", yytext, "SUB_ASSIGN"); }
"*="        { printf("%-8s \t %s\n", yytext, "MUL_ASSIGN"); }
"/="        { printf("%-8s \t %s\n", yytext, "QUO_ASSIGN"); }
"%="        { printf("%-8s \t %s\n", yytext, "REM_ASSIGN"); }
"&&"        { printf("%-8s \t %s\n", yytext, "AND"); }
"||"        { printf("%-8s \t %s\n", yytext, "OR"); }
"!"         { printf("%-8s \t %s\n", yytext, "NOT"); }
"("         { printf("%-8s \t %s\n", yytext, "LPAREN"); }
")"         { printf("%-8s \t %s\n", yytext, "RPAREN"); }
"["         { printf("%-8s \t %s\n", yytext, "LBRACK"); }
"]"         { printf("%-8s \t %s\n", yytext, "RBRACK"); }
"{"         { printf("%-8s \t %s\n", yytext, "LBRACE"); }
"}"         { printf("%-8s \t %s\n", yytext, "RBRACE"); }
";"         { printf("%-8s \t %s\n", yytext, "SEMICOLON"); }
","         { printf("%-8s \t %s\n", yytext, "COMMA"); }
"int"       { printf("%-8s \t %s\n", yytext, "INT"); }
"float"     { printf("%-8s \t %s\n", yytext, "FLOAT"); }
"bool"      { printf("%-8s \t %s\n", yytext, "BOOL"); }
"string"    { printf("%-8s \t %s\n", yytext, "STRING"); }
"void"      { printf("%-8s \t %s\n", yytext, "VOID"); }
"true"      { printf("%-8s \t %s\n", yytext, "TRUE"); }
"false"     { printf("%-8s \t %s\n", yytext, "FALSE"); }
"print"     { printf("%-8s \t %s\n", yytext, "PRINT"); }
"return"    { printf("%-8s \t %s\n", yytext, "RETURN"); }
"if"        { printf("%-8s \t %s\n", yytext, "IF"); }
"else"      { printf("%-8s \t %s\n", yytext, "ELSE"); }
"for"       { printf("%-8s \t %s\n", yytext, "FOR"); }
"while"     { printf("%-8s \t %s\n", yytext, "WHILE"); }
"continue"  { printf("%-8s \t %s\n", yytext, "CONTINUE"); }
"break"     { printf("%-8s \t %s\n", yytext, "BREAK"); }

{id}        { printf("%-8s \t %s\n", yytext, "IDENT"); }

{string}    {   printf("%-8c \t %s\n", yytext[0], "QUOTA");
                int x=0;
                char* temp=(char*)malloc(sizeof(char)*(strlen(yytext)-2));
                for(x=1;x<strlen(yytext)-1;x++){
                    temp[x-1]=yytext[x];
                }
                printf("%-8s \t %s\n", temp, "STRING_LIT");
                printf("%-8c \t %s\n", yytext[strlen(yytext)-1], "QUOTA");
              
            }

{inumber}   { printf("%-8s \t %s\n", yytext, "INT_LIT"); }
{fnumber}   { printf("%-8s \t %s\n", yytext, "FLOAT_LIT"); }

{comment1}  { printf("%-8s \t %s\n", yytext, "C++ Comment"); comment_num++;}
{comment2}  { printf("%-8s \t %s\n", yytext, "C Comment"); comment_num++;}
"/*"        { printf("%s", yytext); BEGIN COMMENT;}

"\n"        { line_num++; }
<<EOF>>     { line_num++; yyterminate(); }
.           {;}

<COMMENT>.        { printf("%s", yytext); }
<COMMENT>\n       { printf(" \t %s\n", "C Comment"); line_num++; comment_num++;}
<COMMENT>"*/" { printf("%s \t %s\n", yytext, "C Comment"); comment_num++; BEGIN INITIAL;}

%%

/*  C Code section  */
int yywrap(void)
{
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    yylex();
    printf("\nFinish scanning,\n");
    printf("total line: %d\n", line_num);
    printf("comment line: %d\n", comment_num);
    fclose(yyin);
    return 0;
}