#include "../inc/uchat.h"

void log_click(GtkWidget *widget, t_wid *wid) {
	(void)widget;
	hide_start(wid);
	gtk_widget_show(wid->log->log_gif_pic);
	gtk_widget_show(wid->log->log_gif);
	show_fields(wid);
}
