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
# Configuration for Avkon, Callstatus & AknMemoryCardUI bitmaps.
# ----------------------------------------------------------------------------

TARGETDIR=$(ZDIR)\resource\apps
HEADERDIR=\epoc32\include
ICONTARGETFILENAME=$(TARGETDIR)\avkon2.mif
HEADERFILENAME=$(HEADERDIR)\avkon.mbg
CALLSTATUSICONTARGETFILENAME=$(TARGETDIR)\callstatus.mif
CALLSTATUSHEADERFILENAME=$(HEADERDIR)\callstatus.mbg
AKNMEMORYCARDUITARGETFILENAME=$(TARGETDIR)\aknmemorycardui.mif
AKNMEMORYCARDUIHEADERFILENAME=$(HEADERDIR)\aknmemorycardui.mbg

TARGETS_AVKON=$(HEADERFILENAME) $(ICONTARGETFILENAME) $(TARGETDIR)\avkon2.mbm 
TARGETS_CALLSTATUS=$(CALLSTATUSHEADERFILENAME) $(CALLSTATUSICONTARGETFILENAME) $(TARGETDIR)\callstatus.mbm 
TARGETS_AKNMEMORYCARDUI=$(AKNMEMORYCARDUIHEADERFILENAME) $(AKNMEMORYCARDUITARGETFILENAME) $(TARGETDIR)\aknmemorycardui.mbm

ICONLIST_SOURCELIST=$(foreach FILE, \
                     $(basename $(shell $(type iconlist.txt))),\
                     $(wildcard $(EPOCROOT)epoc32\s60\icons\$(FILE).svg \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE).bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask.bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask_soft.bmp))

ICONLIST2_SOURCELIST=$(foreach FILE, \
                     $(basename $(shell $(type iconlist2.txt))),\
                     $(wildcard $(EPOCROOT)epoc32\s60\icons\$(FILE).svg \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE).bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask.bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask_soft.bmp))

ICONLIST3_SOURCELIST=$(foreach FILE, \
                     $(basename $(shell $(type iconlist3.txt))),\
                     $(wildcard $(EPOCROOT)epoc32\s60\icons\$(FILE).svg \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE).bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask.bmp \
                                $(EPOCROOT)epoc32\s60\bitmaps\$(FILE)_mask_soft.bmp))

BLD : ;

CLEAN :
	-del $(TARGETS_AVKON)
	-del $(TARGETS_CALLSTATUS)
	-del $(TARGETS_AKNMEMORYCARDUI)

LIB : ;

CLEANLIB : ;

# ----------------------------------------------------------------------------
# NOTE 1: DO NOT DEFINE MASK FILE NAMES! They are included automatically by
# MifConv if the mask depth is defined.
#
# NOTE 2: Usually, source paths should not be included in the bitmap
# definitions. MifConv searches for the icons in all icon directories in a
# predefined order, which is currently \s60\icons, \s60\bitmaps2.
# The directory \s60\icons is included in the search only if the feature flag
# __SCALABLE_ICONS is defined.
# ----------------------------------------------------------------------------
$(TARGETS_AVKON) ..\avkon2mifheader\avkon2mifheader_inst.cpp : iconlist.txt $(ICONLIST_SOURCELIST)
	mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) /F$<
	MifToCdlIndex -p..\Avkon2MifHeader -s $(ICONTARGETFILENAME) Avkon2MifHeader 0x102827CF

$(TARGETS_CALLSTATUS) : iconlist2.txt $(ICONLIST2_SOURCELIST)
	mifconv $(CALLSTATUSICONTARGETFILENAME) /h$(CALLSTATUSHEADERFILENAME) /F$<

$(TARGETS_AKNMEMORYCARDUI) : iconlist3.txt $(ICONLIST3_SOURCELIST)
	mifconv $(AKNMEMORYCARDUITARGETFILENAME) /h$(AKNMEMORYCARDUIHEADERFILENAME) /F$<

$(OLDUDEBZDIR)\resource\apps\avkon2.mif \
$(OLDURELZDIR)\resource\apps\avkon2.mif : $(ZDIR)\resource\apps\avkon2.mif
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps\avkon2.mbm \
$(OLDURELZDIR)\resource\apps\avkon2.mbm : $(ZDIR)\resource\apps\avkon2.mbm 
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps\callstatus.mif\
$(OLDURELZDIR)\resource\apps\callstatus.mif : $(ZDIR)\resource\apps\callstatus.mif
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps\callstatus.mbm \
$(OLDURELZDIR)\resource\apps\callstatus.mbm : $(ZDIR)\resource\apps\callstatus.mbm 
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps\aknmemorycardui.mif \
$(OLDURELZDIR)\resource\apps\aknmemorycardui.mif: $(ZDIR)\resource\apps\aknmemorycardui.mif
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps\aknmemorycardui.mbm \
$(OLDURELZDIR)\resource\apps\aknmemorycardui.mbm : $(ZDIR)\resource\apps\aknmemorycardui.mbm 
	-copy $< $@

$(OLDUDEBZDIR)\resource\apps \
$(OLDURELZDIR)\resource\apps : 
	$(call ifnotexistd,$@)


MAKMAKE \
RESOURCE: $(TARGETS_AVKON) \
          $(TARGETS_CALLSTATUS) \
          $(TARGETS_AKNMEMORYCARDUI) \
          $(OLDUDEBZDIR)\resource\apps \
          $(OLDURELZDIR)\resource\apps \
          $(OLDUDEBZDIR)\resource\apps\avkon2.mif \
          $(OLDURELZDIR)\resource\apps\avkon2.mif \
          $(OLDUDEBZDIR)\resource\apps\avkon2.mbm \
          $(OLDURELZDIR)\resource\apps\avkon2.mbm \
          $(OLDUDEBZDIR)\resource\apps\callstatus.mif \
          $(OLDURELZDIR)\resource\apps\callstatus.mif \
          $(OLDUDEBZDIR)\resource\apps\callstatus.mbm \
          $(OLDURELZDIR)\resource\apps\callstatus.mbm \
          $(OLDUDEBZDIR)\resource\apps\aknmemorycardui.mif \
          $(OLDURELZDIR)\resource\apps\aknmemorycardui.mif \
          $(OLDUDEBZDIR)\resource\apps\aknmemorycardui.mbm \
          $(OLDURELZDIR)\resource\apps\aknmemorycardui.mbm \
	  ..\avkon2mifheader\avkon2mifheader_inst.cpp

FREEZE : ;

SAVESPACE : ;

RELEASABLES :
	@echo $(TARGETS_AVKON)&& \
	@echo $(TARGETS_CALLSTATUS)&& \
	@echo $(TARGETS_AKNMEMORYCARDUI)

FINAL : ;
