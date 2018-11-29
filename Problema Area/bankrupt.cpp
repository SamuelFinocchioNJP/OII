/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

using namespace std;

// constraints
#define MAXN 1000000

// input data
int N;

typedef struct {
	 int x;
	 int y;
}Vertex;



int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &N));
    //VLA
    Vertex vertexes[N];
    
    for (int i=0; i<N; i++){
    	assert(2 == scanf("%d %d", &vertexes[i].x, &vertexes[i].y));
	}
        
    long long partial_area = 0;
    
    for(int i = 0; i < N - 1; i++)
    {
    	partial_area += vertexes[i].x * vertexes[i+1].y;
    	
	}
	//Dopo la moltiplicazione ho l'area parziale meno i primi 2
	
	partial_area += vertexes[N-1].x * vertexes[0].y;
	long long area = partial_area;
	
    
    partial_area = 0;
    for(int i = 0; i < N - 1; i++)
    {
    	partial_area += vertexes[i].y * vertexes[i+1].x;
    	
	}
	
	partial_area += vertexes[N - 1].y * vertexes[0].x;
    area -= partial_area;
	
    area = abs(area);
    area = (long long)area / 2;
    
    printf("%lld\n", area);
    return 0;
}
