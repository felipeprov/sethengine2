
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "window.h"

static LIST_HEAD(window_head);

int window_register(struct window_module* window)
{
	printf("Added %s\n", window->name);
	list_add_tail(&window->list, &window_head);

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