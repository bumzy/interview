#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "qh_string.h"

//test ctor : string::string()
void test1()
{
    qh::string str1;
    assert(str1.size() == 0);
    assert(!strcmp("", str1.data()));
}

//test ctor : string::string(const char* s)
void test2()
{
    qh::string str1("abc");
    assert(str1.size() == 3);
    assert(!strcmp("abc", str1.c_str()));

    qh::string str2(NULL);
    assert(str2.size() == 0);
    assert(!strcmp("", str2.c_str()));

    qh::string str3("");
    assert(str3.size() == 0);
    assert(!strcmp("", str3.c_str()));
}

//test ctor : string::string(const char* s, size_t len)
void test3()
{
    qh::string str1("abc", 5);
    assert(str1.size() == 3);
    assert(!strcmp("abc", str1.data()));

    qh::string str2("abc", 3);
    assert(str2.size() == 3);
    assert(!strcmp("abc", str2.data()));

    qh::string str3("abc", 2);
    assert(str3.size() == 2);
    assert(!strcmp("ab", str3.data()));

    qh::string str4("abc", 0);
    assert(str4.size() == 0);
    assert(!strcmp("", str4.data()));

    qh::string str5(NULL, 3);
    assert(str5.size() == 0);
    assert(!strcmp("", str5.data()));
}

//test ctor : string::string(const string& rhs)
void test4()
{
    qh::string str1 = qh::string("abc");
    assert(str1.size() == 3);
    assert(!strcmp("abc", str1.c_str()));

    qh::string str2 = qh::string("");
    assert(str2.size() == 0);
    assert(!strcmp("", str2.c_str()));

    qh::string str3 = qh::string();
    assert(str3.size() == 0);
    assert(!strcmp("", str3.c_str()));
}

//test string& string::operator=(const string& rhs)
void test5()
{
    qh::string str1("abc");

    str1 = qh::string();
    assert(str1.size() == 0);
    assert(!strcmp("", str1.data()));

    str1 = qh::string("");
    assert(str1.size() == 0);
    assert(!strcmp("", str1.data()));

    qh::string str2 = str1 = qh::string("abc");
    assert(str2.size() == 3);
    assert(!strcmp("abc", str2.data()));

    str1 = qh::string(NULL);
    assert(str1.size() == 0);
    assert(!strcmp("", str1.data()));
}

//test char& operator[](size_t index)
void test6()
{
    qh::string str1("abc");
    str1[0] = str1[1] = str1[2] = '1';
    assert(str1.size() == 3);
    assert(!strcmp("111", str1.c_str()));
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

