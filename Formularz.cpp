#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

bool zaloguj();
void gotoxy(int x, int y);
void wyczyscEkran();
void wyswietlMenu();
void listaObejrzanychFilmow();
void dodajFilm();
void usunFilm();
void pasek(int x, int y);

int main() {
    int proba = 0;
    const int maxProby = 3;
    bool wyswietlonoIntro = false;

    while (proba < maxProby)
    {
        if (!wyswietlonoIntro)
        {
            gotoxy(50, 0);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
            cout << "FILMY\n";
            pasek(10, 500);
            wyczyscEkran();
            wyswietlonoIntro = true;
        }

        if (zaloguj())
        {
            wyczyscEkran();
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Witaj uzytkowniku w bazie filmow\n";

            int wybor;
            do
            {
                wyswietlMenu();
                cout << "Twoj wybor (1-4): ";
                cin >> wybor;
                switch (wybor) {
                case 1:
                    listaObejrzanychFilmow();
                    break;
                case 2:
                    dodajFilm();
                    break;
                case 3:
                    usunFilm();
                    break;
                case 4:
                    cout << "Dziekujemy za skorzystanie z programu.\n";
                    cout << "Zapisywanie dokonanych zmian...\n";
                    pasek(10, 800);
                    break;
                default:
                    cout << "Nieprawidlowy wybor. Sprobuj jeszcze raz.\n";
                    pasek(10, 500);
                }
                wyczyscEkran();
            } while (wybor != 4);
            break;
        }
        else
        {
            proba++;
            if (proba < maxProby)
            {
                wyczyscEkran();
                cout << "Blad logowania. Nieprawidlowy login lub haslo. Pozostalo prob: " << maxProby - proba << endl;
                pasek(10, 750);
                wyczyscEkran();
            }
            else
            {
                wyczyscEkran();
                cout << "Przekroczono maksymalna liczbe prob. Program zostanie zamkniety.\n";
                Sleep(1000);
                break;
            }
        }
    }

    return 0;
}

bool zaloguj()
{
    string login;
    string haslo;

    gotoxy(50, 0);
    cout << "LOGOWANIE \n";
    cout << "Login: ";
    cin >> login;

    cout << "Haslo: ";
    char znak;
    haslo = "";
    while (true)
    {
        znak = _getch();
        if (znak == 13)
        {
            break;
        } 
        haslo.push_back(znak); 
        cout << "*"; 
    }

    if (login == "admin" && haslo == "admin")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void gotoxy(int x, int y)
{
    COORD c = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void wyczyscEkran()
{
    system("cls");
}

void wyswietlMenu()
{
    gotoxy(50, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    cout << "MENU" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "[1] \t Lista obejrzanych filmow" << endl;
    cout << "[2] \t Dodaj film" << endl;
    cout << "[3] \t Usun film" << endl;
    cout << "[4] \t Wyjscie" << endl;
}

void listaObejrzanychFilmow()
{
    wyczyscEkran();
    gotoxy(40, 0);
    cout << "LISTA OBEJRZANYCH FILMOW \n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | BACKGROUND_RED);
    cout << "NUMER \t TYTUL \t ROK PRODUKCJI\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "1. \t Avengers \t 2012\n";
    cout << "2. \t Diuna \t \t 2021\n";
    cout << "3. \t Napoleon \t 2023\n";

    cout << "\nNacisnij dowolny klawisz, aby wrocic do menu.\n";
    _getch();
}

void dodajFilm()
{
    wyczyscEkran();
    string tytul;
    int rok_produkcji;
    gotoxy(50, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | BACKGROUND_RED);
    cout << "Podaj dane filmu: \n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Tytul: ";
    cin >> tytul;
    cout << "Rok produkcji: ";
    cin >> rok_produkcji;
    cout << "Trwa zapisywanie informacji do bazy danych...\n";
    pasek(10, 900);
    cout << endl;
    cout << "Baza danych uaktualniona.\n";
    Sleep(3000);
}

void usunFilm()
{
    wyczyscEkran();
    int nr;
    char pewnosc;
    
    cout << "Podaj numer filmu do usuniecia: ";
    cin >> nr;

    do 
    {
        cout << "Czy jestes pewny? (t/n): ";
        cin >> pewnosc;

        if (pewnosc == 't' || pewnosc == 'T')
        {
            cout << "Trwa usuwanie... \n";
            pasek(10, 650);
            cout << endl;
            cout << "Film usuniety. \n";
            Sleep(3000);
        }
        else if (pewnosc == 'n' || pewnosc == 'N')
        {
            cout << "Operacja anulowana. \n";
            Sleep(3000);
        }
        else
        {
            cout << "Niepoprawna odpowiedz. Uzyj 't' lub 'n'.\n";
        }
    } while (pewnosc != 't' && pewnosc != 'T' && pewnosc != 'n' && pewnosc != 'N');
}

void pasek(int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        cout << char(187) << char(200);
        Sleep(y);
    }
}
