/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <akntextsettingpage.h>
#include <centralrepository.h>
#include <aknphysicscrkeys.h>
#include <bautils.h>

#include "aknconfsettingitem.h"
#include "aknconfsettinglist.h"
#include "aknconf.hrh"
#include <aknconf.rsg>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfSettingList::~CAknConfSettingList()
// -----------------------------------------------------------------------------
//
CAknConfSettingList::~CAknConfSettingList()
    {
    iEikonEnv->DeleteResourceFile( iResourceOffset );
    delete iCenRep;
    }

// -----------------------------------------------------------------------------
// CAknConfSettingList::SettingPageClosed()
// -----------------------------------------------------------------------------
//
void CAknConfSettingList::SettingPageClosed( TBool aOkPressed,
                                             const TInt& aValue,
                                             const TInt& aCenRepKey )
    {
    if ( aOkPressed )
        {
        if ( iCenRep )
            {
            iCenRep->Set( aCenRepKey, aValue );
            }
        DrawDeferred();
        }
    }


// -----------------------------------------------------------------------------
// CAknConfSettingList::CreateSettingItemL()
// -----------------------------------------------------------------------------
//
CAknSettingItem* CAknConfSettingList::CreateSettingItemL( TInt aIdentifier )
    {
    CAknSettingItem* settingItem = NULL;
    TInt cenRepKey( 0 );
    TInt* settingValue( ValueFromCenRep( aIdentifier, cenRepKey ) );
    settingItem 
        =  new ( ELeave ) CAknConfSettingItem( 
                this, *settingValue, aIdentifier, cenRepKey );
    return settingItem;
    }


// -----------------------------------------------------------------------------
// CAknConfSettingList::CAknConfSettingList()
// -----------------------------------------------------------------------------
//
CAknConfSettingList::CAknConfSettingList()
    : iCenRep( NULL )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfSettingList::ConstructL()
// -----------------------------------------------------------------------------
//
void CAknConfSettingList::ConstructL( const TUid& aCenRepUid,
        const TDesC& aResourceFile )
    {
    iCenRep = CRepository::NewL( aCenRepUid );
    TFileName resourceFile;
    resourceFile.Append( aResourceFile );
    BaflUtils::NearestLanguageFile( iEikonEnv->FsSession(), resourceFile );
    iResourceOffset = iEikonEnv->AddResourceFileL( resourceFile );
    }


// -----------------------------------------------------------------------------
// CAknConfSettingList::ValueFromCenRep()
// -----------------------------------------------------------------------------
//
TInt* CAknConfSettingList::ValueFromCenRep( const TInt& aId, 
                                            TInt& aCenRepKey )
    {
    aCenRepKey = 0;
    TInt* settingValue( DataValuePointer( aId, aCenRepKey ) );
    if ( !settingValue || !aCenRepKey )
        {
        return NULL;
        }

    TInt value( -1 );
    if ( iCenRep )
        {
        iCenRep->Get( aCenRepKey, value );
        }
    *settingValue = value;
    return settingValue;
    }
// End of File
