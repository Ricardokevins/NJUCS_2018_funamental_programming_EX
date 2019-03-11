#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
using namespace std;

//�������ռ��ֹhash����
namespace xiaxie {
	int hash(char *s) {
		int res = 0;
		for (char *c = s; *c != '\0'; ++c) {
			res = res * 26 + (*c - 'a');
			res = res % 2333;
		}
		return res;
	}
}
//�������ݽṹ����������ʵ��
struct haxibiao {
	char A[40];
	haxibiao *next;
};
//��ʼ�����ò��õ�ȫ�ֱ���
//hash������ļ����������
haxibiao * myhash[2333] = { NULL };
char A[2000] = { '\0' };
//����������
//ת��Сд����
void to_lower(char *s);
//�Լ�д���ַ����ȽϺ���
int mystrlen(char *s);
//�Լ�д���ַ����ȽϺ���
int str_equal(char *s1, char *s2);
//�ж��Ƿ�Ϊ�ַ��ĺ��������ڷָ��
bool isChar(char ch);
//��ҵҪ��Ĳ��뺯��
void ht_insert(char *s);
//�ļ��ļ��غ���
char * jiazaiwenjian(void);
//��ҵҪ��Ĳ�ѯ����
int ht_find(char *s);

int main() 
{
	char *A = jiazaiwenjian();
	to_lower(A);
	ht_insert(A);
	for(int i(0);i<3;i++)
	{
		char s[50];
		cin >> s;
		ht_find(s);
	}
	return 0;
}



void to_lower(char *s) {
	while (*s != '\0') {
		if ((*s <= 'Z') && (*s >= 'A')) {
			*s = *s - 'A' + 'a';
		}
		s++;
	}
}

int mystrlen(char *s) {
	int num(0);
	while (*s != '\0') {
		num++;
		s++;
	}
	return num;
}

int str_equal(char *s1, char *s2) {
	int flag = 1;
	int num1 = mystrlen(s1);
	int num2 = mystrlen(s2);
	int min(0);
	if (num1 != num2) {
		flag = 0;
		return flag;
	}
	while (*s1 != '\0') {
		if (*s1 != *s2) {
			flag = 0;
			break;
		}
		s1++;
		s2++;
	}
	return flag;

}

bool isChar(char ch)
{
	if ((ch >= 'a' && ch <= 'z')
		|| ch >= 'A' && ch <= 'Z')
		return true;
	else
		return false;
}

void ht_insert(char *s)
{
	int i(0);
	while (s[i] != '\0')
	{
		char C[40];
		for (int j(0); isChar(s[i]); i++, j++)
		{
			C[j] = s[i];
			C[j + 1] = '\0';
		}
		to_lower(C);
		int hashnum = xiaxie::hash(C);
		if (myhash[hashnum] == NULL)
		{
			haxibiao *head = (haxibiao *)malloc(sizeof(haxibiao));
			for (int q(0); C[q] != '\0'; q++)
			{
				head->A[q] = C[q];
				head->A[q + 1] = '\0';
			}
			head->next = NULL;
			myhash[hashnum] = head;

		}
		else
		{
			haxibiao *current = myhash[hashnum];
			while (current->next)
			{
				current = current->next;
			}
			haxibiao * nowuse = (haxibiao *)malloc(sizeof(haxibiao));
			for (int q(0); C[q] != '\0'; q++)
			{
				nowuse->A[q] = C[q];
				nowuse->A[q + 1] = '\0';
			}
			nowuse->next = NULL;
			current->next = nowuse;
		}
		i++;
	}
} 

char * jiazaiwenjian(void) {
	ifstream fin;
	fin.open("article.txt");
	if (!fin.good()) {
		return 0;
	}
	fin.getline(A, 2500);
	return A;
}

int ht_find(char *s) {
	to_lower(s);
	int num = xiaxie::hash(s);
	if (myhash[num] == NULL)
	{
		cout << "False" << endl;
		return 0;
	}
	else
	{
		haxibiao *temp = myhash[num];
		int flag(0);
		while (temp != NULL)
		{
			if (str_equal(s, temp->A))
			{
				flag = 1;
				cout << "True" << endl;
				return 1;
			}
			temp = temp->next;
			
		}
		if (flag == 0)
		{
			cout << "False" << endl;
		}
	}
	return 1;
}







