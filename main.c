#include <stdio.h>
#include <string.h>
#include <hash.h>
#include <mac.h>
#include <symmetric.h>

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        printf("Use -help to get information");
        exit(1);
    }
    if (strcmp(argv[1], "hash") == 0)
    {
        hashHandler(argv);
    }
    else if (strcmp(argv[1], "enc") == 0)
    {
        symmetricHandler(argv, 1);
    }
    else if(strcmp(argv[1], "dec") == 0)
    {
        symmetricHandler(argv, 0);
    }
    else if ((strcmp(argv[1], "hmac") == 0) || (strcmp(argv[1], "HMAC") == 0))
    {
        macHandler(argv);
    }
    else if ((strcmp(argv[1], "cmac") == 0) || (strcmp(argv[1], "CMAC") == 0))
    {
        macHandler(argv);
    }
    else if (strcmp(argv[1], "sm2"))
    {
        
    }
    else if (strcmp(argv[1], "ecdsa"))
    {
        
    }
    else if (strcmp(argv[1], "rsa") == 0)
    {
        
    }
    else
    {
        printf("Unknown param %s\n", argv[1]);
    }
    return 0;
}