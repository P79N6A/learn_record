/*************************************************************************
 > File Name: main.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 17 May 2018 05:49:03 AM PDT
 ************************************************************************/

#include<iostream>
#include<string>
#include<stdint.h>
#include <sstream>
using namespace std;

/// 哈希函数
uint32_t hash(const string str)
{
	char const *_str = str.c_str();
	int len = str.length();
	unsigned long hash = 0;
	for (int i = 0; i < len; ++i) {
		// hash = hash * 33 + str[i]
		// *33 = (32 + 1)
		hash = hash + (hash << 5) + str[i];
	}
	return hash;
}

template<typename T>
string to_string(const T& t)
{
	ostringstream oss;  //创建一个格式化输出流
	oss<<t;             //把值传递如流中
	return oss.str();
}

string uin = "646270";
string passwd = "123456";
string randnum = "878777"; //保证每次请求随机性， 避免回放攻击
string now_time = "123450"; //时间戳，限制请求时效，避免回放攻击

string key = "666666"; // server 鉴权返回的key
// server 端保存的用户密码信息，不保存原始密码，避免被脱裤子
// client 每次动态生成
string h_passwd = to_string(hash(passwd));
string K_server = to_string(hash(h_passwd + uin));

string encode(string src, const string &key)
{
	return src;
}

string decode(string src, string &key)
{
	return src;
}

class client {
	string randnum;
	public:
	client(string randnum):randnum(randnum){};
	string requert(const string &uin, const string &passwd)
	{
		//uin + A(=K(uin + randnum + time))
		string h_passwd = to_string(hash(passwd));
		string K = to_string(hash(h_passwd + uin));
		return uin + encode(uin+randnum+now_time, K);
	}
	string get_key(const string &respone)
	{
		// uin _ key
		string uin_key = decode(respone, randnum);
		// 校验能否正常解析uin
		return uin_key;
	}

};

class server {
	public:
	server() {};
	string respone(const string req)
	{
		string src = decode(req, K_server);
		//uin
		//randnum
		//now_time
		//通过解包client的请求去除randnum
		//再用randnum 加密返回给client的数据
		//如果client解密失败，说明server取出的randnum有误，可能是假的server
		return encode(uin + key, randnum);
	}
};

int main(int argc, char* argv[])
{
	client my_client(randnum);
	server my_server;

	cout << "Client : Access info uin : " << uin << " passwd " << passwd << endl;
	cout << "Client : randnum : " << randnum << "  time  " << now_time << endl;
	// client 根据输入账户密码发送鉴权请求
	string client_requert = my_client.requert(uin, passwd);
	cout << "Client : snd requert : " << client_requert << endl;

	cout << "Server : K_server : " << K_server  << endl << endl;
	// server 解密鉴权请求，校验，返回 key
	string server_respone = my_server.respone(client_requert);
	if (server_respone.empty()) {
		cout << "Server : respone  error " << endl;
	} else {
		cout << "Server : respone : " << server_respone  << endl << endl;
		//client 解析server回包，去除key
		string conn_key = my_client.get_key(server_respone);
		if (conn_key.empty()) {
			cout << "Client : nibushi my server " << endl;
		} else {
			cout << "Client : get key : " << conn_key << endl;
		}
	}

	return 0;
}
