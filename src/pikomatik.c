#include <gtk/gtk.h>

#include "pikomatik.h"
#include "menu.h"
#include "delay.h"
#include "pin_diagrams.h"

GlobalWidgets *global_widgets;

int main (int argc, char *argv[])
{    
    GtkWidget *window_main;
    GtkWidget *vbox_layout_main;
    GtkWidget *notebook_main;
    GtkWidget *page_delay, *page_timer, *page_pin_diagrams;

    gtk_init (&argc, &argv);
    
    /* Arrange the global widgets */
    
    global_widgets = g_malloc (sizeof (GlobalWidgets));

    window_main = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    vbox_layout_main = gtk_vbox_new (FALSE, 0);
    notebook_main = gtk_notebook_new ();
    
    global_widgets->window_main = window_main;
    global_widgets->vbox_layout_main = vbox_layout_main;
    global_widgets->notebook_main = notebook_main;

    gtk_window_set_title (GTK_WINDOW (window_main), "Pikomatik");
    g_signal_connect (G_OBJECT (window_main), "destroy", G_CALLBACK (quit), NULL);
    gtk_widget_set_size_request (window_main, -1, 400);
    gtk_window_set_position (GTK_WINDOW (window_main), GTK_WIN_POS_CENTER);
    
    gtk_container_add (GTK_CONTAINER (window_main), vbox_layout_main);

    create_menus ();
    
    gtk_box_pack_start_defaults (GTK_BOX (vbox_layout_main), notebook_main);
    
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook_main), FALSE);
    
    page_delay = create_page_delay ();
    page_timer = gtk_label_new ("Geri Sayım");
    page_pin_diagrams = create_page_pin_diagrams ();

    gtk_notebook_append_page (GTK_NOTEBOOK (notebook_main), page_delay, gtk_label_new ("Gecikme"));
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook_main), page_timer, gtk_label_new ("Geri Sayım"));
    gtk_notebook_append_page(GTK_NOTEBOOK (notebook_main), page_pin_diagrams, gtk_label_new ("Bacak Şemaları"));

    gtk_widget_show_all (window_main);

    gtk_main ();

    return 0;
}

void quit (GtkWidget *window_main, gpointer data)
{
    gtk_main_quit ();
}
