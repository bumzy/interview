#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "qh_vector.h"

//test ctor, empty(), size(), capacity(), clear()
void test1()
{
    qh::vector<int> num_vect1;
    assert(num_vect1.empty() == true);
    assert(num_vect1.size() == 0);
    assert(num_vect1.capacity() == 0);

    qh::vector<int> num_vect2(3, 1);
    assert(num_vect2.empty() == false);
    assert(num_vect2.size() == 3);
    assert(num_vect2.capacity() == 3);
    assert(num_vect2[0] == 1);
    assert(num_vect2[1] == 1);
    assert(num_vect2[2] == 1);

    qh::vector<int> num_vect3(num_vect1);
    assert(num_vect3.empty() == true);
    assert(num_vect3.size() == 0);
    assert(num_vect3.capacity() == 0);

    qh::vector<int> num_vect4(num_vect2);
    assert(num_vect4.empty() == false);
    assert(num_vect4.size() == 3);
    assert(num_vect4.capacity() == 3);
    assert(num_vect4[0] == 1);
    assert(num_vect4[1] == 1);
    assert(num_vect4[2] == 1);
    num_vect4.clear();
    assert(num_vect4.empty() == true);
    assert(num_vect4.size() == 0);
    assert(num_vect4.capacity() == 3);
}

//test reserve()
void test2()
{
    qh::vector<int> num_vect(3, 1);
    num_vect.reserve(3);
    assert(num_vect.size() == 3);
    assert(num_vect.capacity() == 3);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
    assert(num_vect[2] == 1);

    num_vect.reserve(4);
    assert(num_vect.size() == 3);
    assert(num_vect.capacity() == 4);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
    assert(num_vect[2] == 1);

    num_vect.reserve(2);
    assert(num_vect.size() == 2);
    assert(num_vect.capacity() == 2);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
}
//test resize()
void test3()
{
    qh::vector<int> num_vect(3, 1);
    num_vect.resize(3);
    assert(num_vect.size() == 3);
    assert(num_vect.capacity() == 3);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
    assert(num_vect[2] == 1);

    num_vect.resize(4);
    assert(num_vect.size() == 4);
    assert(num_vect.capacity() == 6);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
    assert(num_vect[2] == 1);

    num_vect.resize(2);
    assert(num_vect.size() == 2);
    assert(num_vect.capacity() == 6);
    assert(num_vect[0] == 1);
    assert(num_vect[1] == 1);
}

//test push_back()
void test4()
{
    qh::vector<int> num_vect;
    assert(num_vect.size() == 0);
    assert(num_vect.capacity() == 0);

    num_vect.push_back(1);
    assert(num_vect.size() == 1);
    assert(num_vect.capacity() == 1);

    num_vect.push_back(2);
    assert(num_vect.size() == 2);
    assert(num_vect.capacity() == 2);

    num_vect.push_back(3);
    assert(num_vect.size() == 3);
    assert(num_vect.capacity() == 4);

    num_vect.push_back(4);
    assert(num_vect.size() == 4);
    assert(num_vect.capacity() == 4);

    num_vect.push_back(5);
    assert(num_vect.size() == 5);
    assert(num_vect.capacity() == 8);

    assert(num_vect[0] == 1);
    assert(num_vect[1] == 2);
    assert(num_vect[2] == 3);
    assert(num_vect[3] == 4);
    assert(num_vect[4] == 5);
}

//test pop_back()
void test5()
{
    qh::vector<char> char_vect(5, 'a');
    assert(char_vect.size() == 5);
    assert(char_vect.capacity() == 5);
    assert(char_vect[0] == 'a');
    assert(char_vect[1] == 'a');
    assert(char_vect[2] == 'a');
    assert(char_vect[3] == 'a');
    assert(char_vect[4] == 'a');

    char_vect.push_back('b');
    assert(char_vect.size() == 6);
    assert(char_vect.capacity() == 10);

    char_vect.push_back('c');
    assert(char_vect.size() == 7);
    assert(char_vect.capacity() == 10);

    char back = '\0';
    char_vect.pop_back(back);
    assert(back == 'c');
    assert(char_vect.size() == 6);
    assert(char_vect.capacity() == 10);

    back = '\0';
    char_vect.pop_back(back);
    assert(back == 'b');
    assert(char_vect.size() == 5);
    assert(char_vect.capacity() == 10);

    back = '\0';
    char_vect.pop_back(back);
    assert(back == 'a');
    assert(char_vect.size() == 4);
    assert(char_vect.capacity() == 10);
}

//test operator=()
void test6()
{
    qh::vector<std::string> str_vect;
    str_vect = qh::vector<std::string>(3, "abc");
    assert(str_vect.size() == 3);
    assert(str_vect.capacity() == 3);
    assert(str_vect[0] == "abc");
    assert(str_vect[1] == "abc");
    assert(str_vect[2] == "abc");

    str_vect = str_vect;
    assert(str_vect.size() == 3);
    assert(str_vect.capacity() == 3);
    assert(str_vect[0] == "abc");
    assert(str_vect[1] == "abc");
    assert(str_vect[2] == "abc");
}

//test operator[]()
void test7()
{
    qh::vector<std::string> str_vect(3, "abc");
    assert(str_vect.size() == 3);
    assert(str_vect.capacity() == 3);
    assert(str_vect[0] == "abc");
    assert(str_vect[1] == "abc");
    assert(str_vect[2] == "abc");

    str_vect[0] = str_vect[2] = "123";
    assert(str_vect.size() == 3);
    assert(str_vect.capacity() == 3);
    assert(str_vect[0] == "123");
    assert(str_vect[1] == "abc");
    assert(str_vect[2] == "123");
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
    test7();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

