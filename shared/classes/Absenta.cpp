#include "Absenta.h"

Absenta::Absenta() : id_elev(0), materie(""), data(), motivata(false) {}

Absenta::Absenta(int id, std::string mat, Data d, bool mot) 
    : id_elev(id), materie(mat), data(d), motivata(mot) {}

int Absenta::getIdElev() const { return id_elev; }
std::string Absenta::getMaterie() const { return materie; }
Data Absenta::getData() const { return data; }
bool Absenta::isMotivata() const { return motivata; }

void Absenta::setIdElev(int id) { id_elev = id; }
void Absenta::setMaterie(std::string mat) { materie = mat; }
void Absenta::setData(Data d) { data = d; }
void Absenta::setMotivata(bool mot) { motivata = mot; }

std::istream& operator>>(std::istream& in, Absenta& a) {
    int mot;
    in >> a.id_elev >> a.materie >> a.data >> mot;
    a.motivata = (mot == 1);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Absenta& a) {
    out << a.id_elev << " " << a.materie << " " << a.data << " " << (a.motivata ? 1 : 0);
    return out;
}