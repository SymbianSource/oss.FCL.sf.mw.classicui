/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

#include "AknLib.h"
#include <e32std.h>
#include "avkon.hrh"
#include <aknlists.h>
#include <aknjavalists.h>
#include <eikimage.h>
#include <akntitle.h>
#include <akncontext.h>
#include "akncontextidle.h"
#include <aknnavi.h>
#include <AknSignal.h>
#include <AknBattery.h>
#include <AknIndicatorContainer.h>
#include <aknnotecontrol.h>
#include <aknQueryControl.h>
#include <AknQueryDialog.h>
#include <AknPopupFieldText.h>
#include <aknsettingpage.h>
#include <aknpopupsettingpage.h>
#include <aknslider.h>
#include <aknCharMap.h>
#include <eikfrlb.h>
#include <aknPopupHeadingPane.h>
#include <AknQueryDialog.h>
#include <aknQueryControl.h>
#include <aknmessagequerycontrol.h>
#include <aknmultilinequerycontrol.h>
#include <aknlistquerycontrol.h>
#include <AknPhoneNumberEditor.h>
#include <AknNumEdwin.h>
#include <AknAppGrid.h>
#include "aknlistquerysearchcontrol.h"
#include "aknstatuspanedigitalclock.h"
#include "aknemptycontrol.h"
#include "aknuniversalindicatorcontainer.h"
#include "aknsignalindicatorcontainer.h"
#include "aknbatteryindicatorcontainer.h"

#include <aknbutton.h>


_LIT(KResFileName,         "z:\\resource\\avkon.rsc");
_LIT(KAknPrivResourceFile, "z:\\resource\\aknpriv.rsc");

// Static DLL functions
GLDEF_C void Panic(TAknPanic aPanic)
    {
    _LIT(KPanicCat,"AVKON");
    User::Panic(KPanicCat,aPanic);
    }


//
// CAknLibrary
//
CAknLibrary::CAknLibrary()
    {
    }

EXPORT_C TFileName CAknLibrary::ResourceFile()
    {
    return KResFileName();
    }

EXPORT_C TFileName CAknLibrary::PrivateResourceFile()
    {
    return KAknPrivResourceFile();
    }

EXPORT_C TCreateByTypeFunction  CAknLibrary::ControlFactory()
    {
    return CreateByTypeL;
    }


