#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FreqNode
{
    char symbol;
    int frequency;
};

// TODO: integrate this into FreqNode.
struct HuffmanNode
{
    char symbol;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

struct HuffmanNode* create_huffman_node(char symbol, int frequency)
{
    struct HuffmanNode* new_node = malloc(sizeof(struct HuffmanNode));
    new_node->symbol = symbol;
    new_node->frequency = frequency;
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct FreqNode
*calculateFrequency(const char* input_string, int* table_size)
{
    struct FreqNode* frequency_table = NULL;

    if(input_string == NULL)
        return frequency_table;

    int char_count = 0;
    for(int i = 0; input_string[i] != '\0'; ++i)
        char_count++;

    frequency_table = malloc(char_count * sizeof(struct FreqNode));

    // Initialize the frequency table with unique characters and set frequencies to zero.
    int table_index = 0;
    for(int i = 0; input_string[i] != '\0'; ++i)
    {
        // Check if the character is already in the frequency table.
        int found = 0;
        for(int j = 0; j < table_index; ++j)
        {
            if(frequency_table[j].symbol == input_string[i])
            {
                found = 1;
                break;
            }
        }

        // If not found, add it to the frequency table.
        if(!found)
        {
            frequency_table[table_index].symbol = input_string[i];
            frequency_table[table_index].frequency = 1;
            table_index++;
        }
        else
        {
            // If found, increment the frequency.
            for(int j = 0; j < table_index; ++j)
            {
                if(frequency_table[j].symbol == input_string[i])
                {
                    frequency_table[j].frequency++;
                    break;
                }
            }
        }
    }

    *table_size = table_index;

    return frequency_table;
}


int
main(void)
{
    const char* input_string = "This is some kind of input with some redudancies I guess you know man, like, seee.";

    int table_size;

    struct FreqNode* result_table = calculateFrequency(input_string, &table_size);

    for(int i = 0; i < table_size; ++i)
        printf("%c: %d\n", result_table[i].symbol, result_table[i].frequency);

    free(result_table);

    return 0;
}
