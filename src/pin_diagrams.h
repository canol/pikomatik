#ifndef PIN_DIAGRAMS_H
#define PIN_DIAGRAMS_H

#include <gtk/gtk.h>

typedef struct
{
    const gchar *name;
    const gchar *image_file;
} Component;

typedef struct
{
    GArray    *components;
    gint      selected_component_id;
    GtkWidget *combo_box_components;
    GtkWidget *image_pin_diagram;
} GlobalWidgetsPinDiagrams;

GArray* create_component_list ();
void refresh_combo_box_components ();
GtkWidget* create_page_pin_diagrams ();
void add_new_component (GtkButton*, gpointer);
gint compare_components (Component**, Component**);
void sort_component_list (GArray*);
void save_component_list (GArray*);
void show_pin_diagram (gint);
void show_next_pin_diagram (GtkButton*);
void show_previous_pin_diagram (GtkButton*);
void combo_box_components_changed (GtkComboBox*, gpointer);

#endif /* PIN_DIAGRAMS_H */
