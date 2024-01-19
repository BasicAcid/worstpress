#include <stdio.h>
#include <string.h>

#define SYMBOL_COUNT 1024

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

    int frequency[SYMBOL_COUNT];

    count_freq(input, frequency);

    for(int i = 0; i < SYMBOL_COUNT; i++)
    {
        if(frequency[i] > 0)
        {
            printf("Symbol '%c' has frequency: %d\n", (char)i, frequency[i]);
        }
   }

    return 0;
}
