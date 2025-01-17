/*使用max_min算法*/
#include "Einstein.h"
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<fstream>
#include<ctime>
using namespace std;

int status(0);
double runtime(0.0);
clock_t mystart;
clock_t myend;

#define supermax 1000
#define supermin -1000


struct chesser {
	int hpos;
	int lpos;
	int chess_id;
	double at_val;
	double def_val;
	double dis_val;
	double thr_val;
	double pro_val;
	double self_val;
};

struct Node {
	int val;
	int op_target;//保存的是操作的对象，结合起来就是表示怎么到达这个局面的
	int op;//保存的是哪一个操作
	Node *next;
};

vector<chesser> All_chess;
int mychessboard[5][5];
int prechessboard[5][5];
int bluechess_num;
int redchess_num;
int mypos;//表示我是蓝方还是红方，1是蓝方，0是红方

bool comp(const chesser&a,const chesser&b)
{
	return a.chess_id < b.chess_id;
}

vector<string> command_split(const string &s, const string &seperator)
{
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;
	while (i != s.size())
	{
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0)
		{
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

Einstein::Einstein()
{
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

int count_pos(chesser &A)
{
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (mychessboard[i][j] == A.chess_id)
			{
				A.hpos = i;
				A.lpos = j;
				return 1;
			}
		}
	}
	return 0;
}

int count_dis(int i,vector<chesser>&A)
{
	int dis(0);
	if (A[i].chess_id > 6)
	{
		if (A[i].hpos > A[i].lpos)
		{
			dis = A[i].hpos;
		}
		else
		{
			dis = A[i].lpos;
		}
		return dis;
	}
	else
	{
		if (A[i].hpos < A[i].lpos)
		{
			dis = A[i].hpos;
		}
		else
		{
			dis = A[i].lpos;
		}
		return 4 - dis;
	}
}

int count_num(vector<chesser>&A)
{
	bluechess_num = 0;
	redchess_num = 0;
	for (int i(0); i < A.size(); i++)
	{
		if (A[i].chess_id > 6)
		{
			bluechess_num++;
		}
		else
		{
			redchess_num++;
		}
	}
	return 0;
}

double count_self(int i,vector<chesser>&A)
{
	if (A[i].chess_id > 6)
	{
		if (A[i].hpos == 4 && A[i].lpos == 4)
		{
			return 0;
		}
		/*
		if (A[i].hpos == 0 || A[i].lpos == 0)
		{
			return (5 * (2 ^ (2 - count_dis(i,A))));
		}
		*/
		else
		{
			return (2 ^ (4 - count_dis(i,A)));
		}
	}
	else
	{
		if (A[i].hpos == 0 &&A[i].lpos == 0)
		{
			return 0;
		}
		
		/*if (A[i].hpos == 4 || A[i].lpos == 4)
		{
			return (5 * (2 ^ (2 - count_dis(i,A))));
		}
		*/
		else
		{
			return (2 ^ (4 - count_dis(i,A)));
		}
	}
	return 0;
}

double count_pro(int i,vector<chesser>&A)
{
	int  count(0);
	count_num(A);
	if (A[i].chess_id > 6)//如果是蓝方的棋子，那么就要考虑6和最大的界限
	{
		if (i != A.size() - 1)
		{
			count += A[i + 1].chess_id - 1 - A[i].chess_id;//向后找，如果只是相邻的自然就是0
		}
		if (i>0&&A[i - 1].chess_id > 6)//也不是第一个棋子,使用逻辑短路避免一些问题
		{
			count += A[i].chess_id - A[i - 1].chess_id-1;//这么一减就知道中间有多少的棋子被吃了，可以更好的计算期望
		}
	}
	else
	{
		if (i != 0)
		{
			count += A[i].chess_id - 1 - A[i-1].chess_id;//向前找，如果只是相邻的自然就是0
		}
		if ( i < A.size()-1 && A[i +1].chess_id < 6)//也不是第一个棋子,使用逻辑短路避免一些问题
		{
			count += A[i+1].chess_id - A[i].chess_id - 1;//这么一减就知道中间有多少的棋子被吃了，可以更好的计算期望
		}
	}
	A[i].pro_val = (1.0 / 6.0)*(count + 1);
	return A[i].pro_val;
}

double count_attack(int i,vector<chesser> &A)
{
	return count_pro(i,A)*count_self(i,A);
}

double count_defend(int i,vector<chesser>&A)
{
	return -count_attack(i,A);
}

int intial_chessboard()
{
	All_chess.clear();
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (mychessboard[i][j] != 0)
			{
				chesser temp;
				temp.chess_id = mychessboard[i][j];
				temp.hpos = i;
				temp.lpos = j;
				All_chess.push_back(temp);
			}
		}
	}
	return 0;

}

