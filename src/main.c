#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer, *s_time_layer_before, *s_time_layer_before_before, *s_time_layer_after, *s_time_layer_after_after;
static InverterLayer *inverter;

static void update_time() {
  ////Before Before Time!
  // Get a tm structure
  time_t temp = time(NULL) - 60 - 60; 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00", before_buffer[] = "00:00", before_before_buffer[] = "00:00", buffer_after[] = "00:00", buffer_after_after[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(before_before_buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(before_before_buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_before_before, before_before_buffer);
  
  ////Before time!
  temp += 60; 
  tick_time = localtime(&temp);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(before_buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(before_buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_before, before_buffer);
  
  ////Actual time!
  temp += 60; 
  tick_time = localtime(&temp);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
  
  ////After time!
  temp += 60; 
  tick_time = localtime(&temp);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer_after, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer_after, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_after, buffer_after);
  
  ////After After time!
  temp += 60; 
  tick_time = localtime(&temp);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer_after_after, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer_after_after, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_after_after, buffer_after_after);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  // Create time before TextLayer
  s_time_layer_before_before = text_layer_create(GRect(0, 33, 144, 20));
  text_layer_set_background_color(s_time_layer_before_before, GColorClear);
  text_layer_set_text_color(s_time_layer_before_before, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer_before_before, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_time_layer_before_before, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_before_before));
  
  // Create time before TextLayer
  s_time_layer_before = text_layer_create(GRect(0, 42, 144, 30));
  text_layer_set_background_color(s_time_layer_before, GColorClear);
  text_layer_set_text_color(s_time_layer_before, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer_before, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_time_layer_before, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_before));
  
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 62, 144, 30));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  // Create time TextLayer
  s_time_layer_after = text_layer_create(GRect(0, 86, 144, 30));
  text_layer_set_background_color(s_time_layer_after, GColorClear);
  text_layer_set_text_color(s_time_layer_after, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer_after, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(s_time_layer_after, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_after));
  
  // Create time TextLayer
  s_time_layer_after_after = text_layer_create(GRect(0, 110, 144, 20));
  text_layer_set_background_color(s_time_layer_after_after, GColorClear);
  text_layer_set_text_color(s_time_layer_after_after, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer_after_after, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_time_layer_after_after, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_after_after));
  
  
  //Invert colours!
  inverter = inverter_layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter));
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer_before_before);
  text_layer_destroy(s_time_layer_before);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_time_layer_after);
  text_layer_destroy(s_time_layer_after_after);
  inverter_layer_destroy(inverter);
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
}

static void deinit() {
  // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}