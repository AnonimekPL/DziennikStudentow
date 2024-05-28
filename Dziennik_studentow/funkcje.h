/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H


#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/** Funkcja odczytujaca dane z pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli odczytano dane z pliku*/
static inline bool czytajPlik(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja usuwajaca studentow ktorzy uzyskali ocene ponizej 3
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static inline void Podsumowanie_Semestru(map<int, map<string, map<string, vector<float> > > >& uczelnia);


/**Funkcja podajaca: srednia, minimalna, maksymalna ocena z przedmiotow, srednia ocen dla kazdej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static inline void raportPrzedmiotow(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja podajaca: grupe, oceny z przedmiotow, na tle grupy danego ucznia
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static inline void raportUcznia(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja podajaca: liczbe studentow w grupie, srednia ocen, srednia ocen dla kazdego przedmiotu, najwyzsza srednia w grupie
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void raportGrup(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja edytujaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void edytujOcene(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja dodajaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void dodajOcene(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja tworzaca pusta grupe
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void dodajGrupe(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja usuwajaca grupe ze studentami
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void usunGrupe(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja usuwajaca grupe z przeniesieniem studentow do innych grup
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void usunGrupePRZ(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja umozliwiajaca dodanie studenta do podanej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void dodajStudenta(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja umozliwiajaca usuniecie studenta z danej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void usunStudenta(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja pytajaca sie co zrobic ze zmienna "uczelnia"
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void menu(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja wyrownujaca ilosc grup, aby maksymalnie w grp bylo 30 osob
@param uczelnia zmienna przechowujaca dane na temat studentow*/
static void likwidacjaGrup(map<int, map<string, map<string, vector<float> > > >& uczelnia);

/**Funkcja zapisujaca dane do pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli zapisano dane z pliku */
static bool zapiszDoPliku(map<int, map<string, map<string, vector<float> > > >& uczelnia);

#endif