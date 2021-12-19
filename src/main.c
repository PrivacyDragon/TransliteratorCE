#include <tice.h>
#include <stdlib.h>
#include <stddef.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <string.h>
#include "oghamfont.h"

fontlib_font_t *futhark;
fontlib_font_t *nyctograph;
fontlib_font_t *ogham;
fontlib_font_t *phoenician;
fontlib_font_t *protoSinaitic;

char *input(){
	const char *chars = "\0\0\0\0\0\0\0\0\0\0\"wrmh\0\0?[vqlg\0\0:zupkfc\0 ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";
	uint8_t key, i = 0;
	int x = 1;
	int y = 15;
	char buffer[110];//= "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	delay(100);
	for (int j = 0; j < 110; j++){
		buffer[j] = 0;
		//buffer++;
	}
	while((key = os_GetCSC()) != sk_Enter) {
		if (chars[key] && key != sk_Enter && i < 109) {
			/*if (key == sk_Del){ //Delete key
				//Delete the last character.
				//This is done by going back one character. For what the user sees, the last character is replaced by a space.
				i--;
				gfx_SetTextXY(x-=10,y);
				gfx_PrintChar('-');
				x-=10;
			}*/
			buffer[i++] = chars[key];
			if (x >= LCD_WIDTH-10){
				y += 15;
				x = 1;
			}
			gfx_SetTextXY(x+=10,y);
			gfx_PrintChar(chars[key]);
		}
	}
	//buffer[i++] = 0;
	//char *string = strtok(buffer, "\"");
	//gfx_PrintStringXY(buffer, 20, 20);
	//delay(1000);
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
	nyctograph = fontlib_GetFontByIndex("NYCTO", 0);
	ogham = fontlib_GetFontByIndex("OGHAM", 0);
	phoenician = fontlib_GetFontByIndex("PHOENIC", 0);
	protoSinaitic = fontlib_GetFontByIndex("SINAITIC", 0);
}


void Transliterate(fontlib_font_t *font){
	char *toConvert;
	char ToConvert[110];
	gfx_BlitScreen();
	gfx_FillScreen(255);
	gfx_PrintStringXY("Input string:",1,1);
	toConvert = input();
	if (font == futhark){
		//gfx_PrintStringXY("function will enter", 30, 34);
		//delay(1000);
		th(toConvert, ToConvert);
	} else {
		for(int i = 0; i < strlen(toConvert); i++) {
			ToConvert[i] = toConvert[i];
		}
		ToConvert[strlen(toConvert)] = 0;
	}	
	gfx_FillScreen(255);
	//gfx_PrintStringXY(ToConvert, 1, 25);
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
	gfx_PrintStringXY("[2]: Nyctograph", 1, 91);
	gfx_PrintStringXY("[3]: Ogham", 1, 111);
	gfx_PrintStringXY("[4]: Phoenician", 1, 131);
	gfx_PrintStringXY("[5]: Proto-sinaitic", 1, 151);
	gfx_PrintStringXY("press [clear] to exit", 1, 176);
	gfx_PrintStringXY("(c) Privacy_Dragon 2021", 1, LCD_HEIGHT-20);
	do {
		kb_Scan();
		if (kb_Data[3] == kb_1){ //Elder Futhark
			if (!futhark){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"FUTHARK\" not found!", 1,1);
				gfx_PrintStringXY("Transfer FUTHARK.8xv to your calc!",1,16);
				os_GetCSC();
				gfx_BlitBuffer();
			}
			else {
				Transliterate(futhark);
			}
		}
		else if (kb_Data[4] == kb_2){ //Nyctograph
			if (!nyctograph){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"NYCTO\" not found!", 0,0);
				gfx_PrintStringXY("Please transfer NYCTO.8xv to your calc!",0,15);
				os_GetCSC();
				gfx_BlitBuffer();
			}
			else {
				Transliterate(nyctograph);
			}
		}
		else if (kb_Data[5] == kb_3){ //Ogham
			if (!ogham){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"OGHAM\" not found!", 0,0);
				gfx_PrintStringXY("Please transfer OGHAM.8xv to your calc!",0,15);
				os_GetCSC();
				gfx_BlitBuffer();
			}
			else {
				Transliterate(ogham);
			}
		}
		else if (kb_Data[3] == kb_4){ //Phoenician
			if (!protoSinaitic){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"PHOENIC\" not found!", 0,0);
				gfx_PrintStringXY("Please transfer PHOENIC.8xv to your calc!",0,15);
				os_GetCSC();
				gfx_BlitBuffer();
			}
			else {
				Transliterate(phoenician);
			}
		}
		else if (kb_Data[4] == kb_5){ //Proto-sinaitic
			if (!protoSinaitic){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"SINAITIC\" not found!", 1,1);
				gfx_PrintStringXY("Please transfer SINAITIC.8xv to your calc!", 1, 16);
				while (!os_GetCSC());
				gfx_BlitBuffer();
			}
			else {
				Transliterate(protoSinaitic);
			}
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
