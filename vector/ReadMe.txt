vector 工程

请实现std::vector类的主要功能。函数声明以及写作头文件中。部分实现也做了，但可能不完全正确。

请面试者实现这个类，并补充尽可能详尽的单元测试用例，越多越好，代码逻辑路径覆盖越全越好。

请认真对待，仔细考虑每一个细节问题。


做完每个项目，请回答一下问题：
1. 是否有资源泄露？例如内存泄露、文件句柄打开而未关闭等等
答：无资源泄露
经 valgrind --tool=memcheck ./unittest_vector 检查无内存泄露
未使用文件句柄

2. 尽可能详细的说清楚每个函数的时间复杂度和空间复杂度。例如INI解析器Parse过程的时间复杂度是多少？
vector()                                        时间复杂度O(1) 空间复杂度O(1)
vector( size_t n, const T& value = T())         时间复杂度O(n) 空间复杂度O(n)
vector( const vector<T>& rhs )                  时间复杂度O(n) 空间复杂度O(n)
vector<T>& operator=(const vector<T>& rhs)      时间复杂度O(n) 空间复杂度O(n)
~vector()                                       时间复杂度O(n) 空间复杂度O(1)
size_t size() const                             时间复杂度O(1) 空间复杂度O(1)
size_t capacity() const                         时间复杂度O(1) 空间复杂度O(1)
T& operator[](size_t index)                     时间复杂度O(1) 空间复杂度O(1)
void push_back(const T& element);               时间复杂度O(n) 空间复杂度O(n)
void pop_back(T& element)                       时间复杂度O(1) 空间复杂度O(1)
void resize(size_t size)                        时间复杂度O(n) 空间复杂度O(n)
void reserve(size_t capacity)                   时间复杂度O(n) 空间复杂度O(n)
void clear()                                    时间复杂度O(1) 空间复杂度O(1)
bool empty() const                              时间复杂度O(1) 空间复杂度O(1)
