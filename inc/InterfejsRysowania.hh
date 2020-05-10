#ifndef INTERFEJSRYSOWANIA_HH
#define INTERFEJSRYSOWANIA_HH

#include "Dr3D_gnuplot_api.hh"

class InterfejsRysowania
{
    protected:
    std::shared_ptr<drawNS::Draw3DAPI> rysownik;

    public:
    InterfejsRysowania(std::shared_ptr<drawNS::Draw3DAPI> nowy_rysownik) {};
};


#endif