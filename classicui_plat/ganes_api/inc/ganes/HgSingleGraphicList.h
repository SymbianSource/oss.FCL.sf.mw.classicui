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


#ifndef HGSINGLEGRAPHICLIST_H_
#define HGSINGLEGRAPHICLIST_H_

#include <ganes/HgList.h>

class CHgSingleGraphicList : public CHgList
    {
public:
    /**
     * Creates new CHgSingleGraphicList.
     * 
     * @param aRect Rect that the control draws onto.
     * @param aItemCount Total count of items in the grid
     * @param aDefaultIcon Default icon to be used.
     * @param aSession Window server session for DSA. Default is NULL and DSA is disabled.
     * 
     * @return CHgSingleGraphicList-object
     */
    IMPORT_C static CHgSingleGraphicList* NewL( const TRect& aRect, 
            TInt aItemCount, 
            CGulIcon* aDefaultIcon = NULL,
            RWsSession* aSession = NULL); 

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CHgSingleGraphicList( );

public:
    
    /**
     * Returns preferred image size that should be used when passing images.
     */
    IMPORT_C static TSize PreferredImageSize();

protected: // CHgScroller
    void HandleSizeChanged();
    void HandleScrollbarVisibilityChange(TBool aVisible);

protected: // CHgList
    void DrawItem(TInt aIndex, const TRect& aRect) const; 
    
protected:
    CHgSingleGraphicList( TInt aItemCount, 
            CGulIcon* aDefaultIcon );

    };

#endif /*HGSINGLEGRAPHICLIST_H_*/
