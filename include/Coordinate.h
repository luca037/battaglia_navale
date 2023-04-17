// AUTORE FILE: Baldo Enrico

#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include <vector>
#include <cctype>
#include <ostream>

// rappresenta le coordinate di un campo di battaglia generico
class Coordinate{
public:
	Coordinate() : x_{'0'}, y_{0}, mark_{0} { }
	Coordinate(std::string s); 
	Coordinate(char c, int n) : x_{c}, y_{n}, mark_{0} {
        if (!isupper(c)) x_ = std::toupper(c);
    }

	char x() const { return x_ ; }
	int y() const { return y_ ; }
    bool is_marked() const { return mark_; }

    void mark() { mark_ = 1; }
    void unmark() { mark_ = 0; }

private:
	char x_; // indice di riga
	int y_; // indice di colonna
    bool mark_; // coordinata colpita
};

std::ostream& operator<<(std::ostream& os, const Coordinate& c);
bool operator==(const Coordinate& a,const Coordinate& b);
bool operator!=(const Coordinate& a,const Coordinate& b);

// torna un vettore che contiene le posizioni che si trovano tra from e to
std::vector<Coordinate> generate_inline_position(const Coordinate& from, const Coordinate& to);

#endif
