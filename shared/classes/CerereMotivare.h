#ifndef CERERE_MOTIVARE_H
#define CERERE_MOTIVARE_H

#include <iostream>
#include <string>
#include "Data.h"

class CerereMotivare {
private:
    int id_elev;
    std::string materie;
    Data data;

public:
    CerereMotivare();
    CerereMotivare(int id, std::string mat, Data d);

    int getIdElev() const;
    std::string getMaterie() const;
    Data getData() const;

    void setIdElev(int id);
    void setMaterie(std::string mat);
    void setData(Data d);

    friend std::istream& operator>>(std::istream& in, CerereMotivare& c);
    friend std::ostream& operator<<(std::ostream& out, const CerereMotivare& c);
};

#endif