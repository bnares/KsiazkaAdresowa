#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

bool sprawdzanieDlugosciZNaku(string tekst);



struct uzytkownicy
{
    string imie, nazwisko,adres,email,telefon, przyjaciel;
    int id;
};


int ostatniNumerIDUzytkownika(vector <uzytkownicy> dane)
{
    fstream mojPlik;
    mojPlik.open("dane.txt", ios::in);
    if(mojPlik.good())
    {
    int ostatniaOsoba = dane.size()-1;
    int wartoscID = dane[ostatniaOsoba].id+1;
    return wartoscID;
    }
    else
    {
        return 0;
    }
    mojPlik.close();
}



int zamienNaLiczbe(string tekstDoZamiany)
{
    int liczba;
    stringstream ss(tekstDoZamiany);
    ss>>liczba;
    return liczba;

}


vector <uzytkownicy> wczytywaniePoczatkoweDanych()
{
    uzytkownicy PojemnikNaIteracjePoUzytkownikach;
    vector <string> tymaczasowyPojemnik;
    vector <uzytkownicy> dane;
    fstream mojPlik;
    string linia;
    mojPlik.open("dane.txt", ios::in);
    if(mojPlik.good()==false)
    {
        return dane;
    }
    else
    {
        int numerZmiennejLini=0;
        int numerPozycji=0;
        while(getline(mojPlik,linia, '|'))
        {
            numerPozycji++;
            tymaczasowyPojemnik.push_back(linia);

            if(numerPozycji==7)
            {
                PojemnikNaIteracjePoUzytkownikach.id = zamienNaLiczbe(tymaczasowyPojemnik[0]);
                PojemnikNaIteracjePoUzytkownikach.imie = tymaczasowyPojemnik[1];
                PojemnikNaIteracjePoUzytkownikach.nazwisko = tymaczasowyPojemnik[2];
                PojemnikNaIteracjePoUzytkownikach.adres = tymaczasowyPojemnik[3];
                PojemnikNaIteracjePoUzytkownikach.email = tymaczasowyPojemnik[4];
                PojemnikNaIteracjePoUzytkownikach.telefon = tymaczasowyPojemnik[5];
                PojemnikNaIteracjePoUzytkownikach.przyjaciel = tymaczasowyPojemnik[6];
                dane.push_back(PojemnikNaIteracjePoUzytkownikach);
                tymaczasowyPojemnik.clear();
                numerPozycji =0;
            }
        }
        return dane;
    }
    mojPlik.close();
}




void dodawanieDoPliku(vector <uzytkownicy> dane)
{
    fstream mojPlik;
    mojPlik.open("dane.txt", ios::out| ios::app);
    int dlugoscWektora = dane.size();
    mojPlik<<dane[dlugoscWektora-1].id<<"|"<<dane[dlugoscWektora-1].imie<<"|"<<dane[dlugoscWektora-1].nazwisko<<"|"<<dane[dlugoscWektora-1].adres<<"|"<<dane[dlugoscWektora-1].email<<"|"<<dane[dlugoscWektora-1].telefon<<"|"<<dane[dlugoscWektora-1].przyjaciel<<"|"<<endl;
    mojPlik.close();

}

bool sprawdzCzyUzytkownikIstnieje(vector <uzytkownicy> dane, string imie, string nazwisko)
{
    for(int i =0; i<dane.size(); i++)
    {
        if(dane[i].imie==imie && dane[i].nazwisko==nazwisko)
        {
            return true;
        }
    }
    return false;
}



string sprawdzeniePoprawnosciSlowa()
{
    string tekst;
    cout<<"Podaj imie/nazwisko a nastepnie kliknij enter: ";
    cin.sync();
    cin.clear();
    getline(cin,tekst);
    while(sprawdzanieDlugosciZNaku(tekst)==false)
        {
            getline(cin, tekst);
            cin.sync();
            cin.clear();
        }
        system("cls");
    return tekst;
}



