#include "Macierz.hh"
#include <math.h>


/* 
    Konstuktor zmiennej Macierz, zeruje tabelę tab
    Argumenty:
        this
    Zwraca:
        this
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR>::Macierz()
{
    for(int i = 0; i < ROZMIAR; i++)
    {
        for(int j = 0; j < ROZMIAR; j++)
        {
            tab[i][j] = 0;
        }
    }
}


/* 
    Funkcja ta przeciąża operator indeksujący
    Argumenty:
        this
        int indeks - indeks zmniennej którą chcemy uzyskać
    Zwraca:
        tab[indeks] - zwraca tą zmienną klasy, której indeks podaliśmy
*/
template<class TYP, int ROZMIAR>
const Wektor<TYP,ROZMIAR> & Macierz<TYP,ROZMIAR>::operator[] (int indeks) const
{
    if (indeks < 0 || indeks >= ROZMIAR) {
      std::cerr << "blad: zly indeks macierzy";
      exit(1);
    }
    return this->tab[indeks];
}


/* 
    Funkcja ta przeciąża operator indeksujący
    Argumenty:
        this
        int indeks - indeks zmniennej którą chcemy uzyskać
    Zwraca:
        tab[indeks] - zwraca tą zmienną klasy, której indeks podaliśmy
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> & Macierz<TYP,ROZMIAR>::operator[] (int indeks)
{
    if (indeks < 0 || indeks >= ROZMIAR) {
      std::cerr << "blad: zly indeks macierzy";
      exit(1);
    }
    return this->tab[indeks];
}


/* 
    Funkcja ta przeciąża operator funkcjonalny
    Argumenty:
        this
        int ind1 - pierwszy indeks(wiersze)
        int ind2 - drugi indeks(kolumny)
    Zwraca:
        tab[ind1][ind2] - zwraca tą zmienną klasy, której indeksy podaliśmy
*/
template<class TYP, int ROZMIAR>
const TYP & Macierz<TYP,ROZMIAR>::operator() (int ind1, int ind2) const
{
    if (ind1 < 0 || ind1 >= ROZMIAR || ind2 < 0 || ind2 >= ROZMIAR) {
      std::cerr << "blad: zly indeks macierzy";
      exit(1);
    }
    return this->tab[ind1][ind2];
}


/* 
    Funkcja ta przeciąża operator funkcjonalny
    Argumenty:
        this
        int ind1 - pierwszy indeks(wiersze)
        int ind2 - drugi indeks(kolumny)
    Zwraca:
        tab[ind1][ind2] - zwraca tą zmienną klasy, której indeksy podaliśmy
*/
template<class TYP, int ROZMIAR>
TYP & Macierz<TYP,ROZMIAR>::operator() (int ind1, int ind2)
{
    if (ind1 < 0 || ind1 >= ROZMIAR || ind2 < 0 || ind2 >= ROZMIAR) {
      std::cerr << "blad: zly indeks macierzy";
      exit(1);
    }
    return this->tab[ind1][ind2];
}


/* 
    Funkcja ta transponuje macierz
    Argumenty:
        this
    Zwraca:
        Mac - transponowana macierz
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::transpozycja2() const
{
    Macierz Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        for(int j=0; j<ROZMIAR; j++)
        {
            Mac.tab[i][j] = this->tab[j][i];
        }
    }

    return Mac;
}


/* 
    Funkcja ta oblicza wyznacznik macierzy metodą Gaussa
    Argumenty:
        this
    Zwraca:
        d - wynacznik macierzy
*/
template<class TYP, int ROZMIAR>
TYP Macierz<TYP,ROZMIAR>::Wyznacznik() const
{
    int z;
    TYP d;
    Macierz<TYP,ROZMIAR> M;

    z = 0;
    M = *this;

    for(int i=0, x=ROZMIAR-1; i<ROZMIAR; i++, x--)  /* Przekształcamy macierz, w macierz trójkątną górną */
    {   
        for(int j=0; j<x; j++)
        {
            if(M[i][i] == 0)                        //Chroni przed dzieleniem przez 0, zamienia wiersze w macierzy
            {                                       
                M.zamiana(ROZMIAR-(j+1), i);
                z++;                                
            }
            M[ROZMIAR-(j+1)] = M[ROZMIAR-(j+1)] - M[i] * (M[ROZMIAR-(j+1)][i]/M[i][i]);
        }
    }

    d = pow(-1, z);                                 //W zależności od ilości zamian wierszy, zmienia znak wyznacznika

    for(int i=0; i<ROZMIAR; i++)    /* Obliczamy wyznacznik mnożąc liczby po przekątnej*/
    {
        d *= M[i][i];       
    }

    return d;
}


