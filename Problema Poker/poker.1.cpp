#include <stdio.h>
#include <assert.h>
#include <algorithm>

typedef struct {
    int giornoTorneo;
    int oraInizio;
    int oraFine;
    int costoIscrizione;
    int premio;
} Tournament;

bool operator == (const Tournament, const Tournament);
bool isOverlapping ( Tournament, Tournament );
Tournament getHighestAward ( Tournament, Tournament );
bool byDateTime ( Tournament, Tournament );

int main ( void ) {
    // Input redirection
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    /** 
        Numero di tornei disponibili
    **/
    int tournamentsAmount;
    assert ( 1 == scanf( "%d", &tournamentsAmount ) );

    /**
        Denaro utilizzabile per l'iscrizione ai tornei
    **/
    int currentBalance;
    assert ( 1 == scanf( "%d", &currentBalance ) );

    /**
        Tornei disponibili ( VLA )
    **/
    Tournament availableTournaments [ tournamentsAmount ];
    for ( int i = 0; i < tournamentsAmount; i ++ ) {
        assert ( 5 == scanf( "%d%d%d%d%d", 
            &availableTournaments [ i ].giornoTorneo,
            &availableTournaments [ i ].oraInizio,
            &availableTournaments [ i ].oraFine,
            &availableTournaments [ i ].costoIscrizione,
            &availableTournaments [ i ].premio
        ) );  
    }

    /** 
        Ordiniamo i torneo per data e ora
    **/
    std::sort ( availableTournaments, availableTournaments + tournamentsAmount, byDateTime );
    
    /** 
        Torneo da svolgere 
    **/
    Tournament todo;
    for ( int i = 0; i < tournamentsAmount; i ++ ) {
        /**
            Verifichiamo i tornei con date incidenti
        **/
        
        // Se posso svolegere il seguente torneo
        if ( availableTournaments [ i ].costoIscrizione <= currentBalance ) {
            todo = availableTournaments [ i ];
            // Controllo se c'è di meglio nella stessa fascia oraria
            int j = i;

            // Finchè trovo collisioni tra il torneo scelto e i tornei successivi
            while ( isOverlapping ( todo, availableTournaments [ j + 1 ] ) && ( j + 1 ) < tournamentsAmount ) {
                // Se posso svolgere anche il torneo j + 1
                if ( availableTournaments [ j + 1 ].costoIscrizione <= currentBalance ) 
                    // Se trovo un torneo in collisione più proficuo
                    if ( !( todo == getHighestAward ( todo, availableTournaments [ j + 1 ] ) ) ) {
                        // Sostituico il torneo da svolgere
                        todo = getHighestAward ( todo, availableTournaments [ j + 1 ] );
                    }
                
                /**
                    Mando avanti il contatore per continuare a trovare di meglio
                    tra i tornei in collisione
                **/
                j ++;
            }

            /** 
                Una volta scelto il torneo migliore
                svolgo il torneo scelto.
            **/
            currentBalance = currentBalance + ( todo.premio - todo.costoIscrizione );

            /**
                Continuo a controllare da quel torneo in poi
            **/
        }
    }

    /**
        Restituisco ciò che ho guadagnato
    **/
    printf ( "%d\n", currentBalance );
    return 0;
}

bool isOverlapping ( Tournament t1, Tournament t2 ) {
    /**
        Verifica se tra 2 tornei c'è una collisione di orari e giornata
    **/
    if ( t1.giornoTorneo == t2.giornoTorneo )
        return t1.oraInizio < t2.oraFine && t2.oraInizio < t1.oraFine;
    return false;
}

Tournament getHighestAward ( Tournament t1, Tournament t2 ) {
    /** 
        Calcola tra i 2 tornei quello più proficuo 
    **/
    int awardT1 = t1.premio - t1.costoIscrizione;
    int awardT2 = t2.premio - t2.costoIscrizione;

    if ( awardT1 > awardT2 ) 
        return t1;
    return t2;
}

bool operator == ( const Tournament t1, const Tournament t2 ) {
    if ( t1.giornoTorneo        == t2.giornoTorneo      &&
         t1.oraInizio           == t2.oraInizio         && 
         t1.oraFine             == t2.oraFine           &&
         t1.costoIscrizione     == t2.costoIscrizione   &&
         t1.premio              == t2.premio ) 
        return true;
    return false;
}

bool byDateTime ( Tournament t1, Tournament t2 ) {
    if ( t1.giornoTorneo == t2.giornoTorneo ) {
        if ( t1.oraInizio == t2.oraInizio ) 
             return t1.oraFine < t2.oraFine;
        return t1.oraInizio < t2.oraInizio;
    }
    return t1.giornoTorneo < t2.giornoTorneo;
}