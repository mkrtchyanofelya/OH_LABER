#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void check_addr_range(unsigned long start, unsigned long end, void* addr, const char* var_name);
void check_for_function(unsigned long start, unsigned long end);

int global_var;

int main() {
    pid_t pid = getpid();  // 1. get PID
    printf("PID: %d\n", pid);

    int a = 42;
    double b = 3.14;

    printf("Original values: a=%d, b=%f\n", a, b);
    printf("Addresses: &a=%p, &b=%p\n", (void*)&a, (void*)&b);

    char maps_path[64];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);

    FILE *maps = fopen(maps_path, "r");
    unsigned long stack_start = 0, stack_end = 0;
    unsigned long heap_start = 0, heap_end = 0;
    
    char line[256];
    while (fgets(line, sizeof(line), maps)) {
        if (strstr(line, "[heap]")) {
            sscanf(line, "%lx-%lx", &heap_start, &heap_end);
        } else if (strstr(line, "[stack]")) {
            sscanf(line, "%lx-%lx", &stack_start, &stack_end);
            break;
        }
    }

    fclose(maps);
    printf("Stack: 0x%lx - 0x%lx\n", stack_start, stack_end);
    printf("Heap: 0x%lx - 0x%lx\n", heap_start, heap_end);

    check_addr_range(stack_start, stack_end, (void*)&global_var, "global_var");

    check_addr_range(stack_start, stack_end, (void*)&a, "a");

    check_addr_range(stack_start, stack_end, (void*)&b, "b");

    {
        char scope_var = 'a';
        
        check_addr_range(stack_start, stack_end, (void*)&scope_var, "scope_var");
    }
    
    float* dyn_fl = (float*)malloc(sizeof(float));
    
    check_addr_range(heap_start, heap_end, (void*)dyn_fl, "dyn_fl");

    check_for_function(stack_start, stack_end);

    scanf("%d", &a);

    return 0;
}

void check_addr_range(unsigned long start, unsigned long end, void* addr, const char* var_name) {
    printf("Addresses: &%s=%p\n", var_name, addr);
    
    unsigned long long_addr = (unsigned long)addr;

    if (start <= long_addr && long_addr <= end) {
        printf("%s address is in right range!\n", var_name);
    } else {
        printf("Error: %s address isn't in right range!\n", var_name);
    }
}

void check_for_function(unsigned long start, unsigned long end) {
    int func_var;
    
    check_addr_range(start, end, (void*)&func_var, "func_var");
}
