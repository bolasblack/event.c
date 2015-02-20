
# event.c

Simple PubSub pattern implemented by c.

## API

Below is the public api currently provided by "event.c".

## dict_t \*event_init();

Initialize event pool, and return it.

```c
dict_t *event_pool = event_init();
```

## void event_deinit()

Free the event pool.

```c
event_deinit();
```

## void event_register(char \*event_name, EventCallback callback)

Register a callback for the event.

```c
static void on_event_test(void *data) {
  char *string = (char *)data;
  puts(string);
}

event_register("test", on_event_test);
```

## void event_unregister(char \*event_name, EventCallback callback)

Unregister a callback for the event.

```c
static void on_event_test(void *data) {
  char *string = (char *)data;
  puts(string);
}

event_unregister("test", on_event_test);
```

## void event_emit(char \*event_name, void *data)

Emit an event with data;

```c
static void on_event_test(void *data) {
  char *string = (char *)data;
  puts(string);
}

event_emit("test", "hello world");
```


## Examples

```c
typedef struct {
  char *name;
} User;

static void unregister_event_callback(void *data) {
  puts((char *)data);
  event_unregister("test event name", unregister_event_callback);
}

static void register_event_example() {
  event_register("test event name", unregister_event_callback);
}

static void emit_event_example() {
  event_emit("test event name", "hello world");
}

int main(void) {
  event_init();
  register_and_unregister_event_example();
  emit_event_example();
  event_deinit();
}
```

stdout:

    hello world

## Testing

    $ make test

## License

(The MIT License)

Copyright (c) 2015 c4605 &lt;bolasblack@gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
