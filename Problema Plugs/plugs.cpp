/*
 *
 * Current Complexity: Θ ( NLogN )
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <limits.h>

#define DEBUGNO

using namespace std;

// Definiamo un tipo di dato server che associa ad un server la relativa potenza
typedef struct {
    int flops;
    string plug;
} server;

bool byFlops ( server s1, server s2 ) {
    return s1.flops > s2.flops;
}

int main ( void ) {
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    // Quantità di muffin
    int serverAmount;

    // Dimensione della pala
    int plugsAmount;

    cin >> serverAmount >> plugsAmount;

    // Lista di server
    int serverList [ serverAmount ];

    // Leggiamo i server in input
    string serverPlugsList [ serverAmount ];
    for ( int i = 0; i < serverAmount; i++ )
        cin >> serverList [ i ];

    // Leggiamo le prese dei server in input
    for ( int i = 0; i < serverAmount; i++ )
        cin >> serverPlugsList [ i ];

    // Leggiamo le prese
    int L10 = 0, L16 = 0, bipasso = 0;
    string presa;

    for ( int i = 0; i < plugsAmount; i++ ) {
        cin >> presa;

        if ( presa == "L10" )
            L10 ++;

        if ( presa == "L16" )
            L16 ++;

        if ( presa == "bipasso" )
            bipasso ++;
    }

    // Riempiamo un array di 'server' con i dati presi in input
    server serverListAssoc [ serverAmount ];
    for ( int i = 0; i < serverAmount; i++ ) {
        serverListAssoc[ i ].flops = serverList[ i ];
        serverListAssoc[ i ].plug = serverPlugsList[ i ];
    }

    // Ordiniamo per FLOPS l'array di server
    sort ( serverListAssoc, serverListAssoc + serverAmount, byFlops );

    #ifdef DEBUG
    cout << "Risultato dell'ordinamento: " << endl;
    for ( int i = 0; i < serverAmount; i++ ) {
        cout << serverListAssoc[ i ].flops << " " << serverListAssoc[ i ].plug << endl;
    }
    #endif // DEBUG

    int finalFlops = 0;
    #ifdef DEBUG
    cout << "Prese diponibili: " << endl << "L10 = " << L10 << endl << "L16 = " << L16 << endl << "Bipasso " << bipasso << endl;
    #endif // DEBUG
    /** Ciclamo per i server con approccio goloso **/
    for ( int i = 0; i < serverAmount ; i++ ) {

        /// Se troviamo un server L10 diminuiamo il numero di prese L10
        if ( L10 > 0 && serverListAssoc[ i ].plug == "L10" ) {
            #ifdef DEBUG
            cout << "Server collegato: " << serverListAssoc[ i ].flops << " con presa: " << serverListAssoc[ i ].plug << endl;
            #endif // DEBUG
            L10--;
            finalFlops = finalFlops + serverListAssoc[ i ].flops;
            serverListAssoc[ i ].flops = 0;
        }


        if ( L16 > 0 && serverListAssoc[ i ].plug == "L16" ) {
            #ifdef DEBUG
            cout << "Server collegato: " << serverListAssoc[ i ].flops << " con presa: " << serverListAssoc[ i ].plug << endl;
            #endif // DEBUG
            L16--;
            finalFlops = finalFlops + serverListAssoc[ i ].flops;
            serverListAssoc[ i ].flops = 0;
        }
        #ifdef DEBUG
        cout << "Prese diponibili: " << endl << "L10 = " << L10 << endl << "L16 = " << L16 << endl << "Bipasso " << bipasso << endl;
        #endif // DEBUG
    }
    #ifdef DEBUG
    cout << "Flops assegnati obbligatoriamente " << finalFlops << endl;
    #endif // DEBUG

    // Ri riordiniamo per FLOPS l'array di server
    sort ( serverListAssoc, serverListAssoc + serverAmount, byFlops );

    #ifdef DEBUG
    cout << "Risultato dell'ordinamento 2: " << endl;
    #endif // DEBUG
    for ( int i = 0; i < bipasso; i++ ) {
        #ifdef DEBUG
        cout << serverListAssoc[ i ].flops << " " << serverListAssoc[ i ].plug << endl;
        #endif // DEBUG
        finalFlops = finalFlops + serverListAssoc[ i ].flops;
    }

    #ifdef DEBUG
    cout << "Flops totali: ";
    #endif
    cout << finalFlops;

    return 0;
}
