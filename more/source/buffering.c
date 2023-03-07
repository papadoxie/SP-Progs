#include <buffering.h>

// Index of header underlines
#define HEADER_ROW1 0
#define HEADER_ROW2 1
#define HEADER_ROW3 2

#define HEADER_FILENAME "│      File: "
#define HEADER_FILENAME_SIZE strlen(HEADER_FILENAME) + 1
#define HEADER_ROW2_TEXT_ESC NORM_SEQ_SIZE + HEADER_FILENAME_SIZE
#define HEADER_ROW2_TEXT_START HEADER_ROW2_TEXT_ESC + COLOR_SEQ_SIZE
#define HEADER_ROW2_TEXT_SIZE window.cols - HEADER_ROW2_TEXT_START - NORM_SEQ_SIZE - 1

#define HEADER_LINE_COLS window.cols - NORM_SEQ_SIZE
#define HEADER_LINE_END HEADER_LINE_COLS

unsigned int lineNumber = 2;
char **outputBuffer = NULL;

// Will only be called when SIGWINCH is raised
int initBuffer(void)
{
    // Debug printfs
    // printf("ROWS: %d\n", window.rows);
    // printf("COLS: %d\n", window.cols);

    outputBuffer = malloc(sizeof(char *) * window.rows);
    if (outputBuffer == NULL)
    {
        return 0;
    }
    for (unsigned int i = 0; i < window.rows; i++)
    {
        outputBuffer[i] = malloc(sizeof(char) * (window.cols + SEQ_SIZE));
        if (outputBuffer[i] == NULL)
        {
            perror("Error allocating screen buffer");
            return EXIT_FAILURE;
        }
        memset(outputBuffer[i], 0, window.cols);
    }
    return 1;
}

void deleteBuffer()
{
    // First call to sigwinch handler will attempt to dereference a null ptr
    // Buffer is allocated when more() is called
    if (outputBuffer == NULL)
    {
        return;
    }
    free(outputBuffer);
}

void writeHeader(const char *filename)
{
    // First row of header
    if (window.rows < 1)
    {
        return;
    }
    strncpy(&outputBuffer[HEADER_ROW1][0], ESC_DIM, NORM_SEQ_SIZE);
    for (unsigned int i = NORM_SEQ_SIZE; i < HEADER_LINE_COLS; i++)
    {
        outputBuffer[HEADER_ROW1][i] = '_';
    }
    strncpy(&outputBuffer[HEADER_ROW1][HEADER_LINE_END], ESC_RESET, NORM_SEQ_SIZE);

    // Second row of header
    if (window.rows < 2)
    {
        return;
    }
    strncpy(&outputBuffer[HEADER_ROW2][0], ESC_DIM, NORM_SEQ_SIZE);
    strncpy(&outputBuffer[HEADER_ROW2][NORM_SEQ_SIZE], HEADER_FILENAME, HEADER_FILENAME_SIZE);
    strncpy(&outputBuffer[HEADER_ROW2][HEADER_ROW2_TEXT_ESC], ESC_FG_YELLOW, COLOR_SEQ_SIZE);
    int written = strlen(strncpy(&outputBuffer[HEADER_ROW2][HEADER_ROW2_TEXT_START], filename, HEADER_ROW2_TEXT_SIZE));
    strncpy(&outputBuffer[HEADER_ROW2][HEADER_ROW2_TEXT_START + written], ESC_RESET "\n", NORM_SEQ_SIZE + 1);

    // Third row of header
    if (window.rows < 3)
    {
        return;
    }
    strncpy(&outputBuffer[2][0], ESC_DIM, NORM_SEQ_SIZE);
    for (unsigned int i = NORM_SEQ_SIZE; i < window.cols - NORM_SEQ_SIZE - 1; i++)
    {
        outputBuffer[2][i] = '_';
    }
    strncpy(&outputBuffer[2][window.cols - NORM_SEQ_SIZE], ESC_RESET, NORM_SEQ_SIZE);
}

void at_sigwinch(void)
{
    deleteBuffer();
}

void post_sigwinch(void)
{
    initBuffer();
}