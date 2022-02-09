#include <stdio.h>

#define Debug
#include "coroutine.h"

int main(int argc, char const *argv[])
{

    int i = 0;
    /*control with coroutine*/
    CONTROL({
        if (i > 0)
        {
            goto B;
        }
        if (1)
        {
            goto A;
        }
    });
    /*create the codes with close spare*/
    DEFCODE(A, 1, {
        while (i < 100)
        {
            i += 1;
            printf("%d\n", i);
            goto __CONTROL__;
        }
    });
    DEFCODE(B, 1, {
        while (i != 0 && i > 0)
        {
            i -= 1;
            printf("%d\n",i);
            goto __CONTROL__;
        }
    });
    /*a example with test code block*/
    DEFCODE(test, 1, {
        printf("test.\n");
    })
    EXECUTE(test);
    return 0;
}