vector <uzytkownicy> dodawanieUzytkownika(vector <uzytkownicy> dane, int iloscOsobWBazie)
{
    uzytkownicy nowyUzytkownik;
    string imie,nazwisko, adres, email, telefon, przyjaciel;
    int numerIdentyfikacyjny;
    cin.sync();
    cin.clear();
    imie = sprawdzeniePoprawnosciSlowa();
    nazwisko = sprawdzeniePoprawnosciSlowa();
    if(sprawdzCzyUzytkownikIstnieje(dane, imie, nazwisko))
    {
        cout<<"Taki uzytkownik juz istnieje"<<endl;
        Sleep(1500);
        return dane;
    }
    cin.sync();
    cin.clear();
    cout<<"Adres: ";
    getline(cin,adres);
    system("cls");
    cin.sync();
    cin.clear();
    cout<<"Email: ";
    getline(cin, email);
    system("cls");
    cin.sync();
    cin.clear();
    cout<<"Telefon: ";
    getline(cin, telefon);
    system("cls");
    cin.sync();
    cin.clear();
    cout<<"Czy to jest przyjaciel TAK/NIE? ";
    getline(cin, przyjaciel);
    system("cls");
    transform(przyjaciel.begin(), przyjaciel.end(), przyjaciel.begin(), ::toupper);
    numerIdentyfikacyjny = iloscOsobWBazie;


    nowyUzytkownik.imie = imie;
    nowyUzytkownik.nazwisko = nazwisko;
    nowyUzytkownik.adres = adres;
    nowyUzytkownik.email = email;
    nowyUzytkownik.telefon = telefon;
    nowyUzytkownik.przyjaciel = przyjaciel;
    nowyUzytkownik.id = numerIdentyfikacyjny;

    dane.push_back(nowyUzytkownik);

    dodawanieDoPliku(dane);
    cout<<"Dodano uzytkownika "<<nowyUzytkownik.nazwisko<<endl;
    return dane;

}

void szukajPoimieniu(vector <uzytkownicy> dane)
{
    string imie;
    //cout<<"Szukane imie: "<<endl;
    imie = sprawdzeniePoprawnosciSlowa();
    const int iloscRekordowDanych = dane.size();
    int iloscWystapien = 0;
    for(int i =0; i<iloscRekordowDanych; i++)
    {
        if(dane[i].imie==imie)
        {
            cout<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].adres<<" "<<dane[i].email<<" "<<dane[i].telefon<<" "<<dane[i].przyjaciel<<endl;
            iloscWystapien++;
        }
    }
    if(iloscWystapien==0)
    {
        cout<<"Brak osob o takim imieniu"<<endl;
        Sleep(1500);
    }
    else
    {
        cout<<"Znaleciono "<<iloscWystapien<<" o takim imieniu"<<endl;
        Sleep(3500);
    }
    iloscWystapien=0;
}

void szukajPoNazwisku(vector <uzytkownicy> dane)
{
    int iloscWystapien = 0;
    const int wielkoscBazyDanych = dane.size();
    string nazwisko;
    cin.sync();
    cin.clear();
    //cout<<"Szukane nazwisko "<<endl;
    nazwisko = sprawdzeniePoprawnosciSlowa();
    for(int i =0; i<wielkoscBazyDanych; i++)
    {
        if(dane[i].nazwisko==nazwisko)
        {
            cout<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].adres<<" "<<dane[i].email<<" "<<dane[i].telefon<<" "<<dane[i].przyjaciel<<endl;
            iloscWystapien++;
        }
    }

    if(iloscWystapien==0)
    {
        cout<<"Nie znakeziono osoby o takim nazwisku"<<endl;
        Sleep(2000);
        system("cls");
    }
    else
    {
        cout<<"znaleziono "<<iloscWystapien<<" osob"<<endl;
        iloscWystapien=0;
        Sleep(3500);
        system("cls");
    }

}

