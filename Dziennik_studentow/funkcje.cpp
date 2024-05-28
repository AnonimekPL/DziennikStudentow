/** @file */
#include "funkcje.h"

/** Funkcja odczytujaca dane z pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli odczytano dane z pliku*/
bool czytajPlik(BazaDanychUczelni& uczelnia) {
	ifstream plik("dane.dat");

	if (plik.good())
	{

		string linia, nazwisko;
		int grupa;
		while (getline(plik, linia))
		{
			stringstream ss;
			ss << linia;

			string x;
			ss >> x;
			if (x == "GRUPA")
			{
				ss >> grupa;
				uczelnia[grupa] = map<string, map<string, vector<float> > >(); //konstruktor
			}
			else if (x == "nazwisko")
			{
				ss >> nazwisko;
				uczelnia[grupa][nazwisko] = map<string, vector<float> >();
			}
			else
			{

				uczelnia[grupa][nazwisko][x] = vector<float>();
				float ocena;
				while (ss >> ocena) {
					uczelnia[grupa][nazwisko][x].push_back(ocena);
				}
			}
		}

		return true;
	}
	else
	{
		cerr << "Nie udalo sie odczytac pliku wejsciowego!\n";
		return false;
	}

	plik.close();
}

/**Funkcja usuwajaca studentow ktorzy uzyskali ocene ponizej 3
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void Podsumowanie_Semestru(BazaDanychUczelni& uczelnia)
{
	map<int, vector<string>> naz;
	for (auto&& grupa : uczelnia) {
		for (auto&& nazwisko : grupa.second) {



			for (auto&& przedmiot : nazwisko.second) {
				float sum = 0;
				if (przedmiot.second.size() == 0)
				{
					naz[grupa.first].push_back(nazwisko.first);
					break;
				}
				for (int i = 0; i < przedmiot.second.size(); i++)
				{
					sum = sum + przedmiot.second[i];

				}
				sum = sum / przedmiot.second.size();
				if (sum < 3.0)
				{
					naz[grupa.first].push_back(nazwisko.first);
					break;
				}
			}

		}
	}
	for (auto&& grupa : naz)
	{
		for (auto& nazwisko : grupa.second)
		{
			uczelnia[grupa.first].erase(nazwisko);
		}

	}
}

/**Funkcja podajaca: srednia, minimalna, maksymalna ocena z przedmiotow, srednia ocen dla kazdej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportPrzedmiotow(BazaDanychUczelni& uczelnia)
{
	map < string, vector<float>> przedmioty;
	for (auto& grupa : uczelnia)
	{
		for (auto& nazwisko : grupa.second)
		{
			for (auto& przedmiot : nazwisko.second)
			{
				for (int i = 0; i < przedmiot.second.size(); i++)
				{
					przedmioty[przedmiot.first].push_back(przedmiot.second[i]);
				}
			}
		}
	}
	for (auto& przedmiot : przedmioty)
	{
		int min = 7;
		int max = 0;
		float sum = 0;
		cout << "Przedmiot: " << przedmiot.first << endl;
		for (int i = 0; i < przedmiot.second.size(); i++)
		{
			if (min > przedmiot.second[i])
			{
				min = przedmiot.second[i];
			}
			if (max < przedmiot.second[i])
			{
				max = przedmiot.second[i];
			}
			sum = sum + przedmiot.second[i];
		}
		cout << "Minimalna ocena: " << min << endl;
		cout << "Maksymalna ocena: " << max << endl;

		sum = sum / przedmiot.second.size();
		cout << "srednia: " << setprecision(3) << sum << endl << "--------------------------------" << endl;

	}
}
/**Funkcja podajaca: grupe, oceny z przedmiotow, na tle grupy danego ucznia
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportUcznia(BazaDanychUczelni& uczelnia)
{
	string nazwisko;
	int grp = 0;
	float sum_Sr_ucznia = 0;
	cout << "Podaj nazwisko ucznia";
	cin >> nazwisko;
	for (auto& grupa : uczelnia)
	{
		for (auto& naz : grupa.second)
		{

			if (naz.first == nazwisko)
			{
				grp = grupa.first;
				cout << "Grupa: " << grp << endl;
				for (auto&& przedmiot : naz.second)
				{
					float sum = 0;
					if (przedmiot.second.size() != 0)
					{
						for (int i = 0; i < przedmiot.second.size(); i++)
						{
							sum = sum + przedmiot.second[i];
						}
						sum = sum / przedmiot.second.size();
					}

					sum_Sr_ucznia = sum_Sr_ucznia + sum;
					cout << przedmiot.first << ": " << sum << endl;
				}
				sum_Sr_ucznia = sum_Sr_ucznia / size(naz.second);
			}
		}

	}
	for (auto&& grupa : uczelnia)
	{
		if (grupa.first == grp)
		{
			float srednia_Ocen = 0;
			for (auto& nazwisko : grupa.second) {

				float sum_Sr = 0;
				for (auto& przedmiot : nazwisko.second) {
					float sum = 0;
					if (przedmiot.second.size() != 0)
					{
						for (int i = 0; i < przedmiot.second.size(); i++)
						{
							sum = sum + przedmiot.second[i];

						}
						sum = sum / przedmiot.second.size();
					}



					sum_Sr = sum_Sr + sum;
				}
				sum_Sr = sum_Sr / size(nazwisko.second);


				srednia_Ocen = srednia_Ocen + sum_Sr;


			}
			srednia_Ocen = srednia_Ocen / size(grupa.second);
			if (sum_Sr_ucznia >= srednia_Ocen)
			{
				srednia_Ocen = sum_Sr_ucznia - srednia_Ocen;
				if (srednia_Ocen >= 1)
				{
					cout << "Uczen ma wieksza srednia od sredniej klasy o:  " << setprecision(3) << srednia_Ocen << endl;
				}
				else
				{
					cout << "Uczen ma wieksza srednia od sredniej klasy o:  " << setprecision(2) << srednia_Ocen << endl;
				}
			}
			else
			{
				srednia_Ocen = srednia_Ocen - sum_Sr_ucznia;
				if (srednia_Ocen >= 1)
				{
					cout << "Uczen ma mniejsza srednia od sredniej klasy o:  " << setprecision(3) << srednia_Ocen << endl;
				}
				else
				{
					cout << "Uczen ma mniejsza srednia od sredniej klasy o:  " << setprecision(2) << srednia_Ocen << endl;
				}

			}

		}
	}
}
/**Funkcja podajaca: liczbe studentow w grupie, srednia ocen, srednia ocen dla kazdego przedmiotu, najwyzsza srednia w grupie
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void raportGrup(BazaDanychUczelni& uczelnia)
{
	for (auto& grupa : uczelnia) {
		//	map<string, vector<float> > srednia_Prz;
		float srednia_Ocen = 0;
		float max = 0;

		cout << "Dla grupy: " << grupa.first << endl;
		cout << "Ilosc osob: " << size(grupa.second) << endl;
		for (auto&& nazwisko : grupa.second) {


			//vector<float> srednia_Ucznia;
			float sum_Sr = 0;
			for (auto&& przedmiot : nazwisko.second) {
				float sum = 0;
				if (przedmiot.second.size() != 0)
				{
					for (int i = 0; i < przedmiot.second.size(); i++)
					{
						sum = sum + przedmiot.second[i];

					}
					sum = sum / przedmiot.second.size();
				}



				sum_Sr = sum_Sr + sum;
			}
			sum_Sr = sum_Sr / size(nazwisko.second);
			if (max < sum_Sr)
			{
				max = sum_Sr;
			}
			//cout<<sum_Sr<< endl;
			//cout << "----------------------"<<endl ;
			srednia_Ocen = srednia_Ocen + sum_Sr;


		}
		srednia_Ocen = srednia_Ocen / size(grupa.second);
		cout << "Srednia ocen: " << setprecision(3) << srednia_Ocen << endl;
		cout << "Najwyzsza srednia w grp: " << setprecision(3) << max; // round
		cout << endl << "-----------------------------------------" << endl;
	}
}
/**Funkcja edytujaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void edytujOcene(BazaDanychUczelni& uczelnia)
{
	//int x;
	int nr, nr_oceny;
	float ocena;
	string nazwisko, przedmiot;
	cout << "Podaj nr grupy: ";
	cin >> nr;
	for (auto& grp : uczelnia)
	{
		if (grp.first == nr)
		{
			cout << endl << "Podaj nazwisko: ";
			cin >> nazwisko;
			for (auto& naz : grp.second)
			{
				if (naz.first == nazwisko)
				{
					cout << endl << "Podaj przedmiot: ";
					cin >> przedmiot;
					for (int i = 0; i < size(naz.second[przedmiot]); i++)
					{
						cout << "ocena: " << naz.second[przedmiot][i] << " Kliknij -> " << i << endl;
					}
					cin >> nr_oceny;
					cout << "Podaj na jaka ocene chcesz zmienic: ";
					cin >> ocena;
					uczelnia[nr][nazwisko][przedmiot][nr_oceny] = ocena;

				}
			}

		}

	}


}

/**Funkcja dodajaca ocene ucznia z danego przedmiotu
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajOcene(BazaDanychUczelni& uczelnia)
{
	int nr;
	float ocena;
	string nazwisko, przedmiot;
	cout << "Podaj nr grupy: ";
	cin >> nr;
	for (auto& grp : uczelnia)
	{
		if (grp.first == nr)
		{
			cout << endl << "Podaj nazwisko: ";
			cin >> nazwisko;
			for (auto& naz : grp.second)
			{
				if (naz.first == nazwisko)
				{
					cout << endl << "Podaj przedmiot: ";
					cin >> przedmiot;
					cout << endl << "Podaj ocene: ";
					cin >> ocena;
					uczelnia[nr][nazwisko][przedmiot].push_back(ocena);
				}
			}

		}

	}


}

/**Funkcja tworzaca pusta grupe
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajGrupe(BazaDanychUczelni& uczelnia)
{
	cout << "Grupe o jakim numerze chcesz dodac?" << endl;
	int nr;
	cin >> nr;
	uczelnia[nr] = map<string, map<string, vector<float> > >();
}

/**Funkcja usuwajaca grupe ze studentami
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunGrupe(BazaDanychUczelni& uczelnia)
{
	cout << "Grupe o jakim numerze chcesz usunac?" << endl;
	int nr;
	cin >> nr;
	uczelnia.erase(nr);
}

/**Funkcja usuwajaca grupe z przeniesieniem studentow do innych grup
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunGrupePRZ(BazaDanychUczelni& uczelnia)
{
	int max = 3;
	cout << "Grupe o jakim numerze chcesz usunac?" << endl;
	int nr, rozmiar, licz = 0;
	cin >> nr;
	vector<string>nazwiska;
	for (auto& naz : uczelnia[nr])
	{
		nazwiska.push_back(naz.first);
	}
	rozmiar = size(nazwiska);

	for (auto& grp : uczelnia)
	{
		if (grp.first != nr and licz != rozmiar)
		{
			for (int i = licz; i < rozmiar; i++)
			{
				if (rozmiar < max)
				{
					uczelnia[grp.first][nazwiska[i]] = uczelnia[nr][nazwiska[i]];
					licz = licz + 1;
				}
			}
		}
	}

	uczelnia.erase(nr);
}

/**Funkcja umozliwiajaca dodanie studenta do podanej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void dodajStudenta(BazaDanychUczelni& uczelnia)
{
	cout << "Podaj numer grupy i nazwisko studenta" << endl;
	int nr;
	string nazwisko;
	cin >> nr;
	cin >> nazwisko;
	for (auto&& grupa : uczelnia)
	{
		for (auto&& naz : grupa.second)
		{
			for (auto&& przedmiot : naz.second)
			{
				uczelnia[nr][nazwisko][przedmiot.first] = vector<float>();
			}
			break;
		}
		break;
	}

}

/**Funkcja umozliwiajaca usuniecie studenta z danej grupy
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void usunStudenta(BazaDanychUczelni& uczelnia)
{

	cout << "Podaj numer grupy i nazwisko studenta" << endl;
	int nr;
	string nazwisko;
	cin >> nr;
	cin >> nazwisko;
	uczelnia[nr].erase(nazwisko);
}

/**Funkcja pytajaca sie co zrobic ze zmienna "uczelnia"
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void menu(BazaDanychUczelni& uczelnia)
{
	int wybor;
	cout << "dodanie/usuniecie grupy: wpisz -> 1" << endl;
	cout << "dodanie/usuniecie studenta z grupy: wpisz -> 2" << endl;
	cout << "dodanie/edycja oceny studenta -> 3" << endl;
	cout << "generowanie raportow: wpisz -> 4" << endl;
	cin >> wybor;
	if (wybor == 1)
	{
		cout << "jesli chcesz dodac grupe: wpisz -> 1" << endl;
		cout << "jesli chcesz usunac grupe bez przenoszenia osob: wpisz -> 2" << endl;
		cout << "jesli chcesz usunac grupe z przenoszeniem osob: wpisz -> 3" << endl;
		cin >> wybor;
		if (wybor == 1)
			dodajGrupe(uczelnia);
		else if (wybor == 2)
			usunGrupe(uczelnia);
		else if (wybor == 3)
			usunGrupePRZ(uczelnia);
	}
	else if (wybor == 2)
	{
		cout << "jesli chcesz dodac stuednta: wpisz -> 1" << endl;
		cout << "jesli chcesz usunac studenta: wpisz -> 2" << endl;
		cin >> wybor;
		if (wybor == 1)
			dodajStudenta(uczelnia);
		else if (wybor == 2)
			usunStudenta(uczelnia);
	}
	else if (wybor == 3)
	{
		cout << "jesli chcesz dodac ocene wpisz -> 1" << endl;
		cout << "jesli chcesz edytowac ocene wpisz -> 2" << endl;
		cin >> wybor;
		if (wybor == 1)
			dodajOcene(uczelnia);
		else if (wybor == 2)
			edytujOcene(uczelnia);
	}
	else if (wybor == 4)
	{
		cout << "Raport na temat grup wpisz -> 1" << endl;
		cout << "Raport na temat ucznia wpisz -> 2" << endl;
		cout << "Raport na temat przedmiotow wpisz -> 3" << endl;
		cin >> wybor;
		if (wybor == 1)
			raportGrup(uczelnia);
		else if (wybor == 2)
			raportUcznia(uczelnia);
		else if (wybor == 3)
			raportPrzedmiotow(uczelnia);
	}

}

/**Funkcja wyrownujaca ilosc grup, aby maksymalnie w grp bylo 30 osob
@param uczelnia zmienna przechowujaca dane na temat studentow*/
void likwidacjaGrup(BazaDanychUczelni& uczelnia)
{
	int max = 30;//maskymalna ilosc osob w grp
	int x = 0, licznik = 0, grpDoUsun;
	map<int, int>baza;//grupa, ilosc osob
	for (auto& grupa : uczelnia)
	{
		if (grupa.second.size() < max)
		{
			baza[grupa.first] = grupa.second.size();
			x = x + grupa.second.size();
			licznik += 1;//liczgrp
		}

	}
	if (x % max != 0)
	{
		grpDoUsun = licznik - (x / max + 1);
	}
	else
		grpDoUsun = licznik - (x / max);
	//cout<<endl << grpDoUsun<<endl;

	if (grpDoUsun > 0)
	{
		for (int i = 0; i < grpDoUsun; i++)
		{
			int maks = 0, min = 31, maksGrp, minGrp;
			for (auto& map : baza)
			{
				if (map.second < min)
				{
					min = map.second;
					minGrp = map.first;
				}
				else if (map.second > maks)
				{
					maks = map.second;
					maksGrp = map.first;
				}
			}

			while (min != 0)
			{
				vector<string>nazwiska;
				for (auto& x : uczelnia[minGrp])
				{

					if (maks < max)
					{
						//uczelnia[maksGrp][x.first] = map<string, vector<float> >();
						uczelnia[maksGrp][x.first] = uczelnia[minGrp][x.first];
						nazwiska.push_back(x.first);

						//else

						maks = maks + 1;
					}
				}
				for (int i = 0; i < size(nazwiska); i++)
				{
					min = min - 1;
					//if (min == 1)
					//	{
					//		uczelnia.erase(minGrp);
					//	}
					//else
					uczelnia[minGrp].erase(nazwiska[i]);
				}



				if (maks == max)
				{
					baza.erase(maksGrp);
					maks = 0;
				}
				for (auto& map : baza)
				{
					if (maks <= map.second)
					{
						maks = map.second;
						maksGrp = map.first;
					}
				}
			}
			baza.erase(minGrp);
			uczelnia.erase(minGrp);
		}
	}




}

/**Funkcja zapisujaca dane do pliku
@param uczelnia zmienna przechowujaca dane na temat studentow
@return zwraca true jesli zapisano dane z pliku */
bool zapiszDoPliku(BazaDanychUczelni& uczelnia) {
	ofstream plik("dane.dat");

	if (plik.good())
	{

		string linia, nazwisko;
		int grupa;

		for (auto& g : uczelnia) {
			plik << "GRUPA " << to_string(g.first) << "\n";

			for (auto& n : g.second) {
				plik << "nazwisko " << n.first << "\n";

				for (auto& p : n.second) {
					plik << p.first << " ";

					for (auto& ocena : p.second) {
						plik << ocena << " ";
					}
					plik << "\n";
				}
			}
		}

		return true;
	}
	else
	{
		cerr << "Nie udalo sie odczytac pliku wejsciowego!\n";
		return false;
	}

	plik.close();
}
