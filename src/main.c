#include <tice.h>
#include <stdlib.h>
#include <stddef.h>
#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <string.h>

fontlib_font_t *futhark;
fontlib_font_t *nyctograph;
fontlib_font_t *ogham;
fontlib_font_t *phoenician;
fontlib_font_t *protoSinaitic;

char *input(fontlib_font_t *font){
	const char *chars = "\0\0\0\0\0\0\0\0\0\0\"wrmh\0\0?[vqlg\0\0:zupkfc\0 ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";
	uint8_t key, i = 0;
	int x = 1;
	int y = 15;
	char buffer[110];
	char thbuffer[110];
	for (int j = 0; j < 110; j++){
		buffer[j] = 0;
		thbuffer[j] = 0;
	}
	gfx_SetTextBGColor(254);
	while((key = os_GetCSC()) != sk_Enter) {
		if ((chars[key] && key != sk_Enter && i < 109) || key == sk_Del) {
			if (key == sk_Del && i>0){ //Delete key
				//Delete the last character.
				//This is done by going back one character. For what the user sees, the last character is replaced by a space.
				i--;
				gfx_SetTextXY(x,y);
				gfx_PrintChar('_');
				x-=10;
			} else {
				buffer[i++] = chars[key];
				if (x >= LCD_WIDTH-10){
					y += 15;
					x = 1;
				}
				gfx_SetTextXY(x+=10,y);
				gfx_PrintChar(chars[key]);
			}
		}
	}
	//Now deal with the replacing of 'th' with '1' if the font is futhark.
	if (font == futhark){
		int outnr = 0;
		for (i = 0; i < strlen(buffer); i++) {
			if (buffer[i] == 't' && buffer[i+1] == 'h') {
				thbuffer[outnr] = '1';
				i++;
			} else {
				thbuffer[outnr] = buffer[i];
			}
			outnr++;
		}
		thbuffer[outnr] = 0;
		return thbuffer;
	} else {
		buffer[i++] = 0;
		return buffer;
	}
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
	gfx_BlitScreen();
	gfx_FillScreen(255);
	gfx_PrintStringXY("Input string:",1,1);
	toConvert = input(font);
	gfx_FillScreen(255);
	fontlib_SetFont(font, 0);
	fontlib_SetCursorPosition(1,1);
	fontlib_DrawString(toConvert);
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
	gfx_PrintStringXY("(c) Privacy_Dragon 2021-2022", 1, LCD_HEIGHT-20);
	do {
		kb_Scan();
		if (kb_Data[3] == kb_1){ //Elder Futhark
			if (!futhark){
				gfx_BlitScreen();
				gfx_FillScreen(255);
				gfx_PrintStringXY("ERROR: Font \"FUTHARK\" not found!", 1,1);
				gfx_PrintStringXY("Transfer FUTHARK.8xv to your calc!",1,16);
				while (!os_GetCSC());
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
				while (!os_GetCSC());
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
				while (!os_GetCSC());
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
				while (!os_GetCSC());
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
	} while (kb_Data[6] != kb_Clear);
}
	
int main(void) {
	gfx_Begin();
	fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
	SetupFonts(); \\the fonts are set up here.
	menu(); \\everything happens from the menu. the menu is the next 'main' kinda.
	gfx_End();
}
