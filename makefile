# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= TRANSLIT
ICON ?= icon.png
DESCRIPTION ?= "A transliterator"
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

temp3.bin: src/Nyctograph.fnt
	convfont -o fontpack -N "NYCTOGRAPH" -P "ASCII" -V "Version 1.0" -A "Privacy_Dragon" -D "Lewis Carroll's Nyctograph alphabet" -f src/Nyctograph.fnt temp3.bin

NYCTO.8xv: temp3.bin
	convbin -j bin -k 8xv -n NYCTO -i temp3.bin -o NYCTO.8xv

temp4.bin: src/Proto-Sinaitic.fnt
	convfont -o fontpack -N "PROTO-SINAITIC" -P "ASCII" -V "Version 1.0" -A "Privacy_Dragon" -D "Proto-sinaitic alphabet" -f src/Proto-Sinaitic.fnt temp4.bin

SINAITIC.8xv: temp4.bin
	convbin -j bin -k 8xv -n SINAITIC -i temp4.bin -o SINAITIC.8xv

temp5.bin: src/Phoenician.fnt
	convfont -o fontpack -N "PHOENICIAN" -P "ASCII" -V "Version 1.0" -A "Privacy_Dragon" -D "Phoenician alphabet" -f src/Phoenician.fnt temp5.bin

PHOENIC.8xv: temp5.bin
	convbin -j bin -k 8xv -n PHOENIC -i temp5.bin -o PHOENIC.8xv


all: OGHAM.8xv FUTHARK.8xv NYCTO.8xv SINAITIC.8xv PHOENIC.8xv
