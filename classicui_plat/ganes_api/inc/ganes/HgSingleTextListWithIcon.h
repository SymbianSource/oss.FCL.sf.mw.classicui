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

#ifndef HGSINGLETEXTLISTWITHICON_H_
#define HGSINGLETEXTLISTWITHICON_H_

#include <ganes/HgSingleTextList.h>

// Forward declarations
//class CHgItem;

class CHgSingleTextListWithIcon : public CHgSingleTextList
    {
public:
    /**
     * Creates new CHgSingleTextList.
     * 
     * @param aRect Rect that the control draws onto.
     * @param aItemCount Total count of items in the grid
     * @param aDefaultIcon Default icon to be used.
     * @param aSession Window server session for DSA. Default is NULL and DSA is disabled.
     * 
     * @return CHgSingleTextList-object
     */
    IMPORT_C static CHgSingleTextListWithIcon* NewL ( const TRect& aRect, 
          TInt aItemCount, 
          CGulIcon* aDefaultIcon = NULL,
          RWsSession* aSession = NULL); 

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CHgSingleTextListWithIcon( );

protected: // CHgScroller
    void HandleSizeChanged();
    void HandleScrollbarVisibilityChange(TBool aVisible);
    
protected: // CHgList

    void DrawItem(TInt aIndex, const TRect& aRect) const; 
    
    void ConstructL( const TRect& aRect, RWsSession* aSession );
    
protected:
    CHgSingleTextListWithIcon( TInt aItemCount, 
            CGulIcon* aDefaultIcon );

private: // Data
    CHgListLayoutData* iGraphicLayoutData;

    };

#endif /*HGSINGLETEXTLISTWITHICON_H_*/
