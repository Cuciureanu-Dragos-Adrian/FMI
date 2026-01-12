/* nume: Cuciureanu Dragos-Adrian 131
 * tutore de laborator: Dobrovat Anca Madalina
 * compilator/IDE: CLion */
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <limits>

using namespace std;


//clasa citire si afisare
class CA {
public:
    virtual ~CA() {};

    friend istream &operator>>(istream &, CA &);

    friend ostream &operator<<(ostream &, CA &);

    virtual void citire(istream &) = 0;

    virtual void afisare(ostream &) = 0;
};

istream &operator>>(istream &in, CA &ca) {
    ca.citire(in);
    return in;
}

ostream &operator<<(ostream &out, CA &ca) {
    ca.afisare(out);
    return out;
}


//clase
class Malware : public CA {
protected:
    float rating;
    int zi_infectare;
    int luna_infectare;
    int an_infectare;
    string infectare;
    vector<string> registrii;

public:
    Malware() : rating(0), zi_infectare(0), luna_infectare(0), an_infectare(0), infectare("unknown"), registrii(0) {};

    Malware(float rating, int ziInfectare, int lunaInfectare, int anInfectare, const string &infectare,
            const vector<string> &registrii) : rating(rating), zi_infectare(ziInfectare), luna_infectare(lunaInfectare),
                                               an_infectare(anInfectare), infectare(infectare), registrii(registrii) {};

    virtual ~Malware() {};

    float getRating() const {
        return rating;
    }

    void setRating(float rating) {
        Malware::rating = rating;
    }

    int getZiInfectare() const {
        return zi_infectare;
    }

    void setZiInfectare(int ziInfectare) {
        zi_infectare = ziInfectare;
    }

    int getLunaInfectare() const {
        return luna_infectare;
    }

    void setLunaInfectare(int lunaInfectare) {
        luna_infectare = lunaInfectare;
    }

    int getAnInfectare() const {
        return an_infectare;
    }

    void setAnInfectare(int anInfectare) {
        an_infectare = anInfectare;
    }

    const string &getInfectare() const {
        return infectare;
    }

    void setInfectare(const string &infectare) {
        Malware::infectare = infectare;
    }

    const vector<string> &getRegistrii() const {
        return registrii;
    }

    void setRegistrii(const vector<string> &registrii) {
        Malware::registrii = registrii;
    }

    void citire(istream &) override;

    void afisare(ostream &) override;
};

void Malware::citire(istream &in) {
    rating = 0;

    cout << "\nzi_infectare: ";
    in >> zi_infectare;

    cout << "\nluna_infectare: ";
    in >> luna_infectare;

    cout << "\nan_infectare: ";
    in >> an_infectare;

    cout << "\ninfectare: ";
    in >> infectare;

    cout << "\nnr de registrii: ";
    int n;
    in >> n;

    for (int i = 0; i < n; i++) {
        string r;
        cin >> r;
        registrii.push_back(r);
        if (r == "HKLM-run")
            setRating(getRating() + 20);
        if (r == "HKCU-run")
            setRating(getRating() + 20);
    }
}

void Malware::afisare(ostream &out) {
    out << "\nrating: " << rating;

    out << "\nzi_infectare: " << zi_infectare;

    out << "\nluna_infectare: " << luna_infectare;

    out << "\nan_infectare: " << an_infectare;

    out << "\ninfectare: " << infectare;

    out << "\nregistrii: ";
    for (auto i:registrii)
        out << i << " ";
}


class Rootkit : virtual public Malware {
protected:
    vector<string> importuri;
    vector<string> string_sem;

public:
    const vector<string> &getImporturi() const {
        return importuri;
    }

    void setImporturi(const vector<string> &importuri) {
        Rootkit::importuri = importuri;
    }

    const vector<string> &getStringSem() const {
        return string_sem;
    }

    void setStringSem(const vector<string> &stringSem) {
        string_sem = stringSem;
    }

    void citire(istream &) override;

    void afisare(ostream &) override;
};

void Rootkit::citire(istream &in) {
    Malware::citire(in);

    int n;

    cout << "\nnr de stringuri: ";
    in >> n;
    for (int i = 0; i < n; i++) {
        string imp;
        in >> imp;
        string_sem.push_back(imp);
        if (imp == "System_Service_Descriptor_Table")
            setRating(getRating() + 100);
        if (imp == "SSDT")
            setRating(getRating() + 100);
        if (imp == "NtCreateFile")
            setRating(getRating() + 100);
    }

    cout << "\nnr de importuri: ";
    in >> n;
    for (int i = 0; i < n; i++) {
        string imp;
        in >> imp;
        string_sem.push_back(imp);
        if (imp == "ntoskrnl.exe")
            setRating(getRating() * 2);
    }
}

