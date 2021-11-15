#include "oghamfont.h"

/* This contains the raw data for the font. */
static const unsigned char ogham_font_data[] = {
    #include "oghamfont.inc"
};
/* However, C89 does not allow us to typecast a byte array into a
fontlib_font_t pointer directly, so we have to use a second statement to do it,
though helpfully we can at least do it in the global scope. */
const fontlib_font_t *ogham_font = (fontlib_font_t *)ogham_font_data;
