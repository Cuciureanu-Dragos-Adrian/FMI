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


class Candidat
{
protected:
	string nume;
	string seria;
	int pasaport;
	int CI_P;
	float medie_bacalaureat;

public:
	Candidat() : nume(""), seria(""), CI_P(0), medie_bacalaureat(0) {}
	Candidat(string n = "", string s = "",int p = 0, int cip = 0, float mb = 0) : nume(n), seria(s),pasaport(p), CI_P(cip), medie_bacalaureat(mb) {}
	~Candidat() { cout << "Destructor Candidat\n"; }

	string get_nume()
	{
		return nume;
	}
	string get_seria()
	{
		return seria;
	}
	int get_pasaport()
	{
		return pasaport;
	}
	int get_CI_P()
	{
		return CI_P;
	}
	float get_medie_bacalaureat()
	{
		return medie_bacalaureat;
	}

	friend istream& operator >>(istream&, Candidat&);
	friend ostream& operator <<(ostream&, Candidat&);

	virtual void citire()
	{
		cout << "\nnume: ";
		cin >> nume;

		cout << "\nseria:";
		cin >> seria;

		cout << "\nintroduceti pasaport? (0-NU 1-DA)";
		cin >> pasaport;

		cout << "\nnumărul CI sau numărul Pașaportului:";
		cin >> CI_P;

		cout << "\nmedia la bac:";
		cin >> medie_bacalaureat;
	}

	virtual float CalculMA() = 0;
};

istream& operator>>(istream& in, Candidat& c)
{
	cout << "\nnume: ";
	in >> c.nume;

	cout << "\nseria: ";
	in >> c.seria;

	cout << "\nintroduceti pasaport? (0-NU 1-DA)";
	in >> c.pasaport;

	cout << "\nnumărul CI sau numărul Pașaportului: ";
	in >> c.CI_P;

	cout << "\nmedia la bac: ";
	in >> c.medie_bacalaureat;

	return in;
}

ostream& operator<<(ostream& out, Candidat& c)
{
	out << "\nnume: " << c.nume;

	out << "\nseria: " << c.seria;

	if (c.pasaport == 0)
		out << "\npasaport: nu";
	else
		out << "\npasaport: da";

	out << "\nnumarul CI sau numarul Pașaportului: " << c.CI_P;

	out << "\nmedia la bac: " << c.medie_bacalaureat;

	return out;
}





class DosarIF1 : public Candidat
{
protected:
	static int nrif1;
	int id;
	string cod_legitimatie;
	float nota_ps;

public:
	DosarIF1(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "", float nr = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_ps(nr) {}
	~DosarIF1() { cout << "Destructor DosarIF1\n"; }

	float get_nota_ps()
	{
		return nota_ps;
	}

	static void crestere_nrif1()
	{
		nrif1++;
	}

	friend istream& operator >>(istream&, DosarIF1&);
	friend ostream& operator <<(ostream&, DosarIF1&);

	void citire()
	{
		Candidat::citire();

		crestere_nrif1();

		id = nrif1;

		cod_legitimatie = to_string(id);

		cout << "\nnota proba scrisa: ";
		cin >> nota_ps;
	}

	float CalculMA()
	{
		float s = 0.8 * get_nota_ps() + 0.2 * get_medie_bacalaureat();
		return s;
	}
};

int DosarIF1::nrif1;

istream& operator>>(istream& in, DosarIF1& dif1)
{
	in >> (Candidat&)dif1;

	cout << "\nnota proba scrisa: ";
	in >> dif1.nota_ps;

	return in;
}

ostream& operator<<(ostream& out, DosarIF1& dif1)
{
	out << (Candidat&)dif1;

	out << "\nid:"<< dif1.id;

	out << "\ncod:" << dif1.cod_legitimatie;

	out << "\nnota proba scrisa: " << dif1.nota_ps;

	out << "\nmedie admitere: " << dif1.CalculMA();

	return out;
}




class DosarIF2 : public Candidat
{
private:
	static int nrif2;
	int id;
	string cod_legitimatie;
	float nota_po;
	float nota_a;

public:
	DosarIF2(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "", float nr = 0, float na = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr), nota_a(na) {}
	~DosarIF2() { cout << "Destructor DosarIF2\n"; }

	float get_nota_po()
	{
		return nota_po;
	}
	float get_nota_a()
	{
		return nota_a;
	}
	static void crestere_nrif2()
	{
		nrif2++;
	}

	friend istream& operator >>(istream&, DosarIF2&);
	friend ostream& operator <<(ostream&, DosarIF2&);

	void citire()
	{
		Candidat::citire();

		crestere_nrif2();

		id = nrif2;

		cod_legitimatie = "IF2_" + to_string(id);

		cout << "\nnota proba orala: ";
		cin >> nota_po;

		cout << "\nnota abslovire prima facultate: ";
		cin >> nota_a;
	}

