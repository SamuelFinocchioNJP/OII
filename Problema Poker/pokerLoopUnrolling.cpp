/**
    1] Ordinamento 
    2] Programmazione dinamica
    3] Backtracking in tournamentValues [ i ] dove i Ã¨ l'orario il migliore del giorno
**/

#include <stdio.h>
#include <assert.h>
#include <algorithm>

#define MAXIMUM_HOURS 1001



struct Tournament {
    int day;
    int startingTime;
    int endingTime;
    int buyIn;
    int prize;
};

bool canDo(Tournament t1, int currentBalance) {
    return t1.buyIn <= currentBalance;
}

bool isOverlapping(Tournament t1, Tournament t2) {
    /**
    	Verifica se tra 2 tornei c'è una collisione di orari e giornata
    **/
    if (t1.day == t2.day)
        return t1.startingTime < t2.endingTime && t2.startingTime < t1.endingTime;
    return false;
}

bool byDateTime ( Tournament t1, Tournament t2 ) {
	if (t1.day == t2.day) {
		if (t1.endingTime == t2.endingTime)
			return t1.startingTime < t2.startingTime;
		return t1.endingTime < t2.endingTime;
	}
	return t1.day < t2.day;
}

// input data
/**
    Array giornaliero
**/
int tournamentValues [ MAXIMUM_HOURS ]; 

/**
    Array complessivo
**/
int num [ MAXIMUM_HOURS ];

int main ( void ) {
    int tournamentsAmount;
    int balance;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    assert ( 1 == scanf ( "%d", &tournamentsAmount ) );
    assert ( 1 == scanf ( "%d", &balance) );

    Tournament tournaments [ tournamentsAmount ];

    for( int i = 0; i < tournamentsAmount; i++ ) {
        assert(5 == scanf("%d%d%d%d%d", 
            &tournaments [ i ].day, 
            &tournaments [ i ].startingTime, 
            &tournaments [ i ].endingTime, 
            &tournaments [ i ].buyIn, 
            &tournaments [ i ].prize ));
        
        tournaments [ i ].prize = tournaments [ i ].prize - tournaments [ i ].buyIn;
    }

    std::sort ( tournaments, tournaments + tournamentsAmount, byDateTime );

    int day = 0;
    int backtrackingTournament = 0;
    tournamentValues [ 0 ] = balance;

    for ( int currentTournament = 0; currentTournament < tournamentsAmount; currentTournament++ ) {
        // Backtracking fino ad oggi
        if ( tournaments [ currentTournament ].day > day ) {
            while ( backtrackingTournament < MAXIMUM_HOURS ) {
                if (tournamentValues [ backtrackingTournament + 1 ] < tournamentValues [ backtrackingTournament ] ) {
                    tournamentValues [ backtrackingTournament + 1 ] = tournamentValues [ backtrackingTournament ];
                    num [ backtrackingTournament + 1 ] = num [ backtrackingTournament ];
                }
                backtrackingTournament ++;
            }

            for ( int i = 0; i < MAXIMUM_HOURS; i++ ) {
                tournamentValues [ i ] = tournamentValues [ MAXIMUM_HOURS - 1 ];
                num [ i ] = num [ MAXIMUM_HOURS - 1 ];
            }

            day = tournaments [ currentTournament ].day;
            backtrackingTournament = tournaments [ currentTournament ].startingTime;
        } else {
            while ( backtrackingTournament < tournaments [ currentTournament ].startingTime ) {
                if ( tournamentValues [ backtrackingTournament + 1 ] < tournamentValues [ backtrackingTournament ] ) {
                    tournamentValues [ backtrackingTournament + 1 ] = tournamentValues [ backtrackingTournament ];
                    num [ backtrackingTournament + 1 ] = num [ backtrackingTournament ];
                } 
                backtrackingTournament ++;
            }
        }
        
        /**
            Se posso svolgere il problema AND
            Ho un guadagno superiore
        **/
        if ( tournamentValues [ backtrackingTournament ] >= tournaments [ currentTournament ].buyIn 
            && tournamentValues [ tournaments [ currentTournament ].endingTime ] < tournamentValues [ backtrackingTournament ] + tournaments [ currentTournament ].prize 
			&& !isOverlapping(tournaments[currentTournament],tournaments[backtrackingTournament]) ) {
                tournamentValues [ tournaments [ currentTournament ].endingTime ] = tournamentValues [ backtrackingTournament ] + tournaments [ currentTournament ].prize
			
                num [  tournaments [ currentTournament ].endingTime ] = num [ backtrackingTournament ] + 1; // update tournamentValues of the end
        }
    }

    /**
        Profitto massimo
    **/
    int max = tournamentValues [ 0 ];

    for ( int i = 0; i < MAXIMUM_HOURS; i++ ) 
        if ( tournamentValues [ i ] > max )
            max = tournamentValues [ i ];

    printf("%d\n", max );

    return 0;
}