/* 
    Funkcja ta tworzy macierz odwrotną metodą Gaussa
    Argumenty:
        this
    Zwraca:
        Jed - macierz odwócona
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::odwrotnosc() const
{
    Macierz<TYP,ROZMIAR> M;
    Macierz<TYP,ROZMIAR> Jed;
    TYP p, temp;

    for(int i=0; i<ROZMIAR; i++)    /* Tworzymy macierz jednostkową */
    {
        Jed[i][i] = 1;
    }

    temp = 1;
    M = *this;

    for(int i=0, x=ROZMIAR-1; i<ROZMIAR; i++, x--)      // Przekształcamy macierz wejściową M w macierz trójkątną górną, wykonując 
    {                                                   // te same działania na macierzy jednostkowej Jed
        for(int j=0; j<x; j++)
        {   
            if(M[i][i] == 0)                            //Chroni przed dzieleniem przez 0, zamienia wiersze w obu macierzach
            {                                           
                M.zamiana(ROZMIAR-(j+1), i);
                Jed.zamiana(ROZMIAR-(j+1), i);
            }

            p = M[ROZMIAR-(j+1)][i]/M[i][i];
            M[ROZMIAR-(j+1)] = M[ROZMIAR-(j+1)] - M[i] * p;
            Jed[ROZMIAR-(j+1)] = Jed[ROZMIAR-(j+1)] - Jed[i] * p;
        }
    }

    for(int i=0; i<ROZMIAR; i++)                        //W macierzy M przekształcam wartości po przekątnej dzielimy aby uzykać jeden
    {                                                   //Dla macierzy Jed wykonujemy dokładniei te same działania co dla M
        p = temp/M[i][i];
        M[i] = M[i] * p;
        Jed[i] = Jed[i] * p;
    }


    for(int i=0, x=ROZMIAR-1; i<ROZMIAR; i++, x--)      //Przekształacmy macierz wejściową w macierz diagonalizowaną 
    {                                                   //Dla macierzy Jed wykonujemy te same działania co dla M
        for(int j=0; j<x; j++)
        {   
            p = M[j][ROZMIAR-(i+1)]/M[ROZMIAR-(i+1)][ROZMIAR-(i+1)];
            M[j] = M[j] - M[ROZMIAR-(i+1)] * p;
            Jed[j] = Jed[j] - Jed[ROZMIAR-(i+1)] * p;
        }
    }

    return Jed;
}


