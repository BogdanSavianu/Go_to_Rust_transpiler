%{
    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1

    void yyerror(const char *s);
    int yylex(void);    

    int yydebug = 1;
    int print_newline_flag = 0;
    FILE *fptr;

    struct Parameter {
        char* name;
        char* type;
    };

    struct LibMap {
        const char* go_lib;
        const char* rust_lib;
    } lib_mappings[] = {
        {"fmt", "std::io"},
        {"std", "std"}
    };

    const char* map_library(const char* go_lib) {
        char *clean_lib = strdup(go_lib);
        if (clean_lib[0] == '"') {
            clean_lib++;
            clean_lib[strlen(clean_lib)-1] = '\0';
        }
        
        for (int i = 0; lib_mappings[i].go_lib != NULL; i++) {
            if (strcmp(clean_lib, lib_mappings[i].go_lib) == 0) {
                return lib_mappings[i].rust_lib;
            }
        }
        return clean_lib;
    }

    const char* convert_type(const char* go_type) {
        if (!go_type) return "()";
        if (strcmp(go_type, "int") == 0) return "i32";
        if (strcmp(go_type, "float") == 0) return "f64";
        if (strcmp(go_type, "string") == 0) return "String";
        return go_type;
    }

    char* current_block = NULL;

    char* param_list_buffer = NULL;
%}

%union {
    char *str;
    char *expr;
    char *block;
    char *stmt_list;
    struct {
        char* name;
        char* type;
    } param;
}

%token <str> INT FLOAT STRING '+' '-' '*' '/' '%' ';' NUMBER DECLARE_ASSIGN ASSIGN EQUALS ID PACKAGE IMPORT TYPE STRUCT FUNC RETURN LBRACE RBRACE LPAR RPAR LSTRPAR RSTRPAR NEWLINE IF ELSE FOR WHILE
%type <expr> expr
%type <str> type
%type <str> newlines
%type <param> param
%type <expr> statement
%type <expr> expr_stmt
%type <expr> returnable
%type <expr> var_decl
%type <expr> return_stmt
%type <expr> top_lvl_decl
%type <expr> func_decl
%type <expr> struct_decl
%type <expr> if_stmt
%type <expr> while_stmt
%type <expr> for_stmt
%type <block> block
%type <stmt_list> stmt_list

%%
program
    : package_decl newlines import_decls newlines top_lvl_decls newlines
    ;

newlines
    : 
    | newlines NEWLINE {
            if (print_newline_flag) {
                $$ = "\n";
            } else {
                print_newline_flag = 1;
                break;
            }
            print_newline_flag = 0;
        }
    ;

package_decl
    : PACKAGE ID {/*fprintf(fptr,"mod %s;\n", $2);*/}
    ;

import_decls
    : 
    | import_decls newlines import_decl 
    ;

import_decl
    : IMPORT ID {fprintf(fptr,"use %s;\n", map_library($2));}
    ;

top_lvl_decls
    :
    | top_lvl_decls newlines top_lvl_decl
    ;

top_lvl_decl
    : func_decl { $$ = $1; }
    | var_decl { $$ = NULL; }
    | struct_decl { $$ = $1; }
    ;

func_decl
    : FUNC ID LPAR param_list RPAR type block {
        char* temp;
        asprintf(&temp, "fn %s(", $2);
        if (param_list_buffer) {
            char* temp2;
            asprintf(&temp2, "%s%s", temp, param_list_buffer);
            free(temp);
            temp = temp2;
            free(param_list_buffer);
            param_list_buffer = NULL;
        }
        const char* return_type = convert_type($6);
        if (strcmp(return_type, "()") != 0) {
            fprintf(fptr, "%s) -> %s {\n", temp, return_type);
        } else {
        fprintf(fptr, "%s) {\n", temp);
        }
        if ($7) {
            fprintf(fptr, "%s", $7);
            free($7);
        }
        fprintf(fptr, "}\n");
        $$ = temp;
    }
    ;

param_list
    : { param_list_buffer = strdup(""); }
    | param_list_nonempty
    ;

param_list_nonempty
    : param {
        param_list_buffer = strdup($1.name);
        char* temp;
        asprintf(&temp, "%s: %s", $1.name, convert_type($1.type));
        param_list_buffer = temp;
    }
    | param_list_nonempty ',' param {
        char* temp;
        asprintf(&temp, "%s, %s: %s", param_list_buffer, $3.name, convert_type($3.type));
        free(param_list_buffer);
        param_list_buffer = temp;
    }
    ;

param 
    : ID type {
        $$.name = strdup($1);
        $$.type = strdup(convert_type($2));
        //fprintf(fptr, "%s: %s", $1, convert_type($2));
    }
    ;

type
    : { $$ = NULL; }
    | INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | STRING { $$ = $1; }
    ;

