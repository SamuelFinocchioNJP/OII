#include <iostream>
#include <algorithm>
#include <stdio.h>

#define DEBUGNO
using namespace std;

struct Persona {
    long long int oraArrivo;
    long long int oraUscita;
};

long long int solve ( Persona persone[], size_t numero_persone );
bool per_ora_ingresso ( struct Persona p1, struct Persona p2 );
bool per_ora_uscita ( struct Persona p1, struct Persona p2 );
void stampa_array ( Persona persone[], size_t dimensione );

int main( void )
{
    int N;

    cin >> N;
    Persona persone [ N ];

    for ( int i = 0; i < N; i++ ) {
        cin >> persone[ i ].oraArrivo >> persone[ i ].oraUscita;
    }

    #ifdef DEBUG
    cout << "Numero di strette: " << solve ( persone, N );
    #endif // DEBUG

    cout << solve ( persone, N );
    return 0;
}

void stampa_array ( Persona persone[], size_t dimensione ) {
    cout << "[ ";

    for ( int i = 0; i < dimensione - 1; i++ )
        cout << persone [ i ].oraArrivo << " " << persone [ i ].oraUscita << ", ";

    cout << persone [ dimensione - 1 ].oraArrivo << " " << persone [ dimensione - 1 ].oraUscita;

    cout << " ]";
}

bool per_ora_ingresso ( struct Persona p1, struct Persona p2 ) {
    return p1.oraArrivo < p2.oraArrivo;
}

bool per_ora_uscita ( struct Persona p1, struct Persona p2 ) {
    return p1.oraUscita < p2.oraUscita;
}

long long int solve ( Persona persone[], size_t numero_persone ) {
    long long int personePresenti = 1;
    long long int strette = 0;

    /// Dichiaro 2 array, ordinati rispettivamente per ora ingresso e per ora uscita
    Persona persone_per_ingresso [ numero_persone ];
    Persona persone_per_uscita [ numero_persone ];

    /// Clono e ordino gli array
    copy( persone, persone + numero_persone, persone_per_ingresso );
    sort ( persone_per_ingresso, persone_per_ingresso + numero_persone, per_ora_ingresso );

    /// Clono e ordino gli array
    copy( persone, persone + numero_persone, persone_per_uscita );
    sort ( persone_per_uscita, persone_per_uscita + numero_persone, per_ora_uscita );

    #ifdef DEBUG
    /// Stampo i 3 array modificati
    cout << "Array originale: " << endl;
    stampa_array ( persone, numero_persone );

    cout << endl << "Array ordinato per ingresso: " << endl;
    stampa_array ( persone_per_ingresso, numero_persone );

    cout << endl << "Array ordinato per uscita: " << endl;
    stampa_array ( persone_per_uscita, numero_persone );

    cout << endl;
    #endif // DEBUG

    int i = 0;
    int j = 0;
    while ( i < numero_persone || j < numero_persone ) {
        if ( persone_per_ingresso [ i ].oraArrivo < persone_per_uscita [ j ].oraUscita ) {
            #ifdef DEBUG
            cout << "Entra " << i + 1 << endl;
            #endif // DEBUG

            strette = strette + personePresenti;
            personePresenti ++;
            i++;
        }

        if ( persone_per_ingresso [ i ].oraArrivo > persone_per_uscita [ j ].oraUscita ) {
            #ifdef DEBUG
            cout << "Esce " << j + 1 << endl;
            #endif // DEBUG

            personePresenti--;
            strette = strette + personePresenti;
            j++;
        }
    }

    return strette;
}
