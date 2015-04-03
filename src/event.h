#ifndef _EVENT_H
#define _EVENT_H

#include <string.h>
#include <dict.c/dict.h>
#include <list/list.h>

typedef void (*EventCallback)(void *context);

void event_emit(char *event_name, void *data);
void event_register(char *event_name, EventCallback fn);
void event_unregister(char *event_name, EventCallback fn);
dict_t* event_init();
void event_deinit();

#endif
