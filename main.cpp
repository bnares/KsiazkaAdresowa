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

struct Adresaci
{
    string imie,nazwisko,telefon,email,adres;
    int idAdresata, idUzytkownika;
};

void zamienPLikiGLowne(int numerIdAdresata, Adresaci zmienianaOsoba);

void zmienNazwePlikuTekstowego(string nowaNazwaPliku, string staraNazwaPLiku);




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


void dodajDoPLikuUzytkownika(vector <Uzytkownicy> daneUzytkownikow)
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
            //break;
        }
    }
        cout<<"Nieprawidlowy login lub haslo"<<endl;
        liczbaProb--;
        cout<<"Pozostalo prob: "<<liczbaProb<<endl;
        Sleep(1600);
        system("cls");
        if(liczbaProb==0)
        {
            cout<<"Przekroczono liczbe prob"<<endl;
            Sleep(1500);
            return -1;
            break;

        }
    }
    }
    else
    {
        cout<<"NIe ma zadnego zarejestrowanego uzytkownika"<<endl;
        Sleep(1800);
        return -1;

    }
}


void menuGlowne()
{
    cout<<"Okno Logowania: "<<endl;
    cout<<"1-Logowanie"<<endl;
    cout<<"2-Rejestracja"<<endl;
    cout<<"3-Zamknij program"<<endl;
}











void menuZalogowanego()
{
    cout<<"KSIAZKA ADRESOWA"<<endl;
    cout<<"1.Dodaj adresata"<<endl;
    cout<<"2.Wyszukaj po imieniu"<<endl;
    cout<<"3.Wyszukaj po nazwisku"<<endl;
    cout<<"4.Wyswietl wszystkich Adresatow"<<endl;
    cout<<"5.Usun Adresata"<<endl;
    cout<<"6.Edytuj Adresata"<<endl;
    cout<<"7.Zmien haslo"<<endl;
    cout<<"8.Wyloguj sie"<<endl;
}


vector <int> zapisujNumeryIdWierszyZalogowanego(vector <Adresaci> dane)
{
    vector <int> listaUzywanychNumerowWierszy;
    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        listaUzywanychNumerowWierszy.push_back( it -> idAdresata);
    }
    return listaUzywanychNumerowWierszy;
}




vector <Adresaci> ladowaniePoczatkowDanychZalogowanemu(int numerIDuztkownika)
{
    vector <Adresaci> BazaDanychZalogowanego;
    if(numerIDuztkownika==-1)
    {
        return BazaDanychZalogowanego;
    }

    else
    {

    Adresaci daneAdresata;
    fstream mojPlik;
    vector <string> tymczasowe;
    string imie, nazwisko, email,adres,telefon;
    int IDadresata, IDuzytkownika;

    IDuzytkownika = numerIDuztkownika;
    mojPlik.open("Adresaci.txt", ios::in);
    if(mojPlik.good())
    {
        string linia;
        int wyrazy=1;
        while(getline(mojPlik,linia, '|'))
        {
            tymczasowe.push_back(linia);
            wyrazy++;
            if(wyrazy==8)
            {
                daneAdresata.idAdresata = zamienNaLiczbe(tymczasowe[0]);
                daneAdresata.idUzytkownika = zamienNaLiczbe(tymczasowe[1]);
                daneAdresata.imie = tymczasowe[2];
                daneAdresata.nazwisko = tymczasowe[3];
                daneAdresata.telefon = tymczasowe[4];
                daneAdresata.email = tymczasowe[5];
                daneAdresata.adres = tymczasowe[6];
                if(daneAdresata.idUzytkownika!=numerIDuztkownika)
                {
                    wyrazy=1;
                    tymczasowe.clear();
                }
                else
                {
                    BazaDanychZalogowanego.push_back(daneAdresata);
                    tymczasowe.clear();
                    wyrazy=1;
                }
            }

        }
        return BazaDanychZalogowanego;

    }
    else
    {
        return BazaDanychZalogowanego;
    }
    mojPlik.close();

    }


}

int ostaniNumerAdresata()
{
    fstream mojPlik;
    vector <string> numeryAdresatow;
    vector <string> tymczasowy;
    mojPlik.open("Adresaci.txt",ios::in);
    if(mojPlik.good())
    {
        string linia;
        int licznikSlow=1;
        while(getline(mojPlik,linia, '|'))
        {
            tymczasowy.push_back(linia);
            licznikSlow++;
            if(licznikSlow==8)
            {
                licznikSlow=1;
                numeryAdresatow.push_back(tymczasowy[0]);
                tymczasowy.clear();

            }
        }
        if(numeryAdresatow.empty()==true)
        {
            return 0;
        }
        else
        {
            int numery = zamienNaLiczbe(numeryAdresatow[numeryAdresatow.size()-1]);
            return numery;
        }
    }
    else
    {
        return 0;
    }
    mojPlik.close();
}

