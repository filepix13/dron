#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>


/*
  Klasa wektor modeluje pojęcie macierzy o 1 kolumnie i ROZMIAR wierszach
 */
template <class TYP, int ROZMIAR>
class Wektor 
{
  protected:
  
  TYP dane[ROZMIAR];

  /*!
    * \brief Pole zlicza ilość obiektów klasy wektor które istnieją
  */
  static int ile_istnieje;

  /*!
    * \brief Pole zlicza ilość obiektów klasy wektor które utworzono
  */
  static int ile_utworzono;

  public:
  /*!
    * \brief Konstruktor bezparametryczny
  */
  Wektor()
  {
    dane[0] = 0;
    dane[1] = 0;
    dane[2] = 0;

    ile_istnieje++;
    ile_utworzono++;
  }

  /*!
    * \brief konstuktor kopiujący
    * \param nowy - wektor który kopiujemy
  */
  Wektor(const Wektor & nowy)
  {
    dane[0] = nowy.dane[0];
    dane[1] = nowy.dane[1];
    dane[2] = nowy.dane[2];
    
    ile_istnieje++;
    ile_utworzono++;
  }
  
  /*!
    * \brief Konstruktor parametryczny
    * \param x - zmienna x
    * \param y - zmienna y
    * \param z - zmienna z
  */
  Wektor(double x, double y, double z)
  {
    dane[0] = x;
    dane[1] = y;
    dane[2] = z;

    ile_istnieje++;
    ile_utworzono++;
  }

  /*!
    * \brief Dekonstruktor
  */
  ~Wektor()
  {
    ile_istnieje--;
  }

  //Deklaracja funkcji zmieniającej dane wektora
  Wektor ustaw(double x, double y, double z);

  //Deklaracja funkcji dodającej dwa wektory
  Wektor operator + (const Wektor & W2) const;

  Wektor operator += (const Wektor & W2);

  //Deklaracja funkcji odejmującej dwa wektory
  Wektor operator - (const Wektor & W2) const;

  //Deklaracja funckji obliczającej iloczyn skalarny dwóch wektorów
  TYP operator * (const Wektor & W2) const;

  //Deklaracja funkcji mnożącej poszczególne elementy wektora przez liczbę
  Wektor operator * (TYP t) const;

  //Deklaracja funkcji zamieniającej dwie liczby wektora
  void zamiana (int x, int y);

  //Deklaracja przeciążenia funkcji indeksującej
  const TYP & operator [] (int indeks) const;

  //Deklaracja przeciążenia funkcji indeksującej
  TYP & operator[] (int indeks);

  /*!
    * \brief Pole zlicza ilość obiektów klasy wektor które istnieją
    */
  static int zwroc_istniejace()
  {
      return ile_istnieje;
  }

  /*!
    * \brief Pole zlicza ilość obiektów klasy wektor które utworzono
    */
  static int zwroc_utworzone()
  {
      return ile_utworzono;
  } 

};

template <class TYP, int ROZMIAR>
int Wektor<TYP,ROZMIAR>::ile_istnieje = 0;

template <class TYP, int ROZMIAR>
int Wektor<TYP,ROZMIAR>::ile_utworzono = 0;

/* 
  Funkcja wczytująca wektor ze strumienia wejściowego
*/
template <class TYP, int ROZMIAR>
std::istream & operator>> (std::istream & Strm, Wektor<TYP,ROZMIAR> & Wek);

/*
  Funkcja wyświetlająca wektor na strumień wejściowy
 */
template <class TYP, int ROZMIAR>
std::ostream& operator << (std::ostream &Strm, const Wektor<TYP,ROZMIAR> & Wek);


#endif
