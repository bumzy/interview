题目内容请通过图片链接阅读：https://github.com/zieckey/interview/blob/master/climber_problem/The%20problem.png


做完每个项目，请回答一下问题：
1. 是否有资源泄露？例如内存泄露、文件句柄打开而未关闭等等
答：无资源泄露
经 valgrind --tool=memcheck ./unittest_climber 检查无内存泄露
未使用文件句柄

2. 尽可能详细的说清楚每个函数的时间复杂度和空间复杂度。例如INI解析器Parse过程的时间复杂度是多少？
输入用例长方形个数为n，时间复杂度O(nlog(n))，空间复杂度O(n)
