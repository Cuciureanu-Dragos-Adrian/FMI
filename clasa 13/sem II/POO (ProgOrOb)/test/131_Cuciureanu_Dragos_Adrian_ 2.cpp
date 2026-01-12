#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <exception>

using namespace std;



class ContBancar
{
protected:
	int sold;
	char* detinator;

public:
	ContBancar() : sold(0), detinator(0) {}
	ContBancar(int s, char* d) : sold(s), detinator(d) {}
	~ContBancar() { cout << "Destructor ContBancar;"; }

	int get_sold()
	{
		return sold;
	}
	char* get_detinator()
	{
		return detinator;
	}

	void set_sold(int s)
	{
		sold = s;
	}
	void set_detinator(char* nume)
	{
		detinator = nume;
	}

	virtual void depunere(int suma) = 0;
	virtual void retragere(int suma) = 0;

	friend istream& operator >>(istream&, ContBancar&);
	friend ostream& operator <<(ostream&, ContBancar&);

	virtual void afisare();

	ContBancar& operator = (ContBancar&);
};

istream& operator>>(istream& in, ContBancar& cb)
{
	cout << "\nSold: ";
	in >> cb.sold;
	string s;
	cout << "\nDetiantor: ";
	in >> s;
	int n = s.size();
	cb.detinator = new char[n + 1];
	for (int i = 0; i <= n; i++)
		cb.detinator[i] = s[i];
	return in;
}

ostream& operator<<(ostream& out, ContBancar& cb)
{
	out << "\ndetinator: ";
	out << cb.detinator;
	cout << "\n Sold: ";
	out << cb.sold;
	return out;
}

void ContBancar::afisare()
{
	cout << "\ndetinator: ";
	cout << detinator;
	cout << "\n Sold: ";
	cout << sold;
}

ContBancar& ContBancar::operator=(ContBancar& cb)
{
	if (this != &cb)
	{
		sold = cb.sold;
		detinator = cb.detinator;
	}
	return *this;
}



class ContEconomii : virtual public ContBancar
{
protected:
	double rataDobanda;

public:
	ContEconomii() : ContBancar(0, 0), rataDobanda(0) {}
	ContEconomii(int s, char* d, double r) : ContBancar(s, d), rataDobanda(r) {}
	~ContEconomii() { cout << "Destructor ContEconomii"; }

	double det_rataDobanda()
	{
		return rataDobanda;
	}

	void set_rataDobanda(double s)
	{
		rataDobanda = s;
	}

	friend istream& operator >>(istream&, ContEconomii&);
	friend ostream& operator <<(ostream&, ContEconomii&);

	void afisare();

	void depunere(int suma);
	void retragere(int suma);

	void aplicaDobanda();

	ContEconomii& operator = (ContEconomii&);
};


istream& operator>>(istream& in, ContEconomii& ce)
{
	in >> (ContBancar&)ce;
	cout << "\nrata dobanzii: ";
	in >> ce.rataDobanda;
	return in;
}

ostream& operator<<(ostream& out, ContEconomii& ce)
{
	out << (ContBancar&)ce;
	cout << "\nrata dobanzii: ";
	out << ce.rataDobanda;
	return out;
}

void ContEconomii::afisare()
{
	ContBancar::afisare();
	cout << "\nrata dobanzii: ";
	cout << rataDobanda;
}

void ContEconomii::depunere(int suma)
{
	sold += suma;
}

void ContEconomii::retragere(int suma)
{
	sold -= suma;
}

void ContEconomii::aplicaDobanda()
{
	sold += sold * rataDobanda;
}

ContEconomii& ContEconomii::operator=(ContEconomii& ce)
{
	if (this != &ce)
	{
		ContBancar::operator=(ce);
		rataDobanda = ce.rataDobanda;
	}
	return *this;
}




class ContCurent : virtual public ContBancar
{
protected:
	int nrTranzactii;
	int nrTranzactiiGratis;
	int costTranzactie;

public:
	ContCurent() : ContBancar(), nrTranzactii(0), nrTranzactiiGratis(0), costTranzactie(0) {}
	ContCurent(int s, char* d, int nt, int ntg, int ct) : ContBancar(s, d), nrTranzactii(nt), nrTranzactiiGratis(ntg), costTranzactie(ct) {}
	~ContCurent() { cout << "Destructor ContCurent"; }

	int get_nrTranzactii()
	{
		return nrTranzactii;
	}
	int get_nrTranzactiiGratis()
	{
		return nrTranzactiiGratis;
	}
	int get_costTranzactie()
	{
		return costTranzactie;
	}

	void set_nrTranzactii(int nt)
	{
		nrTranzactii = nt;
	}
	void set_nrTranzactiiGratis(int ntg)
	{
		nrTranzactiiGratis = ntg;
	}
	void set_costTranzactie(int ct)
	{
		costTranzactie = ct;
	}

	friend istream& operator >>(istream&, ContCurent&);
	friend ostream& operator <<(ostream&, ContCurent&);

	void afisare();

	void depunere(int suma);
	void retragere(int suma);

	void cheltuieli();

	ContCurent& operator = (ContCurent&);
};

istream& operator>>(istream& in, ContCurent& cc)
{
	in >> (ContBancar&)cc;
	cout << "\nnumar tranzactii: ";
	in >> cc.nrTranzactii;
	cout << "\nnumar tranzactii gratis: ";
	in >> cc.nrTranzactiiGratis;
	cout << "\ncost tranzactie: ";
	in >> cc.costTranzactie;
	return in;
}

