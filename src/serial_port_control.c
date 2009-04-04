#include <gtk/gtk.h>

#include "seri_port_denetimi.h"

GtkWidget* seri_port_denetimi_sayfasini_olustur(GtkWidget *pencere_ana)
{
    GtkWidget *sayfa_seri_port_denetimi;
    GtkWidget *gecici;
    GtkWidget *dugme_ekrani_temizle, *dugme_gonder;
    GtkWidget *radyo_hex, *radyo_ascii;
    GtkWidget *cerceve_seri_port_cikisi;
    GtkWidget *etiket_giris_yontemi;
    GtkWidget *yazi_seri_port_cikisi;
    GtkWidget *girdi_seri_port_girisi;

    sayfa_seri_port_denetimi = gtk_vbox_new(FALSE, 3);
    gtk_container_set_border_width(GTK_CONTAINER(sayfa_seri_port_denetimi), 3);

    cerceve_seri_port_cikisi = gtk_frame_new("Seri Port Çıkışı");
    
    gecici = gtk_alignment_new(0.5, 0.5, 1, 1);
    gtk_alignment_set_padding(GTK_ALIGNMENT(gecici), 3, 5, 3, 5);
    
    yazi_seri_port_cikisi = gtk_text_view_new();
    gtk_container_set_border_width(GTK_CONTAINER(yazi_seri_port_cikisi), 1);
    
    gtk_container_add(GTK_CONTAINER(gecici), yazi_seri_port_cikisi);
    gtk_container_add(GTK_CONTAINER(cerceve_seri_port_cikisi), gecici);

    gtk_box_pack_start_defaults(GTK_BOX(sayfa_seri_port_denetimi), cerceve_seri_port_cikisi);

    gecici = gtk_hbox_new(FALSE, 3);

    etiket_giris_yontemi = gtk_label_new("Giriş Yöntemi:");
    
    dugme_ekrani_temizle = gtk_button_new_with_mnemonic("Ekrani _Temizle");
    
    radyo_hex = gtk_radio_button_new_with_label(NULL, "Hex");
    radyo_ascii = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radyo_hex), "Ascii");

    gtk_box_pack_start_defaults(GTK_BOX(gecici), dugme_ekrani_temizle);
    gtk_box_pack_start(GTK_BOX(gecici), etiket_giris_yontemi, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gecici), radyo_hex, FALSE, TRUE, 0);
    gtk_box_pack_start_defaults(GTK_BOX(gecici), radyo_ascii);

    gtk_box_pack_start(GTK_BOX(sayfa_seri_port_denetimi), gecici, FALSE, TRUE, 0);

    gecici = gtk_hbox_new(FALSE, 3);

    girdi_seri_port_girisi = gtk_entry_new();

    dugme_gonder = gtk_button_new_with_mnemonic("_Gönder");

    gtk_box_pack_start_defaults(GTK_BOX(gecici), girdi_seri_port_girisi);
    gtk_box_pack_start_defaults(GTK_BOX(gecici), dugme_gonder);

    gtk_box_pack_start(GTK_BOX(sayfa_seri_port_denetimi), gecici, FALSE, TRUE, 0);

    return sayfa_seri_port_denetimi;
}
