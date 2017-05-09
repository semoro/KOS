#include "resource_data.h"

#define RES_START(name) _binary_##name##_start
#define RES_SIZE(name) _binary_##name##_size
#define RES_START_PTR(name) &RES_START(name)

#define DEF_RES(name) void* RES_START(name); uint64_t RES_SIZE(name);

#define RES_PTR_CASE(id, name) case id: return RES_START_PTR(name)
#define RES_SIZE_CASE(id, name) case id: return RES_SIZE(name)


DEF_RES(src_res_kotlin_dat)
DEF_RES(src_res_font_font_dat)

uint64_t get_resource_ptr_by_id(int id) {
    switch (id) {
        RES_PTR_CASE(KOTLIN_LOGO_ID, src_res_kotlin_dat);
        RES_PTR_CASE(FONT_ID, src_res_font_font_dat);
        default:
            return 0;
    }
}

uint64_t get_resource_size_by_id(int id) {
    switch (id) {
        RES_SIZE_CASE(KOTLIN_LOGO_ID, src_res_kotlin_dat);
        RES_SIZE_CASE(FONT_ID, src_res_font_font_dat);
        default:
            return 0;
    }
}
