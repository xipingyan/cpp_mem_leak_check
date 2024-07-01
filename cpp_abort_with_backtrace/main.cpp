// #include <iostream>
#include <memory>

// Call boost to print backtrace
#define BOOST_STACKTRACE_USE_ADDR2LINE
#include <boost/stacktrace.hpp>
#include <iostream>
void print_stacktrace(void)
{
	std::cout << boost::stacktrace::stacktrace() << std::endl;

	// without: <iostream>
	auto vec = boost::stacktrace::stacktrace().as_vector();
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf(" %ld# %s\n", i, vec[i].name().c_str());
	}
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