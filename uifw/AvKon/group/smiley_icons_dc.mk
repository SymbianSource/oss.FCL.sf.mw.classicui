#
# Copyright (c) 2004-2008 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:  Icons makefile for project AVKON
#
include $(EPOCROOT)epoc32/tools/shell/$(notdir $(basename $(SHELL))).mk


OLDUDEBZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\udeb\z
OLDURELZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\urel\z
ZDIR=$(EPOCROOT)epoc32\data\z

# ----------------------------------------------------------------------------
# Configuration for smiley bitmaps.
# ----------------------------------------------------------------------------

TARGETDIR=$(ZDIR)\resource\apps
HEADERDIR=\epoc32\include
ICONTARGETFILENAME=$(TARGETDIR)\smiley.mif
HEADERFILENAME=$(HEADERDIR)\smiley.mbg

TARGETS_SMILEY=$(HEADERFILENAME) $(ICONTARGETFILENAME)

ICONLIST_SOURCELIST=$(foreach FILE, \
                     $(basename $(shell $(type smileyiconlist.txt))),\
                     $(EPOCROOT)epoc32\s60\icons\$(FILE).svg)

BLD : ;

CLEAN :
	-del $(TARGETS_SMILEY)

LIB : ;

CLEANLIB : ;

$(TARGETS_SMILEY) : smileyiconlist.txt $(ICONLIST_SOURCELIST)
	mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) /F$<

$(OLDUDEBZDIR)\resource\apps\smiley.mif \
$(OLDURELZDIR)\resource\apps\smiley.mif : $(ZDIR)\resource\apps\smiley.mif
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps \
$(OLDURELZDIR)\resource\apps : 
	$(call ifnotexistd,$@)


MAKMAKE \
RESOURCE: $(TARGETS_SMILEY) \
          $(OLDUDEBZDIR)\resource\apps \
          $(OLDURELZDIR)\resource\apps \
          $(OLDUDEBZDIR)\resource\apps\smiley.mif \
          $(OLDURELZDIR)\resource\apps\smiley.mif

FREEZE : ;

SAVESPACE : ;

RELEASABLES :
	@echo $(TARGETS_SMILEY)

FINAL : ;
