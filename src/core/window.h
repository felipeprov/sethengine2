#ifndef __WINDOW_H
#define __WINDOW_H

#include "list.h"

typedef int (*window_init)(void);

/**
 * @brief      Windows describe the low level visible interface
 */
struct window_module{
	struct list_head list;
	const char* name;
	window_init init;
};

int window_register(struct window_module* window);
void window_print_available();
#endif