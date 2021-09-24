/*	Definition section */
%{
    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    char *type1;
    char *type2;

    char *temp1 = "a";
    char *temp2 = "a";

    char *t;
    bool undefined=false;

    typedef struct{
        char *name;
        char *type;
        int address;
        int lineno;
        int scopeLevel;
        char element_type[10];
        
    }symbol_table;

    typedef struct{
        symbol_table stable[30];
    }table;

    table final_table[30];

    int table_number = 0;

    int table_number_number[30] = {0};
    int address = 0;

    /* Symbol table function - you can add new function if needed. */
    static void create_symbol();
    static void insert_symbol();
    static bool lookup_symbol();
    static void dump_symbol();

    void yyerror (char const *s)
    {
        if(!strcmp(s, "ADD") || !strcmp(s, "SUB") || !strcmp(s, "ASSIGN")){
            if(!undefined){
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno + 1,  s, temp1, temp2);
                undefined = false;
            }
        }
        if(!strcmp(s, "REM")){
            if(strcmp(temp1, "a"))
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp1);
            else
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp2);
        }
        if(!strcmp(s, "AND")){
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp1);
        }
        if(!strcmp(s, "OR")){
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp2);
        }
        if(!strcmp(s, "condition")){
                printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 2,  temp1);
        }
        if(!strcmp(s, "redeclared")){
            int prev = 0 ,find= 0;
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, t) && final_table[i].stable[j].scopeLevel == table_number && !find) {
                        // Same name and scope level.
                        // printf("LINENO:%d\n",final_table[i].stable[j].lineno);
                        prev = final_table[i].stable[j].lineno+1;
                        find = 1;
                    }
                }
            }
            printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno + 1, t, prev);
        }
        if(!strcmp(s, "undefined")){
            printf("error:%d: undefined: %s\n", yylineno + 1, t);
            undefined=true;
        }
        if(!strcmp(s, "ADD_ASSIGN")){
            if(!strcmp(t,"INT_LIT"))
                printf("error:%d: cannot assign to %s\n", yylineno + 1,"int");
        }
    }
%}

%define parse.error verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token typed
 */
%union {
    int i_val;
    float f_val;
    char *s_val;
    /* ... */
}

/* Token without return */
%token VAR
%token <s_val> INT FLOAT BOOL STRING
%token INC DEC
%token  GEQ LEQ EQL NEQ
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token  OR AND
%token NEWLINE
%token PRINT PRINTLN IF ELSE FOR WHILE
%token TRUE FALSE 
/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT
%token <s_val>  ID 
/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type TypeName ArrayType 
%type <s_val> add_op mul_op cmp_op unary_op
%type<s_val> Expression Term1 Term2 Term3 Term4 UnaryExpr PrimaryExpr Operand ConversionExpr
%type<s_val> assign_op  Literal 
/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : StatementList {dump_symbol();}
;

StatementList
    :  Statement
    | Statement StatementList
;

Expression
    : Expression OR Term1 { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT") || !strcmp($3, "int"))temp2 = "int";
        if(!strcmp(temp2, "int"))yyerror("OR");
        printf("OR\n"); 
        $$ = strdup("bool"); 
    }
    | Term1
;

Term1
    : Term1 AND Term2 { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp($1, "I") || !strcmp($1, "INT_LIT") || !strcmp($1, "int"))temp1 = "int";
        if(!strcmp(temp1, "int"))yyerror("AND");
        printf("AND\n"); 
        $$ = strdup("bool");
    }
    | Term2
;

Term2
    : Term2 cmp_op Term3  { printf("%s\n", $2); $$ = strdup("bool");}
    | Term3 
;

Term3
    : Term3 add_op Term4 { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp($1, "I") || !strcmp($1, "INT_LIT") || !strcmp($1, "int"))temp1 = "int";
        if(!strcmp($1, "F") || !strcmp($1, "FLOAT_LIT") || !strcmp($1, "float"))temp1 = "float"; 
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT") || !strcmp($3, "int"))temp2 = "int";
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float"))temp2 = "float"; 
        if(strcmp(temp1, temp2))yyerror($2);
        printf("%s\n", $2);
    }
    | Term4 
