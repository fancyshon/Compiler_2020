/*	Definition section */
%{
    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    #define codegen(...) \
        do { \
            for (int i = 0; i < INDENT; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;
    
    /* Other global variables */
    FILE *fout = NULL;
    bool HAS_ERROR = false;
    int INDENT = 0;
    
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

    int nowid = -1;
    // 0 => int , 1 => float
    int nowtype = -1;   
    int Nwhile = 0;
    int nowWhile = 0;
    int Ntrurfalse = 0;
    int leftid=-1;
    bool whileloop =false;
    bool ifcmp=false;
    bool novalue=false;
    bool printTrue=true;
    bool inelse=false;
    bool whilefin[5]={true,true,true,true,true};   
    bool right=false;


    /* Symbol table function - you can add new function if needed. */
    static void create_symbol();
    static void insert_symbol();
    static bool lookup_symbol();
    static void dump_symbol();

    void yyerror (char const *s)
    {   
        HAS_ERROR=true;
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

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
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
%token GEQ LEQ EQL NEQ
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token OR AND
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
    : Statement
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
    : Term2 cmp_op Term3  {     
        printf("%s\n", $2); $$ = strdup("bool");   
        if(ifcmp){
            codegen("isub\n");
            codegen("ifeq L_cmp_0\n");
            codegen("iconst_0\n");
            codegen("goto L_cmp_1\n");
            codegen("L_cmp_0 :\n");
            codegen("iconst_1\n");
            codegen("L_cmp_1 :\n");
            codegen("ifeq L_if_false\n");
        } else {
            if(!strcmp($2,"GTR")){
                codegen("isub\n");
                codegen("ifgt L_cmp_0%d\n",nowWhile);
                codegen("iconst_0\n");
                codegen("goto L_cmp_1%d\n",nowWhile);
                codegen("L_cmp_0%d :\n",nowWhile);
                codegen("iconst_1\n");
                codegen("L_cmp_1%d :\n",nowWhile);
                codegen("ifeq L_for_exit%d\n",nowWhile);
            }
            else if(!strcmp($2,"LEQ")){
                codegen("isub\n");
                codegen("ifle L_cmp_0%d\n",nowWhile);
                codegen("iconst_0\n");
                codegen("goto L_cmp_1%d\n",nowWhile);
                codegen("L_cmp_0%d :\n",nowWhile);
                codegen("iconst_1\n");
                codegen("L_cmp_1%d :\n",nowWhile);
                codegen("ifeq L_for_exit%d\n",nowWhile);
            }

        }
    }
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

        if(!strcmp($2,"ADD")){
            if(!strcmp(temp1,"int")){
                codegen("iadd\n");
            } else {
                codegen("fadd\n");
            }
        }
        if(!strcmp($2,"SUB")){
            if(!strcmp(temp1,"int")){
                codegen("isub\n");
            } else {
                codegen("fsub\n");
            }
        }
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
            codegen("irem\n");
        }
        printf("%s\n", $2);

        if(!strcmp($2, "MUL")){
            if(!strcmp($1, "F") || !strcmp($1, "FLOAT_LIT") || !strcmp($1, "float") || !strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float")){
                codegen("fmul\n");
            } else {
                codegen("imul\n");
            }
        }
        if(!strcmp($2, "QUO")){
            if(!strcmp($1, "F") || !strcmp($1, "FLOAT_LIT") || !strcmp($1, "float") || !strcmp($3, "F") || !strcmp($3, "FLOAT_LIT") || !strcmp($3, "float")){
                codegen("fdiv\n");
            } else {
                codegen("idiv\n");
            }
        }
    }
    | UnaryExpr
;

UnaryExpr
    : PrimaryExpr
    | unary_op UnaryExpr {
        printf("%s\n", $1);
        if(nowtype==0){
            codegen("ineg\n");
            nowtype=-1;
        }
        if(nowtype==1){
            codegen("fneg\n");
            nowtype=-1;
        }
    }
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
    | '-'  { $$ = strdup("SUB"); }
;

mul_op
    : '*' { $$ = strdup("MUL");}
    | '/'  { $$ = strdup("QUO"); }
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
        if(whileloop){
            nowWhile=Nwhile++;
            codegen("L_for_begin%d :\n",nowWhile);
            whilefin[nowWhile]=false;
            whileloop=false;
        }
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
    : INT_LIT { 
        printf("INT_LIT %d\n", $1);  
        $$ = "INT_LIT";
        codegen("ldc %d\n",$1); 
        // if(right&&nowtype==3){
        //     codegen("iaload\n");
        //     right=false;
        // }
        // nowtype=-1;
    }
    | FLOAT_LIT { printf("FLOAT_LIT %f\n", $1);  $$ = "FLOAT_LIT"; codegen("ldc %f\n",$1); }
    | TRUE { printf("TRUE\n");  $$ = "TRUE"; codegen("iconst_1\n"); }
    | FALSE { printf("FALSE\n");  $$ = "FALSE"; codegen("iconst_0\n"); }
    | STRING_LIT { printf("STRING_LIT %s\n", $1); $$ = "string"; codegen("ldc \"%s\"\n",$1); }
;

IndexExpr
    : PrimaryExpr '[' Expression ']' {
        lookup_symbol($1);
    }
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

        if(temp1=='I' && temp2=='F'){
            codegen("f2i\n");
        } else if(temp1=='F' && temp2=='I'){
            codegen("i2f\n");
        }
                 
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
        novalue=true;

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
        printf(" %s %s\n",temp1,temp2);
        if(!strcmp($2,"ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowtype!=3){
                    if(nowid!=-1){
                        codegen("istore %d\n",nowid);
                        nowid=-1;
                    }
                    codegen("istore 99\n");
                } else {
                    codegen("iastore\n");
                }
            }
            else if(!strcmp(temp1,"float")&&!strcmp($3,"FLOAT_LIT")){
                if(nowid!=-1){
                    codegen("fstore %d\n",nowid);
                    nowid=-1;
                }
                codegen("fstore 99\n");
            }
            else if(!strcmp(temp1,"int")&&!strcmp(temp2,"int")){
                if(nowid!=-1){
                    codegen("istore %d\n",leftid);
                    nowid=-1;
                }
                codegen("istore 99\n");
            }
            else if(!strcmp(temp1,"float")&&!strcmp(temp2,"float")){
                if(nowid!=-1){
                    codegen("fstore %d\n",leftid);
                    nowid=-1;
                }
                codegen("fstore 99\n");
            }
            else if(!strcmp($1,"string")){
                if(nowid!=-1){
                    codegen("astore %d\n",nowid);
                    nowid=-1;
                }
                codegen("astore 99\n");
            }
            else if(!strcmp($1,"bool")){
                if(nowid!=-1){
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
                codegen("istore 99\n");
            }
            else if(!strcmp($1,"int")&&nowtype==3){
                codegen("iastore\n");
            }
            
        }
        if(!strcmp($2,"ADD_ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowid!=-1){
                    codegen("iadd\n");
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
            }
            if(!strcmp(temp1,"float")&&!strcmp($3,"FLOAT_LIT")){
                if(nowid!=-1){
                    codegen("fadd\n");
                    codegen("fstore %d\n",nowid);
                    nowid=-1;
                }
            }
        }
        if(!strcmp($2,"SUB_ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowid!=-1){
                    codegen("isub\n");
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
            }
            if(!strcmp(temp1,"float")&&!strcmp($3,"FLOAT_LIT")){
                if(nowid!=-1){
                    codegen("fsub\n");
                    codegen("fstore %d\n",nowid);
                    nowid=-1;
                }
            }
        }
        if(!strcmp($2,"MUL_ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowid!=-1){
                    codegen("imul\n");
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
            }
            if(!strcmp(temp1,"float")&&!strcmp($3,"FLOAT_LIT")){
                if(nowid!=-1){
                    codegen("fmul\n");
                    codegen("fstore %d\n",nowid);
                    nowid=-1;
                }
            }
        }
        if(!strcmp($2,"QUO_ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowid!=-1){
                    codegen("idiv\n");
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
            }
            if(!strcmp(temp1,"float")&&!strcmp($3,"FLOAT_LIT")){
                if(nowid!=-1){
                    codegen("fdiv\n");
                    codegen("fstore %d\n",nowid);
                    nowid=-1;
                }
            }
        }
        if(!strcmp($2,"REM_ASSIGN")){
            if(!strcmp(temp1,"int")&&!strcmp($3,"INT_LIT")){
                if(nowid!=-1){
                    codegen("irem\n");
                    codegen("istore %d\n",nowid);
                    nowid=-1;
                }
            }
        }
    }
;

assign_op
    : '=' { $$ = strdup("ASSIGN");leftid=nowid; }
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
    : Expression INC { 
        printf("INC\n"); 
        
        if(nowtype==0){
            codegen("ldc 1\n");
            codegen("iadd\n");
            if(nowid!=-1){
                codegen("istore %d\n",nowid);
                nowid=-1;
            }
            nowtype=-1;
        }
        if(nowtype==1){
            codegen("ldc 1.0\n");
            codegen("fadd\n");
            if(nowid!=-1){
                codegen("fstore %d\n",nowid);
                nowid=-1;
            }
            nowtype=-1;
        }
    }
    | Expression DEC {
        printf("DEC\n");
        if(nowtype==0){
            codegen("ldc 1\n");
            codegen("isub\n");
            if(nowid!=-1){
                codegen("istore %d\n",nowid);
                nowid=-1;
            }
            nowtype=-1;
        }
        if(nowtype==1){
            codegen("ldc 1.0\n");
            codegen("fsub\n");
            if(nowid!=-1){
                codegen("fstore %d\n",nowid);
                nowid=-1;
            }
            nowtype=-1;
        }
    }
;

Block
    :'{' { create_symbol();} StatementList {if(ifcmp)codegen("goto L_if_exit\n");} '}' {
        dump_symbol();
    }
;

IfStmt
    : IFtoken ConditionIf Block ElseStmt {
        codegen("L_if_exit :\n");
        ifcmp=false;
    }
    | IFtoken ConditionIf Block NEWLINE {
        codegen("L_if_false :\n");
        codegen("L_if_exit :\n");
    }
;

IFtoken
    : IF {
        ifcmp=true;
    }
;

ElseStmt
    : ELSE {codegen("L_if_false :\n"); inelse=true;} Block 
    | ELSE {codegen("L_if_false :\n");} IfStmt
;

ConditionWhile
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

ConditionIf
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
    : WHILEtoken ConditionWhile Block {
        if(whilefin[nowWhile]){
            nowWhile--;
        }
        codegen("goto L_for_begin%d\n",nowWhile);
        codegen("L_for_exit%d :\n",nowWhile);
        whilefin[nowWhile]=true;
    }
;

WHILEtoken
    : WHILE {
        whileloop=true;
    }
;

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
        if(!strcmp($3, "I") || !strcmp($3, "INT_LIT") ){
            temp = "int";
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(I)V\n");
        }
        if(!strcmp($3, "F") || !strcmp($3, "FLOAT_LIT")){
            temp = "float";
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(F)V\n");
        }
        printf("PRINT %s\n", temp);
        if(!strcmp($3,"string")){
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }
        if(!strcmp($3,"bool")){
            codegen("ifne LL_cmp_0%d\n",Ntrurfalse);
            codegen("ldc \"false\"\n");
            codegen("goto LL_cmp_1%d\n",Ntrurfalse);
            codegen("LL_cmp_0%d :\n",Ntrurfalse);
            codegen("ldc \"true\"\n");
            codegen("LL_cmp_1%d :\n",Ntrurfalse);
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n");
            codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
            Ntrurfalse++;
        }
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
        codegen("newarray %s\n",$1);
        codegen("astore %d\n",final_table[table_number].stable[table_number_number[table_number]-1].address);
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

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    codegen(".source hw3.j\n");
    codegen(".class public Main\n");
    codegen(".super java/lang/Object\n");
    codegen(".method public static main([Ljava/lang/String;)V\n");
    codegen(".limit stack 100\n");
    codegen(".limit locals 100\n");
    INDENT++;

    yyparse();

	printf("Total lines: %d\n", yylineno);

    /* Codegen end */
    codegen("return\n");
    INDENT--;
    codegen(".end method\n");
    fclose(fout);
    fclose(yyin);

    if (HAS_ERROR) {
        remove(bytecode_filename);
    }
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
    if(novalue){
        if(!strcmp(type,"int")){
            codegen("ldc 0\n");
            codegen("istore %d\n",address);
        }
        if(!strcmp(type,"float")){
            codegen("ldc 0.0\n");
            codegen("fstore %d\n",address);
        }
        if(!strcmp(type,"string")){
            codegen("ldc \"\"\n");
            codegen("astore %d\n",address);
        }
        novalue=false;
    } else {
        if(!strcmp(type,"int") || !strcmp(type,"bool"))
            codegen("istore %d\n",address);
        if(!strcmp(type,"float"))
            codegen("fstore %d\n",address);
        if(!strcmp(type,"string"))
            codegen("astore %d\n",address);

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
                if(!strcmp(final_table[i].stable[j].type,"int") || !strcmp(final_table[i].stable[j].type,"bool")){
                    codegen("iload %d\n",final_table[i].stable[j].address);
                    nowtype=0;
                }
                if(!strcmp(final_table[i].stable[j].type,"float")){
                    codegen("fload %d\n",final_table[i].stable[j].address);
                    nowtype=1;
                }
                if(!strcmp(final_table[i].stable[j].type,"string")){
                    codegen("aload %d\n",final_table[i].stable[j].address);
                    nowtype=2;
                }
                if(!strcmp(final_table[i].stable[j].type,"array")){
                    codegen("aload %d\n",final_table[i].stable[j].address);
                    nowtype=3;
                }
                nowid = final_table[i].stable[j].address;
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
