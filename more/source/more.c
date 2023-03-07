#include <more.h>

void printBuffer(char **outputBuffer)
{
    // Clear the screen before every write
    system("clear");

    // Print the header
    write(STDOUT, outputBuffer[0], window.cols);
    write(STDOUT, outputBuffer[1], window.cols);
    write(STDOUT, ESC_DIM"│"ESC_RESET, NORM_SEQ_SIZE*2 + 2);
    write(STDOUT, outputBuffer[2], window.cols);

    
    for (unsigned int i = 3; i < TEXT_ROWS; i++)
    {
        write(STDOUT, "\n", 1);
        write(STDOUT, ESC_DIM"│"ESC_RESET, NORM_SEQ_SIZE*2 + 2);
        char line[4];
        snprintf(line, 5, "%4d", i - 2);
        write(STDOUT, line, 4);
        write(STDOUT, ESC_DIM" │"ESC_RESET, NORM_SEQ_SIZE*2 + 3);
        write(STDOUT, outputBuffer[i], window.cols);
    }
}

int more(const char *filename)
{
    lineNumber = 2;
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while(1){
        writeHeader(filename);
        printBuffer(outputBuffer);
        sleep(REFRESH);
    }


    fclose(fptr);
    return EXIT_SUCCESS;
}