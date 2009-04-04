#include <gtk/gtk.h>

#include "pikomatik.h"
#include "menu.h"

extern GlobalWidgets *global_widgets;

void create_menus ()
{
    GtkWidget *menu_bar_main;
    GtkWidget *menu_item_program, *menu_item_help;
    GtkWidget *menu_shell_program, *menu_shell_help;
    GtkWidget *menu_item_delay, *menu_item_timer, *menu_item_pin_diagrams;
    GtkWidget *menu_item_contents, *menu_item_about;

    menu_bar_main = gtk_menu_bar_new ();
    gtk_box_pack_start (GTK_BOX (global_widgets->vbox_layout_main), menu_bar_main, FALSE, FALSE, 0);

    menu_item_program = gtk_menu_item_new_with_label ("Program");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar_main), menu_item_program);
    
    menu_item_help = gtk_menu_item_new_with_label ("Yardım");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar_main), menu_item_help);
    
    menu_shell_program = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu_item_program), menu_shell_program);

    menu_shell_help = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu_item_help), menu_shell_help);

    menu_item_delay = gtk_menu_item_new_with_label ("Gecikme");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell_program), menu_item_delay);
    g_signal_connect (G_OBJECT (menu_item_delay), "activate", G_CALLBACK (show_page_delay), NULL);

    menu_item_timer = gtk_menu_item_new_with_label ("Geri Sayım");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell_program), menu_item_timer);
    g_signal_connect (G_OBJECT (menu_item_timer), "activate", G_CALLBACK (show_page_timer), NULL);

    menu_item_pin_diagrams = gtk_menu_item_new_with_label ("Bacak Şemaları");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell_program), menu_item_pin_diagrams);
    g_signal_connect (G_OBJECT (menu_item_pin_diagrams), "activate", G_CALLBACK (show_page_pin_diagrams), NULL);

    menu_item_contents = gtk_menu_item_new_with_label ("Konular");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell_help), menu_item_contents);

    menu_item_about = gtk_menu_item_new_with_label ("Hakkında");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell_help), menu_item_about);
    g_signal_connect (G_OBJECT (menu_item_about), "activate", G_CALLBACK (show_window_about), NULL);
}

void show_page_delay (GtkWidget *menu_item_delay, gpointer data)
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK (global_widgets->notebook_main), PAGE_DELAY);
}

void show_page_timer (GtkWidget *menu_item_timer, gpointer data)
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK (global_widgets->notebook_main), PAGE_TIMER);
}

void show_page_pin_diagrams (GtkWidget *menu_item_pin_diagrams, gpointer data)
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK (global_widgets->notebook_main), PAGE_PIN_DIAGRAMS);
}

void show_window_about (GtkWidget *menu_item_about, gpointer data)
{
    GtkWidget *window_about;

    const gchar *programmers[] = {
        "Mustafa Tufaner (mtufaner@gmail.com)",
        "Canol Gökel (canol@canol.info)",
        NULL
    };

    window_about = gtk_about_dialog_new ();
    
    gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (window_about), "Pikomatik");
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (window_about), "0.1");
    gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (window_about), "(c) 2008 Hacettepe Robot Topluluğu");
    gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (window_about), "Dünyanın en bir mükemmel şeysi");
    gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (window_about), "Bu program ücretsizdir, ticari bir şekilde olmadığı sürece dağıtılması serbestdir.");
    gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (window_about), "http://robot.ee.hacettepe.edu.tr");
    gtk_about_dialog_set_website_label (GTK_ABOUT_DIALOG (window_about), "robot.ee.hacettepe.edu.tr");
    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (window_about), programmers);
    
    gtk_dialog_run (GTK_DIALOG (window_about));
    gtk_widget_destroy (window_about);
}
