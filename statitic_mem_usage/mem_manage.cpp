#include <iostream>
#include <memory>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;

static bool g_bClose = false;
static std::map<void*, uint64_t>  _mem_map;
static uint64_t _mem_size = 0;
static uint64_t _max_size = 0;
struct my_mem
{
    void* ptr=nullptr;
    size_t sz=0;
};
static size_t g_mem_num = 1024;
static my_mem *g_my_mem = static_cast<my_mem *>(malloc(sizeof(my_mem) * g_mem_num));
static bool g_bInit = []()
{
    memset(g_my_mem, 0, sizeof(my_mem) * g_mem_num);
    return true;
};
static void
remalloc_my_mem()
{
    size_t old_num = g_mem_num;
    my_mem *old_my_mem = g_my_mem;

    g_mem_num *= 2;
    g_my_mem = static_cast<my_mem*>(malloc(sizeof(my_mem) * g_mem_num));
    memcpy(g_my_mem, old_my_mem, sizeof(my_mem) * old_num);

    memset(g_my_mem + old_num * sizeof(my_mem), 0, sizeof(my_mem) * (g_mem_num - old_num));
};

static uint64_t g_cur_idx = 0;
static void record_mem(void*& ptr, size_t& sz) {
    if (g_cur_idx < g_mem_num) {
        g_my_mem[g_cur_idx].ptr = ptr;
        g_my_mem[g_cur_idx].sz = sz;
        for (size_t i = g_cur_idx + 1; i < g_mem_num; i++)
        {
            if (g_my_mem[g_cur_idx].ptr == nullptr)
            {
                continue;
            }
            g_cur_idx = i;
            break;
        }
    }
}

static size_t rm_mem(void*& ptr) {
    for(uint64_t i = 0; i < g_mem_num; i++) {
        if (g_my_mem[i].ptr == ptr)
        {
            auto old_sz = g_my_mem[i].sz;
            g_my_mem[i].ptr = nullptr;
            g_my_mem[i].sz = 0;
            g_cur_idx = std::min(g_cur_idx, i);
            return old_sz;
        }
    }
    return 0;
}

// libc中的定义
void *operator new(size_t size)
{
	void *p = malloc(size);
	record_mem(p, size);
	_mem_size += size;
	_max_size = std::max(_max_size, _mem_size);
	return p;
}
void operator delete(void *ptr)
{
	if (ptr == nullptr)
		return;

	free(ptr);
	_mem_size -= rm_mem(ptr);
	ptr = nullptr;

	printf("Current mem size: %lu, max size: %lu\n", _mem_size, _max_size);
};

void set_flag_close()
{
    for(uint64_t i = 0; i < g_mem_num; i++) {
            if (g_my_mem[i].ptr) {
                std::cout << "Forget to free [" << g_my_mem[i].ptr << ", " << g_my_mem[i].sz << "]\n";
            }
        }
}
