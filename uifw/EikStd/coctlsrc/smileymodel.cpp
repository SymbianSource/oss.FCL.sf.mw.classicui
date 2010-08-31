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
* Description:  smiely engine class
*
*/

//#include <streamlogger.h>

#include "smileymanager.h"
#include "smileymodel.h"

const TText KSpace = ' ';
const TInt KLinkIndexMark = 0x8000;

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyInfo::CSmileyInfo
// ---------------------------------------------------------------------------
//
CSmileyInfo::CSmileyInfo()
    {    
    }

CSmileyInfo::~CSmileyInfo()
    {
    iStrArray.Reset();
    iStrArray.Close();
    }

void CSmileyInfo::Reset()
    {
    iImageInfo.Reset();
    iStrArray.Reset();
    }

void CSmileyInfo::SetSmileyText( const TDesC& aText )
    {
    TInt startIndex( KErrNotFound );
    for ( TInt i( 0 ); i <= aText.Length(); i++ )
        {
        if ( ( i == aText.Length() || aText[i] == KSpace ) && 
            startIndex != KErrNotFound )
            {
            iStrArray.Append( aText.Mid( startIndex, i - startIndex ) );
            startIndex = KErrNotFound;
            }
        if ( startIndex == KErrNotFound && i < aText.Length() && 
            aText[i] != KSpace )
            {
            startIndex = i;
            }
        }
    }
    
// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// TImageInfo::TImageInfo
// ---------------------------------------------------------------------------
//
TImageInfo::TImageInfo() : iCode( 0 ), iBmpId( 0 ), iMaskId( 0 ),
    iIsAnimation( EFalse ), iStaticBmpId( 0 ), iStaticMaskId( 0 )
    {    
    }

void TImageInfo::Reset()
    {
    iCode = iBmpId = iMaskId = iStaticBmpId = iStaticMaskId = 0;
    iIsAnimation = EFalse;
    }

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyModel::TLinkToImage::TLinkToImage
// ---------------------------------------------------------------------------
//
CSmileyModel::TLinkToImage::TLinkToImage() : iStrLength( 0 ),
    iStrNode( KInvalidIndex ), iImageIndex( KInvalidIndex )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyModel::TStrNode::TStrNode
