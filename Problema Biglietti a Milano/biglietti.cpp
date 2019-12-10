#include <iostream>
#include <stdio.h>

using namespace std;

int main( void )
{
    /** Input redirection su file **/
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int numero_corse, dimensione_carnet, costo_corsa, costo_carnet;

    cin >> numero_corse >> dimensione_carnet >> costo_corsa >> costo_carnet;

    /// Se il carnet NON conviene
    if ( ( costo_corsa * dimensione_carnet ) < costo_carnet ) {
        cout << numero_corse * costo_corsa;
    } else {
        int spesa = 0;

        // Compro carnet fino a che il numero dei viaggi rimanenti è maggiore del numero di Carnet
        while ( numero_corse >= dimensione_carnet ) {
            spesa = spesa + costo_carnet;
            numero_corse = numero_corse - dimensione_carnet;
        }

        if ( ( numero_corse * costo_corsa ) < costo_carnet )
            // Se per i rimanenti NON conviene un carnet
            spesa = spesa + numero_corse * costo_corsa;
        else
            // Se conviene un carnet
            spesa = spesa + costo_carnet;

        cout << spesa;
    }

    return 0;
}
