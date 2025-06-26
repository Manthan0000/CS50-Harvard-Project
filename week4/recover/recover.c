#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    char filename[8];
    int file_count = 0;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(filename, "%03i.jpg", file_count);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(input);
                return 1;
            }

            file_count++;
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);

    return 0;
}
