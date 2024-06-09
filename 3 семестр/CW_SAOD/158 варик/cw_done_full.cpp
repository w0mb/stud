
#define YES true
#define NO false

#include <fstream>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

const int N = 4000;
const int M = 256;
int sum = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

int sim_cf = 0, sim_f = 0, sym_count = 0;

int *W;
int *h;

struct country
{
	char FIO[32];
	char street[18];
	short int number_home;
	short int number_appart;
	char Date[10];
};

struct list
{
	country *data;
	list *next;
	list *prev;
};

struct Vertex
{
	country *data;
	int w;
	int h;
	Vertex *Next;
	Vertex *Left;
	Vertex *Right;
};
Vertex *root = NULL;

struct SN_code
{
	float p;
	float q;
	int l;
	char a;
};
SN_code A[M];

int Menu();

void Read_base(FILE *fp, list *base);
void copy_base(list *, list *);

void Print(list *Base);
void Print_sort_index_mas(list **mas);

void quick_sort(list *&head);
void perseption(list *h1, list *t1, list *h2, list *t2, list *&hr, list *&tr);
int compare(char *a, char *b);
int compare_street(char *a, char *b);
int compare_house_num(short int a, short int b);

int BSearch(list **A, char *depositor);

void A2(int L, int R, list **mas);
void seth(Vertex *p);
void LR_print(Vertex *p, int &count);
void TreeSearch(Vertex *p, short int num);

int size(Vertex *);
int height(Vertex *);
int max(int, int);
int sdp(Vertex *, int);

void shanon();
void Code();
void code_file();
void CodePrint();

int Menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE *fp;
	int search_start = 0;
	int search = N - 1;
	W = new int[N];

	fp = fopen("testBase4.dat", "rb");
	list *OriginBase = new list;
	list *SortBase = new list;
	Read_base(fp, OriginBase);
	fclose(fp);
	copy_base(OriginBase, SortBase);
	quick_sort(SortBase);
	list *mas[N];
	for (int i = 0; i < N; i++)
	{
		mas[i] = SortBase;
		SortBase = SortBase->next;
	}
	Code();
	code_file();

	int SoD;
	cout << "1.Standard list\n2.Sorted list\n3.BSearch\n4.TreePrint\n5.Coding\n6.Exit" << endl;
	cin >> SoD;
	switch (SoD)
	{
	case 1:
	{
		Print(OriginBase);
		break;
	}
	case 2:
	{
		Print_sort_index_mas(mas);
		break;
	}
	case 3:
	{
		cout << endl;
		cout << "Enter Fio" << endl;
		char date[3];
		SetConsoleCP(866);
		cin >> date;
		SetConsoleCP(1251);
		if (strcmp(date, "0") != 0)
		{
			search = BSearch(mas, date);
			int fam_pos = 0;
			if (search == -1)
			{
				cout << "This Fio doesn't exists''" << endl;
			}
			else
			{
				do
				{
					if (search == 0)
					{
						break;
					}
					else
					{
						search--;
					}
					if (strncmp(mas[search]->data->FIO, date, 3) != 0)
					{
						search++;
						break;
					}
				} while (YES);

				search_start = search;

				do
				{
					search++;
					if (search == N)
					{
						search--;
						break;
					}
					if (strncmp(mas[search]->data->FIO, date, 3) != 0)
					{
						break;
					}
				} while (YES);
				cout << endl
					 << endl
					 << "Founded " << search - search_start << " pozitions (" << search_start << " - " << search - 1 << ")" << endl;
				for (int i = search_start; i < search; i++)
				{
					cout << i << " " << mas[i]->data->FIO << "\t" << mas[i]->data->street << "\t" << mas[i]->data->number_home
						 << "\t" << mas[i]->data->number_appart << "\t" << mas[i]->data->Date << endl;
					W[i] = rand() % 99 + 1;
				}
				A2(search_start, search, mas);
				root->h = 1;
				seth(root);
			}
		}
		break;
	}

	case 4:
	{

		int count = 0;
		short int num;
		LR_print(root, count);
		cout << endl;
		printf("+------+----------+----------+----------------+\n");
		printf("|%6d| UniqSize |  Height  |   Mid. height  |\n", N);
		printf("+------+----------+----------+----------------+\n");
		printf("|  A2  |%10d|%10d|%16.2f|\n", size(root), height(root), (double)sdp(root, 1) / size(root));
		printf("+------+----------+----------+----------------+\n");
		cout << endl
			 << "Element find: " << endl;
		SetConsoleCP(866);
		cin >> num;
		SetConsoleCP(1251);

		TreeSearch(root, num);

		break;
	}
	case 5:
	{
		CodePrint();
		break;
	}
	case 6:
	{
		system("PAUSE");
		return 0;
	}
	default:
	{
		cout << "Invalid number entered\nPlease enter numder again" << endl;
		system("PAUSE");
		system("cls");
		break;
	}
	}
	_getch();
	Menu();
	return 0;
}