void Rootkit::afisare(ostream &out) {
    Malware::afisare(out);

    out << "\nstring semnificativ: ";
    for (auto i:string_sem) {
        out << i << " ";
    }

    out << "\nimporturi: ";
    for (auto i:importuri) {
        out << i << " ";
    }
}


class Keylogger : virtual public Malware {
protected:
    vector<string> functii;
    vector<string> taste;

public:
    void citire(istream &) override;

    void afisare(ostream &) override;
};

void Keylogger::citire(istream &in) {
    Malware::citire(in);

    int n;

    cout << "\nnr de taste: ";
    in >> n;
    for (int i = 0; i < n; i++) {
        string imp;
        in >> imp;
        taste.push_back(imp);
        if (imp == "[Up]")
            setRating(getRating() + 10);
        if (imp == "[Num_Lock]")
            setRating(getRating() + 10);
        if (imp == "[Down]")
            setRating(getRating() + 10);
        if (imp == "[Right]")
            setRating(getRating() + 10);
        if (imp == "[Left]")
            setRating(getRating() + 10);
    }

    cout << "\nnr de functii: ";
    in >> n;
    for (int i = 0; i < n; i++) {
        string imp;
        in >> imp;
        functii.push_back(imp);
        if (imp == "CreateFileW")
            setRating(getRating() + 30);
        if (imp == "OpenProcess")
            setRating(getRating() + 30);
        if (imp == "ReadFile")
            setRating(getRating() + 30);
        if (imp == "WriteFile")
            setRating(getRating() + 30);
        if (imp == "RegisterHotKey")
            setRating(getRating() + 30);
        if (imp == "SetWindowsHookEx")
            setRating(getRating() + 30);
    }
}

void Keylogger::afisare(ostream &out) {
    Malware::afisare(out);

    out << "\ntaste: ";
    for (auto i:taste) {
        out << i << " ";
    }

    out << "\nfunctii: ";
    for (auto i:functii) {
        out << i << " ";
    }
}


class Kernel : public Rootkit, public Keylogger {
protected:

public:
    void citire(istream &) override;

    void afisare(ostream &) override;
};


class Ransomware : public Malware {
protected:
    int criptare;
    float obfuscare;

public:
    void citire(istream &) override;

    void afisare(ostream &) override;
};

void Ransomware::citire(istream &in) {
    Malware::citire(in);

    cout << "\ncriptare: ";
    in >> criptare;

    cout << "\nobfuscare: ";
    in >> obfuscare;

    setRating(getRating() + criptare + obfuscare);
}

void Ransomware::afisare(ostream &out) {
    Malware::afisare(out);

    out << "\ncriptare: " << criptare;

    out << "\nobfuscare: " << obfuscare;
}


class Computer : public CA {
protected:
    static int idc;
    int id;
    float rating_total;
    vector<Malware *> v;

public:
    int Computer::getIdc() {
        return idc;
    }

    void Computer::setIdc(int idc) {
        Computer::idc = idc;
    }

    int Computer::getId() const {
        return id;
    }

    void Computer::setId(int id) {
        Computer::id = id;
    }

    int Computer::getRatingTotal() const {
        return rating_total;
    }

    void Computer::setRatingTotal(int ratingTotal) {
        rating_total = ratingTotal;
    }

    const vector<Malware *> &Computer::getV() const {
        return v;
    }

    void Computer::setV(const vector<Malware *> &v) {
        Computer::v = v;
    }

    void citire(istream &) override;

    void afisare(ostream &) override;
};

int Computer::idc;

void Computer::citire(istream &in) {
    setIdc(getIdc() + 1);
    setId(getIdc());

    cout << "\nnr de malware: ";
    int n;
    in >> n;

    setRatingTotal(0);

    for (int i = 0; i < n; i++) {
        Malware *aux;
        cout << "\n1 - Rootkit";
        cout << "\n2 - Keylogger";
        cout << "\n3 - neterminat";
        cout << "\n4 - Ransomware";

        int tip_mal;
        cout << "\nTip Malware: ";
        cin >> tip_mal;

        if (tip_mal == 1) {
            aux = new Rootkit();
            dynamic_cast<Rootkit *>(aux)->citire(cin);
        } else if (tip_mal == 2) {
            aux = new Keylogger();
            dynamic_cast<Keylogger *>(aux)->citire(cin);
        } else if (tip_mal == 3) {

        } else if (tip_mal == 4) {
            aux = new Ransomware();
            dynamic_cast<Ransomware *>(aux)->citire(cin);
        }

        v.push_back(aux);

        setRatingTotal(getRatingTotal() + aux->getRating());
    }
}

