#include <iostream> 
#include <cstdio>
using namespace std;

int NubmerLev = 0;//���������� � ������� ����� ��������� ����� ������

int LoadLevel(){

	FILE* in = freopen("input" , "r", stdin); 	
	
	int level;
	cin >> level;
FILE* out = freopen("input" , "w+", stdout);
	if ( level > NubmerLev ){
		NubmerLev = level;	
	cout << NubmerLev;
	}

	return 0;
	//return NubmerLev;
}

int UpdateLevel(int NubmerLev){

	FILE* out = freopen("input" , "w+", stdout);
		
	cout << NubmerLev;

	
	return 0;
	return NubmerLev;
}

/*�� ������� ��������� ����� �������� ���������� ��� �������� ����������� ������ �� ������ �� ����*/
void main()
{
	LoadLevel();
	//UpdateLevel(2);
	
}