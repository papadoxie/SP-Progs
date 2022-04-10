#include <more.h>

static char **outputBuffer;
static unsigned int lineNumber;

// Will only be called when SIGWINCH is raised
int initBuffer()
{
    // printf("ROWS: %d\n", window.rows);
    // printf("COLS: %d\n", window.cols);
    window.cols += 10;

    outputBuffer = malloc(sizeof(char *) * window.rows);
    if (outputBuffer == NULL)
    {
        return 0;
    }
    for (unsigned int i = 0; i < window.rows; i++)
    {
        outputBuffer[i] = malloc(sizeof(char) * (window.cols + (NORM_SEQ_SIZE * 2)));
        if (outputBuffer[i] == NULL)
        {
            return 0;
        }
        memset(outputBuffer[i], 0, window.cols);
    }
    return 1;
}

void writeHeader(const char *filename)
{
    strncpy(&outputBuffer[0][0], ESC_DIM, NORM_SEQ_SIZE);
    for (unsigned int i = NORM_SEQ_SIZE; i < (window.cols - NORM_SEQ_SIZE); i++)
    {
        outputBuffer[0][i] = '_';
    }
    strncpy(&outputBuffer[0][window.cols - NORM_SEQ_SIZE], ESC_RESET, NORM_SEQ_SIZE);

    strncpy(&outputBuffer[1][0], ESC_FG_YELLOW, COLOR_SEQ_SIZE);
    strncpy(&outputBuffer[1][COLOR_SEQ_SIZE], filename, strlen(filename));
    strncpy(&outputBuffer[1][COLOR_SEQ_SIZE + strlen(filename)], ESC_RESET, NORM_SEQ_SIZE);

    strncpy(&outputBuffer[2][0], ESC_DIM, NORM_SEQ_SIZE);
    for (unsigned int i = NORM_SEQ_SIZE; i < window.cols - NORM_SEQ_SIZE - 1; i++)
    {
        outputBuffer[2][i] = '_';
    }
    strncpy(&outputBuffer[2][window.cols - NORM_SEQ_SIZE], ESC_RESET, NORM_SEQ_SIZE);
}

void printBuffer()
{
    // Clear the screen before every write
    system("clear");

    // Print the header
    write(STDOUT, outputBuffer[0], window.cols);
    write(STDOUT, ESC_DIM"│      File: "ESC_RESET, NORM_SEQ_SIZE*2 + 14);
    write(STDOUT, outputBuffer[1], window.cols);
    write(STDOUT, "\n", 1);
    write(STDOUT, ESC_DIM"│"ESC_RESET, NORM_SEQ_SIZE*2 + 2);
    write(STDOUT, outputBuffer[2], window.cols);

    
    for (unsigned int i = 3; i < window.rows; i++)
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
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while(1){
        writeHeader(filename);
        printBuffer(outputBuffer);
        sleep(1);
    }

    return EXIT_SUCCESS;
}