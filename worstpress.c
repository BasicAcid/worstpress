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

struct HuffmanNode
*create_huffman_node(char symbol, int frequency)
{
    struct HuffmanNode* new_node = malloc(sizeof(struct HuffmanNode));
    new_node->symbol = symbol;
    new_node->frequency = frequency;
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct HuffmanNode
*build_huffman_tree(struct FreqNode *frequencyTable, int tableSize)
{
    // Create an array of Huffman nodes and initialize it with the characters and frequencies.
    struct HuffmanNode *huffman_nodes[tableSize];
    for(int i = 0; i < tableSize; ++i)
        huffman_nodes[i] = create_huffman_node(frequencyTable[i].symbol, frequencyTable[i].frequency);

    // Build the Huffman Tree.
    while(tableSize > 1) {
        // Find the two nodes with the lowest frequencies.
        int min1 = 0, min2 = 1;
        if(huffman_nodes[min1]->frequency > huffman_nodes[min2]->frequency)
        {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for(int i = 2; i < tableSize; ++i)
        {
            if(huffman_nodes[i]->frequency < huffman_nodes[min1]->frequency)
            {
                min2 = min1;
                min1 = i;
            }
            else if(huffman_nodes[i]->frequency < huffman_nodes[min2]->frequency)
            {
                min2 = i;
            }
        }

        // Create a new internal node with the sum of frequencies of the two lowest nodes.
        struct HuffmanNode *internalNode = create_huffman_node('\0', huffman_nodes[min1]->frequency + huffman_nodes[min2]->frequency);
        internalNode->left = huffman_nodes[min1];
        internalNode->right = huffman_nodes[min2];

        // Replace the two lowest nodes with the new internal node.
        huffman_nodes[min1] = internalNode;
        huffman_nodes[min2] = huffman_nodes[tableSize - 1];

        tableSize--;
    }

    // The remaining node is the root of the Huffman Tree.
    return huffman_nodes[0];
}

void
generate_huffman_codes(struct HuffmanNode *root, char *code, int codeIndex)
{
    if (root == NULL)
        return;

    // Assign '0' to the left edge and '1' to the right edge.
    if(root->left != NULL)
    {
        code[codeIndex] = '0';
        generate_huffman_codes(root->left, code, codeIndex + 1);
    }

    if(root->right != NULL)
    {
        code[codeIndex] = '1';
        generate_huffman_codes(root->right, code, codeIndex + 1);
    }

    // If it's a leaf node (contains a character), print the character and its code.
    if(root->left == NULL && root->right == NULL)
    {
        printf("%c: %s\n", root->symbol, code);
    }
}

void
compress_huffman(struct FreqNode *frequencyTable, int table_size, const char *inputString)
{
    struct HuffmanNode *huffmanTree = build_huffman_tree(frequencyTable, table_size);

    // Generate Huffman codes for each character.
    char code[256]; // Assuming ASCII characters.
    generate_huffman_codes(huffmanTree, code, 0);

    // Compress the input string using Huffman codes.
    printf("\nCompressed String:\n");
    for(int i = 0; inputString[i] != '\0'; ++i)
    {
        // Find the corresponding Huffman code for the character.
        for(int j = 0; j < table_size; ++j)
        {
            if(frequencyTable[j].symbol == inputString[i])
            {
                printf("%d ", code[j]);
                break;
            }
        }
    }
    free(huffmanTree);
}


struct FreqNode
*calculateFrequency(const char *input_string, int *table_size)
{
    struct FreqNode *frequency_table = NULL;

    if(input_string == NULL)
        return frequency_table;

    long unsigned int char_count = 0;
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
    const char *input_string = "This is some kind of input with some redudancies I guess you know man, like, seee.";

    int table_size;

    struct FreqNode *result_table = calculateFrequency(input_string, &table_size);

    for(int i = 0; i < table_size; ++i)
        printf("%c: %d\n", result_table[i].symbol, result_table[i].frequency);

    compress_huffman(result_table, table_size, input_string);

    free(result_table);

    return 0;
}
