#pragma once
#include"alldefine.h"

class user {
public:
	vector<string>touch_table;//�ɲ��������ݿ�
	vector<vector<string>>table_power;//��Ӧÿһ�����ݿ�
	vector<string>command_table;//��Ϊ�����鱣������Ȩ����Ϣ���������vector��ͬ����һ�������ڶ�ά����Ķ���
	int create();
	int drop();
	int tablelist();
	int insert();
	int mydelete();
	int select();
	int grant();
	int revoke();
	int command_analyse(string A);
	string username;//�û���
	string password;//�û�������

};
