%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "y.tab.h"
%}

alpha       [A-Za-z]
digit       [0-9]
id          \"*[_]*{alpha}[A-Za-z0-9_]*\"*
number      {digit}+
string      \"[^\"]*\"

%%

package     { yylval.str = strdup(yytext); return PACKAGE; }
import      return IMPORT;
type        return TYPE;
struct      return STRUCT;
int         { yylval.str = strdup(yytext); return INT; }
float       { yylval.str = strdup(yytext); return FLOAT; }
string      { yylval.str = strdup(yytext); return STRING; }
func        return FUNC;
return      return RETURN;
if          { yylval.str = strdup(yytext); return IF; }
else        { yylval.str = strdup(yytext); return ELSE; }
for         return FOR;
while       return WHILE;
":="        return DECLARE_ASSIGN;
"="         return ASSIGN;
"=="        return EQUALS;
"{"         return LBRACE;
"}"         return RBRACE;
"("         return LPAR;
")"         return RPAR;
"["         return LSTRPAR;
"]"         return RSTRPAR;
"+"         return '+';
"-"         return '-';
"*"         return '*';
"/"         return '/';
"%"         { yylval.str = strdup("%"); return '%'; }
"<"         return '<';
">"         return '>';
";"         return ';';  
{id}        { yylval.str = strdup(yytext); return ID; }
{number}    { yylval.str = strdup(yytext); return NUMBER; }
[ \t]       ;
\n          return NEWLINE;
.           {printf("Invalid character: %s\n", yytext); exit(1);}
%%

int yywrap() {
    return 1;
}