void wyswietlWszystkich(vector <uzytkownicy> dane)
{
    const int iloscRekordow = dane.size();

    if(iloscRekordow==0)
    {
        cout<<"Baza danych jest pusta"<<endl;
        Sleep(1500);
    }
    else
    {

    for(int i =0; i<iloscRekordow; i++)
    {
        cout<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].adres<<" "<<dane[i].email<<" "<<dane[i].telefon<<" "<<dane[i].przyjaciel<<endl;
    }
    Sleep(3500);
    }
}

vector <uzytkownicy> usunElementWektora(vector <uzytkownicy> dane)
{
    string numerID;
    int numerIdentyfikacyjny;
    cout<<"Podaj numer ID uzytkownika do usuniecia: ";
    cin.sync();
    cin.clear();
    getline(cin, numerID);
    numerIdentyfikacyjny = zamienNaLiczbe(numerID);


    const int wielkoscBazy = dane.size();
    int pozycjaWskzanika =-1;
    for(int i =0; i<wielkoscBazy; i++)
    {
        if(dane[i].id == numerIdentyfikacyjny)
        {
            pozycjaWskzanika = i;
            cout<<"Pozycja wskaznka do usuniecia: "<<pozycjaWskzanika<<endl;
            Sleep(2000);
        }
    }
    if(pozycjaWskzanika!=-1)
    {

    cout<<"Usunieto: "<<dane[pozycjaWskzanika].imie<<" "<<dane[pozycjaWskzanika].nazwisko<<endl;
    Sleep(1500);
    dane.erase(dane.begin()+pozycjaWskzanika);
    system("cls");
    return dane;
    }

    else
    {
        cout<<"Nie ma takiego rekordu"<<endl;
        Sleep(1500);
        system("cls");
        return dane;
    }

    system("cls");
}

void stworzPlikZWektora(vector <uzytkownicy> dane)
{
    fstream mojPlik;
    string imie, nazwisko, adres,email,telefon,przyjaciel;
    int NumerIdentyfikacyjny;
    const int wielkoscBazy = dane.size();
    mojPlik.open("dane.txt", ios::out);
    for(int i =0; i<wielkoscBazy; i++)
    {
        NumerIdentyfikacyjny = i;
        imie = dane[i].imie;
        nazwisko = dane[i].nazwisko;
        adres = dane[i].adres;
        email = dane[i].email;
        telefon = dane[i].telefon;
        przyjaciel = dane[i].przyjaciel;
        NumerIdentyfikacyjny = dane[i].id;
        mojPlik<<NumerIdentyfikacyjny<<"|"<<imie<<"|"<<nazwisko<<"|"<<adres<<"|"<<email<<"|"<<telefon<<"|"<<przyjaciel<<"|"<<endl;
    }
    mojPlik.close();
}

void wyswietlpodMenu()
{
            cout<<"Wybierz pole do zmiany: "<<endl;
            cout<<"1-imie"<<endl;
            cout<<"2-Nazwisko"<<endl;
            cout<<"3-adres"<<endl;
            cout<<"4-email"<<endl;
            cout<<"5-numer telefonu"<<endl;
            cout<<"6-powrot do menu"<<endl;
}

bool sprawdzanieDlugosciZNaku(string tekst)
{
    if(tekst.length()>0)
    {
        return true;
    }
    else
    {
        cout<<"Slowo zbyt krotkie, sprobuj ponownie"<<endl;
        return false;
    }
}