block
    : LBRACE newlines stmt_list newlines RBRACE {
        $$ = $3 ? strdup($3) : strdup("");
        printf("DEBUG: Block content: '%s'\n", $$);
        if ($3) free($3);
    }
    ;

stmt_list
    : { 
        $$ = strdup(""); 
    }
    | stmt_list newlines statement {
        if ($3) {
            asprintf(&$$, "%s    %s\n", $1 ? $1 : "", $3);
            if ($1) free($1);
            if ($3) free($3);
        } else {
            $$ = $1 ? strdup($1) : strdup("");
            printf("DEBUG: No statement to add, keeping: '%s'\n", $$);
            if ($1) free($1);
        }
    }
    ;

statement
    : expr_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    | var_decl { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    ;

expr_stmt
    : expr { $$ = $1; }
    ;

var_decl
    : ID DECLARE_ASSIGN expr {
        char* temp;
        asprintf(&temp, "let mut %s = %s;", $1, $3);
        $$ = temp;
    }
    ;

struct_decl
    : { $$ = NULL; }
    ;

if_stmt
    : IF expr block {
        char* temp;
        asprintf(&temp, "if %s {\n    %s    }", $2, $3 ? $3 : "");
        $$ = temp;
        if ($3) free($3);
    }
    | IF expr block ELSE block {
        char* temp;
        asprintf(&temp, "if %s {\n    %s    } else {\n    %s    }", $2, $3 ? $3 : "", $5 ? $5 : "");
        $$ = temp;
        if ($3) free($3);
        if ($5) free($5);
    }
    | IF expr block ELSE if_stmt {
        char* temp;
        asprintf(&temp, "if %s {\n    %s    } else %s", $2, $3 ? $3 : "", $5 ? $5 : "");
        $$ = temp;
        if ($3) free($3);
    }
    ;

while_stmt
    : WHILE expr block {
        char* temp;
        asprintf(&temp, "while %s {\n    %s    }", $2, $3 ? $3 : "");
        $$ = temp;
        if ($3) free($3);
    }
    ;

for_stmt
    : FOR ID DECLARE_ASSIGN expr ';' expr ';' ID ASSIGN expr block {
        char* temp;
        char* end_term = $6;
        int i = 0;
        while (end_term[i] && end_term[i] != '<' && end_term[i] != '>') i++;
        end_term += i + 1;
        asprintf(&temp, "for %s in %s..%s {\n    %s}", $2, $4, end_term, $11 ? $11 : "");
        $$ = temp;
        if ($11) free($11);
        if ($2) free($2);
        if ($4) free($4);
        if ($6) free($6);
        if ($8) free($8);
        if ($10) free($10);
    }
    ;

return_stmt
    : RETURN returnable {
        char* temp;
        asprintf(&temp, "return %s;", $2);
        $$ = temp;
    }
    ;

returnable
    : { $$ = strdup(""); }
    | expr { $$ = $1; }
    ;

expr
    : ID ASSIGN expr {  
        char* temp;
        asprintf(&temp, "%s = %s;", $1, $3);
        $$ = temp;
    }
    | ID DECLARE_ASSIGN expr { 
        char* temp;
        asprintf(&temp, "let mut %s = %s;", $1, $3);
        $$ = temp;
    }
    | expr EQUALS expr { 
        char* temp;
        asprintf(&temp, "%s == %s", $1, $3);
        $$ = temp;
    }
    | ID '(' arg_list ')' {
        char* temp;
        asprintf(&temp, "%s()", $1);
        $$ = temp;
    }
    | expr '+' expr { 
        char* temp;
        asprintf(&temp, "%s + %s", $1, $3);
        $$ = temp;
    }
    | expr '-' expr { 
        char* temp;
        asprintf(&temp, "%s - %s", $1, $3);
        $$ = temp;
    }
    | expr '*' expr { 
        char* temp;
        asprintf(&temp, "%s * %s", $1, $3);
        $$ = temp;
    }
    | expr '/' expr { 
        char* temp;
        asprintf(&temp, "%s / %s", $1, $3);
        $$ = temp;
    }
    | expr '%' expr { 
        char* temp;
        asprintf(&temp, "%s %% %s", $1, $3);
        $$ = temp;
        if ($1) free($1);
        if ($3) free($3);
    }
    | expr '<' expr { 
        char* temp;
        asprintf(&temp, "%s < %s", $1, $3);
        $$ = temp;
    }
    | expr '>' expr { 
        char* temp;
        asprintf(&temp, "%s > %s", $1, $3);
        $$ = temp;
    }
    | ID { $$ = $1; }
    | NUMBER { $$ = $1; }
    | STRING { $$ = $1; }
    ;

arg_list
    :
    | arg_list_nonempty
    ;

arg_list_nonempty
    : expr
    | arg_list_nonempty ',' expr
    ; 
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    fptr = fopen("test.rs", "w");
    yyparse();
    return 0;
}