#include "scan.h"

#include <string>

namespace scan
{
	static unsigned long long g_base = 0;
	static unsigned long long g_size = 0;
}

void scan::set_data(unsigned long long base, unsigned long long size)
{
	g_base = base;
	g_size = size;
}

unsigned long long scan::search(char* pattern, char* mask)
{
    unsigned long long pattern_size = strlen((char*)mask);
    for (int i = 0; i < g_size; i++)
    {
        bool match = true;
        for (int j = 0; j < pattern_size; j++)
        {
            if (*(char*)((uintptr_t)g_base + i + j) != pattern[j] && mask[j] != '?')
            {
                match = false;
                break;
            }
        }
        if (match) return (g_base + i);
    }
    return 0;
}
