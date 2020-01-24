#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main ( void )
{

    freopen ("input.txt","r", stdin );
    freopen ("output.txt","w",stdout);

    vector <int> pari;
    vector <int> dispari;

    int amount;

    cin >> amount;
    int input;
    for ( int i = 0; i < amount; i++ ) {
        cin >> input;
        if ( input % 2 == 0 )
            pari.push_back ( input );
        else
            dispari.push_back ( input );
    }

    sort ( pari.begin(), pari.end() );
    sort ( dispari.begin(), dispari.end() );

    int pariMax = -1;
    if ( pari.size() >= 2 )
        pariMax = pari[ pari.size() - 1 ] + pari [ pari.size() - 2 ];

    int dispariMax = -1;
    if ( dispari.size() >= 2 )
       dispariMax = dispari[ dispari.size() - 1  ] + dispari[ dispari.size() - 2 ];


    cout << max ( pariMax, dispariMax );

    return 0;
}
