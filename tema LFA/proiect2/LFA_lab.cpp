#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("citire.in");
ofstream fout ("afisare.out");

struct prod
{
	string si;
	string sf;
};

void fisier_generare_cuvinte(vector<prod>v, string cuvant, string neterminal, int nr)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (neterminal == v[i].si)
		{
			if (v[i].sf == "lambda" && nr == 0)
			{
				fout << cuvant << " ";
			}
			else if (v[i].sf.size() == 1 && nr == 1)
			//else if (v[i].sf[v[i].sf.size()-1] >= 'a' && v[i].sf[v[i].sf.size()-1] <= 'z' && v[i].sf != "lambda" && nr == 1)
			{
				fout << cuvant + v[i].sf << " ";
			}
			else if (v[i].sf.size() == 2 && nr > 0)
			//else if (v[i].sf[v[i].sf.size()-1] >= 'A' && v[i].sf[v[i].sf.size()-1] <= 'Z' && nr > 0)
			{
				//fisier_generare_cuvinte(v, cuvant + v[i].sf.substr(0, v[i].sf.size()-2), v[i].sf.substr(v[i].sf.size()-1, v[i].sf.size()-1), nr - 1);
				fisier_generare_cuvinte(v, cuvant + v[i].sf[0], v[i].sf.substr(1, 1), nr - 1);
			}
		}
	}
}

void fisier_algo()
{
	int nr_neterminale, nr_productii, nr_terminale, nr_lit, opt = 1;

	fin >> nr_neterminale;
	vector <string> neterminale(nr_neterminale);
	for (int i = 0; i < nr_neterminale; i++)
		fin >> neterminale[i];

	fin >> nr_terminale;
	vector <string> terminale(nr_terminale);
	for (int i = 0; i < nr_terminale; i++)
		fin >> terminale[i];

	fin >> nr_productii;
	vector <prod> productii(nr_productii);
	for (int i = 0; i < nr_productii; i++)
		fin >> productii[i].si >> productii[i].sf;

	fin >> nr_lit;

	fout << "cuvintele acceptate sunt: ";
	fisier_generare_cuvinte(productii, "", "S", nr_lit);
}


#pragma region Algoritm_tastatura
/*
void generare_cuvinte(vector<prod>v, string cuvant, string neterminal, int nr)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (neterminal == v[i].si)
		{
			if (v[i].sf == "0" && nr == 0)
			{
				cout << cuvant << " ";
			}
			else if (v[i].sf.size() == 1 && nr == 1 && v[i].sf != "0")
			{
				cout << cuvant + v[i].sf << " ";
			}
			else if (v[i].sf.size() == 2 && nr > 0)
			{
				generare_cuvinte(v, cuvant + v[i].sf[0], v[i].sf.substr(1, 1), nr - 1);
			}
		}
	}
}
void algo()
{
	cout << "Introduceti un REG!!!\n\n";
	int nr_neterminale, nr_productii, nr_terminale, nr_lit, opt = 1;

	cout << "\nintroduceti numarul de neterminale: ";
	cin >> nr_neterminale;
	vector <string> neterminale(nr_neterminale);
	for (int i = 0; i < nr_neterminale; i++)
		cin >> neterminale[i];

	cout << "\nintroduceti numarul de terminale: ";
	cin >> nr_terminale;
	vector <string> terminale(nr_terminale);
	for (int i = 0; i < nr_terminale; i++)
		cin >> terminale[i];

	cout << "\nintroduceti numarul de productii: ";
	cin >> nr_productii;
	vector <prod> productii(nr_productii);
	for (int i = 0; i < nr_productii; i++)
	{
		int ok = 0;
		while (ok == 0)
		{
			int ok1 = 0, ok2 = 0, ok3 = 0;

			cout << "productia " << i + 1 << ": ";
			cin >> productii[i].si >> productii[i].sf;

			for (int j = 0; j < nr_neterminale; j++)
				if (productii[i].si == neterminale[j])
					ok1 = 1;

			if (productii[i].sf.size() == 1)
			{
				for (int j = 0; j < nr_terminale; j++)
					if (productii[i].sf == terminale[j] || productii[i].sf == "0")
					{
						ok2 = 1;
						ok3 = 1;
					}
			}

			if (productii[i].sf.size() == 2)
			{
				for (int j = 0; j < nr_terminale; j++)
					if (productii[i].sf.substr(0, 1) == terminale[j] || productii[i].sf == "0")
						ok2 = 1;

				for (int j = 0; j < nr_neterminale; j++)
					if (productii[i].sf.substr(1, 1) == neterminale[j])
						ok3 = 1;
			}

			if (ok1 == 1 && ok2 == 1 && ok3 == 1)
				ok = 1;
		}
	}

	while (opt)
	{
		cout << "\nintroduceti numarul de litere: ";
		cin >> nr_lit;

		cout << "\ncuvintele acceptate sunt: ";
		generare_cuvinte(productii, "", "S", nr_lit);


		cout << "\n\ndoriti sa introduceti alt numar de litere? (0 - NU, 1 - DA)\n";
		cout << "optiune: ";
		cin >> opt;
	}
}
void meniu()
{
	int optiune = 1;

	while (optiune)
	{
		algo();

		cout << "\n\ndoriti sa introduceti alt REG? (0 - NU, 1 - DA)\n";
		cout << "optiune: ";
		cin >> optiune;
	}
}
*/
#pragma endregion

int main()
{
	fisier_algo();
	//meniu();
	return 0;
}
