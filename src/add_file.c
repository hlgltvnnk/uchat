#include "../inc/uchat.h"

static void msg_file_pushfront(t_msg **head, t_add_m *s) {
    t_msg *tmp = NULL;

    tmp = create_msg(NULL, s->text);
    tmp->my = s->my;
    tmp->prev = *head;
    tmp->next = (*head)->next; 
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
}

void file_check(t_msg **msg, char *name, bool my) {
    t_msg *t = *msg;

    t->file = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    MX_BOX_START(t->file, gtk_image_new_from_file("./source/resource/load image.png"));
    gtk_box_pack_start(GTK_BOX(t->file), gtk_label_new(name), FALSE, FALSE, 10); 
    gtk_container_add(GTK_CONTAINER(t->label), t->file);
    mx_idle_show(my, t->label);
}

static void send_file(t_user *us, t_add_m *s, t_msg *t) {
    t->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(t->box, 630, 30);
    MX_MSG_PACK(s->my, t->label, t->box);
    MX_SET_NAME_MSG(s->my, t->label);
    gtk_grid_attach(GTK_GRID(us->text_grid), t->box, 0, t->count, 1, 1);
    mx_idle_show(s->my, t->box);   
    us->row++;
    mx_add_popup_menu(t->stic, t);
}

static void check_sticer(int stic, t_add_m *s, t_msg *t, char *name) {
    if (stic == 1) {
        file_check(&t, name, s->my);
        send_file(t->user, s, t);
    }
    else {
        t->file = gtk_image_new_from_file(s->text);
        gtk_button_set_image(GTK_BUTTON(t->label), t->file);
        send_file(t->user, s, t);
    }
}

void add_file(t_user *us, t_add_m *s, int stic, int id) {
    t_msg *t = NULL;
    char **p = mx_strsplit(s->text, '/');
    char *name = NULL;
    (void)id;

    if (p)
        name = p[mx_len_of_array(p) - 1];
    else 
        name = s->text;
    msg_file_pushfront(&us->msg, s);
    t = us->msg->next;
    t->user = us;
    t->id = mx_id_for_msg(us, id);
    t->stic = stic;
    check_sticer(stic, s, t, name);
    MX_SCROL_END(us->m);
    mx_del_strarr(&p);
}