vector <uzytkownicy> edytujBazeDanych(vector <uzytkownicy> dane)
{
    string numer;
    int numerId;
    cout<<"Podaj nr id rekordu do edycji: ";
    cin.sync();
    cin.clear();
    getline(cin, numer);
    numerId = zamienNaLiczbe(numer);
    const int wielkoscBazy = dane.size();
    int liczbaWystapien =0;
    for(int i =0; i<wielkoscBazy; i++)
    {
        if(dane[i].id==numerId)
        {
            cout<<"Wybrales: "<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].adres<<" "<<dane[i].email<<" "<<dane[i].telefon<<endl;
            liczbaWystapien++;
            char wyborOpcji;
            wyswietlpodMenu();
            cin>>wyborOpcji;
            if(wyborOpcji=='1')
            {
                string imie = sprawdzeniePoprawnosciSlowa();
                dane[i].imie = imie;
                cout<<"Edytowano imie na: "<<imie<<endl;
                Sleep(1500);
                system("cls");
                stworzPlikZWektora(dane);
            }
            else if(wyborOpcji=='2')
            {
                string nazwisko = sprawdzeniePoprawnosciSlowa();
                dane[i].nazwisko = nazwisko;
                cout<<"Edytowano nazwisko na: "<<nazwisko<<endl;
                Sleep(1500);
                system("cls");
                stworzPlikZWektora(dane);
                system("cls");
            }
            else if(wyborOpcji=='3')
            {
                string adres;
                cin.sync();
                cin.clear();
                cout<<"Podaj nowy adres: ";
                getline(cin,adres);
                cin.clear();
                dane[i].adres = adres;
                stworzPlikZWektora(dane);
                system("cls");
            }
            else if(wyborOpcji=='4')
            {
                string email;
                cin.sync();
                cin.clear();
                cout<<"Podaj nowy email: ";
                getline(cin,email);
                cin.clear();
                dane[i].email = email;
                stworzPlikZWektora(dane);
                system("cls");
            }
            else if(wyborOpcji=='5')
            {
                string telefon;
                cin.sync();
                cin.clear();
                cout<<"POdaj nr telefonu: ";
                getline(cin, telefon);
                cin.clear();
                dane[i].telefon = telefon;
                stworzPlikZWektora(dane);
                system("cls");
            }
            else
            {

                cout<<"Powrot do menu glownego"<<endl;
                Sleep(1000);
                system("cls");
            }
        }
    }

    if(liczbaWystapien==0)
    {
        cout<<"nie znaleziono uzytkownika o takim id"<<endl;
        Sleep(1500);
        system("cls");
    }
    liczbaWystapien=0;
    return dane;
}

void menuGlowne()
{
    cout<<"KSIAZKA ADRESOWA"<<endl;
    cout<<"1.Dodaj adresata"<<endl;
    cout<<"2.Wyszukaj po imieniu"<<endl;
    cout<<"3.Wyszukaj po nazwisku"<<endl;
    cout<<"4.Wyswietl wszystkich Adresatow"<<endl;
    cout<<"5.Usun Adresata"<<endl;
    cout<<"6.Edytuj Adresata"<<endl;
    cout<<"7.Zakoncz program"<<endl;
}

int main()
{
    vector <uzytkownicy> bazaDanych;
    char wyborOpcji;
    bazaDanych = wczytywaniePoczatkoweDanych();
    int IloscOsobWBazie = ostatniNumerIDUzytkownika(bazaDanych);

    cout<<"Poczatkowa ilosc osob: "<<bazaDanych.size()<<endl;

    while(true)
    {
    menuGlowne();
    cin>>wyborOpcji;
    system("cls");


    if(wyborOpcji=='1')
        {
            bazaDanych = dodawanieUzytkownika(bazaDanych, IloscOsobWBazie);
            IloscOsobWBazie = ostatniNumerIDUzytkownika(bazaDanych);
            system("cls");
        }
     if(wyborOpcji=='2')
    {
        szukajPoimieniu(bazaDanych);
        system("cls");
    }

    if(wyborOpcji=='3')
    {
        szukajPoNazwisku(bazaDanych);
        system("cls");
    }

    if(wyborOpcji=='4')
    {
        wyswietlWszystkich(bazaDanych);
        system("cls");
    }
    if(wyborOpcji=='5')
    {
        bazaDanych = usunElementWektora(bazaDanych);
        IloscOsobWBazie = ostatniNumerIDUzytkownika(bazaDanych);
        stworzPlikZWektora(bazaDanych);
    }

    if(wyborOpcji=='6')
    {
       bazaDanych =  edytujBazeDanych(bazaDanych);
    }


    if(wyborOpcji=='7')
        {
            cout<<"Do widzenia"<<endl;
            Sleep(1500);
            exit(0);
        }
    }

    return 0;
}
