%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char *s);
    int yylex(void);
%}

%token INT FLOAT STRING + - * / NUMBER DECLARE_ASSIGN ASSIGN ID PACKAGE IMPORT TYPE STRUCT FUNC RETURN LBRACE RBRACE LPAR RPAR LSTRPAR RSTRPAR;

%%
program
    : package_decl import_decls top_lvl_decls
    ;

package_decl
    : PACKAGE ID
    ;

import_decls
    : 
    | import_decls import_decl 
    ;

import_decl
    : IMPORT ID
    ;

top_lvl_decls
    :
    | top_lvl_decls top_lvl_decl
    ;

top_lvl_decl
    : func_decl
    | var_decl
    | struct_decl

func_decl
    : FUNC ID LPAR param_list RPAR type block
    ;

param_list
    :
    | param_list_nonempty
    ;

param_list_nonempty
    : param
    | param_list_nonempty ',' param
    ;

param 
    : ID type
    ;

type
    : INT
    | FLOAT
    | STRING
    ;

block
    : LBRACE stmt_list RBRACE
    ;

stmt_list
    : 
    | stmt_list statement
    ;

statement
    : expr_stmt
    | return_stmt
    | var_decl
    | if_stmt
    | while_stmt
    | for_stmt
    ;

expr_stmt
    : expr
    ;

return_stmt
    : RETURN returnable
    ;

/// continue adding statements

returnable
    : // empty return
    | expr
    ;

expr
    : ID ASSIGN expr
    | ID DECLARE_ASSIGN expr
    | ID '(' arg_list ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | ID
    | NUMBER
    ;

arg_list
    :
    | arg_list_nonempty
    ;

arg_list_nonempty
    : expr
    | arg_list_nonempty ',' expr
    ; 


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    printf("Enter the expression:\n");
    yyparse();
    return 0;
}