#include <tice.h>
#include <stdlib.h>
#include <stddef.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <string.h>
#include "oghamfont.h"

fontlib_font_t *futhark;
fontlib_font_t *ogham;

char *input(){
	const char *chars = "\0\0\0\0\0\0\0\0\0\0\"wrmh\0\0?[vqlg\0\0:zupkfc\0 ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";
	uint8_t key, i = 0;
	int x = 1;
	char buffer[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	delay(100);
	/*for (int j = 0; j < 50; j++){
		buffer[j] = "\"";
	}*/
	while((key = os_GetCSC()) != sk_Enter) {
		if(chars[key] && key != sk_Enter) {
			buffer[i++] = chars[key];
			gfx_SetTextXY(x+=5,15);
			gfx_PrintChar(chars[key]);
		}
	}
	//char *string = strtok(buffer, "\"");
	gfx_PrintStringXY(buffer, 20, 20);
	delay(1000);
	return buffer;
}

void th(const char *in, char *out){
	for(int i = 0; i < strlen(in); i++) {
  		if(in[i] == 't' && in[i+1] == 'h') {
   	 		*out = '1';
    			i++; // skip h
  		} else {
    		*out = in[i]; // copy existing character
  		}
  		out++;
	}
	*out = 0;
}

void SetupFonts(){
	futhark = fontlib_GetFontByIndex("FUTHARK", 0);
	ogham = fontlib_GetFontByIndex("OGHAM", 0);
}


void Transliterate(fontlib_font_t *font){
	char *toConvert;
	char ToConvert[50];
	gfx_BlitScreen();
	gfx_FillScreen(255);
	gfx_PrintStringXY("Input string:",1,1);
	toConvert = input();
	if (font == futhark){
		gfx_PrintStringXY("function will enter", 30, 34);
		delay(1000);
		th(toConvert, ToConvert);
	} else {
		for(int i = 0; i < strlen(toConvert); i++) {
			ToConvert[i] = toConvert[i];
		}
		ToConvert[strlen(toConvert)] = 0;
	}	
	gfx_FillScreen(255);
	gfx_PrintStringXY(ToConvert, 1, 25);
	fontlib_SetFont(font, 0);
	fontlib_SetCursorPosition(1,1);
	fontlib_DrawString(ToConvert);
	delay(100);
	do {
		kb_Scan();
	} while (kb_Data[6] != kb_Clear && !kb_IsDown(kb_KeyEnter));
	gfx_BlitBuffer();
}

void menu() {
	gfx_PrintStringXY("Calculator Transliterator", 1,1);
	gfx_HorizLine(1, 26, LCD_WIDTH);
	gfx_PrintStringXY("Menu:", LCD_WIDTH/2-10, 51);
	gfx_PrintStringXY("[1]: Elder Futhark", 1, 71);
	gfx_PrintStringXY("[2]: Ogham", 1, 91);
	gfx_PrintStringXY("press [clear] to exit", 1, 126);
	gfx_PrintStringXY("(c) Privacy_Dragon 2021", 1, LCD_HEIGHT-20);
	do {
		kb_Scan();
		if (kb_Data[3] == kb_1){ //Elder Futhark
			if (!futhark){
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"FUTHARK\" not found!", 1,1);
				gfx_PrintStringXY("Transfer FUTHARK.8xv to your calculator!",1,16);
			}
			else {
				Transliterate(futhark);
			}
		}
		else if (kb_Data[4] == kb_2){ //Ogham
			/*if (!ogham){
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"OGHAM\" not found!", 0,0);
				gfx_PrintStringXY("Please transfer OGHAM.8xv to your calculator!",0,15);
			}
			else {*/
				Transliterate(ogham_font);
			//}
		}
		/*if (kb_Data[6] == kb_Clear){
			return false;
		} else {
			return true;
		}*/
	} while (kb_Data[6] != kb_Clear);
}
	
int main(void) {
	gfx_Begin();
	fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
	SetupFonts();
	menu();
	//fontlib_SetFont(ogham_font, 0);
	//fontlib_DrawString("test test test");
	//while (!os_GetCSC());
	gfx_End();
}

//bij het laten zien van het resultaat moet je [enter] gebruiken, maar [clear] mag ook, maar dan schiet het gelijk door, waardoor je met clear het programma verlaat.
