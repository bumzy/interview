#include "ini_parser.h"

#include <string.h>
#include <assert.h>

void test1()
{
    const char* ini_text= "a=1\nb=2\n";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

//test key_value_seperator.length() > 1
void test4()
{
    const char* ini_text= "||||a===1||b===2||||c===3||||||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "===")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

//test when line_seperator is "||" and ini_text include "|||"
void test5()
{
    const char* ini_text= "|||a===1||b===2|||c===3||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "===")) {
        assert(false);
    }

    const std::string& a = parser.Get("|a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("|c", NULL);
    assert(c == "3");
}

//test when key_value_seperator is "==" and ini_text include "==="
void test6()
{
    const char* ini_text= "|||a===1||b===2|||c===3||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "==")) {
        assert(false);
    }

    const std::string& a = parser.Get("|a", NULL);
    assert(a == "=1");

    std::string b = parser.Get("b", NULL);
    assert(b == "=2");

    const std::string& c = parser.Get("|c", NULL);
    assert(c == "=3");

    const std::string& d = parser.Get("c", NULL);
    assert(d == "");
}

//test one special section
void test7()
{
    const char* ini_text= "[host1]\na=1\nb=2";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("host1", "a", NULL);
    assert(a == "1");

    std::string b = parser.Get("host1", "b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("host1", "c", NULL);
    assert(c == "");
}

//test default and special section
void test8()
{
    const char* ini_text= "\na=1\nb=2\nc=3\n[host1]\na=4\nb=5\nd=8[host2]\na=6\nb=7";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    bool isFound = false;
    const std::string& a = parser.Get("a", &isFound);
    assert(a == "1");
    assert(isFound == true);

    isFound = false;
    std::string b = parser.Get("b", &isFound);
    assert(b == "2");
    assert(isFound == true);

    isFound = false;
    const std::string& c = parser.Get("c", &isFound);
    assert(c == "3");
    assert(isFound == true);

    isFound = true;
    const std::string& d = parser.Get("d", &isFound);
    assert(d == "");
    assert(isFound == false);

    isFound = false;
    const std::string& a1 = parser.Get("host1", "a", &isFound);
    assert(a1 == "4");
    assert(isFound == true);

    isFound = false;
    std::string b1 = parser.Get("host1", "b", &isFound);
    assert(b1 == "5");
    assert(isFound == true);

    isFound = false;
    const std::string& c1 = parser.Get("host1", "c", &isFound);
    assert(c1 == "3");
    assert(isFound == true);

    isFound = false;
    const std::string& d1 = parser.Get("host1", "d", &isFound);
    assert(d1 == "8");
    assert(isFound == true);

    isFound = false;
    const std::string& a2 = parser.Get("host2", "a", &isFound);
    assert(a2 == "6");
    assert(isFound == true);

    isFound = false;
    std::string b2 = parser.Get("host2", "b", &isFound);
    assert(b2 == "7");
    assert(isFound == true);

    isFound = false;
    const std::string& c2 = parser.Get("host2", "c", &isFound);
    assert(c2 == "3");
    assert(isFound == true);

    isFound = true;
    const std::string& d2 = parser.Get("host2", "d", &isFound);
    assert(d2 == "");
    assert(isFound == false);
}

//test read ini file
void test9()
{
    qh::INIParser parser;
    if (!parser.Parse("./ini_file")) {
        assert(false);
    }

    bool isFound = false;
    const std::string& a = parser.Get("a", &isFound);
    assert(a == "1");
    assert(isFound == true);

    isFound = false;
    std::string b = parser.Get("b", &isFound);
    assert(b == "2");
    assert(isFound == true);

    isFound = true;
    const std::string& c = parser.Get("c", &isFound);
    assert(c == "");
    assert(isFound == false);

    isFound = false;
    const std::string& name = parser.Get("owner", "name", &isFound);
    assert(name == "John Doe");
    assert(isFound == true);

    isFound = false;
    const std::string& organization = parser.Get("owner", "organization", &isFound);
    assert(organization == "Acme Widgets Inc.");
    assert(isFound == true);

    isFound = false;
    const std::string& server = parser.Get("database", "server", &isFound);
    assert(server == "192.0.2.62");
    assert(isFound == true);

    isFound = false;
    const std::string& port = parser.Get("database", "port", &isFound);
    assert(port == "143");
    assert(isFound == true);

    isFound = false;
    const std::string& file = parser.Get("database", "file", &isFound);
    assert(file == "\"payroll.dat\"");
    assert(isFound == true);
}

void test10()
{
    const char* ini_text= "";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    bool isFound = true;
    const std::string& a = parser.Get("a", &isFound);
    assert(a == "");
    assert(isFound == false);
}

void test11()
{
    const char* ini_text= NULL;
    qh::INIParser parser;
    if (!parser.Parse(ini_text, 0, "\n", "=")) {
        assert(false);
    }

    bool isFound = true;
    const std::string& a = parser.Get("a", &isFound);
    assert(a == "");
    assert(isFound == false);
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();

    return 0;
}


