# COROUTINE(协程)

异步的操作一般用于IO操作的等待与执行，比如

```c
/* codes */
fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
/* codes */
```

等待读取会占用大量的时间，so，我们很容易想到利用多线程来实现并发甚至是并行操作。

但是这时我们不得不面临一个问题：线程的切换和唤醒操作将同样占用不菲的处理资源开销。

那么有没有一种<u>单线程的异步操作</u>呢？有，这时我们想到了著名的单线程异步操作——JavaScript；

众所周知，JS是单线程的，而且是支持异步操作的。

所以我们引入JS的 “协程操作”；

![什么是协程？——来源于知乎](https://pic1.zhimg.com/v2-6e24040bcefef3325dd2493f99013257_1440w.jpg?source=172ae18b)

所以理论上，我们需求的利用多核的协程是很不现实的。因为这期间核与核之间的操作是相对独立的。

而且睡眠只能停止上下文的交换，不能停止流水的执行。

所以我们还是来研究一下单核的异步操作吧。

```C
#include <stdio.h>

int main(int argc, char const *argv[])
{

    int i = 0;
    /*control with coroutine*/
C:
    if (i > 0)
    {
        goto B;
    }
    if (1)
    {
        goto A;
    }
/*create the codes with close spare*/
if(0){
A:
    while (i < 100)
    {
        i += 1;
        printf("%d\n", i);
        goto C;
    }


B:
    while (i != 0 && i > 0)
    {
        i -= 1;
        printf("%d\n", i);
        goto C;
    }
    // CONTROL(C);
}
    return 0;
}
```

显而易见，我们可以利用`goto`语句来实现跳转的过程，期间我们把代码封装成代码块（code block），但是这个编写的过程我们可以加宏以优化

coroutine.h：

```c
#ifndef __COROUTINE__H__
#define __COROUTINE__H__

#define DEFCODE(__name__,__expression__,...) if(0){__name__:if(__expression__){__VA_ARGS__}};
#define CONTROL(codes...) __CONTROL__: codes;
#define EXECUTE(codes) goto codes;

#endif  //!__COROUTINE__H__
```

现在上面的代码可以改写成：

```c
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

```

显然大大提高了效率。而且加入了`CONTROL()`控制函数，可以在这里添加用于控制的代码块。

跳转至  `__CONTROL__`代码块就是控制函数所在；

这种方式可以显示地避免杂七杂八的函数命名方式，实现了复用和优化。

> *在一个函数中，有且只有一个 `__CONTROL__`多了会打架，不过可以安排*。

可以利用`EXECUTE()`函数来调用定义的代码块。
