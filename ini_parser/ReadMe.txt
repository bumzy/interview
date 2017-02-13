请面试者用C++实现这个INI解析器

这个INI解析器可以直接解析内存数据和磁盘文件。
举个简单例子：

const char* ini_text= "a=1\nb=2\n";
qh::INIParser parser;
if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
    //TODO error process
}

const std::string& a = parser.Get("a", NULL);
assert(a == "1");

std::string b = parser.Get("a", NULL);
assert(b == "2");

const std::string& c = parser.Get("c", NULL);
assert(c == "");

	这个ini_text就是内存数据。调用代码如上。
	硬盘数据可以通过读文件的api读入内存而变为内存数据。

考察点：
-          INI核心解析功能的完备性
-          测试用例覆盖率尽量高
-          代码编程风格比较友好(参考google的C++编程规范)
-          代码可阅读性、可维护性比较好
-          Linux下开发和测试
请将源码、测试用例代码、Makefile等一并打包(注意包文件名上带上自己的姓名)发给我们。

1. 是否有资源泄露？例如内存泄露、文件句柄打开而未关闭等等
答：无资源泄露
经 valgrind --tool=memcheck ./unittest_string 检查无内存泄露
std::ifstream ini_file文件句柄已关闭

2. 尽可能详细的说清楚每个函数的时间复杂度和空间复杂度。例如INI解析器Parse过程的时间复杂度是多少？
ini文件长度为n
INIParser()                                                     时间复杂度O(1) 空间复杂度O(1)
~INIParser()                                                    时间复杂度O(1) 空间复杂度O(1)
bool Parse(const std::string& ini_file_path)                    时间复杂度O(n) 空间复杂度O(n)
bool Parse(const char* ini_data, size_t ini_data_len,           时间复杂度O(n) 空间复杂度O(n)
        const std::string& line_seperator,
        const std::string& key_value_seperator)
const std::string& Get(const std::string& key, bool* found)     时间复杂度O(1) 空间复杂度O(1)
const std::string& Get(const std::string& section,              时间复杂度O(1) 空间复杂度O(1)
        const std::string& key, bool* found);

注：使用了Tokener、unordered_map类，Tokener添加了std::string nextString( const std::string& quote )函数
