#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <exception>

using namespace std;

#pragma region Declarari:

int n, m, nr_stari_finale, nr_cuvinte, stare_initiala;
int* sf;
string cuvant;

class Muchie
{
private:
	int start;
	int end;
	char simbol;
	string afis;

public:
	Muchie() {}
	~Muchie() {}

	int get_start()
	{
		return start;
	}
	int get_end()
	{
		return end;
	}
	char get_simbol()
	{
		return simbol;
	}
	string get_afis()
	{
		return afis;
	}

	friend istream& operator >> (istream&, Muchie&);

	bool operator == (Muchie&);
};

istream& operator >> (istream& in, Muchie& m)
{
	in >> m.start;
	in >> m.end;
	in >> m.simbol;
	in.ignore();
	getline(in, m.afis);
	return in;
}

bool Muchie::operator== (Muchie& m)
{
	if (start != m.start)
		return false;
	if (end != m.end)
		return false;
	if (simbol != m.simbol)
		return false;
	return true;
}

Muchie* muchii;

#pragma endregion

#pragma region Functii:

bool comp(Muchie a, Muchie b)
{
	return a.get_start() < b.get_start();
}

int toint(string aux) {
	int x;
	try {
		x = stoi(aux);
		return x;
	}
	catch (exception& ia) {
		return -1;
	}
}

bool Mealy(string cuvant, string& afisare, int nod_curent, vector <int>& traseu)
{
	if (cuvant.size() == NULL)
	{
		for (int i = 0; i < nr_stari_finale; i++)
			if (nod_curent == sf[i])
				return true;
		return false;
	}
	else
	{
		for (int i = 0; i < m; i++)
			if ((muchii[i].get_start() == nod_curent) && (muchii[i].get_simbol() == cuvant[0]))
			{
				afisare += muchii[i].get_afis();
				traseu.push_back(muchii[i].get_end());
				return Mealy(cuvant.substr(1, cuvant.size()), afisare, muchii[i].get_end(), traseu);
			}
			else if (muchii[i].get_start() > nod_curent)
				return false;
		return false;
	}
}

void meniu()
{
	cout << "\nIntroduceti numarul de noduri: \nn = ";
	string nr_nod;
	cin >> nr_nod;
	while (toint(nr_nod) <= 0)
	{
		cout << "Input invalid";
		cout << "\nIntroduceti numarul de noduri: \nn = ";
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> nr_nod;
	}
	n = toint(nr_nod);


	cout << "\nIntroduceti numarul de muchii: \nm = ";
	string nr_muc;
	cin >> nr_muc;
	while (toint(nr_muc) < 0)
	{
		cout << "Input invalid";
		cout << "\nIntroduceti numarul de muchii: \nm = ";
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> nr_muc;
	}
	m = toint(nr_muc);

	muchii = new Muchie[m];

	cout << "\nIntroduceti nodul de inceput si cel final si simbolul pentru muchii(nodurile sunt indexate de la 0 la " << n - 1 << "):\n\n";

	bool good = false;
	for (int i = 0; i < m; i++)
	{
		good = false;
		while (good == false)
		{
			cout << "muchia " << i + 1 << ": ";
			cin >> muchii[i];
			if ((muchii[i].get_start() < 0) || (muchii[i].get_start() >= n))
				cout << "Nodul de inceput nu este valid\n";
			else if ((muchii[i].get_end() < 0) || (muchii[i].get_end() >= n))
				cout << "Nodul de la final nu este valid\n";
			else
			{
				bool noua = true;
				for (int j = 0; j < i; j++)
					if (muchii[i] == muchii[j])
					{
						cout << "Muchia exista deja\n";
						noua = false;
					}
				if (noua == true)
					for (int j = 0; j < i; j++)
						if ((muchii[i].get_start() == muchii[j].get_start()) && (muchii[i].get_simbol() == muchii[j].get_simbol()))
						{
							cout << "Introducerea acestei muchii ar transforma DFA-ul intr-un NFA\n";
							noua = false;
						}
				if (noua == true)
				{
					good = true;
				}
			}
		}
	}

	/*
	good = false;
	while (good == false)
	{
		cout << "\nstare initiala = ";
		cin >> stare_initiala;
		if ((stare_initiala < 0) || (stare_initiala >= n))
			cout << "Input invalid";
		else
			good = true;
	}*/

	cout << "\nstare initiala = ";
	string sti;
	cin >> sti;
	while (toint(sti) < 0 || toint(sti) >= n)
	{
		cout << "Input invalid";
		cout << "\nstare initiala = ";
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> sti;
	}
	stare_initiala = toint(sti);

	/*
	good = false;
	while (good == false)
	{
		cout << "\nnumar stari finale = ";
		cin >> nr_stari_finale;
		if ((nr_stari_finale < 0) || (nr_stari_finale >= n))
			cout << "Input invalid";
		else
			good = true;
	}
	cout << "\n";*/

	cout << "\nnumar stari finale = ";
	string nr_stf;
	cin >> nr_stf;
	while (toint(nr_stf) < 0 || toint(nr_stf) > n)
	{
		cout << "Input invalid";
		cout << "\nnumar stari finale = ";
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> nr_stf;
	}
	nr_stari_finale = toint(nr_stf);

	sf = new int[nr_stari_finale];
	vector <int> fr(n, 0);
	for (int i = 0; i < nr_stari_finale; i++)
	{

		cout << "starea finala " << i + 1 << " = ";
		string stf;
		cin >> stf;
		while (toint(stf) < 0 || toint(stf) >= n || fr[toint(stf)] == 1)
		{
			cout << "Input invalid";
			cout << "\nstarea finala " << i + 1 << " = ";
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> stf;
		}
		sf[i] = toint(stf);
		fr[sf[i]] = 1;

	}

	sort(muchii, muchii + m, comp);

	int optiune = 1;

	while (optiune)
	{
		cout << "\nIntroduceti numarul de cuvinte ce doriti sa fie verificate: \nnumar de cuvinte = ";
		string nrc;
		cin >> nrc;
		while (toint(nrc) < 0)
		{
			cout << "Input invalid";
			cout << "\nIntroduceti numarul de cuvinte ce doriti sa fie verificate: \nnumar de cuvinte = ";
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> nrc;
		}
		nr_cuvinte = toint(nrc);

		cin.ignore();

		for (int i = 0; i < nr_cuvinte; i++)
		{
			cout << "\ncuvantul " << i + 1 << ": ";
			getline(cin, cuvant);
			string rez = "";

			vector <int> traseu;
			traseu.push_back(stare_initiala);

			if (Mealy(cuvant, rez, stare_initiala, traseu) == true)
			{
				cout << "Cuvantul <" << cuvant << "> a fost acceptat si afiseaza <" << rez << ">.\n";
				cout << "Traseu: ";
				for (int i = 0; i < traseu.size(); i++)
					cout << traseu[i] << " ";
				cout << "\n";
			}
			else
				cout << "Cuvantul <" << cuvant << "> nu a fost acceptat.\n";
		}

		cout << "\nOptiuni:\n";
		cout << "0 - terminare\n";
		cout << "1 - testati alte cuvinte\n";
		cout << "2 - introduceti alt Mealy\n";

		cout << "\nOptiunea dumneavoatra = ";
		string op;
		cin >> op;
		while (toint(op) < 0 || toint(op) > 2)
		{
			cout << "Input invalid";
			cout << "\nOptiunea dumneavoatra = ";
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> op;
		}
		optiune = toint(op);

		if (optiune == 2)
		{
			meniu();
			optiune = 0;
		}
	}
}

#pragma endregion

int main()
{
	meniu();
	return 0;
}
