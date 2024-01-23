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

struct IntArray
count_freq(const char *input)
{
    struct IntArray freq_arr = create_dynamic_array(100);

    while(*input != '\0')
    {
        freq_arr.data[ (unsigned char)*input ]++;
        input++;
    }
    return freq_arr;
}

void
print_dynamic_array(struct IntArray arr)
{
    for(size_t i = 0; i < arr.size; i++)
        printf("%f\n", arr.data[i]);
}

int
main()
{
    //const char *input = "This is some kind of input with some redudancies I guess you know man, like, seee.";

    const char *input = "hello";

    struct IntArray better_freqs = count_freq(input);

    print_dynamic_array(better_freqs);

    return 0;
}
