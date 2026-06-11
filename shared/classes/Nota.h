#ifndef NOTA_H
#define NOTA_H

#include <iostream>
#include <string>
#include "Data.h"

class Nota {
private:
    int id_elev;
    std::string materie;
    double valoare;
    Data data; // relatie de compozitie

public:
    Nota();
    Nota(int id, std::string mat, double val, Data d);

    int getIdElev() const;
    std::string getMaterie() const;
    double getValoare() const;
    Data getData() const;

    void setIdElev(int id);
    void setMaterie(std::string mat);
    void setValoare(double val);
    void setData(Data d);

    friend std::istream& operator>>(std::istream& in, Nota& n);
    friend std::ostream& operator<<(std::ostream& out, const Nota& n);
};

#endif