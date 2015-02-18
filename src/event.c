#include "event.h"

static dict_t *s_callbacks;

static list_t* get_event_handler_list(char *event_name) {
  list_t *result;
  dict_pair_t *pair = dict_get(s_callbacks, event_name);

  if (pair) {
    result = pair->val;
  } else {
    result = list_new();
    dict_set(s_callbacks, event_name, result);
  }
  return result;
}

static void foreach_event_callback(char *event_name, void (*processer)(list_node_t *, list_t *, void *), void *context) {
  list_node_t *node;
  list_t *callbacks = get_event_handler_list(event_name);
  list_iterator_t *it = list_iterator_new(callbacks, LIST_HEAD);
  while ((node = list_iterator_next(it))) {
    processer(node, callbacks, context);
  }
}

static void fire_handler(list_node_t *node, list_t *callbacks, void *context) {
  void *data = context;
  EventCallback fn = (EventCallback)node->val;
  fn(data);
}

static void remove_handler(list_node_t *node, list_t *callbacks, void *context) {
  EventCallback fn = (EventCallback)context;
  if (node->val == fn) {
    list_remove(callbacks, node);
  }
}

static void free_callbacks(char *key, void *list) {
  list_destroy((list_t *)list);
}

void event_emit(char *event_name, void *data) {
  foreach_event_callback(event_name, fire_handler, data);
}

void event_unregister(char *event_name, EventCallback fn) {
  foreach_event_callback(event_name, remove_handler, fn);
}

void event_register(char *event_name, EventCallback fn) {
  list_t *callbacks = get_event_handler_list(event_name);
  list_node_t *node = list_node_new(fn);
  list_rpush(callbacks, node);
}

void event_init() {
  s_callbacks = dict_new();
  s_callbacks->free = free_callbacks;
}

void event_deinit() {
  dict_destroy(s_callbacks);
}
