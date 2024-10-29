#include <gtk/gtk.h>
#include <math.h>

GtkWidget *entry;
GtkWidget *window;       
GtkWidget *fullscreen_button; 
double num1, num2;
char operator;
int operation_set = 0;
int fullscreen = 0;      

void on_button_click(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (strcmp(label, "+") == 0 || strcmp(label, "-") == 0 || strcmp(label, "*") == 0 || strcmp(label, "/") == 0 || strcmp(label, "%") == 0) {
        num1 = atof(entry_text);
        operator = label[0];
        operation_set = 1;
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else if (strcmp(label, "=") == 0 && operation_set) {
        num2 = atof(entry_text);
        double result = 0;
        switch (operator) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
            case '%': result = fmod(num1, num2); break;
        }
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.2f", result);
        gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        operation_set = 0;
    } else if (strcmp(label, "C") == 0) {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
        operation_set = 0;
    } else if (strcmp(label, "x²") == 0) {
        double number = atof(entry_text);
        double result = number * number;
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.2f", result);
        gtk_entry_set_text(GTK_ENTRY(entry), buffer);
    } else if (strcmp(label, "√") == 0) {
        double number = atof(entry_text);
        if (number >= 0) {
            double result = sqrt(number);
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.2f", result);
            gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        } else {
            gtk_entry_set_text(GTK_ENTRY(entry), "Hata");
        }
    } else if (strcmp(label, "1/x") == 0) {
        double number = atof(entry_text);
        if (number != 0) {
            double result = 1.0 / number;
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.2f", result);
            gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        } else {
            gtk_entry_set_text(GTK_ENTRY(entry), "Hata");
        }
    } else {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%s%s", entry_text, label);
        gtk_entry_set_text(GTK_ENTRY(entry), buffer);
    }
}


void toggle_fullscreen(GtkWidget *widget, gpointer data) {
    if (fullscreen) {
        gtk_window_unfullscreen(GTK_WINDOW(window));
        gtk_button_set_label(GTK_BUTTON(fullscreen_button), "Tam Ekran"); 
        fullscreen = 0;  
    } else {
        gtk_window_fullscreen(GTK_WINDOW(window));
        gtk_button_set_label(GTK_BUTTON(fullscreen_button), "Küçük Ekran"); 
        fullscreen = 1;  
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

   
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hesap Makinesi");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);

    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(window), grid);


    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);


    const char *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "=", "+", "C",
        "x²", "√", "1/x", "%"
    };

    int pos = 0;
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            GtkWidget *button = gtk_button_new_with_label(buttons[pos]);
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_click), NULL);

            gtk_widget_set_size_request(button, 100, 100); 
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
            pos++;
        }
    }

     
    fullscreen_button = gtk_button_new_with_label("Tam Ekran");
    g_signal_connect(fullscreen_button, "clicked", G_CALLBACK(toggle_fullscreen), NULL);
    gtk_grid_attach(GTK_GRID(grid), fullscreen_button, 0, 6, 4, 1);  

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
