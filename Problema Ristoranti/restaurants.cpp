/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <stdio.h>
#include <assert.h>

// input data
int N, i, j;
int vote;

int main ( void ) {
    // Il template propone la seguente soluzione di lettura 
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
    
    assert( 1 == scanf( "%d", &N ) );

    int votes [ N ] ;
    for( i = 0; i < N; i++ ) {
        votes [ i ] = 0;
        for( j = 0; j <= N; j++ ) {
            assert( 1 == scanf("%d", &vote) );

            /** 
                Ogni voto diverso da -1
                dove -1 indica ( NON votato )
                viene sommato al punteggio dello specifico ristorante
            */
            if ( vote != -1 )
                votes[i] += vote;
        }
    }

    /** 
        Definiamo leader come l'identificatore del ristorante più votato 
    **/
    int leader = 0;

    /**
        Definiamo max come il voto del ristorante più votato
    **/
    int max = 0;

    /** 
        Ricerca dell'indice massimo:
        La ricerca seguente trova il ristorante (Indice) che ha il voto maggiore
        Tuttavia la ricerca necessita di essere effettuta comparando il voto con max.
    **/ 
    for ( int i = 0; i < N; i++ ) {
        /**
            Se abbiamo trovato un ristorante con un voto superiore al massimo corrente
            sappiamo che quel ristorante diventa il più votato.
            Per assegnarlo come più votato dobbiamo sostituire entrambi il voto e l'indice superiore
        **/
        if ( votes[i] > max ) {
            max = votes[i];
            leader = i;
        }

        /**
            Al termine dobbiamo stampare esclusivamente l'indice come richiesto dal problema
            Partendo l'indice da 0 ma essendo richiesto un indice da 1 sommiamo 1 al valore del leader
        **/
        printf( "%d\n", leader + 1 );
    }

    return 0;
}
