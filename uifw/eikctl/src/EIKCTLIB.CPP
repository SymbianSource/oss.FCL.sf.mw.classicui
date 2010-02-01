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


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikctrlstatus.h>
#endif
#include <eikctlib.h>
#include <eikpanic.h>
#include <eikon.hrh>
#include <eikmfne.h>
#include <eikseced.h>

#include <eikprogi.h>
#include <eikfpne.h>
#include <eikrted.h>

#include <eikgted.h>
#include <eikspace.h>
#include <eikfnlab.h>
#include <eikclb.h>
#include <eikctl.rsg>
#include <aknipfed.h>
#include <eikcoctlpanic.h>
#include <aknlocationed.h>
#include <aknuniteditor.h>

// Static DLL functions
GLDEF_C void Panic(TEikPanic aPanic)
    {
    _LIT(KPanicCat,"EIKCTL");
    User::Panic(KPanicCat,aPanic);
    }

GLDEF_C void Panic(TEikCoCtlPanic aPanic)
    {
    _LIT(KPanicCat,"AVKON-EIKCOCTL");
    User::Panic(KPanicCat,aPanic);
    }

CEikCtlLibrary::CEikCtlLibrary()
    {
    }

EXPORT_C TFileName CEikCtlLibrary::ResourceFile()
    // static
    {
    _LIT(KResFileName,"z:\\resource\\eikctl.rsc");
    return KResFileName();
    }

EXPORT_C TCreateByTypeFunction  CEikCtlLibrary::ControlFactory()
    // static
    {
    return CreateByTypeL;
    }

EXPORT_C void CEikCtlLibrary::InitializeL()
    // static
    {
    }

/**
 * @internal
 * Internal to Symbian
 * @since App-Framework_6.1
 */
EXPORT_C TCreateButtonGroupByTypeFunction CEikCtlLibrary::ButtonGroupFactory()
    {//static
    return CreateButtonGroupByTypeL;
    }

SEikControlInfo CEikCtlLibrary::CreateByTypeL(TInt aControlType)
    // static
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL;
    controlInfo.iTrailerTextId = 0;
    controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case EEikCtRichTextEditor:
        controlInfo.iControl = new(ELeave) CEikRichTextEditor;
        break;
    case EEikCtSecretEd:
        controlInfo.iControl = new(ELeave) CEikSecretEditor;
        break;

    case EEikCtListBox:
        controlInfo.iControl = new(ELeave) CEikTextListBox;
        break;
    case EEikCtColListBox:
        controlInfo.iControl = new(ELeave) CEikColumnListBox;
        break;

    case EEikCtProgInfo:
        controlInfo.iControl = new(ELeave) CEikProgressInfo;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
// Reintroduced, JIn 1/2/2001.
    case EEikCtFlPtEd:
        controlInfo.iControl = new(ELeave) CEikFloatingPointEditor;
        break;

// Reintroduced, JIn 1/2/2001.
    case EEikCtFxPtEd:
        controlInfo.iControl = new(ELeave) CEikFixedPointEditor;
        break;

    case EEikCtNumberEditor:
        controlInfo.iControl = new(ELeave) CEikNumberEditor;
        controlInfo.iFlags = EEikControlHasEars;
        break;
    case EEikCtRangeEditor:
        controlInfo.iControl = new(ELeave) CEikRangeEditor;
        break;
    case EEikCtTimeEditor:
        controlInfo.iControl = new(ELeave) CEikTimeEditor;
        break;
    case EEikCtDateEditor:
        controlInfo.iControl = new(ELeave) CEikDateEditor;
        break;
    case EEikCtTimeAndDateEditor:
        controlInfo.iControl = new(ELeave) CEikTimeAndDateEditor;
        break;
    case EEikCtDurationEditor:
        controlInfo.iControl = new(ELeave) CEikDurationEditor;
        break;
    case EEikCtTimeOffsetEditor:
        controlInfo.iControl = new(ELeave) CEikTimeOffsetEditor;
        break;
//  case EEikCtLatitudeEditor:
//      controlInfo.iControl = new(ELeave) CEikLatitudeEditor;
//      break;
//  case EEikCtLongitudeEditor:
//      controlInfo.iControl = new(ELeave) CEikLongitudeEditor;
//      break;
    case EEikCtGlobalTextEditor:
        controlInfo.iControl = new(ELeave) CEikGlobalTextEditor;
        break;
    case EEikCtSpacer:
        controlInfo.iControl = new(ELeave) CEikSpacer;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;

    case EAknCtIpFieldEditor:
        controlInfo.iControl = new(ELeave) CAknIpFieldEditor;
        break;
    case EAknCtLocationEditor:
	controlInfo.iControl = new(ELeave) CAknLocationEditor;
	break;
    case EAknCtUnitEditor:
        controlInfo.iControl = CAknUnitEditor::NewL();
        break;
    default:
        break;
        }

    return controlInfo;
    }

/**
 * Creates the button group identified by aButtonGroupType, if it exists in this button
 * group factory.  Extra required information is supplied in aCreationData.  If the button group
 * is to be added to the button group stack then this can be set in aAddToButtonGroupStack.
 * If the aButtonGroupType value does not exist, then it returns NULL.
 */
MEikButtonGroup* CEikCtlLibrary::CreateButtonGroupByTypeL(TInt /*aButtonGroupType*/,EikButtonGroupFactory::TCreationData& /*aCreationData*/,TBool& /*aAddToButtonGroupStack*/)
    {//static
    return NULL;
    }
