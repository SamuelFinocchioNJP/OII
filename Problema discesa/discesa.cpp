/***
    OII Training 2020 - UnivAQ
    Author: Samuel Finocchio
    Date: 24/01/2020
    Name: discesa
    Link: https://training.olinfo.it/#/task/discesa
    Description:
    Solved using simple recursion
**/
#include <iostream>
#include <vector>

using namespace std;

int solve ( const vector<vector<int>> &piramid );
int solve ( const vector<vector<int>> &piramid, int i, int j );

int main( void )
{
    /// IO From file
    freopen ("input.txt","r", stdin );
    freopen ("output.txt","w", stdout);

    int N;
    cin >> N;

    /// Matrix initialized with -1 everywhere
    vector <vector<int>> piramid ( N, vector<int>( N, -1 ) );

    /// Reading input
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j <= i; j++ )
            cin >> piramid [ i ][ j ];

    /// Calling helper function
    cout << solve ( piramid );
    return 0;
}

int solve ( const vector<vector<int>> &piramid ) {
    return solve ( piramid, 0, 0 );
}

int solve ( const vector<vector<int>> &piramid, int i, int j ) {
    /// Exiting on outofbound or on -1
    if ( i < 0 || i >= piramid.size() )
        return 0;
    if ( j < 0 || j >= piramid.size() )
        return 0;
    if ( piramid [i][j] == -1 )
        return 0;

    /// Returning the maximum between left and right side
    int res = piramid[i][j] +
        max (
            solve ( piramid, i + 1, j    ),
            solve ( piramid, i + 1, j + 1)
        );

    /// Uncomment to watch recursion
    // cout << "( " << i << ", " << j << " ) -> " << res << endl;
    return res;
}
