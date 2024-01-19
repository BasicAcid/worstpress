#include <stdio.h>
#include <string.h>

#define SYMBOL_COUNT 1024

struct FreqNode
{
    char symbol;
    int frequency;
};

void
count_freq(const char* input, int* frequency)
{
    memset(frequency, 0, sizeof(int) * SYMBOL_COUNT);

    while(*input != '\0')
    {
        frequency[ (unsigned char)*input ]++;  // Unsigned char to handle extended ASCII.
        input++;
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
            //printf("Symbol '%c' has frequency: %d\n", (char)i, frequency[i]);
        }
        //printf("Symbol '%c' has frequency: %d\n", l_freq.symbol[i], frequency[i]);
   }

    return 0;
}
