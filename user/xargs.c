#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argcc, char *argv[])
{
    char *argvv[MAXARG];
    int k = 0;
    for (int i = 1; i < argcc; i++)
    {
        argvv[k++] = argv[i];
    }
    char p[512];
    char *op = p;
    while (read(0, op, 1))
    {
        if (*op == '\n')
        {
            *op = 0;
            argvv[k] = p;
            if (fork() == 0)
            {
                exec(argv[1], argvv);
                exit(0);
            }
            else
            {
                op=p;
                wait(0);
            }
        }
        else
        {
            op++;
        }
    }
    return 0;
}