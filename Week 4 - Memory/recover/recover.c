#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover memory_card\n");
        return 1;
    }

    // Open the memory card
    FILE *memory_card = fopen(argv[1], "r");
    if (memory_card == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 2;
    }

    uint8_t buffer[BLOCK_SIZE]; // Use the defined constant

    // While there's still data left to read from the memory card
    int jpg_count = 0;
    FILE *jpg_file = NULL; // File pointer for the JPEG files
    char filename[8];      // Buffer for filename storage

    while (fread(buffer, 1, BLOCK_SIZE, memory_card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG file if it's open
            if (jpg_file != NULL)
            {
                fclose(jpg_file);
            }

            // Form new filename for each new JPEG detected
            sprintf(filename, "%03i.jpg", jpg_count++);
            jpg_file = fopen(filename, "w");
            if (jpg_file == NULL)
            {
                fprintf(stderr, "Could not create file %s.\n", filename);
                return 2; // Exit if file cannot be created
            }
        }

        // If a JPEG file is open, write the current buffer to it
        if (jpg_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg_file);
        }
    }

    // Close any remaining open JPEG file and memory card
    if (jpg_file != NULL)
    {
        fclose(jpg_file);
    }

    fclose(memory_card);

    return 0;
}
