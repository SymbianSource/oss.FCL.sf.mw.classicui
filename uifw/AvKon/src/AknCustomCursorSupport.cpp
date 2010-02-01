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


// INCLUDE FILES

#include "AknCustomCursorSupport.h"
#include "avkon.hrh"
#include "AknUtils.h"
#include <aknlayoutscalable_avkon.cdl.h> // Scalable layout API

/* 
The following code supplies IDs for scaled bitmaps for non-low res resolutions. (Low res Ids are public 
in Avkon.hrh.)  

Rather than expand the list of public custom cursor IDs, the additional range for Qvga and double res
are kept internal: 0x1020E6E7 - 0x1020E6EE inclusive.
*/

#define KAknCustomTextCursorIdQvgaLeftToRight         0x1020E6E7
#define KAknCustomTextCursorIdQvgaLeftToRightThin     0x1020E6E9
#define KAknCustomTextCursorIdDoubleLeftToRight       0x1020E6Eb
#define KAknCustomTextCursorIdDoubleLeftToRightThin   0x1020E6Ed

// Uses magic numbers to say which ids are to be used. This is required because it is not possible
// to get a all layouts at one time - you can only get to the current layout.
TInt const KMaxLowResPrimaryCursorHeight(15);
TInt const KMaxQvgaPrimaryCursorHeight(30); 
TInt const KMaxLowResPrimarySmallCursorHeight(15);
TInt const KMaxQvgaPrimarySmallCursorHeight(26);

EXPORT_C TInt AknCustomCursorSupport::CustomBidiTextCursorId( 
    TAknFontCategory aFontCategory, 
    TRect aBitmapRect, 
    TBool aRightToLeft )
    {
    // The default is KAknCustomTextCursorIdLeftToRight
    TInt id = KAknCustomTextCursorIdLeftToRight;
    TInt height = aBitmapRect.Height();
    if ( aFontCategory == EAknFontCategoryPrimary )
        {
        if ( height <= KMaxLowResPrimaryCursorHeight)
            id = KAknCustomTextCursorIdLeftToRight;
        else if ( height  <= KMaxQvgaPrimaryCursorHeight )
            id = KAknCustomTextCursorIdQvgaLeftToRight;
        else
            id = KAknCustomTextCursorIdDoubleLeftToRight;
        }
    else if (aFontCategory == EAknFontCategoryPrimarySmall ) 
        {
        if ( height <= KMaxLowResPrimarySmallCursorHeight)
            id = KAknCustomTextCursorIdLeftToRightThin;
        else if ( height  <= KMaxQvgaPrimarySmallCursorHeight )
            id = KAknCustomTextCursorIdQvgaLeftToRightThin;
        else 
            id = KAknCustomTextCursorIdDoubleLeftToRightThin;
        }

    if ( aRightToLeft )  // True for all cursor types (right-to-left is always 1 more than left-to-right
        id++;

    return id;
    }

EXPORT_C TInt AknCustomCursorSupport::GetBidiTextCursorFromFontSpec( 
    const TFontSpec& aFontSpec,
    TBool aRightToLeft,
    TTextCursor& aTextCursor )
    {
    // What needs to be determined here is what type of text is focused, Primary 
    // or Primary_small. This can only reliably be obtained from the cursor height, 
    // not width:
    TInt cursorHeight = AknLayoutUtils::CursorHeightFromFont(aFontSpec);
        
    // Compare this height with the heights in layout
    // First we need to get the layouts:
    TAknWindowLineLayout primaryLayout = 
        AknLayoutScalable_Avkon::cursor_primary_pane().LayoutLine();
    TAknWindowLineLayout primarySmallLayout = 
        AknLayoutScalable_Avkon::cursor_primary_small_pane().LayoutLine();
    
    // We need to get rectangles from them, so combine with parent rectangles
    TAknLayoutRect primaryCursor;
    TAknLayoutRect primarySmallCursor;
    TRect rectParent = CEikonEnv::Static()->EikAppUi()->ApplicationRect();
    primaryCursor.LayoutRect( rectParent, primaryLayout );
    primarySmallCursor.LayoutRect( rectParent, primarySmallLayout );
        
    // If the height is less than for a primary small_cursor, then use the primary_small
    TRect rectToUse;
    TAknFontCategory fontCategory(EAknFontCategoryPrimary);
    if (cursorHeight <= primarySmallCursor.Rect().Height())
        {
        fontCategory = EAknFontCategoryPrimarySmall;
        rectToUse = primarySmallCursor.Rect();
        }
    else
        {
        fontCategory = EAknFontCategoryPrimary;
        rectToUse = primaryCursor.Rect();
        }
    // Fill in the iType:
    aTextCursor.iType = AknCustomCursorSupport::CustomBidiTextCursorId( 
        fontCategory, rectToUse, aRightToLeft );

    return KErrNone;
}
//  End of File  
