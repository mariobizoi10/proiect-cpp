#ifndef ELEV_H
#define ELEV_H

#include <iostream>
#include <string>

class Elev {
private:
    int id_elev;
    std::string nume;
    int clasa;

public:
    Elev();
    Elev(int id, std::string n, int c);

    int getId() const;
    std::string getNume() const;
    int getClasa() const;

    void setId(int id);
    void setNume(std::string n);
    void setClasa(int c);

    friend std::istream& operator>>(std::istream& in, Elev& e);
    friend std::ostream& operator<<(std::ostream& out, const Elev& e);
    
    bool operator==(const Elev& other) const;
};

#endif