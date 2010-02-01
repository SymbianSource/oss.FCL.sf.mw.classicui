/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#ifndef AKNCUSTOMCURSORSUPPORT_H
#define AKNCUSTOMCURSORSUPPORT_H

// INCLUDES

#include <AknFontCategory.hrh>
#include <e32std.h>
#include <gdi.h>
#include <w32std.h>

// CLASS DECLARATION

/**
* Bi-directional cursor support interfaces
* Entirely static class
* 
* @since Series 60 3.0
*
* @internal
*/
NONSHARABLE_CLASS(AknCustomCursorSupport)
    {
    public:

    /**
    * Return the Wserv custom text cursor id to be used for the given avkon font category, cursor height, 
    *  and directionality.
    * 
    * Supported font categories are primary, and primary_small.
    * 
    * @since Series 60 3.0
    *
    * @param aFontCategory Avkon layout font category. 
    * @param aBitmapRect Rectangle representing the cursor as if it were a block cursor. This is either a cursor rectangle
    *  obtained from the Avkon layout specification, or it may be based on a cursor specification of a current cursor.
    * @param aRightToLeft Boolean flag that indicates whether the input direction is right-to-left.
    * @return The Wserv cursor Id to use.
    *  See RWsSession::SetCustomTextCursor
    */
    IMPORT_C static TInt CustomBidiTextCursorId( 
        TAknFontCategory aFontCategory, 
        TRect aBitmapRect, 
        TBool aRightToLeft );
            
    /**
    * Fill in a TTextCursor structure for a bidi custom cursor, depending upon the supplied
    * TFontSpec.
    * 
    * @since Series 60 3.0
    * 
    * @param aFontSpec     Symbian Font Specification to base the choice on.
    * @param aRightToLeft  Boolean flag that indicates whether the input direction is right-to-left.
    * @param aTextCursor   Text cursor structure to fill in.
    * @return   Always returns KErrNone
    */        
    IMPORT_C static TInt GetBidiTextCursorFromFontSpec( 
        const TFontSpec& aFontSpec,
        TBool aRightToLeft,
        TTextCursor& aTextCursor );        
    };

#endif // AKNCUSTOMCURSORSUPPORT_H

// End of File