SEikControlInfo CAknLibrary::CreateByTypeL(TInt aControlType)
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL;
    controlInfo.iTrailerTextId = 0;
    controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case EAknCtTest:
        controlInfo.iControl = new(ELeave) CEikImage;
        break;

        // generic listboxes
    case EAknCtFormattedListBox:
        controlInfo.iControl = new(ELeave) CEikFormattedCellListBox;
        break;
        // SERIES60 listboxes

    case EAknCtSingleListBox:
        controlInfo.iControl = new(ELeave) CAknSingleStyleListBox;
        break;
    case EAknCtSingleNumberListBox:
        controlInfo.iControl = new(ELeave) CAknSingleNumberStyleListBox;
        break;
    case EAknCtSingleHeadingListBox:
        controlInfo.iControl = new(ELeave) CAknSingleHeadingStyleListBox;
        break;
    case EAknCtSingleGraphicListBox:
        controlInfo.iControl = new(ELeave) CAknSingleGraphicStyleListBox;
        break;
    case EAknCtSingleGraphicHeadingListBox:
        controlInfo.iControl = new(ELeave) CAknSingleGraphicHeadingStyleListBox;
        break;
    case EAknCtSingleNumberHeadingListBox:
        controlInfo.iControl = new(ELeave) CAknSingleNumberHeadingStyleListBox;
        break;
    case EAknCtSingleLargeListBox:
        controlInfo.iControl = new(ELeave) CAknSingleLargeStyleListBox;
        break;
    case EAknCtSingle2GraphicListBox:
        controlInfo.iControl = new(ELeave) CAknSingle2GraphicStyleListBox;
        break;
    case EAknCtDoubleListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleStyleListBox;
        break;
    case EAknCtDoubleNumberListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleNumberStyleListBox;
        break;
    case EAknCtDoubleTimeListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleTimeStyleListBox;
        break;
    case EAknCtDoubleLargeListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleLargeStyleListBox;
        break;
    case EAknCtDoubleGraphicListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleGraphicStyleListBox;
        break;
    case EAknCtDouble2GraphicListBox:
        controlInfo.iControl = new(ELeave) CAknDouble2GraphicStyleListBox;
        break;
    case EAknCtDouble2LargeListBox:
        controlInfo.iControl = new(ELeave) CAknDouble2LargeStyleListBox;
        break;
    case EAknCtDouble2GraphicLargeListBox:
        controlInfo.iControl = new(ELeave) CAknDouble2GraphicLargeStyleListBox;
        break;
    case EAknCtSettingListBox:
        controlInfo.iControl = new(ELeave) CAknSettingStyleListBox;
        break;
    case EAknCtSettingNumberListBox:
        controlInfo.iControl = new(ELeave) CAknSettingNumberStyleListBox;
        break;
    case EAknCtSingleHeadingPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknSingleHeadingPopupMenuStyleListBox;
        break;

    case EAknCtSinglePopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknSinglePopupMenuStyleListBox;
        break;
    case EAknCtSingleGraphicPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknSingleGraphicPopupMenuStyleListBox;
        break;
    case EAknCtSingleGraphicHeadingPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknSingleGraphicHeadingPopupMenuStyleListBox;
        break;
    case EAknCtMenuDoublePopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknDoublePopupMenuStyleListBox;
        break;
    case EAknCtSinglePopupSubmenuListBox:
        controlInfo.iControl = new(ELeave) CAknSinglePopupSubmenuStyleListBox;
        break;
    case EAknCtDoubleLargeGraphicPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleLargeGraphicPopupMenuStyleListBox;
        break;
    case EAknCtDouble2PopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknDouble2PopupMenuStyleListBox;
        break;
    case EAknCtSingle2GraphicPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknSingle2GraphicPopupMenuStyleListBox;
        break;
    case EAknCtDoubleGraphicPopupMenuListBox:
        controlInfo.iControl = new(ELeave) CAknDoubleGraphicPopupMenuStyleListBox;
        break;

    case EAknSetListBox:
        controlInfo.iControl = new(ELeave) CAknSetStyleListBox;
        break;
    case EAknFormGraphicListBox:
        controlInfo.iControl = new(ELeave) CAknFormGraphicStyleListBox;
        break;

