#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

#pragma region Declarari:

ifstream fin("citire.in");
ofstream fout("afisare.out");

int nr, nrmax;
int v[10000001];
double vnou[10000001];
double d[10000001];
string s[1000001];
string snou[1000001];

#pragma endregion

#pragma region Sortari:

#pragma region Sortari_int:

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
			if (v[i] > piv || ((v[i] == piv) && (rand() % 2 == 1)))
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
			if (v[i] > v[st] || ((v[i] == v[st]) && (rand() % 2 == 1)))
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

#pragma endregion

#pragma region Sortari_double:

void Bubble_double(double v[], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (v[j + 1] < v[j])
				swap(v[j + 1], v[j]);
}

void Interclasare_double(double v[], int s, int d)
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

void Merge_double(double v[], int s, int d)
{
	if (d - s < 2)
	{
		if (v[s] > v[d])
			swap(v[s], v[d]);
	}
	else
	{
		int m = (s + d) / 2;
		Merge_double(v, s, m);
		Merge_double(v, m + 1, d);
		Interclasare_double(v, s, d);

	}
}

void Quick_pivst_double(double v[], int st, int dr)
{
	if (st < dr)
	{
		int piv = v[st];
		int id = dr;
		for (int i = st + 1; i <= id; i++)
			if (v[i] > piv || ((v[i] == piv) && (rand() % 2 == 1)))
			{
				swap(v[i], v[id]);
				id--;
				i--;
			}
		swap(v[st], v[id]);
		Quick_pivst_double(v, st, id - 1);
		Quick_pivst_double(v, id + 1, dr);
	}
}

int Med3_double(double v[], int st, int dr)
{
	int mij = (st + dr) / 2;
	if ((v[st] > v[mij]) xor (v[st] > v[dr]))
		return st;
	else if ((v[dr] > v[st]) xor (v[dr] > v[mij]))
		return dr;
	else
		return mij;
}

void Quick_pivMed3_double(double v[], int st, int dr)
{
	if (st < dr)
	{
		int piv = Med3_double(v, st, dr);
		int id = dr;
		swap(v[piv], v[st]);
		for (int i = st + 1; i <= id; i++)
			if (v[i] > v[st] || ((v[i] == v[st]) && (rand() % 2 == 1)))
			{
				swap(v[i], v[id]);
				id--;
				i--;
			}
		swap(v[st], v[id]);
		Quick_pivMed3_double(v, st, id - 1);
		Quick_pivMed3_double(v, id + 1, dr);
	}
}

#pragma endregion

#pragma region Sortari_string:

void Bubble_string(string v[], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (v[j + 1] < v[j])
				swap(v[j + 1], v[j]);
}

void Interclasare_string(string v[], int s, int d)
{
	int m = (s + d) / 2;
	int i1 = s;
	int i2 = m + 1;
	int k = 0;
	while (i1 <= m and i2 <= d)
	{
		if (v[i1] <= v[i2])
		{
			snou[k] = v[i1];
			k++;
			i1++;
		}
		else
		{
			snou[k] = v[i2];
			k++;
			i2++;
		}
	}
	while (i1 <= m)
	{
		snou[k] = v[i1];
		i1++;
		k++;
	}
	while (i2 <= d)
	{
		snou[k] = v[i2];
		i2++;
		k++;
	}
	for (int i = s; i <= d; i++)
		v[i] = snou[i - s];
}

void Merge_string(string v[], int s, int d)
{
	if (d - s < 2)
	{
		if (v[s] > v[d])
			swap(v[s], v[d]);
	}
	else
	{
		int m = (s + d) / 2;
		Merge_string(v, s, m);
		Merge_string(v, m + 1, d);
		Interclasare_string(v, s, d);

	}
}

void Quick_pivst_string(string v[], int st, int dr)
{
	if (st < dr)
	{
		string piv = v[st];
		int id = dr;
		for (int i = st + 1; i <= id; i++)
			if (v[i] > piv || ((v[i] == piv) && (rand() % 2 == 1)))
			{
				swap(v[i], v[id]);
				id--;
				i--;
			}
		swap(v[st], v[id]);
		Quick_pivst_string(v, st, id - 1);
		Quick_pivst_string(v, id + 1, dr);
	}
}

int Med3_string(string v[], int st, int dr)
{
	int mij = (st + dr) / 2;
	if ((v[st] > v[mij]) xor (v[st] > v[dr]))
		return st;
	else if ((v[dr] > v[st]) xor (v[dr] > v[mij]))
		return dr;
	else
		return mij;
}

