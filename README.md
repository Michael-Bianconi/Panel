# Panels

Panels is a thread-safe C utility that allows developers to split their
terminal output into columns. Output can be asynchronously
displayed side-by-side.

## Build

    $ gcc panel.c -lpthread

## Usage

### Test file

    #include "panel.h"
    #include <stdio.h>
    #include <pthread.h>
    #include <unistd.h>

    #define LEFT_PANEL 0    // Left panel starts at the far left
    #define MIDDLE_PANEL 31 // Middle panel starts at the 31st column
    #define RIGHT_PANEL 62  // Right panel starts at the 62nd column
    #define PANEL_WIDTH 30  // All panels are 30 characters wide

    // Holds arguments to pass to run()
    struct args
    {
        Panel panel;
        char* out;
        int delay;
    };

    // Prints out the given string after a delay, 100 times
    static void* run(void* args_v)
    {
        struct args* _args = (struct args*) args_v;

        for (int d = 0; d < 100; d++)
        {
            usleep(_args->delay);
            pprintf(_args->panel, _args->out);
        }

        return NULL;
    }

    int main(int argc, char** argv)
    {
        (void) argc;
        (void) argv;

        clearTerminal();

        // Create 3 panels and 3 threads that will run side by side
        Panel left = createPanel(LEFT_PANEL, PANEL_WIDTH);
        Panel middle = createPanel(MIDDLE_PANEL, PANEL_WIDTH);
        Panel right = createPanel(RIGHT_PANEL, PANEL_WIDTH);

        pthread_t lthread;
        pthread_t mthread;
        pthread_t rthread;

        struct args largs = {left, "(a)", 100000};
        struct args margs = {middle, "(bb)", 110000};
        struct args rargs = {right, "(ccc)", 120000};

        pthread_create(&lthread, NULL, &run, (void*) &largs);
        pthread_create(&mthread, NULL, &run, (void*) &margs);
        pthread_create(&rthread, NULL, &run, (void*) &rargs);

        pthread_join(lthread, NULL);
        pthread_join(mthread, NULL);
        pthread_join(rthread, NULL);

        free(left);
        free(middle);
        free(right);

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

        return 0;
    }

### Output

    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
    (a)(a)(a)(a)(a)(a)(a)(a)(a)(a) b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                   (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                   b)(bb)(bb)(bb)(bb)(bb)(bb)(bb) (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                   (bb)(bb)(bb)(bb)(bb)(bb)(bb)(b (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                   b)(bb)(bb)                     (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                                                  (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                                                  (ccc)(ccc)(ccc)(ccc)(ccc)(ccc)
                                                                  (ccc)(ccc)(ccc)(ccc)


## Functions

### void clearTerminal()

Clears all previous input from the terminal and sets the cursor to the
top left. Should be called <i>once</i> before printing to panels.

### Panel createPanel(size_t position, size_t width)

Allocates memory for a new Panel and sets its attributes. Remember to free()!

<i>position:</i> Index of the panel's leftmost column in the terminal.

<i>width:</i> Number of characters to print to the panel before inserting
a new line.

<i>return:</i> Returns a malloc'd Panel.

### void pprintf(Panel panel, const char* format, ...)

Prints to the given panel. Output will not exceed the
width of the panel. If it does, a newline is inserted.

<i>panel:</i> Panel to print to.

<i>format:</i> Output to print, can be formatted with var args.

<i>var args:</i> Formats given string.
