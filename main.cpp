#include <gtk/gtk.h>
#include <initializer_list>

GtkWidget *window;

void message_dialog_clicked([[maybe_unused]] GtkButton *button, [[maybe_unused]] gpointer user_data) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW (window),
                                               static_cast<GtkDialogFlags>(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT),
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Hello gtk4");
    g_signal_connect (dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_widget_show(dialog);
}

void activateApp(GtkApplication *app, [[maybe_unused]] gpointer user_data) {
    //set dark theme
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE,  NULL);

    /* create a new window, and set its title */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "gtkdemo");

    /* Here we construct the container that is going pack our widgets */
    GtkWidget *grid = gtk_grid_new();

    /* Pack the container in the window */
    gtk_window_set_child(GTK_WINDOW (window), grid);

    GtkWidget *label = gtk_label_new_with_mnemonic ("Label   ");
    gtk_grid_attach(GTK_GRID (grid), label, 0, 0, 1, 1);

    GtkWidget *button = gtk_button_new_with_label("Button");
    g_signal_connect (button, "clicked", G_CALLBACK(message_dialog_clicked), NULL);
    gtk_grid_attach(GTK_GRID (grid), button, 1, 0, 1, 1);


    GtkWidget *check= gtk_check_button_new_with_mnemonic ("Check");
    gtk_grid_attach(GTK_GRID (grid), check, 0, 1, 1, 1);

    GtkWidget *combo=      gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),  "Regular");    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),  "Colors");
    gtk_grid_attach(GTK_GRID (grid), combo, 0, 2, 2, 1);


    auto v1={"A","B","C","D","E","F","G","H","I","J","K","L","M","N"};
    GtkWidget *list=    gtk_list_box_new ();
    for (auto& i:v1){
        GtkWidget *label = gtk_label_new_with_mnemonic (i);
        gtk_list_box_insert (GTK_LIST_BOX (list),label, -1);
    }

    gtk_grid_attach(GTK_GRID (grid), list, 0, 3, 2, 1);


    gtk_widget_show(window);

}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.mycompany.gtkdemo", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activateApp), NULL);
    int status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    return status;
}
