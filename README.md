This program is meant to translate simple Go code into equivalent Rust code using the lex and yacc tools.

What can be parsed as of right now:
    - packages (Rust does not use package declarations the same way, but rather a separate module file, so this step is skipped)
    - imports ("std" and "fmt") - adding more is trivial, as simple as adding values to lib_mappings
    - function declarations, with or without return types and parameters
    - function bodies containing variable declarations, expressions, if, while, for and return statements
    - **more to come**

In order to use the program, the following trivial steps must be followed:

1. Compiling the lex file:
    - **lex src/translate.l**
2. Compiling the yacc file:
    - **yacc src/translate.y -d -t**
3. Compiling the resulted c files to create the executable:
    - **gcc lex.yy.c y.tab.c -ll -ly -DYYDEBUG**
4. Run the created executable file by directing your go source file as standard input for the program:
    - **./a.out < test.go**