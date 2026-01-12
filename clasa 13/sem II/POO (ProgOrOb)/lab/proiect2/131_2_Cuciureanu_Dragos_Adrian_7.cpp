#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <exception>

using namespace std;


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

float tofloat(string aux) {
	float x;
	try {
		x = stof(aux);
		return x;
	}
	catch (exception& ia) {
		return -1;
	}
}



class Locuinta
{
private:
	string numeClient;
	int suprafataUtila;
	float discount;

public:
	Locuinta(): numeClient (""), suprafataUtila (0), discount (0) {}
	Locuinta(string s) : numeClient(s), suprafataUtila(0), discount(0) {};
	Locuinta(string s, int x) : numeClient(s), suprafataUtila(x), discount(0) {};
	Locuinta(string s, int x, float d) : numeClient(s), suprafataUtila(x), discount(d) {};
	Locuinta(Locuinta&);
	~Locuinta() { cout << "Destructor Locuinta\n"; }

	string get_numeClient()
	{
		return numeClient;
	}
	int get_suprafataUtila()
	{
		return suprafataUtila;
	}
	float get_discount()
	{
		return discount;
	}

	void set_numeClient(string s)
	{
		numeClient = s;
	}
	void set_suprafataUtila(int nr)
	{
		suprafataUtila = nr;
	}
	void set_discount(float nr)
	{
		discount = nr;
	}

	friend istream& operator >>(istream&, Locuinta&);
	friend ostream& operator <<(ostream&, Locuinta&);

	Locuinta& operator = (Locuinta&);

	void afisare_locuinta();

	virtual float CalculChirie(float, int) = 0;
};


Locuinta::Locuinta(Locuinta& l)
{
	numeClient = l.numeClient;
	suprafataUtila = l.suprafataUtila;
	discount = l.discount;
}

istream& operator>>(istream& in, Locuinta& l)
{
	cout << "\nnume client: ";
	in.ignore();
	getline (in, l.numeClient);

	cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
	string suprafata;
	in >> suprafata;
	while (toint(suprafata) < 50 || toint(suprafata) > 1000)
	{
		cout << "Input invalid";
		cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> suprafata;
	}
	l.suprafataUtila = toint(suprafata);

	cout << "\ndiscount(intre 0 si 100): ";
	string dis;
	in >> dis;
	while (tofloat(dis) < 0 || tofloat(dis) > 100)
	{
		cout << "Input invalid";
		cout << "\ndiscount(intre 0 si 100): ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> dis;
	}
	l.discount = tofloat(dis);
	return in;
}

ostream& operator << (ostream& out, Locuinta& l)
{
	out << "\nnume client: " << l.get_numeClient();
	out << "\nsuprafata utila: " << l.get_suprafataUtila() << " metri patrati";
	out << "\ndiscount: " << l.get_discount() << "%";
	return out;
}

Locuinta& Locuinta::operator = (Locuinta& l)
{
	if (this != &l)
	{
		numeClient = l.numeClient;
		suprafataUtila = l.suprafataUtila;
		discount = l.discount;
	}
	return *this;
}

void Locuinta::afisare_locuinta()
{
	cout << "\nnume client: " << get_numeClient();
	cout << "\nsuprafata utila: " << get_suprafataUtila() << " metri patrati";
	cout << "\ndiscount: " << get_discount() << "%";
}



class Apartament : public Locuinta
{
private:
	static int nr_apartamente;
	int etaj;

public:
	Apartament() : Locuinta("", 0, 0), etaj(0) { nr_apartamente++; };
	Apartament(string s, int x, float d) : Locuinta(s, x, d), etaj(0) { nr_apartamente++; }
	Apartament(string s, int x, float d, int et) : Locuinta(s, x, d), etaj(et) { nr_apartamente++; }
	Apartament(Apartament&);
	~Apartament() { cout << "Destructor apartament\n"; };

	int get_etaj()
	{
		return etaj;
	}

	void set_etaj(int nr)
	{
		etaj = nr;
	}

	static void scadere_nr_apartamente()
	{
		nr_apartamente--;
	}

	friend istream& operator >>(istream&, Apartament&);
	friend ostream& operator <<(ostream&, Apartament&);

	Apartament& operator = (Apartament&);

	float CalculChirie(float, int);

	static void afisare_nr_apartamente()
	{
		cout << "\n" << nr_apartamente << " apartamente";
	}
};


int Apartament::nr_apartamente;

Apartament::Apartament(Apartament& a) : Locuinta(a)
{
	nr_apartamente++;
	etaj = a.etaj;
}

