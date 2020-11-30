#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<windows.h>
#include <cstdio>

using namespace std;


string plikGlowny = "Adresaci.txt";
string plikPomocniczy = "Adresaci_tymczasowy.txt";

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

void zmienNazwePlikuTekstowego();




int zamienNaLiczbe(string tekst)
{
    stringstream ss(tekst);
    int liczba;
    ss>>liczba;
    return liczba;
}

string zamienNaTekst(int liczba)
{
    stringstream ss;
    ss<<liczba;
    string tekst;
    ss>>tekst;
    return tekst;
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



int ostaniUzytyNumerAdresataPliku()
{
    fstream mojPlik;
    vector <string> numeryAdresatow;
    vector <string> tymczasowy;
    mojPlik.open(plikGlowny.c_str(),ios::in);
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
            return 1;
        }
        else
        {
            int numery = zamienNaLiczbe(numeryAdresatow[numeryAdresatow.size()-1]);
            return numery+1;
        }
    }
    else
    {
        return 1;
    }
    mojPlik.close();
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

string wpiszTekstZklawiatury()
{
    string wynik;
    cin.sync();
    getline(cin, wynik);
    return wynik;
}

void dodajAdresataDoWektora(vector <Adresaci> &dane, int &idUzytkownika)
{
    Adresaci daneDodawanejOsoby;
    daneDodawanejOsoby.idAdresata = ostaniUzytyNumerAdresataPliku();

    cout<<"Imie: ";
    daneDodawanejOsoby.imie = wpiszTekstZklawiatury();
    cout<<"Nazwisko: ";
    daneDodawanejOsoby.nazwisko = wpiszTekstZklawiatury();
    cout<<"Telefon: ";
    daneDodawanejOsoby.telefon = wpiszTekstZklawiatury();
    cout<<"Email: ";
    daneDodawanejOsoby.email = wpiszTekstZklawiatury();
    cout<<"Adres: ";
    daneDodawanejOsoby.adres = wpiszTekstZklawiatury();
    daneDodawanejOsoby.idUzytkownika = idUzytkownika;

    dane.push_back(daneDodawanejOsoby);


}


void dodajDoPlikuAdresata(vector <Adresaci> &dane)
{
    fstream mojPlik;
    mojPlik.open(plikGlowny.c_str(), ios::out | ios::app);
    mojPlik<<dane.back().idAdresata<<"|"<<dane.back().idUzytkownika<<"|"<<dane.back().imie<<"|"<<dane.back().nazwisko<<"|"<<dane.back().telefon<<"|"<<dane.back().email<<"|"<<dane.back().adres<<"|"<<endl;
    mojPlik.close();
}



void szukajAdresataPoImieniu(vector <Adresaci> &dane)
{
    string imie;
    int wystapienia =0;
    cin.sync();
    cout<<"Podaj imie: ";
    imie = wpiszTekstZklawiatury();
    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        if(it -> imie==imie)
        {
            wystapienia++;
            cout<<it -> idAdresata<<" "<<it -> imie<<" "<<it -> nazwisko<<" "<<it -> telefon<<" "<<it -> email<<" "<<it -> adres<<endl;
        }
    }

    if(wystapienia==0)
    {
        cout<<"Nie znaleziono osoby o imieniu: "<<imie<<endl;
    }
    system("pause");

}


void szukajAdresataPoNazwisku(vector <Adresaci> &dane)
{
    string nazwisko;
    int wystapienia =0;
    cin.sync();
    cout<<"Podaj nazwisko: ";
    nazwisko = wpiszTekstZklawiatury();

    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        if(it -> nazwisko == nazwisko)
        {
            wystapienia++;
            cout<<it -> idAdresata<<" "<<it -> imie<<" "<<it -> nazwisko<<" "<<it -> telefon<<" "<<it -> email<<" "<<it -> adres<<endl;
        }
    }

    if(wystapienia==0)
    {
        cout<<"Nie znaleziono osoby o naziwku: "<<nazwisko<<endl;
    }
    system("pause");

}

void wyswietlWszystkichAdresatow(vector <Adresaci> &dane)
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



