/**
    Training OIS
    Greedy Santa ( christmas )
    https://training.olinfo.it/#/task/ois_christmas

    Author: Samuel Finocchio
    Date: 23/12/2019
    Solution 1: [ 19:36, 19:50 ] ( 50/100 ) Timeout
    Solution 2: [ 21:17, 21:22 ] ( 100/100 ) Added memoization
    Solution 3: [ 22:01, 22:05 ] ( 100/100 ) Added fast but unelegant memoization
**/

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

int solve ( vector < int > gifts, int index, int expense, int budget );

int MEMO [ 40001 ][ 1000 ] = { { 0 } };
int main ( void )
{
    int giftsAmount, budget;
    cin >> giftsAmount >> budget;

    vector <int> gifts ( giftsAmount );

    int maximumExpense = 0;
    for ( int i = 0; i < giftsAmount; i++ ) {
        cin >> gifts [ i ];
        maximumExpense = maximumExpense + gifts [ i ];
    }

    if ( maximumExpense <= budget )
        cout << maximumExpense;
    else {
        cout << solve ( gifts, 0, 0, budget);
    }

    return 0;
}

int solve ( vector < int > gifts, int index, int expense, int budget ) {

    if ( MEMO [ expense ][ index ] != 0 )
        return MEMO [ expense ][ index ];

    if ( expense >= budget ) {
        MEMO [ expense ][ index ] = expense;
        return expense;
    }

    if ( index == gifts.size() ) {
        MEMO [ expense ][ index ] = numeric_limits<int>::max();
        return numeric_limits<int>::max();
    }

    int result = min (
        solve ( gifts, index + 1, expense + gifts [ index ], budget ),
        solve ( gifts, index + 1, expense, budget )
    );

    MEMO [ expense ][ index ] = result;
    return result;
}
