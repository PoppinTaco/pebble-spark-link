#include <pebble.h>

#define KEY_TOGGLE 0

static Window *window;
static TextLayer *text_layer;

static void send_int(int key, int cmd)
{
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	
	Tuplet value = TupletInteger(key, cmd);
	dict_write_tuplet(iter, &value);
	
	app_message_outbox_send();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	send_int(KEY_TOGGLE, 0);	//Value can be any int for now
}

static void click_config_provider(void *context) 
{
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window *window) 
{
	//Create TextLayer
	text_layer = text_layer_create(GRect(0, 0, 144, 168));
	text_layer_set_text(text_layer, "Press SELECT to toggle Spark pin D0");
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) 
{
	//Destroy TextLayer
	text_layer_destroy(text_layer);
}

static void init(void) 
{
	//Create Window
	window = window_create();
	window_set_click_config_provider(window, click_config_provider);
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});

//Prepare AppMessage
app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

	window_stack_push(window, true);
}

static void deinit(void) 
{
	//Destroy Window
	window_destroy(window);
}

int main(void) 
{
	init();
	app_event_loop();
	deinit();
}
