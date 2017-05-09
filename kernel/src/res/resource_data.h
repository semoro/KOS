
#ifndef RESOURCE_DATA_H
#define RESOURCE_DATA_H

#include <inttypes.h>

#define KOTLIN_LOGO_ID 1
#define FONT_ID 2


uint64_t get_resource_ptr_by_id(int id);

uint64_t get_resource_size_by_id(int id);


#endif