ostream& operator<<(ostream& out, ContCurent& cc)
{
	out << (ContBancar&)cc;
	cout << "\nnumar tranzactii: ";
	out << cc.nrTranzactii;
	cout << "\nnumar tranzactii gratis: ";
	out << cc.nrTranzactiiGratis;
	cout << "\ncost tranzactie: ";
	out << cc.costTranzactie;
	return out;
}

void ContCurent::afisare()
{
	ContBancar::afisare();
	cout << "\nnumar tranzactii: ";
	cout << nrTranzactii;
	cout << "\nnumar tranzactii gratis: ";
	cout << nrTranzactiiGratis;
	cout << "\ncost tranzactie: ";
	cout << costTranzactie;
}

void ContCurent::depunere(int suma)
{
	sold += suma;
}

void ContCurent::retragere(int suma)
{
	sold -= suma;
}

void ContCurent::cheltuieli()
{
	for (int i = 1; i <= nrTranzactii; i++)
	{
		if (i > nrTranzactiiGratis)
			set_sold(get_sold() - costTranzactie);
		int optiune;
		cout << "\nTipuri tranzactii: ";
		cout << "\n1 - depunere";
		cout << "\n2- retragere";
		cin >> optiune;
		if (optiune == 1)
		{
			int suma;
			cout << "suma depusa: ";
			cin >> suma;
			depunere(suma);
		}
		else
		{
			int suma;
			cout << "suma retrasa: ";
			cin >> suma;
			retragere(suma);
		}
	}
}

ContCurent& ContCurent::operator=(ContCurent& cc)
{
	if (this != &cc)
	{
		ContBancar::operator=(cc);
		nrTranzactii = cc.nrTranzactii;
		nrTranzactiiGratis = cc.nrTranzactiiGratis;
		costTranzactie = cc.costTranzactie;
	}
	return *this;
}



class Conturi
{
protected:
	int perioade;
	int nrConturi;
	ContBancar** v;

public:
	Conturi() : perioade(0), nrConturi(0), v(0) {}
	Conturi(int p, int nc, ContBancar** cb) : perioade(p), nrConturi(nc), v(cb) {}
	~Conturi() { cout << "Destrucor Conturi"; }

	int get_perioade()
	{
		return perioade;
	}
	int get_nrConturi()
	{
		return nrConturi;
	}
	ContBancar* get_cont(int nr)
	{
		return v[nr];
	}

	void set_perioade(int p)
	{
		perioade = p;
	}
	void set_nrConturi(int nc)
	{
		nrConturi = nc;
	}

	friend istream& operator >>(istream&, Conturi&);
	friend ostream& operator <<(ostream&, Conturi&);
};

istream& operator >> (istream& in, Conturi& c)
{
	cout << "\n perioade: ";
	in >> c.perioade;

	cout << "\n numar conturi: ";
	in >> c.nrConturi;

	c.v = new ContBancar * [c.nrConturi];

	cout << "\nTipuri de conturi: ";
	cout << "\n1 - cont economii";
	cout << "\n2 - cont curent";

	for (int i = 0; i < c.nrConturi; i++)
	{
		int tip;
		cout << "\n\nintroduceti tipul contului " << i + 1 << ": ";
		in >> tip;

		if (tip == 1)
		{
			c.v[i] = new ContEconomii();
			in >> *dynamic_cast<ContEconomii*> (c.v[i]);
		}
		else
		{
			c.v[i] = new ContCurent();
			in >> *dynamic_cast<ContCurent*> (c.v[i]);
		}
	}

	return in;
}

ostream& operator << (ostream& out, Conturi& c)
{
	cout << "\nperioade: ";
	out << c.perioade;

	int idx_economii = 1;
	int idx_curent = 1;

	out << "\n\nsunt " << c.nrConturi << " conturi:";

	for (int i = 0; i < c.nrConturi; i++)
	{
		if (typeid(*c.v[i]) == typeid(ContEconomii))
		{
			cout << "\n\ncontul " << i + 1 << " / contul economic " << idx_economii << ":\n";
			idx_economii++;
			out << *dynamic_cast<ContEconomii*> (c.v[i]);
		}
		else
		{
			cout << "\n\ncontul " << i + 1 << " / contul curent " << idx_curent << ":\n";
			idx_curent++;
			out << *dynamic_cast<ContCurent*> (c.v[i]);
		}
	}

	return out;
}


void meniu()
{
	Conturi c;
	cin >> c;
	for (int i = 0; i < c.get_perioade(); i++)
	{
		for (int j = 0; j < c.get_nrConturi(); j++)
		{
			if (typeid(*c.get_cont(j)) == typeid(ContEconomii))
			{
				(*dynamic_cast<ContEconomii*>(c.get_cont(j))).aplicaDobanda();
			}
			else
			{
				(*dynamic_cast<ContCurent*>(c.get_cont(j))).cheltuieli();
			}
		}
	}
	cout << c;
}

int main()
{
	/*
	ContEconomii ce;
	cin >> ce;
	cout << ce;

	ContCurent cc;
	cin >> cc;
	cout << cc;
	*/

	char* nume = new char[50];
	cin >> nume;
	ContEconomii ce(12, nume, 2.5);
	ce.afisare();

	meniu();

	return 0;
}
