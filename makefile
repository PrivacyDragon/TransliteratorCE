# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= TRANSLIT
ICON ?= icon.png
DESCRIPTION ?= ""
COMPRESSED ?= YES
ARCHIVED ?= YES

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

# Convert a .fnt file into a .inc file
temp.bin: src/Ogham.fnt
	convfont -o fontpack -N "OGHAM" -P "ASCII" -V "Version 1.0" -A "Privacy_Dragon" -D "Ogham alphabet" -f src/Ogham.fnt temp.bin

OGHAM.8xv: temp.bin
	convbin -j bin -k 8xv -n OGHAM -i temp.bin -o OGHAM.8xv

temp2.bin: src/Futhark.fnt
	convfont -o fontpack -N "FUTHARK" -P "ASCII" -V "Version 1.0" -A "Privacy_Dragon" -D "Elder Futhark alphabet" -f src/Futhark.fnt temp2.bin

FUTHARK.8xv: temp2.bin
	convbin -j bin -k 8xv -n FUTHARK -i temp2.bin -o FUTHARK.8xv

all: OGHAM.8xv FUTHARK.8xv
