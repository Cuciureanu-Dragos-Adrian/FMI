#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

ifstream fin("citire.in");
ofstream fout("afisare.out");


class CA {
public:
	virtual ~CA() {};

	friend istream& operator>>(istream&, CA&);

	friend ostream& operator<<(ostream&, const CA&);

	virtual void citire(istream&) = 0;

	virtual void afisare(ostream&) = 0;
};

istream& operator>>(istream& in, CA& ca) {
	ca.citire(in);
	return in;
}

ostream& operator<<(ostream& out, CA& ca) {
	ca.afisare(out);
	return out;
}


class Candidat : public CA {
protected:
	string nume;
	string seria;
	int pasaport;
	int CI_P;
	float medie_bacalaureat;

public:
	Candidat() : nume(""), seria(""), CI_P(0), medie_bacalaureat(0) {}

	Candidat(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0) : nume(n), seria(s), pasaport(p),
		CI_P(cip), medie_bacalaureat(mb) {}

	~Candidat() { cout << "Destructor Candidat\n"; }

	string get_nume() {
		return nume;
	}

	string get_seria() {
		return seria;
	}

	int get_pasaport() {
		return pasaport;
	}

	int get_CI_P() {
		return CI_P;
	}

	float get_medie_bacalaureat() {
		return medie_bacalaureat;
	}

	void citire(istream&) override;

	void afisare(ostream&) override;

	virtual float CalculMA() = 0;
};

void Candidat::citire(istream& in) {
	cout << "\nnume: ";
	in >> nume;

	cout << "\nseria: ";
	in >> seria;

	cout << "\nintroduceti pasaport? (0-NU 1-DA)";
	in >> pasaport;

	cout << "\nnumarul CI sau numarul Pasaportului: ";
	in >> CI_P;

	cout << "\nmedia la bac: ";
	in >> medie_bacalaureat;
}

void Candidat::afisare(ostream& out) {
	out << "\nnume: " << nume;
	out << "\nseria: " << seria;

	if (pasaport == 0)
		out << "\npasaport: nu";
	else
		out << "\npasaport: da";

	out << "\nnumarul CI sau numarul Pasaportului: " << CI_P;
	out << "\nmedia la bac: " << medie_bacalaureat;
}


class DosarIF1 : public Candidat {
protected:
	static int nrif1;
	int id;
	string cod_legitimatie;
	float nota_ps;

public:
	DosarIF1(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "",
		float nr = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_ps(nr) {}

	~DosarIF1() { cout << "Destructor DosarIF1\n"; }

	float get_nota_ps() {
		return nota_ps;
	}

	static void crestere_nrif1() {
		nrif1++;
	}

	void citire(istream&) override;

	void afisare(ostream&) override;

	float CalculMA() {
		const float s = 0.8 * get_nota_ps() + 0.2 * get_medie_bacalaureat();
		return s;
	}
};

int DosarIF1::nrif1;

void DosarIF1::citire(istream& in) {
	Candidat::citire(in);

	cout << "\nnota proba scrisa: ";
	in >> nota_ps;

}

void DosarIF1::afisare(ostream& out) {
	Candidat::afisare(out);

	out << "\nnota proba scrisa: " << nota_ps;

	out << "\nmedie admitere: " << CalculMA();
}


class DosarIF2 : public Candidat {
protected:
	static int nrif2;
	int id;
	string cod_legitimatie;
	float nota_po;
	float nota_a;

public:
	DosarIF2(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "",
		float nr = 0, float na = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr),
		nota_a(na) {}

	~DosarIF2() { cout << "Destructor DosarIF2\n"; }

	float get_nota_po() {
		return nota_po;
	}

	float get_nota_a() {
		return nota_a;
	}

	static void crestere_nrif2() {
		nrif2++;
	}

	void citire(istream&) override;

	void afisare(ostream&) override;

	float CalculMA() {
		float s = 0.6 * get_nota_po() + 0.4 * get_nota_a();
		return s;
	}
};

int DosarIF2::nrif2;

void DosarIF2::citire(istream& in) {
	Candidat::citire(in);

	cout << "\nnota proba orala: ";
	in >> nota_po;

	cout << "\nnota abslovire prima facultate: ";
	in >> nota_a;
}

void DosarIF2::afisare(ostream& out) {
	Candidat::afisare(out);

	out << "\nid:" << id;

	out << "\ncod:" << cod_legitimatie;

	out << "\nnota proba orala: " << nota_po;

	out << "\nnota abslovire prima facultate: " << nota_a;

	out << "\nmedie admitere: " << CalculMA();
}


class DosarID1 : public Candidat {
private:
	static int nrid1;
	int id;
	string cod_legitimatie;
	float nota_po;

public:
	DosarID1(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "",
		float nr = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr) {}

