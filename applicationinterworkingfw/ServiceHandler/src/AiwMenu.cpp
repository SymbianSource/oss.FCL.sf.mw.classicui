/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implements AIW Menu utilities for providers to access consumer menu.
*
*/




#include <barsread.h> 
#include <barsc.h> 
#include <bautils.h>
#include "AiwMenu.h"
#include "AiwCommon.hrh"

// This is needed for resource reading.
const TInt KCCMask(0x00000fff);


EXPORT_C CAiwMenuPane::CAiwMenuPane(CEikMenuPane& aMenuPane, TInt aBaseCmdId) 
: iMenuPane(&aMenuPane), iBaseCmdId(aBaseCmdId)
    {
    iNextCmdId = aBaseCmdId;
    }


EXPORT_C CAiwMenuPane::~CAiwMenuPane()
    {   
    delete iMenuPane;
    
    for(TInt i = 0; i < iIdMap.Count(); i++)
        {
        iIdMap[i].extraText.Close();
        }
    
    iIdMap.Reset();
    }


EXPORT_C void CAiwMenuPane::AddMenuItemL(
    TInt aServiceCmd,
    CEikMenuPaneItem::SData& aMenuItem, 
    TInt aIndex)
    {
    AddMenuItemL(aServiceCmd, aMenuItem, aIndex, KNullDesC());
    }
    
    
EXPORT_C void CAiwMenuPane::AddMenuItemL(
    TInt aServiceCmd,
    CEikMenuPaneItem::SData& aMenuItem, 
    TInt aIndex,
    const TDesC& aExtraText)
    {
    SMenuIdMap map;

    map.dynMenuCmdId = iNextCmdId + iPaneOffset;
    map.serviceCmdId = aServiceCmd;
    map.origCmdId = aMenuItem.iCommandId;
    map.owner = iInitializingOwner;
    map.extraText.Assign(aExtraText.AllocL());
    CleanupClosePushL(map.extraText);

    aMenuItem.iCommandId = iNextCmdId + iPaneOffset;
    iNextCmdId++;

    iMenuPane->InsertMenuItemL(aMenuItem, aIndex); 
    User::LeaveIfError(iIdMap.Append( map ));
    CleanupStack::Pop(); // map.extraText
    }    


    
EXPORT_C void CAiwMenuPane::AddMenuItemsL(
    TResourceReader& aReader,
    TInt aServiceCmd,
    TInt aIndex,
    TBool /*aAddSeperator*/)
    {
    CEikMenuPaneItem::SData data;

    TInt index = aIndex;
   
    TInt count = aReader.ReadInt16();
    for (TInt i = 0; i < count; i++)
        {
        data.iCommandId = aReader.ReadInt32();
        data.iCascadeId = aReader.ReadInt32();  
        data.iFlags = aReader.ReadInt32();
        data.iText.Copy(aReader.ReadTPtrC());
        
        // Extra text (additional submenu text) must be handled separately
        // because SData doesn't offer space for it.
        TPtrC extraText = aReader.ReadTPtrC();
        
        aReader.ReadTPtrC(); // Skip bmpfile.
        aReader.ReadInt16(); // Skip bmpid.
        aReader.ReadInt16(); // Skip bmpmask. 
        aReader.ReadInt32(); // Skip extension.   

        if (data.iCommandId == AIW_SUBMENU_TITLE)
            {
            AddTitleItemL(data.iText, index);
            }
        else
            {
            AddMenuItemL(aServiceCmd, data, index++, extraText);
            }
        } 
    }


  
EXPORT_C void CAiwMenuPane::AddMenuItemsL(
    TFileName& aFileName,
    TInt aResId,
    TInt aServiceCmd,
    TInt aIndex,
    TBool aAddSeparator)
    {
    TResourceReader reader; 

    RFs fsSession;
    User::LeaveIfError( fsSession.Connect() );
    CleanupClosePushL( fsSession );

    BaflUtils::NearestLanguageFile(fsSession, aFileName);

    RResourceFile rsFile;
    rsFile.OpenL( fsSession, aFileName );
    CleanupClosePushL( rsFile );

    // Read multitapping resource.
    HBufC8* rBuffer = rsFile.AllocReadLC(aResId & KCCMask); // Remove offset from id
    reader.SetBuffer( rBuffer );

    AddMenuItemsL(reader, aServiceCmd, aIndex, aAddSeparator);

    CleanupStack::PopAndDestroy(3);  // rBuffer, rsFile, fsSession
    }



EXPORT_C TInt CAiwMenuPane::MenuCmdId(TInt aDynCmdId) const
    {
    for (TInt i = 0; i < iIdMap.Count(); i++)
        {
        if (iIdMap[i].dynMenuCmdId == aDynCmdId)
            {
            return iIdMap[i].origCmdId;
            }
        }

    return 0;
    }

    

EXPORT_C TInt CAiwMenuPane::DynCmdId(TInt aMenuCmdId) const
    {
    for (TInt i = 0; i < iIdMap.Count(); i++)
        {
        if (iIdMap[i].origCmdId == aMenuCmdId)
            {
            return iIdMap[i].dynMenuCmdId;
            }
        }

    return 0;
    }



EXPORT_C TInt CAiwMenuPane::ServiceCmdId(TInt aDynCmdId) const
    {
    for (TInt i = 0; i < iIdMap.Count(); i++)
        {
        if (iIdMap[i].dynMenuCmdId == aDynCmdId)
            {
            return iIdMap[i].serviceCmdId;
            }
        }

    return 0; 
    }



TInt CAiwMenuPane::FindCmdId(TInt aIndex)
    {
    TInt index;

    for (TInt i = 0; i < iIdMap.Count(); i++)
        {
        if (iMenuPane->MenuItemExists(iIdMap[i].dynMenuCmdId, index))   
            {
            if (aIndex == index)
                {
                return iIdMap[i].dynMenuCmdId;
                }
            }
        }

    return -1;
    }



EXPORT_C void CAiwMenuPane::AddTitleItemL(const TDesC& aTitle, TInt aIndex) 
    {
    CEikMenuPaneItem::SData data;
    
    data.iCommandId = AIW_SUBMENU_TITLE;
    data.iCascadeId = 0;  
    data.iFlags = 0;
    data.iText.Copy(aTitle);

    iMenuPane->InsertMenuItemL(data, aIndex);       
    }


TBool CAiwMenuPane::IsCmdInRange(TInt aCmdSpaceSize, TInt aCmd)
    {
    if ((aCmd >= iPaneOffset + iBaseCmdId) &&
        (aCmd < iPaneOffset + iBaseCmdId + aCmdSpaceSize))
        {
        return ETrue;
        }

    return EFalse;
    }


CAiwServiceIfBase* CAiwMenuPane::CommandOwner(TInt aDynCmd) const
    {
    for (TInt i = 0; i < iIdMap.Count(); i++)
        {
        if (iIdMap[i].dynMenuCmdId == aDynCmd)
            {
            return iIdMap[i].owner;
            }
        }   

    return NULL;
    }
    
    
const TDesC& CAiwMenuPane::ExtraText(TInt aDynMenuCmdId)
    {
    TInt count = iIdMap.Count();
    for(TInt i = 0; i < count; i++)
        {
        if(iIdMap[i].dynMenuCmdId == aDynMenuCmdId)
            {
            return iIdMap[i].extraText;
            }
        }
    return KNullDesC;        
    }

// End of file
