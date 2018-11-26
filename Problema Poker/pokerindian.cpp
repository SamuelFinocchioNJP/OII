#include <stdio.h> 
#include <assert.h> 
#include <algorithm> 
#include <string.h>

#define NODEBUB

typedef struct {
    int giornoTorneo;
    int oraInizio;
    int oraFine;
    int costoIscrizione;
    int premio;
}
Tournament;

bool isOverlapping(Tournament, Tournament);
bool byDateTime(Tournament, Tournament);
bool canDo(Tournament, int);

int main(void) {
    // Input redirection
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    /**
    	Numero di tornei disponibili
    **/
    int tournamentsAmount;
    assert(1 == scanf("%d", & tournamentsAmount));

    /**
    	Denaro utilizzabile per l'iscrizione ai tornei
    **/
    int currentBalance;
    assert(1 == scanf("%d", & currentBalance));

    /**
    	Tornei disponibili ( VLA )
    **/
    Tournament availableTournaments[tournamentsAmount];
    for (int i = 0; i < tournamentsAmount; i++) {
        assert(5 == scanf("%d%d%d%d%d", &
            availableTournaments[i].giornoTorneo, &
            availableTournaments[i].oraInizio, &
            availableTournaments[i].oraFine, &
            availableTournaments[i].costoIscrizione, &
            availableTournaments[i].premio
        ));
    }

    /**
    	Ordiniamo i torneo per data e ora
    **/
    std::sort(availableTournaments, availableTournaments + tournamentsAmount, byDateTime);

    bool dayChanged = false;

    // Tournament earning array 
    int tournamentValues[tournamentsAmount];
    memset(tournamentValues, 0, sizeof(tournamentValues));

    int firstDailyTournament = 0;
    int currentDailyTurnament = 0;

    /**
     * Inizializziamo il guadagno del primo torneo
     */
    if (canDo(availableTournaments[0], currentBalance)) {
        tournamentValues[0] =
            currentBalance +
            availableTournaments[0].premio -
            availableTournaments[0].costoIscrizione;
    } else {
        tournamentValues[0] = -1;
    }

    int currentDay = availableTournaments[0].giornoTorneo;

    int currentBalanceBackup = currentBalance;
    /**
     *  Per ogni torneo:
     *       Se siamo nello stesso giorno:
     */
    for (int currentTournament = 1; currentTournament < tournamentsAmount; currentTournament++) {

        //controllo se il giorno è cambiato 
        if (availableTournaments[currentTournament].giornoTorneo !=
            currentDay) {
            dayChanged = true;
            currentDay = availableTournaments[currentTournament].giornoTorneo;
        }

        //controllo quanto ho guadagnato il giorno prima
        if (tournamentValues[currentTournament - 1] > currentBalance) {
            currentBalance = tournamentValues[currentTournament - 1];
        }

        //se il giorno è cambiato allora setto manualmente il value del primo torneo del giorno.
        if (dayChanged) {
            currentBalanceBackup = currentBalance;
            if (canDo(availableTournaments[currentTournament], currentBalance)) {
                tournamentValues[currentTournament] =
                    currentBalance +
                    availableTournaments[currentTournament].premio -
                    availableTournaments[currentTournament].costoIscrizione;
            } else {
                tournamentValues[currentTournament] = -1;
            }
            firstDailyTournament = currentTournament;
            dayChanged = false;
            currentDay = availableTournaments[currentTournament].giornoTorneo;
            continue;
        }

        //BACKTRACKING
        for (currentDailyTurnament = firstDailyTournament; currentDailyTurnament < currentTournament; currentDailyTurnament++) {

            if (canDo(availableTournaments[currentTournament], tournamentValues[currentDailyTurnament])) {
                if (!isOverlapping(availableTournaments[currentTournament], availableTournaments[currentDailyTurnament])) {

                    int hipValue = tournamentValues[currentDailyTurnament] +
                        availableTournaments[currentTournament].premio -
                        availableTournaments[currentTournament].costoIscrizione;

                    if (hipValue > tournamentValues[currentTournament])
                        tournamentValues[currentTournament] = hipValue;
                } else {
                    if (canDo(availableTournaments[currentTournament], currentBalanceBackup)) {
                        int hipValue = currentBalanceBackup +
                            availableTournaments[currentTournament].premio -
                            availableTournaments[currentTournament].costoIscrizione;
                        if (hipValue >= tournamentValues[currentTournament])
                            tournamentValues[currentTournament] = hipValue;
                    } else {
                        if (tournamentValues[currentTournament] == 0)
                            tournamentValues[currentTournament] = -1;
                    }
                }
            } else {
                if (canDo(availableTournaments[currentTournament], currentBalanceBackup)) {
                    int hipValue = currentBalanceBackup +
                        availableTournaments[currentTournament].premio -
                        availableTournaments[currentTournament].costoIscrizione;
                    if (hipValue >= tournamentValues[currentTournament])
                        tournamentValues[currentTournament] = hipValue;
                } else {
                    if (tournamentValues[currentTournament] == 0)
                        tournamentValues[currentTournament] = -1;
                }
            }

        }
    }

    //Last Item
    if (tournamentValues[tournamentsAmount - 1] > currentBalance) {
        currentBalance = tournamentValues[tournamentsAmount - 1];
    }
    /**
    	Restituisco ciò che ho guadagnato
    **/
    printf("%d\n", currentBalance);
    return 0;
}

bool isOverlapping(Tournament t1, Tournament t2) {
    /**
    	Verifica se tra 2 tornei c'è una collisione di orari e giornata
    **/
    if (t1.giornoTorneo == t2.giornoTorneo)
        return t1.oraInizio < t2.oraFine && t2.oraInizio < t1.oraFine;
    return false;
}

bool canDo(Tournament t1, int currentBalance) {
    return t1.costoIscrizione <= currentBalance;
}

bool byDateTime(Tournament t1, Tournament t2) {
    if (t1.giornoTorneo == t2.giornoTorneo) {
        if (t1.oraFine == t2.oraFine)
            return t1.oraInizio < t2.oraInizio;
        return t1.oraFine < t2.oraFine;
    }
    return t1.giornoTorneo < t2.giornoTorneo;
}
