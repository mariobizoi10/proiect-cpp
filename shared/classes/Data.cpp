#include "Data.h"

// constructor implicit
Data::Data() : zi(1), luna(1), an(2000) {}

// constructor cu parametri
Data::Data(int z, int l, int a) : zi(z), luna(l), an(a) {}

int Data::getZi() const { return zi; }
int Data::getLuna() const { return luna; }
int Data::getAn() const { return an; }

void Data::setZi(int z) { zi = z; }
void Data::setLuna(int l) { luna = l; }
void Data::setAn(int a) { an = a; }

std::istream& operator>>(std::istream& in, Data& d) {
    in >> d.zi >> d.luna >> d.an;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Data& d) {
    out << d.zi << " " << d.luna << " " << d.an;
    return out;
}

bool Data::operator==(const Data& other) const {
    return (zi == other.zi && luna == other.luna && an == other.an);
}