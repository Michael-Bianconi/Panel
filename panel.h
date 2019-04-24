/**
 * @author Michael Bianconi
 * @since 04-23-2019
 */

#ifndef PANEL_H
#define PANEL_H

#include <stdlib.h>

/// ===========================================================================
/// Structure definitions
/// ===========================================================================

struct Panel_s
{
	size_t position; // starting column
	size_t width; // number of characters that can be printed before '\n'
	size_t row; // current row
	size_t col; // current col
};

/// ===========================================================================
/// Typedefs
/// ===========================================================================

typedef struct Panel_s* Panel;

/// ===========================================================================
/// Function declarations
/// ===========================================================================


/**
 * Clears the terminal.
 * Must be called prior to the first pprintf().
 */
void clearTerminal();


/**
 * Will allocate memory for a new Panel.
 *
 * @param pos Position of the first column in the panel.
 * @param width Number of characters that will be printed before
 *              a newline is inserted. Must be greater than 0.
 * @return Returns malloc'd Panel.
 */
Panel createPanel(const size_t pos, const size_t width);


/**
 * Prints to the given panel. Has the same format as printf().
 * A newline will be inserted if the string exceeds the width
 * of the panel.
 *
 * @param p Panel to print to.
 * @param format String to print
 */
void pprintf(Panel p, const char* format, ...);

#endif
