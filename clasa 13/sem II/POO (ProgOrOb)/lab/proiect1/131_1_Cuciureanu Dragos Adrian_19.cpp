#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

class Actor
{
private:
    string nume_actor;
    int varsta;

public:
    Actor() {}
    ~Actor() {}

    string get_nume_actor()
    {
        return nume_actor;
    }
    void set_nume_actor(string nume)
    {
        nume_actor = nume;
    }
    int get_varsta()
    {
        return varsta;
    }
    void set_varsta(int nr)
    {
        varsta = nr;
    }

    Actor& operator = (Actor&);

    friend istream& operator>>(istream&, Actor&);
    friend ostream& operator<<(ostream&, Actor&);
};

istream& operator>>(istream& in, Actor& a)
{
    cout << "Nume: ";
    in.ignore();
    getline (in,  a.nume_actor);
    cout << "Varsta: ";
    in >> a.varsta;
    return in;
}

ostream& operator << (ostream& out, Actor& a)
{
    out << a.nume_actor << " " << a.varsta << " ani\n";
    return out;
}



Actor& Actor::operator = (Actor& ob)
{
    if (this != &ob)
    {
        nume_actor = ob.nume_actor;
        varsta = ob.varsta;
    }
    return *this;
}



class Piesa
{
private:
    string denumire_piesa;
    int nr_actori;
    Actor* actori;
    float rating;

public:
    Piesa()
    {
        actori = NULL;
    }
    ~Piesa()
    {
        delete[] actori;
    }
    Piesa(Piesa&);


    #pragma region Set&Get_Piesa:
    int get_nr_actori()
    {
        return nr_actori;
    }
    void set_nr_actori(int nr)
    {
        nr_actori = nr;
    }
    string get_denumire_piesa()
    {
        return denumire_piesa;
    }
    void set_denumire_piesa(string nume)
    {
        denumire_piesa = nume;
    }
    int get_rating()
    {
        return rating;
    }
    void set_rating(float nr)
    {
        rating = nr;
    }
    Actor& get_actor(int nr)
    {
        return actori[nr];
    }

    #pragma endregion

    #pragma region Methods_antet_Piesa:

    friend Piesa& copiere1(Piesa&);
    Piesa copiere2(Piesa);

    friend istream& operator>>(istream&, Piesa&);
    friend ostream& operator<<(ostream&, Piesa&);

    void citire();
    void afisare();

    Piesa& operator = (Piesa&);
    friend bool operator > (Piesa&, Piesa&);
    friend bool operator < (Piesa&, Piesa&);
    friend bool operator >= (Piesa&, Piesa&);
    friend bool operator <= (Piesa&, Piesa&);

    void add(Actor);
    void delet(int);
    //Piesa& operator += (Actor);

    #pragma endregion
};

#pragma region Methods_Piesa:

Piesa::Piesa(Piesa& ob)
{
    denumire_piesa = ob.denumire_piesa;
    nr_actori = ob.nr_actori;
    actori = new Actor[nr_actori];
    for (int i = 0; i < nr_actori; i++)
        actori[i] = ob.actori[i];
    rating = ob.rating;
}

Piesa& copiere1(Piesa& ob)
{
    return ob;
}

Piesa Piesa::copiere2(Piesa ob)
{
    Piesa x(ob);
    return x;
}



istream& operator>>(istream& in, Piesa& t)
{
    cout << "Introduceti denumirea piesei: ";
    in.ignore();
    getline (in, t.denumire_piesa);
    cout << "\nIntroduceti numarul de actori: ";
    in >> t.nr_actori;
    t.actori = new Actor[t.nr_actori];
    cout << "\nIntroduceti numele actorilor si varsta acestora:\n";
    for (int i = 0; i < t.nr_actori; i++)
    {
        cout << "\nActorul " << i + 1 << ":\n";
        in >> t.actori[i];
    }
    cout << "\nIntroduceti ratingul piesei: ";
    in >> t.rating;
    return in;
}

ostream& operator << (ostream& out, Piesa& t)
{
    cout << "Denumirea piesei este: ";
    out << t.denumire_piesa << "\n\n";
    cout << "Piesa are ";
    out << t.nr_actori << " actori:\n";
    for (int i = 0; i < t.nr_actori; i++)
    {
        cout << "Actorul " << i + 1 << ": ";
        out << t.actori[i];
    }
    cout << "\nRatingul piesei este: ";
    out << t.rating << "\n";
    return out;
}



