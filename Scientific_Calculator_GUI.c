// Full GTK Scientific Calculator in C with All Functions

#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 10

double memory = 0.0;
char history[HISTORY_SIZE][100];
int history_index = 0;

// Utility function to update history
void add_to_history(const char *entry)
{
    strncpy(history[history_index % HISTORY_SIZE], entry, 99);
    history_index++;
}

// Callback to handle basic operations and scientific functions
void on_operation_button_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    GtkEntry **entries = (GtkEntry **)data;

    const gchar *num1_text = gtk_entry_get_text(entries[0]);
    const gchar *num2_text = gtk_entry_get_text(entries[1]);
    double num1 = atof(num1_text);
    double num2 = atof(num2_text);
    double result = 0.0;
    char result_str[256];

    if (strcmp(label, "Add") == 0) result = num1 + num2;
    else if (strcmp(label, "Subtract") == 0) result = num1 - num2;
    else if (strcmp(label, "Multiply") == 0) result = num1 * num2;
    else if (strcmp(label, "Divide") == 0) result = (num2 != 0) ? num1 / num2 : 0;
    else if (strcmp(label, "Power") == 0) result = pow(num1, num2);
    else if (strcmp(label, "Square") == 0) result = num1 * num1;
    else if (strcmp(label, "Sqrt") == 0) result = sqrt(num1);
    else if (strcmp(label, "Factorial") == 0)
    {
        int n = (int)num1;
        result = 1;
        for (int i = 1; i <= n; i++) result *= i;
    }
    else if (strcmp(label, "nPr") == 0)
    {
        int n = (int)num1, r = (int)num2, i;
        double nf = 1, nr = 1;
        for (i = 1; i <= n; i++) nf *= i;
        for (i = 1; i <= (n - r); i++) nr *= i;
        result = nf / nr;
    }
    else if (strcmp(label, "nCr") == 0)
    {
        int n = (int)num1, r = (int)num2, i;
        double nf = 1, rf = 1, nrf = 1;
        for (i = 1; i <= n; i++) nf *= i;
        for (i = 1; i <= r; i++) rf *= i;
        for (i = 1; i <= (n - r); i++) nrf *= i;
        result = nf / (rf * nrf);
    }
    else if (strcmp(label, "Deg→Rad") == 0) result = num1 * M_PI / 180.0;
    else if (strcmp(label, "Rad→Deg") == 0) result = num1 * 180.0 / M_PI;
    else if (strcmp(label, "Sin") == 0) result = sin(num1);
    else if (strcmp(label, "Cos") == 0) result = cos(num1);
    else if (strcmp(label, "Tan") == 0) result = tan(num1);
    else if (strcmp(label, "Log") == 0) result = log10(num1);
    else if (strcmp(label, "Ln") == 0) result = log(num1);
    else if (strcmp(label, "Exp") == 0) result = exp(num1);
    else if (strcmp(label, "M+") == 0) memory += num1;
    else if (strcmp(label, "M-") == 0) memory -= num1;
    else if (strcmp(label, "MR") == 0) result = memory;
    else if (strcmp(label, "MC") == 0) memory = 0;

    snprintf(result_str, sizeof(result_str), "Result: %.6lf", result);
    gtk_label_set_text(GTK_LABEL(entries[2]), result_str);
    add_to_history(result_str);
}

void on_history_button_clicked(GtkWidget *widget, gpointer data)
{
    GtkLabel *label = GTK_LABEL(data);
    char history_str[1024] = "History:\n";
    for (int i = 0; i < HISTORY_SIZE && i < history_index; i++)
    {
        strcat(history_str, history[i]);
        strcat(history_str, "\n");
    }
    gtk_label_set_text(label, history_str);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();
    GtkWidget *result_label = gtk_label_new("Result:");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Num 1:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Num 2:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 2, 2, 1);

    const char *buttons[] =
    {
        "Add", "Subtract", "Multiply", "Divide",
        "Power", "Square", "Sqrt", "Factorial",
        "nPr", "nCr", "Deg→Rad", "Rad→Deg",
        "Sin", "Cos", "Tan", "Log",
        "Ln", "Exp", "M+", "M-",
        "MR", "MC"
    };

    GtkEntry *entries[] = { GTK_ENTRY(entry1), GTK_ENTRY(entry2), GTK_ENTRY(result_label) };

    int row = 3, col = 0;
    for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++)
    {
        GtkWidget *btn = gtk_button_new_with_label(buttons[i]);
        gtk_grid_attach(GTK_GRID(grid), btn, col, row, 1, 1);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_operation_button_clicked), entries);
        col++;
        if (col >= 4)
        {
            col = 0;
            row++;
        }
    }

    GtkWidget *history_button = gtk_button_new_with_label("Show History");
    gtk_grid_attach(GTK_GRID(grid), history_button, 0, row+1, 4, 1);
    g_signal_connect(history_button, "clicked", G_CALLBACK(on_history_button_clicked), result_label);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