int main()
{
	Menu();
	return 0;
}

void CodeBase()
{
	FILE *fp, *fcoded;
	fp = fopen("testBase4.dat", "rb");
	fcoded = fopen("BaseCoded.dat", "wb");
	char buffer;
	while (!feof(fp))
	{
		fscanf(fp, "%c", &buffer);
		fcompression++;
		for (int i = 0; i < M; i++)
		{
			if (buffer == (char)(i - 128))
			{
				for (int j = 0; j < A[i].l; j++)
				{
					putc(code[i][j], fcoded);
					cfcompression++;
				}
			}
		}
	}
	fclose(fp);
	fclose(fcoded);
}

void CodePrint()
{
	lgm = 0;
	SetConsoleCP(866);
	printf("\n\nshenon: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| num element   | symbol | veroyatnost |           binary code| dlina coda         |\n");
	printf("|               |        |             |                      |                    |\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M && A[i].p != 0; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ", i, A[i].a, A[i].q);
		for (int j = 0; j < A[i].l + 1; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("   |  %7d      |\n", A[i].l + 1);
		lgm += A[i].p * A[i].l;
	}
	printf("________________________________________________\n");
	printf("| entropy      | avarage dlina coda | koof sjatia         |\n");
	printf("|______________|____________________|_____________________|\n");
	printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)sim_f / sim_cf);
	printf("|______________|____________________|_____________________|\n");

	cout << endl
		 << endl
		 << entropy + 1 << " > " << lgm << endl
		 << endl;
	SetConsoleCP(1251);
}

void Code()
{

	int i, j;
	FILE *f;
	f = fopen("testBase4.dat", "rb");
	for (i = 0; i < M; i++)
	{
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i - 128);
	}
	while (!feof(f))
	{
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		A[c + 128].p += 1;
		sum++;
	}
	fclose(f);
	printf("\n");

	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)
		{
			if (A[i - 1].p < A[i].p)
			{
				SN_code B = A[i - 1];
				A[i - 1] = A[i];
				A[i] = B;
				b = true;
			}
		}
	}
	for (i = 0; i < M && A[i].p != 0; i++)
	{
		A[i].p /= sum;
		A[i].q = A[i].p;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
		sym_count++;
	}
	shanon();
}

void code_file()
{
	FILE *f, *cf;
	f = fopen("testBase4.dat", "rb");
	cf = fopen("CodeBase.dat", "wb");
	char sim;
	while (!feof(f))
	{
		fscanf(f, "%c", &sim);
		sim_f++;
		for (int i = 0; i < M; i++)
		{
			if (sim == A[i].a)
			{
				for (int j = 0; j < A[i].l; j++)
				{
					putc(code[i][j], cf);
					sim_cf++;
				}
			}
		}
	}
	_fcloseall();
}

void shanon()
{
	for (int i = 0; i < M && A[i].p != 0; i++)
	{
		A[i].q = A[i - 1].q + A[i].p;
		A[i].l = ceil(-log(A[i].p) / log(2));
	}
	for (int i = 1; i < M && A[i].p != 0; i++)
	{
		for (int j = 1; j <= A[i].l; j++)
		{
			A[i - 1].q *= 2;
			code[i][j] = floor(A[i - 1].q);
			while (A[i - 1].q >= 1)
				A[i - 1].q -= 1;
		}
	}
}

void LR_print(Vertex *p, int &count)
{
	if (p != NULL)
	{
		LR_print(p->Left, count);
		cout << count + 1 << ") " << p->data->FIO << "\t" << p->data->street << "\t" << p->data->number_home
			 << "\t" << p->data->number_appart << "\t" << p->data->Date << endl;
		count++;
		LR_print(p->Next, count);
		LR_print(p->Right, count);
	}
}