;

Term4
    : Term4 mul_op Term4 { 
        if(!strcmp($2, "REM")){
            temp1 = "a";
            temp2 = "a";
            if(!strcmp($1, "F") || !strcmp($1, "FLOAT_LIT") || !strcmp($1, "float"))temp1 = "float";
            if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float"))temp2 = "float";
            if(!strcmp(temp1, "float") || !strcmp(temp2, "float"))yyerror($2);
        }
        printf("%s\n", $2);
    }
    | UnaryExpr
;

UnaryExpr
    : PrimaryExpr
    | unary_op UnaryExpr { printf("%s\n", $1);}
;

cmp_op
    : EQL { $$ = strdup("EQL");}
    | NEQ { $$ = strdup("NEQ");}
    | '<' { $$ = strdup("LSS");}
    | LEQ { $$ = strdup("LEQ");}
    | '>' { $$ = strdup("GTR");}
    | GEQ { $$ = strdup("GEQ");}
;

add_op
    : '+' { $$ = strdup("ADD");}
    | '-'  { $$ = strdup("SUB");}
;

mul_op
    : '*' { $$ = strdup("MUL");}
    | '/'  { $$ = strdup("QUO");}
    | '%' { $$ = strdup("REM");}
;

unary_op
    : '+' { $$ = strdup("POS");}
    | '-' { $$ = strdup("NEG");}
    | '!' { $$ = strdup("NOT");}
;

PrimaryExpr
    : Operand 
    | IndexExpr
    | ConversionExpr
;

Operand
    : Literal
    | ID {   
        lookup_symbol($1);
        int find = 0;
        for(int i = table_number; i >=0; i--){
            for(int j = 0; j < table_number_number[i]; j++){
                if(!strcmp(final_table[i].stable[j].name, $1) && !find){
                    if(!strcmp(final_table[i].stable[j].type, "int"))$$ = "I";
                    if(!strcmp(final_table[i].stable[j].type, "float"))$$ = "F";
                    if(!strcmp(final_table[i].stable[j].type, "bool"))$$ = "bool";
                    if(!strcmp(final_table[i].stable[j].type, "string"))$$ = "string";
                    if(!strcmp(final_table[i].stable[j].type, "array"))$$ = final_table[i].stable[j].element_type;
                    find = 1;
                }
            }
        }
        if(find==0){
            t=$1;
            yyerror("undefined");
        }
    }
    | '(' Expression ')'
;

Literal
    : INT_LIT { printf("INT_LIT %d\n", $1);  $$ = "INT_LIT"; }
    | FLOAT_LIT { printf("FLOAT_LIT %f\n", $1);  $$ = "FLOAT_LIT"; }
    | TRUE { printf("TRUE\n");  $$ = "TRUE";}
    | FALSE { printf("FALSE\n");  $$ = "FALSE";}
    | STRING_LIT { printf("STRING_LIT %s\n", $1); $$ = "string";}
;

IndexExpr
    : PrimaryExpr '[' Expression ']'
;

ConversionExpr
    : '(' Type ')' Expression {
        char temp1;
        char temp2;
        if(!strcmp($2, "I") || !strcmp($2, "INT_LIT") || !strcmp($2, "int"))temp1 = 'I';
        if(!strcmp($2, "F") || !strcmp($2, "FLOAT_LIT") || !strcmp($2, "float"))temp1 = 'F';
        if(!strcmp($4, "I") || !strcmp($4, "INT_LIT") || !strcmp($4, "int"))temp2 = 'I';
        if(!strcmp($4, "F") || !strcmp($4, "FLOAT_LIT") || !strcmp($4, "float"))temp2 = 'F';
        if(temp1=='I' && temp2=='F')$$ = "float";
        if(temp1=='I' && temp2=='F')$$ = "int";
        printf("%c to %c\n", temp2, temp1);                            
    }
;


