#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <exception>

using namespace std;

class Locuinta
{
protected:
	string adresa;
	int suprafata_locuibila;
	float pret_mp;

public:
	Locuinta(string a = "", int sl = 0, float p = 0) : adresa(a), suprafata_locuibila(sl), pret_mp(p) {}
	~Locuinta() { cout << "Destructor Locuinta\n"; }

	string get_adresa()
	{
		return adresa;
	}
	int get_suprafata_locuibila()
	{
		return suprafata_locuibila;
	}
	float get_pret_mp()
	{
		return pret_mp;
	}

	friend istream& operator >>(istream&, Locuinta&);
	friend ostream& operator <<(ostream&, Locuinta&);

	virtual void citire()
	{
		cout << "\nadresa: ";
		cin >> adresa;

		cout << "\nsuprafata_locuibila:";
		cin >> suprafata_locuibila;

		cout << "\npret_mp:";
		cin >> pret_mp;
	}

	virtual float CalculChirie() = 0;
};

istream& operator>>(istream& in, Locuinta& l)
{
	cout << "\nadresa: ";
	in >> l.adresa;

	cout << "\nsuprafata_locuibila:";
	in >> l.suprafata_locuibila;

	cout << "\npret_mp:";
	in >> l.pret_mp;

	return in;
}

ostream& operator << (ostream& out, Locuinta& l)
{
	out << "\nadresa: " << l.get_adresa();
	out << "\nsuprafata_locuibila:" << l.get_suprafata_locuibila() << " metri patrati";
	out << "\npret_mp:" << l.get_pret_mp() << "unitati";
	return out;
}

class Apartament : public Locuinta
{
protected:
	int etaj;

public:
	Apartament(string a = "", int sl = 0, float p=0, int e = 0) : Locuinta(a, sl, p), etaj(e) {}
	~Apartament() { cout << "Destructor Apartament\n"; }

	int get_etaj()
	{
		return etaj;
	}

	friend istream& operator >>(istream&, Apartament&);
	friend ostream& operator <<(ostream&, Apartament&);

	void citire()
	{
		Locuinta::citire();

		cout << "\netaj: ";
		cin >> etaj;
	}

	float CalculChirie()
	{
		float s = get_suprafata_locuibila() * get_pret_mp();
		return s;
	}
};

istream& operator >> (istream& in, Apartament& a)
{
	in >> (Locuinta&)a;

	cout << "\netaj: ";
	in >> a.etaj;

	return in;
}

ostream& operator << (ostream& out, Apartament& a)
{
	out << (Locuinta&)a;
	out << "\netaj: " << a.get_etaj();
	return out;
}

class Casa : public Locuinta
{
protected:
	int curte;

public:
	Casa(string a = "", int sl = 0, float p= 0, int c = 0) : Locuinta(a, sl, p), curte(c) {}
	~Casa() { cout << "Destructor Casa\n"; }

	int get_curte()
	{
		return curte;
	}

	void citire()
	{
		Locuinta::citire();

		cout << "\ncurte: ";
		cin >> curte;
	}

	friend istream& operator >>(istream&, Casa&);
	friend ostream& operator <<(ostream&, Casa&);

	float CalculChirie()
	{
		float s = (get_suprafata_locuibila() + 0.2 * get_curte()) * get_pret_mp();
		return s;
	}
};

istream& operator >> (istream& in, Casa& c)
{
	in >> (Locuinta&)c;

	cout << "\ncurte: ";
	in >> c.curte;

	return in;
}

ostream& operator << (ostream& out, Casa& c)
{
	out << (Locuinta&)c;
	out << "\ncurte: " << c.get_curte();
	return out;
}


class Agentie
{
protected:
	vector<Locuinta*> v;

public:
	void add()
	{
		int tip_locuinta;
		cout << "Tip locuinta: ";
		cin >> tip_locuinta;

		Locuinta* aux;

		if (tip_locuinta == 1)
		{
			aux = new Apartament();
			dynamic_cast<Apartament*>(aux)->citire();
		}
		else
		{
			aux = new Casa();
			dynamic_cast<Casa*>(aux)->citire();
		}

		v.push_back(aux);
	}

	void afis()
	{
		for (auto i : v)
		{
			if (typeid(*i) == typeid(Apartament))
			{
				cout << "\nApartament:\n";
				cout << *dynamic_cast<Apartament*>(i);
			}
			else
			{
				cout << "\nCasa:\n";
				cout << *dynamic_cast<Casa*>(i);
			}
		}
	}

	void afis_loc()
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << "\nLocuinta:\n";
			cout << (*v[i]);
		}
	}

	void afis_chirii()
	{
		int j = 1;
		int k = 1;
		for (auto i : v)
		{
			if (typeid(*i) == typeid(Apartament))
			{
				cout << "\nApartamentul " << j++ << " are chiria: ";
				cout << (*i).CalculChirie();
				cout << "\n";
			}
			else
			{
				cout << "\nCasa " << k++ << " are chiria: ";
				cout << (*i).CalculChirie();
				cout << "\n";
			}
			
		}
	}
};

int main()
{
	Agentie a;
	a.add();
	a.afis();
	a.afis_loc();
	a.afis_chirii();
	a.add();
	a.afis_chirii();
	return 0;
}