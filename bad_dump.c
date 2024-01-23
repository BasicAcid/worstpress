#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SYMBOL_COUNT 1024
#define MAX_SIZE 1024

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

void
count_freq(const char *input, int *frequency)
{
    memset(frequency, 0, sizeof(int) * SYMBOL_COUNT);

    while(*input != '\0')
    {
        frequency[ (unsigned char)*input ]++;
        input++;
    }
}

struct IntArray
count_freq2(const char *input)
{
    struct IntArray freq_arr = create_dynamic_array(100);

    while(*input != '\0')
    {
        freq_arr.data[ (unsigned char)*input ]++;
        input++;
    }

    return freq_arr;
}

void min_heapify(struct FreqNode *arr[], int n, int i)
{
    int smallest = i;

    int left_child = (i * 2) + 1;
    int right_child =  (i * 2) + 2;

    // If left child is smaller than root.
    if(left_child < n && arr[left_child]->frequency < arr[smallest]->frequency)
    {
        smallest = left_child;
    }

    // If right child is smaller than the smallest so far.
    if(right_child < n && arr[right_child]->frequency < arr[smallest]->frequency)
    {
        smallest = right_child;
    }

    // If the smallest is not the root, swap it with the root.
    if(smallest != i)
    {
        struct FreqNode *temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        // Recursively heapify the affected subtree.
        min_heapify(arr, n, smallest);
    }
}

int
main()
{
    const char *input = "This is some kind of input with some redudancies I guess you know man, like, seee.";

    struct FreqNode l_freq[MAX_SIZE];

    // int frequency[SYMBOL_COUNT];

    // count_freq(input, frequency);

    /* for(int i = 0; i < SYMBOL_COUNT; i++) */
    /* { */
    /*     if(frequency[i] > 0) */
    /*     { */
    /*         l_freq[i].symbol = i; */
    /*         l_freq[i].frequency = frequency[i]; */
    /*         printf("Symbol '%c' has frequency: %d\n", (char)i, frequency[i]); */
    /*     } */
    /* } */


    struct IntArray better_freqs = count_freq2(input);

    for(int i = 0; i < better_freqs.size; i++)
    {
        if(better_freqs.data[i] > 0)
        {
            better_freqs.data[i] = i;
            l_freq[i].frequency = frequency[i];
            printf("Symbol '%c' has frequency: %d\n", (char)i, frequency[i]);
        }
    }



    /* int test[] = {4,3,9,0,43,2,54,9}; */

    //min_heapify(l_freq, 0, 0);

    /* for(int i = 0; i < 8; i++) */
    /* { */
    /*     printf("%d\n", test[i]); */
    /* } */


    return 0;
}
