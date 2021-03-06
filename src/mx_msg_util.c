#include "../inc/uchat.h"

void save_file(GtkMenuItem *item, t_msg *msg) {
    char *str = mx_itoa(msg->id);
    t_main *m = msg->user->m;
    (void)item;

    m->command = mx_arrjoin(m->command, "mx_get_img_path");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, msg->user->name);
    m->command = mx_arrjoin(m->command, str);
    mx_strdel(&str);
}

void delete_msg(GtkMenuItem *item, t_msg *msg) {
    t_msg *t = NULL;
    t_main *m = msg->user->m;
    char *id = mx_itoa(msg->id);

    (void)item;
    gtk_grid_remove_row(GTK_GRID(msg->user->text_grid), msg->count);
    for (t_msg *i = msg->prev; i->prev; i = i->prev)
        i->count--;
    t = msg->next;
    t != NULL ? t->prev = msg->prev : 0;
    msg->prev->next = t;
    reset_l_mess(msg->user);
    msg->count > 0 ? msg->user->row-- : 0;
    m->command = mx_arrjoin(m->command, "mx_del_message");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, msg->user->name);
    m->command = mx_arrjoin(m->command, id);
    free(msg);
    msg = NULL;
}

t_msg *create_msg(char *text, char *filename) {
    t_msg *new = (t_msg *)malloc(sizeof(t_msg) * 15);

    new->next = NULL;
    new->prev = NULL;
    new->count = 0;
    new->stic = 0;
    new->user = NULL;
    new->filename = NULL;
    new->text = NULL;
    new->time = NULL;
    new->label = gtk_button_new();
    if (!text && !filename)
        return new;
    gtk_widget_set_size_request(new->label, 100, 30);
    if (text) {
        new->text = mx_strdup(text);
        gtk_button_set_label(GTK_BUTTON(new->label), new->text);
    }
    else 
        new->filename = mx_strdup(filename); 
    return new;
}

void msg_pushfront(t_msg **head, char *text, bool my, int forw) {
    t_msg *tmp = NULL;

    tmp = create_msg(text, NULL);
    tmp->my = my;
    tmp->forward = forw;
    MX_SET_NAME_MSG(my, tmp->label);
    tmp->prev = *head;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
    mx_add_popup_menu(0, tmp);
}

