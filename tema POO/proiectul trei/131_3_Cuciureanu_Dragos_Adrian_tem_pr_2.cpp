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
	int exista_discount;
	float pret_mp;

public:
	Locuinta() : numeClient(""), suprafataUtila(0), discount(0), exista_discount(0), pret_mp(1) {}
	Locuinta(string s) : numeClient(s), suprafataUtila(0), discount(0), exista_discount(0), pret_mp(1) {};
	Locuinta(string s, int x) : numeClient(s), suprafataUtila(x), discount(0), exista_discount(0), pret_mp(1) {};
	Locuinta(string s, int x, float d) : numeClient(s), suprafataUtila(x), discount(d), exista_discount(0), pret_mp(1) {};
	Locuinta(string s, int x, float d, int e) : numeClient(s), suprafataUtila(x), discount(d), exista_discount(e), pret_mp(1) {};
	Locuinta(string s, int x, float d, int e, float p) : numeClient(s), suprafataUtila(x), discount(d), exista_discount(e), pret_mp(p) {};
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
	int get_exista_discount()
	{
		return exista_discount;
	}
	float get_pret_mp()
	{
		return pret_mp;
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
	void set_exista_discount(int nr)
	{
		exista_discount = nr;
	}
	void set_pret_mp(float nr)
	{
		pret_mp = nr;
	}

	friend istream& operator >>(istream&, Locuinta&);
	friend ostream& operator <<(ostream&, Locuinta&);

	Locuinta& operator = (Locuinta&);

	void afisare_locuinta();

	virtual float CalculChirie() = 0;
};


Locuinta::Locuinta(Locuinta& l)
{
	numeClient = l.numeClient;
	suprafataUtila = l.suprafataUtila;
	discount = l.discount;
	exista_discount = l.exista_discount;
	pret_mp = l.pret_mp;
}

istream& operator>>(istream& in, Locuinta& l)
{
	cout << "\nnume client: ";
	in >> l.numeClient;

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

	cout << "\ndiscount(intre 0 si 10): ";
	string dis;
	in >> dis;
	while (tofloat(dis) < 0 || tofloat(dis) > 10)
	{
		cout << "Input invalid";
		cout << "\ndiscount(intre 0 si 10): ";
		in.ignore(numeric_limits < streamsize > ::max(), '\n');
		in >> dis;
	}
	l.discount = tofloat(dis);

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
	l.exista_discount = toint(disc);

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
	l.pret_mp = tofloat(pmp);

	return in;
}

