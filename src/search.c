#include "../inc/uchat.h"

static void search_msg(GtkEntry *e, t_main *m) {
    t_user *us = NULL;
    char *s = NULL;

    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return ;
    for (t_user *i = m->users; i; i = i->next)
        (i->check == true) ? us = i : 0;
    for (t_msg *i = us->msg; i; i = i->next) {
        if (!mx_strcmp_null(i->text, s)) {
           gtk_adjustment_set_value(m->adj, i->adj_value + 150.0);
           printf("adj now === %f\n", gtk_adjustment_get_value(m->adj));
           return ;
        }
    }
    for (t_msg *i = us->msg; i; i = i->next) {
        if (mx_get_substr_index(i->text, s) > -1) {
           gtk_adjustment_set_value(m->adj, i->adj_value + 150.0);
           printf("adj now === %f\n", gtk_adjustment_get_value(m->adj));
           return ;
        }
    }
}

static void search_user(GtkEntry *e, t_main *m) {
    char *s = NULL;

    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    if ((s = (char *)gtk_entry_get_text(e)) == NULL && !mx_strlen(s))
        return ;
    for (t_user *i = m->users; i; i = i->next) {
        if (!mx_strstr(i->name, s))
            gtk_widget_destroy(i->fix);
    }
    burger_leave(NULL, NULL, m);
}
 
void add_contact_to_us(GtkWidget *wid, t_search *s) {
    user_pushfront(&s->m->users, s->name);
    set_chat_grid(s->m, 1);
    gtk_widget_destroy(s->but);
}

bool mx_user_exist(t_main *m, char *name) {
    for (t_user *i = m->users; i; i = i->next) 
        if (!mx_strcmp(i->name, name))
            return true;
    return false;
}

GtkWidget *create_contacts(char *name, char *path, t_main *m, t_search *s) {
    GtkWidget *fix = gtk_fixed_new(); 
    char *img = "./src/resource/index.jpg";//path;
    char *markup = g_markup_printf_escaped(MX_NAME_COLOR(m->style->color), s->name);
    GtkWidget *l = gtk_label_new(NULL);

    s->but = gtk_button_new_with_label("Add");
    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SLEPT(m->style->color)), 11, 0);
    gtk_label_set_markup(GTK_LABEL(l), markup);
    gtk_fixed_put(GTK_FIXED(fix), resize_image(img, 51, 51), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), 
        gtk_image_new_from_file(MX_SL_PH(m->style->color)), 23, 14);
    gtk_fixed_put(GTK_FIXED(fix), l, 83, 25);
    if (!mx_user_exist(m, name)) {
        gtk_fixed_put(GTK_FIXED(fix), s->but, 210, 21);
        MX_SET_NAME_MSG(m->style->color, s->but);
        g_signal_connect(s->but, "clicked", G_CALLBACK(add_contact_to_us), s);
    }
    g_idle_add((GSourceFunc)mx_show, fix);
    g_free(markup);
    return fix;
}

void show_result_of_search(t_list *list, t_main *m) {
    int row = 0;
    t_search *s = NULL;

    gtk_widget_destroy(m->grid_user);
    m->grid_user = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_user), 8);
    for (t_list *i = list; i; i = i->next) {
        pushfront_search_contact(&m->srch, m, 
            ((t_data *)i->data)->name, ((t_data *)i->data)->path);
        gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
        gtk_grid_attach(GTK_GRID(m->grid_user), 
            create_contacts(m->srch->name, m->srch->path, m, m->srch), 0, row++, 1, 1);
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_users), m->grid_user, 0, 8);
    g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
    m->cmd = DEF;
}

static void search_contacts(GtkEntry *e, t_main *m) {
    char *s = (char *)gtk_entry_get_text(e);

    if (s == NULL || !mx_strlen(s))
        return ;
    m->command = mx_arrjoin(m->command, "mx_user_search");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, s);
    m->cmd = SRCH;
    // char *n[] = {"vova", "carl", "ivan", NULL};
    // show_result_of_search(n, m);
}

void search_activ(GtkEntry *e, t_main *m) {
    if (m->flag_search == 1)
        search_msg(e, m);
    else if (m->flag_search == 2)
        search_user(e, m);
    else if (m->flag_search == 3)
        search_contacts(e, m);
}
