/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.

 * Current Complexity: Θ ( N )
 */

#include <stdio.h>
#include <limits.h>

int main ( void ) {
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    // Quantità di muffin
    int muffinAmount;
    
    // Dimensione della pala
    int groupSize;

    scanf( "%d%d", &muffinAmount, &groupSize );

    // Lista di muffin
    int muffins [ muffinAmount ];

    // Leggiamo i muffin in input
    for ( int i = 0; i < muffinAmount; i++ ) 
        scanf( "%d", &muffins[ i ] );

    

    int muffinOffset = muffinAmount - groupSize;

    int currentTaste = 0;
    for ( int i = 0; i < groupSize; i++ ) {
        currentTaste += muffins[i];
    }

    // Miglior sapore sommato disponibile
    int bestTaste = currentTaste;

    for ( int i = groupSize; i < muffinAmount; i++ ) {
        /**
            Rimosso il primo elemento della precendente somma
        **/
        currentTaste = currentTaste - muffins [ i - groupSize ];

        /**
            Sommare l'elemento successivo
        **/
        currentTaste = currentTaste + muffins [ i ];
        
        if ( currentTaste > bestTaste )
            bestTaste = currentTaste;
    }
        
    /**
        In output la migliore somma dei sapori
    **/
    printf ( "%d\n", bestTaste );
}