ostream& operator << (ostream& out, Locuinta& l)
{
	out << "\n\nnume client: " << l.get_numeClient();
	out << "\nsuprafata utila: " << l.get_suprafataUtila() << " metri patrati";
	out << "\ndiscount: " << l.get_discount() << "%";
	if (l.exista_discount == 0)
		out << "\ndiscount inactiv";
	else
		out << "\ndiscount activ";
	out << "\npret metru/patrat: " << l.pret_mp;
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
	Apartament() : Locuinta("", 0, 0, 0, 0), etaj(0) { nr_apartamente++; };
	Apartament(string s, int x, float d, int e, float p) : Locuinta(s, x, d, e, p), etaj(0) { nr_apartamente++; }
	Apartament(string s, int x, float d, int e, float p, int et) : Locuinta(s, x, d, e, p), etaj(et) { nr_apartamente++; }
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

	float CalculChirie();

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
	out << "\nchiria: " << a.CalculChirie() << " unitati";
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

float Apartament::CalculChirie()
{
	float rez;
	rez = get_pret_mp() * get_suprafataUtila() * (1 - get_exista_discount() * get_discount() / 100.0);
	return rez;
}



class Casa : public Locuinta
{
private:
	static int nr_case;
	int suprafataCurte;

public:
	Casa() : Locuinta("", 0, 0, 0, 0), suprafataCurte(0) { nr_case++; }
	Casa(string s, int x, float d, int e, float p) : Locuinta(s, x, d, e, p), suprafataCurte(0) { nr_case++; }
	Casa(string s, int x, float d, int e, float p, int supr) : Locuinta(s, x, d, e, p), suprafataCurte(supr) { nr_case++; }
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

	float CalculChirie();

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
	out << "\nchiria: " << c.CalculChirie() << " unitati";
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

float Casa::CalculChirie()
{
	float rez;
	rez = get_pret_mp() * (get_suprafataUtila() + 0.2 * get_suprafataCurte()) * (1 - get_exista_discount() * get_discount() / 100.0);
	return rez;
}



class Bunker : public Locuinta
{
private:
	static int nr_bunkere;
	int adancime;

public:
	Bunker() : Locuinta("", 0, 0), adancime(0) { nr_bunkere++; }
	Bunker(string s, int x, float d, int e, float p) : Locuinta(s, x, d, e, p), adancime(0) { nr_bunkere++; }
	Bunker(string s, int x, float d, int e, float p, int ad) : Locuinta(s, x, d, e, p), adancime(ad) { nr_bunkere++; }
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

	float CalculChirie();

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
	out << "\nchiria: " << b.CalculChirie() << " unitati";
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

float Bunker::CalculChirie()
{
	float rez;
	rez = get_pret_mp() * get_suprafataUtila() * (1 - get_exista_discount() * get_discount() / 100.0) * ((100 + get_adancime()) / 100);
	return rez;
}


// template normal

template <class Tip_Locuinta>
class Gestiune
{
	vector <Tip_Locuinta*> v;
	int index;
	static int id;

public:
	Gestiune() : v(0) { index = 0; };
	~Gestiune() { index = 0;  v.clear(); };

	void operator+=(Tip_Locuinta&);
	void afisare();
	void afisare_locuinte();
	void sort_by_chirie();
};

//template <class Tip_Locuinta> int Gestiune<Tip_Locuinta>::index = 0;
template <> int Gestiune<Apartament>::id = 101;
template <> int Gestiune<Bunker>::id = 303;

template <class Tip_Locuinta>
void Gestiune<Tip_Locuinta>::operator +=(Tip_Locuinta& tl)
{
	Tip_Locuinta* aux = new Tip_Locuinta(tl);
	v.push_back(aux);
	index++;
}

template <class Tip_Locuinta>
void Gestiune <Tip_Locuinta>::afisare()
{
	if (typeid(Tip_Locuinta) == typeid(Apartament))
		cout << "\n\nLantul " << id << " are " << index << " apartamente";
	else
		cout << "\n\nLantul " << id << " are " << index << " bunkere";

	/*
	for (int i = 0; i < v.size(); i++)
		cout << *dynamic_cast<Tip_Locuinta*>(v[i]);
	*/

	int i = 1;

	for_each(v.begin(), v.end(), [&i](Tip_Locuinta* tl)
		{
			if (typeid(Tip_Locuinta) == typeid(Apartament))
				cout << "\n\n\nApartamentul " << i++ << ":\n";
			else
				cout << "\n\n\nBunkerul " << i++ << ":\n";

			cout << *tl;
		});
}

template <class Tip_Locuinta>
void Gestiune <Tip_Locuinta>::afisare_locuinte()
{
	if (typeid(Tip_Locuinta) == typeid(Apartament))
		cout << "\n\nLantul " << id << " are " << index << " apartamente(locuinte)";
	else
		cout << "\n\nLantul " << id << " are " << index << " bunkere(locuinte)";

	/*
	for (int i = 0; i < v.size(); i++)
		cout << *dynamic_cast<Tip_Locuinta*>(v[i]);
	*/

	int i = 1;

	for_each(v.begin(), v.end(), [&i](Locuinta* l)
		{
			if (typeid(Tip_Locuinta) == typeid(Apartament))
				cout << "\n\n\nApartamentul(locuinta) " << i++ << ":\n";
			else
				cout << "\n\n\nBunkerul(locuinta) " << i++ << ":\n";

			cout << *l;
		});
}

template <class Tip_Locuinta>
void Gestiune <Tip_Locuinta>::sort_by_chirie()
{
	sort(v.begin(), v.end(), [](Tip_Locuinta* a, Tip_Locuinta* b)
		{
			return (*a).CalculChirie() < (*b).CalculChirie();
		});
}



//template mostenit

template <class Tip_Locuinta>
class Mini_Gestiune : public Gestiune<Tip_Locuinta>
{
	static const int limita = 5;
	vector <Tip_Locuinta*> v;
	int index;
	static int id;

public:
	Mini_Gestiune() : v(0) { index = 0; };
	~Mini_Gestiune() { index = 0;  v.clear(); };

	void operator+=(Tip_Locuinta&);
	void afisare();
	void afisare_locuinte();
	void sort_by_chirie();
};

template <> int Mini_Gestiune<Apartament>::id = 101101;
template <> int Mini_Gestiune<Bunker>::id = 303303;

template <class Tip_Locuinta>
void Mini_Gestiune<Tip_Locuinta>::operator +=(Tip_Locuinta& tl)
{
	Tip_Locuinta* aux = new Tip_Locuinta(tl);

	if (v.size() == limita)
	{
		cout << "\n\nLimita acestei mini gestiuni din pacate a fost atinsa :(\n";
		cout << "Doriti sa dati overwrite la un element din gestiune sau sa nu adaugati ultimul element citit?\n";
		cout << "Optiuni:\n";
		cout << "1 - dati overwrite unui element din mini gestiune\n";
		cout << "2 - ignorati ultimul element citit\n";
		cout << "Optiune: ";

		int optiune;
		string op;
		cin >> op;

		while (toint(op) != 1 && toint(op) != 2)
		{
			cout << "Input invalid";
			cout << "\nOptiune: ";
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> op;
		}
		optiune = toint(op);

		if (optiune == 1)
		{
			cout << "Introduceti indexul elementul pe care doriti sa-l inlocuiti (intre 1 si " << limita << "): ";

			int idx;
			string id;
			cin >> id;

			while (toint(id) < 1 || toint(id) > limita)
			{
				cout << "Input invalid";
				cout << "\nIntroduceti indexul elementul pe care doriti sa-l inlocuiti (intre 1 si " << limita << "): ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> id;
			}
			idx = toint(id);

			v[idx - 1] = aux;
		}
	}
	else
	{
		v.push_back(aux);
		index++;
	}
}

template <class Tip_Locuinta>
void Mini_Gestiune <Tip_Locuinta>::afisare()
{
	if (typeid(Tip_Locuinta) == typeid(Apartament))
		cout << "\n\nLantul " << id << " are " << index << " apartamente";
	else
		cout << "\n\nLantul " << id << " are " << index << " bunkere";

	/*
	for (int i = 0; i < v.size(); i++)
		cout << *dynamic_cast<Tip_Locuinta*>(v[i]);
	*/

	int i = 1;

	for_each(v.begin(), v.end(), [&i](Tip_Locuinta* tl)
		{
			if (typeid(Tip_Locuinta) == typeid(Apartament))
				cout << "\n\n\nApartamentul " << i++ << ":\n";
			else
				cout << "\n\n\nBunkerul " << i++ << ":\n";

			cout << *tl;
		});
}

template <class Tip_Locuinta>
void Mini_Gestiune <Tip_Locuinta>::afisare_locuinte()
{
	if (typeid(Tip_Locuinta) == typeid(Apartament))
		cout << "\n\nLantul " << id << " are " << index << " apartamente(locuinte)";
	else
		cout << "\n\nLantul " << id << " are " << index << " bunkere(locuinte)";

	/*
	for (int i = 0; i < v.size(); i++)
		cout << *dynamic_cast<Tip_Locuinta*>(v[i]);
	*/

	int i = 1;

	for_each(v.begin(), v.end(), [&i](Locuinta* l)
		{
			if (typeid(Tip_Locuinta) == typeid(Apartament))
				cout << "\n\n\nApartamentul(locuinta) " << i++ << ":\n";
			else
				cout << "\n\n\nBunkerul(locuinta) " << i++ << ":\n";

			cout << *l;
		});
}

template <class Tip_Locuinta>
void Mini_Gestiune <Tip_Locuinta>::sort_by_chirie()
{
	sort(v.begin(), v.end(), [](Tip_Locuinta* a, Tip_Locuinta* b)
		{
			return (*a).CalculChirie() < (*b).CalculChirie();
		});
}



//specializare

template <>
class Gestiune<Casa>
{
	vector <Casa*> v;
	static const int id = 202;
	int index;

public:
	Gestiune() : v(0) { index = 0; }
	~Gestiune() { v.clear(); }

	int get_index()
	{
		return index;
	}

	void operator+=(Casa& c)
	{
		Casa* aux = new Casa(c);
		v.push_back(aux);
		index++;
	}

	void afisare_chirie()
	{
		cout << "\nLantul " << id << " are " << index << " case, iar chiria este: ";
		float s = 0;

		/*
		for (int i = 0; i < v.size(); i++)
		{
			s += (*dynamic_cast<Casa*>(v[i])).CalculChirie();
		}
		*/

		for_each(v.begin(), v.end(), [&s](Casa* c)
			{
				s += (*dynamic_cast<Casa*>(c)).CalculChirie();
			});

		cout << s << " unitati\n";
	}
};



void meniu_initial()
{
	/*
	Gestiune<Casa> g_c;
	Casa c1, c2;
	cin >> c1 >> c2;
	g_c += c1;
	g_c += c2;
	g_c.afisare_chirie();
	*/

	/*
	Gestiune<Apartament> g_a;
	Apartament a1, a2;
	cin >> a1 >> a2;
	g_a += a1;
	g_a += a2;
	g_a.afisare();
	*/

	/*
	Gestiune<Bunker> g_b;
	Bunker b1;
	cin >> b1;
	g_b += b1;
	g_b.afisare_locuinte();
	*/

	/*
	Mini_Gestiune<Apartament> mg_a;
	Apartament a1, a2;
	cin >> a1 >> a2;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a2;
	mg_a.afisare();
	*/

	Mini_Gestiune<Apartament> mg_a;
	Apartament a1, a2;
	cin >> a1 >> a2;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a1;
	mg_a += a2;
	mg_a.sort_by_chirie();
	mg_a.afisare();
}

void meniu()
{
	Gestiune<Apartament> ga;
	Gestiune<Casa> gc;
	Gestiune<Bunker> gb;
	Mini_Gestiune<Apartament> mga;
	Mini_Gestiune<Bunker> mgb;

	cout << "Optiuni:\n";
	cout << "0 - terminare\n";
	cout << "1 - afisare\n";
	cout << "2 - adaugare\n";
	cout << "3 - sortare\n";
	cout << "Optiune: ";

	int optiune;
	string op;
	cin >> op;
	while (toint(op) < 0 || toint(op) > 3)
	{
		cout << "Input invalid";
		cout << "\nOptiune: ";
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cin >> op;
	}
	optiune = toint(op);

	while (optiune)
	{
		switch (optiune)
		{
		case 1:
		{
			cout << "\nOptiuni:\n";
			cout << "1 - afisarea gestiunii de apartamente\n";
			cout << "2 - afisarea gestiunii de bunkere\n";
			cout << "3 - afisarea mini-gestiunii de apartamente\n";
			cout << "4 - afisarea mini-gestiunii de bunkere\n";
			cout << "5 - afisarea gestiunii de apartamente(doar locuintele)\n";
			cout << "6 - afisarea gestiunii de bunkere(doar locuintele)\n";
			cout << "7 - afisarea mini-gestiunii de apartamente(doar locuintele)\n";
			cout << "8 - afisarea mini-gestiunii de bunkere(doar locuintele)\n";
			cout << "9 - afisarea sumei chiriilor din gestiune specializata de case\n";
			cout << "10 - intoarcerea la meniul principal\n";
			cout << "Optiune: ";

			int optiune_case1;
			string op1;
			cin >> op1;
			while (toint(op1) < 1 || toint(op1) > 10)
			{
				cout << "Input invalid";
				cout << "\nOptiune: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op1;
			}
			optiune_case1 = toint(op1);

			switch (optiune_case1)
			{
			case 1:
			{
				ga.afisare();
				break;
			}
			case 2:
			{
				gb.afisare();
				break;
			}
			case 3:
			{
				mga.afisare();
				break;
			}
			case 4:
			{
				mgb.afisare();
				break;
			}
			case 5:
			{
				ga.afisare_locuinte();
				break;
			}
			case 6:
			{
				gb.afisare_locuinte();
				break;
			}
			case 7:
			{
				mga.afisare_locuinte();
				break;
			}
			case 8:
			{
				mgb.afisare_locuinte();
				break;
			}
			case 9:
			{
				gc.afisare_chirie();
				break;
			}
			case 10:
			{
				break;
			}
			}

			break;
		}

		case 2:
		{
			cout << "\nOptiuni:\n";
			cout << "1 - apartament\n";
			cout << "2 - bunker\n";
			cout << "3 - casa\n";
			cout << "4 - intoarcerea la meniul principal\n";
			cout << "Optiune: ";

			int optiune_case2;
			string op2;
			cin >> op2;
			while (toint(op2) < 1 || toint(op2) > 4)
			{
				cout << "Input invalid";
				cout << "\nOptiune: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op2;
			}
			optiune_case2 = toint(op2);

			switch (optiune_case2)
			{
			case 1:
			{
				Apartament a;
				cin >> a;

				cout << "\nOptiuni:\n";
				cout << "1 - introduceti in gestiuena de apartamente\n";
				cout << "2 - introduceti in mini-gestiuena de apartamente\n";
				cout << "3 - nu introduceti\n";
				cout << "Optiune: ";

				int optiune_case2_1;
				string op2_1;
				cin >> op2_1;
				while (toint(op2_1) < 1 || toint(op2_1) > 3)
				{
					cout << "Input invalid";
					cout << "\nOptiune: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> op2_1;
				}
				optiune_case2_1 = toint(op2_1);

				if (optiune_case2_1 == 1)
					ga += a;
				if (optiune_case2_1 == 2)
					mga += a;

				break;
			}
			case 2:
			{
				Bunker b;
				cin >> b;

				cout << "\nOptiuni:\n";
				cout << "1 - introduceti in gestiuena de apartamente\n";
				cout << "2 - introduceti in mini-gestiuena de apartamente\n";
				cout << "3 - nu introduceti\n";
				cout << "Optiune: ";

				int optiune_case2_2;
				string op2_2;
				cin >> op2_2;
				while (toint(op2_2) < 1 || toint(op2_2) > 3)
				{
					cout << "Input invalid";
					cout << "\nOptiune: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> op2_2;
				}
				optiune_case2_2 = toint(op2_2);

				if (optiune_case2_2 == 1)
					gb += b;
				if (optiune_case2_2 == 2)
					mgb += b;

				break;
			}
			case 3:
			{
				Casa c;
				cin >> c;
				gc += c;
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
			cout << "1 - sortarea gestiunii de apartamente(dupa chirii)\n";
			cout << "2 - sortarea gestiunii de bunkere(dupa chirii)\n";
			cout << "3 - sortarea mini-gestiunii de apartamente(dupa chirii)\n";
			cout << "4 - sortarea mini-gestiunii de bunkere(dupa chirii)\n";
			cout << "5 - intoarcerea la meniul principal\n";
			cout << "Optiune: ";

			int optiune_case3;
			string op3;
			cin >> op3;
			while (toint(op3) < 1 || toint(op3) > 10)
			{
				cout << "Input invalid";
				cout << "\nOptiune: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> op3;
			}
			optiune_case3 = toint(op3);

			switch (optiune_case3)
			{
			case 1:
			{
				ga.sort_by_chirie();
				break;
			}
			case 2:
			{
				gb.sort_by_chirie();
				break;
			}
			case 3:
			{
				mga.sort_by_chirie();
				break;
			}
			case 4:
			{
				mgb.sort_by_chirie();
				break;
			}
			case 5:
			{
				break;
			}
			}

			break;
		}

		}

		cout << "\n\n\nOptiuni:\n";
		cout << "0 - terminare\n";
		cout << "1 - afisare\n";
		cout << "2 - adaugare\n";
		cout << "3 - sortare\n";
		cout << "Optiune: ";

		cin >> op;
		while (toint(op) < 0 || toint(op) > 3)
		{
			cout << "Input invalid";
			cout << "\nOptiune: ";
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			cin >> op;
		}
		optiune = toint(op);
	}
}



int main()
{
	meniu();
	return 0;
}
