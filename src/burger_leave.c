#include "../inc/uchat.h"

void burger_leave(GtkWidget *widget, GdkEvent *event, t_main *m) {
    (void)widget;
    (void)event;
    gtk_widget_destroy(m->cap->burger_but_img);
    if (m->menu->flag == 1 || m->set->flag == 1 || m->bl == 1) 
        m->cap->burger_but_img =
            gtk_image_new_from_file("./source/resource/cancel.png");
    else
        m->cap->burger_but_img = gtk_image_new_from_file
            ("./source/resource/burger.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
}
