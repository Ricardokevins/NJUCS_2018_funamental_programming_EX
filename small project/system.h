#pragma once
#include"alldefine.h"
#include"user.h"
class mysystem {
public:
	vector<string> cur_username;//���浱ǰ��ϵͳ����û�
	vector<user>cur_user;
	vector<string>table_name;//���浱ǰ���ڵ����ݿ�����
	vector<string>file_name;//���浱ǰ���ڵ��ļ�������
	void run();

	int read_initial_file();

	int load_user();
};
