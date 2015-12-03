#ifndef __WINDOW_H
#define __WINDOW_H

#include "list.h"

struct window_module;
struct window_properties;

typedef int (*wd_init)(struct window_module* module);
typedef int (*wd_update)(struct window_module* module, float dt);
typedef int (*wd_render)(struct window_module* module);

/**
 * @brief      Window properties
 */
struct window_properties
{
	const char* name;
	int width;
	int length;
	int x;
	int y;
};

/**
 * @brief Windows describe the low level visible interface
 */
struct window_module{
	struct list_head list;
	const char* name;
	wd_init init;
	wd_update update;
	wd_render render;
	struct window_properties properties;
	void *data;
};

int window_register(struct window_module* window);
void window_print_available();
void window_start(struct window_properties prop);
int window_update(float dt);
int window_render(void);

void window_loop(void);
#endif
