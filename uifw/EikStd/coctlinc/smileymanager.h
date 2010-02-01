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

#ifndef C_SMILEYMANAGER_H
#define C_SMILEYMANAGER_H

#include <e32base.h>
#include <e32std.h>

class CCoeControl;
class CBitmapContext;
class CSmileyModel;
class CSmileyInfoReader;
class CSmileyDrawer;
class TRgb;
class CEikEdwin;
class CSmileyIconRecord;

_LIT( KSmileyString, "\xf8e4i" );

/**
 *  smiley engine class, manage smiley character strings and icons
 *
 *  @lib ?library
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CSmileyManager ) : public CBase
    {
public:
    static const TText KPlaceHolder = 0xfff0;
    static const TInt KMaxLength = 5;
    static const TInt KMinLength = 2;
    static const TText KZeroCode = 0;
    static const TText KCompensateChar = 'i'; 
    static const TUint KSmileyCodeMin = 0xf880;
    static const TUint KSmileyCodeMax = 0xf8e4;    
    
    enum TOperationType
        {
        EDelete = 0,
        EInsert,
        ESetCursor,
        ESelection
        };
    
//static constructors
    static CSmileyManager* NewL( CEikEdwin& aEdwin );
    static CSmileyManager* NewLC( CEikEdwin& aEdwin );

    virtual ~CSmileyManager();

//new functions    
    TBool ConvertTextForSmileyL( TInt aStart, TDes& aText, 
        TBool aStringToCodes = ETrue );
    void SetVisibleRange( TInt aDocPos, TInt aLength );
    
    void DrawIconL( CBitmapContext& aGc, const TRect& aRect, 
        TInt aDocPos );
    
    void HandleDeleteL( TInt aStart, TInt aLength );
    void HandleInsertL( TInt aStart, TInt aLength );
    void HandleSetCursor( TInt aOldCursor, TInt& aNewCursor );
    void HandleSelection( TInt aStart, TInt aLength  );
    
    void SetHighlightColor( TRgb aColor );

    void SetAnimationPlayTimes( TInt aPlayTimes );
    TText SmileyCodeByPos( TInt aDocPos );
    TInt SmileyLength( TInt aDocPos );
    
    static TBool IsSmileyCode( TText aCode );
    void RemoveIconsInRange( TInt aStart, TInt aLength );
    
    TBool HasSmileyIconsInText();
    TBool IsDisabledSmileyIcon( TInt aDocPos );
    void DisableSmileyIcon( TInt aDocPos );
    
private:
//constructors    
    CSmileyManager();
    void ConstructL( CEikEdwin& aEdwin );
    TBool ConvertCodesToTextL( TDes& aText, TInt aStart );
    TBool ConvertTextToCodesL( TDes& aText, TInt aStart );
    void AddSmileyToRecordL( const TDesC& aSmileyText, TInt aDocPos, 
        TText aCode );
    
private: // data    
    // own
    CSmileyModel* iModel;
    // own
    CSmileyInfoReader* iReader;
    // own
    CSmileyDrawer* iDrawer;
    // own
    CSmileyIconRecord* iIconRecord;

    TInt iSelStart;
    TInt iSelLength;
    TInt iVisibleStart;
    TInt iVisibleLength;
    };

#endif // C_SMILEYMANAGER_H
