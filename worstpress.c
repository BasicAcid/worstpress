#include <stdio.h>
#include <string.h>

#define SYMBOL_COUNT 1024

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
        frequency[ (unsigned char)*input ]++;  // Unsigned char to handle extended ASCII.
        input++;
    }
}

void min_heapify(int arr[], int n, int i)
{
    int smallest = i;

    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    // If left child is smaller than root.
    if(left_child < n && arr[left_child] < arr[smallest])
    {
        smallest = left_child;
    }

    // If right child is smaller than the smallest so far.
    if(right_child < n && arr[right_child] < arr[smallest])
    {
        smallest = right_child;
    }

    // If the smallest is not the root, swap it with the root.
    if(smallest != i)
    {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        // Recursively heapify the affected subtree.
        min_heapify(arr, n, smallest);
    }
}

int
main()
{
    const char* input = "This is some kind of input with some redudancies I guess you know man, like, seee.";

    struct FreqNode l_freq[] = {};

    int frequency[SYMBOL_COUNT];

    count_freq(input, frequency);

    for(int i = 0; i < SYMBOL_COUNT; i++)
    {
        if(frequency[i] > 0)
        {
            l_freq[i].symbol = i;
            l_freq[i].frequency = frequency[i];
            printf("Symbol '%c' has frequency: %d\n", (char)i, frequency[i]);
        }
   }

    return 0;
}
