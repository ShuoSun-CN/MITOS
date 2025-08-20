#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    int p[2],p2[2];
    pipe(p);
    pipe(p2);

    if (fork() == 0)  
    {
        char a='c';
        read(p[0], &a, 1);  
        printf("%d: received ping\n", getpid());
        a = 'v'; 
        write(p2[1], &a, 1);  
        
    }
    else  
    {
        char aa = 'c';
        write(p[1], &aa, 1);  
        read(p2[0], &aa, 1);  
        printf("%d: received pong\n", getpid());
        
    }

    exit(0);
}
