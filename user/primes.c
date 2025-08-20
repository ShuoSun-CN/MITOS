#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define N 280
void primes(int) __attribute__((noreturn));
void primes(int pr)
{
    int p[2];
    pipe(p);
    int nx;
    int x;
    int r = read(pr, &x, sizeof(int));
    if (fork() == 0)
    {
        close(pr);
        close(p[1]);
        if (r)
            primes(p[0]);
        close(p[0]);
    }
    else
    {
        close(p[0]);
        if (r >= 0 && x>0)
            printf("prime %d\n", x);
        if (r)
        {
            while (1)
            {
                r = read(pr, &nx, sizeof(int));
                if (nx % x != 0)
                    write(p[1], &nx, sizeof(int));
                if (r == 0)
                    break;
            }
        }
        close(pr);
        close(p[1]);
        wait(0);
    }
    exit(0);
}
int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        primes(p[0]);
        close(p[0]);
    }
    else
    {
        close(p[0]);
        printf("prime %d\n", 2);
        for (int i = 2; i < N; i++)
        {
            if (i % 2 != 0)
            {
                write(p[1], &i, sizeof(int));
            }
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}