#include<iostream>
#include<cstdio>
#include<string>
#include<mysql.h>
using namespace std;
#define PASSWORDS "&0312163315Dl"
#define IP "127.0.0.1"
#define USER "root"
//判断查询是否有问题
bool judgement(MYSQL_RES*res, int ret)
{
	if (ret == 1)
	{
		cout << "查询错误" << endl;
		mysql_free_result(res);
		return false;
	}
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == NULL)
	{
		cout << "数据为空" << endl;
		mysql_free_result(res);
		return false;
	}
	return true;
}
//展示菜单
void show()
{
	cout << "1、查看人数" << endl;
	cout << "2、删除人数" << endl;
	cout << "3、结束    " << endl;
}
//将没有完成的添加进入数据库(没有数据时使用)
void begin_n(MYSQL&mysql)
{
	mysql_query(&mysql, "insert into no_finished value('王昊')");
	mysql_query(&mysql, "insert into no_finished value('张少奇')");
	mysql_query(&mysql, "insert into no_finished value('全博良')");
	mysql_query(&mysql, "insert into no_finished value('董旭宁')");
	mysql_query(&mysql, "insert into no_finished value('李泽州')");
	mysql_query(&mysql, "insert into no_finished value('张世宇')");
	mysql_query(&mysql, "insert into no_finished value('王珂')");
	mysql_query(&mysql, "insert into no_finished value('王新琪')");
	mysql_query(&mysql, "insert into no_finished value('刘桐')");
	mysql_query(&mysql, "insert into no_finished value('彭威尧')");
	mysql_query(&mysql, "insert into no_finished value('付晋')");
	mysql_query(&mysql, "insert into no_finished value('孟德贤')");
	mysql_query(&mysql, "insert into no_finished value('武路')");
	mysql_query(&mysql, "insert into no_finished value('苗世豪')");
	mysql_query(&mysql, "insert into no_finished value('米政硕')");
	mysql_query(&mysql, "insert into no_finished value('李飞宇')");
	mysql_query(&mysql, "insert into no_finished value('石鑫垚')");
	mysql_query(&mysql, "insert into no_finished value('郭子瑞')");
	mysql_query(&mysql, "insert into no_finished value('任伟康')");
	mysql_query(&mysql, "insert into no_finished value('刘子毅')");
	mysql_query(&mysql, "insert into no_finished value('张玉哲')");
	mysql_query(&mysql, "insert into no_finished value('杨光璞')");
	mysql_query(&mysql, "insert into no_finished value('蒋卓')");
	mysql_query(&mysql, "insert into no_finished value('张明炯')");
	mysql_query(&mysql, "insert into no_finished value('赵洪林')");
	mysql_query(&mysql, "insert into no_finished value('句盛泽')");
	mysql_query(&mysql, "insert into no_finished value('冯宇辰')");
	mysql_query(&mysql, "insert into no_finished value('陈建森')");
	mysql_query(&mysql, "insert into no_finished value('王艺霖')");
}
//打印完成进度
void p_human(MYSQL&mysql)
{
	MYSQL_RES*res = NULL;
	MYSQL_ROW row;
	cout << "请选择要查询的类型" << endl;
	cout << "0、未完成 1、已完成" << endl << "默认为未完成" << endl;
	int choice;
	cin >> choice;
	int ret = 0;
	if (choice == 1)
		ret = mysql_query(&mysql, "select * from is_finished");//mysql中执行的操作
	else
		ret = mysql_query(&mysql, "select * from no_finished");//mysql中执行的操作
	res = mysql_store_result(&mysql);//查询结果
	row = mysql_fetch_row(res);
	if (row != NULL)
	{
		do//获取查询结果的第一行，逐个分为每一列
		{
			cout << row[0] << endl;
		} while (row = mysql_fetch_row(res));
	}
	else
		cout << "数据为空" << endl;
	mysql_free_result(res);
}
//判断能否删除，并且删除对应数据
bool new_delete_person(MYSQL&mysql, MYSQL_RES*&res, int ret, const string&table, const string& name)
{
	char sql[256];
	_snprintf_s(sql, 256, "select * from %s where name='%s'", table.c_str(), name.c_str());
	ret = mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	if (!judgement(res, ret))
	{
		cout << "查无此人" << endl;
		return false;
	}
	_snprintf_s(sql, 256, "delete from %s where name='%s'", table.c_str(), name.c_str());
	mysql_query(&mysql, sql);
	return true;
}
//在对应的表中删除数据
void delete_person(MYSQL&mysql)
{
	char sql[256];
	int ret = 0;
	MYSQL_RES*res = NULL;
	string name;
	MYSQL_ROW row = NULL;
	int choice = 0;
	cout << "请选择你要删除的表" << endl << "0、未完成 1、已完成" << endl << "默认为未完成" << endl;
	cin >> choice;
	cout << "请输入你要删除人的姓名" << endl;
	cin >> name;
	if (choice == 1)
	{
		//判断能否删除，并且删除对应数据
		if (new_delete_person(mysql, res, ret, "is_finished", name))
		{
			cout << "删除成功" << endl;
			_snprintf_s(sql, 256, "insert into no_finished value('%s')", name.c_str());
			mysql_query(&mysql, sql);
			mysql_free_result(res);
		}
	}
	else
	{
		if (new_delete_person(mysql, res, ret, "no_finished", name))
		{
			cout << "删除成功" << endl;
			_snprintf_s(sql, 256, "insert into is_finished value('%s')", name.c_str());
			mysql_query(&mysql, sql);
			mysql_free_result(res);
		}
	}
}
//手动添加(没用)
void add_person(MYSQL&mysql)
{
	char sql[256];
	MYSQL_RES*res = NULL;
	string name;
	int choice = 0;
	cout << "请选择你要添加的表" << endl << "0、未完成 1、已完成" << endl << "默认为未完成" << endl;
	cin >> choice;
	cout << "请输入你要添加人的姓名" << endl;
	cin >> name;
	if (choice == 1)
		_snprintf_s(sql, 256, "insert into is_finished value('%s')", name.c_str());
	else
		_snprintf_s(sql, 256, "insert into no_finished value('%s')", name.c_str());
	int ret = mysql_query(&mysql, sql);//执行添加
}
int main()
{
	MYSQL mysql;
	MYSQL_RES *res = NULL;//数据查询的结果
	MYSQL_ROW row = NULL;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, IP, USER, PASSWORDS, "tast", 3306, NULL, 0) == NULL)
	{
		cout << "错误原因" << mysql_error(&mysql) << endl;
		cout << "连接失败" << endl;
		::system("pause");
		exit(1);
	}
	/*
	//以上为固定步骤
	int ret = mysql_query(&mysql, "select * from student");//mysql中执行的操作
	cout << ret << endl;
	res = mysql_store_result(&mysql);//获取查询的结果
	while (row = mysql_fetch_row(res))//获取查询结果的第一行，逐个分为每一列
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
			cout << "输入错误" << endl; break;
		}
		::system("pause");
		::system("cls");
	}
	mysql_close(&mysql);
	::system("pause");
	return 0;
}