bool sprawdzCzyNieMaPowtorzen(vector <Adresaci> dane, string imie, string nazwisko)
{
  for(int i =0; i<dane.size(); i++)
  {
      if(dane[i].imie==imie & dane[i].nazwisko==nazwisko)
      {
          cout<<dane[i].nazwisko<<" juz wystepuje w twojej ksiazce adresowej, sprobuj ponownie: "<<endl;
          Sleep(1500);
          return false;
      }
  }
  return true;
}


vector <Adresaci> dodajAdresata(vector <Adresaci> dane, int pierwszeWolneIdAdresata, int numerZalogowanego)
{
    int idAdresata = pierwszeWolneIdAdresata;
    int idUzytkownika = numerZalogowanego;
    string imie, nazwisko,telefon,email,adres;
    Adresaci daneNowejOsoby;

    cin.sync();
    cout<<"Imie: ";
    getline(cin, imie);
    cout<<"Nazwisko: ";
    cin.sync();
    getline(cin, nazwisko);
    while(sprawdzCzyNieMaPowtorzen(dane, imie, nazwisko)==false)
    {

        cin.sync();
        cout<<"Imie: ";
        getline(cin, imie);
        cout<<"Nazwisko: ";
        cin.sync();
        getline(cin, nazwisko);
        system("cls");
    }
    cin.sync();
    cout<<"Telefon: ";
    getline(cin, telefon);
    cout<<"Email: ";
    cin.sync();
    getline(cin, email);
    cout<<"Adres: ";
    getline(cin, adres);
    daneNowejOsoby.idAdresata = idAdresata;
    daneNowejOsoby.idUzytkownika = numerZalogowanego;
    daneNowejOsoby.imie = imie;
    daneNowejOsoby.nazwisko = nazwisko;
    daneNowejOsoby.telefon = telefon;
    daneNowejOsoby.email = email;
    daneNowejOsoby.adres = adres;
    dane.push_back(daneNowejOsoby);
    cout<<"Dodano: "<<daneNowejOsoby.imie<<" "<<daneNowejOsoby.nazwisko<<endl;
    Sleep(1500);
    return dane;
}


void dodajDoPlikuAdresata(vector <Adresaci> dane)
{
    fstream mojPlik;
    int indeksOstaniegoAdresata = dane.size()-1;
    mojPlik.open("Adresaci.txt", ios::out| ios::app);
    mojPlik<<dane[indeksOstaniegoAdresata].idAdresata<<"|"<<dane[indeksOstaniegoAdresata].idUzytkownika<<"|"<<dane[indeksOstaniegoAdresata].imie<<"|"<<dane[indeksOstaniegoAdresata].nazwisko<<"|"<<dane[indeksOstaniegoAdresata].telefon<<"|"<<dane[indeksOstaniegoAdresata].email<<"|"<<dane[indeksOstaniegoAdresata].adres<<"|"<<endl;
    cout<<"Dodano do pliku "<<dane[indeksOstaniegoAdresata].nazwisko<<endl;
    mojPlik.close();
}




void szukajAdresataPoImieniu(vector <Adresaci> dane)
{
    string imie;
    int wystapienia =0;
    cin.sync();
    cout<<"Podaj imie: ";
    getline(cin,imie);
    for(int i =0; i<dane.size(); i++)
    {
        if(dane[i].imie==imie)
        {
            wystapienia++;
            cout<<dane[i].idAdresata<<" "<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].telefon<<" "<<dane[i].email<<" "<<dane[i].adres<<endl;
        }
    }

    if(wystapienia==0)
    {
        cout<<"Nie znaleziono osoby o imieniu: "<<imie<<endl;
    }
    system("pause");

}


void szukajAdresataPoNazwisku(vector <Adresaci> dane)
{
    string nazwisko;
    int wystapienia =0;
    cin.sync();
    cout<<"Podaj nazwisko: ";
    getline(cin,nazwisko);
    for(int i =0; i<dane.size(); i++)
    {
        if(dane[i].nazwisko==nazwisko)
        {
            wystapienia++;
            cout<<dane[i].idAdresata<<" "<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].telefon<<" "<<dane[i].email<<" "<<dane[i].adres<<endl;
        }
    }

    if(wystapienia==0)
    {
        cout<<"Nie znaleziono osoby o naziwku: "<<nazwisko<<endl;
    }
    system("pause");

}

