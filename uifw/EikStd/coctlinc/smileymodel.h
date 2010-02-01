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

#ifndef C_SMILEYMODEL_H
#define C_SMILEYMODEL_H

#include <e32base.h>
#include <e32std.h>

class CSmileyIcon;
class CSmileyIconRecord;

typedef TBuf<16> TSmileyString;

class TImageInfo
    {
public:
    TImageInfo();
    void Reset();
    
public: // data
    TUint16 iCode;
    TUint iBmpId;
    TUint iMaskId;
    TBool iIsAnimation;
    TUint iStaticBmpId;
    TUint iStaticMaskId;
    };

NONSHARABLE_CLASS( CSmileyInfo ) : public CBase
    {
public:
    CSmileyInfo();
    ~CSmileyInfo();
    void Reset();
    void SetSmileyText( const TDesC& aText );

public: // data
    TImageInfo iImageInfo;
    RArray<TSmileyString> iStrArray;
    };

/**
 *  class for reading and interpreting infomation stored in CenRep
 *
 *  @lib ?library
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CSmileyModel ) : public CBase
    {
public: //constant definition   
    static const TUint16 KInvalidIndex = 0xffff;

private: // internal class declaration    
    class TStrNode
        {
    public:
        TStrNode();
    public: // data
        TUint16 iCode;
        TUint16 iSibling;
        TUint16 iChild;
        TUint16 iParent;
        };
    
    class TLinkToImage
        {
    public:
        TLinkToImage();
        
    public: // data
        TUint8 iStrLength;
        TUint16 iStrNode;
        TUint16 iImageIndex;
        };
    
public:
// constructor
    CSmileyModel();
    
    ~CSmileyModel();
// new functions    
    HBufC* SupportedCodesL();
    
    void GetImageInfo( TImageInfo& aInfo, HBufC** aFileName );    
    void SetSmileyIconFileL( const TDesC& aIconFileName );
    void AddSimleyL( CSmileyInfo& aInfo );
    void Reset();
    
    //void PrintSmileyInfoL();
    
    TBool IsFinalNode( TInt aIndex );
    TInt TryFindMatchNode( const TDesC& aText, TInt aStartPos );
    TInt SmileyStringLength( TInt aNodeIndex );
    TText SmileyCode( TInt aNodeIndex );
    void ReplaceTextWithCodes( TDes& aText, TInt aDocPos, TInt aNodeIndex );

private:    
    TInt AddLinkAndImageInfoL( CSmileyInfo& aInfo, TInt aStrIndex );    
    void AddStringL( CSmileyInfo& aInfo, TInt aLinkIndex, TInt aStrIndex );  
      
    TInt AddStrNodeL( TInt aIndex, TStrNode& aNode );    
    TInt FindInSibling( TInt& aIndex, TText aCode );
    TInt FindInChild( TInt& aIndex, TText aCode );

    
private: // data        
    RArray<TStrNode> iStrArray;
    RArray<TLinkToImage> iLinkArray;
    RArray<TImageInfo> iImageInfoArray;
    HBufC* iFileName;   
    };

#endif C_SMILEYMODEL_H
