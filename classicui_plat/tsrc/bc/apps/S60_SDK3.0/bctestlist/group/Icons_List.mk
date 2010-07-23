#
# Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
# Description:        
#

ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=\epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=\epoc32\data\z
endif

TARGETDIR=$(ZDIR)\resource\apps
HEADERDIR=\epoc32\include

ICONTARGETFILENAME=$(TARGETDIR)\bctestList.mif

#ok
HEADERFILENAME=$(HEADERDIR)\bctestList.mbg

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE :
	mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) \
	            /c8,8 ..\DataSrc\golgo2.bmp \
                /c8,8 ..\DataSrc\golgo3.bmp \
                /c8,8 ..\DataSrc\golgo4.bmp \
                /c8,8 ..\DataSrc\golgo5.bmp \
                /c8,8 ..\DataSrc\golgo6.bmp \
                /c8,8 ..\DataSrc\athene.bmp \
				/c8,8 ..\DataSrc\marked_add.bmp \
                /c8,1  ..\DataSrc\qgn_indi_marked_add.svg \
		        /c8,1 ..\DataSrc\check.bmp \
		        /c8,1 ..\DataSrc\non_check.bmp \
                /c8,1 ..\DataSrc\prop_group_small.bmp \
                /c8,1 ..\DataSrc\LShellIcon.bmp                

FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(HEADERFILENAME) && \
	@echo $(ICONTARGETFILENAME)

FINAL : do_nothing
