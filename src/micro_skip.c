#include "../inc/uchat.h"

void micro_end(GtkWidget *w, t_main *m) {
    (void)w;
    gtk_widget_show(m->micro_of);
    gtk_widget_show(m->micro_on_but);
    gtk_widget_hide(m->micro_on);
    gtk_widget_hide(m->micro_of_but);
    puts("---\n");
}