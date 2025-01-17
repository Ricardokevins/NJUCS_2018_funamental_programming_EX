#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <functional>
#include <conio.h>
#include<cstring> 
#include <stdio.h>
#include<string>
#include<cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include<iomanip>
#include <winbase.h>
//#include <stdlib.h>
using namespace std;
class song {//打算是在用一个类的数组来保存很多的歌曲对象实体
public:
	string songname;//歌的名字
	string pinyin;
	string singername;//歌手的名
	int serialnum;//序列号，就是在歌单里的序列
	int ranknum;//排行的位置
	int playstatus;//是否处于播放状态
	int playfrequence;
	int judgefrequence;//播放的次数，作为计算的根据
	double totalscore;//总分，也是计算的根据
	double starnum;//评分数
};

class admin
{
public:
	admin();

	friend class ktvsystem;

	friend class user;

	vector<song> mysong;

	int changepassword();//这两个返回值都是表示状态，改成功和登陆成功

	int login();//登陆函数

	int add_song();//加歌

	int delete_song();//删除歌曲，成功返回1

	int file_in();//加载外面文件的歌曲，加载成功就返回1

	int file_out();//导出文件

	int sort_song();//对歌曲排序

	int admenu();//显示管理员的专用界面，并接受输入的操作值

	int initialsong(song &temp);

	int printall(vector<song>&A);

	int printsong(song &temp);

	int legalID(string A);

	int legalpassword(string B);

	int realprintall();

private:
	string ID;
	string password;//保存密码
};

class user {
public:
	//user();
	friend class ktvsystem;

	friend class admin;

	int usmenu(admin &A);//显示用户界面并返回操作值

	int ordersong(admin &A);//点歌

	int see_playingqueue(admin &A);//查看待播放队列里歌曲

	int make_song_top(admin &A);//置顶

	int change_song(admin &A);//切歌

	int delete_song_inqueue(admin & A);//删除播放队列中的歌

	int judge_song(admin& A);//评分

	int realsee_playingqueue(admin &A);

	int search_song(admin &A);

private:
	//int usopnum;//操作值
	vector<int>playing_queue;//正在播放的队列，保存所有的播放的歌曲
};

class ktvsystem {
public:
	admin A;
	user B;
	int pmainmenu();
	int initialsys();
	void run();
private:
	int syoperationnum;//system的操作代码
};

bool comp_srerial(const song&A, const song&B)
{
	return A.serialnum < B.serialnum;
}

bool comp_starnum(const song&A, const song &B)
{
	return A.starnum > B.starnum;
}

bool comp_frenum(const song&A, const song &B)
{
	return A.playfrequence > B.playfrequence;
}
#include"alldefine.h"
//备注歌曲的序列号和在数组里面的下标是不一样的

int main()
{
	ktvsystem cursys;
	cursys.run();
	return 0;
}


admin::admin(void)
{
	ID = "NJUCS";
	password = "CSNB12";
}

