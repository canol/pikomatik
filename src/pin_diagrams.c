#include <gtk/gtk.h>

#include "pikomatik.h"
#include "pin_diagrams.h"
#include "utility.h"

extern GlobalWidgets *global_widgets;
GlobalWidgetsPinDiagrams *global_widgets_pin_diagrams;

GArray* create_component_list ()
{
    gchar *content;
    gsize byte;
    gchar **component_info, **component_data;
    GError *error = NULL;
    GArray *components;
    gint i = 0;

    Component *new_component;

    components = g_array_new (TRUE, FALSE, sizeof (Component*));
    global_widgets_pin_diagrams->components = components;

    g_file_get_contents ("components.txt", &content, &byte, &error);
    
    component_info = g_strsplit (g_strchomp (content), "\n", 0);
    
    i = 0;
    while (component_info[i])
    {
        component_data = g_strsplit (g_strchomp (component_info[i]), "||", 0);
        
        new_component = g_malloc (sizeof (Component*));
        new_component->name = g_strchomp (component_data[0]);
        new_component->image_file = g_strchomp (component_data[1]);
        
        g_array_append_val (components, new_component);

        i++;
    }

    return components;
}

void clear_combo_box_components ()
{
    int i = 0;
    
    while (g_array_index (global_widgets_pin_diagrams->components, Component*, i))
    {
        gtk_combo_box_remove_text (GTK_COMBO_BOX (global_widgets_pin_diagrams->combo_box_components), 0);
        
        i++;
    }
}

void refresh_combo_box_components ()
{
    int i = 0;
    
    while (g_array_index (global_widgets_pin_diagrams->components, Component*, i))
    {
        gtk_combo_box_append_text (GTK_COMBO_BOX (global_widgets_pin_diagrams->combo_box_components), g_array_index (global_widgets_pin_diagrams->components, Component*, i)->name);
        
        i++;
    }
    
    gtk_combo_box_set_active (GTK_COMBO_BOX (global_widgets_pin_diagrams->combo_box_components), 0);
}

GtkWidget* create_page_pin_diagrams ()
{
    GtkWidget *page_pin_diagrams;
    GtkWidget *temp;
    GtkWidget *button_add_new_component, *button_delete_this_component, *button_previous_pin_diagram, *button_next_pin_diagram;
    GtkWidget *combo_box_components;
    GtkWidget *image_pin_diagram;
    
    GArray *components;
    
    global_widgets_pin_diagrams = g_malloc (sizeof (GlobalWidgetsPinDiagrams));

    components = create_component_list ();
    sort_component_list (components);
    
    page_pin_diagrams = gtk_vbox_new (FALSE, 3);
    gtk_container_set_border_width (GTK_CONTAINER (page_pin_diagrams), 3);

    temp = gtk_hbox_new (FALSE, 3);
    gtk_box_pack_start (GTK_BOX (page_pin_diagrams), temp, FALSE, FALSE, 0);

    button_previous_pin_diagram = gtk_button_new ();
    g_signal_connect (G_OBJECT (button_previous_pin_diagram), "clicked",
                      G_CALLBACK (show_previous_pin_diagram),
                      (gpointer) global_widgets_pin_diagrams);
    gtk_button_set_image (GTK_BUTTON (button_previous_pin_diagram), gtk_image_new_from_stock (GTK_STOCK_GO_BACK, GTK_ICON_SIZE_BUTTON));

    combo_box_components = gtk_combo_box_new_text ();
    global_widgets_pin_diagrams->combo_box_components = combo_box_components;
    refresh_combo_box_components ();
    g_signal_connect (G_OBJECT (combo_box_components), "changed",
                      G_CALLBACK (combo_box_components_changed),
                      NULL);

    button_next_pin_diagram = gtk_button_new ();
    g_signal_connect (G_OBJECT (button_next_pin_diagram), "clicked",
                      G_CALLBACK (show_next_pin_diagram),
                      (gpointer) global_widgets_pin_diagrams);
    gtk_button_set_image (GTK_BUTTON (button_next_pin_diagram), gtk_image_new_from_stock (GTK_STOCK_GO_FORWARD, GTK_ICON_SIZE_BUTTON));
    
    gtk_box_pack_start (GTK_BOX (temp), button_previous_pin_diagram, FALSE, TRUE, 0);
    gtk_box_pack_start_defaults (GTK_BOX (temp), combo_box_components);
    gtk_box_pack_start (GTK_BOX (temp), button_next_pin_diagram, FALSE, TRUE, 0);
    
    image_pin_diagram = gtk_image_new ();
    global_widgets_pin_diagrams->image_pin_diagram = image_pin_diagram;
    gtk_box_pack_start_defaults (GTK_BOX (page_pin_diagrams), image_pin_diagram);

    temp = gtk_hbox_new (FALSE, 3);
    gtk_box_pack_start (GTK_BOX (page_pin_diagrams), temp, FALSE, FALSE, 0);

    button_add_new_component = gtk_button_new_with_label ("Yeni Eleman Ekle");
    gtk_button_set_image (GTK_BUTTON (button_add_new_component), gtk_image_new_from_stock (GTK_STOCK_ADD, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button_add_new_component), "clicked",
                      G_CALLBACK (add_new_component),
                      NULL);
    gtk_box_pack_start_defaults (GTK_BOX (temp), button_add_new_component);
    
    button_delete_this_component = gtk_button_new_with_label ("Bu Elemanı Sil");
    gtk_button_set_image (GTK_BUTTON (button_delete_this_component), gtk_image_new_from_stock (GTK_STOCK_REMOVE, GTK_ICON_SIZE_BUTTON));
    gtk_box_pack_start_defaults (GTK_BOX (temp), button_delete_this_component);
    
    global_widgets_pin_diagrams->selected_component_id = 0;
    show_pin_diagram (global_widgets_pin_diagrams->selected_component_id);

    return page_pin_diagrams;
}

