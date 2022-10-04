#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
    #pragma omp parallel num_thread(5)
    {
        int pid = omp_get_thread_num();
        printf("Hello (%d)", pid);
        printf("World (%d) \n", pid);
    }
    return 0;
}
