/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.

    * TODO: 
    *   Solve timed out.
    *   Current complexity:
    *   O( ( N-k )*k )
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

    // Miglior sapore sommato disponibile
    int bestTaste = INT_MIN;

    int muffinOffset = muffinAmount - groupSize;

    int currentTaste;
    for ( int i = 0; i <= muffinOffset; i++ ) {
        currentTaste = 0;
        for ( int j = i; j < groupSize + i; j++ ) {
            currentTaste += muffins[ j ];
        }

        if ( currentTaste > bestTaste )
            bestTaste = currentTaste;
    }
        
    /**
        In output la migliore somma dei sapori
    **/
    printf ( "%d\n", bestTaste );
}