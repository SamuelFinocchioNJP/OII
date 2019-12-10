#include <iostream>

using namespace std;

int solve ( int[], size_t );

/**
    Input: N, C
    • L’intero N rappresenta il numero di città tra Brescia e Pinerolo (incluse).
    • L’array C, indicizzato da 0 a N − 1, contiene i prezzi base dei taxi nelle varie città.
        Non è riportato il prezzo dei taxi a Pinerolo, che non è rilevante per la soluzione di questo problema.
    • La funzione dovrà restituire il costo minimo in euro per un tragitto in taxi da 0 a N, che verrà
        stampato sul file di output.

**/
int main( void )
{
    /** Input redirection su file **/
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int numero_citta;
    cin >> numero_citta;

    int prezzi_taxi [ numero_citta ];
    for ( int i = 0; i < numero_citta; i++ )
        cin >> prezzi_taxi [ i ];

    cout << solve ( prezzi_taxi, numero_citta );

    return 0;
}

int solve ( int prezzi_taxi[], size_t numero_citta ) {
    int spesa = 0;

    int prezzo_corrente = prezzi_taxi [ 0 ];

    for ( int i = 0; i < numero_citta; i++ ) {
        if ( prezzi_taxi [ i ] < prezzo_corrente )
            prezzo_corrente = prezzi_taxi [ i ];

        spesa += prezzo_corrente;
        prezzo_corrente ++;
    }

    return spesa;
}