vector <int> zapisujNumeryIdWierszyZalogowanego(vector <Adresaci> &dane)
{
    vector <int> listaUzywanychNumerowWierszy;
    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        listaUzywanychNumerowWierszy.push_back( it -> idAdresata);
    }
    return listaUzywanychNumerowWierszy;
}


void plikBezUsunietegoAdresta (int &idAdresata)
{
    fstream plikCalyAdresaci;
    fstream pliktymczasowy;
    string linia;
    vector <string> dane;
    int licznik =0;
    plikCalyAdresaci.open(plikGlowny.c_str(), ios::in);
    pliktymczasowy.open(plikPomocniczy.c_str(), ios::out);
    while(getline(plikCalyAdresaci, linia, '|'))
    {
        dane.push_back(linia);
        licznik++;
        if(licznik==7)
        {
            int id = zamienNaLiczbe(dane[0]);
            if(idAdresata != id)
            {
                pliktymczasowy<<dane[0]+"|"+dane[1]+"|"+dane[2]+"|"+dane[3]+"|"+dane[4]+"|"+dane[5]+"|"+dane[6]+"|"<<endl;
            }
                dane.clear();
                licznik=0;
        }
    }
    plikCalyAdresaci.close();
    pliktymczasowy.close();
}



void zmienNazwePlikuTekstowego()
{
    remove(plikGlowny.c_str());

    rename(plikPomocniczy.c_str(), plikGlowny.c_str());
}


