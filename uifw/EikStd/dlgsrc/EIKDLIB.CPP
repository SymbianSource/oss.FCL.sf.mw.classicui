/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


#include "EIKDLIB.H"
#include <eikenv.h>
#include <eikpanic.h>
#include <eikon.hrh>

// Static DLL functions
GLDEF_C void Panic(TEikPanic aPanic)
    {
    _LIT(KPanicCat,"EIKDLG");
    User::Panic(KPanicCat,aPanic);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CEikDlgLibrary
//
///////////////////////////////////////////////////////////////////////////////////////
CEikDlgLibrary::CEikDlgLibrary()
    {
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ResourceFile
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TFileName CEikDlgLibrary::ResourceFile()
    {
    _LIT(KResFileName,"z:\\resource\\eikdlg.rsc");
    return KResFileName();
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ControlFactory
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TCreateByTypeFunction  CEikDlgLibrary::ControlFactory()
    {
    return CreateByTypeL;
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CreateByTypeL
//
///////////////////////////////////////////////////////////////////////////////////////
SEikControlInfo CEikDlgLibrary::CreateByTypeL(TInt /*aControlType*/)
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL;
    controlInfo.iTrailerTextId = 0;
    controlInfo.iFlags = 0;
/*
    if(aControlType == EEikCtDialogToolBar)
        {
        controlInfo.iControl = new(ELeave) CEikDialogToolBar;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        }
*/
    return controlInfo;
    }

///////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////////
