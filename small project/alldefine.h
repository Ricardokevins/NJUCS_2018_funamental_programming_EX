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
#pragma once
#include<iomanip>
#include <winbase.h>
using namespace std;

class mydata {
	vector<string> table_head;//0��λ����ID�������ݵ�һ����
	vector<vector<string>> real_data;//������Ƕ������ݡ�
	vector<string>single_data;//���浥�е�����
	int hrow;//���������ʵ����
	int lrow;//���������ʵ����
};

