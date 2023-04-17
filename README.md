# Battaglia Navale
Si tratta di un esame universitario. La descrizione completa e dettagliata del gioco relaizzato e delle specifiche richieste si trova nel pdf (TODO: inserire il pdf).

## Descrizione
Abbiamo ideato il progetto basandoci sulla connessione tra diverse classi e sottoclassi;
le classi "strutturali" hanno come obbiettivo creare gli oggetti fondamentali per il gioco, come i campi di battaglia, le navi e le loro rispettive coordinate. Ogni oggetto-nave si specializza in base al tipo nelle relative sottoclassi; i tipi di nave si differenziano in base alla loro struttura nel campo da gioco, alla loro "forma" e alle loro azioni.
    Per gestire i turni di gioco abbiamo creato una classe astratta (Player), da cui derivano due sottoclassi: Human e Computer, che prevedono l'istanziamento
e i turni dei rispettivi giocatore umano e giocatore gestito dal computer (basato su istanziamenti e azioni pseudo-casuali).
    In seguito abbiamo così deciso di dare il compito al main per la gestione della partita effettiva, tramite l'ausilio delle classi Human e Computer che gestiscono i vari oggetti (campi di battaglia e navi) per l'intero svolgimento della partita.
    Inoltre, sempre in Human e Computer, c'è la gestione in lettura del file di log. 

## Come abbiamo organizzato le classi
Poniamo qui un elenco sul funzionamento delle rispettive classi:
- Battlefield:  ogni oggetto battlefield prevede la creazione di due campi di battaglia per ogni giocatore, uno d'attacco e uno di difesa; 
la classe si occupa della modifica delle posizioni delle navi, delle loro azioni e dei comandi speciali nei vari campi d'attacco e di difesa (quindi in ogni partita verrano creati due oggetti battlefield).

- NavalUnit: è una classe astratta che estende tre sottoclassi che specificano le tipologie di navi (Battleship, Support vessel, submarine ); ogni sottoclasse erediterà action e in generale diverse caratteristiche per le data-member. Abbiamo pensato di ragionare ponendo come data member di battlefield una lista di puntatori di tipo NavalUnit che si specificano in base al tipo di nave e di conseguenza per il tipo di azione che potranno svolgere. Per questo motivo NalvaUnit e Battlefield sono fortemente legate.
- Battleship: specializzazione di NavalUnit.
- SupportVessel: specializzazione di NavalUnit.
- Submarine: specializzazione di NavalUnit.

- Coordinate: questa classe gestisce gli oggetti coordinata, importanti poichè sono data-member di ciascuna nave (memorizzate in std::vector di coordinate). Controlla anche le operazioni tra le varie coordinate utili nella gestione delle navi istanziate nel Battlefield. La classe fornisce una funzione che, dato un intervallo di coordinate (stessa riga o stessa colonna), restituisce un std::vector che contiene tutte le coordinate comprese nell'intervallo (estremi inclusi). Questa funzione è stata pensata per calcolare in maniera efficace le coordinate che si trovano tra prua e poppa.

- Player: è una classe classe astratta che estende due sottoclassi, human e computer. 
- Human: prevede l'istanziamento fatto da standard input, con gestione dei turni basata sulla volontà dell'utente;
- Computer: prevede l'istanziamento e gestione delle mosse basato su un algoritmo pseudo-randomico; (inoltre in ciascuna di queste due classi, ogni istanziamento e ogni mossa verrà riportata nel file di log).

- replay: la stampa della partita (che sia a video o su file) viene gestita interamente nel main. Non effettua controlli sulla validità delle mosse presenti nel file "log.txt".

- battaglia_navale: nel main c'è l'effettiva gestione della partita: vengono istanziati i campi di battaglia e le navi dei due Player; viene richiesto ai Player di inizializzare le proprie unità; vengono gestiti i turni. Abbiamo messo un limite di mosse pari a 2500, basandoci su una media delle durate delle partite tra computer e computer. (Queste spesso finiscono in stallo).

## Note aggiuntive
- Abbiamo deciso che la classe che rappresenta le coordinate accettasse anche gli indici di riga 'J' e 'K' per mantenerla più generica possibile. In conseguenza a ciò, tutte le funzioni che istanziano oggetti di tipo coordinata, fanno un conttrollo (se necessario) sull'indice di riga.

- Abbiamo deciso di disabilitare tutti i costruttori di copia e gli assegnamenti di copia (fatta eccezione per la classe Coordinate)

- Non abbiamo usato una data-member per verificare se una specifica nave sia orizzontale o verticale in quanto questa informazione era utile soltanto alla funzione "move" all'interno della classe Battlefield. Quindi abbiamo gestito la cosa tramite semplici operazioni algebriche tra gli indici delle coordinate di poppa e prua delle navi.

- I comandi speciali dell'utente devono essere scritti in maiuscolo altrimenti non vengono accettati

- Le navi da supporto e i sottomarini eseguono comunque l'azione se il target passato è il loro centro di massa corrente


## Problemi
- Nella stampa di replay su file le scritte "Defence" e "Attack" non risultano allineati
