string ����

��ʵ��std::string�����Ҫ�����ӿڣ������䱣�ֹ�����Ϊ��һ���ԡ����������Լ�д��ͷ�ļ��С�����ʵ��Ҳ���ˣ������� *����ȫ��ȷ* ��

��������ʵ������࣬�����価�����꾡�ĵ�Ԫ����������Խ��Խ�ã������߼�·������ԽȫԽ�á�

������Դ�����ϸ����ÿһ��ϸ�����⡣

����ÿ����Ŀ����ش�һ�����⣺
1. �Ƿ�����Դй¶�������ڴ�й¶���ļ�����򿪶�δ�رյȵ�
������Դй¶
�� valgrind --tool=memcheck ./unittest_string ������ڴ�й¶
δʹ���ļ����

2. ��������ϸ��˵���ÿ��������ʱ�临�ӶȺͿռ临�Ӷȡ�����INI������Parse���̵�ʱ�临�Ӷ��Ƕ��٣�
string()                                        ʱ�临�Ӷ�O(1) �ռ临�Ӷ�O(1)
string(const char* s)                           ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(n)
string(const char* s, size_t len)               ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(n)
string(const string& rhs)                       ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(n)
string& operator=(const string& rhs)            ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(n)
~string()                                       ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(1)
size_t size() const                             ʱ�临�Ӷ�O(1) �ռ临�Ӷ�O(1)
const char* data() const                        ʱ�临�Ӷ�O(1) �ռ临�Ӷ�O(1)
const char* c_str() const                       ʱ�临�Ӷ�O(1) �ռ临�Ӷ�O(1)
char& operator[](size_t index)                  ʱ�临�Ӷ�O(1) �ռ临�Ӷ�O(1)
