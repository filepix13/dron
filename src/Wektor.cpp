#include "Wektor.hh"
#include <math.h>  
#include <iostream>


/* 
    Funkcja zmieniająca zmienna Wektor
    Argumenty:
        x - zmienia dana[0]
        y - zmienia dana[1]
        z - zmienia dana[2]
    Zwraca:
        this
*/
template<>
Wektor<double,3> Wektor<double,3>::ustaw(double x, double y, double z)
{
    dane[0] = x;
    dane[1] = y;
    dane[2] = z;

    return *this;
}

/* 
    Funkcja ta dodaje dwa wektory
    Argumenty:
        this
        W2 - drugi wektor
    Zwraca:
        W - suma dwóch wektorów
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Wektor<TYP,ROZMIAR>::operator + (const Wektor & W2) const
{
    Wektor W;

    for(int i=0; i<ROZMIAR; i++)
    {
        W.dane[i] = this->dane[i] + W2.dane[i];
    }

    return W;
}


/* 
    Funkcja ta dodaje dwa wektory
    Argumenty:
        this
        W2 - drugi wektor
    Zwraca:
        W - suma dwóch wektorów
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Wektor<TYP,ROZMIAR>::operator += (const Wektor & W2)
{
    Wektor W;

    for(int i=0; i<ROZMIAR; i++)
    {
        dane[i] += W2.dane[i];
    }

    return *this;
}

/* 
    Funkcja ta odejmnuje dwa wektory
    Argumenty:
        this
        W2 - drugi wektor
    Zwraca:
        W - różnica dwóch wektorów
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Wektor<TYP,ROZMIAR>::operator - (const Wektor & W2) const
{
    Wektor W;

    for(int i=0; i<ROZMIAR; i++)
    {
        W.dane[i] = this->dane[i] - W2.dane[i];
    }

    return W;
}


/* 
    Funkcja ta oblicza iloczyn sklarny dwóch wektorów
    Argumenty:
        this
        W2 - drugi wektor
    Zwraca:
        Iloczyn skalarny(double)
*/
template<class TYP, int ROZMIAR>
TYP Wektor<TYP,ROZMIAR>::operator * (const Wektor & W2) const
{
    TYP d;

    for(int i=0; i<ROZMIAR; i++)
    {
        d += dane[i] * W2.dane[i];
    }

    return d;
}


/* 
    Funkcja ta mnoży elementy wektora przez liczbę
    Argumenty:
        this
        t - liczba przez którą mnożymy
    Zwraca:
        Wektor pomnozony przez liczbę
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Wektor<TYP,ROZMIAR>::operator * (TYP t) const
{
    Wektor W;

    for(int i=0; i<ROZMIAR; i++)
    {
        W[i] = dane[i] * t;
    }

    return W;
}


/* 
    Funkcja ta zamienia dwie liczby wektora
    Argumenty:
        this
        x - indeks pierwszej liczby którą zamieniamy
        y - indeks drugiej liczby którą zamieniamy
    Zwraca:
        brak`
*/
template<class TYP, int ROZMIAR>
void Wektor<TYP,ROZMIAR>::zamiana(int x, int y)
{
    TYP temp;
    temp = dane[x];
    dane[x] = dane[y];
    dane[y] = temp;
}


/* 
    Funkcja ta przeciąża operator indeksujący
    Argumenty:
        this
        int indeks - indeks zmniennej którą chcemy uzyskać
    Zwraca:
        dane[indeks] - zwraca tą zmienną klasy, której indeks podaliśmy
*/
template<class TYP, int ROZMIAR>
const TYP & Wektor<TYP,ROZMIAR>::operator[] (int indeks) const
{
    if (indeks < 0 || indeks >= ROZMIAR) {
      std::cerr << "blad:  zly indeks wektora";
      exit(1);
    }
    return this->dane[indeks];
}


/* 
    Funkcja ta przeciąża operator indeksujący
    Argumenty:
        this
        int indeks - indeks zmniennej którą chcemy uzyskać
    Zwraca:
        dane[indeks] - zwraca tą zmienną klasy, której indeks podaliśmy
*/
template<class TYP, int ROZMIAR>
TYP & Wektor<TYP,ROZMIAR>::operator[] (int indeks)
{
    if (indeks < 0 || indeks >= ROZMIAR) {
      std::cerr << "blad: zly indeks wektora";
      exit(1);
    }
    return this->dane[indeks];
}


/* 
    Funkcja ta wczytuje wektor z strumienia wejściowego
    Argumenty:
        Strm - strumień wejściowy
        Wek - wektor do którego wczytujemy dane
    Zwraca:
        Strumień wejściowy
*/
template <class TYP, int ROZMIAR>
std::istream& operator >> (std::istream &Strm, Wektor<TYP, ROZMIAR> &Wek)
{
    for(int i=0; i<ROZMIAR; i++)
    {
        Strm >> Wek[i];
    }

    if(std::cin.fail())
    {
        std::cerr << "Wpisany znak nie jest liczbą rzeczywistą" << std::endl << "Zamykanie programu...";
        exit(1);
    }

    return Strm;
}


/* 
    Funkcja ta wyświetla wektor na strumień wejściowy
    Argumenty:
        Strm - strumień wyjściowy
        Wek - wektor który wyświetlamy
    Zwraca:
        Strumień wyjściowy
*/
template <class TYP, int ROZMIAR>
std::ostream& operator << (std::ostream &Strm, const Wektor<TYP,ROZMIAR> & Wek)
{
    for(int i=0; i<ROZMIAR; i++)
    {
        Strm << Wek[i] << "  ";
    }

    Strm << std::endl;

    return Strm;
}


template class Wektor<double,3>;
template std::istream& operator >> (std::istream &Strm, Wektor<double,3> &Wek);
template std::ostream& operator << (std::ostream &Strm, const Wektor<double,3> & Wek);
