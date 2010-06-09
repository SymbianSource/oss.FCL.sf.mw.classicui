# 
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

case : bctestakncase
tested header files:
<aknskinnableclock.h>
<aknsmallindicator.h>
<aknsoftnotificationparameters.h>
<aknsoftnotifier.h>
<aknstatuspaneutils.h>
<aknstylusactivatedpopupcontent.h>
<aknsyncdraw.h>
<akntasklist.h>
<akntransitionutils.h>
<aknvolumepopup.h>
<aknsystemfont.h>

case : bctesteikcase
tested header files:
<eikalmct.h>
<eikslbd.h>
<eiksoftkeyimage.h>
<eiksrvui.h>

case : bctestfindcase
tested header files:
<finditemdialog.h>
<finditemmenu.h>
<findutil.h>
<itemfinder.h>

case : bctestjplangcase
tested header files:
<jplangutil.h>
<numbergrouping.h>

case :bctestpslncase
tested header files:
<PslnFWAppThemeHandler.h>
<PslnFWBaseContainer.h>
<PslnFWBaseView.h>
<PslnFWIconHelper.h>
<PslnFWPluginHandler.h>

Warning:

there would be some error in the header file "aknstylusactivatedpopupcontent.h"
when compiling the project on the Week38 SDK,the user can modify the header file
by add the "class TAknWindowComponentLayout;" predeclaration to reslove the problem




