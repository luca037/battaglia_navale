// AUTORE FILE: Piai Luca

#include "../include/Battlefield.h"
#include "../include/NavalUnit.h"

Battlefield::Battlefield() {
    // inizializzo le matrici con caratteri vuoti
    // la colonna (x,0) e la riga (0,y) delle griglie vengono ignorate
    for (int i=0; i<13; i++)
        for (int j=0; j<13; j++) {
            attack_[i][j] = ' ';
            defence_[i][j] = ' ';
        }
}

void Battlefield::refresh_defence() {
    if (units_.empty()) return;

    // pulisco la griglia di difesa
    for (int i=0; i<13; i++)
        for (int j=0; j<13; j++)
            defence_[i][j] = ' ';

    // aggiorno i caratteri nella griglia
    for (auto it=units_.begin(); it!=units_.end(); ) {
        if (!(*it)->is_alive()) // se è affondata la rimuovo
            it = units_.erase(it);
        else { // per ogni posizione occupata dalla nave
            for (const Coordinate& p : (*it)->get_positions())
                if (p.is_marked()) // se la coordinata è stata colpita inserisco un carattere minuscolo
                    defence_[row(p.x())][p.y()] = std::tolower((*it)->type());
                else // altrimenti inserisco un carattere maiuscolo
                    defence_[row(p.x())][p.y()] = (*it)->type();
            ++it;
        }
    }
}

void Battlefield::clean_attack(char c) {
    for (int i=0; i<13; i++)
        for (int j=0; j<13; j++) {
            if (attack_[i][j] == c)
                attack_[i][j] = ' ';
        }
}

void Battlefield::mark_attack(const Coordinate& p, char c) {
    if (!is_inside(p)) return;
    attack_[row(p.x())][p.y()] = c;
}

bool Battlefield::move(NavalUnit* u, const Coordinate& p) {
    if (!u) return false;

    // calcolo la distanza della prua e della poppa dal cm corrente
    // necessario in quanto non sappiamo se la nave è orizzontale o verticale
    int bow_x = row(u->get_bow().x()) - row(u->get_cm().x());
    int bow_y = u->get_bow().y() - u->get_cm().y();
    int stern_x = row(u->get_stern().x()) - row(u->get_cm().x());
    int stern_y = u->get_stern().y() - u->get_cm().y();

    // controllo le lettere J K delle righe, è necessario solo
    // per la nave di supporto quando è posizionata in verticale
    // se il cm è alla riga 'L' => sposto la prua alla riga 'I'
    if (bow_x+p.x() == 'K') bow_x -= 2; 
    // se il cm è alla riga 'I' => sposto la poppa alla riga 'L'
    if (stern_y+p.y() == 'J') bow_x += 2;

    // creo le nuove coordinate della prua e della poppa
    Coordinate bow(bow_x+p.x(), bow_y+p.y());
    Coordinate stern(stern_x+p.x(), stern_y+p.y());

    // controllo che le posizioni della nave siano tutte intene alla griglia
    std::vector<Coordinate> pos = generate_inline_position(bow, stern);
    for (const Coordinate& c : pos)
        if (!is_inside(c)) return false;

    // controllo che tutte le posizioni non siano occupate da altre navi (escluso se stesso)
    for (const Coordinate& c : pos) {
        NavalUnit* owner = get_coordinate_owner(c);
        if (check_position(c) && owner!=u) return false;
    }

    // cambio le posizioni alla nave e aggiorno la griglia di difesa
    u->set_positions(pos);
    refresh_defence();

    return true;
}

void Battlefield::insert(NavalUnit* u) {
    if (!u) return;

    //inserisco nella lista
    units_.push_back(u);

    // disegno la nave nella griglia
    char t = u->type();
    for (Coordinate p : u->get_positions())
        defence_[row(p.x())][p.y()] = t;
}

bool Battlefield::check_position(const Coordinate& p) const {
    if (!is_inside(p)) return false;
    int x = row(p.x());
    int y = p.y();
    return defence_[x][y] != ' ';
}

bool Battlefield::check_position(const std::vector<Coordinate>& v) const {
    for (Coordinate p : v)
        if (check_position(p)) return true;
    return false;
}

bool Battlefield::is_inside(const Coordinate& p) const {
    char x = p.x();
    int y = p.y();
    // controllo sul range delle righe e colonne
    if (row(x) == -1) return false;
    if (y<1 || y>12) return false;
    return true;
}

bool Battlefield::is_inside(const std::vector<Coordinate>& v) const {
    for (Coordinate c : v)
        if (!is_inside(c)) return false;
    return true;
}

NavalUnit* Battlefield::choose_unit(const Coordinate& p) const {
    for (NavalUnit* u : units_)
        if (u->get_cm() == p) return u;
    return nullptr;
}

NavalUnit* Battlefield::get_coordinate_owner(const Coordinate& p) const {
    NavalUnit* owner = nullptr;
    // controllo tutte le posizioni di tutte le unità presenti
    for (NavalUnit* u : units_)
        for (const Coordinate& c : u->get_positions())
            if (c == p) {
                owner = u;
                break;
            }
    return owner;
}

int Battlefield::row(char c) const {
    switch (c) {
        case 'A': return 1; break;
        case 'B': return 2; break;
        case 'C': return 3; break;
        case 'D': return 4; break;
        case 'E': return 5; break;
        case 'F': return 6; break;
        case 'G': return 7; break;
        case 'H': return 8; break;
        case 'I': return 9; break;
        case 'L': return 10; break;
        case 'M': return 11; break;
        case 'N': return 12; break;
        default: return -1;
    }
}

// Operators
std::ostream& operator<<(std::ostream& os, const Battlefield& b) {
    os << "\t\tDefence\t\t\t\t\t\tAttack" << std::endl;

    char row  = 'A';
    for (int i = 1; i < 13; i++) {
        // salto la J e K
        if (row == 'J') row = 'L'; 

        // stampo la i-esima riga della prima matrice
        os << char(row) << " ";
        for (int j = 1; j < 13; j++) 
            os << b.defence_[i][j] << "  ";
        
        // aggiungo spazi
        os << "\t\t";

        // stampo la i-esima riga della seconda matrice
        os << char(row++) << " ";
        for (int j = 1; j < 13; j++) 
            os << b.attack_[i][j] << "  ";

        // vado a capo alla fine della riga
        os << std::endl; 
    }

    // stampa dei numeri sotto alle griglie
    os << "  1  2  3  4  5  6  7  8  9 10 11 12\t\t" 
       << "  1  2  3  4  5  6  7  8  9 10 11 12" << std::endl
       << "-------------------------------------------"
       << "------------------------------------------";

    return os;
}