void add_new_component (GtkButton *button, gpointer data)
{
    GtkWidget *dialog_add_new_component;
    GtkWidget *temp;
    GtkWidget *label_name, *label_image;
    GtkWidget *button_select_image;
    GtkWidget *entry_name;
    
    Component *new_component;
    
    dialog_add_new_component = gtk_dialog_new_with_buttons ("Yeni Component Ekleme", GTK_WINDOW (global_widgets->window_main),
                                                           GTK_DIALOG_MODAL,
                                                           "Ekle", GTK_RESPONSE_OK,
                                                           "İptal", GTK_RESPONSE_REJECT,
                                                           NULL);

    temp = gtk_table_new (2, 2, FALSE);
    gtk_table_set_row_spacings (GTK_TABLE (temp), 3);
    gtk_table_set_col_spacings (GTK_TABLE (temp), 3);
    gtk_box_pack_start_defaults (GTK_BOX (GTK_DIALOG (dialog_add_new_component)->vbox), temp);

    label_name = gtk_label_new ("İsim:");
    gtk_misc_set_alignment (GTK_MISC (label_name), 0, 0.5);

    entry_name = gtk_entry_new ();

    label_image = gtk_label_new ("Resim:");
    gtk_misc_set_alignment (GTK_MISC (label_image), 0, 0.5);

    button_select_image = gtk_file_chooser_button_new ("Resim Seç", GTK_FILE_CHOOSER_ACTION_OPEN);

    gtk_table_attach (GTK_TABLE (temp), label_name, 0, 1, 0, 1,
                      GTK_FILL, GTK_SHRINK, 0, 0);
    gtk_table_attach (GTK_TABLE (temp), entry_name, 1, 2, 0, 1,
                      GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);
    gtk_table_attach (GTK_TABLE (temp), label_image, 0, 1, 1, 2,
                      GTK_FILL, GTK_SHRINK, 0, 0);
    gtk_table_attach (GTK_TABLE (temp), button_select_image, 1, 2, 1, 2,
                      GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);
                      
    gtk_widget_show_all (dialog_add_new_component);
    
    if (gtk_dialog_run (GTK_DIALOG (dialog_add_new_component)) == GTK_RESPONSE_OK)
    {
        new_component = g_malloc (sizeof (Component*));
        new_component->name = gtk_entry_get_text (GTK_ENTRY (entry_name));
        new_component->image_file = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (button_select_image));
        
        clear_combo_box_components ();
        g_array_append_val (global_widgets_pin_diagrams->components, new_component);
        refresh_combo_box_components ();
    }
    
    gtk_widget_destroy (dialog_add_new_component);
}

