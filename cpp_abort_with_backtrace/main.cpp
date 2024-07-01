#include <iostream>
#include <memory>

// Call boost to print backtrace
#define BOOST_STACKTRACE_USE_ADDR2LINE
#include <boost/stacktrace.hpp>
void print_stacktrace(void)
{
	std::cout << boost::stacktrace::stacktrace();
}

void fun3()
{
	print_stacktrace();
	abort();
	// std::terminate();
}
void fun2()
{
	fun3();
}

void fun1()
{
	fun2();
}
int main(int argc, char **argv)
{
	fun1();
	return 0;
}