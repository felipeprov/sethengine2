
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "window.h"

static LIST_HEAD(window_head);
static struct window_module* active_window;

int window_register(struct window_module* window)
{
	printf("Added %s\n", window->name);
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
	active_window->properties = prop;
	active_window->init(active_window);
}

int window_update(float dt)
{
	return active_window->update(active_window, dt);
}

int window_render(void)
{
	return active_window->render(active_window);
}

void window_loop(void)
{
	int rc;
	do
	{
		window_render();
		rc = window_update(100);
	}while(rc == 0);
}