void Quick_pivMed3_string(string v[], int st, int dr)
{
	if (st < dr)
	{
		int piv = Med3_string(v, st, dr);
		int id = dr;
		swap(v[piv], v[st]);
		for (int i = st + 1; i <= id; i++)
			if (v[i] > v[st] || ((v[i] == v[st]) && (rand() % 2 == 1)))
			{
				swap(v[i], v[id]);
				id--;
				i--;
			}
		swap(v[st], v[id]);
		Quick_pivMed3_string(v, st, id - 1);
		Quick_pivMed3_string(v, id + 1, dr);
	}
}

#pragma endregion

#pragma endregion

#pragma region Generatoare:

#pragma region Generatoare_Int:

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
	Merge(v, 0, nr - 1);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_almost_cresc(int v[], int nr, int nrmax)
{
	generator_cresc(v, nr, nrmax);
	for (int i = 0; i < nr; i += 100)
		swap(v[i], v[nr - i - 1]);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_desc(int v[], int nr, int nrmax)
{
	generator_cresc(v, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(v[i], v[nr - i - 1]);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_almost_desc(int v[], int nr, int nrmax)
{
	generator_almost_cresc(v, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(v[i], v[nr - i - 1]);
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

#pragma endregion

#pragma region Generatoare_Double:

void generator_double(double d[], int nr, int nrmax)
{
	for (int i = 0; i < nr; i++)
		d[i] = llrand() % (nrmax) + (llrand() % 1000) / 1000;
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_cresc_double(double d[], int nr, int nrmax)
{
	generator_double(d, nr, nrmax);
	Merge_double(d, 0, nr - 1);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_almost_cresc_double (double d[], int nr, int nrmax)
{
	generator_cresc_double(d, nr, nrmax);
	for (int i = 0; i < nr; i += 100)
		swap(d[i], d[nr - i - 1]);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_desc_double(double d[], int nr, int nrmax)
{
	generator_cresc_double(d, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(d[i], d[nr - i - 1]);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_almost_desc_double(double d[], int nr, int nrmax)
{
	generator_almost_cresc_double(d, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(d[i], d[nr - i - 1]);
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

void generator_const_double(double d[], int nr, int nrmax)
{
	double c = llrand() % (nrmax + 1) + (llrand() % 1000) / 1000;
	for (int i = 0; i < nr; i++)
		d[i] = c;
	for (int i = 0; i < nr; i++)
		vnou[i] = 0;
}

#pragma endregion

#pragma region Generatoare_String:

string gen_random(const int len) {

	string random;
	static const char alfabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";


	random.reserve(len);

	for (int i = 0; i < len; ++i)
		random += alfabet[rand() % (sizeof(alfabet) - 1)];


	return random;
}

void generator_string(string s[], int nr, int nrmax)
{
	for (int i = 0; i < nr; i++)
		s[i] = gen_random(nrmax);
}

void generator_cresc_string(string s[], int nr, int nrmax)
{
	generator_string(s, nr, nrmax);
	Merge_string(s, 0, nr - 1);
}

void generator_almost_cresc_string(string s[], int nr, int nrmax)
{
	generator_cresc_string(s, nr, nrmax);
	for (int i = 0; i < nr; i += 100)
		swap(s[i], s[nr - i - 1]);
}

void generator_desc_string(string s[], int nr, int nrmax)
{
	generator_cresc_string(s, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(s[i], s[nr - i - 1]);
}

void generator_almost_desc_string(string s[], int nr, int nrmax)
{
	generator_almost_cresc_string(s, nr, nrmax);
	for (int i = 0; i < nr / 2; i++)
		swap(s[i], s[nr - i - 1]);
}

void generator_const_string(string s[], int nr, int nrmax)
{
	string c = gen_random(nrmax);
	for (int i = 0; i < nr; i++)
		s[i] = c;
}

#pragma endregion

#pragma endregion

#pragma region Chestii:

bool verificare(int v[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (v[i] > v[i + 1])
			return false;
	return true;
}

bool verificare_double(double v[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (v[i] > v[i + 1])
			return false;
	return true;
}

bool verificare_string(string v[], int n)
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

#pragma endregion

#pragma region Afisare_sortari:

#pragma region Afisare_sortari_int:

void Bubble_sort(int v[], int gen)
{
	if (nr <= 10000)
	{
		if (gen == 1)
			generator(v, nr, nrmax);
		else if (gen == 2)
			generator_cresc(v, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc(v, nr, nrmax);
		else if (gen == 4)
			generator_desc(v, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc(v, nr, nrmax);
		else if (gen == 6)
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
		cout << "Bubble dureaza prea mult.\n";
	}
}

void Count_sort(int v[], int gen)
{
	if (nrmax <= 100000000)
	{
		if (gen == 1)
			generator(v, nr, nrmax);
		else if (gen == 2)
			generator_cresc(v, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc(v, nr, nrmax);
		else if (gen == 4)
			generator_desc(v, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc(v, nr, nrmax);
		else if (gen == 6)
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
		cout << "Count dureaza prea mult.\n";
	}
}

void RadixLSD_sort(int v[], int gen)
{
	if (gen == 1)
		generator(v, nr, nrmax);
	else if (gen == 2)
		generator_cresc(v, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc(v, nr, nrmax);
	else if (gen == 4)
		generator_desc(v, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc(v, nr, nrmax);
	else if (gen == 6)
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

void RadixMSD_opbit_sort(int v[], int gen)
{
	if (gen == 1)
		generator(v, nr, nrmax);
	else if (gen == 2)
		generator_cresc(v, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc(v, nr, nrmax);
	else if (gen == 4)
		generator_desc(v, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc(v, nr, nrmax);
	else if (gen == 6)
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

void Merge_sort(int v[], int gen)
{
	if (gen == 1)
		generator(v, nr, nrmax);
	else if (gen == 2)
		generator_cresc(v, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc(v, nr, nrmax);
	else if (gen == 4)
		generator_desc(v, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc(v, nr, nrmax);
	else if (gen == 6)
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

void Quick_pivst_sort(int v[], int gen)
{
	if ((nr <= 10000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator(v, nr, nrmax);
		else if (gen == 2)
			generator_cresc(v, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc(v, nr, nrmax);
		else if (gen == 4)
			generator_desc(v, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc(v, nr, nrmax);
		else if (gen == 6)
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
		cout << "Quick_pivst dureaza prea mult.\n";
	}
}

void Quick_pivMed3_sort(int v[], int gen)
{
	if ((nr <= 100000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator(v, nr, nrmax);
		else if (gen == 2)
			generator_cresc(v, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc(v, nr, nrmax);
		else if (gen == 4)
			generator_desc(v, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc(v, nr, nrmax);
		else if (gen == 6)
			generator_const(v, nr, nrmax);
		float t = clock();
		Quick_pivMed3(v, 0, nr - 1);
		t = clock() - t;
		cout << "Quick_pivMed3 a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare(v, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT\n";
	}
	else
	{
		cout << "Quick_pivMed3 dureaza prea mult.\n";
	}
}

void STD_sort(int v[], int gen)
{
	if (gen == 1)
		generator(v, nr, nrmax);
	else if (gen == 2)
		generator_cresc(v, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc(v, nr, nrmax);
	else if (gen == 4)
		generator_desc(v, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc(v, nr, nrmax);
	else if (gen == 6)
		generator_const(v, nr, nrmax);
	float t = clock();
	sort(v, v + nr);
	t = clock() - t;
	cout << "STD_sort a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
	if (verificare(v, nr) == true)
		cout << "SORTAT!\n\n\n";
	else
		cout << "NESORTAT\n";
}

#pragma endregion

#pragma region Afisare_sortari_double:

void Bubble_sort_double(double d[], int gen)
{
	if (nr <= 10000)
	{
		if (gen == 1)
			generator_double(d, nr, nrmax);
		else if (gen == 2)
			generator_cresc_double(d, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_double(d, nr, nrmax);
		else if (gen == 4)
			generator_desc_double(d, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_double(d, nr, nrmax);
		else if (gen == 6)
			generator_const_double(d, nr, nrmax);
		float t = clock();
		Bubble_double(d, nr);
		t = clock() - t;
		cout << "Bubble_sort_double a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_double(d, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT.\n";
	}
	else
	{
		cout << "Bubble_double dureaza prea mult.\n";
	}
}

void Merge_sort_double(double d[], int gen)
{
	if (gen == 1)
		generator_double(d, nr, nrmax);
	else if (gen == 2)
		generator_cresc_double(d, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc_double(d, nr, nrmax);
	else if (gen == 4)
		generator_desc_double(d, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc_double(d, nr, nrmax);
	else if (gen == 6)
		generator_const_double(d, nr, nrmax);
	float t = clock();
	Merge_double(d, 0, nr - 1);
	t = clock() - t;
	cout << "Merge_sort_double a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
	if (verificare_double(d, nr) == true)
		cout << "SORTAT!\n";
	else
		cout << "NESORTAT!\n";
}

void Quick_pivst_sort_double(double d[], int gen)
{
	if ((nr <= 10000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator_double(d, nr, nrmax);
		else if (gen == 2)
			generator_cresc_double(d, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_double(d, nr, nrmax);
		else if (gen == 4)
			generator_desc_double(d, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_double(d, nr, nrmax);
		else if (gen == 6)
			generator_const_double(d, nr, nrmax);
		float t = clock();
		Quick_pivst_double(d, 0, nr - 1);
		t = clock() - t;
		cout << "Quick_pivst_double a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_double(d, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT!\n";
	}
	else
	{
		cout << "Quick_pivst_double dureaza prea mult.\n";
	}
}

void Quick_pivMed3_sort_double(double d[], int gen)
{
	if ((nr <= 10000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator_double(d, nr, nrmax);
		else if (gen == 2)
			generator_cresc_double(d, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_double(d, nr, nrmax);
		else if (gen == 4)
			generator_desc_double(d, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_double(d, nr, nrmax);
		else if (gen == 6)
			generator_const_double(d, nr, nrmax);
		float t = clock();
		Quick_pivMed3_double(d, 0, nr - 1);
		t = clock() - t;
		cout << "Quick_pivMed3_double a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_double(d, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT\n";
	}
	else
	{
		cout << "Quick_pivMed3_double dureaza prea mult.\n";
	}
}

void STD_sort_double(double d[], int gen)
{
	if (gen == 1)
		generator_double(d, nr, nrmax);
	else if (gen == 2)
		generator_cresc_double(d, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc_double(d, nr, nrmax);
	else if (gen == 4)
		generator_desc_double(d, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc_double(d, nr, nrmax);
	else if (gen == 6)
		generator_const_double(d, nr, nrmax);
	float t = clock();
	sort(d, d + nr);
	t = clock() - t;
	cout << "STD_sort_double a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
	if (verificare_double(d, nr) == true)
		cout << "SORTAT!\n\n\n";
	else
		cout << "NESORTAT\n";
}

#pragma endregion

#pragma region Afisare_sortari_string:

void Bubble_sort_string(string s[], int gen)
{
	if (nr <= 10000)
	{
		if (gen == 1)
			generator_string (s, nr, nrmax);
		else if (gen == 2)
			generator_cresc_string (s, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_string(s, nr, nrmax);
		else if (gen == 4)
			generator_desc_string(s, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_string(s, nr, nrmax);
		else if (gen == 6)
			generator_const_string(s, nr, nrmax);
		float t = clock();
		Bubble_string(s, nr);
		t = clock() - t;
		cout << "Bubble_sort_string a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_string(s, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT.\n";
	}
	else
	{
		cout << "Bubble_string dureaza prea mult.\n";
	}
}

void Merge_sort_string(string s[], int gen)
{
	if (gen == 1)
		generator_string(s, nr, nrmax);
	else if (gen == 2)
		generator_cresc_string(s, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc_string(s, nr, nrmax);
	else if (gen == 4)
		generator_desc_string(s, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc_string(s, nr, nrmax);
	else if (gen == 6)
		generator_const_string(s, nr, nrmax);
	float t = clock();
	Merge_string (s, 0, nr - 1);
	t = clock() - t;
	cout << "Merge_sort_string a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
	if (verificare_string(s, nr) == true)
		cout << "SORTAT!\n";
	else
		cout << "NESORTAT!\n";
}

void Quick_pivst_sort_string(string s[], int gen)
{
	if ((nr <= 10000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator_string(s, nr, nrmax);
		else if (gen == 2)
			generator_cresc_string(s, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_string(s, nr, nrmax);
		else if (gen == 4)
			generator_desc_string(s, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_string(s, nr, nrmax);
		else if (gen == 6)
			generator_const_string(s, nr, nrmax);
		float t = clock();
		Quick_pivst_string(s, 0, nr - 1);
		t = clock() - t;
		cout << "Quick_pivst_string a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_string(s, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT!\n";
	}
	else
	{
		cout << "Quick_pivst_string dureaza prea mult.\n";
	}
}

void Quick_pivMed3_sort_string(string s[], int gen)
{
	if ((nr <= 10000) || ((gen == 1) || (gen == 6)))
	{
		if (gen == 1)
			generator_string(s, nr, nrmax);
		else if (gen == 2)
			generator_cresc_string(s, nr, nrmax);
		else if (gen == 3)
			generator_almost_cresc_string(s, nr, nrmax);
		else if (gen == 4)
			generator_desc_string(s, nr, nrmax);
		else if (gen == 5)
			generator_almost_desc_string(s, nr, nrmax);
		else if (gen == 6)
			generator_const_string(s, nr, nrmax);
		float t = clock();
		Quick_pivMed3_string (s, 0, nr - 1);
		t = clock() - t;
		cout << "Quick_pivMed3_string a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
		if (verificare_string(s, nr) == true)
			cout << "SORTAT!\n";
		else
			cout << "NESORTAT\n";
	}
	else
	{
		cout << "Quick_pivMed3_string dureaza prea mult.\n";
	}
}

void STD_sort_string(string s[], int gen)
{
	if (gen == 1)
		generator_string(s, nr, nrmax);
	else if (gen == 2)
		generator_cresc_string(s, nr, nrmax);
	else if (gen == 3)
		generator_almost_cresc_string(s, nr, nrmax);
	else if (gen == 4)
		generator_desc_string(s, nr, nrmax);
	else if (gen == 5)
		generator_almost_desc_string(s, nr, nrmax);
	else if (gen == 6)
		generator_const_string(s, nr, nrmax);
	float t = clock();
	sort(s, s + nr);
	t = clock() - t;
	cout << "STD_sort_string a durat:" << t / CLOCKS_PER_SEC << " secunde.\n";
	if (verificare_string(s, nr) == true)
		cout << "SORTAT!\n\n\n";
	else
		cout << "NESORTAT\n";
}

#pragma endregion

#pragma endregion

#pragma region Teste:

void teste_int(int i)
{
	cout << "\nIntroduceti numarul de termeni (<= 10.000.000)";
	cout << " si marimea maxima a aceastora (<= limita int-ului) pentru testul ";
	cout << i + 1 << " - termeni de tip int:\n";
	cin >> nr >> nrmax;
	cout << "\nTestul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array random cu elemente de tip int:\n\n";
	Bubble_sort(v, 1);
	Count_sort(v, 1);
	RadixLSD_sort(v, 1);
	RadixMSD_opbit_sort(v, 1);
	Merge_sort(v, 1);
	Quick_pivst_sort(v, 1);
	Quick_pivMed3_sort(v, 1);
	STD_sort(v, 1);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array crescator cu elemente de tip int:\n\n";
	Bubble_sort(v, 2);
	Count_sort(v, 2);
	RadixLSD_sort(v, 2);
	RadixMSD_opbit_sort(v, 2);
	Merge_sort(v, 2);
	Quick_pivst_sort(v, 2);
	Quick_pivMed3_sort(v, 2);
	STD_sort(v, 2);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape crescator cu elemente de tip int:\n\n";
	Bubble_sort(v, 3);
	Count_sort(v, 3);
	RadixLSD_sort(v, 3);
	RadixMSD_opbit_sort(v, 3);
	Merge_sort(v, 3);
	Quick_pivst_sort(v, 3);
	Quick_pivMed3_sort(v, 3);
	STD_sort(v, 3);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array descrescator cu elemente de tip int:\n\n";
	Bubble_sort(v, 4);
	Count_sort(v, 4);
	RadixLSD_sort(v, 4);
	RadixMSD_opbit_sort(v, 4);
	Merge_sort(v, 4);
	Quick_pivst_sort(v, 4);
	Quick_pivMed3_sort(v, 4);
	STD_sort(v, 4);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape descrescator cu elemente de tip int:\n\n";
	Bubble_sort(v, 5);
	Count_sort(v, 5);
	RadixLSD_sort(v, 5);
	RadixMSD_opbit_sort(v, 5);
	Merge_sort(v, 5);
	Quick_pivst_sort(v, 5);
	Quick_pivMed3_sort(v, 5);
	STD_sort(v, 5);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array constant cu elemente de tip int:\n\n";
	Bubble_sort(v, 6);
	Count_sort(v, 6);
	RadixLSD_sort(v, 6);
	RadixMSD_opbit_sort(v, 6);
	Merge_sort(v, 6);
	Quick_pivst_sort(v, 6);
	Quick_pivMed3_sort(v, 6);
	STD_sort(v, 6);

	cout << "\n\n";
}

void teste_double(int i)
{
	cout << "\nIntroduceti numarul de termeni (<= 10.000.000)";
	cout << "si marimea maxima a aceastora (<= limita double-ului) pentru testul ";
	cout << i + 1 << " - termeni de tip double:\n";
	cin >> nr >> nrmax;
	cout << "\nTestul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array random cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 1);
	Merge_sort_double(d, 1);
	Quick_pivst_sort_double(d, 1);
	Quick_pivMed3_sort_double(d, 1);
	STD_sort_double(d, 1);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array crescator cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 2);
	Merge_sort_double(d, 2);
	Quick_pivst_sort_double(d, 2);
	Quick_pivMed3_sort_double(d, 2);
	STD_sort_double(d, 2);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape crescator cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 3);
	Merge_sort_double(d, 3);
	Quick_pivst_sort_double(d, 3);
	Quick_pivMed3_sort_double(d, 3);
	STD_sort_double(d, 3);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array descrescator cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 4);
	Merge_sort_double(d, 4);
	Quick_pivst_sort_double(d, 4);
	Quick_pivMed3_sort_double(d, 4);
	STD_sort_double(d, 4);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape descrescator cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 5);
	Merge_sort_double(d, 5);
	Quick_pivst_sort_double(d, 5);
	Quick_pivMed3_sort_double(d, 5);
	STD_sort_double(d, 5);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array constant cu elemente de tip double:\n\n";
	Bubble_sort_double(d, 6);
	Merge_sort_double(d, 6);
	Quick_pivst_sort_double(d, 6);
	Quick_pivMed3_sort_double(d, 6);
	STD_sort_double(d, 6);

	cout << "\n\n";
}

void teste_string (int i)
{
	cout << "\nIntroduceti numarul de termeni (<= 1.000.000)";
	cout << "si marimea maxima a aceastora (<= 250) pentru testul ";
	cout << i + 1 << " - termeni de tip string:\n";
	cin >> nr >> nrmax;
	cout << "\nTestul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array random cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 1);
	Merge_sort_string(s, 1);
	Quick_pivst_sort_string(s, 1);
	Quick_pivMed3_sort_string(s, 1);
	STD_sort_string(s, 1);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array crescator cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 2);
	Merge_sort_string(s, 2);
	Quick_pivst_sort_string(s, 2);
	Quick_pivMed3_sort_string(s, 2);
	STD_sort_string(s, 2);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape crescator cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 3);
	Merge_sort_string(s, 3);
	Quick_pivst_sort_string(s, 3);
	Quick_pivMed3_sort_string(s, 3);
	STD_sort_string(s, 3);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array descrescator cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 4);
	Merge_sort_string(s, 4);
	Quick_pivst_sort_string(s, 4);
	Quick_pivMed3_sort_string(s, 4);
	STD_sort_string(s, 4);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array aproape descrescator cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 5);
	Merge_sort_string(s, 5);
	Quick_pivst_sort_string(s, 5);
	Quick_pivMed3_sort_string(s, 5);
	STD_sort_string(s, 5);

	cout << "Testul numarul " << i + 1 << " cu " << nr << " numere si marimea maxima de " << nrmax;
	cout << " pentru un array constant cu elemente de tip string:\n\n";
	Bubble_sort_string(s, 6);
	Merge_sort_string(s, 6);
	Quick_pivst_sort_string(s, 6);
	Quick_pivMed3_sort_string(s, 6);
	STD_sort_string(s, 6);

	cout << "\n\n";
}

#pragma endregion

void meniu()
{
	int nrteste;
	cout << "Introduceti numarul de teste: \n";
	cin >> nrteste;
	for (int i = 0; i < nrteste; i++)
	{
		int cerinta;
		cout << "\nDoriti ca testele sa fie pentru:\n";
		cout << "Optiunea 1 - doar int\n";
		cout << "Optiunea 2 - doar double\n";
		cout << "Optiunea 3 - doar string\n";
		cout << "Optiunea 4 - toate trei\n";
		cout << "Optiunea dumneavoastra = ";
		cin >> cerinta;
		switch (cerinta)
		{
		case 1:
		{
			teste_int(i);
			break;
		}
		case 2:
		{
			teste_double(i);
			break;
		}
		case 3:
		{
			teste_string(i);
			break;
		}
		case 4:
		{
			teste_int(i);
			teste_double(i);
			teste_string(i);
			break;
		}
		}
	}
}

int main()
{
	srand(time(NULL));
	meniu();
	return 0;
}