istream& operator >> (istream& in, Apartament& a)
{
	in >> (Locuinta&)a;
	cout << "\netaj: ";
	string et;
	in >> et;
	while (toint(et) < 0)
	{
		cout << "Input invalid";
		cout << "\netaj: ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> et;
	}
	a.etaj = toint(et);
	return in;
}

ostream& operator << (ostream& out, Apartament& a)
{
	out << (Locuinta&)a;
	out << "\netaj: " << a.get_etaj();
	return out;
}

Apartament& Apartament::operator = (Apartament& a)
{
	if (this != &a)
	{
		Locuinta::operator = (a);
		etaj = a.etaj;
	}
	return *this;
}

float Apartament::CalculChirie(float x, int y)
{
	float rez;
	rez = x * get_suprafataUtila() * (1 - y * get_discount() / 100.0);
	return rez;
}



class Casa : public Locuinta
{
private:
	static int nr_case;
	int suprafataCurte;

public:
	Casa() : Locuinta("", 0, 0), suprafataCurte(0) { nr_case++; }
	Casa(string s, int x, float d) : Locuinta(s, x, d), suprafataCurte(0) { nr_case++; }
	Casa(string s, int x, float d, int supr) : Locuinta(s, x, d), suprafataCurte(supr) { nr_case++; }
	Casa(Casa&);
	~Casa() { cout << "Destructor casa\n"; };

	int get_suprafataCurte()
	{
		return suprafataCurte;
	}

	void set_suprafataCurte(int nr)
	{
		suprafataCurte = nr;
	}

	static void scadere_nr_case()
	{
		nr_case--;
	}

	friend istream& operator >>(istream&, Casa&);
	friend ostream& operator <<(ostream&, Casa&);

	Casa& operator = (Casa&);

	float CalculChirie(float, int);

	static void afisare_nr_case()
	{
		cout << "\n" << nr_case << " case";
	}
};


int Casa::nr_case;

Casa::Casa(Casa& c) : Locuinta(c)
{
	nr_case++;
	suprafataCurte = c.suprafataCurte;
}

istream& operator >> (istream& in, Casa& c)
{
	in >> (Locuinta&)c;
	cout << "\nsuprafata curte: ";
	string sc;
	in >> sc;
	while (toint(sc) < 0)
	{
		cout << "Input invalid";
		cout << "\nsuprafata curte: ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> sc;
	}
	c.suprafataCurte = toint(sc);
	return in;
}

ostream& operator << (ostream& out, Casa& c)
{
	out << (Locuinta&)c;
	out << "\nsuprafata curte: " << c.get_suprafataCurte() << " metri";
	return out;
}

Casa& Casa::operator = (Casa& c)
{
	if (this != &c)
	{
		Locuinta::operator = (c);
		suprafataCurte = c.suprafataCurte;
	}
	return *this;
}

float Casa::CalculChirie(float x, int y)
{
	float rez;
	rez = x * (get_suprafataUtila() + 0.2 * get_suprafataCurte()) * (1 - y * get_discount() / 100.0);
	return rez;
}



class Bunker : public Locuinta
{
private:
	static int nr_bunkere;
	int adancime;

public:
	Bunker() : Locuinta("", 0, 0), adancime(0) { nr_bunkere++; }
	Bunker(string s, int x, float d) : Locuinta(s, x, d), adancime(0) { nr_bunkere++; }
	Bunker(string s, int x, float d, int ad) : Locuinta(s, x, d), adancime(ad) { nr_bunkere++; }
	Bunker(Bunker&);
	~Bunker() { cout << "Destructor bunker\n"; };

	int get_nr_bunkere()
	{
		return nr_bunkere;
	}
	int get_adancime()
	{
		return adancime;
	}

	void set_nr_bunkere(int nr)
	{
		nr_bunkere = nr;
	}
	void set_adancime(int nr)
	{
		adancime = nr;
	}

	static void scadere_nr_bunkere()
	{
		nr_bunkere--;
	}

	friend istream& operator >>(istream&, Bunker&);
	friend ostream& operator <<(ostream&, Bunker&);

	Bunker& operator = (Bunker&);

	float CalculChirie(float, int);

	static void afisare_nr_bunkere()
	{
		cout << "\n" << nr_bunkere << " bunkere";
	}
};


int Bunker::nr_bunkere;

Bunker::Bunker(Bunker& b) : Locuinta(b)
{
	nr_bunkere++;
	adancime = b.adancime;
}

istream& operator >> (istream& in, Bunker& b)
{
	in >> (Locuinta&)b;
	cout << "\nadancime: ";
	string ad;
	in >> ad;
	while (toint(ad) < 0)
	{
		cout << "Input invalid";
		cout << "\nadancime: ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> ad;
	}
	b.adancime = toint(ad);
	return in;
}