/* 
    Funkcja ta dodaje dwie macierze
    Argumenty:
        this
        M - druga macierz
    Zwraca:
        Mac - suma dwóch macierzy wejściowych
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::operator + (const Macierz & M) const
{
    Macierz<TYP,ROZMIAR> Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        for(int j=0; j<ROZMIAR; j++)
        {
            Mac.tab[i][j] = this->tab[i][j] + M.tab[i][j];
        }
    }

    return Mac;
}


/* 
    Funkcja ta odejmnuje dwie macierze
    Argumenty:
        this
        M - druga macierz
    Zwraca:
        Mac - różnica dwóch macierzy wejściowych
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::operator - (const Macierz & M) const
{
    Macierz<TYP,ROZMIAR> Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        for(int j=0; j<ROZMIAR; j++)
        {
            Mac.tab[i][j] = this->tab[i][j] - M.tab[i][j];
        }
    }

    return Mac;
}


/* 
    Funkcja ta mnoży dwie macierze
    Argumenty:
        this
        M - druga macierz
    Zwraca:
        Mac - iloraz dwóch macierzy wejściowych
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::operator * (const Macierz & M) const
{
   Macierz<TYP,ROZMIAR> Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        for(int j=0; j<ROZMIAR; j++)
        {
            for(int k=0; k<ROZMIAR; k++)
            {
                Mac.tab[i][j] += this->tab[i][k] * M.tab[k][j];
            }
        }
    }

    return Mac;
}


/* 
    Funkcja ta mnoży dwie macierze
    Argumenty:
        this
        M - druga macierz
    Zwraca:
        Mac - iloraz dwóch macierzy wejściowych
*/
template<class TYP, int ROZMIAR>
Macierz<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::operator *= (const Macierz & M)
{
    Macierz<TYP,ROZMIAR> Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        for(int j=0; j<ROZMIAR; j++)
        {
            for(int k=0; k<ROZMIAR; k++)
            {
                Mac.tab[i][j] += this->tab[i][k] * M.tab[k][j];
            }
        }
    }
    *this = Mac;

    return *this;
}


/* 
    Funkcja ta mnoży macierz z wektorem
    Argumenty:
        this
        W - wektor
    Zwraca:
        Wek - Iloraz macierzy i wektora wejściowego
*/
template<class TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Macierz<TYP,ROZMIAR>::operator * (const Wektor<TYP,ROZMIAR> & W) const
{
    Wektor<TYP,ROZMIAR> Wek;

    for(int i=0; i<ROZMIAR; i++)
    {   
        for(int j=0; j<ROZMIAR; j++)
        {   
            Wek[i] += this->tab[i][j] * W[j];
        }
    }

    return Wek;
}

template<class TYP, int ROZMIAR>
bool Macierz<TYP,ROZMIAR>::operator == (const Macierz & M)
{   
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            if(tab[i][j] != M[i][j])
                return false;
        }
    }
    return true;
}


/* 
    Funkcja ta zamienia dwa wiersze macierzy
    Argumenty:
        this
        x - indkes pierszego wiersza do zamiany
        y - indeks drugiego wiersza do zamiany
    Zwraca:
        brak
*/
template<class TYP, int ROZMIAR>
void Macierz<TYP,ROZMIAR>::zamiana(int x, int y)
{
    Wektor<TYP,ROZMIAR> temp;
    temp = tab[x];
    tab[x] = tab[y];
    tab[y] = temp;
}


/* 
    Funkcja ta wczytuje macierz z strumienia wejściowego
    Argumenty:
        Strm - strumień wejściowy
        Wek - macierz do której wczytujemy dane
    Zwraca:
        Strumień wejściowy
*/
template<class TYP, int ROZMIAR>
std::istream& operator >> (std::istream &Strm, Macierz<TYP,ROZMIAR> &Mac)
{
    for(int i=0; i<ROZMIAR; i++)
    {
        Strm >> Mac[i];
    }

    Mac = Mac.transpozycja2();
    return Strm;
}


/* 
    Funkcja ta wyświetla macierz na strumień wejściowy
    Argumenty:
        Strm - strumień wyjściowy
        Wek - macierz którą wyświetlamy
    Zwraca:
        Strumień wyjściowy
*/
template<class TYP, int ROZMIAR>
std::ostream& operator << (std::ostream &Strm, const Macierz<TYP,ROZMIAR> &Mac)
{   
    Macierz<TYP,ROZMIAR> M;
    //M = Mac.transpozycja2();
    M = Mac;

    for(int i=0; i<ROZMIAR; i++)
    {
        Strm << M[i] << std::endl;
    }
    
    return Strm; 
}


template class Macierz<double,3>;
template std::istream& operator >> (std::istream &Strm, Macierz<double,3> &Mac);
template std::ostream& operator << (std::ostream &Strm, const Macierz<double,3>  &Mac);
