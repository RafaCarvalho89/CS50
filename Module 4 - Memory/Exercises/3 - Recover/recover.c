#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recorver image\n");
        return 1;
    }

    char *input_file = argv[1];

    FILE *input = fopen(input_file, "r");

    if (input == NULL)
    {
        printf("Error: '%s' can not be open\n", input_file);
        return 1;
    }


    BYTE buffer[512];
    int count = 0;
    FILE *output = NULL;
    char filename[9];

    while (fread(buffer, 512, 1, input) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count != 0)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count++;
        }

        if (count != 0)
        {
            fwrite(&buffer, 512, 1, output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;

    /*
    FILE *f = fopen(argv[1], "r");

    // read data file
    fread(buffer, 512, number, inptr);

    (buffer[3] & 0xf0) == 0xe0

    sprintf(filename, "%03i.jpeg", 2);
    FILE *img = fopen(filename, "w");

    // write data to a file
    fwrite(data, size, number, outptr);
    */

}