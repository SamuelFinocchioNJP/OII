
#include <stdio.h>
#include <assert.h>
#include <algorithm>

#define DEBUG

int main(void) {
	// Input redirection
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	/**
		Numero di malls disponibili
	**/
	int mallsAmount;
	assert(1 == scanf("%d", &mallsAmount));

	/**
		Lunghezza della strada
	**/
	int maxLength;
	assert(1 == scanf("%d", &maxLength));

	/**
		Tornei disponibili ( VLA )
	**/
	int malls [ mallsAmount ];

	for (int i = 0; i < mallsAmount ; i++) {
		assert(1 == scanf("%d", &malls[i] ));
	}


    /**
		Ordiniamo i supermercati
	**/

	std::sort( malls, malls + mallsAmount );

    int maxDistance = malls [0];
    int bestPosition = 0;
    
    if ( mallsAmount == 1 ) {
        if ( malls [ 0 ] > ( maxLength - malls[0] ) ) 
            printf ( "%d", 0 );
        else 
            printf ( "%d", maxLength );
        
        return 0;
    }

    for ( int i = 0; i < mallsAmount - 1; i++ ) {
        int currentDistance = malls [ i + 1 ] - malls [ i ];
        if ( currentDistance > maxDistance ) {
            maxDistance = currentDistance;
            bestPosition = ( malls [ i ] + malls [ i + 1 ] ) / 2;
        }
    }

    // printf ( "%d\n", maxLength - malls [ mallsAmount - 1 ] );
    // printf( "MAXD %d\n", maxDistance );
    if ( ( maxLength - malls [ mallsAmount - 1 ] ) > ( maxDistance / 2 ) ) 
        bestPosition = maxLength;
    
    if ( malls [ 0 ] > ( maxDistance / 2 ) )
        bestPosition = 0;

    printf ("%d", bestPosition );
    return 0;
}