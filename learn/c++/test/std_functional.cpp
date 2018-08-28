/*************************************************************************
 > File Name: std_functional.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Tue 28 Aug 2018 11:43:58 AM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<functional>

void printfMsg(const std::string &msg)
{
    std::cout << "[INFO] "<< msg << std::endl;
}


typedef void(*pfun_t)(const std::string &msg);
pfun_t  pfun = printfMsg;
//void (*pfun) (const std::string &msg) = printfMsg;

class MsgClss {
    public:
        static void staticPrintfMsg(const std::string &msg)
        {
            std::cout << "[INFO] "<< msg << std::endl;
        }
        void printfMsg(const std::string &msg) const
        {
            std::cout << "[INFO] "<< msg << std::endl;
        }

};

class PrintMsgClass {
    public:
        void operator() (const std::string &msg) const
        {
            std::cout << "[INFO] "<< msg << std::endl;
        }
};

void test_bind(int a, int b, int c)
{
    std::cout << a << b << c << std::endl;
}

int main(int argc, char *argvp[])
{
    printfMsg("Test std::function");
    std::function<void(const std::string&)> f1 = printfMsg;
    f1("test normal function\n");

    std::function<void(const std::string&)> f2 = pfun;
    f2("test normal function pointer\n");

    std::function<void(const std::string&)> f3 = [](const std::string &msg) {std::cout << "[INFO] "<< msg << std::endl;};
    f3("test lambad function pointer\n");

    std::function<void(const std::string&)> f4 = MsgClss::staticPrintfMsg;
    f4("test class static function\n");

    MsgClss testMsg;
    std::function<void(const std::string&)> f5 = std::bind(&MsgClss::printfMsg, &testMsg/*obj this*/, std::placeholders::_1);
    f5("test class function\n");

    std::function<void(const std::string&)> f6 = PrintMsgClass();
    f6("test function obj\n");

    //偏函数，占位
    std::function<void(int a)> f71 = std::bind(&test_bind, std::placeholders::_1, 2, 3);
    std::function<void(int b)> f72 = std::bind(&test_bind, 1,std::placeholders::_1, 3);
    std::function<void(int a, int c)> f73 = std::bind(&test_bind, std::placeholders::_1, 2, std::placeholders::_2);
    f71(1);
    f72(2);
    f73(1,3);

    return 0;
}
