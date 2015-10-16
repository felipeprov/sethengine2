
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "window.h"

static LIST_HEAD(window_head);
static struct window_module* active_window;

int window_register(struct window_module* window)
{
	printf("Window added %s\n", window->name);
	list_add_tail(&window->list, &window_head);
	active_window = window;

	return 0;
}

void window_print_available()
{
	struct list_head *pos;

	int i = 0;
	list_for_each(pos, &window_head)
	{
		struct window_module* tmp = list_entry(pos, struct window_module, list);
		printf("%d - %s\n", i++, tmp->name);
	}
}

void window_start(struct window_properties prop)
{
	if(active_window == 0)
		return;

	active_window->properties = prop;
	active_window->init(active_window);
}

int window_update(float dt)
{
	if(active_window == 0)
		return -1;

	return active_window->update(active_window, dt);
}

int window_render(void)
{
	if(active_window == 0)
		return -1;

	return active_window->render(active_window);
}