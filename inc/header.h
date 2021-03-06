#ifndef HEADER_H
#define HEADER_H

#include <pwd.h>
#include <grp.h>
#include <poll.h>
#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/uio.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <ctype.h>

#include "../libmx/inc/libmx.h"
#include "json_functions.h"
#include "database.h"
#include "ssl.h"
#include "uchat.h"

#include "portaudio.h"
#include "sndfile.h"

#define FLAG 100
#define TIMER 1000
#define SIZE_SEND 1027
#define FILE_SIZE 262144000
#define SIZE_SEND_LESS 1024

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS (5)
#define NUM_CHANNELS (2)

#define DITHER_FLAG (0) 
#define WRITE_TO_FILE (0)

#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE (0.0f)
#define PRINTF_S_FORMAT "%.8f"

typedef struct s_paTestData{
    int frameIndex;
    int maxFrameIndex;
    SAMPLE *recordedSamples;
}              t_paTestData;

// Client
void mx_for_cash(char *json);
int mx_client(int argc, char *argv[]);
void mx_send_command(char *json, t_client *client);
void *mx_files(void *client_pointer);
int mx_pre_parse_time(char *json1, char *json2);
int mx_intcmp(char *str1, char *str2);
int mx_monthcmp(char *month1, char *month2);
void mx_sort_mssg(t_list **list, int flag);
void mx_client_send(t_client *client);
void mx_hash_pass(char **json);
void mx_recv_lan_theme(char ch[], t_client *client);
char *mx_right_path(t_info **info, t_files *files, t_client *client, char *name);
void mx_recv_list_files(char ch[], t_info **info, t_files *files, t_client *client);
void mx_recv_list(char ch[], t_info **info, t_files *files, t_client *client);
void mx_client_recv_file(char ch[], t_client *client);
void *mx_client_read(void *client_pointer);
void mx_get_request(char **json, t_client *client);
t_data *mx_create_data(void);
t_info *mx_create_info(void);

// Server
void mx_send_history_list(t_node **node, char *name, char *json);
void mx_send_answer_type(t_node **node, int type, int flag);
void mx_send_user_file(char *img_path, t_node **node);
void mx_send_answer_list(t_node **node, t_list *list, int hist_flag, char *json);
int mx_server(int argc, char *argv[]);
void *mx_server_files(void *data);
void mx_del_client(t_way **list, t_node **node, void *data, int flag);
void *mx_server_handel(void *data);
void mx_choose(t_node *node, char **json);
void mx_log_out_fie_del(t_way **list);
void mx_exe_request(t_node **node, char **json);
void mx_mutex_command(t_node **node, char *json);
void mx_send_your_photo(t_node **node);
void mx_not_mutex(t_node **node, char **json);
void mx_send_back(t_node **node, char **json);

// Help
void mx_del_if_exist(char *name);
void mx_del_file(FILE *file, char **size, char **name);
void mx_check_file_size(FILE *file, char **size, char **name);
char *mx_add_char(char *str, char c);
char *mx_super_join(char *src1, char *src2, int fl);
char **mx_copy_arr(char **s);
char **mx_arrjoin(char **arr, char *str);
bool mx_for_file(char *json);
void mx_free_node(t_way **list);
void mx_del_list(t_list **list, int flag);
void mx_unset_file_node(t_way **list);
void mx_replace(char **old, char *new);
void mx_static_read(char ch[], char **str);
void mx_push_file_way(t_way **list, void *data);
void mx_push_back_t_way(t_way **list, void *data);
void mx_bites_str(SSL *ssl, char *json, char ch1);
void mx_file_bites(FILE *file, SSL *ssl, char ch1, char ch2);
void mx_file_format(char **arr, SSL *ssl, char ch1, char ch2);
void mx_file_size_close(SSL *ssl, char *str, char ch1, char ch2);
void *mx_mom(void *restrict dst, const void *restrict src, size_t n, size_t i);
int mx_arr_size(char **arr);

// Ilay
int mx_chat_screen(t_main **gtk);
void mx_enter_argv(char ***arr, t_client *client);
bool mx_check_file_format(char *path);
void mx_move_to_part_dir(char *name, char *user);
void mx_new_msg_back(t_user *us, t_list *list);
bool mx_check_last_index(t_user *us, t_list *list);
void check_edited(t_user *us, t_list *list, int size);
void mx_check_rename(t_main *m, t_info *info);
void mx_check_rcv_list(t_info *info, t_main *m);
void mx_check_sigup(t_main *m);
void mx_check_sigin(t_main *m);

void mx_voice_save(char *path, t_main *m);
int mx_recordcallback(const void *inputBuffer,
                      void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData);
void mx_save_snd_file(t_paTestData data, int numSamples, char *path);
int mx_daemon_state(int argc, char *argv[]);
char *mx_path_down(t_main *m);
bool mx_check_last_index(t_user *us, t_list *list);
void check_edited(t_user *us, t_list *list, int size);
void mx_check_rename(t_main *m, t_info *info);
void mx_check_rcv_list(t_info *info, t_main *m);
void mx_notif(t_add_m *s, t_user *i);

#endif