	~DosarID1() { cout << "Destructor DosarID1\n"; }

	float get_nota_po() {
		return nota_po;
	}

	static void crestere_nrid1() {
		nrid1++;
	}

	void citire(istream&) override;

	void afisare(ostream&) override;

	float CalculMA() {
		float s = 0.6 * get_nota_po() + 0.4 * get_medie_bacalaureat();
		return s;
	}
};

int DosarID1::nrid1;

void DosarID1::citire(istream& in) {
	Candidat::citire(in);

	cout << "\nnota proba orala: ";
	in >> nota_po;
}

void DosarID1::afisare(ostream& out) {
	Candidat::afisare(out);

	out << "\nid:" << id;

	out << "\ncod:" << cod_legitimatie;

	out << "\nnota proba orala: " << nota_po;

	out << "\nmedie admitere: " << CalculMA();
}


class DosarID2 : public Candidat {
private:
	static int nrid2;
	int id;
	string cod_legitimatie;
	float nota_po;
	float nota_a;

public:
	DosarID2(string n = "", string s = "", int p = 0, int cip = 0, float mb = 0, int i = 0, string cd = "",
		float nr = 0, float na = 0) : Candidat(n, s, p, cip, mb), id(i), cod_legitimatie(cd), nota_po(nr),
		nota_a(na) {}

	~DosarID2() { cout << "Destructor DosarID2\n"; }

	float get_nota_po() {
		return nota_po;
	}

	float get_nota_a() {
		return nota_a;
	}

	static void crestere_nrid2() {
		nrid2++;
	}

	void citire(istream&) override;

	void afisare(ostream&) override;

	float CalculMA() {
		float s = 0.6 * get_nota_po() + 0.4 * get_nota_a();
		return s;
	}
};

int DosarID2::nrid2;

void DosarID2::citire(istream& in) {
	Candidat::citire(in);

	cout << "\nnota proba orala: ";
	in >> nota_po;

	cout << "\nnota abslovire prima facultate: ";
	in >> nota_a;
}

void DosarID2::afisare(ostream& out) {
	Candidat::afisare(out);

	out << "\nid:" << id;

	out << "\ncod:" << cod_legitimatie;

	out << "\nnota proba orala: " << nota_po;

	out << "\nnota abslovire prima facultate: " << nota_a;

	out << "\nmedie admitere: " << CalculMA();
}


class DosarDD : public DosarID2 {
protected:
	int xax;

public:
	void citire(istream&) override;

	void afisare(ostream&) override;
};

void DosarDD::citire(istream& in) {
	DosarID2::citire(in);

	cout << "\nxax: ";
	in >> xax;
}

void DosarDD::afisare(ostream& out) {
	DosarID2::afisare(out);

	out << "\nxax:" << xax;
}



class Gestiune {
private:
	vector<Candidat*> v;
	int nrid;
	int nrif;

public:
	Gestiune() : v(0) {}

	~Gestiune() { cout << "Destructor gestiune\n"; }

	void set_nrid(int n) {
		nrid = n;
	}

	void set_nrif(int n) {
		nrif = n;
	}

	void add() {
		cout << "1 - DosarIF1\n";
		cout << "2 - DosarIF2\n";
		cout << "3 - DosarID1\n";
		cout << "4 - DosarID2\n";

		int tip_dosar;
		cout << "Tip dosar: ";
		cin >> tip_dosar;

		Candidat* aux;

		if (tip_dosar == 1) {
			aux = new DosarIF1();
			dynamic_cast<DosarIF1*>(aux)->citire(cin);
		}
		else if (tip_dosar == 2) {
			aux = new DosarIF2();
			dynamic_cast<DosarIF2*>(aux)->citire(cin);
		}
		else if (tip_dosar == 3) {
			aux = new DosarID1();
			dynamic_cast<DosarID1*>(aux)->citire(cin);
		}
		else if (tip_dosar == 4) {
			aux = new DosarID2();
			dynamic_cast<DosarID2*>(aux)->citire(cin);
		}
		else
		{
			aux = new DosarDD();
			dynamic_cast<DosarDD*>(aux)->citire(cin);
		}

		v.push_back(aux);
	}