ostream& operator << (ostream& out, Bunker& b)
{
	out << (Locuinta&)b;
	out << "\nadancime: " << b.get_adancime() << " metri";
	return out;
}

Bunker& Bunker::operator = (Bunker& b)
{
	if (this != &b)
	{
		Locuinta::operator = (b);
		adancime = b.adancime;
	}
	return *this;
}

float Bunker::CalculChirie(float x, int y)
{
	float rez;
	rez = x * get_suprafataUtila() * (1 - y * get_discount() / 100.0) * ((100 + get_adancime()) / 100);
	return rez;
}


class Agentie
{
private:
	float pret_mp;
	int exista_discount;
	int nr_locuinte;
	Locuinta** v;

public:
	Agentie() : pret_mp(0), exista_discount(0), nr_locuinte(0), v(0) {}
	Agentie(float p) : pret_mp(p), exista_discount(0), nr_locuinte(0), v(0) {}
	Agentie(float p, int e) : pret_mp(p), exista_discount(e), nr_locuinte(0), v(0) {}
	Agentie(float p, int e, int n) : pret_mp(p), exista_discount(e), nr_locuinte(n), v(0) {}
	Agentie(float p, int e, int n, Locuinta** x) : pret_mp(p), exista_discount(e), nr_locuinte(n), v(x) {}
	Agentie(Agentie&);
	~Agentie() { delete[]v; }

	float get_pret_mp()
	{
		return pret_mp;
	}
	int get_exista_discount()
	{
		return exista_discount;
	}
	int get_nr_locuinte()
	{
		return nr_locuinte;
	}
	Locuinta* get_entitate(int nr)
	{
		return v[nr];
	}

	void set_pret_mp(float nr)
	{
		pret_mp = nr;
	}
	void set_exista_discount(int nr)
	{
		exista_discount = nr;
	}
	void set_nr_locuinte(int nr)
	{
		nr_locuinte = nr;
	}

	friend istream& operator >>(istream&, Agentie&);
	friend ostream& operator <<(ostream&, Agentie&);

	Agentie& operator = (Agentie&);

	void afisare_locuinte();
	void afisare_chirii();

	void add(Locuinta*);
	void delet(int);
};

Agentie::Agentie(Agentie& a)
{
	pret_mp = a.pret_mp;
	exista_discount = a.exista_discount;
	nr_locuinte = a.nr_locuinte;

	v = new Locuinta * [nr_locuinte];

	for (int i = 0; i < nr_locuinte; i++)
	{
		v[i] = a.v[i];
	}
}

istream& operator >> (istream& in, Agentie& a)
{
	cout << "\npret metru/patrat: ";
	string pmp;
	in >> pmp;
	while (tofloat(pmp) <= 0)
	{
		cout << "Input invalid";
		cout << "\npret metru/patrat: ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> pmp;
	}
	a.pret_mp = tofloat(pmp);

	cout << "\nse aplica discountul? (0-NU 1-DA): ";
	string disc;
	in >> disc;
	while (toint(disc) != 0 && toint(disc) != 1)
	{
		cout << "Input invalid";
		cout << "\nse aplica discountul? (0-NU 1-DA): ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> disc;
	}
	a.exista_discount = toint(disc);

	cout << "\nnumarul de entitati: ";
	string nr;
	in >> nr;
	while (toint(nr) < 0)
	{
		cout << "Input invalid";
		cout << "\nnumarul de entitati: ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> nr;
	}
	a.nr_locuinte = toint(nr);

	a.v = new Locuinta * [a.nr_locuinte];

	cout << "\nTipuri de locuinte:";
	cout << "\n1 - apartament";
	cout << "\n2 - casa";
	cout << "\n3 - bunker (oportunitate de neratat)";

	for (int i = 0; i < a.nr_locuinte; i++)
	{
		int tips;
		cout << "\n\nintroduceti tipul locuintei " << i + 1 << ": ";
		string tip;
		in >> tip;
		while (toint(tip) != 1 && toint(tip) != 2 && toint(tip) != 3)
		{
			cout << "Input invalid";
			cout << "\nintroduceti tipul locuintei " << i + 1 << ":";
			in.ignore(numeric_limits < streamsize > ::max(), '\n');
			in >> tip;
		}
		tips = toint(tip);

		if (tips == 1)
		{
			a.v[i] = new Apartament();
			cin >> *dynamic_cast<Apartament*>(a.v[i]);
		}
		else if (tips == 2)
		{
			a.v[i] = new Casa();
			cin >> *dynamic_cast<Casa*>(a.v[i]);
		}
		else
		{
			a.v[i] = new Bunker();
			cin >> *dynamic_cast<Bunker*>(a.v[i]);
		}
	}

	return in;
}

