#include "Nota.h"

Nota::Nota() : id_elev(0), materie(""), valoare(0.0), data() {}

Nota::Nota(int id, std::string mat, double val, Data d) 
    : id_elev(id), materie(mat), valoare(val), data(d) {}

int Nota::getIdElev() const { return id_elev; }
std::string Nota::getMaterie() const { return materie; }
double Nota::getValoare() const { return valoare; }
Data Nota::getData() const { return data; }

void Nota::setIdElev(int id) { id_elev = id; }
void Nota::setMaterie(std::string mat) { materie = mat; }
void Nota::setValoare(double val) { valoare = val; }
void Nota::setData(Data d) { data = d; }

std::istream& operator>>(std::istream& in, Nota& n) {
    in >> n.id_elev >> n.materie >> n.valoare >> n.data;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Nota& n) {
    out << n.id_elev << " " << n.materie << " " << n.valoare << " " << n.data;
    return out;
}