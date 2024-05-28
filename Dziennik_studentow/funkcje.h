/** @file */

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

using BazaDanychUczelni = map<int, map<string, map<string, vector<float>>>>;

/** Funkcja odczytujaca dane z pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli odczytano dane z pliku*/
bool czytajPlik(BazaDanychUczelni& uczelnia);

/**Funkcja usuwajaca studentow ktorzy uzyskali ocene ponizej 3
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void Podsumowanie_Semestru(BazaDanychUczelni& uczelnia);


/**Funkcja podajaca: srednia, minimalna, maksymalna ocena z przedmiotow, srednia ocen dla kazdej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportPrzedmiotow(BazaDanychUczelni& uczelnia);

/**Funkcja podajaca: grupe, oceny z przedmiotow, na tle grupy danego ucznia
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportUcznia(BazaDanychUczelni& uczelnia);

/**Funkcja podajaca: liczbe studentow w grupie, srednia ocen, srednia ocen dla kazdego przedmiotu, najwyzsza srednia w grupie
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportGrup(BazaDanychUczelni& uczelnia);

/**Funkcja edytujaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void edytujOcene(BazaDanychUczelni& uczelnia);

/**Funkcja dodajaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajOcene(BazaDanychUczelni& uczelnia);

/**Funkcja tworzaca pusta grupe
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajGrupe(BazaDanychUczelni& uczelnia);

/**Funkcja usuwajaca grupe ze studentami
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunGrupe(BazaDanychUczelni& uczelnia);

/**Funkcja usuwajaca grupe z przeniesieniem studentow do innych grup
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunGrupePRZ(BazaDanychUczelni& uczelnia);

/**Funkcja umozliwiajaca dodanie studenta do podanej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajStudenta(BazaDanychUczelni& uczelnia);

/**Funkcja umozliwiajaca usuniecie studenta z danej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunStudenta(BazaDanychUczelni& uczelnia);

/**Funkcja pytajaca sie co zrobic ze zmienna "uczelnia"
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void menu(BazaDanychUczelni& uczelnia);

/**Funkcja wyrownujaca ilosc grup, aby maksymalnie w grp bylo 30 osob
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void likwidacjaGrup(BazaDanychUczelni& uczelnia);

/**Funkcja zapisujaca dane do pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli zapisano dane z pliku */
bool zapiszDoPliku(BazaDanychUczelni& uczelnia);