	float CalculMA()
	{
		float s = 0.6 * get_nota_po() + 0.4 * get_nota_a();
		return s;
	}
};

int DosarIF2::nrif2;

istream& operator>>(istream& in, DosarIF2& dif2)
{
	in >> (Candidat&)dif2;

	cout << "\nnota proba orala: ";
	in >> dif2.nota_po;

	cout << "\nnota abslovire prima facultate: ";
	in >> dif2.nota_a;

	return in;
}

ostream& operator<<(ostream& out, DosarIF2& dif2)
{
	out << (Candidat&)dif2;

	out << "\nid:" << dif2.id;

	out << "\ncod:" << dif2.cod_legitimatie;

	out << "\nnota proba orala: " << dif2.nota_po;

	out << "\nnota abslovire prima facultate: " << dif2.nota_a;

	out << "\nmedie admitere: " << dif2.CalculMA();

	return out;
}




class DosarID1 : public Candidat
{
private:
	static int nrid1;
	int id;
	string cod_legitimatie;
	float nota_po;

public:
	DosarID1(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "", float nr = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr) {}
	~DosarID1() { cout << "Destructor DosarID1\n"; }

	float get_nota_po()
	{
		return nota_po;
	}

	static void crestere_nrid1()
	{
		nrid1++;
	}

	friend istream& operator >>(istream&, DosarID1&);
	friend ostream& operator <<(ostream&, DosarID1&);

	void citire()
	{
		Candidat::citire();

		crestere_nrid1();

		id = nrid1;

		cod_legitimatie = "ID1_" + to_string(id);

		cout << "\nnota proba orala: ";
		cin >> nota_po;
	}

	float CalculMA()
	{
		float s = 0.6 * get_nota_po() + 0.4 * get_medie_bacalaureat();
		return s;
	}
};

int DosarID1::nrid1;

istream& operator>>(istream& in, DosarID1& did1)
{
	in >> (Candidat&)did1;

	cout << "\nnota proba orala: ";
	in >> did1.nota_po;

	return in;
}

ostream& operator<<(ostream& out, DosarID1& did1)
{
	out << (Candidat&)did1;

	out << "\nid:" << did1.id;

	out << "\ncod:" << did1.cod_legitimatie;

	out << "\nnota proba orala: " << did1.nota_po;

	out << "\nmedie admitere: " << did1.CalculMA();

	return out;
}




class DosarID2 : public Candidat
{
private:
	static int nrid2;
	int id;
	string cod_legitimatie;
	float nota_po;
	float nota_a;

public:
	DosarID2(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "", float nr = 0, float na = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr), nota_a(na) {}
	~DosarID2() { cout << "Destructor DosarID2\n"; }

	float get_nota_po()
	{
		return nota_po;
	}
	float get_nota_a()
	{
		return nota_a;
	}

	static void crestere_nrid2()
	{
		nrid2++;
	}

	friend istream& operator >>(istream&, DosarID2&);
	friend ostream& operator <<(ostream&, DosarID2&);

	void citire()
	{
		Candidat::citire();

		crestere_nrid2();

		id = nrid2;

		cod_legitimatie = "ID2_" + to_string(id);

		cout << "\nnota proba orala: ";
		cin >> nota_po;

		cout << "\nnota abslovire prima facultate: ";
		cin >> nota_a;
	}

	float CalculMA()
	{
		float s = 0.6 * get_nota_po() + 0.4 * get_nota_a();
		return s;
	}
};

int DosarID2::nrid2;

istream& operator>>(istream& in, DosarID2& did2)
{
	in >> (Candidat&)did2;

	cout << "\nnota proba orala: ";
	in >> did2.nota_po;

	cout << "\nnota abslovire prima facultate: ";
	in >> did2.nota_a;

	return in;
}

ostream& operator<<(ostream& out, DosarID2& did2)
{
	out << (Candidat&)did2;

	out << "\nid:" << did2.id;

	out << "\ncod:" << did2.cod_legitimatie;

	out << "\nnota proba orala: " << did2.nota_po;

	out << "\nnota abslovire prima facultate: " << did2.nota_a;

	out << "\nmedie admitere: " << did2.CalculMA();

	return out;
}



class Gestiune
{
private:
	vector <Candidat*> v;
	int nrid;
	int nrif;

public:
	Gestiune(): v(0) {}
	~Gestiune() { cout << "Destructor gestiune\n"; }

	void set_nrid(int n)
	{
		nrid = n;
	}
	void set_nrif(int n)
	{
		nrif = n;
	}

	void add()
	{
		cout << "1 - DosarIF1\n";
		cout << "2 - DosarIF2\n";
		cout << "3 - DosarID1\n";
		cout << "4 - DosarID2\n";

		int tip_dosar;
		cout << "Tip dosar: ";
		cin >> tip_dosar;

		Candidat* aux;

		if (tip_dosar == 1)
		{
			aux = new DosarIF1();
			dynamic_cast<DosarIF1*>(aux)->citire();
		}
		else if (tip_dosar == 2)
		{
			aux = new DosarIF2();
			dynamic_cast<DosarIF2*>(aux)->citire();
		}
		else if (tip_dosar == 3)
		{
			aux = new DosarID1();
			dynamic_cast<DosarID1*>(aux)->citire();
		}
		else
		{
			aux = new DosarID2();
			dynamic_cast<DosarID2*>(aux)->citire();
		}

		v.push_back(aux);
	}

