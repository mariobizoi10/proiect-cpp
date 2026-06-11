#include "Elev.h"

Elev::Elev() : id_elev(0), nume(""), clasa(9) {}

Elev::Elev(int id, std::string n, int c) : id_elev(id), nume(n), clasa(c) {}

int Elev::getId() const { return id_elev; }
std::string Elev::getNume() const { return nume; }
int Elev::getClasa() const { return clasa; }

void Elev::setId(int id) { id_elev = id; }
void Elev::setNume(std::string n) { nume = n; }
void Elev::setClasa(int c) { clasa = c; }

std::istream& operator>>(std::istream& in, Elev& e) {
    // numele nu trebuie sa contina spatii pentru a fi citit corect
    in >> e.id_elev >> e.nume >> e.clasa;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Elev& e) {
    out << e.id_elev << " " << e.nume << " " << e.clasa;
    return out;
}

bool Elev::operator==(const Elev& other) const {
    return id_elev == other.id_elev;
}