// ---------------------------------------------------------------------------
//
CSmileyModel::TStrNode::TStrNode() : iCode(0), iSibling( KInvalidIndex ), 
    iChild( KInvalidIndex ), iParent( KInvalidIndex )
    {    
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CSmileyModel::CSmileyModel
// ---------------------------------------------------------------------------
//
CSmileyModel::CSmileyModel()    
    {    
    }
    
// ---------------------------------------------------------------------------
// CSmileyModel::~CSmileyModel
// ---------------------------------------------------------------------------
//
CSmileyModel::~CSmileyModel()
    {
    Reset();
    iStrArray.Close();
    iImageInfoArray.Close();
    iLinkArray.Close();
    delete iFileName;  
    }

// ---------------------------------------------------------------------------
// CSmileyModel::Reset
// ---------------------------------------------------------------------------
//
void CSmileyModel::Reset()
    {
    iStrArray.Reset();
    iStrArray.Compress();
    iImageInfoArray.Reset();
    iImageInfoArray.Compress();
    iLinkArray.Reset();
    iLinkArray.Compress();
    delete iFileName;
    iFileName = NULL;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::SetSmileyIconFileL
// ---------------------------------------------------------------------------
// 
void CSmileyModel::SetSmileyIconFileL( const TDesC& aIconFileName )
    {
    if ( aIconFileName.Length() > 0 )
        {
        delete iFileName;
        iFileName = NULL;
        iFileName = HBufC::NewL( aIconFileName.Length() );
        TPtr ptr( iFileName->Des() );
        ptr.Copy( aIconFileName );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyModel::SupportedCodesL
// ---------------------------------------------------------------------------
//    
HBufC* CSmileyModel::SupportedCodesL()
    {
    HBufC* codes( NULL );
    if ( iImageInfoArray.Count() > 0 )
        {
        codes = HBufC::NewL( iImageInfoArray.Count() );
        TPtr ptr( codes->Des() );
        for ( TInt i = 0; i < iImageInfoArray.Count(); i++ )
            {
            if ( ptr.Locate( iImageInfoArray[i].iCode ) == KErrNotFound )
                {
                ptr.Append( iImageInfoArray[i].iCode );                                
                }
            }
        }
    return codes;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::GetImageInfo
// ---------------------------------------------------------------------------
//
void CSmileyModel::GetImageInfo( TImageInfo& aImageInfo, HBufC** aFileName )
    {
    TInt count( iImageInfoArray.Count() );
    if ( count == 0 )
        {
        aFileName = NULL;
        aImageInfo.Reset();
        return;
        }
    for ( TInt i = 0; i < count; i++ )
        {
        if ( iImageInfoArray[i].iCode == aImageInfo.iCode )
            {
            aImageInfo = iImageInfoArray[i];
            *aFileName = iFileName;
            }
        }
    }

// ---------------------------------------------------------------------------
// CSmileyModel::AddSimleyL
// ---------------------------------------------------------------------------
//
void CSmileyModel::AddSimleyL( CSmileyInfo& aInfo )
    {
    if ( aInfo.iImageInfo.iCode < CSmileyManager::KSmileyCodeMin || 
        aInfo.iImageInfo.iCode > CSmileyManager::KSmileyCodeMax || 
        aInfo.iStrArray.Count() == 0 )
        {
        return;
        }
    for ( TInt i = 0; i < aInfo.iStrArray.Count(); i++ )
        {
        TInt imageIndex = AddLinkAndImageInfoL( aInfo, i );
        AddStringL( aInfo, imageIndex, i );
        }    
    }

// ---------------------------------------------------------------------------
// CSmileyModel::AddLinkAndImageInfoL
// ---------------------------------------------------------------------------
//
TInt CSmileyModel::AddLinkAndImageInfoL( CSmileyInfo& aInfo, TInt aStrIndex )
    {
    TLinkToImage link;
    for ( TInt i( 0 ); i < iImageInfoArray.Count(); i++ )
        {
        if ( iImageInfoArray[i].iCode == aInfo.iImageInfo.iCode )
            {
            link.iImageIndex = i;
            break;
            }
        }
    if ( link.iImageIndex == KInvalidIndex )
        {
        link.iImageIndex = iImageInfoArray.Count();
        iImageInfoArray.Append( aInfo.iImageInfo );
        }
    link.iStrLength = aInfo.iStrArray[aStrIndex].Length();
    iLinkArray.Append( link );
    return ( iLinkArray.Count() - 1 );
    }

// ---------------------------------------------------------------------------
// CSmileyModel::AddStringL
// ---------------------------------------------------------------------------
//
void CSmileyModel::AddStringL( CSmileyInfo& aInfo, TInt aLinkIndex, 
    TInt aStrIndex )
    {       
    TInt index( KInvalidIndex );    
    for ( TInt i = 0; i < aInfo.iStrArray[aStrIndex].Length(); i++ )
        {        
        TStrNode str; 
        str.iCode = aInfo.iStrArray[aStrIndex][i];
        index = AddStrNodeL( index, str );                               
        }
    iStrArray[index].iChild = ( KLinkIndexMark | aLinkIndex );
    iLinkArray[aLinkIndex].iStrNode = index;    
    }

// ---------------------------------------------------------------------------
// CSmileyModel::AddStrNodeL
// ---------------------------------------------------------------------------
//
TInt CSmileyModel::AddStrNodeL( TInt aIndex, TStrNode& aNode )
    {    
    TInt count = iStrArray.Count();
    if ( count > 0 )
        {        
        TInt child( aIndex == KInvalidIndex ? 0 : 
            iStrArray[aIndex].iChild );
        if ( child != KInvalidIndex )
            {            
            TInt index = FindInSibling( child, aNode.iCode );
            if ( index != KInvalidIndex )
                {
                return index;
                }
            iStrArray[child].iSibling = count;            
            }
        else
            {
            iStrArray[aIndex].iChild = count;
            }
        }
    aNode.iParent = aIndex;
    iStrArray.Append( aNode );
    return count;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::FindInSibling
// ---------------------------------------------------------------------------
//
TInt CSmileyModel::FindInSibling( TInt& aIndex, TText aCode )
    {
    TInt ret( KInvalidIndex );
    if ( iStrArray.Count() > 0 )
        {
        TInt index( aIndex == KInvalidIndex ? 0 : aIndex );
        while ( index != KInvalidIndex )
            {
            if ( iStrArray[index].iCode == aCode )
                {
                ret = index;
                break;
                }
            aIndex = index;
            index = iStrArray[index].iSibling;
            }        
        }
    return ret;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::FindInSibling
// ---------------------------------------------------------------------------
//
TBool CSmileyModel::IsFinalNode( TInt aIndex )
    {
    return ( aIndex != KInvalidIndex && 
        ( iStrArray[aIndex].iChild & KLinkIndexMark ) != 0 );
    }

// ---------------------------------------------------------------------------
// CSmileyModel::FindMatchStr
// ---------------------------------------------------------------------------
//
TInt CSmileyModel::TryFindMatchNode( const TDesC& aText, TInt aTextPos )
    {
    TInt index( 0 );
    index = FindInSibling( index, aText[aTextPos] );
    TInt textPos( aTextPos + 1 );
    while ( index != KInvalidIndex && !IsFinalNode( index ) && 
        textPos < aText.Length() )
        {            
        index = iStrArray[index].iChild;
        index = FindInSibling( index, aText[textPos] );
        if ( index != KInvalidIndex )
            {
            textPos++;
            }
        }
    return index;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::SmileyStringLength
// ---------------------------------------------------------------------------
//
TInt CSmileyModel::SmileyStringLength( TInt aNodeIndex )
    {
    if ( IsFinalNode( aNodeIndex ) )
        {
        TInt linkIndex( iStrArray[aNodeIndex].iChild & ~KLinkIndexMark );
        return iLinkArray[linkIndex].iStrLength;
        }
    return 0;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::SmileyCode
// ---------------------------------------------------------------------------
//
TText CSmileyModel::SmileyCode( TInt aNodeIndex )
    {
    TInt linkIndex( iStrArray[aNodeIndex].iChild & ~KLinkIndexMark );
    TInt imageIndex( iLinkArray[linkIndex].iImageIndex );
    return iImageInfoArray[imageIndex].iCode;
    }

// ---------------------------------------------------------------------------
// CSmileyModel::ReplaceTextWithCodes
// ---------------------------------------------------------------------------
//
void CSmileyModel::ReplaceTextWithCodes( TDes& aText, TInt aDocPos, 
    TInt aNodeIndex )
    {
    TInt linkIndex( iStrArray[aNodeIndex].iChild & ~KLinkIndexMark );
    TInt len( iLinkArray[linkIndex].iStrLength );
    TInt imageIndex( iLinkArray[linkIndex].iImageIndex );
    aText[aDocPos] = iImageInfoArray[imageIndex].iCode;
    aText[aDocPos + 1] = CSmileyManager::KCompensateChar;
    const TInt KThirdIndex = 2;
    for ( TInt i( KThirdIndex ); i < len; i++ )
        {
        aText[i + aDocPos] = CSmileyManager::KPlaceHolder;
        }
    }
