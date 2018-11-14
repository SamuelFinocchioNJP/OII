/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <assert.h>
#include <stdio.h>

// constraints
#define MAXN 1000000

// input data
int N;

int main ( void ) {
    /***
        Leggiamo il numero N per cui calcolare la distanza di Collatz
    **/
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    assert ( 1 == scanf( "%d", &N ) );

    int steps = 1;
    while ( N != 1 ) {
        /** 
            Se N è pari, dividi N per 2
        **/
        if ( N % 2 == 0 ) 
            N = N / 2;
        else
            /**
                Se N è dispari moltiplicalo per 3 e aggiungi 1.
            **/
            N = 3*N + 1;

        // Incrementiamo il numero di operazioni di Collatz
        steps ++;
    }

    /**
        In output il numero di passaggi effettuati per arrivare ad 1
    **/
    printf ( "%d", steps );
    return 0;
}