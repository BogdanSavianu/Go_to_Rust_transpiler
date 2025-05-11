%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "y.tab.h"
%}

alpha       [A-Za-z]
digit       [0-9]
id          {alpha}[A-Za-z0-9]*
number      {digit}+

%%


package     return PACKAGE;
import      return IMPORT;
type        return TYPE;
struct      return STRUCT;
int         return INT;
float       return FLOAT;
string      return STRING;
func        return FUNC;
return      return RETURN;
":="        return DELCARE_ASSIGN;
"="         return ASSIGN;
"{"         return LBRACE;
"}"         return RBRACE;
"("         return LPAR;
")"         return RPAR;
"["         return LSTRPAR;
"]"         return RSTRPAR;
"+"         return +;
"-"         return -;
"*"         return *;
"/"         return /;
{id}        return ID;
{number}    return NUMBER;
.           ;
%%