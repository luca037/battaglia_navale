// AUTORE FILE: Baldo Enrico

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "../include/Battlefield.h"
#include "../include/SupportVessel.h"
#include "../include/Coordinate.h"
#include "../include/BattleShip.h"
#include "../include/Submarine.h"
#include "../include/Human.h"
#include "../include/Computer.h"

using namespace std;

int main(int argc, char* argv[]) {
    // controllo sugli argomenti passati da riga di comando
    if(argc == 1 || argc > 3) return 0; 

    // tipo di partita
    string game = argv[1];
    if (game!="pc" && game!="cc") return 0;

    // apro il file di log
    ofstream log{"../log.txt"};

    // numero massimo turni
    constexpr int kMaxTurns = 2500;

    // setto il seed per rand
    srand(time(0));

    // dichiarazione barche Player1
    BattleShip bs_p1[3];
    SupportVessel sup_p1[3];
    Submarine sub_p1[2];

    // dichiarazione barche Player2 
    BattleShip bs_p2[3];
    SupportVessel sup_p2[3];
    Submarine sub_p2[2];

    // inizzializzazione Battlefield
    Battlefield batt_p1{}; // di Player1
    Battlefield batt_p2{}; // di Player2

    // partita Player vs Computer
    if (game == "pc") {
        system("clear");
        cout <<"Hai selezionato di giocare contro il computer" << endl; 

        // inizzializzo i due giocatori
        Human player1{};
        Computer player2{};

        // inizzializzazione barche Human
        for (int i=0; i<3; i++)
            player1.init_unit(batt_p1, &bs_p1[i], log);

        for (int i=0; i<3; i++)
            player1.init_unit(batt_p1, &sup_p1[i], log);

        for (int i=0; i<2; i++)
            player1.init_unit(batt_p1, &sub_p1[i], log);

        // inizizalizzazione barche Computer
        for (int i=0; i<3; i++)
            player2.init_unit(batt_p2, &bs_p2[i], log);

        for (int i=0; i<3; i++)
            player2.init_unit(batt_p2, &sup_p2[i], log);

        for (int i=0; i<2; i++)
            player2.init_unit(batt_p2, &sub_p2[i], log);

        // introduzione partita
        system("clear");
        cout << "\n\n\t\t\tInizia la Partita\n\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
        cout << "\n\n\t\t\tInizia la Partita.\n\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
        cout << "\n\n\t\t\tInizia la Partita..\n\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
        cout << "\n\n\t\t\tInizia la Partita...\n\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        this_thread::sleep_for(chrono::seconds(1));
        system("clear");

        // gestine turni partita
        int turn_count = 1;
        while ((turn_count != kMaxTurns) && (!batt_p1.is_empty() && !batt_p2.is_empty())) {
            if (turn_count % 2) { // turno Player
                cout << "TURNO: " << turn_count << endl;
                turn_count += player1.turn(batt_p1, batt_p2, log);
                system("clear");
            }
            else // turno Computer
                turn_count += player2.turn(batt_p2, batt_p1, log);
        }
    }

    // partita Computer vs Computer
    else if (game == "cc") {
        cout << "Hai selezionato di simulare una partita computer vs computer" <<endl;

        // inizzializzo i due giocatori
        Computer player1{};
        Computer player2{};

        // inizzializzazione barche Human
        for (int i=0; i<3; i++)
            player1.init_unit(batt_p1, &bs_p1[i], log);

        for (int i=0; i<3; i++)
            player1.init_unit(batt_p1, &sup_p1[i], log);

        for (int i=0; i<2; i++)
            player1.init_unit(batt_p1, &sub_p1[i], log);

        //Inizizalizzazione barche Computer
        for (int i=0; i<3; i++)
            player2.init_unit(batt_p2, &bs_p2[i], log);

        for (int i=0; i<3; i++)
            player2.init_unit(batt_p2, &sup_p2[i], log);

        for (int i=0; i<2; i++)
            player2.init_unit(batt_p2, &sub_p2[i], log);

        // turni partita
        int turn_count = 1;
        while ((turn_count != kMaxTurns) && (!batt_p1.is_empty() && !batt_p2.is_empty())) {
            if (turn_count % 2) // turno computer1
                turn_count += player1.turn(batt_p1, batt_p2, log);
            else // turno computer2
                turn_count += player2.turn(batt_p2, batt_p1, log);
        }
    }

    // messaggio conclusivo partita
    if (!batt_p1.is_empty() && !batt_p2.is_empty())
        cout << "Partita finita in stallo" << endl;
    else if (batt_p2.is_empty())
        cout << "Player1 ha vinto!" << endl;
    else if (batt_p1.is_empty())
        cout << "Player2 ha vinto!" << endl;

    // chiudo il file di log
    log.close();

    return 0;
}
