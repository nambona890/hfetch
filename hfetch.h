#ifndef HFETCH_H
#define HFETCH_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFERSIZE 256 // Default length for all used buffers
#define PADDING 44     // Cliorb size
#define FPS 15         // Speed of animation/stats reloading

// Escape codes for drawing 
#define CLEARSCREEN "\033[2J"
#define COLOR_CYAN "\033[38;5;14m"
#define COLOR_RESET "\033[0m"
#define POS "\033[%d;%dH" // Move cursor to y;x 

#define NULL_RETURN(ptr) do { if (ptr == NULL) return; } while (0)
#define UNUSED_ARG(arg) do { (void)(arg); } while (0)

typedef __uint8_t BOOL;
#define TRUE 1
#define FALSE 0

typedef struct system_stats {
    char user_name[BUFFERSIZE],
         host_name[BUFFERSIZE],
         datetime[BUFFERSIZE],
         os_name[BUFFERSIZE],
         kernel_version[BUFFERSIZE],
         desktop_name[BUFFERSIZE],
         shell_name[BUFFERSIZE],
         terminal_name[BUFFERSIZE],
         cpu_name[BUFFERSIZE],
         cpu_usage[BUFFERSIZE],
         ram_usage[BUFFERSIZE],
         swap_usage[BUFFERSIZE],
         process_count[BUFFERSIZE],
         uptime[BUFFERSIZE],
         battery_charge[BUFFERSIZE],
         disk_usage[BUFFERSIZE][2][BUFFERSIZE],
         gpu_stats[BUFFERSIZE][3][BUFFERSIZE];
    size_t mount_count,gpu_count;
    struct
    {
        BOOL disable_print_disk_usage : 1;
		BOOL disable_print_gpu : 1;
    } flags;
	pthread_mutex_t mutex;
} system_stats;

typedef struct animation_object {
    size_t current_frame;
    size_t frame_count;
    char *frames[];
} animation_object;

typedef struct dynamic_string {
    size_t reserved_size;
    char* str;
} dynamic_string;

void reserve_dynamic_string(dynamic_string* dyn_str, size_t n)
{
    NULL_RETURN(dyn_str);
    if(n==0)
    {
        return;
    }
    const size_t combined_length = dyn_str->reserved_size+n;
    int reserve_more = 0;
    while(dyn_str->reserved_size<combined_length)
    {
        dyn_str->reserved_size*=2;
        reserve_more = 1;
    }
    if(reserve_more)
    {
        dyn_str->str = realloc(dyn_str->str,dyn_str->reserved_size);
    }
}

void append_dynamic_string(dynamic_string* dest, const char* src)
{
    NULL_RETURN(src);
    NULL_RETURN(dest);
    const size_t source_length = strlen(src);
    const size_t dest_length = strlen(dest->str);
    const size_t combined_length = source_length+dest_length+1;
    if(combined_length >= dest->reserved_size)
    {
        while(dest->reserved_size <= combined_length)
        {
            dest->reserved_size *= 2;
        }
        dest->str = realloc(dest->str,dest->reserved_size);
    }
    strncat(dest->str,src,source_length);
}

dynamic_string new_dynamic_string(const char* init)
{
    dynamic_string ret_string;
    const size_t init_length = strlen(init);
    ret_string.reserved_size = 1;
    while(ret_string.reserved_size <= init_length)
    {
        ret_string.reserved_size *= 2;
    }
    ret_string.str = malloc(ret_string.reserved_size);
    strncpy(ret_string.str,init,init_length);
    return ret_string;
}

void free_dynamic_string(dynamic_string* dyn_str)
{
    free(dyn_str->str);
}

#endif // HFETCH_H