Statement
    : DeclarationStmt ';'
    | SimpleStmt ';'
    | Block NEWLINE
    | IfStmt
    | ElseStmt
    | ForStmt 
    | PrintStmt ';'
    | WhileStmt 
    | NEWLINE
;


SimpleStmt
    : AssignmentStmt
    | ExpressionStmt
    | IncDecStmt
;

DeclarationStmt
    : Type ID {
        bool exist = false;

        for(int i = table_number; i >=0; i--){
            for(int j = 0; j < table_number_number[i]; j++){
                if(!strcmp(final_table[i].stable[j].name, $2) && final_table[i].stable[j].scopeLevel == table_number && !exist){
                    exist = true;
                }
            }
        }
        if(!exist)
            insert_symbol($2, $1 );
        else {
            t = $2;
            yyerror("redeclared");
        }
    }
    | Type ID '=' Expression { 
        insert_symbol($2, $1);    
    }
    | ArrayType
;

AssignmentStmt
    : Expression assign_op Expression  {
        temp1 = "a";
        temp2 = "a";
        int find = 0;
        if(!strcmp($1, "I") || !strcmp($1, "INT_LIT") || !strcmp($1, "int"))temp1 = "int";
        if(!strcmp($1, "F") || !strcmp($1, "FLOAT_LIT") || !strcmp($1, "float"))temp1 = "float"; 
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT") || !strcmp($3, "int"))temp2 = "int";
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float"))temp2 = "float"; 

        if(!strcmp(temp1, "a")){
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, $3) && !find){
                        if(!strcmp(final_table[i].stable[j].type, "int"))temp1 = "int";
                        if(!strcmp(final_table[i].stable[j].type, "float"))temp1 = "float";
                        if(!strcmp(final_table[i].stable[j].type, "bool"))temp1 = "bool";
                        if(!strcmp(final_table[i].stable[j].type, "string"))temp1 = "string";
                        if(!strcmp(final_table[i].stable[j].type, "array"))temp1 = final_table[i].stable[j].element_type;
                        find = 1;
                    }
                }
            }
        }

        if(!strcmp(temp2, "a")){
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, $3) && !find){
                        if(!strcmp(final_table[i].stable[j].type, "int"))temp2 = "int";
                        if(!strcmp(final_table[i].stable[j].type, "float"))temp2 = "float";
                        if(!strcmp(final_table[i].stable[j].type, "bool"))temp2 = "bool";
                        if(!strcmp(final_table[i].stable[j].type, "string"))temp2 = "string";
                        if(!strcmp(final_table[i].stable[j].type, "array"))temp2 = final_table[i].stable[j].element_type;
                        find = 1;
                    }
                }
            }
        }

        if(strcmp(temp1, temp2))yyerror($2);
        if(!strcmp($2,"ADD_ASSIGN") && !strcmp($1,"INT_LIT")){
            t=$1;
            yyerror($2);
        }
        printf("%s\n", $2);
    
    }
;

assign_op
    : '=' { $$ = strdup("ASSIGN"); }
    | ADD_ASSIGN { $$ = strdup("ADD_ASSIGN"); }
    | SUB_ASSIGN { $$ = strdup("SUB_ASSIGN"); }
    | MUL_ASSIGN { $$ = strdup("MUL_ASSIGN"); }
    | QUO_ASSIGN { $$ = strdup("QUO_ASSIGN"); }
    | REM_ASSIGN { $$ = strdup("REM_ASSIGN"); }
;

ExpressionStmt
    : Expression
;

IncDecStmt 
    : Expression INC { printf("INC\n");}
    | Expression DEC { printf("DEC\n");}
;

Block
    :'{' { create_symbol();} StatementList '}' {dump_symbol();}
;

IfStmt
    : IF Condition Block ElseStmt
;

ElseStmt
    : ELSE Block
    | ELSE IfStmt
    | NEWLINE
;

