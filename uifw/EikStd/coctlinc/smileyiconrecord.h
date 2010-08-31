/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiley utility class
*
*/

#ifndef C_SMILEYICONRECORD_H
#define C_SMILEYICONRECORD_H

#include <e32base.h>
#include <e32std.h>
#include "smileymanager.h"

class CSmileyImageData;

NONSHARABLE_CLASS( CSmileyIcon ) : public CBase
    {
    friend class CSmileyTextLink;
public:
    CSmileyIcon( TText aCode );
    ~CSmileyIcon();
// new functions
    void SetRect( TRect aRect ){ iRect = aRect; };
    TRect Rect(){ return iRect; };
    void SetPlayTimes( TInt aPlayTimes ){ iLoop = aPlayTimes; };
    TInt PlayTimes(){ return iLoop; };
    void EnableHighlight( TBool aEnable ){ iHighlight = aEnable; };
    TBool IsHighlight(){ return iHighlight; };
    void SetImageData( CSmileyImageData* aImage ){ iImage = aImage; };
    CSmileyImageData* ImageData(){ return iImage; };
    TText Code(){ return iCode; };
    void IncreasePlayCount(){ iPlayCount++; };
    TInt PlayCount(){ return iPlayCount; };
    void PlayOneTime(){ iPlayCount = iLoop - 1; };
    void ResetPlayCount(){ iPlayCount = 0; };
    TBool IsPlayFinished(){ return ( iPlayCount >= iLoop ); };
    TInt DocPos(){ return iDocPos; };
    void SetDocPos( TInt aDocPos ){ iDocPos = aDocPos; };
    
    TInt SmileyLength(){ return iStr.Length(); };
    TInt EndPos(){ return iDocPos + iStr.Length(); };
    void SetSmileyString( const TDesC& aString );
    const TDesC& SmileyString(){ return iStr; };
    
    TBool IsDisabled(){ return iDisabled; };
    void DisableIcon( TBool aDisable = ETrue ){ iDisabled = aDisable; };

private: // data
    TText iCode;
    TRect iRect;
    TInt iDocPos;
    TInt iLoop;
    TInt iPlayCount;
    TBool iHighlight;
    // not own
    CSmileyImageData* iImage;
    TBuf<CSmileyManager::KMaxLength> iStr;
    TBool iDisabled;
    };

NONSHARABLE_CLASS( CSmileyIconRecord ) : public CBase
    {
public:
    CSmileyIconRecord();
    ~CSmileyIconRecord();
    
    void InsertIconL( CSmileyIcon* aIcon );
    void HandleTextDelete( TInt aStart, TInt aLength );
    void HandleTextInsert( TInt aStart, TInt aLength );
    void CancelSelection();
    void SetSelection( TInt aStart, TInt aLength );
    CSmileyIcon* SmileyIconAtPos( TInt aDocPos );
    TBool HasSmileyIcon();
    
private:
    void InsertIconAtL( CSmileyIcon* aIcon, TInt aIndex );
    void DeleteIconsIn( TInt aStart, TInt aLength );
    TInt FirstIndexAfter( TInt aDocPos, TInt aSearchStart = 0 );
    TInt FirstIndexIn( TInt aStart, TInt aLength );
    TInt LastIndexIn( TInt aStart, TInt aLength, TInt aStartIndex );
    
private: // data
    RPointerArray<CSmileyIcon> iIconArray;
    };

#endif // C_SMILEYICONRECORD_H
