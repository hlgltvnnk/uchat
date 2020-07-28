#include "../inc/uchat.h"

static void show_sticer(t_main *m) {
    if (!gtk_widget_get_visible(m->stic_scrol))
        gtk_widget_show(m->stic_scrol);
    else 
        gtk_widget_hide(m->stic_scrol);
}

void attach_file(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gchar *tmp = NULL;
    t_user *us = NULL;
    t_add_m *s = NULL;

    (void)entry;
    (void)event;
    if (icon_pos == GTK_ENTRY_ICON_SECONDARY) {
        show_sticer(m);
        return ;
    }
    for (t_user *i = m->users; i; i = i->next)
        i->check == true ? us = i : 0;
    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
        s = create_struct((char *)tmp, true, 0, NULL);
        add_file(us, s, 1, 
            us->msg->next ? us->msg->next->id + 1 : 1);
        command_msg(us, s, 1);
        free(s);
    }
    gtk_widget_destroy (dialog);
}