void wyswietlWszystkichAdresatow(vector <Adresaci> dane)
{
    int wystapienia =0;
    for(int i =0; i<dane.size(); i++)
    {
        wystapienia++;
        cout<<dane[i].idAdresata<<" "<<dane[i].imie<<" "<<dane[i].nazwisko<<" "<<dane[i].telefon<<" "<<dane[i].email<<" "<<dane[i].adres<<endl;
    }

    if(wystapienia==0)
    {
        cout<<"Uzytkownik nie ma dodanych zadnych adresatow"<<endl;
    }
    system("pause");
}

int wskazNumerIdAdresata()
{
    int wybranyNumerID;
    string numer;
    cout<<"Podaj numer ID uzytkownika do usuniecia/edytowania: ";
    cin.sync();
    getline(cin, numer);
    wybranyNumerID = zamienNaLiczbe(numer);
    return wybranyNumerID;
}



void plikBezUsunietegoAdresta (int idAdresata)
{
    fstream plikCalyAdresaci;
    fstream pliktymczasowy;
    string linia;
    vector <string> dane;
    int licznik =0;
    plikCalyAdresaci.open("Adresaci.txt", ios::in);
    pliktymczasowy.open("Adresaci_tymczasowy.txt", ios::out);
    while(getline(plikCalyAdresaci, linia, '|'))
    {
        dane.push_back(linia);
        licznik++;
        if(licznik==7)
        {
            int id = zamienNaLiczbe(dane[0]);
            if(idAdresata != id)
            {
                pliktymczasowy<<dane[0]<<"|"<<dane[1]<<"|"<<dane[2]<<"|"<<dane[3]<<"|"<<dane[4]<<"|"<<dane[5]<<"|"<<dane[6]<<"|";
            }
                dane.clear();
                licznik=0;
        }
    }
    plikCalyAdresaci.close();
    pliktymczasowy.close();
}


vector <Adresaci> WektorowoUsunAdresata (vector <Adresaci> dane, int usuwanyNumerID)
{

    int wystapienia=0;
    int numerWierszaIdAdresata;
    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        if(it -> idAdresata == usuwanyNumerID)
        {
            numerWierszaIdAdresata = it -> idAdresata;
            cout<<"Usuwam: "<<it -> nazwisko<<endl;
            Sleep(1000);
            dane.erase(it);
            wystapienia++;
            return dane;
        }
    }

    if(wystapienia==0)
    {
        cout<<"Nie ma Adrestata o ID: "<<usuwanyNumerID<<endl;
        Sleep(1500);
        return dane;
    }
}


void menuEdycjiVectoraAdresta()
{
    cout<<"Wybierz pole edycji: "<<endl;
    cout<<"1.Imie"<<endl;
    cout<<"2.Nazwisko"<<endl;
    cout<<"3.Telefon"<<endl;
    cout<<"4.Email"<<endl;
    cout<<"5.Adres"<<endl;

}



