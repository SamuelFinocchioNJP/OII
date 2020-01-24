#include <iostream>

using namespace std;

int cct ( int V[], int C[], int N, int K, int i, int c, int MEMO[][21] );
int ccto ( int V[], int C[], int N, int K, int i, int c );

int main ( void )
{
    /// N numero livelli, k carica necessaria per skippare
    int N, K;

    cin >> N >> K;

    /// V[i] Tempo per livello i
    /// C[i] Carica per livello i
    int V[N];
    int C[N];

    int MEMO [ N ] [ 21 ] = { { 0 } };

    for ( int i = 0; i < N; i++ )
        cin >> V[i];

    for ( int i = 0; i < N; i++ )
        cin >> C[i];

    cout << cct ( V, C, N, K, 0, 0, MEMO ) << endl;
    return 0;
}

int ccto ( int V[], int C[], int N, int K, int i, int c ) {
    if ( i == N )
        return 0;

    if ( c >= K ) {
        int doing = V[i] + ccto ( V, C, N, K, i + 1, c + C[i] );
        int skipping = ccto ( V, C, N, K, i + 1, 0 );
        int res = min ( doing, skipping );
        return res;
    }

    int res = V[i] + ccto ( V, C, N, K, i + 1,  c + C[i] ) ;
    return res;
}

int cct ( int V[], int C[], int N, int K, int i, int c, int MEMO[][21] ) {
    if ( i == N )
        return 0;

    if ( MEMO [ i ][ c ] != 0 )
        return MEMO [ i ][ c ];

    if ( c >= K ) {
        int doing = V[i] + cct ( V, C, N, K, i + 1, c + C[i] >= 20 ? 20 : c + C[i], MEMO );
        int skipping = cct ( V, C, N, K, i + 1, 0, MEMO );
        int res = min ( doing, skipping );

        MEMO [ i ][ c ] = res;
        return res;
    }

    int res = V[i] + cct ( V, C, N, K, i + 1, c + C[i] >= 20 ? 20 : c + C[i], MEMO ) ;
    MEMO [ i ][ c ] = res;
    return res;
}
