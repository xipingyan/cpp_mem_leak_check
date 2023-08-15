#include <iostream>
#include <memory>
using namespace std;

void *operator new(size_t size);
void operator delete(void *ptr);

void set_flag_close();
