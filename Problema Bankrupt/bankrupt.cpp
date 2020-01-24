/*
 * Problema ois_bankrupt
 * Il seguente algoritmo sfrutta il calcolo dell'area tramite determinante di una matrice.
 * 
 * Per eventuali approfondimenti tra la correlazione determinante-area:
 * http://www1.mat.uniroma1.it/people/pozio/images/AnalDue2011DeterminanteRiccardo.pdf
 
 * Per problemi di overflow si utilizzano interi long long
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

using namespace std;

// Numero punti
int N;

// Definiamo un punto (x, y) appartente al prodotto cartesiano RxR
typedef struct {
	 long long x;
	 long long y;
}Vertex;

int main ( void ) {
    // Redirect dell'input
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Lettura numero punti
    assert(1 == scanf("%d", &N));

    //VLA
    Vertex vertexes[N];
    
    // Lettura dei punti
    for (int i=0; i<N; i++){
    	assert(2 == scanf("%lld %lld", &vertexes[i].x, &vertexes[i].y));
	}
    
    // Area parziale parte da 0
    long long partial_area = 0;
    
    // Calcolo dell'area con somma per eccesso
    for(int i = 0; i < N - 1; i++)
    {
    	partial_area += vertexes[i].x * vertexes[i+1].y;
    	
	}
	// Dopo la moltiplicazione ho l'area parziale meno i primi 2
    // Moltiplico i primi 2
	partial_area += vertexes[N-1].x * vertexes[0].y;

    // area = area per eccesso ( area + eccesso )
	long long area = partial_area;
    
    // Calcoliamo l'eccesso
    partial_area = 0;
    for(int i = 0; i < N - 1; i++)
    {
    	partial_area += vertexes[i].y * vertexes[i+1].x;
	}
	
    // Dopo la moltiplicazione ho l'eccesso dell'area parziale meno i primi 2
    // Moltiplico i primi 2
	partial_area += vertexes[N - 1].y * vertexes[0].x;

    // Area con eccesso meno eccesso = area
    area = area - partial_area;
	
    // Valore assoluto dell'area
    area = abs(area);

    // Diviso 2
    area = ((long long)area) / (long long)2;
    
    // Stampa del risultato
    printf("%lld\n", area);
    return 0;
}