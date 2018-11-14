/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define OPERATOR 1
#define OPERANT 0

typedef struct {
    char *value;
    bool type;
} Token;

typedef struct 
    Abs *left;
    char operator;
    char operand [ 10 ];
    Abs *right;
} Abs;

Abs S = { NULL, '', "", NULL };

int main ( void ) {
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    /**
        Reading expression in the form of the following context free grammar
        expressed in BNF notation:

        <Exp> ::= <Exp> <Op> <Exp> | <Num>
        <Num> ::= <Cif> | <Num><Cif>
        <Cif> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
        <Op> ::= + | - | * | /
    **/

    char production[1000];
    assert ( 1 == scanf ( "%s", &production ) );

    char operator [ 10 ] = "";
    for ( int i = 0; production[ i ] != '\0'; i++ ) {
        if ( !isOperand ( production [ i ] ) ) {
            operator = strcat ( operator, production [ i ] );
        } else {
            Abs tree = { }
        }
    }


    printf ( "%s\n", production );
}

bool isOperand ( char element ) {

    switch ( element ) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
    }

    return false;
}

void absAppend ( char operator, const char *operand ) {
    Abs tree = { NULL, operator, operand, NULL };

    if ( S->left == NULL ) 
        S->left = &tree;
    
    Abs *rec = S;

    while ( rec->left != NULL ) {
        rec = rec->right;
    }

    
}