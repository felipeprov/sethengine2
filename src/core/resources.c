#include "resources.h"
#include <string.h>

static LIST_HEAD(resource_loader_head);
static LIST_HEAD(resources_head);

static const char* get_extension(const char* path)
{
	const char* ext = strrchr(path, '.');
	if(ext)
		ext++;

	return ext;
}

void resource_loader_register(struct resource_loader* loader)
{
	list_add_tail(&loader->list, &loader->list);
}

void resource_process(struct resource* res)
{
	res->loader->process(res);
}

struct resource* resource_load(const char* filename)
{
	struct list_head *pos;
	const char* ext = get_extension(filename);

	if(ext == 0)
		return NULL;

	list_for_each(pos, &resource_loader_head)
	{
		struct resource_loader* tmp = list_entry(pos, struct resource_loader, list);
		
		if(strcmp(tmp->ext, ext) == 0) 
		{
			struct resource* res = tmp->load(tmp, filename);
			res->loader = tmp;

			list_add_tail(&tmp->list, &resources_head);
			return res;
		}
	}

	return NULL;
}