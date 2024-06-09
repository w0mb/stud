#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int N=4000;
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int sim_cf = 0, sim_f = 0, sym_count = 0;
int fcompression = 0, cfcompression = 0;
int *W;


struct base
{
	char depositor[30];
	unsigned short int deposit;
	char date[10];
	char lawyer[22];
	
};

struct list {
	base *data;
	list* next;
	list* prev;
};


struct Vertex {
	base *data;
    int w;
    int h;
	Vertex *Next;
	Vertex* Left;
	Vertex* Right;
};
Vertex *root = NULL;


struct SN_code {
	float p;
	float q;
	int l;
	char a;
};
SN_code A[M];

int Menu();

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);

void Print(list *Base);
void Print_sort_index_mas(list **mas);

void quick_sort(list*& head);
void perseption(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr, int sort);
int compare(char* a, char* b);
int compare_name(char* a, char* b);

int BSearch (list **A, char *date);

void A2(int L, int R, list **mas);
void seth(Vertex *p);
void LR_print(Vertex* p, int& count);
void TreeSearch (Vertex* p, char* data);

int size(Vertex*);
int height(Vertex*);
int max(int, int);
int sdp(Vertex*, int);

void shanon();
void Code();
void code_file();
void CodePrint();



int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += A[i].q;
	sr = A[R].q;
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= A[m].q;
		sr += A[m].q;
	}
	return m;
}

void fano(int L, int R, int k)
{
	if (L < R)
	{
		k++;
		int m = med(L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m)
				code[i][k] = 0;
			else
				code[i][k] = 1;
			A[i].l++;
		}
		fano(L, m, k);
		fano(m + 1, R, k);
	}
}

int Menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	

	fp = fopen("testBase3.dat", "rb");
	list* OriginBase = new list;
	list* SortBase = new list;
	Read_base(fp,OriginBase);
	fclose(fp);
	copy_base(OriginBase, SortBase);
    quick_sort(SortBase);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=SortBase;
		SortBase=SortBase->next;
	}
	W = new int[N];
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
			cout <<endl;
			cout << "Enter Fio"<<endl;
			char date[22];
			SetConsoleCP(866);
			cin >> date;
			SetConsoleCP(1251);
			if(strcmp(date,"0")!=0){
				search = BSearch(mas,date);
				int fam_pos=0;
				if(search == -1){
					cout << "This Fio doesn't exists''" << endl;
				}
				else{	
					do{
						if(search==0){
							break;
						}
						else{
							search--;
						}
				    	if(strncmp(mas[search]->data->depositor,date,3)!=0){
				    		search++;
				    		break;
						}
					}
					while(1);
				    
					search_start=search;
					
					do{
						search++;
						if(search==N){
							search--;
							break;
						}
						if(strncmp(mas[search]->data->depositor,date,3)!=0){
				    		break;
						}
					}
					while(1);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " - "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout <<i<<" "<< mas[i]->data->depositor << "\t" << mas[i]->data->deposit << "\t" << mas[i]->data->date
						<< "\t"<< mas[i]->data->lawyer << endl;
				        W[i] = rand() % 99 + 1;
					}
					A2(search_start, search,mas);
                    root->h = 1;
                    seth(root);
				}
			}
			break;
		}
		case 4:
		{	
			int count =0;
			char pos[22];
			char *spc = " ";
			SetConsoleCP(1251);
			LR_print(root, count);
			SetConsoleCP(866);
			cout<<endl;
			printf("+------+----------+----------+----------------+\n");
			printf("|%6d| UniqSize |  Height  |   Mid. height  |\n", N);
			printf("+------+----------+----------+----------------+\n");
			printf("|  A2  |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			printf("+------+----------+----------+----------------+\n");
			cout<<endl<< "input element fo find: "<< endl;
			SetConsoleCP(866);
			cin.sync();
			cin.getline(pos,22);
			SetConsoleCP(1251);
			for(int i = strlen(pos); i<21;i++){
				strcat(pos, spc);
			}
			if(strcmp(pos,"0")!=0){
				TreeSearch(root,pos);
			}
			_getch();
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

void CodeBase() {
	FILE *fp, *fcoded;
    fp = fopen("testBase3.dat", "rb");
    fcoded = fopen("BaseCoded.dat", "wb");
	char buffer;
	while (!feof(fp)) {
		fscanf(fp, "%c", &buffer);
		fcompression++;
		for (int i = 0; i < M; i++) {
			if (buffer == (char)(i-128)) {
				for (int j = 0; j < A[i].l; j++) {
					putc(code[i][j], fcoded);
					cfcompression++;
				}
			}
		}
	}
	fclose(fp);
	fclose(fcoded);
}

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nshenon: \n");
	printf("-------------------------------------------------------------------------------\n");
	printf("| num element   | symbol | veroyatnost |           binary code| dlina coda         |\n");
	printf("|               |        |             |                      |                    |\n");
	SetConsoleCP(1251);
	for (int i = 0; i < M && A[i].p != 0; i++)
	{
		printf("|  %12d |    %c   |  %2.6f   | ",i, A[i].a, A[i].q);
		for (int j = 0; j < A[i].l+1; j++)
			printf("%d", code[i][j]);
		for (int j = A[i].l + 1; j < 18; j++)
			printf(" ");
		printf("   |  %7d      |\n", A[i].l+1);
		lgm += A[i].p * A[i].l;
	}	
    printf("________________________________________________\n");
    printf("| entropy      | avarage dlina coda | koof sjatia         |\n");
    printf("|______________|____________________|_____________________|\n");
    printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)sim_f/sim_cf);
    printf("|______________|____________________|_____________________|\n");

    cout << endl << endl << entropy + 1 << " > " << lgm << endl << endl;
    SetConsoleCP(1251);
}