/*
        // SERIES60 popup listboxes
    case EAknCtPopupSingle1ListBox:
        controlInfo.iControl = new(ELeave) CAknPopupSingle1StyleListBox;
        break;
    case EAknCtPopupSingle2ListBox:
        controlInfo.iControl = new(ELeave) CAknPopupSingle2StyleListBox;
        break;

    case EAknCtPopupSingleGraphic2ListBox:
        controlInfo.iControl = new(ELeave) CAknPopupSingleGraphic2StyleListBox;
        break;
    case EAknCtPopupSingleGraphic3ListBox:
        controlInfo.iControl = new(ELeave) CAknPopupSingleGraphic3StyleListBox;
        break;
    case EAknCtPopupSingleGraphicHeading2ListBox:
        controlInfo.iControl = new(ELeave) CAknPopupSingleGraphicHeading2StyleListBox;
        break;
    case EAknCtPopupDoubleListBox:
        controlInfo.iControl = new(ELeave) CAknPopupDoubleStyleListBox;
        break;
*/

    case EAknCtAppGrid:
        controlInfo.iControl = new(ELeave) CAknAppStyleGrid;
        break;
    case EAknCtPinbGrid:
        controlInfo.iControl = new(ELeave) CAknPinbStyleGrid;
        break;
    case EAknCtQdialGrid:
        controlInfo.iControl = new(ELeave) CAknQdialStyleGrid;
        break;
    case EAknCtCaleMonthGrid:
        controlInfo.iControl = new(ELeave) CAknCaleMonthStyleGrid;
        break;

        // status pane
        case EAknCtTitlePane:
            controlInfo.iControl = new(ELeave) CAknTitlePane;
            break;
        case EAknCtContextPane:
            controlInfo.iControl = new(ELeave) CAknContextPane;
            break;
        case EAknCtIdleContextPane:
            controlInfo.iControl = new(ELeave) CAknIdleContextPane;
            break;
        case EAknCtNaviPane:
            controlInfo.iControl = new(ELeave) CAknNavigationControlContainer;
            break;
        case EAknCtSignalPane:
            controlInfo.iControl = new(ELeave) CAknSignalPane;
            break;
        case EAknCtBatteryPane:
            controlInfo.iControl = new(ELeave) CAknBatteryPane;
            break;
        case EAknCtIndicatorPane:
            controlInfo.iControl = new(ELeave) CAknIndicatorContainer;
            break;
        case EAknCtUniversalIndicatorPane:
            controlInfo.iControl = new(ELeave) CAknUniversalIndicatorContainer;
            break;
        case EAknCtDigitalClockPane:
            controlInfo.iControl = new(ELeave) CAknStatuspaneDigitalClock;
            break;
        case EAknCtStatuspaneEmpty:
            controlInfo.iControl = new(ELeave) CAknEmptyControl;
            break;
        case EAknCtSignalIndicatorContainerPane:
            controlInfo.iControl = new(ELeave) CAknSignalIndicatorContainer;
            break;
        case EAknCtBatteryIndicatorContainerPane:
            controlInfo.iControl = new(ELeave) CAknBatteryIndicatorContainer;
            break;
            
        case EAknCtNote:
            controlInfo.iControl = new(ELeave) CAknNoteControl;
            break;
        case EAknCtQuery:
            controlInfo.iControl = new(ELeave) CAknQueryControl;
            break;

        case EAknExtCtQuery:
            controlInfo.iControl = new(ELeave) CAknExtQueryControl;
            break;

        case EAknCtPopupField:
            controlInfo.iControl = new(ELeave) CAknPopupField;
            break;
        case EAknCtPopupFieldText:
            controlInfo.iControl = new(ELeave) CAknPopupFieldText;
            break;
        case EAknCtSearchField:
            break;

        case EAknCtVolumeControl:
            controlInfo.iControl = new(ELeave) CAknVolumeControl;
            break;
        case EAknCtSlider:
            controlInfo.iControl = new(ELeave) CAknSlider;
            break;
        case EAknCtSpecialCharacterMap:
                controlInfo.iControl = new(ELeave) CAknCharMap;
            break;
        case EAknCtListQueryControl:
            controlInfo.iControl = new(ELeave) CAknListQueryControl;
            break;
        case EAknCtListQuerySearchControl:
            controlInfo.iControl = new(ELeave) CAknListQuerySearchControl;
            break;
        case EAknCtPopupHeadingPane:
            controlInfo.iControl = new(ELeave) CAknPopupHeadingPane;
            break;
        case EAknPhoneNumberEditor:
            controlInfo.iControl = new(ELeave) CAknPhoneNumberEditor;
            break;
        case EAknCtNumericSecretEditor:
            controlInfo.iControl = new(ELeave) CAknNumericSecretEditor;
            break;
        case EAknCtPopupSettingList:
            controlInfo.iControl = new(ELeave) CAknPopupSettingList;
            break;
        case EAknCtIntegerEdwin:
            controlInfo.iControl = new(ELeave) CAknIntegerEdwin;
            break;
        case EAknCtMessageQuery:
            controlInfo.iControl = new(ELeave) CAknMessageQueryControl;
            break;
        case EAknCtMultilineQuery:
            controlInfo.iControl = new(ELeave) CAknMultilineQueryControl;
            break;
        case EAknExtCtMultilineQuery:
            controlInfo.iControl = new(ELeave) CAknExtMultilineQueryControl;
            break;
        case EAknCtBitmapAnimation:
            controlInfo.iControl = CAknBitmapAnimation::NewL();
            break;
        case EAknCtButton:
            controlInfo.iControl = CAknButton::NewL();
            break;
    
        default:
            break;
        }

    return controlInfo;
    }




