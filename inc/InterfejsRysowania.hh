#ifndef INTERFEJSRYSOWANIA_HH
#define INTERFEJSRYSOWANIA_HH

#include "Dr3D_gnuplot_api.hh"

class InterfejsRysowania
{
    protected:
    /*!
    * \brief Pole przechowuje wskażnik na gunplot
    */
    std::shared_ptr<drawNS::Draw3DAPI> rysownik;

    /*!
    * \brief Pole przechowuje indeksy rysunków gunplotowych
    */
    int index[6];

    public:
    /*!
    * \brief Konstruktor bezparametryczny 
    */
    InterfejsRysowania() {};

    /*!
    * \brief Konstruktor parametryczny
    * \param nowy_rysownik - wskaźnik na gunplot
    */
    InterfejsRysowania(std::shared_ptr<drawNS::Draw3DAPI> nowy_rysownik) {};

    /*!
    * \brief Funkcja która rysuje kształt w gunplocie
    * \param api - wskaźnik na gunplot 
    */
    virtual int rysuj(std::shared_ptr<drawNS::Draw3DAPI> &api) = 0;

    /*!
    * \brief Funkcja usuwa kształt z gunplota
    * \param api - wskaźnik na gunplot
    */
    virtual void usun(std::shared_ptr<drawNS::Draw3DAPI> &api, int ind) = 0;
};


#endif