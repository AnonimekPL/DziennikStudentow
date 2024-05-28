#include "funkcje.h"

int main(const int argc, const char* argv[])
{
	BazaDanychUczelni uczelnia;
	if (not czytajPlik(uczelnia))
		return 0;

	cout << "Jesli chcesz rozpoczac wpisz 1, jesli zakonczyc wpisz 0: ";
	int bol;
	cin >> bol;
	while (bol == 1)
	{
		menu(uczelnia);
		cout << "Jesli chcesz kontynuowac wpisz 1, jesli zakonczyc wpisz 0: ";
		cin >> bol;

	}

	Podsumowanie_Semestru(uczelnia);


	likwidacjaGrup(uczelnia);


	zapiszDoPliku(uczelnia);
	return 0;
}