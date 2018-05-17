/*************************************************************************
 > File Name: test_insert.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 17 May 2018 05:11:10 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<mysql.h>

int main(int agrc, char* agrv[])
{
	MYSQL conn;
	MYSQL* pconn;
	MYSQL_RES* result;
	MYSQL_ROW row;
	char* w;
	int res;

	mysql_init(&conn);
	pconn = mysql_real_connect(&conn,
		"localhost", "root", "jklfds", "test", 0, NULL,CLIENT_FOUND_ROWS);
	if (pconn) {
		printf("connect success \n");
		res = mysql_query(&conn, "insert into test values('user','123456')");
		if (0 == res) {
			printf("OK\n");
		} else {
			printf("insert error %d : %s \n",
				mysql_errno(&conn), mysql_error(&conn));
		}

		// 查询
		mysql_query(&conn, "select * from test");
		// 会分配内存，需要释放
		result = mysql_store_result(&conn);
		if (result == NULL) {
			printf("select error %d : %s \n",
				mysql_errno(&conn), mysql_error(&conn));
		} else {
			while ((row = mysql_fetch_row(result))) {
				w = row[0];
				printf("%s %s\n", w, row[1]);
			}
			mysql_free_result(result);
		}
		mysql_close(&conn);
		mysql_library_end();
	} else {
		printf("connect error %d : %s \n",
			mysql_errno(&conn), mysql_error(&conn));
	}
	return 0;
}
