# malloc
[Subject](https://cdn.intra.42.fr/pdf/pdf/69051/en.subject.pdf)

What’s the deal with malloc? You’ve been using it since the piscine C but it’s not a system call. Find out the workings behind optimum memory management and recode it, as well as free and realloc.

## Result

Success: 119/100

## Installation

Makefile:

```bash
  make
```

## Usage

```bash
./run.sh ./your_binary
```

Your source code example
```C
#include <stdlib.h>

int      main(void)
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
}
```
