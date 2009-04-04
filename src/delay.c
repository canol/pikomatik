#include <gtk/gtk.h>

#include "delay.h"

GtkWidget* create_page_delay ()
{
    GtkWidget *page_delay;
    GtkWidget *table_delay;
    GtkWidget *button_calculate;
    GtkWidget *frame_info, *frame_pic_assembly_code;
    GtkWidget *label_delay_time, *label_oscillator_frequency, *label_mhz;
    GtkWidget *entry_delay_time, *entry_oscillator_frequency;
    GtkWidget *combo_box_time_unit;
    GtkWidget *temp;

    page_delay = gtk_vbox_new (FALSE, 3);
    gtk_container_set_border_width (GTK_CONTAINER (page_delay), 3);

    table_delay = gtk_table_new (3, 2, FALSE);
    gtk_box_pack_start (GTK_BOX (page_delay), table_delay, FALSE, TRUE, 0);
    gtk_table_set_row_spacings (GTK_TABLE (table_delay), 3);
    gtk_table_set_col_spacings (GTK_TABLE (table_delay), 3);

    temp = gtk_hbox_new (FALSE, 0);

    entry_delay_time = gtk_entry_new ();
    gtk_box_pack_start_defaults (GTK_BOX (temp), entry_delay_time);

    combo_box_time_unit = gtk_combo_box_new_text ();
    gtk_box_pack_start (GTK_BOX (temp), combo_box_time_unit, FALSE, TRUE, 0);
    
    gtk_table_attach (GTK_TABLE (table_delay), temp, 1, 2, 0, 1,
                      GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);

    gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box_time_unit), "us");
    gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box_time_unit), "ms");
    gtk_combo_box_append_text (GTK_COMBO_BOX (combo_box_time_unit), "s");
    gtk_combo_box_set_active (GTK_COMBO_BOX (combo_box_time_unit), 0);

    label_delay_time = gtk_label_new ("Gecikme Süresi:");
    gtk_table_attach (GTK_TABLE (table_delay), label_delay_time, 0, 1, 0, 1,
                      GTK_FILL, GTK_SHRINK, 0, 0);
                      
    gtk_misc_set_alignment (GTK_MISC (label_delay_time), 0, 0.5);

    label_oscillator_frequency = gtk_label_new ("Osilatör Frekansı:");
    gtk_table_attach (GTK_TABLE (table_delay), label_oscillator_frequency, 0, 1, 1, 2,
                      GTK_FILL, GTK_SHRINK, 0, 0);
    
    gtk_misc_set_alignment (GTK_MISC (label_oscillator_frequency), 0, 0.5);

    temp = gtk_hbox_new (FALSE, 0);

    entry_oscillator_frequency = gtk_entry_new ();
    gtk_box_pack_start_defaults (GTK_BOX(temp), entry_oscillator_frequency);
    
    label_mhz = gtk_label_new ("MHz");
    gtk_box_pack_start (GTK_BOX (temp), label_mhz, FALSE, TRUE, 0);

    gtk_table_attach (GTK_TABLE (table_delay), temp, 1, 2, 1, 2,
                      GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);

    gtk_misc_set_alignment (GTK_MISC(label_mhz), 0, 0.5);
    
    button_calculate = gtk_button_new_with_label ("Hesapla");

    gtk_table_attach (GTK_TABLE (table_delay), button_calculate, 1, 2, 2, 3,
                      GTK_FILL, GTK_SHRINK, 0, 0);

    frame_info = gtk_frame_new ("Açıklamalar");
    gtk_box_pack_start_defaults (GTK_BOX (page_delay), frame_info);

    frame_pic_assembly_code = gtk_frame_new ("PIC Assembly Kodu");
    gtk_box_pack_start_defaults (GTK_BOX (page_delay), frame_pic_assembly_code);

    return page_delay;
}
