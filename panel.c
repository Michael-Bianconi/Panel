/**
 * @author Michael Bianconi
 * @since 04-23-2019
 *
 * Source code for panel.h.
 */

#include "panel.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

/// ===========================================================================
/// Mutex
/// ===========================================================================

pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER;


/// ===========================================================================
/// Static function definitions
/// ===========================================================================

/**
 * Sets the cursor's position to the given position.
 *
 * @param row Y coordinate.
 * @param col X coordinate.
 */
static void setCursorPosition( int row, int col) {
    printf( "\033[%d;%dH", row, col );
}

/// ===========================================================================
/// Function definitions
/// ===========================================================================

void clearTerminal() {
    printf( "\033[2J" );
    setCursorPosition(1, 1);
    fflush( stdout );
}


Panel createPanel(const size_t position, const size_t width)
{
	Panel p = malloc(sizeof(struct Panel_s));
	p->position = position;
	p->width = width;
	p->row = 1;
	p->col = 0;
	return p;
}

void pprintf(Panel p, const char* format, ...)
{
	// thread safety
	pthread_mutex_lock(&printMutex);

    va_list args;
    int length;
    static char getLengthArray[1];

    // Get length of the string
    va_start(args, format);
    length = vsprintf(getLengthArray, format, args);
    va_end(args);

    // Copy the string into the buffer
    va_start(args, format);
    char line[length+1];
	vsprintf(line, format, args);

	// Initialize cursor position
	int n = 0;
	setCursorPosition(p->row, p->col+p->position+1);

	// For each character in the string
	while(line[n])
	{
		// Newline, set cursor position
		if (p->col == p->width || line[n] == '\n')
		{
			p->row++;
			p->col = 0;
			setCursorPosition(p->row, p->position+1);

		}

		// Do not actually print newlines
		if (line[n] != '\n')
		{
			putchar(line[n]);
			p->col++;
		}

		n++;

	}

	fflush(stdout);
	va_end(args);

	pthread_mutex_unlock(&printMutex);
}