int admin::admenu()
{
	system("cls");
	system("color f1");
	cout << "\n\n\t\t\t＋==============================＋\n";
	cout << "\t\t\t ｜                            \n";
	cout << "\t\t\t ｜ 1->查看所有的歌曲            \n";
	cout << "\t\t\t ｜ 2->添加歌曲                 \n";
	cout << "\t\t\t ｜ 3->批量的导入歌曲            \n";
	cout << "\t\t\t ｜ 4->批量的导出歌曲            \n";
	cout << "\t\t\t ｜ 5->删除歌曲                  \n";
	cout << "\t\t\t ｜ 6->歌曲排序                  \n";
	cout << "\t\t\t ｜ 7->修改密码                  \n";
	cout << "\t\t\t ｜ 8->退出                     \n";
	cout << "\t\t\t ｜                             \n";
	cout << "\t\t\t＋==============================＋\n";
	rewind(stdin);
	while (1)
	{
		char op;
		int adnumtemp(0);
		rewind(stdin);
		cin >> op;
		rewind(stdin);
		if (op<'0' || op>'8')
		{
			adnumtemp = 100;
		}
		else
		{
			adnumtemp = op - '0';
		}
		switch (adnumtemp)
		{
		case 1:realprintall(); break;
		case 2:add_song(); break;
		case 3:file_in(); break;
		case 4:file_out(); break;
		case 5:delete_song(); break;
		case 6:sort_song(); break;
		case 7:changepassword(); break;
		case 8:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋==============================＋\n";
		cout << "\t\t\t ｜ ｜\n";
		cout << "\t\t\t ｜ 1->查看所有的歌曲  \n";
		cout << "\t\t\t ｜ 2->添加歌曲       \n";
		cout << "\t\t\t ｜ 3->批量的导入歌曲  \n";
		cout << "\t\t\t ｜ 4->批量的导出歌曲 \n";
		cout << "\t\t\t ｜ 5->删除歌曲       \n";
		cout << "\t\t\t ｜ 6->歌曲排序       \n";
		cout << "\t\t\t ｜ 7->修改密码       \n";
		cout << "\t\t\t ｜ 8->退出           \n";
		cout << "\t\t\t ｜                   \n";
		cout << "\t\t\t＋==============================＋\n";
		rewind(stdin);
	}
	return 1;
}

int admin::login()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t｜  *********管理员登陆********  \n");
	printf("\t\t\t｜ 管理员ID：                    \n");
	printf("\t\t\t｜ 管理员密码：                  \n");
	printf("\t\t\t＋==============================＋\n");
	rewind(stdin);

	string IDtemp;
	string passwordtemp;
	int IDlegal(1);
	int passwordlegal(1);
	int boolsuccess(0);
	char  temp = 's';
	int times(0);
	while (!boolsuccess&&times < 3)
	{
		boolsuccess = 1;
		rewind(stdin);
		IDtemp.clear();
		passwordtemp.clear();
		cout << "|********输入你的账号，请注意输入格式********|" << endl;
		while (IDlegal)
		{
			IDlegal = 0;
			temp = 's';
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9'))
				{
					//putchar('*');
					putchar(temp);
					IDtemp += temp;
				}
				else
				{
					if (temp != '\r' && temp != '\n')
					{
						if ((temp & 0xff) == 8)
						{
							if (IDtemp.length() > 0)
							{
								cout << temp << " " << temp;
								IDtemp.pop_back();
							}
							rewind(stdin);
							continue;
						}
						else
						{
							IDlegal = 1;
							cout << '\r';
							cout << "|*******输入了非法字符，请重新输入*******|" << endl;
							rewind(stdin);
							continue;
						}
					}
					else
					{
						IDlegal = 0;
						cout << endl;
					}

				}
			}
			if (IDtemp.length() >= 12)
			{
				cout << "|*******输入过长，请重新输入*******|" << endl;
				IDlegal = 1;
				IDtemp.clear();
				rewind(stdin);
			}
		}
		IDlegal = 1;
		cout << "|*******输入你的密码，请注意输入格式*******|" << endl;
		while (passwordlegal)
		{
			if (passwordlegal == 1)
			{
				passwordtemp.clear();
			}
			rewind(stdin);
			temp = 's';
			passwordlegal = 0;
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if (temp != '\r'&&temp != '\b'&&temp != '\n')
				{
					putchar('*');
					passwordtemp += temp;
				}
				if ((temp & 0xff) == 8)
				{
					if (passwordtemp.length() > 0)
					{
						cout << temp;
						cout << " ";
						cout << temp;
						passwordtemp.pop_back();
					}
					rewind(stdin);
					continue;
				}
			}
			cout << endl;
			if (legalpassword(passwordtemp))
			{
				passwordlegal = 0;
			}
			else
			{
				passwordlegal = 1;
				cout << "|***输入不合法，请重新输入***|" << endl;
			}
		}
		passwordlegal = 1;
		if (IDtemp.length() != ID.length())//先判断长度，不一样就一定是错的
		{
			boolsuccess = 0;
			times++;
			cout << "|***没有这个ID***|" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		if (passwordtemp.length() != password.length())
		{
			boolsuccess = 0;
			times++;
			cout << "|***密码不对吧***|" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		for (int i = 0; i < IDtemp.length(); i++)//接着进行遍历比对
		{
			if (IDtemp[i] != ID[i])
			{
				boolsuccess = 0;
				times++;
				cout << "|***没有这个ID***|" << endl;
				Sleep(1500);
				break;
			}
		}
		for (int i = 0; i < passwordtemp.length(); i++)
		{
			if (passwordtemp[i] != password[i])
			{
				boolsuccess = 0;
				times++;
				cout << "|***密码不对吧***|" << endl;
				break;
			}
		}
		if (times != 3&&boolsuccess==0)
		{
			cout << "你还有" << 3 - times << "次的机会" << endl;
		}
	}
	if (times == 3)
	{
		cout << "|*****你根本就不是管理员，再见！******|" << endl;
		Sleep(1500);
		return 0;
	}
	cout << "小伙子，没想到你也是管理员啊" << endl;
	cout << "正在跳转页面" << endl;
	Sleep(1500);
	admenu();
	return 1;
}