void Piesa::citire()
{
    cout << "Introduceti denumirea piesei:\n";
    cin >> denumire_piesa;
    cout << "Introduceti numarul de actori:\n";
    cin >> nr_actori;
    cout << "Introduceti numele actorilor si varsta acestora:\n";
    for (int i = 0; i < nr_actori; i++)
    {
        cin >> actori[i];
    }
    cout << "Introduceti ratingul piesei:\n";
    cin >> rating;
}

void Piesa::afisare()
{
    cout << "Denumirea piesei este: " << denumire_piesa << "\n";
    cout << "Numarul de actori este de: " << nr_actori << "\nIar numele si varsta acestora sunt:\n";
    for (int i = 0; i < nr_actori; i++)
        cout << actori[i];
    cout << "Ratingul piesei este: " << rating << "\n";
}



Piesa& Piesa::operator = (Piesa& ob)
{
    if (this != &ob)
    {
        denumire_piesa = ob.denumire_piesa;
        nr_actori = ob.nr_actori;
        actori = new Actor[nr_actori];
        for (int i = 0; i < nr_actori; i++)
            actori[i] = ob.actori[i];
        rating = ob.rating;
    }
    return *this;
}

bool operator > (Piesa& ob1, Piesa& ob2)
{
    return ob1.rating > ob2.rating;
}

bool operator < (Piesa& ob1, Piesa& ob2)
{
    return ob1.rating < ob2.rating;
}

bool operator >= (Piesa& ob1, Piesa& ob2)
{
    return ob1.rating >= ob2.rating;
}

bool operator <= (Piesa& ob1, Piesa& ob2)
{
    return ob1.rating <= ob2.rating;
}



void Piesa::add(Actor x)
{
    Actor* aux;
    aux = new Actor[nr_actori + 1];
    for (int i = 0; i < nr_actori; i++)
        aux[i] = actori[i];
    aux[nr_actori] = x;
    nr_actori++;
    actori = new Actor[nr_actori];
    for (int i = 0; i < nr_actori; i++)
        actori[i] = aux[i];
    delete[] aux;
}

void Piesa::delet(int index)
{
    Actor* aux;
    int j = 0;
    aux = new Actor[nr_actori - 1];
    for (int i = 0; i < nr_actori; i++)
        if(i != index)
        {
            aux[j] = actori[i];
            j++;
        }
    nr_actori--;
    actori = new Actor[nr_actori];
    for (int i = 0; i < nr_actori; i++)
        actori[i] = aux[i];
    delete[] aux;
}


#pragma endregion



class Teatru
{
private:
    int nr_piese;
    Piesa* piese;

public:
    Teatru()
    {
        piese = NULL;
    }
    ~Teatru()
    {
        delete[] piese;
    }
    Teatru(Teatru&);

    Piesa& get_piesa(int nr)
    {
        return piese[nr];
    }
    int get_nr_piese ()
    {
        return nr_piese;
    }


    friend istream& operator>>(istream&, Teatru&);
    friend ostream& operator<<(ostream&, Teatru&);

    void add(Piesa);
    void delet(int);
    //Teatru& operator += (Piesa);
};



istream& operator>>(istream& in, Teatru& t)
{
    cout << "Introduceti date despre teatru:\n";
    cout << "Introduceti numarul de piese dorit: ";
    in >> t.nr_piese;
    t.piese = new Piesa[t.nr_piese];
    for (int i = 0; i < t.nr_piese; i++)
    {
        cout << "\n\nIntroduceti datele pentru piesa cu numarul " << i + 1 << ":\n\n";
        in >> t.piese[i];
    }
    return in;
}

ostream& operator << (ostream& out, Teatru& t)
{
    cout << "\n";
    for (int i = 0; i < t.nr_piese; i++)
    {
        cout << "Datele despre piesa numarul " << i + 1 << ":\n\n";
        out << t.piese[i] << "\n";
        cout << "\n";
    }
    return out;
}



void Teatru::add(Piesa x)
{
    Piesa* aux;
    aux = new Piesa[nr_piese + 1];
    for (int i = 0; i < nr_piese; i++)
        aux[i] = piese[i];
    aux[nr_piese] = x;
    nr_piese++;
    piese = new Piesa[nr_piese];
    for (int i = 0; i < nr_piese; i++)
        piese[i] = aux[i];
    delete[] aux;
}


void Teatru::delet(int index)
{
    Piesa* aux;
    int j = 0;
    aux = new Piesa[nr_piese - 1];
    for (int i = 0; i < nr_piese; i++)
        if (i != index)
        {
            aux[j] = piese[i];
            j++;
        }
    nr_piese--;
    piese = new Piesa[nr_piese];
    for (int i = 0; i < nr_piese; i++)
        piese[i] = aux[i];
    delete[] aux;
}