void add_vertex(Vertex *&p, list *mas, int w)
{
	if (p == NULL)
	{
		p = new Vertex;
		p->data = mas->data;
		p->w = w;
		p->Next = NULL;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (compare_street(p->data->Date, mas->data->Date) == 0)
	{
		add_vertex(p->Next, mas, w);
	}
	else if (compare_street(p->data->Date, mas->data->Date) > 0)
	{
		add_vertex(p->Left, mas, w);
	}
	else if (compare_street(p->data->Date, mas->data->Date) < 0)
	{
		add_vertex(p->Right, mas, w);
	}
}

void A2(int L, int R, list **mas)
{
	int wes = 0, sum = 0;
	int i;
	if (L <= R)
	{
		for (i = L; i <= R; i++)
		{
			wes = wes + W[i];
		}
		for (i = L; i < R; i++)
		{
			if ((sum < (wes / 2)) && (sum + W[i]) > (wes / 2))
			{
				break;
			}
			sum = sum + W[i];
		}

		add_vertex(root, mas[i], W[i]);
		A2(L, i - 1, mas);
		A2(i + 1, R, mas);
	}
}

void TreeSearch(Vertex *p, short int num)
{
	if (p != NULL)
	{
		if (compare_house_num(p->data->number_home, num) > 0)
		{
			TreeSearch(p->Left, num);
		}
		else if (compare_house_num(p->data->number_home, num) < 0)
		{
			TreeSearch(p->Right, num);
		}
		else
		{

			cout << p->data->FIO << "\t" << p->data->street << "\t" << p->data->number_home
				 << "\t" << p->data->number_appart << "\t" << p->data->Date << endl;
		}

		TreeSearch(p->Next, num);
	}
}

void seth(Vertex *p)
{
	if (p)
	{
		if (p->Next)
		{
			p->Next->h = p->h + 1;
		}
		if (p->Left)
		{
			p->Left->h = p->h + 1;
		}
		if (p->Right)
		{
			p->Right->h = p->h + 1;
		}
		seth(p->Left);
		seth(p->Right);
		seth(p->Next);
	}
}

void Read_base(FILE *fp, list *base)
{
	country *mas = new country();
	fread((country *)mas, sizeof(country), 1, fp);
	base->data = mas;
	base->prev = NULL;
	base->next = NULL;

	for (int i = 1; i < N; i++)
	{
		mas = new country();
		list *base_prev;
		fread((country *)mas, sizeof(country), 1, fp);
		base_prev = base;
		base = base->next = new list();
		base->data = mas;
		base->prev = base_prev;
		base->next = NULL;
	}
}

int compare(country *a, country *b)
{
	int result = strcmp(a->FIO, b->FIO);

	if (result == 0)
	{

		result = strcmp(a->street, b->street);
	}

	return result;
}

int compare_street(char *a, char *b)
{
	char bufferA[18];
	char bufferB[18];
	strcpy(bufferA, a);
	strcpy(bufferB, b);

	int space_pos_a = strchr(a, ' ') - a;
	int space_pos_b = strchr(b, ' ') - b;

	int count;
	if (space_pos_a <= space_pos_b)
	{
		count = space_pos_a;
	}
	else
	{
		count = space_pos_b;
	}

	if (strncmp(a, b, count) == 0)
	{
		if (space_pos_a == space_pos_b)
		{
			return 0;
		}
		if (space_pos_a < space_pos_b)
		{
			return 1;
		}
		return -1;
	}

	if (strncmp(a, b, count) > 0)
	{
		return 1;
	}
	return -1;
}
int BSearch(list **A, char *FIO_prefix)
{
	int l = 0, r = N, m = 0;
	while (l < r)
	{
		m = (l + r) / 2;
		if (strncmp(A[m]->data->FIO, FIO_prefix, 3) == 0)
		{
			return m;
		}
		if (strncmp(A[m]->data->FIO, FIO_prefix, 3) < 0)
			l = m + 1;
		else
			r = m - 1;
	}
	return -1;
}

int compare_house_num(short int a, short int b)
{

	if (a == b)
	{

		return 0;
	}
	else if (a < b)
	{

		return -1;
	}
	else
	{

		return 1;
	}
}

void perseption(list *h1, list *t1, list *h2, list *t2, list *&hr, list *&tr)
{
	if (compare(h1->data, h2->data) < 0)
	{
		hr = h1;
		h1 = h1->next;
	}
	else
	{
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2)
	{
		if (compare(h1->data, h2->data) < 0)
		{
			tr->next = h1;
			h1 = h1->next;
			tr = tr->next;
		}
		else
		{
			tr->next = h2;
			h2 = h2->next;
			tr = tr->next;
		}
	}
	if (t1->next != h1)
	{
		tr->next = h1;
		tr = t1;
	}
	else if (t2->next != h2)
	{
		tr->next = h2;
		tr = t2;
	}
	tr->next = NULL;
}

void quick_sort(list *&head)
{
	list *t = new list;
	t->data = NULL;
	t->next = head;
	int k = 1;
	int e = 0;
	list *hp, *tp, *h1, *t1, *h2, *t2, *hr, *tr;
	while (k < 4000)
	{
		hp = t;
		while (hp != NULL)
		{
			if (hp->next == NULL)
			{
				break;
			}
			h1 = hp->next;
			t1 = h1;
			for (int i = 1; i < k; i++)
			{
				if (t1->next == NULL)
				{
					break;
				}
				t1 = t1->next;
			}
			if (t1->next == NULL)
			{
				break;
			}
			h2 = t1->next;
			t2 = h2;
			t1->next = NULL;
			for (int i = 1; i < k; i++)
			{
				if (t2->next == NULL)
				{
					break;
				}
				t2 = t2->next;
			}
			tp = t2->next;
			t1->next = NULL;
			t2->next = NULL;
			perseption(h1, t1, h2, t2, hr, tr);
			hp->next = hr;
			head = hr;
			tr->next = tp;
			hp = tr;
		}
		k *= 2;
	}
}

void Print(list *Base)
{
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing" << endl;
	cin >> n;
	if (n == '1')
	{
		i = 0;
		while (i < N)
		{
			cout << i + 1 << "\t" << Base->data->FIO << "\t" << Base->data->street << "\t" << Base->data->number_home
				 << "\t" << Base->data->number_appart << "\t" << Base->data->Date << endl;
			i++;
			if (int result = _kbhit())
			{
				printf("\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
				char something;
				cin >> something;
				if (something == 'e')
				{
					return;
				}
			}
			Base = Base->next;
		}
	}
	if (n == '2')
	{
		i = 0;
		int g = 0;
		for (int i = 0; i < N; i = i + 20)
		{
			while ((g++) < 20)
			{
				cout << i + g << "\t" << Base->data->FIO << "\t" << Base->data->street << "\t" << Base->data->number_home
					 << "\t" << Base->data->number_appart << "\t" << Base->data->Date << endl;
				Base = Base->next;
			}
			if (g >= 20)
			{
				cout << "y for continue" << endl;
				cin >> n;
				if (n == 'y')
					g = 0;
				else
					return;
			}
		}
	}
}

void Print_sort_index_mas(list **mas)
{
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing" << endl;
	cin >> n;
	if (n == '1')
	{
		i = 0;
		while (i < N)
		{
			cout << i + 1 << "\t" << mas[i]->data->FIO << "\t" << mas[i]->data->street << "\t" << mas[i]->data->number_home
				 << "\t" << mas[i]->data->number_appart << "\t" << mas[i]->data->Date << endl;
			i++;
			if (int result = _kbhit())
			{
				printf("\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
				char something;
				cin >> something;
				if (something == 'e')
				{
					return;
				}
			}
		}
	}
	if (n == '2')
	{
		i = 0;
		int g = 0;
		for (int i = 0; i < N; i = i + 20)
		{
			while ((g++) < 20)
			{
				cout << i + g << "\t" << mas[i + g]->data->FIO << "\t" << mas[i + g]->data->street << "\t" << mas[i + g]->data->number_home
					 << "\t" << mas[i + g]->data->number_appart << "\t" << mas[i + g]->data->Date << endl;
			}
			if (g >= 20)
			{
				cout << "y for continue" << endl;
				cin >> n;
				if (n == 'y')
					g = 0;
				else
					return;
			}
		}
	}
}

void copy_base(list *a, list *b)
{
	b->prev = NULL;
	b->data = a->data;
	for (int i = 1; i < N; i++)
	{
		a = a->next;
		b->next = new list;
		b->next->prev = b;
		b = b->next;
		b->data = a->data;
	}
	b->next = NULL;
}

int size(Vertex *x)
{
	if (x == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + size(x->Left) + size(x->Right);
	}
}

int max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

int height(Vertex *x)
{
	if (x == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(height(x->Left), height(x->Right));
	}
}

int sdp(Vertex *x, int l)
{
	if (x == NULL)
	{
		return 0;
	}
	else
	{
		return l + sdp(x->Left, l + 1) + sdp(x->Right, l + 1);
	}
}
