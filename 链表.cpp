#include<iostream>
#include<cstdlib>
#define N 5
using namespace std;
struct Node {
	int data;
	Node* next;
};
Node* chuangjian(Node*head) {
	Node*p=(Node *)malloc(sizeof(Node));
	p->next=NULL;
	head=p;
	cin>>p->data;
	for(int i(0); i<N; i++) {
		Node*q=(Node *)malloc(sizeof(Node));
		cin>>q->data;
		q->next=NULL;
		p->next=q;
		p=q;
	}
	return head;
}
Node *charu(Node*head,int num) {
	Node* current=head;
	for(int i(1); i<num; i++) {
		current=current->next;
	}
	Node *newnode=(Node*)malloc(sizeof(Node));
	cin>>newnode->data;
	newnode->next=current->next;
	current->next=newnode;
	return head;
}
void bianlishuchu(Node *head) {
	Node *current=head;
	while (current!=NULL) {
		cout<<current->data<<'\t';
		current=current->next;
	}
}
Node *shanchu(Node *head,int num) {
	Node *current=head;
	Node *pre=NULL;
	if(num==1) {
		head=head->next;
	}
	else {
		for(int i(1); i<num; i++) {
			pre=current;
			current=current->next;
		}
		pre->next=current->next;
		free(current);
	}
	return head;
}
void jieshu(Node *head)
{
	Node*current=head;
	while(current!=NULL)
	{
		current=head->next;
		free(head);
		head=current;
	}
}
int sum(int B[][10], int num) {
	/*	int mysum(0);
		for (int i(0); i < num; i++)
		{
			for (int j(0); j < 10; j++)
			{
				mysum += B[i][j];
			}
		}
		return mysum;
		*/


}
int main() {
	/*
	int A[2][10];
	for (int i(0); i < 2; i++)
	{
		for (int j(0); j < 10; j++)
		{
			A[i][j] = 2;
		}

	}
	cout << sum(A, 2);
	return 0;
	*/
	Node *head=NULL;
	head=chuangjian(head);
	bianlishuchu(head);
	cout<<endl;
	charu(head,1);
	bianlishuchu(head);
	cout<<endl;
	head=shanchu(head,1);
	bianlishuchu(head);
	
	return 0;


}


#include<iostream>
#include<cstdlib>
using namespace std;
struct hehe{
	int data;
	hehe *next;
};
struct Node{
	int data;
	Node * next;
};
//���뽨��β������
hehe * wbcr(hehe * p)
{
	hehe *head = p;
	for (int i(0); i < 5; i++)
	{
		hehe *s = (hehe *)malloc(sizeof(hehe));
		head->next = s;
		cin >> s->data;
		s->next = NULL;
		head = s;
	}
	return p;
}
//���뽨��ͷ������
hehe *tbcr(hehe *p)
{
	hehe *head = p;
	for (int i(0); i < 5; i++)
	{
		hehe *s = (hehe *)malloc(sizeof(hehe));
		s->next = head;
		head = s;
		cin >> s->data;
	}
	return head;
}
void PrintList(hehe * p)
{
	if (!p) //����ǿ�����
		printf("List is empty. \n");
	else
	{
		while (p) //���������ȼ���while(head != NULL)
		{
			cout<<p->data<<" ";
			p = p->next;
		}
		printf("\n");
	}
}
int  main()
{
	/*struct HHH{
		int data;
		int date;
		HHH *hhh;
	}a,*psd;
	cin >> a.data;
	cin >> a.date;
	a.hhh = &a;
	psd = &a;
	cout << a.hhh->data ;
	cout << psd->date;
	struct hehe{
		int data;
		hehe *next;
	};
	for (int i(0); i < 10; i++)
	{
		
	}
	return 0;
	*/
	hehe *head = (hehe *)malloc(sizeof(hehe));
	cin >> head->data;
	head->next = NULL; 
	hehe *newhead=tbcr(head);
	PrintList(newhead);
	return 0;


//���뽨������
#define N 10
Node *AppCreate( )
{ Node *head = NULL, *tail = NULL;
for(int i = 0; i < N; i++)
{ Node *p = (Node *)malloc(sizeof(Node)); //�����½ڵ�
p -> data = i; //���½ڵ�����ݳ�Ա����ֵ
p -> next = NULL; //���½ڵ��ָ���Ա��ֵ
if(head == NULL) //��������Ϊ����������
head = p;
else //���������յ����
tail -> next = p;
tail = p;
}

}



void DeleteList(Node *head)
{
	 while(head)
//�����������д��while(head -> next)����ɾ��β�ڵ㣡��
{ Node *current = head;
head = head -> next;
free(current);
}
}




//�õ������β��
Node *gettailer(Node*head)
{
	Node *tailer = NULL;
	while (head)
	{
		tailer = head;
		head = head->next;
	}
	return tailer;
}

