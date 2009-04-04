#ifndef MENU_H
#define MENU_H

#include <gtk/gtk.h>

#include "pikomatik.h"

void create_menus ();
void show_page_delay (GtkWidget*, gpointer);
void show_page_timer (GtkWidget*, gpointer);
void show_page_pin_diagrams (GtkWidget*, gpointer);
void show_window_about (GtkWidget*, gpointer);

#endif /* MENU_H */

