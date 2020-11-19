#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<windows.h>

using namespace std;




struct Uzytkownicy
{
    string nick,haslo;
    int numerID;

};

int zamienNaLiczbe(string tekst)
{
    stringstream ss(tekst);
    int liczba;
    ss>>liczba;
    return liczba;
}

vector <Uzytkownicy> wczytajDanePliku()
{
    fstream mojPlik;
    vector <Uzytkownicy> dane;
    mojPlik.open("Uzytkownicy.txt", ios::in);
    if(mojPlik.good()==true)
    {
        string linia,nick,haslo;
        int numerID;
        vector <string> kontenerNaSlowa;
        int numerSlowa=0;
        Uzytkownicy daneOsoby;

        while(getline(mojPlik,linia,'|'))
        {
            numerSlowa++;
            kontenerNaSlowa.push_back(linia);
            if(numerSlowa==3)
            {
                daneOsoby.numerID = zamienNaLiczbe(kontenerNaSlowa[0]);
                daneOsoby.nick = kontenerNaSlowa[1];
                daneOsoby.haslo = kontenerNaSlowa[2];
                kontenerNaSlowa.clear();
                dane.push_back(daneOsoby);
                numerSlowa=0;
            }
        }
        return dane;


    }
    else
    {
        return dane;
    }
    mojPlik.close();
}


void dodajDoPLiku(vector <Uzytkownicy> daneUzytkownikow)
{
    fstream mojPlik;
    int ostatniWiersz = daneUzytkownikow.size()-1;
    mojPlik.open("Uzytkownicy.txt", ios::out| ios::app);
    if(mojPlik.good()==false)
    {
        cout<<"Brak takiego pliku"<<endl;
        Sleep(1500);
    }
    mojPlik<<daneUzytkownikow[ostatniWiersz].numerID<<"|"<<daneUzytkownikow[ostatniWiersz].nick<<"|"<<daneUzytkownikow[ostatniWiersz].haslo<<"|"<<endl;
    cout<<"Dodano: "<<daneUzytkownikow[ostatniWiersz].nick<<" do bazy"<<endl;
    Sleep(1500);
    mojPlik.close();

}

bool powtorzeniaNicku(vector <Uzytkownicy> dane, string nick)
{
    int liczbaWystapien=0;
    for(int i =0; i<dane.size(); i++)
    {
        if(dane[i].nick==nick)
        {
            liczbaWystapien++;
        }
    }
    if(liczbaWystapien>0)
    {
        cout<<"Taki nick juz istnieje, sprobuj ponownie: "<<endl;
        Sleep(1500);
        return false;
    }
    return true;
}

int PrzydzielNumerID(vector <Uzytkownicy> dane)
{
    if(dane.size()>0)
    {
        int nowyOstatniRekord = dane.size()-1;
        int nowyOstatnieID = dane[nowyOstatniRekord].numerID+1;
        return nowyOstatnieID;
    }
    else
    {
        return 0;
    }

}


string wpisywanieNicku(vector <Uzytkownicy> dane)
{
    string nick;
    cin.clear();
    cout<<"podaj nick: ";
    cin.sync();
    getline(cin,nick);
    while(powtorzeniaNicku(dane,nick)==false)
    {
        cin.clear();
        cin.sync();
        getline(cin, nick);
    }
    return nick;;

}

vector <Uzytkownicy> rejestrujUzytkownika(vector <Uzytkownicy> dane)
{
    string nick,haslo;
    nick = wpisywanieNicku(dane);
    cin.clear();
    cin.sync();
    cout<<"Podaj haslo: ";
    getline(cin, haslo);
    int numerID = PrzydzielNumerID(dane);
    Uzytkownicy daneOsoby;
    daneOsoby.numerID = numerID;
    daneOsoby.nick = nick;
    daneOsoby.haslo = haslo;
    dane.push_back(daneOsoby);
    return dane;

}

int logowanie(vector <Uzytkownicy> dane)
{
    string nick,haslo;
    if(dane.size()>0)
    {

    int liczbaProb =3;
    bool zalogowany = false;
    while(zalogowany==false)
    {
        cin.sync();
        cout<<"Nick: ";
        getline(cin,nick);
        cout<<"Haslo: ";
        cin.sync();
        getline(cin, haslo);


    for(int i =0; i<dane.size(); i++)
    {
        if(dane[i].nick==nick && dane[i].haslo==haslo)
        {
            cout<<"Witaj "<<dane[i].nick<<endl;
            Sleep(1500);
            zalogowany = true;
            return dane[i].numerID;
            break;
        }
    }
        cout<<"Nieprawidlowy login lub haslo"<<endl;
        liczbaProb--;
        cout<<"Pozosta³o prob: "<<liczbaProb<<endl;
        Sleep(1600);
        system("cls");
        if(liczbaProb==0)
        {
            cout<<"Przekroczono liczbe prob"<<endl;
            Sleep(1500);
            break;
            exit(0);
        }
    }
    }
    else
    {
        cout<<"NIe ma zadnego zarejestrowanego uzytkownika"<<endl;
        Sleep(1800);
        exit(0);
    }
}


void menuGlowne()
{
    cout<<"Okno Logowania: "<<endl;
    cout<<"1-Logowanie"<<endl;
    cout<<"2-Rejestracja"<<endl;
    cout<<"3-Zamknij program"<<endl;
}


int main()
{
    vector <Uzytkownicy> daneUzytkownikow = wczytajDanePliku();
    int numerID = PrzydzielNumerID(daneUzytkownikow);
    cout<<"Liczba Osob w bazie: "<<daneUzytkownikow.size()<<endl;

    char wybor;
    while(true)
    {

    menuGlowne();
    cin>>wybor;
    if(wybor=='1')
    {
        int identyfikatorZalogowanego = logowanie(daneUzytkownikow);
        system("cls");
    }
    if(wybor=='2')
    {
        daneUzytkownikow = rejestrujUzytkownika(daneUzytkownikow);
        numerID = PrzydzielNumerID(daneUzytkownikow);
        dodajDoPLiku(daneUzytkownikow);
        system("cls");
    }

    if(wybor=='3')
    {
        exit(0);
    }

    }

    return 0;
}
