#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

int main( void )
{
    /** Input redirection su file **/
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;

    int altezze [ N ];
    int spostamento;

    cin >> spostamento;
    altezze [ 0 ] = 5000 + spostamento;

    /** Calcoliamo le altezze **/
    for ( int i = 1; i < N; i++ ) {
        cin >> spostamento;
        altezze [ i ] = altezze [ i - 1 ] + spostamento;
    }

    map < int, int > mappa_altezze;

    for ( int i = 0; i < N; i++ ) {
        mappa_altezze [ altezze [ i ] ] ++;
    }

    int max_amount = mappa_altezze [ altezze [ 0 ] ];
    int max_height = altezze [ 0 ];

    #ifdef DEBUG
    for ( map < int, int >::iterator it = mappa_altezze.begin( ); it != mappa_altezze.end( ); ++it )
        cout << it->first << " " << it->second << endl;
    #endif // DEBUG
    
    /** Cerchiamo il massimo tra le quantità di altezze **/
    for ( map< int, int >::iterator it = mappa_altezze.begin(); it != mappa_altezze.end(); ++it ) {
        if ( it->second > max_amount ) {
            max_amount = it->second;
            max_height = it->first;
        }
    }

    cout << max_height << endl;

    return 0;
}
