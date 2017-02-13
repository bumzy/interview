string 工程

请实现std::string类的主要函数接口，并与其保持功能行为的一致性。函数声明以及写作头文件中。部分实现也做了，但可能 *不完全正确* 。

请面试者实现这个类，并补充尽可能详尽的单元测试用例，越多越好，代码逻辑路径覆盖越全越好。

请认真对待，仔细考虑每一个细节问题。

做完每个项目，请回答一下问题：
1. 是否有资源泄露？例如内存泄露、文件句柄打开而未关闭等等
答：无资源泄露
经 valgrind --tool=memcheck ./unittest_string 检查无内存泄露
未使用文件句柄

2. 尽可能详细的说清楚每个函数的时间复杂度和空间复杂度。例如INI解析器Parse过程的时间复杂度是多少？
string()                                        时间复杂度O(1) 空间复杂度O(1)
string(const char* s)                           时间复杂度O(n) 空间复杂度O(n)
string(const char* s, size_t len)               时间复杂度O(n) 空间复杂度O(n)
string(const string& rhs)                       时间复杂度O(n) 空间复杂度O(n)
string& operator=(const string& rhs)            时间复杂度O(n) 空间复杂度O(n)
~string()                                       时间复杂度O(n) 空间复杂度O(1)
size_t size() const                             时间复杂度O(1) 空间复杂度O(1)
const char* data() const                        时间复杂度O(1) 空间复杂度O(1)
const char* c_str() const                       时间复杂度O(1) 空间复杂度O(1)
char& operator[](size_t index)                  时间复杂度O(1) 空间复杂度O(1)