Condition
    : '(' Expression ')' {
        temp1 = $2;
        temp2 = "a";     
        if(!strcmp($2, "I") || !strcmp($2, "INT_LIT") || !strcmp($2, "int"))temp1 = "int";
        if(!strcmp($2, "F") || !strcmp($2, "FLOAT_LIT") || !strcmp($2, "float"))temp1 = "float"; 
        if(strcmp($2, "bool"))yyerror("condition");
    }
    | '(' Expression ')' NEWLINE {
        temp1 = $2;
        temp2 = "a";     
        if(!strcmp($2, "I") || !strcmp($2, "INT_LIT") || !strcmp($2, "int"))temp1 = "int";
        if(!strcmp($2, "F") || !strcmp($2, "FLOAT_LIT") || !strcmp($2, "float"))temp1 = "float"; 
        if(strcmp($2, "bool"))yyerror("condition");
    }
;

WhileStmt
    : WHILE Condition Block

ForStmt
    : FOR '(' ForClause ')' Block
;

ForClause
    : InitStmt ';' Expression ';' PostStmt {
        temp1 = $3;
        temp2 = "a";     
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT") || !strcmp($3, "int"))temp1 = "int";
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float"))temp1 = "float"; 
        if(strcmp($3, "bool"))yyerror("condition");
    }
;

InitStmt
    : SimpleStmt
;

PostStmt
    : SimpleStmt
;

PrintStmt
    : PRINT '(' Expression ')' { 
        char *temp;
        temp = $3;
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT"))temp = "int";
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT"))temp = "float"; 
        printf("PRINT %s\n", temp);
    }
    | PRINTLN '(' Expression ')' { 
        char *temp;
        temp = $3;
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT"))temp = "int";
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT"))temp = "float"; 
        printf("PRINTLN %s\n", temp);
    }
;

Type
    : TypeName
    | ArrayType
;

TypeName
    : INT { $$ = strdup("int");}
    | FLOAT { $$ = strdup("float");}
    | STRING { $$ = strdup("string");}
    | BOOL { $$ = strdup("bool");}
;

ArrayType
    : Type ID '[' Expression ']' { 
        $$ = strdup("array"); 
        insert_symbol($2, "array");   
        strcpy(final_table[table_number].stable[table_number_number[table_number]-1].element_type, $1); 
    }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    table_number++;
}

static void insert_symbol(char *id,char *type) {
    printf("> Insert {%s} into symbol table (scope level: %d)\n", id, table_number);
    final_table[table_number].stable[table_number_number[table_number]].name = id;
    final_table[table_number].stable[table_number_number[table_number]].type = type;
    final_table[table_number].stable[table_number_number[table_number]].address = address;
    final_table[table_number].stable[table_number_number[table_number]].lineno = yylineno;
    final_table[table_number].stable[table_number_number[table_number]].scopeLevel = table_number;
    if(strcmp(type, "array")){
        strcpy(final_table[table_number].stable[table_number_number[table_number]].element_type, "-");
    }
    table_number_number[table_number]++;
    address++;
}

static bool lookup_symbol( char *name) {
    int find = 0;
    for(int i = table_number; i >=0; i--){
        for(int j = 0; j < table_number_number[i]; j++){
            if(!strcmp(final_table[i].stable[j].name, name) && !find){
                printf("IDENT (name=%s, address=%d)\n", name, final_table[i].stable[j].address);
                find = 1;
            }
        }
    }
    if(find == 0)
        return false;
    else
        return true;
}

static void dump_symbol() {
    printf("> Dump symbol table (scope level: %d)\n", table_number);
    printf("%-10s%-10s%-10s%-10s%-10s%s\n",  "Index", "Name", "Type", "Address", "Lineno", "Element type");
    for(int i = 0; i < table_number_number[table_number]; i++){
        printf("%-10d%-10s%-10s%-10d%-10d%s\n",
            i, 
            final_table[table_number].stable[i].name, 
            final_table[table_number].stable[i].type, 
            final_table[table_number].stable[i].address, 
            final_table[table_number].stable[i].lineno+1, 
            final_table[table_number].stable[i].element_type
            );   
    }
    table_number_number[table_number] = 0;
    table_number--;
}
