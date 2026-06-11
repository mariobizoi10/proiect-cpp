#ifndef ABSENTA_H
#define ABSENTA_H

#include <iostream>
#include <string>
#include "Data.h"

class Absenta {
private:
    int id_elev;
    std::string materie;
    Data data;
    bool motivata;

public:
    Absenta();
    Absenta(int id, std::string mat, Data d, bool mot);

    int getIdElev() const;
    std::string getMaterie() const;
    Data getData() const;
    bool isMotivata() const;

    void setIdElev(int id);
    void setMaterie(std::string mat);
    void setData(Data d);
    void setMotivata(bool mot);

    friend std::istream& operator>>(std::istream& in, Absenta& a);
    friend std::ostream& operator<<(std::ostream& out, const Absenta& a);
};

#endif