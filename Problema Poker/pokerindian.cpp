#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <string.h>

#define DEBUB

typedef struct {
	int giornoTorneo;
	int oraInizio;
	int oraFine;
	int costoIscrizione;
	int premio;
} Tournament;

bool operator == (const Tournament, const Tournament);
bool isOverlapping(Tournament, Tournament);
Tournament getHighestAward(Tournament, Tournament);
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
	assert(1 == scanf("%d", &tournamentsAmount));

	/**
		Denaro utilizzabile per l'iscrizione ai tornei
	**/
	int currentBalance;
	assert(1 == scanf("%d", &currentBalance));

	/**
		Tornei disponibili ( VLA )
	**/
	Tournament availableTournaments[tournamentsAmount];
	for (int i = 0; i < tournamentsAmount; i++) {
		assert(5 == scanf("%d%d%d%d%d",
			&availableTournaments[i].giornoTorneo,
			&availableTournaments[i].oraInizio,
			&availableTournaments[i].oraFine,
			&availableTournaments[i].costoIscrizione,
			&availableTournaments[i].premio
		));
	}

	/**
		Ordiniamo i torneo per data e ora
	**/
	std::sort(availableTournaments, availableTournaments + tournamentsAmount, byDateTime);

#ifdef DEBUB
	printf("Sorted array: \n");
	for (int i = 0; i < tournamentsAmount; i++)
		printf("%d %d %d %d %d\n",
			availableTournaments[i].giornoTorneo,
			availableTournaments[i].oraInizio,
			availableTournaments[i].oraFine,
			availableTournaments[i].costoIscrizione,
			availableTournaments[i].premio
		);
	printf("\n");
#endif

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
			currentBalance
			+ availableTournaments[0].premio
			- availableTournaments[0].costoIscrizione;
	}
	else {
		tournamentValues[0] = -1;
	}

	int currentDay = availableTournaments[0].giornoTorneo;

	int currentBalanceBackup = currentBalance;
	/**
	*  Per ogni torneo:
	*       Se siamo nello stesso giorno:
	*/
	for (int currentTournament = 1; currentTournament < tournamentsAmount; currentTournament++) {
#ifdef DEBUB
		printf("FORING%d [ %d ]\n", currentBalance, currentTournament);
#endif
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
					currentBalance
					+ availableTournaments[currentTournament].premio
					- availableTournaments[currentTournament].costoIscrizione;
			}
			else {
				tournamentValues[currentTournament] = -1;
			}
			firstDailyTournament = currentTournament;
			/** TODO remove continue **/
			dayChanged = false;
			currentDay = availableTournaments[currentTournament].giornoTorneo;
			continue;
		}

		//BACKTRACKING
		for (currentDailyTurnament = firstDailyTournament;
			currentDailyTurnament < currentTournament;
			currentDailyTurnament++) {

#ifdef DEBUB
			for (int i = 0; i < tournamentsAmount; i++)
				printf("FOR IN: %d [%d]\n", tournamentValues[i], i);
#endif    
			//se non si overlappano allora controllo quanto mi fa guadagnare questa catena se mi fa guadagnare di più l'i-esima catena si aggiorna di valore
			if (!isOverlapping(availableTournaments[currentTournament], availableTournaments[currentDailyTurnament])) {

				if (tournamentValues[currentDailyTurnament] != -1) {

#ifdef DEBUB
					for (int i = 0; i < tournamentsAmount; i++)
						printf("BACKTRACK: %d [%d]\n", tournamentValues[i], i);
#endif

					int hipValue = tournamentValues[currentDailyTurnament]
						+ availableTournaments[currentTournament].premio
						- availableTournaments[currentTournament].costoIscrizione;

					if (hipValue > tournamentValues[currentTournament])
						tournamentValues[currentTournament] = hipValue;
				}
				else {
					if (canDo(availableTournaments[currentTournament], currentBalanceBackup)) {
						int hipValue = 	currentBalanceBackup
						+ availableTournaments[currentTournament].premio
						- availableTournaments[currentTournament].costoIscrizione;
						if(hipValue >= tournamentValues[ currentTournament ])
						tournamentValues[ currentTournament ] = hipValue;
					}
					else {
						tournamentValues[currentTournament] = -1;
					}
				}
			}
			else {
				if (canDo(availableTournaments[currentTournament], currentBalanceBackup)) {
					int hipValue = 	currentBalanceBackup
						+ availableTournaments[currentTournament].premio
						- availableTournaments[currentTournament].costoIscrizione;
					if(hipValue >= tournamentValues[ currentTournament ])
						tournamentValues[ currentTournament ] = hipValue;					
				}
				else {
					tournamentValues[currentTournament] = -1;
				}
			}
		}
	}

#ifdef DEBUB
	for (int i = 0; i < tournamentsAmount; i++)
		printf("tuna%d [%d]\n", tournamentValues[i], i);
#endif

	// Last item
#ifdef DEBUB
	printf("ARRAY VALUES\n");
	for (int i = 0; i < tournamentsAmount; i++)
		printf("%d [%d]| ", tournamentValues[i], i);
#endif

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

Tournament getHighestAward(Tournament t1, Tournament t2) {
	/**
		Calcola tra i 2 tornei quello più proficuo
	**/
	int awardT1 = t1.premio - t1.costoIscrizione;
	int awardT2 = t2.premio - t2.costoIscrizione;

	if (awardT1 > awardT2)
		return t1;
	return t2;
}

bool operator == (const Tournament t1, const Tournament t2) {
	if (t1.giornoTorneo == t2.giornoTorneo      &&
		t1.oraInizio == t2.oraInizio         &&
		t1.oraFine == t2.oraFine           &&
		t1.costoIscrizione == t2.costoIscrizione   &&
		t1.premio == t2.premio)
		return true;
	return false;
}

bool byDateTime(Tournament t1, Tournament t2) {
	if (t1.giornoTorneo == t2.giornoTorneo) {
		if (t1.oraFine == t2.oraFine)
			return t1.oraInizio < t2.oraInizio;
		return t1.oraFine < t2.oraFine;
	}
	return t1.giornoTorneo < t2.giornoTorneo;
}
