#include "CerereMotivare.h"

CerereMotivare::CerereMotivare() : id_elev(0), materie(""), data() {}

CerereMotivare::CerereMotivare(int id, std::string mat, Data d) 
    : id_elev(id), materie(mat), data(d) {}

int CerereMotivare::getIdElev() const { return id_elev; }
std::string CerereMotivare::getMaterie() const { return materie; }
Data CerereMotivare::getData() const { return data; }

void CerereMotivare::setIdElev(int id) { id_elev = id; }
void CerereMotivare::setMaterie(std::string mat) { materie = mat; }
void CerereMotivare::setData(Data d) { data = d; }

std::istream& operator>>(std::istream& in, CerereMotivare& c) {
    in >> c.id_elev >> c.materie >> c.data;
    return in;
}

std::ostream& operator<<(std::ostream& out, const CerereMotivare& c) {
    out << c.id_elev << " " << c.materie << " " << c.data;
    return out;
}