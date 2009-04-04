#ifndef PIKOMATIK_H
#define PIKOMATIK_H

#include <gtk/gtk.h>

enum
{
    PAGE_DELAY,
    PAGE_TIMER,
    PAGE_PIN_DIAGRAMS
};

typedef struct
{
    GtkWidget *window_main;
    GtkWidget *vbox_layout_main;
    GtkWidget *notebook_main;
} GlobalWidgets;

void quit (GtkWidget*, gpointer);

#endif /* PIKOMATIK_H */