ostream& operator << (ostream& out, Agentie& a)
{
	out << "\n\n\npret metru/patrat: " << a.pret_mp;
	if (a.exista_discount == 0)
		out << "\ndiscount inactiv";
	else
		out << "\ndiscount activ";
	out << "\n\nsunt " << a.nr_locuinte << " locuinte:";
	Apartament::afisare_nr_apartamente();
	Casa::afisare_nr_case();
	Bunker::afisare_nr_bunkere();

	int idx_apartament = 1;
	int idx_casa = 1;
	int idx_bunker = 1;

	for (int i = 0; i < a.nr_locuinte; i++)
	{
		if (typeid(*a.v[i]) == typeid(Apartament))
		{
			out << "\n\nlocuinta " << i + 1 << " / apartamentul " << idx_apartament << ":\n";
			idx_apartament++;
			out << *dynamic_cast<Apartament*>(a.v[i]);
			if (a.exista_discount == 0)
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati";
			else
			{
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 1) << " unitati";
				out << " (pret initial: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati)";
			}
		}
		else if (typeid(*a.v[i]) == typeid(Casa))
		{
			out << "\n\nlocuinta " << i + 1 << " / casa " << idx_casa << ":\n";
			idx_casa++;
			out << *dynamic_cast<Casa*>(a.v[i]);
			if (a.exista_discount == 0)
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati";
			else
			{
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 1) << " unitati";
				out << " (pret initial: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati)";
			}
		}
		else
		{
			out << "\n\nlocuinta " << i + 1 << " / bunkerul " << idx_bunker << ":\n";
			idx_bunker++;
			out << *dynamic_cast<Bunker*>(a.v[i]);
			if (a.exista_discount == 0)
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati";
			else
			{
				out << "\nchiria: " << (*a.v[i]).CalculChirie(a.pret_mp, 1) << " unitati";
				out << " (pret initial: " << (*a.v[i]).CalculChirie(a.pret_mp, 0) << " unitati)";
			}
		}
	}

	return out;
}

Agentie& Agentie::operator = (Agentie& a)
{
	if (this != &a)
	{
		pret_mp = a.pret_mp;
		exista_discount = a.exista_discount;
		nr_locuinte = a.nr_locuinte;

		v = new Locuinta * [nr_locuinte];

		for (int i = 0; i < nr_locuinte; i++)
		{
			v[i] = a.v[i];
		}
	}
	return *this;
}

void Agentie::afisare_locuinte()
{
	for (int i = 0; i < nr_locuinte; i++)
	{
		cout << "Locuinta numarul " << i + 1 << ":\n";
		v[i]->afisare_locuinta();
		cout << "\n";
	}
}

void Agentie::afisare_chirii()
{
	int idx_apartament = 1;
	int idx_casa = 1;
	int idx_bunker = 1;

	for (int i = 0; i < nr_locuinte; i++)
	{
		if (typeid(*v[i]) == typeid(Apartament))
		{
			cout << "\n\nlocuinta " << i + 1 << " / apartamentul " << idx_apartament << ":\n";
			idx_apartament++;

			if (exista_discount == 0)
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati";
			else
			{
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 1) << " unitati";
				cout << " (pret initial: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati)";
			}
		}
		else if (typeid(*v[i]) == typeid(Casa))
		{
			cout << "\n\nlocuinta " << i + 1 << " / casa " << idx_casa << ":\n";
			idx_casa++;

			if (exista_discount == 0)
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati";
			else
			{
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 1) << " unitati";
				cout << " (pret initial: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati)";
			}
		}
		else
		{
			cout << "\n\nlocuinta " << i + 1 << " / bunkerul " << idx_bunker << ":\n";
			idx_bunker++;

			if (exista_discount == 0)
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati";
			else
			{
				cout << "\nchiria: " << (*v[i]).CalculChirie(pret_mp, 1) << " unitati";
				cout << " (pret initial: " << (*v[i]).CalculChirie(pret_mp, 0) << " unitati)";
			}
		}
	}
}

void Agentie::add(Locuinta* l)
{
	nr_locuinte++;
	Locuinta** aux = new Locuinta * [nr_locuinte];
	for (int i = 0; i < nr_locuinte - 1; i++)
	{
		aux[i] = v[i];
	}
	aux[nr_locuinte - 1] = l;

	v = new Locuinta * [nr_locuinte];

	for (int i = 0; i < nr_locuinte; i++)
	{
		v[i] = aux[i];
	}

	delete[] aux;
}

