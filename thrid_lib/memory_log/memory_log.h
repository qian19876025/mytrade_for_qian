#ifndef __MEMORY_LOG__
#define __MEMORY_LOG__
#include <stdint.h>

class Memory_log {
    private:
    char *buff;
    uint32_t buf_size;
    public:
    Memory_log(uint32_t log_size);
    int log_input(char *str,...);
};
extern Memory_log log_module;
#define log log_module.log_input
#endif //__MEMORY_LOG__