void Computer::afisare(ostream &out) {
    out << "\nid: " << id;
    out << "\nrating total: " << rating_total;

    for (auto i : v) {
        if (typeid(*i) == typeid(Rootkit)) {
            out << "\nRootkit:\n";
            out << *dynamic_cast<Rootkit *>(i) << "\n\n";
        } else if (typeid(*i) == typeid(Keylogger)) {
            out << "\nKeylogger:\n";
            out << *dynamic_cast<Keylogger *>(i) << "\n\n";
        } else if (typeid(*i) == typeid(Ransomware)) {
            out << "\nRansomware:\n";
            out << *dynamic_cast<Ransomware *>(i) << "\n\n";
        } else if (typeid(*i) == typeid(Ransomware)) {
            out << "\nRansomware:\n";
            out << *dynamic_cast<Ransomware *>(i) << "\n\n";
        }
    }
}


class Gestiune : public CA {
protected:
    vector<Computer> c;

public:
    void citire(istream &) override;

    void afisare(ostream &) override;

    void afisare_ord();

    void afisare_ord_k();

    void afisare_procent();
};

void Gestiune::citire(istream &in) {
    cout << "\nnr computere: ";
    int n;
    in >> n;

    for (int i = 0; i < n; i++) {
        Computer com;
        cin >> com;
        c.push_back(com);
    }
}

void Gestiune::afisare(ostream &out) {
    for (int i = 0; i < c.size(); i++) {
        out << "\n\nComputerul " << i + 1 << ":\n";
        out << c[i];
    }
}

void Gestiune::afisare_ord() {
    vector<Computer> cnou(c);

    for (int i = 0; i < cnou.size(); i++)
        for (int j = i + 1; j < cnou.size(); j++)
            if (cnou[i].getRatingTotal() < cnou[j].getRatingTotal())
                swap(cnou[i], cnou[j]);

    for (int i = 0; i < cnou.size(); i++) {
        cout << "\n\nComputerul " << i + 1 << ":\n";
        cout << cnou[i];
    }
}

void Gestiune::afisare_ord_k() {

    int k;
    cout << "\nk: ";
    cin >> k;
    vector<Computer> cnou(c);

    for (int i = 0; i < cnou.size(); i++)
        for (int j = i + 1; j < cnou.size(); j++)
            if (cnou[i].getRatingTotal() < cnou[j].getRatingTotal())
                swap(cnou[i], cnou[j]);

    for (int i = 0; i < cnou.size(); i++) {
        if (k > 0) {
            cout << "\n\nComputerul " << i + 1 << ":\n";
            cout << cnou[i];
        }
        k--;
    }
}

void Gestiune::afisare_procent() {
    int infectate = 0;

    for (int i = 0; i < c.size(); i++)
        if (c[i].getRatingTotal() > 0)
            infectate++;

    float rez = infectate / c.size();
    cout << "\ninfectate: "<< infectate;
    cout << "\ntotale: "<< c.size();
    cout << "\nprocent infectare: " << infectate / c.size() << "%";
}


//try catch pentru meniu
int e_int(string aux) {
    int x;
    try {
        x = stoi(aux);
        return x;
    }
    catch (exception &ia) {
        return -1;
    }
}


//meniu singleton cu lamba expresii
class Meniu {
private:
    Meniu();

    Meniu(const Meniu &) = delete;

    Meniu operator=(const Meniu &) = delete;

    vector<pair<string, function<void()>>> operatii;

    static Meniu *instance;

    Gestiune g;

public:
    void run();

    static Meniu *get_instance();

    static void delete_instance();
};

Meniu *Meniu::instance = nullptr;

Meniu::Meniu() {
    operatii.push_back(make_pair(" citire/adaugare computere", [&]() {
        cin >> g;
    }));

    operatii.push_back(make_pair(" afisare normala", [&]() {
        g.afisare(cout);
    }));

    operatii.push_back(make_pair(" afisare in ordine", [&]() {
        g.afisare_ord();
    }));

    operatii.push_back(make_pair(" afisare in ordine primele k computere", [&]() {
        g.afisare_ord_k();
    }));

    operatii.push_back(make_pair(" afisare procent infectare firma", [&]() {
        g.afisare_procent();
    }));
}

void Meniu::run() {
    cout << 0 << " incheiere\n";

    for (int i = 1; i <= operatii.size(); i++)
        cout << i << operatii[i - 1].first << "\n";

    cout << "optiune: ";
    int optiune;
    string op;
    cin >> op;

    while (e_int(op) < 0 || e_int(op) > operatii.size()) {
        cout << "input invalid, reincercati";
        cout << "\noptiune: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> op;
    }
    optiune = e_int(op);

    while (optiune) {
        operatii[optiune - 1].second();

        cout << "\n\n";
        cout << 0 << " incheiere\n";

        for (int i = 1; i <= operatii.size(); i++)
            cout << i << operatii[i - 1].first << "\n";

        cout << "optiune: ";
        cin >> op;

        while (e_int(op) < 0 || e_int(op) > operatii.size()) {
            cout << "input invalid, reincercati";
            cout << "\noptiune: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> op;
        }
        optiune = e_int(op);
    }
}

Meniu *Meniu::get_instance() {
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