int record_pre()
{
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			prechessboard[i][j] = mychessboard[i][j];
		}
	}
	return 0;
}

int count_dif()
{
	int num(0);
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (prechessboard[i][j] != mychessboard[i][j])
			{
				num++;
			}
		}
	}
	return num;
}

double count_total_val(vector<chesser>&A)
{
	double value(0.0);
	double attack_total(0.0);
	double defend_total(0.0);
	for (int i(0); i < All_chess.size(); i++)
	{
		
		if (All_chess[i].chess_id > 6)
		{
			if (mypos == 1)
			{
				attack_total += count_attack(i,A);
			}
			else
			{
				defend_total += count_defend(i,A);
			}
		}
		else
		{
			if (mypos == 0)
			{
				attack_total += count_attack(i,A);
			}
			else
			{
				defend_total += count_defend(i,A);
			}
		}	
	}
	value = 100*attack_total + 0.1*defend_total;
	return value;
}

int find_nearest(int mydice)
{
	int pos(All_chess.size()-1);
	for (int i(0); i < All_chess.size(); i++)
	{
		if (All_chess[i].chess_id > 6)
		{
			pos = i;
			break;
		}
	}
	if (mydice > 6)
	{
		for (int i(pos); i < All_chess.size(); i++)
		{
			if (All_chess[i].chess_id >= mydice)
			{
				return i;
			}
		}
		return All_chess.size() - 1;
	}
	else
	{
		for (int i(pos - 1); i >= 0; i--)
		{
			if (All_chess[i].chess_id <= mydice)
			{
				return i;
			}
		}
		return 0;
	}

}

int check_board(int col, int line,int op,int side)//col是列数line是行数
{
	if (side == 0)
	{
		if (op == 0&&col+1>4)
		{
			return 0;
		}
		if (op == 1)
		{
			if (col + 1 > 4 || line + 1 > 4)
			{
				return 0;
			}
		}
		if (op == 2&&line+1>4)
		{
			return 0;
		}
		return 1;
	}
	if (side == 1)
	{
		if (op == 0 && col - 1 < 0)
		{
			return 0;
		}
		if (op == 1)
		{
			if (col - 1 < 0 || line - 1 <0 )
			{
				return 0;
			}
		}
		if (op == 2 && line - 1 < 0)
		{
			return 0;
		}
		return 1;
	}
	return 0;
}

int check_win(vector<chesser>& B)
{
	count_num(B);
	for (int i(0); i < B.size(); i++)
	{
		if (B[i].hpos == 0 && B[i].lpos == 0 && B[i].chess_id > 6)
		{
			return 1;
		}
		if (B[i].hpos == 4 && B[i].lpos == 4 && B[i].chess_id <= 6)
		{
			return 2;
		}
	}
	if (bluechess_num == 0)
		return 1;
	if (redchess_num == 0)
		return 2;
	return 0;
}

int print_chessboard()
{
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			cout << setw(3) << mychessboard[i][j] << "  ";
		}
		cout << endl;
	}
	return 1;
}

