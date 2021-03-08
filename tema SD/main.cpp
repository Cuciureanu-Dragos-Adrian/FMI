#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

ifstream fin("citire.in");
ofstream fout("afisare.out");

int v[100000001];
int vnou[100000001];

void Bubble(int v[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (v[j + 1] < v[j])
                swap(v[j + 1], v[j]);
}

void Count(int v[], int n, int nmax)
{
    for (int i = 0; i < n; i++)
    {
        vnou[v[i]]++;
    }
    int id = 0;
    for (int i = 0; i <= nmax; i++)
    {
        while (vnou[i])
        {
            v[id] = i;
            id++;
            vnou[i] --;
        }
    }
}

int DetOrdin(int v[], int n)
{
    int ordin = 0;
    int maxim = v[0];
    for (int i = 1; i < n; i++)
        if (maxim < v[i])
            maxim = v[i];
    do
    {
        maxim /= 10;
        ordin++;
    } while (maxim > 0);
    return ordin;
}

void RadixLSD(int v[], int ordin, int nr)
{
    int put = 1;
    for (int k = 0; k < ordin; k++)
    {
        int index = 0;
        for (int i = 0; i <= 9; i++)
        {
            for (int j = 0; j < nr; j++)
            {
                if ((v[j] / put) % 10 == i)
                    vnou[index++] = v[j];
            }
        }
        for (int i = 0; i < nr; i++)
            v[i] = vnou[i];
        put *= 10;
    }
}

void RadixMSD_opbit(int v[], int ordin, int st, int dr)
{
    if ((dr > st) & (ordin >= 0))
    {
        int capat = dr;
        int doi = 1 << ordin;
        for (int i = st; i <= capat; i++)
        {
            if ((v[i] & doi) > 0)
            {
                swap(v[i], v[capat]);
                capat--;
                i--;
            }
        }
        RadixMSD_opbit(v, ordin - 1, st, capat);
        RadixMSD_opbit(v, ordin - 1, capat + 1, dr);
    }
}

int DetOrdinBin(int v[], int n)
{
    int ordin = 0;
    int maxim = v[0];
    for (int i = 1; i < n; i++)
        if (maxim < v[i])
            maxim = v[i];
    do
    {
        maxim /= 2;
        ordin++;
    } while (maxim > 0);
    ordin--;
    return ordin;
}

void Interclasare(int v[], int s, int d)
{
    int m = (s + d) / 2;
    int i1 = s;
    int i2 = m + 1;
    int k = 0;
    while (i1 <= m and i2 <= d)
    {
        if (v[i1] <= v[i2])
        {
            vnou[k] = v[i1];
            k++;
            i1++;
        }
        else
        {
            vnou[k] = v[i2];
            k++;
            i2++;
        }
    }
    while (i1 <= m)
    {
        vnou[k] = v[i1];
        i1++;
        k++;
    }
    while (i2 <= d)
    {
        vnou[k] = v[i2];
        i2++;
        k++;
    }
    for (int i = s; i <= d; i++)
        v[i] = vnou[i - s];
}

void Merge(int v[], int s, int d)
{
    if (d - s < 2)
    {
        if (v[s] > v[d])
            swap(v[s], v[d]);
    }
    else
    {
        int m = (s + d) / 2;
        Merge(v, s, m);
        Merge(v, m + 1, d);
        Interclasare(v, s, d);

    }
}

void Quick_pivst(int v[], int st, int dr)
{
    if (st < dr)
    {
        int piv = v[st];
        int id = dr;
        for (int i = st + 1; i <= id; i++)
            if (v[i] > piv)
            {
                swap(v[i], v[id]);
                id--;
                i--;
            }
        swap(v[st], v[id]);
        Quick_pivst(v, st, id - 1);
        Quick_pivst(v, id + 1, dr);
    }
}

int Med3(int v[], int st, int dr)
{
    int mij = (st + dr) / 2;
    if ((v[st] > v[mij]) xor (v[st] > v[dr]))
        return st;
    else if ((v[dr] > v[st]) xor (v[dr] > v[mij]))
        return dr;
    else
        return mij;
}

void Quick_pivMed3(int v[], int st, int dr)
{
    if (st < dr)
    {
        int piv = Med3(v, st, dr);
        int id = dr;
        swap(v[piv], v[st]);
        for (int i = st + 1; i <= id; i++)
            if (v[i] > v[st])
            {
                swap(v[i], v[id]);
                id--;
                i--;
            }
        swap(v[st], v[id]);
        Quick_pivMed3(v, st, id - 1);
        Quick_pivMed3(v, id + 1, dr);
    }
}



unsigned long long llrand() // luata de pe internet
{
    unsigned long long r = 0;
    for (int i = 0; i < 5; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }
    return r & 0xFFFFFFFFFFFFFFFFULL;
}

void generator(int v[], int nr, int nrmax)
{
    for (int i = 0; i < nr; i++)
        v[i] = llrand() % (nrmax + 1);
    for (int i = 0; i < nr; i++)
        vnou[i] = 0;
}

void generator_cresc(int v[], int nr, int nrmax)
{
    generator(v, nr, nrmax);
    int ord = DetOrdinBin(v, nr);
    RadixMSD_opbit(v, ord, 0, nr - 1);
    for (int i = 0; i < nr; i++)
        vnou[i] = 0;
}

void generator_desc(int v[], int nr, int nrmax)
{
    generator_cresc(v, nr, nrmax);
    for (int i = 0; i < nr / 2; i++)
        swap(v[i], v[nr - i]);
    for (int i = 0; i < nr; i++)
        vnou[i] = 0;
}

void generator_const(int v[], int nr, int nrmax)
{
    int c = llrand() % (nrmax + 1);
    for (int i = 0; i < nr; i++)
        v[i] = c;
    for (int i = 0; i < nr; i++)
        vnou[i] = 0;
}

bool verificare(int v[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (v[i] > v[i + 1])
            return false;
    return true;
}

void citire(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        fin >> v[i];
    }
}

void afisare(int v[], int n)
{
    for (int i = 0; i < n; i++)
        fout << v[i] << " ";
    fout << "\n";
}



void Bubble_sort(int v[], int nr, int nrmax, int gen)
{
    if (nr <= 10000)
    {
        if (gen == 1)
            generator(v, nr, nrmax);
        else if (gen == 2)
            generator_cresc(v, nr, nrmax);
        else if (gen == 3)
            generator_desc(v, nr, nrmax);
        else if (gen == 4)
            generator_const(v, nr, nrmax);
        float t = clock();
        Bubble(v, nr);
        t = clock() - t;
        cout << "Bubble_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
        if (verificare(v, nr) == true)
            cout << "SORTAT!\n";
        else
            cout << "NESORTAT.\n";
    }
    else
    {
        cout << "Bubble nu este optim.\n";
    }
}

void Count_sort(int v[], int nr, int nrmax, int gen)
{
    if (nrmax <= 100000000)
    {
        if (gen == 1)
            generator(v, nr, nrmax);
        else if (gen == 2)
            generator_cresc(v, nr, nrmax);
        else if (gen == 3)
            generator_desc(v, nr, nrmax);
        else if (gen == 4)
            generator_const(v, nr, nrmax);
        float t = clock();
        Count(v, nr, nrmax);
        t = clock() - t;
        cout << "Count_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
        if (verificare(v, nr) == true)
            cout << "SORTAT!\n";
        else
            cout << "NESORTAT!\n";
    }
    else
    {
        cout << "Count nu este optim.\n";
    }
}

void RadixLSD_sort(int v[], int nr, int nrmax, int gen)
{
    if (gen == 1)
        generator(v, nr, nrmax);
    else if (gen == 2)
        generator_cresc(v, nr, nrmax);
    else if (gen == 3)
        generator_desc(v, nr, nrmax);
    else if (gen == 4)
        generator_const(v, nr, nrmax);
    float t = clock();
    Merge(v, 0, nr);
    t = clock() - t;
    cout << "RadixLSD_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
    if (verificare(v, nr) == true)
        cout << "SORTAT!\n";
    else
        cout << "NESORTAT!\n";
}

void RadixMSD_opbit_sort(int v[], int nr, int nrmax, int gen)
{
    if (gen == 1)
        generator(v, nr, nrmax);
    else if (gen == 2)
        generator_cresc(v, nr, nrmax);
    else if (gen == 3)
        generator_desc(v, nr, nrmax);
    else if (gen == 4)
        generator_const(v, nr, nrmax);
    float t = clock();
    int ord = DetOrdinBin(v, nr);
    RadixMSD_opbit(v, ord, 0, nr - 1);
    t = clock() - t;
    cout << "RadixMSD_opbit_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
    if (verificare(v, nr) == true)
        cout << "SORTAT!\n";
    else
        cout << "NESORTAT!\n";
}

void Merge_sort(int v[], int nr, int nrmax, int gen)
{
    if (gen == 1)
        generator(v, nr, nrmax);
    else if (gen == 2)
        generator_cresc(v, nr, nrmax);
    else if (gen == 3)
        generator_desc(v, nr, nrmax);
    else if (gen == 4)
        generator_const(v, nr, nrmax);
    float t = clock();
    Merge(v, 0, nr - 1);
    t = clock() - t;
    cout << "Merge_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
    if (verificare(v, nr) == true)
        cout << "SORTAT!\n";
    else
        cout << "NESORTAT!\n";
}

void Quick_pivst_sort(int v[], int nr, int nrmax, int gen)
{
    if ((nr <= 10000) || !((gen == 3) || (gen == 4) || (gen == 2)))
    {
        if (gen == 1)
            generator(v, nr, nrmax);
        else if (gen == 2)
            generator_cresc(v, nr, nrmax);
        else if (gen == 3)
            generator_desc(v, nr, nrmax);
        else if (gen == 4)
            generator_const(v, nr, nrmax);
        float t = clock();
        Quick_pivst(v, 0, nr - 1);
        t = clock() - t;
        cout << "Quick_pivst a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
        if (verificare(v, nr) == true)
            cout << "SORTAT!\n";
        else
            cout << "NESORTAT!\n";
    }
    else
    {
        cout << "Quick_pivst nu este optim.\n";
    }
}

void Quick_pivMed3_sort(int v[], int nr, int nrmax, int gen)
{
    if ((nr <= 10000) || !((gen == 3) || (gen == 4) || (gen == 2)))
    {
        if (gen == 1)
            generator(v, nr, nrmax);
        else if (gen == 2)
            generator_cresc(v, nr, nrmax);
        else if (gen == 3)
            generator_desc(v, nr, nrmax);
        else if (gen == 4)
            generator_const(v, nr, nrmax);
        float t = clock();
        Quick_pivMed3(v, 0, nr - 1);
        t = clock() - t;
        cout << "Quick_pivMed3 a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
        if (verificare(v, nr) == true)
            cout << "SORTAT!\n\n\n";
        else
            cout << "NESORTAT\n";
    }
    else
    {
        cout << "Quick_pivMed3 nu este optim.\n\n\n";
    }
}



int main()
{
    srand(time(NULL));
    int nrteste, nr, nrmax;
    cout << "Introduceti numarul de teste: \n";
    cin >> nrteste;
    for (int i = 0; i < nrteste; i++)
    {
        cout << "Introduceti numarul de termeni si marimea maxima a aceastora pentru testul " << i + 1 << ":\n";
        cin >> nr >> nrmax;
        cout << "\nTestul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
        cout << " pentru un array random:\n";
        Bubble_sort(v, nr, nrmax, 1);
        Count_sort(v, nr, nrmax, 1);
        RadixLSD_sort(v, nr, nrmax, 1);
        RadixMSD_opbit_sort(v, nr, nrmax, 1);
        Merge_sort(v, nr, nrmax, 1);
        Quick_pivst_sort(v, nr, nrmax, 1);
        Quick_pivMed3_sort(v, nr, nrmax, 1);

        cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
        cout << " pentru un array crescator:\n";
        Bubble_sort(v, nr, nrmax, 2);
        Count_sort(v, nr, nrmax, 2);
        RadixLSD_sort(v, nr, nrmax, 2);
        RadixMSD_opbit_sort(v, nr, nrmax, 2);
        Merge_sort(v, nr, nrmax, 2);
        Quick_pivst_sort(v, nr, nrmax, 2);
        Quick_pivMed3_sort(v, nr, nrmax, 2);

        cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
        cout << " pentru un array descrescator:\n";
        Bubble_sort(v, nr, nrmax, 3);
        Count_sort(v, nr, nrmax, 3);
        RadixLSD_sort(v, nr, nrmax, 3);
        RadixMSD_opbit_sort(v, nr, nrmax, 3);
        Merge_sort(v, nr, nrmax, 3);
        Quick_pivst_sort(v, nr, nrmax, 3);
        Quick_pivMed3_sort(v, nr, nrmax, 3);

        cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
        cout << " pentru un array constant:\n";
        Bubble_sort(v, nr, nrmax, 4);
        Count_sort(v, nr, nrmax, 4);
        RadixLSD_sort(v, nr, nrmax, 4);
        RadixMSD_opbit_sort(v, nr, nrmax, 4);
        Merge_sort(v, nr, nrmax, 4);
        Quick_pivst_sort(v, nr, nrmax, 4);
        Quick_pivMed3_sort(v, nr, nrmax, 4);

        cout << "\n";
    }
    return 0;
}
