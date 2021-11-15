# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= OGHAM
ICON ?= icon.png
DESCRIPTION ?= ""
COMPRESSED ?= NO
ARCHIVED ?= YES

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

# Convert a .fnt file into a .inc file
temp.bin: Ogham.fnt
	convfont -o fontpack -N "OGHAM" -A "Privacy_Dragon" -D "Ogham alphabet" -f Ogham.fnt temp.bin

OGHAM.8xv: temp.bin
	convhex -a -v -n OGHAM temp.bin OGHAM.8xv
