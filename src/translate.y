%{
    #define _GNU_SOURCE         /* for asprintf */
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
        if (!go_type) return "()";  // void in Rust
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
    struct {
        char* name;
        char* type;
    } param;
}

%token <str> INT FLOAT STRING '+' '-' '*' '/' NUMBER DECLARE_ASSIGN ASSIGN ID PACKAGE IMPORT TYPE STRUCT FUNC RETURN LBRACE RBRACE LPAR RPAR LSTRPAR RSTRPAR NEWLINE
%type <expr> expr
%type <str> type
%type <param> param
%type <expr> statement
%type <expr> expr_stmt
%type <expr> returnable
%type <expr> var_decl
%type <expr> return_stmt
%type <expr> top_lvl_decl
%type <expr> func_decl
%type <expr> struct_decl

%%
program
    : package_decl newlines import_decls newlines top_lvl_decls newlines
    ;

newlines
    : 
    | newlines NEWLINE {
            if (print_newline_flag) {
                fprintf(fptr, "\n");
            } else {
                print_newline_flag = 1;
                break;
            }
            print_newline_flag = 0;
        }
    ;

package_decl
    : PACKAGE ID {fprintf(fptr,"mod %s;\n", $2);}
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
    | var_decl { $$ = NULL; /* Skip top-level variable declarations */ }
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
        fprintf(fptr, "%s) -> %s {\n", temp, convert_type($6));
        if (current_block) {
            fprintf(fptr, "%s", current_block);
            free(current_block);
            current_block = NULL;
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
        asprintf(&temp, "%s: %s", $1.name, $1.type);
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
    : /* empty */ { $$ = NULL; }
    | INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | STRING { $$ = $1; }
    ;

block
    : LBRACE newlines stmt_list newlines RBRACE {
        // Don't create new string, use what's accumulated
        if (!current_block) {
            current_block = strdup("");
        }
    }
    ;

stmt_list
    : { current_block = strdup(""); }
    | stmt_list newlines statement {
        if ($3) {
            char* temp = current_block;
            asprintf(&current_block, "%s    %s\n", temp ? temp : "", $3);
            free(temp);
        }
    }
    ;

statement
    : expr_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    | var_decl { $$ = $1; }
    | if_stmt { $$ = ""; }
    | while_stmt { $$ = ""; }
    | for_stmt { $$ = ""; }
    ;

expr_stmt
    : expr { $$ = $1; }
    ;

var_decl
    : ID DECLARE_ASSIGN expr {
        char* temp;
        asprintf(&temp, "let %s = %s;", $1, $3);
        $$ = temp;
    }
    ;

struct_decl
    : { $$ = NULL; }
    ;

if_stmt
    :
    ;

while_stmt
    :
    ;

for_stmt
    :
    ;

return_stmt
    : RETURN returnable {
        char* temp;
        asprintf(&temp, "return %s;", $2);
        $$ = temp;
    }
    ;

returnable
    : /* empty */ { $$ = strdup(""); }
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
        asprintf(&temp, "let %s = %s;", $1, $3);
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