gint compare_components (Component **component_1, Component **component_2)
{
    return g_ascii_strcasecmp ((*component_1)->name, (*component_2)->name);
}

void sort_component_list (GArray *components)
{
    g_array_sort (components, (GCompareFunc) compare_components);
}

void save_component_list (GArray *components)
{
    gchar *content;
    GError *error = NULL;
    gint i = 0;
    
    while (g_array_index (components, Component*, i))
    {
        content = g_strconcat (content, "\n", g_array_index (components, Component*, i)->name, "||", g_array_index (components, Component*, i)->image_file, NULL);
        
        i++;
    }

    g_file_set_contents ("components.txt", content, -1, &error);
}

void show_pin_diagram (gint component_id)
{
    GString *image_file;
    GdkPixbuf *image_component_not_scaled;
    gint image_pin_diagram_height, image_pin_diagram_width;
    gint image_pin_diagram_height_new, image_pin_diagram_width_new;
    GError *error = NULL;
    
    image_file = g_string_new ("./pin_diagrams/");
    g_string_append (image_file, g_array_index (global_widgets_pin_diagrams->components, Component*, component_id)->image_file);

    image_pin_diagram_height = global_widgets_pin_diagrams->image_pin_diagram->allocation.height;
    image_pin_diagram_width = global_widgets_pin_diagrams->image_pin_diagram->allocation.width;
    
    image_component_not_scaled = gdk_pixbuf_new_from_file (image_file->str, &error);
    
    image_pin_diagram_height_new = gdk_pixbuf_get_height (image_component_not_scaled);
    image_pin_diagram_width_new = gdk_pixbuf_get_width (image_component_not_scaled);
    
    if (image_pin_diagram_height_new > image_pin_diagram_height)
    {
        gdouble ratio;
        
        ratio = (double) image_pin_diagram_height / image_pin_diagram_height_new;
        
        if (ratio > 0.05)
            image_component_not_scaled = gdk_pixbuf_scale_simple (image_component_not_scaled, (int) (image_pin_diagram_width_new * ratio), (int) (image_pin_diagram_height_new * ratio), GDK_INTERP_BILINEAR);
    }
    
    if (image_pin_diagram_width_new > image_pin_diagram_width)
    {
        gdouble ratio;
        
        ratio = (double) image_pin_diagram_width / image_pin_diagram_width_new;
        
        if (ratio > 0.05)
            image_component_not_scaled = gdk_pixbuf_scale_simple (image_component_not_scaled, (int) (image_pin_diagram_width_new * ratio), (int) (image_pin_diagram_height_new * ratio), GDK_INTERP_BILINEAR);
    }
    gtk_image_set_from_pixbuf (GTK_IMAGE (global_widgets_pin_diagrams->image_pin_diagram), image_component_not_scaled);
}

void show_next_pin_diagram (GtkButton *button)
{
    if (global_widgets_pin_diagrams->selected_component_id == g_array_length (global_widgets_pin_diagrams->components) - 1)
        global_widgets_pin_diagrams->selected_component_id = 0;
    else
        global_widgets_pin_diagrams->selected_component_id += 1;
    gtk_combo_box_set_active (GTK_COMBO_BOX (global_widgets_pin_diagrams->combo_box_components), global_widgets_pin_diagrams->selected_component_id);
    
    show_pin_diagram (global_widgets_pin_diagrams->selected_component_id);
}

void show_previous_pin_diagram (GtkButton *button)
{
    if (global_widgets_pin_diagrams->selected_component_id == 0)
        global_widgets_pin_diagrams->selected_component_id = g_array_length (global_widgets_pin_diagrams->components) - 1;
    else
        global_widgets_pin_diagrams->selected_component_id -= 1;
    gtk_combo_box_set_active (GTK_COMBO_BOX (global_widgets_pin_diagrams->combo_box_components), global_widgets_pin_diagrams->selected_component_id);
    
    show_pin_diagram (global_widgets_pin_diagrams->selected_component_id);
}

void combo_box_components_changed (GtkComboBox *combo_box_components, gpointer data)
{
    if (gtk_combo_box_get_active (combo_box_components) != -1)
    {
        global_widgets_pin_diagrams->selected_component_id = gtk_combo_box_get_active (combo_box_components);
        show_pin_diagram (global_widgets_pin_diagrams->selected_component_id);
    }
}
