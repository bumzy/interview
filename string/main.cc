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
    assert(str1.data() == NULL);
    assert(str1.c_str() == NULL);
}

//test ctor : string::string(const char* s)
void test2()
{
    qh::string str1("abc");
    assert(str1.size() == 3);
    assert(str1[0] == 'a');
    assert(str1[1] == 'b');
    assert(str1[2] == 'c');
    assert(str1[3] == '\0');
    assert(!strcmp("abc", str1.data()));
    assert(!strcmp("abc", str1.c_str()));

    qh::string str2(NULL);
    assert(str2.size() == 0);
    assert(str2.data() == NULL);
    assert(str2.c_str() == NULL);

    qh::string str3("");
    assert(str3.size() == 0);
    assert(str3[0] == '\0');
    assert(!strcmp("", str3.data()));
    assert(!strcmp("", str3.c_str()));
}

//test ctor : string::string(const char* s, size_t len)
void test3()
{
    qh::string str1("abc", 5);
    assert(str1.size() == 3);
    assert(str1[0] == 'a');
    assert(str1[1] == 'b');
    assert(str1[2] == 'c');
    assert(str1[3] == '\0');
    assert(!strcmp("abc", str1.data()));
    assert(!strcmp("abc", str1.c_str()));

    qh::string str2("abc", 3);
    assert(str2.size() == 3);
    assert(str2[0] == 'a');
    assert(str2[1] == 'b');
    assert(str2[2] == 'c');
    assert(str2[3] == '\0');
    assert(!strcmp("abc", str2.data()));
    assert(!strcmp("abc", str2.c_str()));

    qh::string str3("abc", 2);
    assert(str3.size() == 2);
    assert(str3[0] == 'a');
    assert(str3[1] == 'b');
    assert(str3[2] == '\0');
    assert(!strcmp("ab", str3.data()));
    assert(!strcmp("ab", str3.c_str()));

    qh::string str4("abc", 0);
    assert(str4.size() == 0);
    assert(str4[0] == '\0');
    assert(!strcmp("", str4.data()));
    assert(!strcmp("", str4.c_str()));

    qh::string str5(NULL, 3);
    assert(str5.size() == 0);
    assert(str5.data() == NULL);
    assert(str5.c_str() == NULL);
}

//test ctor : string::string(const string& rhs)
void test4()
{
    qh::string str1 = qh::string("abc");
    assert(str1.size() == 3);
    assert(str1[0] == 'a');
    assert(str1[1] == 'b');
    assert(str1[2] == 'c');
    assert(str1[3] == '\0');
    assert(!strcmp("abc", str1.data()));
    assert(!strcmp("abc", str1.c_str()));

    qh::string str2 = qh::string("");
    assert(str2.size() == 0);
    assert(str2[0] == '\0');
    assert(!strcmp("", str2.data()));
    assert(!strcmp("", str2.c_str()));

    qh::string str3 = qh::string();
    assert(str3.size() == 0);
    assert(str3.data() == NULL);
    assert(str3.c_str() == NULL);
}

//test string& string::operator=(const string& rhs)
void test5()
{
    qh::string str1("abc");

    str1 = qh::string();
    assert(str1.size() == 0);
    assert(str1.data() == NULL);
    assert(str1.c_str() == NULL);

    str1 = qh::string("");
    assert(str1.size() == 0);
    assert(str1[0] == '\0');
    assert(!strcmp("", str1.data()));
    assert(!strcmp("", str1.c_str()));

    qh::string str2 = str1 = qh::string("abc");
    assert(str2.size() == 3);
    assert(str2[0] == 'a');
    assert(str2[1] == 'b');
    assert(str2[2] == 'c');
    assert(str2[3] == '\0');
    assert(!strcmp("abc", str2.data()));
    assert(!strcmp("abc", str2.c_str()));

    str1 = qh::string(NULL);
    assert(str1.size() == 0);
    assert(str1.data() == NULL);
    assert(str1.c_str() == NULL);
}

//test string& string::operator=(const string& rhs)
void test6()
{
    qh::string str1("abc");
    str1[0] = str1[1] = str1[2] = '1';
    assert(str1[0] == '1');
    assert(str1[1] == '1');
    assert(str1[2] == '1');
    assert(str1[3] == '\0');
    assert(!strcmp("111", str1.data()));
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

