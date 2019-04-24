# Panels

Panels is a C utility that allows developers to split their
terminal output into columns. Output can be asynchronously
displayed side-by-side.

## Usage

    #include "panel.h"
    #define LEFT_PANEL 0	// Left panel starts at the far left
    #define RIGHT_PANEL 31  // Right panel starts at the 31st column
    #define PANEL_WIDTH 30	// Both panels are 30 characters wide

    clearTerminal(); // Clear the terminal to get right of previous output

    Panel left = createPanel(LEFT_PANEL, PANEL_WIDTH);
    Panel right = createPanel(RIGHT_PANEL, PANEL_WIDTH);

    char* vararg = "right";

    pprintf(left, "This is the left panel!");
    pprintf(right, "Let's print 'right': %s!", vararg);

    printf("\n"); // Reset the command prompt

    free(left);
    free(right);

## Functions

#### void clearTerminal()

Clears all previous input from the terminal and sets the cursor to the
top left. Should be called <i>once</i> before printing to panels.

    clearTerminal();

#### Panel createPanel(size_t position, size_t width)

Allocates memory for a new Panel and sets its attributes. Remember to free()!

<b>position:</b> Index of the panel's leftmost column in the terminal.

<b>width</b> Number of characters to print to the panel before inserting
a new line.

<b>return:</b> Returns a malloc'd Panel.

#### void pprintf(Panel panel, const char* format, ...)

Prints to the given panel. Output will not exceed the
width of the panel. If it does, a newline is inserted.

<b>panel</b> Panel to print to.

<b>format</b> Output to print, can be formatted with var args.

<b>var args</b> Formats given string.


