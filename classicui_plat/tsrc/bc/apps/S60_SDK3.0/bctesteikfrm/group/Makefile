.PHONY: all

all: compile run

prepare:
	bldmake bldfiles

debug:
	abld build winscw udeb

compile:
	abld build winscw

arm:
	abld build armv5 urel

lib:
	abld freeze winscw
	abld build winscw udeb

armlib:
	abld freeze armv5
	abld build armv5 urel

track:
	tail -f %TMP%/epocwind.out

run:
	epoc

clean:
	abld clean winscw udeb
	abld clean armv5 urel
	abld clean winscw urel
	abld clean armv5 udeb
	del ..\sis\*.sisx

sis:
	make -C ..\sis

install:
	copy ..\sis\*.sisx %PUB%\exchange\liuxinyu
