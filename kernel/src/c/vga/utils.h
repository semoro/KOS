#ifndef VGA_TEXTMODE_UTILS_H
#define VGA_TEXTMODE_UTILS_H 

void vga_textmode_print_int(int x, int pos);
void vga_textmode_memdump(void* s, void* e, int pos);
void vga_textmode_print(const char* message, char attr, int pos);

#endif