void Agentie::delet(int index)
{
	if (typeid(*v[index]) == typeid(Apartament))
	{
		Apartament::scadere_nr_apartamente();
	}
	else if (typeid(*v[index]) == typeid(Casa))
	{
		Casa::scadere_nr_case();
	}
	else
	{
		Bunker::scadere_nr_bunkere();
	}

	int j = 0;
	Locuinta** aux = new Locuinta * [nr_locuinte];
	for (int i = 0; i < nr_locuinte; i++)
	{
		if (index != i)
		{
			aux[j] = v[i];
			j++;
		}
	}
	nr_locuinte--;

	v = new Locuinta * [nr_locuinte];

	for (int i = 0; i < nr_locuinte; i++)
	{
		v[i] = aux[i];
	}

	delete[] aux;
}



void afis(Locuinta* l)
{
	cout << "\nnume client: " << (*l).get_numeClient();
	cout << "\nsuprafata utila: " << (*l).get_suprafataUtila() << " metri patrati";
	cout << "\ndiscount: " << (*l).get_discount() << "%";
}

void meniu()
{
	Agentie a;
	cin >> a;
	
	cout << "\n\nOptiuni:\n";
	if (a.get_nr_locuinte() != 0)
	cout << "1 - afisare\n";
	if (a.get_nr_locuinte() != 0)
	cout << "2 - modificare\n";
	cout << "3 - adaugare\n";
	if (a.get_nr_locuinte() != 0)
	cout << "4 - eliminare\n";
	cout << "5 - terminare\n";
	

	int optiune;
	string op;
	cout << "\nOptiunea dumneavoastra: ";
	cin >> op;
	while (toint(op) != 5 && toint(op) != 3 && (toint(op) != 1 || a.get_nr_locuinte() == 0) && (toint(op) != 2 || a.get_nr_locuinte() == 0) && (toint(op) != 4 || a.get_nr_locuinte() == 0))
	{
		cout << "Input invalid";
		cout << "\nOptiunea dumneavoastra: ";
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> op;
	}
	optiune = toint(op);

	while (optiune!=5)
	{
		switch (optiune)
		{
		case 1:
		{
			
			cout << "\nOptiuni:\n";
			cout << "1 - afisarea agentiei complete\n";
			cout << "2 - afisarea unei entitati din agentie\n";
			cout << "3 - afisarea doar a locuintelor din entitati\n";
			cout << "4 - afisarea doar a chiriilor\n";
			cout << "5 - intoarcerea la meniul principal\n";
			int optiune_case1;

			string op1;
			cout << "\nOptiunea dumneavoastra: ";
			cin >> op1;
			while (toint(op1) != 1 && toint(op1) != 2 && toint(op1) != 3 && toint(op1) != 4 && toint(op1) != 5)
			{
				cout << "Input invalid";
				cout << "\nOptiunea dumneavoastra: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op1;
			}
			optiune_case1 = toint(op1);

			cout << "\n";

			switch (optiune_case1)
			{
			case 1:
			{
				cout << a;
				break;
			}
			case 2:
			{
				int nr;
				cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
				string nre;
				cin >> nre;
				while (toint(nre) <= 0 || toint(nre) > a.get_nr_locuinte())
				{
					cout << "Input invalid";
					cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> nre;
				}
				nr = toint(nre);
				cout << "\n";

				if (typeid(*a.get_entitate(nr - 1)) == typeid(Apartament))
				{
					cout << *dynamic_cast<Apartament*>(a.get_entitate(nr - 1));
					if (a.get_exista_discount() == 0)
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati";
					else
					{
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 1) << " unitati";
						cout << " (pret initial: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati)";
					}
				}
				else if (typeid(*a.get_entitate(nr - 1)) == typeid(Casa))
				{
					cout << *dynamic_cast<Casa*>(a.get_entitate(nr - 1));
					if (a.get_exista_discount() == 0)
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati";
					else
					{
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 1) << " unitati";
						cout << " (pret initial: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati)";
					}
				}
				else
				{
					cout << *dynamic_cast<Bunker*>(a.get_entitate(nr - 1));
					if (a.get_exista_discount() == 0)
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati";
					else
					{
						cout << "\nchiria: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 1) << " unitati";
						cout << " (pret initial: " << (*a.get_entitate(nr - 1)).CalculChirie(a.get_pret_mp(), 0) << " unitati)";
					}
				}
				break;
			}
			case 3:
			{
				for (int i = 0; i < a.get_nr_locuinte(); i++)
				{
					cout << "\n\nLocuinta " << i + 1 << ":\n";
					if (typeid(*a.get_entitate(i)) == typeid(Apartament))
					{
						afis(dynamic_cast<Apartament*>(a.get_entitate(i)));
					}
					else if (typeid(*a.get_entitate(i)) == typeid(Casa))
					{
						afis(dynamic_cast<Casa*>(a.get_entitate(i)));
					}
					else
					{
						afis(dynamic_cast<Bunker*>(a.get_entitate(i)));
					}
				}
				break;
			}
			case 4:
			{
				a.afisare_chirii();
				break;
			}
			case 5:
			{
				break;
			}
			}

			break;
		}
		case 2:
		{
			cout << "\nOptiuni:\n";
			cout << "1 - modificarea pretului pe metru patrat\n";
			cout << "2 - modificarea existentei discountului\n";
			cout << "3 - modificarea unei entitati\n";
			cout << "4 - intoarcerea la meniul principal\n";
			int optiune_case2;
			

			string op2;
			cout << "\nOptiunea dumneavoastra: ";
			cin >> op2;
			while (toint(op2) != 1 && toint(op2) != 2 && toint(op2) != 3 && toint(op2) != 4)
			{
				cout << "Input invalid";
				cout << "\nOptiunea dumneavoastra: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op2;
			}
			optiune_case2 = toint(op2);

			cout << "\n";

			switch (optiune_case2)
			{
			case 1:
			{
				float nr;
				cout << "\npret metru/patrat: ";
				string pmp;
				cin >> pmp;
				while (tofloat(pmp) <= 0)
				{
					cout << "Input invalid";
					cout << "\npret metru/patrat: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> pmp;
				}
				nr = tofloat(pmp);
				a.set_pret_mp(nr);
				break;
			}
			case 2:
			{
				int bin;
				cout << "\nse aplica discountul? (0-NU 1-DA): ";
				string disc;
				cin >> disc;
				while (toint(disc) != 0 && toint(disc) != 1)
				{
					cout << "Input invalid";
					cout << "\nse aplica discountul? (0-NU 1-DA): ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> disc;
				}
				bin = toint(disc);
				a.set_exista_discount(bin);
				break;
			}
			case 3:
			{
				int nr;
				cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
				string nre;
				cin >> nre;
				while (toint(nre) <= 0 || toint(nre) > a.get_nr_locuinte())
				{
					cout << "Input invalid";
					cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> nre;
				}
				nr = toint(nre);

				if (typeid(*a.get_entitate(nr - 1)) == typeid(Apartament))
				{
					cout << "\nOptiuni:\n";
					cout << "1 - modificarea numelui clientului\n";
					cout << "2 - modificarea suprafetei utile\n";
					cout << "3 - modificarea discountului\n";
					cout << "4 - modificarea etajului\n";
					cout << "5 - intoarcerea la meniul principal\n";
					int optiune_case2_1;

					string op2_1;
					cout << "\nOptiunea dumneavoastra: ";
					cin >> op2_1;
					while (toint(op2_1) != 1 && toint(op2_1) != 2 && toint(op2_1) != 3 && toint(op2_1) != 4 && toint(op2_1) != 5)
					{
						cout << "Input invalid";
						cout << "\nOptiunea dumneavoastra: ";
						cin.ignore(numeric_limits < streamsize > ::max(), '\n');
						cin >> op2_1;
					}
					optiune_case2_1 = toint(op2_1);

					cout << "\n";

					switch (optiune_case2_1)
					{
					case 1:
					{
						string nume;
						cout << "\nnume client: ";
						cin.ignore();
						getline(cin, nume);

						(*a.get_entitate(nr - 1)).set_numeClient(nume);
						break;
					}
					case 2:
					{
						int supr;
						cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
						string suprafata;
						cin >> suprafata;
						while (toint(suprafata) < 50 || toint(suprafata) > 1000)
						{
							cout << "Input invalid";
							cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> suprafata;
						}
						supr = toint(suprafata);

						a.get_entitate(nr - 1)->set_suprafataUtila(supr);
						break;
					}
					case 3:
					{
						float disc;
						cout << "\ndiscount(intre 0 si 100): ";
						string dis;
						cin >> dis;
						while (tofloat(dis) < 0 || tofloat(dis) > 100)
						{
							cout << "Input invalid";
							cout << "\ndiscount(intre 0 si 100): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> dis;
						}
						disc = tofloat(dis);

						(*a.get_entitate(nr - 1)).set_discount(disc);
						break;
					}
					case 4:
					{
						int etaj;
						cout << "\netaj: ";
						string et;
						cin >> et;
						while (toint(et) < 0)
						{
							cout << "Input invalid";
							cout << "\netaj: ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> et;
						}
						etaj = toint(et);

						(*dynamic_cast<Apartament*>(a.get_entitate(nr - 1))).set_etaj(etaj);
						break;
					}
					case 5:
					{
						break;
					}
					}
				}
				else if (typeid(*a.get_entitate(nr - 1)) == typeid(Casa))
				{
					cout << "\nOptiuni:\n";
					cout << "1 - modificarea numelui clientului\n";
					cout << "2 - modificarea suprafetei utile\n";
					cout << "3 - modificarea discountului\n";
					cout << "4 - modificarea suprafetei curtii\n";
					cout << "5 - intoarcerea la meniul principal\n";
					int optiune_case2_2;

					string op2_2;
					cout << "\nOptiunea dumneavoastra: ";
					cin >> op2_2;
					while (toint(op2_2) != 1 && toint(op2_2) != 2 && toint(op2_2) != 3 && toint(op2_2) != 4 && toint(op2_2) != 5)
					{
						cout << "Input invalid";
						cout << "\nOptiunea dumneavoastra: ";
						cin.ignore(numeric_limits < streamsize > ::max(), '\n');
						cin >> op2_2;
					}
					optiune_case2_2 = toint(op2_2);

					cout << "\n";

					switch (optiune_case2_2)
					{
					case 1:
					{
						string nume;
						cout << "\nnume client: ";
						cin.ignore();
						getline(cin, nume);

						(*a.get_entitate(nr - 1)).set_numeClient(nume);
						break;
					}
					case 2:
					{
						int supr;
						cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
						string suprafata;
						cin >> suprafata;
						while (toint(suprafata) < 50 || toint(suprafata) > 1000)
						{
							cout << "Input invalid";
							cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> suprafata;
						}
						supr = toint(suprafata);

						a.get_entitate(nr - 1)->set_suprafataUtila(supr);
						break;
					}
					case 3:
					{
						float disc;
						cout << "\ndiscount(intre 0 si 100): ";
						string dis;
						cin >> dis;
						while (tofloat(dis) < 0 || tofloat(dis) > 100)
						{
							cout << "Input invalid";
							cout << "\ndiscount(intre 0 si 100): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> dis;
						}
						disc = tofloat(dis);

						(*a.get_entitate(nr - 1)).set_discount(disc);
						break;
					}
					case 4:
					{
						int supr;
						cout << "\nsuprafata curte: ";
						string sc;
						cin >> sc;
						while (toint(sc) < 0)
						{
							cout << "Input invalid";
							cout << "\nsuprafata curte: ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> sc;
						}
						supr = toint(sc);

						(*dynamic_cast<Casa*>(a.get_entitate(nr - 1))).set_suprafataCurte(supr);
						break;
					}
					case 5:
					{
						break;
					}
					}
				}
				else
				{
					cout << "\nOptiuni:\n";
					cout << "1 - modificarea numelui clientului\n";
					cout << "2 - modificarea suprafetei utile\n";
					cout << "3 - modificarea discountului\n";
					cout << "4 - modificarea adancimii\n";
					cout << "5 - intoarcerea la meniul principal\n";
					int optiune_case2_3;

					string op2_3;
					cout << "\nOptiunea dumneavoastra: ";
					cin >> op2_3;
					while (toint(op2_3) != 1 && toint(op2_3) != 2 && toint(op2_3) != 3 && toint(op2_3) != 4 && toint(op2_3) != 5)
					{
						cout << "Input invalid";
						cout << "\nOptiunea dumneavoastra: ";
						cin.ignore(numeric_limits < streamsize > ::max(), '\n');
						cin >> op2_3;
					}
					optiune_case2_3 = toint(op2_3);

					cout << "\n";

					switch (optiune_case2_3)
					{
					case 1:
					{
						string nume;
						cout << "\nnume client: ";
						cin.ignore();
						getline(cin, nume);

						(*a.get_entitate(nr - 1)).set_numeClient(nume);
						break;
					}
					case 2:
					{
						int supr;
						cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
						string suprafata;
						cin >> suprafata;
						while (toint(suprafata) < 50 || toint(suprafata) > 1000)
						{
							cout << "Input invalid";
							cout << "\nsuprafata utila (intre 50mp si 1000mp): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> suprafata;
						}
						supr = toint(suprafata);

						a.get_entitate(nr - 1)->set_suprafataUtila(supr);
						break;
					}
					case 3:
					{
						float disc;
						cout << "\ndiscount(intre 0 si 100): ";
						string dis;
						cin >> dis;
						while (tofloat(dis) < 0 || tofloat(dis) > 100)
						{
							cout << "Input invalid";
							cout << "\ndiscount(intre 0 si 100): ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> dis;
						}
						disc = tofloat(dis);

						(*a.get_entitate(nr - 1)).set_discount(disc);
						break;
					}
					case 4:
					{
						int adanc;
						cout << "\nadancime: ";
						string ad;
						cin >> ad;
						while (toint(ad) < 0)
						{
							cout << "Input invalid";
							cout << "\nadancime: ";
							cin.ignore(numeric_limits < streamsize > ::max(), '\n');
							cin >> ad;
						}
						adanc = toint(ad);

						(*dynamic_cast<Bunker*>(a.get_entitate(nr - 1))).set_adancime(adanc);
						break;
					}
					case 5:
					{
						break;
					}
					}
				}
				break;
			}
			case 4:
			{
				break;
			}
			}

			break;
		}
		case 3:
		{
			cout << "\nOptiuni:\n";
			cout << "1 - adaugarea unei entitati\n";
			cout << "2 - intoarcerea la meniul principal\n";
			int optiune_case3;

			string op3;
			cout << "\nOptiunea dumneavoastra: ";
			cin >> op3;
			while (toint(op3) != 1 && toint(op3) != 2)
			{
				cout << "Input invalid";
				cout << "\nOptiunea dumneavoastra: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op3;
			}
			optiune_case3 = toint(op3);

			cout << "\n";

			switch (optiune_case3)
			{
			case 1:
			{
				Locuinta* l;

				cout << "\nTipuri de locuinte:";
				cout << "\n1 - apartament";
				cout << "\n2 - casa";
				cout << "\n3 - bunker (oportunitate de neratat)";

				int tips;
				cout << "\n\nintroduceti tipul locuintei: ";
				string tip;
				cin >> tip;
				while (toint(tip) != 1 && toint(tip) != 2 && toint(tip) != 3)
				{
					cout << "Input invalid";
					cout << "\nintroduceti tipul locuintei: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> tip;
				}
				tips = toint(tip);

				if (tips == 1)
				{
					l = new Apartament();
					cin >> *dynamic_cast<Apartament*>(l);
				}
				else if (tips == 2)
				{
					l = new Casa();
					cin >> *dynamic_cast<Casa*>(l);
				}
				else
				{
					l = new Bunker();
					cin >> *dynamic_cast<Bunker*>(l);
				}

				a.add(l);
				break;
			}
			case 2:
			{
				break;
			}
			}
			break;
		}
		case 4:
		{
			cout << "\nOptiuni:\n";
			cout << "1 - eliminarea unei entitati\n";
			cout << "2 - intoarcerea la meniul principal\n";
			int optiune_case4;

			string op4;
			cout << "\nOptiunea dumneavoastra: ";
			cin >> op4;
			while (toint(op4) != 1 && toint(op4) != 2)
			{
				cout << "Input invalid";
				cout << "\nOptiunea dumneavoastra: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op4;
			}
			optiune_case4 = toint(op4);

			cout << "\n";

			switch (optiune_case4)
			{
			case 1:
			{
				int nr;
				cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
				string nre;
				cin >> nre;
				while (toint(nre) <= 0 || toint(nre) > a.get_nr_locuinte())
				{
					cout << "Input invalid";
					cout << "\nintroduceti numarul entitatii (1 - " << a.get_nr_locuinte() << "): ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> nre;
				}
				nr = toint(nre);

				a.delet(nr-1);
				break;
			}
			case 2:
			{
				break;
			}
			}
		}
		case 5:
		{
			break;
		}
		}
		cout << "\n\nOptiuni:\n";
		if (a.get_nr_locuinte() != 0)
			cout << "1 - afisare\n";
		if (a.get_nr_locuinte() != 0)
			cout << "2 - modificare\n";
		cout << "3 - adaugare\n";
		if (a.get_nr_locuinte() != 0)
			cout << "4 - eliminare\n";
		cout << "5 - terminare\n";

		string op0;
		cout << "\nOptiunea dumneavoastra: ";
		cin >> op0;
		while (toint(op0) != 5 && toint(op0) != 3 && (toint(op0) != 1 || a.get_nr_locuinte() == 0) && (toint(op0) != 2 || a.get_nr_locuinte() == 0) && (toint(op0) != 4 || a.get_nr_locuinte() == 0))
		{
			cout << "Input invalid";
			cout << "\nOptiunea dumneavoastra: ";
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> op0;
		}
		optiune = toint(op0);
	}
}




int main()
{
	meniu();
	return 0;
}