void meniu()
{
    Teatru masca;
    cin >> masca;
    int optiune;
    cout << "\nOptiuni:\n";
    cout << "0 - terminare\n";
    cout << "1 - afisare\n";
    cout << "2 - modificare\n";
    cout << "3 - adaugare\n";
    cout << "4 - eliminare\n";
    cout << "Optiunea dumneavoastra: ";
    cin >> optiune;
    while (optiune)
    {
        switch (optiune)
        {
        case 1:
        {
            int optiune_case1;
            cout << "\nOptiuni:\n";
            cout << "1 - afisarea teatrului\n";
            cout << "2 - afisarea unei piese de teatru\n";
            cout << "3 - intoarcerea la meniul principal\n";
            cout << "Optiunea dumneavoastra: ";
            cin >> optiune_case1;
            cout << "\n";

            switch (optiune_case1)
            {
            case 1:
            {
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << masca;
                }
                break;
            }
            case 2:
            {
                int nr_piesa;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "introduceti indexul piesei: ";
                    cin >> nr_piesa;
                    cout << "\n";
                    if ((nr_piesa <= 0) || (nr_piesa > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                        cout << "\n" << masca.get_piesa(nr_piesa-1) << "\n";
                }
                break;
            }
            case 3:
            {
                break;
            }
            }

            break;
        }
        case 2:
        {
            int optiune_case2;
            cout << "\nOptiuni:\n";
            cout << "1 - modificarea denumirii unei piese\n";
            cout << "2 - modificarea ratingului unei piese\n";
            cout << "3 - modificarea numelui unui actor\n";
            cout << "4 - modificarea varstei unui actor\n";
            cout << "5 - intoarcerea la meniul principal\n";
            cout << "Optiunea dumneavoastra: ";
            cin >> optiune_case2;
            cout << "\n";

            switch (optiune_case2)
            {
            case 1:
            {
                int idx_piesa_case1;
                string noua_denumire;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul unei piese de teatru: ";
                    cin >> idx_piesa_case1;
                    cout << "\n";
                    if ((idx_piesa_case1 <= 0) || (idx_piesa_case1 > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        cout << "Introduceti noua denumire pentru teatrul cu indexul ales: ";
                        cin.ignore();
                        getline (cin, noua_denumire);
                        masca.get_piesa(idx_piesa_case1 - 1).set_denumire_piesa(noua_denumire);
                    }
                }
                break;
            }
            case 2:
            {
                int idx_piesa_case2;
                float nou_rating;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul unei piese de teatru: ";
                    cin >> idx_piesa_case2;
                    cout << "\n";
                    if ((idx_piesa_case2 <= 0) || (idx_piesa_case2 > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        cout << "Introduceti noul rating pentru piesa de teatru cu indexul ales: ";
                        cin >> nou_rating;
                        masca.get_piesa(idx_piesa_case2 - 1).set_rating(nou_rating);
                    }
                }
                break;
            }
            case 3:
            {
                int idx_piesa_case3;
                int idx_actor_case3;
                string noua_denumire_actor;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul unei piese de teatru: ";
                    cin >> idx_piesa_case3;
                    cout << "\n";
                    if ((idx_piesa_case3 <= 0) || (idx_piesa_case3 > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        if (masca.get_piesa(idx_piesa_case3 - 1).get_nr_actori() == 0)
                        {
                            cout << "Nu exista actori in aceasta piesa.\n";
                        }
                        else
                        {
                            cout << "Introduceti indexul actorului al carui nume doriti sa-l schimbati: ";
                            cin >> idx_actor_case3;
                            cout << "\n";
                            if ((idx_actor_case3 <= 0) || (idx_actor_case3 > masca.get_piesa(idx_piesa_case3 - 1).get_nr_actori() ))
                                cout << "Nu este bun indexul.\n";
                            else
                            {
                                cout << "Introduceti noul nume pentru actorul cu indexul ales: ";
                                cin.ignore();
                                getline (cin, noua_denumire_actor);
                                masca.get_piesa(idx_piesa_case3 - 1).get_actor(idx_actor_case3 - 1).set_nume_actor(noua_denumire_actor);
                            }
                        }
                    }
                }
                break;
            }
            case 4:
            {
                int idx_piesa_case4;
                int idx_actor_case4;
                int noua_varsta_actor;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul unei piese de teatru: ";
                    cin >> idx_piesa_case4;
                    cout << "\n";
                    if ((idx_piesa_case4 <= 0) || (idx_piesa_case4 > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        if (masca.get_piesa(idx_piesa_case4 - 1).get_nr_actori() == 0)
                        {
                            cout << "Nu exista actori in aceasta piesa.\n";
                        }
                        else
                        {
                            cout << "Introduceti indexul actorului a carui varste doriti sa o schimbati: ";
                            cin >> idx_actor_case4;
                            cout << "\n";
                            if ((idx_actor_case4 <= 0) || (idx_actor_case4 > masca.get_piesa(idx_piesa_case4 - 1).get_nr_actori() ))
                                cout << "Nu este bun indexul.\n";
                            else
                            {
                                cout << "Introduceti noua varsta pentru actorul cu indexul ales: ";
                                cin >> noua_varsta_actor;
                                masca.get_piesa(idx_piesa_case4 - 1).get_actor(idx_actor_case4 - 1).set_varsta(noua_varsta_actor);
                            }
                        }
                    }
                }
                break;
            }
            case 5:
            {
                break;
            }
            }

            break;
        }
        case 3:
        {
            int optiune_case3;
            cout << "\nOptiuni:\n";
            cout << "1 - adaugarea unei piese de teatru\n";
            cout << "2 - adaugarea unui actor la o piesa de teatru\n";
            cout << "3 - intoarcerea la meniul principal\n";
            cout << "Optiunea dumneavoastra: ";
            cin >> optiune_case3;
            cout << "\n";

            switch (optiune_case3)
            {
            case 1:
            {
                Piesa noua_piesa;
                cin >> noua_piesa;
                masca.add(noua_piesa);
                break;
            }
            case 2:
            {
                int idx_piesa;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul piesei unde doriti sa adaugati un actor: ";
                    cin >> idx_piesa;

                    if ((idx_piesa <= 0) || (idx_piesa > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        Actor actor_nou;
                        cout << "Introduceti actorul pe care doriti sa-l adaugati la piesa aleasa:\n";
                        cin >> actor_nou;
                        masca.get_piesa(idx_piesa - 1).add(actor_nou);
                    }
                }
                break;
            }
            case 3:
            {
                break;
            }
            }
            break;
        }
        case 4:
        {
            int optiune_case4;
            cout << "\nOptiuni:\n";
            cout << "1 - eliminarea unei piese de teatru\n";
            cout << "2 - eliminarea unui actor dintr-o piesa de teatru\n";
            cout << "3 - intoarcerea la meniul principal\n";
            cout << "Optiunea dumneavoastra: ";
            cin >> optiune_case4;
            cout << "\n";

            switch(optiune_case4)
            {
            case 1:
            {
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    int idx_piesa;
                    cout << "Introduceti indexul piesei pe care doriti sa o eliminati: ";
                    cin >> idx_piesa;
                    if ((idx_piesa <= 0) || (idx_piesa > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                        masca.delet(idx_piesa - 1);
                }
                break;
            }
            case 2:
            {
                int idx_piesa, idx_actor;
                if (masca.get_nr_piese() == 0)
                {
                    cout << "Nu mai exista piese.\n";
                }
                else
                {
                    cout << "Introduceti indexul piesei unde se afla actorul pe care doriti sa-l eliminati: ";
                    cin >> idx_piesa;
                    if ((idx_piesa <= 0) || (idx_piesa > masca.get_nr_piese() ))
                        cout << "Nu este bun indexul.\n";
                    else
                    {
                        if (masca.get_piesa(idx_piesa - 1).get_nr_actori() == 0)
                        {
                            cout << "Nu exista actori in aceasta piesa.\n";
                        }
                        else
                        {
                            cout << "Introduceti indexul actorului pe care doriti sa-l eliminati: ";
                            cin >> idx_actor;
                            if ((idx_actor <= 0) || (idx_actor > masca.get_piesa(idx_piesa - 1).get_nr_actori() ))
                                cout << "Nu este bun indexul.\n";
                            else
                            {
                                masca.get_piesa(idx_piesa - 1).delet(idx_actor - 1);
                            }
                        }
                    }
                }
                break;
            }
            case 3:
            {
                break;
            }
            }
        }
        }
        cout << "\nOptiuni:\n";
        cout << "0 - terminare\n";
        cout << "1 - afisare\n";
        cout << "2 - modificare\n";
        cout << "3 - adaugare\n";
        cout << "4 - eliminare\n";
        cout << "Optiunea dumneavoastra: ";
        cin >> optiune;
    }
}



int main()
{
    meniu();
    return 0;
}
