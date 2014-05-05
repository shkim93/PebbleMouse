#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static AppTimer *timer;
static DictionaryIterator *iter;
char *pikachu = "X,Y,Z:                      ";

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  if (app_message_outbox_begin(&iter) != APP_MSG_OK) {
    return;
  }
  app_message_outbox_send();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
  if (app_message_outbox_begin(&iter) != APP_MSG_OK) {
    return;
  }
  app_message_outbox_send();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
  if (app_message_outbox_begin(&iter) != APP_MSG_OK) {
    return;
  }
  app_message_outbox_send();
}

// static void accel_handler(AccelData *data, uint32_t num_samples) {
//   //lastData = accel_service_peek (data);
//   text_layer_set_text(text_layer, "lastData"); 
// }

#define ACCEL_STEP_MS 50

static void timer_callback(void *data) {
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };

  accel_service_peek(&accel);

  int16_t i = accel.x;
  int16_t j = accel.y;
  int16_t k = accel.z;

  snprintf(pikachu,22,"X,Y,Z: %d,%d,%d",i,j,k);
  text_layer_set_text(text_layer, pikachu);

  app_message_outbox_begin(&iter);
  if (app_message_outbox_begin(&iter) != APP_MSG_OK) {
    return;
  }

  dict_write_data(iter,25,pikachu,sizeof(pikachu));

  app_message_outbox_send();

  //text_layer_set_text(text_layer, "HIII");
  timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void app_message_init(void) {
  // Reduce the sniff interval for more responsive messaging at the expense of
  // increased energy consumption by the Bluetooth module
  // The sniff interval will be restored by the system after the app has been
  // unloaded
  app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
  // Init buffers
  app_message_open(64, 16);
  // Register message handlers
  // app_message_register_inbox_received(in_received_handler);
}

static void init(void) {
  window = window_create();

  app_message_init();

  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });


  const bool animated = true;
  window_stack_push(window, animated);

  accel_data_service_subscribe(0, NULL);
  timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);


}

static void deinit(void) {
  accel_data_service_unsubscribe();
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