	void afis() {
		for (auto i : v) {
			if (typeid(*i) == typeid(DosarIF1)) {
				cout << "\nDosarIF1:\n";
				cout << *dynamic_cast<DosarIF1*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarIF2)) {
				cout << "\nDosarIF2:\n";
				cout << *dynamic_cast<DosarIF2*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarID1)) {
				cout << "\nDosarID1:\n";
				cout << *dynamic_cast<DosarID1*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarID2)) {
				cout << "\nDosarID2:\n";
				cout << *dynamic_cast<DosarID2*>(i) << "\n\n";
			}
			else if (typeid(*i) == typeid(DosarDD)) {
				cout << "\nDosarDD:\n";
				cout << *dynamic_cast<DosarDD*>(i) << "\n\n";
			}
		}
	}

	void afis_cal() {
		vector<Candidat*> vn(v);

		for (int i = 0; i < vn.size(); i++)
			for (int j = i; j < vn.size(); j++) {
				if ((*vn[i]).CalculMA() < (*vn[j]).CalculMA())
					swap(vn[i], vn[j]);
			}

		int nr1 = nrif;
		int nr2 = nrid;


		cout << "-------------IF-----------";
		for (int i = 0; i < vn.size(); i++) {
			if (nr1 > 0 && (*vn[i]).CalculMA() >= 5 &&
				(typeid(*vn[i]) == typeid(DosarIF1) || typeid(*vn[i]) == typeid(DosarIF2))) {
				nr1--;
				if (typeid(*vn[i]) == typeid(DosarIF2))
					cout << *dynamic_cast<DosarIF2*>(vn[i]) << "\n\n";
				else
					cout << *dynamic_cast<DosarIF1*>(vn[i]) << "\n\n";
			}
		}

		cout << "-------------ID-----------";
		for (int i = 0; i < vn.size(); i++) {
			if (nr2 > 0 && (*vn[i]).CalculMA() >= 5 &&
				(typeid(*vn[i]) == typeid(DosarID1) || typeid(*vn[i]) == typeid(DosarID2))) {
				nr2--;
				if (typeid(*vn[i]) == typeid(DosarID2))
					cout << *dynamic_cast<DosarID2*>(vn[i]) << "\n\n";
				else
					cout << *dynamic_cast<DosarID1*>(vn[i]) << "\n\n";
			}
		}
	}

	void afis_cal_pas() {
		vector<Candidat*> vn(v);

		for (int i = 0; i < vn.size(); i++)
			for (int j = i; j < vn.size(); j++) {
				if ((*vn[i]).CalculMA() < (*vn[j]).CalculMA())
					swap(vn[i], vn[j]);
			}

		int nr1 = nrif;
		int nr2 = nrid;


		cout << "-------------IF-----------";
		for (int i = 0; i < vn.size(); i++) {
			if (nr1 > 0 && (*vn[i]).CalculMA() >= 5 &&
				(typeid(*vn[i]) == typeid(DosarIF1) || typeid(*vn[i]) == typeid(DosarIF2))) {
				nr1--;
				if (typeid(*vn[i]) == typeid(DosarIF2) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarIF2*>(vn[i]) << "\n\n";
				else if (typeid(*vn[i]) == typeid(DosarIF1) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarIF1*>(vn[i]) << "\n\n";
			}
		}

		cout << "-------------ID-----------";
		for (int i = 0; i < vn.size(); i++) {
			if (nr2 > 0 && (*vn[i]).CalculMA() >= 5 &&
				(typeid(*vn[i]) == typeid(DosarID1) || typeid(*vn[i]) == typeid(DosarID2))) {
				nr2--;
				if (typeid(*vn[i]) == typeid(DosarID2) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarID2*>(vn[i]) << "\n\n";
				else if (typeid(*vn[i]) == typeid(DosarID1) && (*vn[i]).get_pasaport() == 1)
					cout << *dynamic_cast<DosarID1*>(v[i]) << "\n\n";
			}
		}
	}
};


class Meniu {
private:

	Meniu();

	Meniu(const Meniu&) = delete;

	Meniu& operator=(const Meniu&) = delete;

	vector<pair<string, function<void()>>> operatii;

	static Meniu* instance;

	Gestiune g;

public:
	void run();

	static Meniu* get_instance();

	static void delete_instance();

};

Meniu* Meniu::instance = nullptr;

Meniu::Meniu() {
	operatii.push_back(make_pair(" adaugare", [&]() {
		g.add();
		}));

	operatii.push_back(make_pair(" afisare", [&]() {
		g.afis();
		}));
}

void Meniu::run() {
	cout << 0 << " inchidere" << "\n";

	for (int i = 1; i <= operatii.size(); i++)
		cout << i << operatii[i - 1].first << "\n";

	int op;
	cout << "optiune: ";
	cin >> op;

	while (op) {
		operatii[op - 1].second();

		cout << "\n\n";
		cout << 0 << " inchidere" << "\n";

		for (int i = 1; i <= operatii.size(); i++)
			cout << i << operatii[i - 1].first << "\n";

		cout << "optiune: ";
		cin >> op;
	}
}

Meniu* Meniu::get_instance() {
	if (!instance)
		instance = new Meniu();

	return instance;
}

void Meniu::delete_instance() {
	delete instance;
	instance = nullptr;
}


int main() {
	Meniu::get_instance()->run();
	Meniu::delete_instance();

	return 0;
}
