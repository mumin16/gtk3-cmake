#include <gtk/gtk.h>

void appStart(GtkApplication *app, [[maybe_unused]] gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "gtkexample");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.mgsoftware.gtkexample", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(appStart), NULL);
    g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    return 0;
}