void Code(){
	
	int i,j;
	FILE *f;	
	f=fopen("testBase3.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].l = 0;
		A[i].q = 0;
		A[i].a = (char)(i-128); 
	}
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		A[c+128].p +=1;
		sum++;
	}
	fclose(f);
	printf("\n");
	//���������� �� ���������� ���������� ��������
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < M; i++)  
		{
			if (A[i - 1].p < A[i].p)
			{
				SN_code B = A[i-1];
				A[i-1]=A[i];
				A[i]=B;
				b = true;
			}
		}
	}
	for (i = 0; i < M && A[i].p != 0; i++){
		A[i].p /=sum;
		A[i].q = A[i].p;
		entropy += A[i].p * abs(log(A[i].p) / log(2));
		sym_count++;
	}
	shanon();
}

void code_file() {
	FILE *f, *cf;
	f = fopen("testBase3.dat", "rb");
	cf = fopen("CodeBase.dat", "wb");
	char sim;
	while (!feof(f)) {
		fscanf(f, "%c", &sim);
		sim_f++;
		for (int i = 0; i < M; i++) {
			if (sim == A[i].a) {
				for (int j = 0; j < A[i].l; j++) {
					putc(code[i][j], cf);
					sim_cf++;
				}
			}
		}
	}
	_fcloseall();
}