vector <Adresaci> wektorowoEdytujAdresta(vector <Adresaci> dane, int numerID)
{
    vector <int> uzywaneNumeryWierszy = zapisujNumeryIdWierszyZalogowanego(dane);
    int wystapienia =0;
    for(int i = 0; i<uzywaneNumeryWierszy.size(); i++)
    {
        if(numerID==uzywaneNumeryWierszy[i])
        {
            wystapienia++;
        }
    }
    if(wystapienia>0)
    {

    Adresaci daneAdresataDoPlikuTxt;
    for(vector <Adresaci>::iterator it=dane.begin(); it != dane.end(); it++)
    {

        if(it -> idAdresata == numerID)
        {

            char wybor;
            menuEdycjiVectoraAdresta();
            cin.sync();
            cin>>wybor;

            if(wybor=='1')
            {
                string imie;
                cout<<"Podaj nowe imie: ";
                cin.sync();
                getline(cin,imie);
                cout<<"zmieniono imie "<<it -> imie<<" na "<<imie<<endl;
                Sleep(1500);
                it -> imie = imie;
                system("cls");
            }

            if(wybor=='2')
            {
                string nazwisko;
                cout<<"Podaj nowe nazwisko: ";
                cin.sync();
                getline(cin,nazwisko);
                cout<<"Zamieniono nazwisko "<<it -> nazwisko<<" na "<<nazwisko<<endl;
                Sleep(1500);
                it -> nazwisko = nazwisko;
                system("cls");
            }

            if(wybor=='3')
            {
                string telefon;
                cout<<"POdaj nowy numer telefonu: ";
                cin.sync();
                getline(cin, telefon);
                cout<<"Zamieniono nr telefonu "<<it -> telefon<<" na "<<telefon<<endl;
                Sleep(1500);
                it -> telefon = telefon;
                system("cls");
            }

            if(wybor =='4')
            {
                string email;
                cout<<"POdaj nowy email: ";
                cin.sync();
                getline(cin, email);
                cout<<"Zmieniono adres email z: "<<it -> email<<" na "<<email<<endl;
                Sleep(1500);
                it -> email = email;
                system("cls");
            }

            if(wybor=='5')
            {
                string adres;
                cout<<"Podaj nowy adres: ";
                cin.sync();
                getline(cin, adres);
                cout<<"Zmieniono adres z"<<it -> adres<<" na "<<adres<<endl;
                Sleep(1500);
                it -> adres = adres;
                system("cls");
            }
            daneAdresataDoPlikuTxt.idAdresata = it -> idAdresata;
            daneAdresataDoPlikuTxt.idUzytkownika = it -> idUzytkownika;
            daneAdresataDoPlikuTxt.imie = it -> imie;
            daneAdresataDoPlikuTxt.nazwisko = it -> nazwisko;
            daneAdresataDoPlikuTxt.telefon = it -> telefon;
            daneAdresataDoPlikuTxt.email = it -> email;
            daneAdresataDoPlikuTxt.adres = it -> adres;
            zamienPLikiGLowne(numerID, daneAdresataDoPlikuTxt);
            zmienNazwePlikuTekstowego("Adresaci.txt", "Adresaci_tymczasowy.txt");

            return dane;
            break;
        }
    }
    }
    else
    {
        cout<<"Wybrany numer ID nie jest przypisany temu uzytkownikowi"<<endl;
        Sleep(1000);
        return dane;
    }

}


void zapiszZmianeHaslaDoPliku(vector <Uzytkownicy> dane)
{
    fstream mojPlik;
    mojPlik.open("Uzytkownicy.txt", ios::out);
    for(vector <Uzytkownicy>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        mojPlik<< it -> numerID<<"|"<< it -> nick<<"|"<< it -> haslo<<"|"<<endl;
    }
    mojPlik.close();
}



vector <Uzytkownicy> zmienHasloUzytkownika(vector <Uzytkownicy> dane, int numerId)
{
    for (vector <Uzytkownicy>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        if(it -> numerID == numerId)
        {
            string haslo;
            cout<<"Podaj nowe haslo:";
            cin.sync();
            getline(cin, haslo);
            cout<<"zmieniono stare haslo "<<it -> haslo<<" na "<<haslo<<endl;
            Sleep(1500);
            it -> haslo = haslo;
            return dane;
        }
    }
}

void zamienPLikiGLowne(int numerIdAdresata, Adresaci zmienianaOsoba)
{
    fstream adresat;
    fstream adresataTymczasowy;
    string linia;
    adresat.open("Adresaci.txt", ios::in);
    adresataTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);
    vector <string> dane;
    if(adresat.good()==false)
    {
        cout<<"Brak takiego pliku..."<<endl;
    }
    int licznik =0;
    while(getline(adresat,linia,'|'))
    {

        dane.push_back(linia);
        licznik++;
        if(licznik==7)
        {
            int adresataId = zamienNaLiczbe(dane[0]);
            int uzytkownikaId = zamienNaLiczbe(dane[1]);

            if(adresataId == zmienianaOsoba.idAdresata)
            {
                adresataTymczasowy<<"\n"<<zmienianaOsoba.idAdresata<<"|"<<zmienianaOsoba.idUzytkownika<<"|"<<zmienianaOsoba.imie<<"|"<<zmienianaOsoba.nazwisko<<"|"<<zmienianaOsoba.telefon<<"|"<<zmienianaOsoba.email<<"|"<<zmienianaOsoba.adres<<"|";

            }

            else
            {
                adresataTymczasowy<<dane[0]<<"|"<<dane[1]<<"|"<<dane[2]<<"|"<<dane[3]<<"|"<<dane[4]<<"|"<<dane[5]<<"|"<<dane[6]<<"|";

            }

                licznik=0;
                dane.clear();
        }
    }

    adresat.close();
    adresataTymczasowy.close();
}