int admin::file_out()
{
	fstream myoperate;
	myoperate.open("ktvsong.txt", ofstream::out);
	if (myoperate.fail())
	{
		cout << "文件导出失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int length(0);
	length = mysong.size();
	for (int i(0); i < length; i++)
	{
		string mysinger;
		mysinger = mysong[i].singername;
		myoperate << mysinger << " ";

		string mysongname;
		mysongname = mysong[i].songname;
		myoperate << mysongname << " ";

		string mypinyin;
		mypinyin = mysong[i].pinyin;
		myoperate << mypinyin << " ";
		myoperate << endl;
	}
	cout << "文件导出成功,返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::file_in()
{
	ifstream infile;
	string filesite;
	int sus(0);
	int fai(0);
	cout << "输入导入的文件名" << endl;
	rewind(stdin);
	cin >> filesite;
	infile.open(filesite);
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int n = mysong.size();
	for (int j(1); !infile.eof(); )
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.judgefrequence = 0;
		temp.playfrequence = 0;
		temp.totalscore = 0;
		if (temp.judgefrequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore / temp.judgefrequence;
		temp.serialnum = j + n;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		int flag = 0;
		for (int i(0); i < mysong.size(); i++)
		{
			if (temp.songname == mysong[i].songname&&temp.singername == mysong[i].singername)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			fai++;
		}
		else
		{
			sus++;
			j++;
			mysong.push_back(temp);
		}
	}
	mysong.pop_back();
	cout << "文件导入成功" << endl;
	cout << "导入成功 " << sus-1 << "首" << "，失败了 " << fai+1 << "首" << endl;
	cout << "正在返回上一级" << endl;
	Sleep(2000);
	return 1;
}

int admin::add_song()
{
	song temp;
	cout << "input singer name" << endl;
	string singer;
	cin >> singer;
	temp.singername = singer;

	cout << "input song name" << endl;
	rewind(stdin);
	string songname;
	cin >> songname;
	temp.songname = songname;

	cout << "input song pinyin" << endl;
	string mypinyin;
	rewind(stdin);
	cin >> mypinyin;
	temp.pinyin = mypinyin;

	int i = mysong.size();
	temp.serialnum = i + 1;
	
	initialsong(temp);
	for (int i(0); i < mysong.size(); i++)
	{
		if (temp.singername == mysong[i].singername&&temp.songname == mysong[i].songname)
		{
			cout << "已经有这一首歌了，即将返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
	}
	mysong.push_back(temp);
	cout << "歌曲添加成功正在返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::delete_song()
{
	cout << "请输入你想删除的歌曲的编号" << endl;
	int serielnumber;
	cin >> serielnumber;
	if (serielnumber<1 || serielnumber>mysong.size())
	{
		cout << "输入不合法，即将返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	for (int i(0); i < mysong.size(); i++)
	{
		if (mysong[i].serialnum == serielnumber)
		{
			mysong.erase(mysong.begin()+i);
		}
	}
	for (int i(0); i < mysong.size(); i++)
	{
		mysong[i].serialnum=i+1;
	}
	cout << "删除成功！！！" << endl;
	Sleep(2000);
	return 1;
}

int admin::initialsong(song&temp)
{
	temp.judgefrequence = 0;
	temp.playstatus = 0;
	temp.ranknum = 0;
	temp.starnum = 0;
	temp.totalscore = 0;
	temp.playfrequence = 0;
	return 0;
}

int admin::printall(vector<song>&A)
{
	int pagenum(1);
	int maxpage(0);
	int songsize = A.size();
	maxpage = songsize / 5;
	if (maxpage * 5 != songsize)
	{
		maxpage++;
	}
	system("cls");
	system("color f1");
	cout << "这是第 " << pagenum << " 页" << endl;
	cout << left << setw(10) << "序列号" << "|";
	cout << left << setw(30) << "歌手" << "|";
	cout << left << setw(30) << "歌名" << "|";
	cout << left << setw(15) << "评分" << "|";
	cout << left << setw(15) << "播放次数" << endl;
	for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
	{
		song temp = A[i + pagenum * 5];
		printsong(temp);
	}
	cout << endl;
	cout << "按上或下翻页。按esc退出浏览模式" << endl;
	char ch;
	while ((ch = _getch()) != 0x1B)
	{ 
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 80)
			{
				system("cls");
				system("color f1");
				if (pagenum == maxpage)
				{
					cout << "已经是最后一页啦！" << endl;
				}
				else
					pagenum++;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
			if (ch == 72)
			{
				system("cls");
				system("color f1");
				if (pagenum == 1)
				{
					cout << "已经是第一页啦！" << endl;
				}
				else
					pagenum--;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
		}
		else
		{
			{
				system("cls");
				system("color f1");
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
				cout << "**********不合法的按键************" << endl;
			}
		}
		rewind(stdin);
	}
	return 0;
}

int admin::printsong(song&temp)
{
	cout << left << setw(10) << temp.serialnum << "|";
	cout << left << setw(30) << temp.singername << "|";
	cout << left << setw(30) << temp.songname << "|";
	cout << left << setw(15) << temp.starnum << "|";
	cout << left << setw(15) << temp.playfrequence << "|";
	if (temp.playstatus == 1)
		cout << "--playing" << " ";
	cout << endl;
	return 0;
}

int admin::changepassword()
{
	int legalchange(1);
	while (legalchange)
	{
		cout << "请输入新的密码" << endl;
		rewind(stdin);
		string temp;
		cin >> temp;
		if (temp == password)
		{
			cout << "和旧密码一样，请重新输入" << endl;
			continue;
		}
		string confirm;
		cout << "请再输入一次确认密码" << endl;
		rewind(stdin);
		cin >> confirm;
		if (temp != confirm)
		{
			cout << "前后密码输入不一致请重新输入" << endl;
			temp.clear();
			confirm.clear();
			rewind(stdin);
			continue;
		}
		if (!legalpassword(temp))
		{
			cout << "输入的密码不合法" << endl;
			temp.clear();
			confirm.clear();
			rewind(stdin);
			continue;
		}
		cout << "密码更改成功，即将为你跳转页面" << endl;
		password = temp;
		legalchange = 0;
	}
	Sleep(2000);
	return 1;
}

int admin::sort_song()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t｜ 1->序列号排序                \n");
	printf("\t\t\t｜ 2->评分排序                   \n");
	printf("\t\t\t｜ 3->播放次数排序                 \n");
	printf("\t\t\t｜ 请输入选项[ ]                 \n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t＋==============================＋\n");
	char i;
	int opnum;
	rewind(stdin);
	cin >> i;
	if (i<'1' || i>'3')
	{
		cout << "输入不合法，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	opnum = i - '0';
	if (opnum == 1)
	{
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	if (opnum == 2)
	{
		sort(mysong.begin(), mysong.end(), comp_starnum);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	if (opnum == 3)
	{
		sort(mysong.begin(), mysong.end(), comp_frenum);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	cout << "输入不合法，返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::legalID(string A)
{
	int legalnum(1);
	if (A.length() > 20)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z') || (A[i] >= '0'&&A[i] <= '9'))
			legalnum = 1;
		else
		{
			legalnum = 0;
			break;
		}
	}
	return legalnum;

}

int admin::legalpassword(string A)
{
	int wordlegalnum(0);
	int numberlegalnum(0);
	if (A.length() > 12)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z'))
		{
			wordlegalnum += 1;
		}
		else
			if ((A[i] >= '0'&&A[i] <= '9'))
			{
				numberlegalnum += 1;
			}
	}
	if (numberlegalnum > 0 && wordlegalnum > 0)
	{
		return 1;
	}
	else
		return 0;
}

int admin::realprintall()
{
	printall(mysong);
	char i;
	cout << "任意输入返回" << endl;
	rewind(stdin);
	cin >> i;
	return 0;
}



int ktvsystem::pmainmenu()
{
	while (1)
	{
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋==============================＋\n");
		printf("\t\t\t｜                              \n");
		printf("\t\t\t｜  1->用户直达                 \n");
		printf("\t\t\t｜  2->管理员登陆               \n");
		printf("\t\t\t｜  3->退出系统                \n");
		printf("\t\t\t｜  请输入选项[]                  \n");
		printf("\t\t\t｜                              \n");
		printf("\t\t\t＋==============================＋\n");
		rewind(stdin);
		char temp;
		cin >> temp;
		rewind(stdin);
		if (temp<'1' || temp>'3')
		{
			cout << "输入错误,请重新输入" << endl;
			Sleep(1000);
		}
		else
		{
			syoperationnum = temp - '0';
			return syoperationnum;
		}
	}
}

void ktvsystem::run()
{
	initialsys();
	Sleep(1500);
	int opnumtemp = 100;
	while (opnumtemp != 3)
	{
		opnumtemp = pmainmenu();
		if (opnumtemp != 3 && opnumtemp != 1 && opnumtemp != 2)
		{
			cout << "输入错了，请输入合法的字符！！！" << endl;
			opnumtemp = 111;
			rewind(stdin);
			continue;
		}
		switch (opnumtemp)
		{
		case 3:cout << "再见，感谢使用，欢迎下次再来" << endl; break;
		case 1:B.usmenu(A); break;
		case 2:A.login(); break;
		}
	}
}

int ktvsystem::initialsys()
{
	//初始化歌曲库读入
	system("cls");
	system("color f1");
	cout << "欢迎使用本KTV点歌系统     " << endl;
	cout << "初始化系统中，请稍后    " << endl;
	ifstream infile;
	infile.open("ktvsong.txt");
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	for (int j(1); !infile.eof(); j++)
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.judgefrequence = 0;
		temp.playfrequence = 0;
		temp.totalscore = 0;
		if (temp.judgefrequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore / temp.judgefrequence;
		temp.serialnum = j;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		A.mysong.push_back(temp);
	}
	A.mysong.pop_back();
	cout << "初始化成功" << endl;
	return 1;
}



int user::usmenu(admin &A)
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋=====================================＋\n");
	printf("\t\t\t｜                                   \n");
	printf("\t\t\t｜ 1->点歌                            \n");
	printf("\t\t\t｜ 2->置顶歌曲                        \n");
	printf("\t\t\t｜ 3->删除歌曲                        \n");
	printf("\t\t\t｜ 4->歌曲评分                        \n");
	printf("\t\t\t｜ 5->查看已点歌曲                    \n");
	printf("\t\t\t｜ 6->播放选择                        \n");
	printf("\t\t\t｜ 7->搜索歌曲                        \n");
	printf("\t\t\t｜ 8->退出                            \n");
	printf("\t\t\t｜                                    \n");
	printf("\t\t\t＋=====================================＋\n");
	rewind(stdin);
	int adnumtemp = 100;
	while (1)
	{
		char temp;
		rewind(stdin);
		cin >> temp;
		if (temp<'0' || temp>'8')
		{
			adnumtemp = 100;
		}
		else
			adnumtemp = temp - '0';
		switch (adnumtemp)
		{
		case 1:ordersong(A); break;
		case 2:make_song_top(A); break;
		case 3:delete_song_inqueue(A); break;
		case 4:judge_song(A); break;
		case 5:realsee_playingqueue(A); break;
		case 6:change_song(A); break;
		case 7:search_song(A); break;
		case 8:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl; Sleep(1000);
		}
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋=====================================＋\n");
		printf("\t\t\t｜                                    \n");
		printf("\t\t\t｜ 1->点歌                            \n");
		printf("\t\t\t｜ 2->置顶歌曲                        \n");
		printf("\t\t\t｜ 3->删除歌曲                        \n");
		printf("\t\t\t｜ 4->歌曲评分                        \n");
		printf("\t\t\t｜ 5->查看已点歌曲                    \n");
		printf("\t\t\t｜ 6->播放选择                        \n");
		printf("\t\t\t｜ 7->搜索歌曲                        \n");
		printf("\t\t\t｜ 8->退出                            \n");
		printf("\t\t\t｜                                    \n");
		printf("\t\t\t＋=====================================＋\n");
		rewind(stdin);
	}
	return 1;
}

int user::ordersong(admin &A)
{
	while (1) 
	{
		system("cls");
		system("color f1");
		A.printall(A.mysong);
		cout << "输入你想点的歌曲的编号" << endl;
		int i(0);
		rewind(stdin);
		cin >> i;
		if (i<1 || i>A.mysong.size())
		{
			cout << "输入的号码不合法，返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
		for (int j(0); j < playing_queue.size(); j++)
		{
			if (playing_queue[j] == i)
			{
				cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
				Sleep(2000);
				return 0;
			}
		}
		if (i != -1)
		{
			playing_queue.push_back(i);
			cout << "添加成功" << endl;
		}
		cout << "继续点歌？输入1继续，其他键返回" << endl;
		char nextop;
		rewind(stdin);
		cin >> nextop;
		if (nextop == '1');
		else
			return 1;
	}

}

int user::make_song_top(admin &A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		Sleep(1000);
		return 0;
	}
	cout << "输入你想置顶的歌曲的编号" << endl;
	int i(0);
	rewind(stdin);
	cin >> i;
	if (i<1 || i>A.mysong.size())
	{
		cout << "没有这首歌，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	playing_queue.insert(playing_queue.begin(), i);
	vector<int>::iterator it;
	for (it = playing_queue.begin()+1; it != playing_queue.end(); )
	{
		if (*it == i)
		{
			it = playing_queue.erase(it);
		}
		else
		{
			++it;
		}
	}
	cout << "置顶成功，正在返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int user::delete_song_inqueue(admin&A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		cout << "正在返回上一级" << endl;
		Sleep(1000);
		return 0;
	}
	cout << "输入你想删除的歌的编号" << endl;
	int number;
	rewind(stdin);
	cin >> number;
	if (number < 1)
	{
		cout << "输入有误，将会返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	vector<int>::iterator it;
	int flag = 0;
	for (it = playing_queue.begin(); it != playing_queue.end(); )
	{
		if (*it == number)
		{
			it = playing_queue.erase(it);
			flag = 1;
		}
		else
		{
			++it;
		}
	}
	if (flag == 1)
	{
		cout << "删除成功,正在返回上一级" << endl;
	}
	else
	{
		cout << "没有这一首歌" << endl;
	}
	Sleep(2000);
	return 0;
}

int user::judge_song(admin&A)
{
	double star;
	int IDnum;
	system("cls");
	system("color f1");
	A.printall(A.mysong);
	cout << "输入你要评分的歌曲对应的ID号" << endl;
	rewind(stdin);
	cin >> IDnum;
	if (IDnum<1 || IDnum>A.mysong.size())
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "输入你的评分，介于1-5分" << endl;
	rewind(stdin);
	cin >> star;

	if (star < 1 || star>5)
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	A.mysong[IDnum - 1].totalscore += star;
	A.mysong[IDnum - 1].judgefrequence += 1;
	A.mysong[IDnum - 1].starnum = A.mysong[IDnum - 1].totalscore / A.mysong[IDnum - 1].judgefrequence;
	cout << "评分成功，正在返回上一级" << endl;
	Sleep(2000);
	return 1;
}

int user::see_playingqueue(admin&A)
{
	if (playing_queue.size() == 0)
	{
		cout << "空空如也的歌单，先去点首试试？" << endl;
		Sleep(1000);
		return 0;
	}
	vector<song>result;
	for (int i(0); i < playing_queue.size(); i++)
	{
		result.push_back(A.mysong[playing_queue[i]-1]);
	}
	A.printall(result);
	return 0;
}

int user::realsee_playingqueue(admin &A)
{
	see_playingqueue(A);
	char i;
	cout << "输入任意数字返回" << endl;
	rewind(stdin);
	cin >> i;
	return 0;
}

int user::change_song(admin &A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		cout << "准备返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "请输入你想开始播放的歌曲的编号" << endl;
	int number;
	rewind(stdin);
	cin >> number;
	if (number < 1)
	{
		cout << "输入有问题，准备回到上一级" << endl;
		Sleep(2000);
		return 1;
	}
	for (int i(0); i < playing_queue.size(); i++)
	{
		if (number == playing_queue[i])
		{
			A.mysong[number - 1].playstatus = 1;
			A.mysong[number - 1].playfrequence++;
			for (int i(0); i < playing_queue.size(); i++)
			{
				if (playing_queue[i] == number)
					continue;
				A.mysong[playing_queue[i] - 1].playstatus = 0;
			}
			cout << "切歌成功，准备返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
	}
	cout << "播放列表没有这首，准备返回上一级" << endl;
	Sleep(2000);
	return 0;

}

int user::search_song(admin &A)
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ 1->歌名搜索                      \n");
	printf("\t\t\t｜ 2->歌手搜索                      \n");
	printf("\t\t\t｜ 3->拼音搜索                      \n");
	printf("\t\t\t｜ 请输入选项[ ]                    \n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t\t\t＋==============================＋\n");
	vector<song>result;
	string temp;
	int i(0);
	rewind(stdin);
	cin >> i;
	if (i == 1)
	{
		cout << "输入查找对象的歌名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size();i++)
		{
			if (A.mysong[i].songname == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	if (i == 2)
	{
		cout << "输入查找对象的歌手名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size(); i++)
		{
			if (A.mysong[i].singername == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	if (i == 3)
	{
		cout << "输入查找对象的拼音名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size(); i++)
		{
			if (A.mysong[i].pinyin == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	cout << "输入不合法" << endl;
	return 0;
}

