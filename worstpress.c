#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct IntArray
{
    unsigned int *data;
    size_t size;
};

struct IntArray
create_dynamic_array(size_t size)
{
    struct IntArray arr;
    arr.data = malloc(size * sizeof(arr));
    arr.size = size;
    return arr;
}

struct FreqNode
{
    char symbol;
    int frequency;
    struct FreqNode *left;
    struct FreqNode *right;
};


int
main()
{



    return 0;
}