int gen_op(vector<int> &A,vector<chesser>&B,int pos)
{
	count_num(B);
	if (pos == 1)//假如我是蓝方，做出决策
	{
		for (int j(0); j < bluechess_num-1; j++)
		{
			for (int i(0); i < 3; i++)
			{
				if (check_board(B[redchess_num + j+1].lpos, B[redchess_num + j+1].hpos, i, 1))
				{
					A.push_back(redchess_num + j);
					A.push_back(i);
				}
			}
		}
	}
	if (pos == 0)//假如我是红方，做出决策
	{
		for (int j(0); j < redchess_num; j++)
		{
			for (int i(0); i < 3; i++)
			{
				if (check_board(B[j].lpos, B[j].hpos, i, 0))
				{
					A.push_back(j);
					A.push_back(i);
				}
			}
		}
	}
	return 0;
}

double max_min(int player,int depth,vector<chesser>&A)//player=0代表是我着手下棋
{
	if (depth == 0||check_win(A))
		return count_total_val(A);
	vector<int>All_op;
	gen_op(All_op, A,player);
	int temp_max = supermax;
	int temp_min = supermin;
	for (int j(0); j< (All_op.size()/2); j++)
	{
		int op_target(0);
		int op(0);
		op_target = All_op[j * 2];
		op = All_op[j * 2 + 1];
		if (op == 0)
		{
			if (player == 0 )//是我下棋
			{
				if (mypos == 0)//我是红方
				{
					A[op_target].lpos += 1;
					int i1(0);
					chesser I;
					int eat(0);
					for (; i1 < A.size(); i1++)
					{
						if (A[i1].hpos == A[op_target].hpos&&A[i1].lpos == A[op_target].lpos&&op_target != i1)//判断是否有吃掉对手
						{
							I = A[i1];
							A.erase(A.begin() + i1);
							eat = 1;
							break;
						}
					}
					int temp_num(0);
					temp_num = max_min(1, depth - 1, A);
					if (temp_num > temp_min)
					{
						temp_min = temp_num;
					}
					if (eat)
					{
						
						A.insert(A.begin() + i1, I);
					}				
					A[op_target].lpos -= 1;
				}
				else
				{
					A[op_target].lpos -= 1;
					chesser I;
					int eat(0);
					int i(0);
					for (; i < A.size(); i++)
					{
						if (A[i].hpos == A[op_target].hpos&&A[i].lpos == A[op_target].lpos&&op_target != i)//判断是否有吃掉对手
						{
							I = A[i];
							eat = 1;
							A.erase(A.begin() + i);
							break;
						}
					}
					int temp_num = max_min(1, depth - 1, A);
					if (temp_num > temp_min)
					{
						temp_min = temp_num;
					}
					
					if (eat)
					{
						
						A.insert(A.begin() + i, I);
					}
					A[op_target].lpos += 1;
				}				
			}
			else
			{
				if (mypos == 0)//我是红方，那么对手就是蓝方
				{
					chesser I;
					int eat(0);
					int i2(0);
					A[op_target].lpos -= 1;
					for (; i2 < A.size(); i2++)
					{
						if (A[i2].hpos == A[op_target].hpos&&A[i2].lpos == A[op_target].lpos&&op_target != i2)//判断是否有吃掉对手
						{
							I = A[i2];
							A.erase(A.begin() + i2);
							eat = 1;
							break;
						}
					}
					int temp_num(0);
					temp_num = max_min(0, depth - 1, A);
					if (temp_num < temp_max)
					{
						temp_max = temp_num;
					}
					if (eat)
					{
						
						A.insert(A.begin() + i2, I);
					}
					A[op_target].lpos += 1;
				}
				else
				{
					chesser I;
					A[op_target].lpos += 1;
					int eat(0);
					int i(0);
					for (; i < A.size(); i++)
					{
						if (A[i].hpos == A[op_target].hpos&&A[i].lpos == A[op_target].lpos&&op_target != i)//判断是否有吃掉对手
						{
							I = A[i];
							A.erase(A.begin() + i);
							eat = 1;
							break;
						}
					}
					int temp_num(0);
					temp_num = max_min(0, depth - 1, A);
					if (temp_num < temp_max)
					{
						temp_max = temp_num;
					}
					if (eat)
					{
						
						A.insert(A.begin() + i, I);
					}
					A[op_target].lpos -= 1;
				}
			}
		}
		else
		{
			if (op == 1)
			{
				if (player == 0)//是我下棋
				{
					if (mypos == 0)//我是红方
					{
						chesser I;
						int eat(0);
						A[op_target].lpos += 1;
						A[op_target].hpos += 1;
						int i3(0);
						for (; i3 < A.size(); i3++)
						{
							if (A[i3].hpos == A[op_target].hpos&&A[i3].lpos == A[op_target].lpos&&op_target != i3)//判断是否有吃掉对手
							{
								I = A[i3];
								A.erase(A.begin() + i3);
								eat = 1;
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(1, depth - 1, A);
						if (temp_num > temp_min)
						{
							temp_min = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i3, I);
						}
						A[op_target].lpos -= 1;
						A[op_target].hpos -= 1;
					}
					else
					{
						A[op_target].lpos -= 1;
						A[op_target].hpos -= 1;
						int i4(0);
						int eat(0);
						chesser I;
						for (; i4 < A.size(); i4++)
						{
							if (A[i4].hpos == A[op_target].hpos&&A[i4].lpos == A[op_target].lpos&&op_target != i4)//判断是否有吃掉对手
							{
								I = A[i4];
								A.erase(A.begin() + i4);
								eat = 1;
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(1, depth - 1, A);
						if (temp_num > temp_min)
						{
							temp_min = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i4, I);
						}
						A[op_target].lpos += 1;
						A[op_target].hpos += 1;
					}
				}
				else
				{
					if (mypos == 0)//我是红方，那么对手就是蓝方
					{
						int i5(0);
						chesser I;
						int eat(0);
						A[op_target].lpos -= 1;
						A[op_target].hpos -= 1;
						for (; i5 < A.size(); i5++)
						{
							if (A[i5].hpos == A[op_target].hpos&&A[i5].lpos == A[op_target].lpos&&op_target != i5)//判断是否有吃掉对手
							{
								I = A[i5];
								eat = 1;
								A.erase(A.begin() + i5);
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(0, depth - 1, A);
						if (temp_num < temp_max)
						{
							temp_max = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i5, I);
						}
						A[op_target].lpos += 1;
						A[op_target].hpos += 1;
					}
					else
					{
						int i6(0);
						chesser I;
						int eat(0);
						A[op_target].lpos += 1;
						A[op_target].hpos += 1;
						for (; i6< A.size(); i6++)
						{
							if (A[i6].hpos == A[op_target].hpos&&A[i6].lpos == A[op_target].lpos&&op_target != i6)//判断是否有吃掉对手
							{
								I = A[i6];
								A.erase(A.begin() + i6);
								eat = 1;
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(0, depth - 1, A);
						if (temp_num < temp_max)
						{
							temp_max = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i6, I);
						}
						A[op_target].lpos -= 1;
						A[op_target].hpos -= 1;
					}
				}
			}
			else
			{
				if (player == 0)//是我下棋
				{
					if (mypos == 0)//我是红方
					{
						int i7(0);
						chesser I;
						int eat(0);
						A[op_target].hpos += 1;
						for (; i7 < A.size(); i7++)
						{
							if (A[i7].hpos == A[op_target].hpos&&A[i7].lpos == A[op_target].lpos&&op_target != i7)//判断是否有吃掉对手
							{
								I = A[i7];
								A.erase(A.begin() + i7);
								eat = 1;
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(1, depth - 1, A);
						if (temp_num > temp_min)
						{
							temp_min = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i7, I);
						}
						A[op_target].hpos -= 1;
					}
					else
					{
						int i8(0);
						chesser I;
						int eat(0);
						A[op_target].hpos -= 1;
						for (; i8 < A.size(); i8++)
						{
							if (A[i8].hpos == A[op_target].hpos&&A[i8].lpos == A[op_target].lpos&&op_target != i8)//判断是否有吃掉对手
							{
								I = A[i8];
								eat = 1;
								A.erase(A.begin() + i8);
								break;
							}
						}
 						int temp_num(0);
						temp_num = max_min(1, depth - 1, A);
						if (temp_num > temp_min)
						{
							temp_min = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i8, I);
						}
						A[op_target].hpos += 1;
					}
				}
				else
				{
					if (mypos == 0)//我是红方，那么对手就是蓝方
					{
						int i9(0);
						int eat(0);
						chesser I;
						A[op_target].hpos -= 1;
						for (; i9 < A.size(); i9++)
						{
							if (A[i9].hpos == A[op_target].hpos&&A[i9].lpos == A[op_target].lpos&&op_target != i9)//判断是否有吃掉对手
							{
								I = A[i9];
								eat = 1;
								A.erase(A.begin() + i9);
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(0, depth - 1, A);
						if (temp_num < temp_max)
						{
							temp_max = temp_num;
						}
						if (eat)
						{
							
							A.insert(A.begin() + i9, I);
						}
						A[op_target].hpos += 1;
					}
					else
					{
						int eat(0);
						int i10(0);
						chesser I;
						A[op_target].hpos += 1;
						for (; i10 < A.size(); i10++)
						{
							if (A[i10].hpos == A[op_target].hpos&&A[i10].lpos == A[op_target].lpos&&op_target != i10)//判断是否有吃掉对手
							{
								eat = 1;
								I = A[i10];
								A.erase(A.begin() + i10);
								break;
							}
						}
						int temp_num(0);
						temp_num = max_min(0, depth - 1, A);
						if (temp_num < temp_max)
						{
							temp_max = temp_num;
						}
						if (eat)
						{							
							A.insert(A.begin() + i10, I);
						}
						A[op_target].hpos -= 1;
					}
				}
			}
		}
	}
	if (player == 0)
	{
		return temp_min;
	}
	else
		return temp_max;
}

int Einstein::handle()
{
	
	int dif_num(0);
	clientsocket.recvMsg();
	string s = clientsocket.getRecvMsg();
	if(s.size()==0)
	{
		return 0;
	}
	parse(s);
	if (dice > 6)
	{
		mypos = 1;
	}
	else
		mypos = 0;
	intial_chessboard();
	dif_num = count_dif();
	cout << "count_dif" << endl;
	if (dif_num > 4)
	{
		status++;
		if (status % 2 == 0)
		{
			myend = clock();
			string temp_a = "game over!";
			cout << "game over!  " << endl << endl;
			if (check_win(All_chess) == 2)
			{
				temp_a += "blue win!   ";
				cout << "blue win!   ";
			}
			else
			{
				temp_a += "red win!   ";
				cout << "red win!   ";
			}
			runtime = (double)(myend - mystart) / CLOCKS_PER_SEC;
			stringstream la;
			la << runtime;
			string hrhr;
			la >> hrhr;
			temp_a += hrhr;
			logger.push_back(temp_a);
			cout << "using time： " << runtime / 1000 << endl;
		}
		else
		{
			mystart = clock();
		}
	}
	record_pre();
	print_chessboard();
	sort(All_chess.begin(), All_chess.end(), comp);
	for (int i(0); i < All_chess.size(); i++)
	{
		count_pos(All_chess[i]);
	}
	int target = find_nearest(dice);
	string temp;
	temp = to_string(All_chess[target].chess_id);
	string op; 
	op = temp + "|";
	vector<int>mytemp;
	int profit_pos(0);
	int now_profit(-1000);
	for (int i(0); i < 3; i++)
	{
		if (check_board(All_chess[target].lpos, All_chess[target].hpos, i, mypos))
		{
			int heheha = max_min(0, 3, All_chess);
			cout << target << endl;
			sort(All_chess.begin(), All_chess.end(), comp);
			for (int s(0); s < All_chess.size(); s++)
			{
				cout << All_chess[s].chess_id << " ";
			}
			cout << endl;
			cout<<"operate target      "<< All_chess[target].chess_id <<"    "<< i << "        profit" << heheha << endl;
			if (heheha> now_profit)
			{
				profit_pos = i;
				now_profit = heheha;
			}
		}
	}
	if (profit_pos == 0)
	{
		if (mypos == 1)
		{
			op += "left";
		}
		else
		{
			op += "right";
		}
	}
	if (profit_pos == 1)
	{
		if (mypos == 1)
		{
			op += "leftup";
		}
		else
		{
			op += "rightdown";
		}
	}
	if (profit_pos == 2)
	{
		if (mypos == 1)
		{
			op += "up";
		}
		else
		{
			op += "down";
		}
	}
	cout << "cal_op success      " << op << endl;
	const char *hehe = op.c_str();
	clientsocket.sendMsg(hehe);
	string log_infor = s + "   operation" + op;
	logging(log_infor);
	return 1;
}

int Einstein::parse(std::string A)
{
	A.erase(A.begin());
	int flag_pos(0);
	for (int i(0); i < A.size(); i++)
	{
		if (A[i] == '|')
		{
			flag_pos = i;
			break;
		}
	}
	std::string mydice;
	for (int i(flag_pos+1); i < A.size(); i++)
	{
		mydice.push_back(A[i]);
	}
	stringstream ss;
	ss << mydice;
	ss >> dice;
	vector<string> temp;
	for (int i(A.size() - 1); i >= flag_pos; i--)
	{
		A.pop_back();
	}
	A.pop_back();
	temp = command_split(A, " ");
	for (int i(0); i < temp.size(); i++)
	{
		for (int j(0); j < temp[i].size();)
		{
			int s = temp[i].size();
			if (temp[i][j] == '[' || temp[i][j] == ']' || temp[i][j] == ',' || temp[i][j] == ' ')
			{
				temp[i].erase(temp[i].begin() + j);
			}
			else
				j++;
		}
	}
	for (int i(0); i < 25; i++)
	{
		stringstream sa;
		sa << temp[i];
		sa >> chessboard[i];
	}
	int num(0);
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			mychessboard[i][j] = chessboard[num];
			num++;
		}
	}
	return 0;
}

int Einstein::logging(std::string s)
{
	time_t t = time(NULL);
	tm *tp = localtime(&t);
	stringstream myyear;
	string myyears;
	stringstream mymonth;
	string mymonths;
	stringstream myday;
	string mydays;
	stringstream myhour;
	string myhours;
	stringstream mymin;
	string mymins;
	stringstream mysecond;
	string myseconds;
	myyear << tp->tm_year + 1900;
	myyear >> myyears;
	mymonth << tp->tm_mon + 1;
	mymonth >> mymonths;
	myday << tp->tm_mday;
	myday >> mydays;
	myhour << tp->tm_hour;
	myhour >> myhours;
	mymin << tp->tm_min;
	mymin >> mymins;
	mysecond << tp->tm_sec;
	mysecond >> myseconds;
	string time_infor;
	time_infor = myyears + "-"+mymonths +"-"+ mydays + "-"+myhours + "-"+ mymins + "-" + myseconds+":";
	logger.push_back(time_infor);
	logger.push_back(s);
	cout << time_infor << endl;
	cout << s << endl;
	return 1;
}

int Einstein::writelog()
{
	time_t t = time(NULL);
	tm *tp = localtime(&t);
	stringstream myyear;
	string myyears;
	stringstream mymonth;
	string mymonths;
	stringstream myday;
	string mydays;
	stringstream myhour;
	string myhours;
	stringstream mymin;
	string mymins;
	stringstream mysecond;
	string myseconds;
	myyear << tp->tm_year + 1900;
	myyear >> myyears;
	mymonth << tp->tm_mon + 1;
	mymonth >> mymonths;
	myday << tp->tm_mday;
	myday >> mydays;
	myhour << tp->tm_hour;
	myhour >> myhours;
	mymin << tp->tm_min;
	mymin >> mymins;
	mysecond << tp->tm_sec;
	mysecond >> myseconds;
	string myID = "181860077";
	string finalpath;
	finalpath = myyears + "-"+mymonths + "-" + mydays + "-" + myID+".log";
	ofstream outfile(finalpath, ios::app);
	if (!outfile)
	{
		cout << "文件打开失败" << endl;
		return 1;
	}
	list<string>:: iterator w;
	for(w = logger.begin(); w != logger.end(); ++w)
	{
		outfile << *w << endl;
	}
	return 0;
}