void usuwanieAdresataWektor(vector <Adresaci> &dane, int &numerID)
{
    if(! dane.empty())
    {

    vector <int> uzywaneNumeryIdAdresata = zapisujNumeryIdWierszyZalogowanego(dane);
    bool czyAdresastIstnieje = false;
    for(vector <int>::iterator n = uzywaneNumeryIdAdresata.begin(); n != uzywaneNumeryIdAdresata.end(); n++)
    {
        if(*n == numerID)
        {
            for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
            {
                if(it -> idAdresata == numerID)
                {
                    czyAdresastIstnieje = true;
                    cout<<"Usuwam: "<<it -> nazwisko<<endl;
                    Sleep(1500);
                    dane.erase(it);
                    plikBezUsunietegoAdresta(numerID);
                    zmienNazwePlikuTekstowego();
                    break;

                }
            }

        }
    }
    if(czyAdresastIstnieje==false)
    {
        cout<<"Adresat o takim ID nie istnieje w twojej bazie"<<endl;
        Sleep(1500);
    }

    }
    else
    {
        cout<<"Twoja Baza Danych jest pusta"<<endl;
        Sleep(1500);
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

void zapiszWszystkichAdresatowDoPliku(vector <Adresaci> &dane)
{
    fstream plikAdresaci;
    string linia="";
    plikAdresaci.open("lol.txt", ios::out);

    for(vector <Adresaci>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        linia += zamienNaTekst(it -> idAdresata) +"|";
        linia += zamienNaTekst(it -> idUzytkownika)+"|";
        linia += it -> imie+"|";
        linia += it -> nazwisko + "|";
        linia += it -> telefon+"|";
        linia += it -> email+"|";
        linia += it -> adres+"|";

        plikAdresaci<<linia<<endl;
        linia="";
    }

}


void zapiszEdytowanegoAdresataDoPlikuPomocniczego(string liniaEdytowanegoAdresata, int idAdresata)
{
    fstream calyPlikAdresaci, tymczasowyPlikAdresaci;
    string linia;
    calyPlikAdresaci.open(plikGlowny.c_str(), ios::in);
    tymczasowyPlikAdresaci.open(plikPomocniczy.c_str(), ios::out);
    vector <string> tymczasowy;
    int licznik =0;
    while(getline(calyPlikAdresaci, linia, '|'))
    {
        if(linia.size()>0)
        {

        tymczasowy.push_back(linia);
        }
        licznik++;
        if(licznik==7)
        {
            licznik=0;
            int numerAdresata = zamienNaLiczbe(tymczasowy[0]);
            if(numerAdresata==idAdresata)
            {
                tymczasowyPlikAdresaci<<liniaEdytowanegoAdresata<<endl;
            }
            else
            {
                string tekst = tymczasowy[0]+"|"+tymczasowy[1]+"|"+tymczasowy[2]+"|"+tymczasowy[3]+"|"+tymczasowy[4]+"|"+tymczasowy[5]+"|"+tymczasowy[6]+"|";
                tymczasowyPlikAdresaci<< tekst<<endl;
            }
            tymczasowy.clear();

        }
    }
    tymczasowyPlikAdresaci.close();
    calyPlikAdresaci.close();


}



void edytujAdresata(vector <Adresaci> &dane, int idAdresata)
{
    vector <int> uzywaneNumeryIdAdresata = zapisujNumeryIdWierszyZalogowanego(dane);
    bool adresatIstnieje = false;
    int opcja = -2;
    for(vector <int>::iterator it = uzywaneNumeryIdAdresata.begin(); it != uzywaneNumeryIdAdresata.end(); it++)
    {
        if(*it == idAdresata)
        {
            cout<<"JESTES TRUE"<<endl;
            system("pause");
        adresatIstnieje = true;

        }

    }

    if(adresatIstnieje ==true)
    {
        for(vector <Adresaci>::iterator n = dane.begin(); n != dane.end(); n++)
        {
            if(n -> idAdresata == idAdresata)
            {
                menuEdycjiVectoraAdresta();
                char wybor;
                cin.sync();
                cin>>wybor;

                if(wybor=='1')
                {
                    cout<<"Podaj nowe Imie: ";
                    string imie = wpiszTekstZklawiatury();
                    n -> imie = imie;
                }
                if(wybor=='2')
                {
                    cout<<"Podaj nowe Nazwisko: ";
                    string nazwisko = wpiszTekstZklawiatury();
                    n -> nazwisko = nazwisko;
                }
                if(wybor =='3')
                {
                    cout<<"Podaj nowy Telefon: ";
                    string telefon = wpiszTekstZklawiatury();
                    n -> telefon = telefon;
                }
                if(wybor =='4')
                {
                    cout<<"Podaj nowy Email: ";
                    string email = wpiszTekstZklawiatury();
                    n -> email = email;
                }
                if(wybor=='5')
                {
                    cout<<"Podaj nowy Adres: ";
                    string adres = wpiszTekstZklawiatury();
                    n -> adres = adres;
                }
                string linia = zamienNaTekst( n -> idAdresata)+"|"+zamienNaTekst( n -> idUzytkownika)+"|"+ n -> imie+"|"+ n -> nazwisko+"|"+ n -> telefon+"|"+ n -> email +"|"+ n -> adres+'|';
                zapiszEdytowanegoAdresataDoPlikuPomocniczego(linia,idAdresata);
                zmienNazwePlikuTekstowego();
            }
        }
    }
    if(adresatIstnieje==false)
    {
        cout<<"Adresat o takim ID nie istnieje"<<endl;
        Sleep(1500);
    }

}


void zapiszZmianeHaslaDoPliku(vector <Uzytkownicy> &dane)
{
    fstream mojPlik;
    mojPlik.open("Uzytkownicy.txt", ios::out);
    for(vector <Uzytkownicy>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        mojPlik<< it -> numerID<<"|"<< it -> nick<<"|"<< it -> haslo<<"|"<<endl;
    }
    mojPlik.close();
}



void zmienHasloUzytkownika(vector <Uzytkownicy> &dane, int numerId)
{
    bool nickIstnieje = false;
    for (vector <Uzytkownicy>::iterator it = dane.begin(); it != dane.end(); it++)
    {
        if(it -> numerID == numerId)
        {
            nickIstnieje = true;
            string haslo;
            cout<<"Podaj nowe haslo:";
            cin.sync();
            getline(cin, haslo);
            cout<<"zmieniono stare haslo "<<it -> haslo<<" na "<<haslo<<endl;
            Sleep(1500);
            it -> haslo = haslo;
        }
    }
    if(nickIstnieje==false)
    {
        cout<<"Uzytkownik o takim ID nie istieje"<<endl;
        Sleep(1000);
    }
    return dane;
}


void usunSpacjePliku()
{
    fstream aktualnyPlik, nowyPlik;

    aktualnyPlik.open(plikGlowny.c_str(), ios::in);
    nowyPlik.open(plikPomocniczy.c_str(), ios::out);
    string linia;
    while(getline(aktualnyPlik, linia))
    {
        if(linia.size()>6)
        {
            nowyPlik<<linia<<endl;

        }

    }


    nowyPlik.close();
    aktualnyPlik.close();

}


int main()
{
    vector <Uzytkownicy> daneZarejestrowanychUzytkownikow = wczytajDanePliku();

    while(true)
    {
        menuGlowne();
        char wybor;
        cout<<"Wybierz opcje: ";
        cin.sync();
        cin>>wybor;
        if(wybor=='1')
        {
            int numerIdZalogowanegoUzytkownika =-1;
            numerIdZalogowanegoUzytkownika = logowanie(daneZarejestrowanychUzytkownikow);
            system("cls");
            vector <Adresaci> dodaniAdresaciZalogowanego = ladowaniePoczatkowDanychZalogowanemu(numerIdZalogowanegoUzytkownika);
            while(numerIdZalogowanegoUzytkownika != -1)
            {
                cout<<"Liczba dodanych uzytkownikow: "<<dodaniAdresaciZalogowanego.size()<<endl;
                menuZalogowanego();
                char wyborOpcjiZalogowanego;
                cin.sync();
                cout<<"Wyberz opcje; ";
                cin>>wyborOpcjiZalogowanego;
                if(wyborOpcjiZalogowanego=='1')
                {
                    dodajAdresataDoWektora(dodaniAdresaciZalogowanego, numerIdZalogowanegoUzytkownika);
                    dodajDoPlikuAdresata(dodaniAdresaciZalogowanego);
                    system("cls");
                }
                if(wyborOpcjiZalogowanego=='2')
                {
                    szukajAdresataPoImieniu(dodaniAdresaciZalogowanego);
                    system("cls");
                }

                if(wyborOpcjiZalogowanego=='3')
                {
                    szukajAdresataPoNazwisku(dodaniAdresaciZalogowanego);
                    system("cls");
                }

                if(wyborOpcjiZalogowanego=='4')
                {
                    wyswietlWszystkichAdresatow(dodaniAdresaciZalogowanego);
                    system("cls");
                }
                if(wyborOpcjiZalogowanego=='5')
                {
                    string liczba;
                    cout<<"Podaj ID do usuniecia: ";
                    liczba = wpiszTekstZklawiatury();
                    int numerID = zamienNaLiczbe(liczba);
                    usuwanieAdresataWektor(dodaniAdresaciZalogowanego, numerID);
                    system("cls");
                }
                if(wyborOpcjiZalogowanego=='6')
                {
                    string liczba;
                    cout<<"Podaj ID do Edycji: ";
                    liczba = wpiszTekstZklawiatury();
                    int numerID = zamienNaLiczbe(liczba);
                    edytujAdresata(dodaniAdresaciZalogowanego, numerID);
                    zapiszWszystkichAdresatowDoPliku(dodaniAdresaciZalogowanego);
                    system("cls");
                }
                if(wyborOpcjiZalogowanego=='7')
                {
                    zmienHasloUzytkownika(daneZarejestrowanychUzytkownikow, numerIdZalogowanegoUzytkownika);
                    zapiszZmianeHaslaDoPliku(daneZarejestrowanychUzytkownikow);
                    system("cls");
                }
                if(wyborOpcjiZalogowanego=='8')
                {
                    cout<<"Wylogowywanie..."<<endl;
                    Sleep(1000);
                    system("cls");
                    numerIdZalogowanegoUzytkownika = -1;
                }

            }
                usunSpacjePliku();
                zmienNazwePlikuTekstowego();
        }

        if(wybor=='2')
        {
            daneZarejestrowanychUzytkownikow = rejestrujUzytkownika(daneZarejestrowanychUzytkownikow);
            dodajDoPLikuUzytkownika(daneZarejestrowanychUzytkownikow);
            system("cls");
        }

        if(wybor=='3')
        {
            cout<<"Zamykanie programu"<<endl;
            Sleep(1000);
            exit(0);
        }
    }



    return 0;
}
