// AUTORE FILE: Baldo Enrico

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "../include/Battlefield.h"
#include "../include/SupportVessel.h"
#include "../include/Coordinate.h"
#include "../include/BattleShip.h"
#include "../include/Submarine.h"
#include "../include/Computer.h"

using namespace std;

void init_player_units(Battlefield& b, NavalUnit* u, int size, ifstream& in) {
    string bow{""};
    string stern{""};
    for (int i=0; i<size || in.eof(); i++) {
        // prelevo prua e poppa
        in >> bow;
        in >> stern;

        // creo il vettore delle posizioni della nave
        vector<Coordinate> pos = generate_inline_position(Coordinate{bow}, Coordinate{stern});

        // inerisco l'unità nel campo di battaglia
        u[i].set_positions(pos);
        b.insert(&u[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc ==1 || argc > 4) return 0;

    // controllo sugli argomenti passati
    string check{argv[1]};
    if (argc==4 && check!="f") return 0;
    if (argc==3 && check!="v") return 0;

    // apro i file
    ifstream in{argv[2]};
    ofstream out;
    if (check == "f") out.open(argv[3]);
    else system("clear");

    // campi dei due giocatori
    Battlefield batt_p1{};
    Battlefield batt_p2{};

    // navi player 1 
    BattleShip bs_p1[3];
    SupportVessel sup_p1[3];
    Submarine sub_p1[2];

    init_player_units(batt_p1, bs_p1, 3, in);
    init_player_units(batt_p1, sup_p1, 3, in);
    init_player_units(batt_p1, sub_p1, 2, in);

    // navi player 2 
    BattleShip bs_p2[3];
    SupportVessel sup_p2[3];
    Submarine sub_p2[2];

    init_player_units(batt_p2, bs_p2, 3, in);
    init_player_units(batt_p2, sup_p2, 3, in);
    init_player_units(batt_p2, sub_p2, 2, in);

    // mossa del giocatore
    string cm{""};
    string target{""};

    int turn_count = 1;
    while (in >> cm >> target) {
        if (turn_count % 2) { // turno player1
            NavalUnit* unit = batt_p1.choose_unit(cm);
            unit->action(batt_p1, batt_p2, target);

            if (out.is_open()) { // se ho inserito il file di out
                out << "TURNO: " << turn_count << endl
                    << "CAMPO GIOCATORE 1:" << endl
                    << " -> CM SELEZIONATO: " << cm  << " TARGET: " << target << endl 
                    << " -> TIPO NAVE: " << unit->type() << endl
                    << batt_p1 << endl;
            }
            else { // altrimenti faccio la stampa a viedo
                cout << "TURNO: " << turn_count << endl
                     << "CAMPO GIOCATORE 1:" << endl
                     << " -> CM SELEZIONATO: " << cm  << " TARGET: " << target << endl 
                     << " -> TIPO NAVE: " << unit->type() << endl
                     << batt_p1 << endl;
                // pulisco il terminale
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
            }
        }
        else { // turno player2
            NavalUnit* unit = batt_p2.choose_unit(cm);
            unit->action(batt_p2, batt_p1, target);

            if (out.is_open()) { // se ho inserito il file di out
                out << "TURNO: " << turn_count << endl
                    << "CAMPO GIOCATORE 2:" << endl
                    << " -> CM SELEZIONATO: " << cm  << " TARGET: " << target << endl 
                    << " -> TIPO NAVE: " << unit->type() << endl
                    << batt_p2 << endl;
            }
            else { // altrimenti faccio la stampa a viedo
                cout << "TURNO: " << turn_count << endl
                     << "CAMPO GIOCATORE 2:" << endl
                     << " -> CM SELEZIONATO: " << cm  << " TARGET: " << target << endl 
                     << " -> TIPO NAVE: " << unit->type() << endl
                     << batt_p2 << endl;
                // pulisco il terminale
                this_thread::sleep_for(std::chrono::seconds(2));
                system("clear");
            }
        }
        turn_count++;
    }

    // chiudo i file
    in.close();
    if (out.is_open()) {
        cout << "Replay partita salvato nel file di out specificato" << endl;
        out.close();
    }

    return 0;
}