void zmienNazwePlikuTekstowego(string nowaNazwaPliku, string staraNazwaPLiku)
{
    fstream nowyPlik, staryPlik;
    staryPlik.open(staraNazwaPLiku, ios::in);
    nowyPlik.open(nowaNazwaPliku, ios::out);
    string linia;
    while(getline(staryPlik, linia))
    {
        nowyPlik<<linia<<endl;
    }
    staryPlik.close();
    nowyPlik.close();

}


int main()
{
    vector <Uzytkownicy> daneUzytkownikow = wczytajDanePliku();
    int numerID = PrzydzielNumerID(daneUzytkownikow);
    cout<<"Liczba Osob w bazie: "<<daneUzytkownikow.size()<<endl;

    while(true)
    {

    char wybor;
    menuGlowne();
    cin>>wybor;
    if(wybor=='1')
    {
        int identyfikatorZalogowanego=-1;
        identyfikatorZalogowanego = logowanie(daneUzytkownikow);
        int NumerOstatniegoWolnegoRekordu = ostaniNumerAdresata()+1;
        system("cls");
        vector <Adresaci> bazaDanychZalogowanegoUzytkownika = ladowaniePoczatkowDanychZalogowanemu(identyfikatorZalogowanego);


        while(identyfikatorZalogowanego!=-1)
        {

            char OpcjeZalogowanego;
            cout<<"Wczytano "<<bazaDanychZalogowanegoUzytkownika.size()<<" pozycji"<<endl;
            menuZalogowanego();
            cin.sync();
            cin>>OpcjeZalogowanego;
            if(OpcjeZalogowanego=='1')
            {
                bazaDanychZalogowanegoUzytkownika = dodajAdresata(bazaDanychZalogowanegoUzytkownika, NumerOstatniegoWolnegoRekordu, identyfikatorZalogowanego);
                dodajDoPlikuAdresata(bazaDanychZalogowanegoUzytkownika);
                NumerOstatniegoWolnegoRekordu = ostaniNumerAdresata()+1;
                system("cls");

            }

            if(OpcjeZalogowanego=='2')
            {
                szukajAdresataPoImieniu(bazaDanychZalogowanegoUzytkownika);
                system("cls");
            }

            if(OpcjeZalogowanego=='3')
            {
                szukajAdresataPoNazwisku(bazaDanychZalogowanegoUzytkownika);
                system("cls");
            }

            if(OpcjeZalogowanego=='4')
            {
                wyswietlWszystkichAdresatow(bazaDanychZalogowanegoUzytkownika);
                system("cls");
            }

            if(OpcjeZalogowanego=='5')
            {
                int usuwaneIdAdresata = wskazNumerIdAdresata();
                vector <Adresaci> test = bazaDanychZalogowanegoUzytkownika;
                bazaDanychZalogowanegoUzytkownika = WektorowoUsunAdresata(test, usuwaneIdAdresata);
                plikBezUsunietegoAdresta(usuwaneIdAdresata);
                system("cls");
            }

            if(OpcjeZalogowanego=='6')
            {
                int edytowaneIdAdresta = wskazNumerIdAdresata();
                bazaDanychZalogowanegoUzytkownika = wektorowoEdytujAdresta(bazaDanychZalogowanegoUzytkownika, edytowaneIdAdresta);
                system("cls");
            }

            if(OpcjeZalogowanego=='7')
            {
                identyfikatorZalogowanego = identyfikatorZalogowanego;
                daneUzytkownikow = zmienHasloUzytkownika(daneUzytkownikow, identyfikatorZalogowanego);
                zapiszZmianeHaslaDoPliku(daneUzytkownikow);
                system("cls");
            }

            if(OpcjeZalogowanego=='8')
            {
                cout<<"Wylogowywanie..."<<endl;
                Sleep(1000);
                identyfikatorZalogowanego=-1;
                system("cls");

            }

        }
    }
    if(wybor=='2')
    {
        daneUzytkownikow = rejestrujUzytkownika(daneUzytkownikow);
        numerID = PrzydzielNumerID(daneUzytkownikow);
        dodajDoPLikuUzytkownika(daneUzytkownikow);
        system("cls");
    }

    if(wybor=='3')
    {
        exit(0);
    }

    }
    return 0;
}
