#ifndef DATA_H
#define DATA_H

#include <iostream>

class Data {
private:
    int zi;
    int luna;
    int an;

public:
    Data();
    Data(int z, int l, int a);

    int getZi() const;
    int getLuna() const;
    int getAn() const;

    void setZi(int z);
    void setLuna(int l);
    void setAn(int a);

    // supraincarcare operatori pentru citire si afisare
    friend std::istream& operator>>(std::istream& in, Data& d);
    friend std::ostream& operator<<(std::ostream& out, const Data& d);
    
    // operator pentru compararea a doua date
    bool operator==(const Data& other) const;
};

#endif