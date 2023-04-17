// AUTORE FILE: Baldo Enrico

#include "../include/Coordinate.h"

Coordinate::Coordinate(std::string s) {
    if (s.empty()) return;
    x_ = std::toupper(s.at(0));
    try {
        y_ = std::stoi(s.substr(1, 2));
    }
    catch (const std::invalid_argument& e) {
        x_ = '0';
        y_ = 0;
    }
    mark_ = 0;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& c) {
	return os << c.x() << c.y();
}

bool operator==(const Coordinate& a,const Coordinate& b) {
	return (a.x()==b.x() && a.y()==b.y());
}

bool operator!=(const Coordinate& a,const Coordinate& b) {
	return (a.x()!=b.x() || a.y()!=b.y());
}

// non vengono generate coordinate che si trovano sulle righe 'J' e/o 'K'
std::vector<Coordinate> generate_inline_position(const Coordinate& from, const Coordinate& to) {
	if (from == to)
        return { from };

    // se le posizioni passate sono diagonali
	if (from.x() != to.x() && from.y() != to.y()) return {};

    // posizioni in linea
	std::vector<Coordinate> inline_pos;

    // se from e to sono sulla stessa riga
	if (from.x() == to.x()) {
		if(from.y() > to.y()) // se from è più a destra di to
			for(int i = to.y(); i <= from.y(); i++)
                inline_pos.push_back(Coordinate(from.x(),i));
		else // from è più a sinistra di to
			for(int i = from.y(); i <= to.y(); i++)
                inline_pos.push_back(Coordinate(from.x(), i));
	}  

    // se from e to sono sulla stessa colonna
	if (from.y() == to.y()) {
		if (from.x() > to.x()) // se from è sopra to
			for (int i = to.x(); i <= from.x(); i++) {
                // salto le lettere J e K
                if(i == 'J' || i == 'K') i = 'L'; 
                inline_pos.push_back(Coordinate(i, from.y()));
            }
		else  // from è sotto to
			for (int i = from.x(); i <= to.x(); i++) {
                // salto le lettere J e K
                if(i == 'J' || i == 'K') i = 'L'; // salto le lettere J e K
                inline_pos.push_back(Coordinate(i, from.y()));
            }
	} 

	return inline_pos;
}
