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


// INCLUDE FILES
#include "AknIconArray.h"  // This class
#include <barsread.h>       // TResourceReader
#include <fbs.h>            // CFbsBitmap
#include <gulicon.h>        // CGulIcon
#include <coemain.h>        // CCoeEnv
#include <bautils.h>
#include "avkon.hrh"
#include "AknPanic.h"

#include <AknIconUtils.h>


// LOCAL FUNCTION PROTOTYPES
// ==================== LOCAL FUNCTIONS ====================


// ================= MEMBER FUNCTIONS =======================

EXPORT_C CAknIconArray::CAknIconArray(TInt aGranurality)
    : CArrayPtrFlat<CGulIcon>(aGranurality)
    {
    }

EXPORT_C void CAknIconArray::ConstructFromResourceL(TInt aResId)
    {
    AppendFromResourceL(aResId);
    }

EXPORT_C void CAknIconArray::ConstructFromResourceL(TResourceReader& aReader)
    {
    AppendFromResourceL(aReader);
    }

EXPORT_C CAknIconArray::~CAknIconArray()
    {
    ResetAndDestroy();
    }

EXPORT_C void CAknIconArray::AppendFromResourceL(TInt aResId)
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, aResId);
    AppendFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // reader
    }

EXPORT_C void CAknIconArray::AppendFromResourceL(TResourceReader& aReader)
    {
    TInt type = aReader.ReadInt16();
    switch (type)
		{
		case EAknIconArraySimple:
		break; // go to the actual reader
		case EAknIconArrayComplex:
			{
			TInt count_a = aReader.ReadInt16();
			while(count_a-- > 0)
				{
				// recursive algorithm.	
				AppendFromResourceL(aReader);
				}
			}
			return;
		default:
		aReader.Rewind(2);

		};
    

    // this reads AKN_ICON_ARRAY *except* the type field!
    HBufC* bmpName = GetBmpNameLC(aReader); 

    TInt count = aReader.ReadInt16();
    SetReserveL(Count() + count);
    while (count-- > 0)
        {
        TInt32 iconId = aReader.ReadInt32();
        TInt32 maskId = aReader.ReadInt32();

    	CFbsBitmap* bitmap;
        CFbsBitmap* mask;

        AknIconUtils::CreateIconLC( bitmap, mask, *bmpName, iconId, maskId );

        CGulIcon* icon = CGulIcon::NewL(bitmap, mask);
        CleanupStack::Pop(2);  // mask, bitmap

        // Following AppendL call cannot leave due to lack of memory because 
        // of SetReserveL above. This is why there is no need to push icon
        // on the cleanup stack.
        AppendL(icon);
        }

    CleanupStack::PopAndDestroy();  // bmpName
    }

HBufC* CAknIconArray::GetBmpNameLC(TResourceReader& aReader)
    {
    HBufC* bmpName = aReader.ReadHBufCL();
    CleanupStack::PushL(bmpName);

    TBool drivePresent =
        (bmpName->Length() >= 3 &&
        (*bmpName)[1] == ':' &&
        (*bmpName)[2] == '\\' );

    RFs& fs = CCoeEnv::Static()->FsSession();

    TBool found = EFalse;
    if ( drivePresent )
        {
        found = BaflUtils::FileExists( fs, *bmpName );
        }

    // If drive letter is not specified, or not found in the specified drive,
    // FindByDir scans the drives in order E:, D:, C:, Z:

    if (!found)
        {
        TFindFile find( fs );
        if (find.FindByDir(*bmpName, KNullDesC) == KErrNone)
            {
            if (bmpName->Length() < find.File().Length())
                {
                bmpName = bmpName->ReAllocL(find.File().Length());
                CleanupStack::Pop(); // old bmpName
                CleanupStack::PushL( bmpName );
                }
    
            *bmpName = find.File();
            }
        }

    return bmpName;
    }
//  End of File  

