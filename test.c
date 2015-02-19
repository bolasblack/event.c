
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "src/event.h"

// Helpers

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

// Callbacks

dict_t *event_pool;
char *last_emited_person_name;
char *last_emited_string;

typedef struct {
  char *name;
} Person;

static void for_event_register(void *data) {}
static void for_event_unregister(void *data) {}
static void for_event_emit_string(void *data) {
  last_emited_string = (char *)data;
}
static void for_event_emit_struct(void *data) {
  Person *person = (Person *)data;
  last_emited_person_name = person->name;
}

// Tests

static void
test_event_emit() {
  event_register("event:emit:string", for_event_emit_string);
  event_register("event:emit:person", for_event_emit_struct);

  event_emit("event:emit:string", "hello world");
  Person person = { .name = "c4605" };
  event_emit("event:emit:person", &person);

  assert(strcmp(last_emited_string, "hello world") == 0);
  assert(strcmp(last_emited_person_name, "c4605") == 0);
}

static void
test_event_register() {
  event_register("event:register", for_event_register);
  list_t *cbs = dict_get(event_pool, "event:register")->val;
  assert(list_find(cbs, for_event_register) != NULL);
}

static void
test_event_unregister() {
  event_register("event:unregister", for_event_unregister);
  event_unregister("event:unregister", for_event_unregister);
  list_t *cbs = dict_get(event_pool, "event:unregister")->val;
  assert(list_find(cbs, for_event_unregister) == NULL);
}

int
main(void){
  event_pool = event_init();
  puts("\n");
  test(event_register);
  test(event_unregister);
  test(event_emit);
  puts("... \x1b[32m100%\x1b[0m\n");
  event_deinit();
  return 0;
}
