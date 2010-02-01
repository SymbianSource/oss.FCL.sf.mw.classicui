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





/*
 * HgLayoutData.h
 *
 *  Created on: Feb 6, 2009
 *      Author: anjokela
 */

#ifndef HGLAYOUTDATA_H_
#define HGLAYOUTDATA_H_

#include <e32base.h>
#include <AknLayout2ScalableDef.h>
#include "HgConstants.h"

NONSHARABLE_CLASS( CHgListLayoutData ) : public CBase
    {
public:
    static CHgListLayoutData* NewL()
        {
        CHgListLayoutData* self = new (ELeave) CHgListLayoutData;
        CleanupStack::PushL(self);
        self->ConstructL( KMaxNumberOfTitleIndicators );
        CleanupStack::Pop(self);
        return self;
        }
    
    virtual ~CHgListLayoutData()
        {
        iTitleLayouts.Close();
        }
    
public:

    inline void SetBaseLayout( const TAknWindowComponentLayout& aLayout )
        {
        iBaseLayout = aLayout;
        }
    
    inline const TAknWindowComponentLayout& BaseLayout()
        {
        return iBaseLayout;
        }
    
    inline void SetItemLayout( const TAknWindowComponentLayout& aLayout )
        {
        iItemLayout = aLayout;
        }
    
    inline const TAknWindowComponentLayout& ItemLayout()
        {
        return iItemLayout;
        }
    
    inline void SetIconLayout( const TAknWindowComponentLayout& aLayout )
        {
        iIconLayout = aLayout;
        }
    
    inline const TAknWindowComponentLayout& IconLayout()
        {
        return iIconLayout;
        }
    
    inline void SetTitleLayout( TInt aIndicators, const TAknTextComponentLayout& aLayout )
        {
        if(aIndicators >= 0 && aIndicators < iTitleLayouts.Count())
            {
            iTitleLayouts[aIndicators] = aLayout;
            }
        }
    
    inline const TAknTextComponentLayout& TitleLayout( TInt aIndicators )
        {
        return iTitleLayouts[aIndicators];
        }
    
    inline void SetTextLayout( const TAknTextComponentLayout& aLayout )
        {
        iTextLayout = aLayout;
        }
    
    inline const TAknTextComponentLayout& TextLayout()
        {
        return iTextLayout;
        }
    
    inline void SetFirstIndicatorLayout( const TAknWindowComponentLayout& aLayout )
        {
        iFirstIndicatorLayout = aLayout;
        }
    
    inline const TAknWindowComponentLayout& FirstIndicatorLayout()
        {
        return iFirstIndicatorLayout;
        }
    
    inline void SetSecondIndicatorLayout( const TAknWindowComponentLayout& aLayout )
        {
        iSecondIndicatorLayout = aLayout;
        }

    inline const TAknWindowComponentLayout& SecondIndicatorLayout()
        {
        return iSecondIndicatorLayout;
        }
protected:

    void ConstructL( TInt aMaxIndicators )
        {
        for(TInt i = 0; i <= aMaxIndicators; ++i)
            {
            User::LeaveIfError(iTitleLayouts.Append(TAknTextComponentLayout()));
            }
        }

protected: // data

    TAknWindowComponentLayout iBaseLayout;
    TAknWindowComponentLayout iItemLayout;
    TAknWindowComponentLayout iIconLayout;
    RArray<TAknTextComponentLayout> iTitleLayouts;
    TAknTextComponentLayout iTextLayout;
    TAknWindowComponentLayout iFirstIndicatorLayout;
    TAknWindowComponentLayout iSecondIndicatorLayout;
    
    };

NONSHARABLE_CLASS( CHgGridLayoutData ) : public CHgListLayoutData
    {
public:
    static CHgGridLayoutData* NewL(TInt aMaxColumnCount)
        {
        CHgGridLayoutData* self = new (ELeave) CHgGridLayoutData;
        CleanupStack::PushL(self);
        self->ConstructL( aMaxColumnCount );
        CleanupStack::Pop(self);
        return self;
        }
    
    virtual ~CHgGridLayoutData()
        {
        iColumnLayouts.Close();
        }
public:        
    inline void SetColumnLayout( TInt aIndex, const TAknWindowComponentLayout& aLayout )
        {
        if(aIndex >= 0 && aIndex < iColumnLayouts.Count())
            {
            iColumnLayouts[aIndex] = aLayout;
            }
        }
    
    inline const TAknWindowComponentLayout& ColumnLayout(TInt aIndex)
        {
        return iColumnLayouts[aIndex];
        }

    void ChangeCols( TInt aCols )
        {
        if(aCols < 0) aCols = 0;
        
        while( iColumnLayouts.Count() < aCols )
            {
            iColumnLayouts.Append(TAknWindowComponentLayout());
            }
        while( iColumnLayouts.Count() > aCols )
            {
            iColumnLayouts.Remove(iColumnLayouts.Count() - 1);
            }
        }
protected:

    void ConstructL( TInt aMaxColumnCount )
        {
        CHgListLayoutData::ConstructL(0);
        
        for(TInt i = 0; i < aMaxColumnCount; ++i)
            {
            User::LeaveIfError(iColumnLayouts.Append(TAknWindowComponentLayout()));
            }
        }
protected:
    RArray<TAknWindowComponentLayout> iColumnLayouts;
    
    };

#endif /* HGLAYOUTDATA_H_ */
