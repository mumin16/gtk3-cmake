#include <gtk/gtk.h>

void print_hello([[maybe_unused]] GtkWidget *widget, [[maybe_unused]] gpointer data) {
    g_print("Hello gtk4\n");
}

void activateApp(GtkApplication *app, [[maybe_unused]] gpointer user_data) {
    /* create a new window, and set its title */
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "gtkdemo");

    /* Here we construct the container that is going pack our buttons */
    GtkWidget *grid = gtk_grid_new();

    /* Pack the container in the window */
    gtk_window_set_child(GTK_WINDOW (window), grid);

    GtkWidget *button = gtk_button_new_with_label("Button 1");
    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach(GTK_GRID (grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Button 2");
    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);

    /* Place the second button in the grid cell (1, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach(GTK_GRID (grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK(gtk_window_destroy), window);

    /* Place the Quit button in the grid cell (0, 1), and make it
     * span 2 columns.
     */
    gtk_grid_attach(GTK_GRID (grid), button, 0, 1, 2, 1);

    gtk_widget_show(window);

}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.mycompany.gtkdemo", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activateApp), NULL);
    int status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    return status;
}