	void afis()
	{
		for (auto i : v)
		{
			if (typeid(*i) == typeid(DosarIF1))
			{
				cout << "\nDosarIF1:\n";
				cout << *dynamic_cast<DosarIF1*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarIF2))
			{
				cout << "\nDosarIF2:\n";
				cout << *dynamic_cast<DosarIF2*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarID1))
			{
				cout << "\nDosarID1:\n";
				cout << *dynamic_cast<DosarID1*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarID2))
			{
				cout << "\nDosarID2:\n";
				cout << *dynamic_cast<DosarID2*>(i) << "\n\n";
			}
		}
	}

	void afis_cal()
	{
		vector<Candidat*> vn(v);

		for(int i=0;i<vn.size();i++)
			for (int j = i; j < vn.size(); j++)
			{
				if ((*vn[i]).CalculMA() < (*vn[j]).CalculMA())
					swap(vn[i], vn[j]);
			}

		int nr1 = nrif;
		int nr2 = nrid;


		cout << "-------------IF-----------";
		for (int i = 0; i < vn.size(); i++)
		{
			if (nr1 > 0 && (*vn[i]).CalculMA() >= 5 && (typeid(*vn[i]) == typeid(DosarIF1) || typeid(*vn[i]) == typeid(DosarIF2)))
			{
				nr1--;
				if (typeid(*vn[i]) == typeid(DosarIF2))
					cout << *dynamic_cast<DosarIF2*>(vn[i]) << "\n\n";
				else 
					cout << *dynamic_cast<DosarIF1*>(vn[i]) << "\n\n";
			}
		}

		cout << "-------------ID-----------";
		for (int i = 0; i < vn.size(); i++)
		{
			if (nr2 > 0 && (*vn[i]).CalculMA() >= 5 && (typeid(*vn[i]) == typeid(DosarID1) || typeid(*vn[i]) == typeid(DosarID2)))
			{
				nr2--;
				if (typeid(*vn[i]) == typeid(DosarID2))
					cout << *dynamic_cast<DosarID2*>(vn[i]) << "\n\n";
				else
					cout << *dynamic_cast<DosarID1*>(vn[i]) << "\n\n";
			}
		}
	}

	void afis_cal_pas()
	{
		vector<Candidat*> vn(v);

		for (int i = 0; i < vn.size(); i++)
			for (int j = i; j < vn.size(); j++)
			{
				if ((*vn[i]).CalculMA() < (*vn[j]).CalculMA())
					swap(vn[i], vn[j]);
			}

		int nr1 = nrif;
		int nr2 = nrid;


		cout << "-------------IF-----------";
		for (int i = 0; i < vn.size(); i++)
		{
			if (nr1 > 0 && (*vn[i]).CalculMA() >= 5 && (typeid(*vn[i]) == typeid(DosarIF1) || typeid(*vn[i]) == typeid(DosarIF2)))
			{
				nr1--;
				if (typeid(*vn[i]) == typeid(DosarIF2) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarIF2*>(vn[i]) << "\n\n";
				else if (typeid(*vn[i]) == typeid(DosarIF1) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarIF1*>(vn[i]) << "\n\n";
			}
		}

		cout << "-------------ID-----------";
		for (int i = 0; i < vn.size(); i++)
		{
			if (nr2 > 0 && (*vn[i]).CalculMA() >= 5 && (typeid(*vn[i]) == typeid(DosarID1) || typeid(*vn[i]) == typeid(DosarID2)))
			{
				nr2--;
				if (typeid(*vn[i]) == typeid(DosarID2) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarID2*>(vn[i]) << "\n\n";
				else if (typeid(*vn[i]) == typeid(DosarID1) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarID1*>(v[i]) << "\n\n";
			}
		}
	}
};


void meniu()
{
	Gestiune g;
	int nrid, nrif;

	cout << "introduceti nr de admisi if: ";
	cin >> nrif;
	g.set_nrif(nrif);

	cout << "\nintroduceti nr de admisi id: ";
	cin >> nrid;
	g.set_nrid(nrid);

	cout << "Optiuni:\n";
	cout << "0 - terminare\n";
	cout << "1 - adaugare\n";
	cout << "2 - afisare\n";
	cout << "3 - afisare admisi\n";
	cout << "4 - afisare admisi_pasaport\n";
	cout << "Optiune: ";

	int optiune;
	string op;
	cin >> op;
	while (toint(op) < 0 || toint(op) > 4)
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
			g.add();
			break;
		}
		case 2:
		{
			g.afis();
			break;
		}
		case 3:
		{
			g.afis_cal();
			break;
		}
		case 4:
		{
			g.afis_cal_pas();
			break;
		}
		}

		cout << "Optiuni:\n";
		cout << "0 - terminare\n";
		cout << "1 - adaugare\n";
		cout << "2 - afisare\n";
		cout << "3 - afisare admisi\n";
		cout << "4 - afisare admisi_pasaport\n";
		cout << "Optiune: ";

		cin >> op;
		while (toint(op) < 0 || toint(op) > 4)
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