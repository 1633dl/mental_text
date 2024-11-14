#include<iostream>
#include<cstdio>
#include<string>
#include<mysql.h>
using namespace std;
#define PASSWORDS "&0312163315Dl"
#define IP "127.0.0.1"
#define USER "root"
//�жϲ�ѯ�Ƿ�������
bool judgement(MYSQL_RES*res, int ret)
{
	if (ret == 1)
	{
		cout << "��ѯ����" << endl;
		mysql_free_result(res);
		return false;
	}
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == NULL)
	{
		cout << "����Ϊ��" << endl;
		mysql_free_result(res);
		return false;
	}
	return true;
}
//չʾ�˵�
void show()
{
	cout << "1���鿴����" << endl;
	cout << "2��ɾ������" << endl;
	cout << "3������    " << endl;
}
//��û����ɵ���ӽ������ݿ�(û������ʱʹ��)
void begin_n(MYSQL&mysql)
{
	mysql_query(&mysql, "insert into no_finished value('���')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('ȫ����')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('����')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('��ͩ')");
	mysql_query(&mysql, "insert into no_finished value('����Ң')");
	mysql_query(&mysql, "insert into no_finished value('����')");
	mysql_query(&mysql, "insert into no_finished value('�ϵ���')");
	mysql_query(&mysql, "insert into no_finished value('��·')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('����˶')");
	mysql_query(&mysql, "insert into no_finished value('�����')");
	mysql_query(&mysql, "insert into no_finished value('ʯ�Έ�')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('��ΰ��')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('����')");
	mysql_query(&mysql, "insert into no_finished value('��׿')");
	mysql_query(&mysql, "insert into no_finished value('������')");
	mysql_query(&mysql, "insert into no_finished value('�Ժ���')");
	mysql_query(&mysql, "insert into no_finished value('��ʢ��')");
	mysql_query(&mysql, "insert into no_finished value('���')");
	mysql_query(&mysql, "insert into no_finished value('�½�ɭ')");
	mysql_query(&mysql, "insert into no_finished value('������')");
}
//��ӡ��ɽ���
void p_human(MYSQL&mysql)
{
	MYSQL_RES*res = NULL;
	MYSQL_ROW row;
	cout << "��ѡ��Ҫ��ѯ������" << endl;
	cout << "0��δ��� 1�������" << endl << "Ĭ��Ϊδ���" << endl;
	int choice;
	cin >> choice;
	int ret = 0;
	if (choice == 1)
		ret = mysql_query(&mysql, "select * from is_finished");//mysql��ִ�еĲ���
	else
		ret = mysql_query(&mysql, "select * from no_finished");//mysql��ִ�еĲ���
	res = mysql_store_result(&mysql);//��ѯ���
	row = mysql_fetch_row(res);
	if (row != NULL)
	{
		do//��ȡ��ѯ����ĵ�һ�У������Ϊÿһ��
		{
			cout << row[0] << endl;
		} while (row = mysql_fetch_row(res));
	}
	else
		cout << "����Ϊ��" << endl;
	mysql_free_result(res);
}
//�ж��ܷ�ɾ��������ɾ����Ӧ����
bool new_delete_person(MYSQL&mysql, MYSQL_RES*&res, int ret, const string&table, const string& name)
{
	char sql[256];
	_snprintf_s(sql, 256, "select * from %s where name='%s'", table.c_str(), name.c_str());
	ret = mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	if (!judgement(res, ret))
	{
		cout << "���޴���" << endl;
		return false;
	}
	_snprintf_s(sql, 256, "delete from %s where name='%s'", table.c_str(), name.c_str());
	mysql_query(&mysql, sql);
	return true;
}
//�ڶ�Ӧ�ı���ɾ������
void delete_person(MYSQL&mysql)
{
	char sql[256];
	int ret = 0;
	MYSQL_RES*res = NULL;
	string name;
	MYSQL_ROW row = NULL;
	int choice = 0;
	cout << "��ѡ����Ҫɾ���ı�" << endl << "0��δ��� 1�������" << endl << "Ĭ��Ϊδ���" << endl;
	cin >> choice;
	cout << "��������Ҫɾ���˵�����" << endl;
	cin >> name;
	if (choice == 1)
	{
		//�ж��ܷ�ɾ��������ɾ����Ӧ����
		if (new_delete_person(mysql, res, ret, "is_finished", name))
		{
			cout << "ɾ���ɹ�" << endl;
			_snprintf_s(sql, 256, "insert into no_finished value('%s')", name.c_str());
			mysql_query(&mysql, sql);
			mysql_free_result(res);
		}
	}
	else
	{
		if (new_delete_person(mysql, res, ret, "no_finished", name))
		{
			cout << "ɾ���ɹ�" << endl;
			_snprintf_s(sql, 256, "insert into is_finished value('%s')", name.c_str());
			mysql_query(&mysql, sql);
			mysql_free_result(res);
		}
	}
}
//�ֶ����(û��)
void add_person(MYSQL&mysql)
{
	char sql[256];
	MYSQL_RES*res = NULL;
	string name;
	int choice = 0;
	cout << "��ѡ����Ҫ��ӵı�" << endl << "0��δ��� 1�������" << endl << "Ĭ��Ϊδ���" << endl;
	cin >> choice;
	cout << "��������Ҫ����˵�����" << endl;
	cin >> name;
	if (choice == 1)
		_snprintf_s(sql, 256, "insert into is_finished value('%s')", name.c_str());
	else
		_snprintf_s(sql, 256, "insert into no_finished value('%s')", name.c_str());
	int ret = mysql_query(&mysql, sql);//ִ�����
}
int main()
{
	MYSQL mysql;
	MYSQL_RES *res = NULL;//���ݲ�ѯ�Ľ��
	MYSQL_ROW row = NULL;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, IP, USER, PASSWORDS, "tast", 3306, NULL, 0) == NULL)
	{
		cout << "����ԭ��" << mysql_error(&mysql) << endl;
		cout << "����ʧ��" << endl;
		::system("pause");
		exit(1);
	}
	/*
	//����Ϊ�̶�����
	int ret = mysql_query(&mysql, "select * from student");//mysql��ִ�еĲ���
	cout << ret << endl;
	res = mysql_store_result(&mysql);//��ȡ��ѯ�Ľ��
	while (row = mysql_fetch_row(res))//��ȡ��ѯ����ĵ�һ�У������Ϊÿһ��
	{
	cout << row[0] << " " << row[1] << " " << row[2] << endl;
	}
	*/
	//begin_n(mysql);
	int choice;
	while (1)
	{
		show();
		cin >> choice;
		switch (choice)
		{
		case 1:
			p_human(mysql); break;
		case 2:
			delete_person(mysql); break;
		case 3:
			exit(0); break;
		default:
			cout << "�������" << endl; break;
		}
		::system("pause");
		::system("cls");
	}
	mysql_close(&mysql);
	::system("pause");
	return 0;
}