void shanon(){
	for (int i = 0; i < M && A[i].p!=0; i++)
	{
		A[i].q = A[i - 1].q + A[i].p;
		A[i].l = ceil(-log(A[i].p) / log(2));
	}
	for (int i = 1; i < M && A[i].p!=0; i++)
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

void LR_print(Vertex* p, int& count) {
	if (p != NULL) {
		LR_print(p->Left, count);
		cout << count+1 << ") "<< p->data->depositor << "\t" << p->data->deposit << "\t" << p->data->date << "\t"<< p->data->lawyer << endl;
		count++;
		LR_print(p->Next, count);
		LR_print(p->Right, count);
	}
}

void add_vertex(Vertex *&p, list* mas, int w) {
	if (p == NULL) {
		p = new Vertex;
		p->data = mas->data;
        p->w = w;
		p->Next = NULL;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (strncmp(p->data->depositor,mas->data->depositor,3) == 0) {
		add_vertex(p->Next, mas, w);
	}
	else if (strncmp(p->data->depositor,mas->data->depositor,3)  > 0) {
		add_vertex(p->Left, mas, w);
	}
	else if (strncmp(p->data->depositor,mas->data->depositor,3)  < 0) {
		add_vertex(p->Right, mas, w);
	}
}

void A2(int L, int R, list **mas) {
	int wes = 0, sum = 0;
	int i;
	if (L <= R) {
		for (i = L; i <= R; i++) {
			wes = wes + W[i];
		}
		for (i = L; i < R; i++) {
			if ((sum < (wes / 2)) && (sum + W[i]) > (wes / 2)) {
				break;
			}
			sum = sum + W[i];
		}
		//cout << L << " - " << R << " - " << wes << " - " << i  << " - " << W[i] << endl;
		add_vertex(root, mas[i], W[i]);
		A2(L, i - 1,mas);
		A2(i + 1, R,mas);
	}
}

void TreeSearch(Vertex* p, char* name) {
    if (p != NULL) {
        // Продолжаем поиск в обеих ветвях, так как совпадение может быть в любой из них
        TreeSearch(p->Left, name);

        // Сравниваем по полю Position
        int comparison = strcmp(p->data->lawyer, name);

        // Если нашли совпадение, выводим информацию
        if (comparison == 0) {
            cout << p->data->depositor << "\t" << p->data->deposit << "\t" << p->data->date << "\t"<< p->data->lawyer << endl;
        }

        // Продолжаем поиск в следующем элементе
        TreeSearch(p->Next, name);

        // Продолжаем поиск в правом поддереве
        TreeSearch(p->Right, name);
    }
}









void seth(Vertex *p)
{
	if (p) {
		if (p->Next) {
			p->Next->h = p->h +1;
		}
		if (p->Left) {
			p->Left->h = p->h + 1;
		}
		if (p->Right) {
			p->Right->h = p->h + 1;
		}
		seth(p->Left);
		seth(p->Right);
		seth(p->Next);
	}
}

void Read_base(FILE *fp, list *rbase){
	base *struk = new base();
	fread((base *)struk, sizeof(base), 1, fp);
	rbase->data=struk;
	rbase->prev=NULL;
	rbase->next=NULL;
	
	for (int i = 1; i < N; i++) {
        struk = new base();
        list *rbase_prev;
        fread((base*)struk, sizeof(base), 1, fp);
        rbase_prev = rbase;
        rbase = rbase->next = new list();
        rbase->data = struk;
        rbase->prev = rbase_prev;
        rbase->next = NULL;
    }
}

int BSearch(list **A, char *FIO_prefix) {
    int l = 0, r = N, m = 0;
    while (l < r) {
        m = (l + r) / 2;
        if (strncmp(A[m]->data->depositor, FIO_prefix, 3) == 0) {
            return m;
        }
        if (strncmp(A[m]->data->depositor, FIO_prefix, 3) < 0)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int compare_name(char* a, char* b) {
	char bufferA[30];
	char bufferB[30];
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	//������� ������� ������� �������
	int space_pos_a = strchr(a,' ') - a;
	int space_pos_b = strchr(b,' ') - b;
	
	//����������� ���������� �������� � ������� 3
	int count =4;
	//���� ������������ ������� ������ �������� �������� ������� ������ ��� ���������
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//���������� �������
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//���� ������������ ������� ������ �������� �������� �������
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	//���� ������� ���������, ��...
	//������� ������� ������� �������
	strcpy(bufferA, a);
	strcpy(bufferB, b);
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;
	//���� ������������ ����� ������ �������� �������� ������� ������ ��� ���������
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//���������� �����
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//���� ������������ ����� ������ �������� �������� �������
	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	
	//���� ����� ���������, ��...
	//������� ������� �������� �������
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;
	//���� ������������ �������� ������ �������� �������� ������� ������ ��� ���������
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	//���������� ��������
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	//���� ������������ ����� ������ �������� �������� �������
	if(space_pos_a >= space_pos_b){
		return 1;
	}
	return -1;
}


int compare(base *a, base *b) {
    int res = strcmp(a->depositor, b->depositor);
    if (res > 0) {
        return 1;
    } else if (res < 0) {
        return -1;
    } else {
        // Depositors are equal, compare deposits as numbers
        if (a->deposit > b->deposit) {
            return 1;
        } else if (a->deposit < b->deposit) {
            return -1;
        } else {
            return 0;  // Depositors and deposits are equal
        }
    }
}


//������� ������� h1-t1 � h2-t2 � ������� hr-tr
void perseption(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr) {
	if (compare(h1->data, h2->data) < 0) {
		hr = h1;
		h1 = h1->next;
	}
	else {
		hr = h2;
		h2 = h2->next;
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if (compare(h1->data, h2->data) < 0) {
			tr->next = h1;
			h1 = h1->next;
			tr = tr->next;
		}
		else {
			tr->next = h2;
			h2 = h2->next;
			tr = tr->next;
		}
	}
	if (t1->next != h1) {
		tr->next = h1;
		tr = t1;
	}
	else if (t2->next != h2) {
		tr->next = h2;
		tr = t2;
	}
	tr->next = NULL;
}

void quick_sort(list*& head) {
	list* t = new list;
	t->data = NULL;
	t->next = head;
	int k = 1;
	int e = 0;
	list* hp, * tp, * h1, * t1, * h2, * t2, * hr, * tr;
	while (k < 4000) {
		hp = t;
		while (hp != NULL) {
			if (hp->next == NULL) {
				break;
			}
			h1 = hp->next;
			t1 = h1;
			for (int i = 1; i < k; i++) {
				if (t1->next == NULL) {
					break;
				}
				t1 = t1->next;
			}
			if (t1->next == NULL) {
				break;
			}
			h2 = t1->next;
			t2 = h2;
			t1->next = NULL;
			for (int i = 1; i < k; i++) {
				if (t2->next == NULL) {
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
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
			cout << i + 1 << "\t" << Base->data->depositor << "\t" << Base->data->deposit << "\t" << Base->data->date << "\t" << Base->data->lawyer << endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
			Base = Base->next;
		}
	}
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
				cout << i + g << "\t" << Base->data->depositor << "\t" << Base->data->deposit << "\t" << Base->data->date << "\t" << Base->data->lawyer << endl;
				Base = Base->next;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
}

void Print_sort_index_mas(list **mas){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
			cout << i + 1 << "\t" << mas[i]->data->depositor << "\t" << mas[i]->data->deposit << "\t" << mas[i]->data->date << "\t" << mas[i]->data->lawyer << endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
		}
	}
    if(n=='2'){
		i=0;	
		int g=-1;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
				cout << i + g << "\t" << mas[i+g]->data->depositor << "\t" << mas[i+g]->data->deposit << "\t" << mas[i+g]->data->date << "\t" << mas[i+g]->data->lawyer << endl;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}		
}

void copy_base(list *a, list *b) {
	b->prev = NULL;
	b->data = a->data;
	for (int i = 1; i < N; i++) {
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
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->Left) + size(x->Right);
	}
}

int max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int height(Vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->Left), height(x->Right));
	}
}

int sdp(Vertex *x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->Left, l + 1) + sdp(x->Right, l + 1);
	}
}

