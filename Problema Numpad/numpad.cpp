/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constraints
#define MAXN 1000000

// input data
int N;
char S[ MAXN + 1 ];

// Struttura dati contente una tuple di coordinate (x, y) di un tasto
typedef struct {
    int x;
    int y;
} Tuple;

Tuple map ( char );
int distance ( Tuple, Tuple );

int main ( void ) {
    /***
        Leggiamo la stringa da digitare sul tastierino
    **/
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    assert ( 1 == scanf( "%s", S ) );
    N = strlen ( S );

    /***
        Definiamo un array di tuple (x, y)
        dove inseriremo le coordinate corrispondenti ad ogni tasto premuto sul tastierino
    **/
    Tuple mappedButtons [ N ];

    /**
        Mappiamo ogni tasto premuto sul tastierino 
        con una corrispondente tupla di coordinate
    **/
    for ( int i = 0; i < N; i++ ) {
        mappedButtons [ i ] = map( S[ i ] );
        
        // Decommentare per vedere l'output della funzione map su tutta la stringa
        // printf ( "[%d, %d] ", mappedButtons[ i ].x, mappedButtons[ i ].y );
    }

    /** 
        Calcoliamo la distanza di mappedButtons[ i ] con mappedButtons [ i + 1 ] 
        per ogni i nell'intervallo [0, N - 1]
    **/
    int path_size = 0;
    for ( int i = 0; i < N - 1; i++ ) {
        path_size += distance ( mappedButtons[i], mappedButtons[i + 1] );
    }

    /**
        Se il primo carattere del numero di telefono da digitare non è zero
        sommare la distanza tra il primo carattere da digitare e 0
    **/
    if ( S[ 0 ] != 0 ) 
        path_size = path_size + distance ( map ( '0' ), map ( S[ 0 ] ) );
    
    /** 
        Sommiamo alla distanza tra i tasti il numero dei tasti da premere
        e restituiamo in output il risultato
    **/
    printf( "%d", path_size + N );
    return 0;
}

// Assegna ad ogni pulsante della tastiera le sue coordinate
Tuple map ( char button ) {

    switch ( button ) {
        // Assegnamo a * il numero 10
        case '*': 
            button = 10;
            break;

        // Assegnamo a # il numero 11
        case '#': 
            button = 11;
            break;
        
        // Assegnamo ad ogni numero il suo corrispettivo valore numerico 
        // '1' -> 1, '2' -> 2, ... '9' -> 9
        default:
            button = button - 48;
            break;
    }

    // Array di tuple associate tramite l'indice alle rispettive coordinate
    Tuple keys [ 12 ] = {
        { 3, 1 }, // 0
        { 0, 0 }, // 1
        { 0, 1 }, // 2
        { 0, 2 }, // 3
        { 1, 0 }, // 4
        { 1, 1 }, // 5
        { 1, 2 }, // 6
        { 2, 0 }, // 7
        { 2, 1 }, // 8
        { 2, 2 }, // 9
        { 3, 0 }, // 10 *
        { 3, 2 }  // 11 #
    };

    return keys [ button ];
}

/**
    Calcola la distanza tra 2 tuple
**/
int distance ( Tuple t1, Tuple t2 ) {
    /**
        Definiamo la distanza tra una tupla t1 e una tupla t2 come segue:
        | t1.x - t2.x | + | t1.y - t2.y |
    **/
    int distance = abs ( t1.x - t2.x ) + abs ( t1.y - t2.y );
    
    return distance;
}