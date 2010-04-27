/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <barsread.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>

#include <AknBidiTextUtils.h>
#include <AknPanic.h>

#include <smiley.rsg>
#include <smiley.mbg>

#include "AknSmileyModel.h"
#include "AknSmileyImage.h"
#include "akntrace.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// TSmileyIconInfo
///////////////////////////////////////////////////////////////////////////////////////////////

TSmileyIconInfo::TSmileyIconInfo()
    {
    Reset();
    }

TSmileyIconInfo::TSmileyIconInfo(const TSmileyIconInfo& aInfo) : 
iSkinItemID(aInfo.iSkinItemID), 
iDefaultStillImageID(aInfo.iDefaultStillImageID), 
iDefaultAnimationImageID(aInfo.iDefaultAnimationImageID)
    {
    }

void TSmileyIconInfo::Reset()
    {
    iSkinItemID.Set(0, 0);
    iDefaultStillImageID = 0;
    iDefaultAnimationImageID = 0;
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyIcon
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyIcon* CSmileyIcon::NewL(const TSmileyIconInfo& aInfo, MAknSmileyObserver* aObserver)
    {
    CSmileyIcon* self = new (ELeave) CSmileyIcon(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL(aInfo);
    CleanupStack::Pop(); // self;
    return self;
    }

void CSmileyIcon::ConstructL(const TSmileyIconInfo& aInfo)
    {
    iIndex = aInfo.iIndex;
    
    iStillImage = CSmileyImage::NewL(aInfo.iSkinItemID, aInfo.iDefaultStillImageID, EFalse, this);
    
    if(aInfo.iSkinItemID.iMinor==0 && aInfo.iDefaultAnimationImageID>0)
        {
        TAknsItemID nullID;
        nullID.Set(0, 0);
        iAnimationImage = CSmileyImage::NewL(nullID, aInfo.iDefaultAnimationImageID, ETrue, this);
        }
    }

CSmileyIcon::CSmileyIcon(MAknSmileyObserver* aObserver) : iSmileyIconObserver(aObserver)
    {
    }

CSmileyIcon::~CSmileyIcon()
    {
    delete iStillImage;
    delete iAnimationImage;
    
    iTextArray.Close();
    iCodeArray.Close();
    }

const CFbsBitmap* CSmileyIcon::Image() const
    {
    if(AnimationImageIsReadyToDraw())
        {
        return iAnimationImage->Image();
        }
    else
        {
        return iStillImage->Image();
        }
    }

const CFbsBitmap* CSmileyIcon::Mask() const
    {
    if(AnimationImageIsReadyToDraw())
        {
        return iAnimationImage->Mask();
        }
    else
        {
        return iStillImage->Mask();
        }
    }

TBool CSmileyIcon::ReadyToDraw() const
    {
    return StillImageIsReadyToDraw() || AnimationImageIsReadyToDraw();
    }

void CSmileyIcon::SetSize(const TSize& aSize)
    {
    iStillImage->SetSize(aSize);
    
    if(iAnimationImage)
        {
        iAnimationImage->SetSize(aSize);
        }
    }

const TSize& CSmileyIcon::Size() const
    {
    return iStillImage->Size();
    }

void CSmileyIcon::PlayAnimationL(TInt aRepeat, TInt aDelay)
    {
    if(iAnimationImage)
        {
        iAnimationImage->LoadL(aRepeat, aDelay);
        }
    }

void CSmileyIcon::StopAnimation()
    {
    if(iAnimationImage)
        {
        iAnimationImage->Release();
        }
    }

void CSmileyIcon::BitmapChanged(CSmileyImage* aSmileyImage, CFbsBitmap* /*aBitmap*/)
    {
    if(aSmileyImage == iStillImage)
        {
        if(iSmileyIconObserver) iSmileyIconObserver->SmileyStillImageLoaded(this);
        }
    else
        {
        if(iSmileyIconObserver) iSmileyIconObserver->SmileyAnimationChanged(this);
        }
    }

TInt CSmileyIcon::Index() const
    {
    return iIndex;
    }

void CSmileyIcon::LoadStillImageL(TInt aDelay)
    {
    iStillImage->LoadL(0, aDelay);
    }

TBool CSmileyIcon::StillImageIsReadyToDraw() const
    {
    return iStillImage->ReadyToDraw();
    }

TBool CSmileyIcon::AnimationImageIsReadyToDraw() const
    {
    return (iAnimationImage && iAnimationImage->ReadyToDraw());
    }

void CSmileyIcon::AddVariant(const TDesC& aText, TChar aBaseCode)
    {
    TPtrC ptr(aText);
    TUint16 baseCode = aBaseCode;

    while(ptr.Length())
        {
        TInt left = ptr.Find(_L(" "));
        TInt right = ptr.Length() - left - 1;
        if(left == KErrNotFound)
            {
            left = ptr.Length();
            right = 0;
            }

        iTextArray.Append(ptr.Left(left));
        ptr.Set(ptr.Right(right));
        iCodeArray.Append(baseCode++);
        }
    }

TInt CSmileyIcon::VariantCount() const
    {
    return iTextArray.Count();
    }
const TDesC& CSmileyIcon::Text(TInt aVariant) const
    {
    if(aVariant>=0 && aVariant<VariantCount())
        {
        return iTextArray[aVariant];
        }
    else
        {
        return KNullDesC;
        }
    }

TChar CSmileyIcon::Code(TInt aVariant) const
    {
    if(aVariant>=0 && aVariant<VariantCount())
        {
        return iCodeArray[aVariant];
    }
    else
        {
        return 0;
        }
    }


///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyTnumbnailAsynLoader
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyTnumbnailAsynLoader::CSmileyTnumbnailAsynLoader()
    {
    
    }

CSmileyTnumbnailAsynLoader::~CSmileyTnumbnailAsynLoader()
    {
    iLoadingTaskArray.Close();
    }

void CSmileyTnumbnailAsynLoader::AddTaskL(CSmileyIcon* aSmileyIcon)
    {
    if(aSmileyIcon)
        {
        TBool isIdel = (TaskCount() == 0);
        iLoadingTaskArray.Append(aSmileyIcon);
        if(isIdel)
            {
            DoNextTaskL();
            }
        }
    }

void CSmileyTnumbnailAsynLoader::DiscardAll()
    {
    iLoadingTaskArray.Reset();
    }

TInt CSmileyTnumbnailAsynLoader::TaskCount() const
    {
    return iLoadingTaskArray.Count();
    }

void CSmileyTnumbnailAsynLoader::DoNextTaskL()
    {
    if(TaskCount() > 0)
        {
        CSmileyIcon* icon = iLoadingTaskArray[0];
        iLoadingTaskArray.Remove(0);
        
        if(icon->StillImageIsReadyToDraw())
            {
            DoNextTaskL();
            }
        else
            {
            icon->LoadStillImageL();
            }
        }
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyTextTreeNode
///////////////////////////////////////////////////////////////////////////////////////////////

NONSHARABLE_CLASS(CSmileyTextTreeNode) : public CBase
    {
public:
    CSmileyTextTreeNode(TChar aChar);
    ~CSmileyTextTreeNode();

    TChar Char() const;

    CSmileyTextTreeNode* AddTreeL(const TDesC& aText, TChar aCode);
    TInt ChildCount() const;
    CSmileyTextTreeNode* Child(TInt aIndex) const;
    CSmileyTextTreeNode* Child(TChar aChar) const;
    
private:
    CSmileyTextTreeNode* AddChildAscendingL(TChar aChar);
    
private:
    TChar   iChar;
    
    typedef CArrayPtrFlat<CSmileyTextTreeNode> CSmileyTextTreeNodeArrayPtrFlat;
    CSmileyTextTreeNodeArrayPtrFlat* iChildArray;
    
    };


CSmileyTextTreeNode::CSmileyTextTreeNode(TChar aChar) : iChar(aChar)
    {
    }

CSmileyTextTreeNode::~CSmileyTextTreeNode()
    {
    if(iChildArray)
        {
        iChildArray->ResetAndDestroy();
        delete iChildArray;
        }
    }

TChar CSmileyTextTreeNode::Char() const
    {
    return iChar;
    }



CSmileyTextTreeNode* CSmileyTextTreeNode::AddTreeL(const TDesC& aText, TChar aCode)
    {
    TInt length = aText.Length();
    if(length > 0)
        {
        CSmileyTextTreeNode* node = AddChildAscendingL(aText[0]);
        return node->AddTreeL(aText.Right(length-1), aCode);
        }
    else
        {
        return AddChildAscendingL(aCode);
        }
    }

TInt CSmileyTextTreeNode::ChildCount() const
    {
    if(iChildArray)
        {
        return iChildArray->Count();
        }
    else
        {
        return 0;
        }
    }

CSmileyTextTreeNode* CSmileyTextTreeNode::Child(TInt aIndex) const
    {
    if(aIndex>=0 && aIndex<ChildCount())
        {
        return iChildArray->At(aIndex);
        }
    else
        {
        return NULL;
        }
    }

CSmileyTextTreeNode* CSmileyTextTreeNode::Child(TChar aChar) const
    {
    if(iChildArray)
        {
        const TInt KFirstPos = 0;
        const TInt KEndPos = iChildArray->Count() - 1;
        if(aChar<iChildArray->At(KFirstPos)->Char() || aChar>iChildArray->At(KEndPos)->Char())
            {
            return NULL;
            }
        for(TInt i=KEndPos; i>=KFirstPos; i--)
            {
            CSmileyTextTreeNode* node = iChildArray->At(i);
            if(node->Char() == aChar)
                {
                return node;
                }
            }
        }
    
    return NULL;
    }

CSmileyTextTreeNode* CSmileyTextTreeNode::AddChildAscendingL(TChar aChar)
    {
    // new
    if(!iChildArray)
        {
        iChildArray = new (ELeave) CSmileyTextTreeNodeArrayPtrFlat(1);
        }
    
    // sequential search
    TInt pos = 0;
    for(; pos<iChildArray->Count(); pos++)
        {
        CSmileyTextTreeNode* node = iChildArray->At(pos);
        TChar character = node->Char();
        if(aChar == character)
            {
            return node;
            }
        else if(aChar < character)
            {
            break;
            }
        }
    
    CSmileyTextTreeNode* node = new (ELeave) CSmileyTextTreeNode(aChar);
    iChildArray->InsertL(pos, node);
    return node;
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyModel
///////////////////////////////////////////////////////////////////////////////////////////////

const TUint16 KBaseCode = 0xf880;
//const TUint16 KBaseCodeOff = 0x7FFF;
_LIT(KPlaceHolder, "\xf880i");

CSmileyModel::CSmileyModel(MAknSmileyObserver* aObserver) : iSmileyIconObserver(aObserver)
    {
    }

CSmileyModel::~CSmileyModel()
    {
    ReleaseResource();
    
    iSmileyIconArray.Close();
    iSmileyCodeIndexArray.Close();
    }

void CSmileyModel::LoadResourceL()
    {
    if(Count() > 0) return;

    // append image resourece
    TResourceReader reader;
    TFileName smileyRscName;
    SmileyUtils::GetCustomizableResPath(smileyRscName, KSmileyRsc);
    TInt offset = CCoeEnv::Static()->AddResourceFileL(smileyRscName);
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_SMILEY_ICONS_INFO);

    TUint16 codeRef = KBaseCode;
    TInt index = 0;
    
    iTextSearchTree = new (ELeave) CSmileyTextTreeNode(0);
    
    TInt count(reader.ReadInt16());
    for(TInt i(0); i<count; i++)
        {
        TSmileyIconInfo info;

        TBool isAnimation = (reader.ReadInt16() == 1);
        TInt16 code = reader.ReadInt16();
        TInt bmpId1 = reader.ReadInt32();
        TInt maskId1 = reader.ReadInt32();
        TInt bmpId2 = reader.ReadInt32();
        TInt maskId2 = reader.ReadInt32();
        
        
        info.iIndex = index++;

        if(bmpId2 > 0)
            {
            info.iDefaultStillImageID = bmpId2;
            info.iDefaultAnimationImageID = bmpId1;
            }
        else
            {
            info.iDefaultStillImageID = bmpId1;
            info.iDefaultAnimationImageID = 0;
            }

        TBuf<64> smileyName = reader.ReadTPtrC(); // strings
        
        CSmileyIcon* icon = CSmileyIcon::NewL(info, this);
        icon->AddVariant(smileyName, codeRef);
        iSmileyIconArray.Append(icon);
        
        // build text search tree
        for(TInt j=0; j<icon->VariantCount(); j++)
            {
            iTextSearchTree->AddTreeL(icon->Text(j), codeRef++);
            iSmileyCodeIndexArray.Append(TSmileyCodeIndex(icon,j));
            }
        }
    
    CCoeEnv::Static()->DeleteResourceFile(offset);
    CleanupStack::PopAndDestroy(); // reader
    
    // sct & smiley switch icon
    TSmileyIconInfo info;
    info.iIndex = index++;
    info.iSkinItemID = KAknsIIDQgnIndiSwitchSmiley2;
    info.iDefaultStillImageID = EMbmSmileyQgn_indi_switch_smiley2;
    CSmileyIcon* switchSmileyIcon = CSmileyIcon::NewL(info, this);
    iSmileyIconArray.Append(switchSmileyIcon);
    iSmileyCodeIndexArray.Append(TSmileyCodeIndex(switchSmileyIcon));

    info.iIndex = index++;
    info.iSkinItemID = KAknsIIDQgnIndiSwitchSct2;
    info.iDefaultStillImageID = EMbmSmileyQgn_indi_switch_sct2;
    CSmileyIcon* switchSctIcon = CSmileyIcon::NewL(info,this);
    iSmileyIconArray.Append(switchSctIcon);
    iSmileyCodeIndexArray.Append(TSmileyCodeIndex(switchSctIcon));

    }

void CSmileyModel::ReleaseResource()
    {
    if(Count() == 0) return;

    // reset array
    for(TInt i(0); i<ArrayCount(); i++)
        {
        delete iSmileyIconArray[i];
        iSmileyIconArray[i] = NULL;
        }
    iSmileyIconArray.Reset();
    
    iSmileyCodeIndexArray.Reset();
    // reset task loader
    iSmileyLoader.DiscardAll();
    
    delete iTextSearchTree;
    iTextSearchTree = NULL;
    
    }

TInt CSmileyModel::ConvertCodesToTextL(TDes& aText)
    {
    TInt converted = 0;
    iConvertBuffer.Zero();
    
    // deal all
    TInt pos = 0;
    while(pos < aText.Length())
        {
        TChar character = aText[pos++];
        if(IsSmiley(character))
            {
            converted++;
            pos++; // jump the 'i'
            iConvertBuffer.Append(Text(character));
            }
        else
            {
            iConvertBuffer.Append(character);
            }
        }
    
    // replace
    if(converted)
        {
        aText.Copy(iConvertBuffer);
        }

    return converted;
    }

TInt CSmileyModel::ConvertTextToCodesL(TDes& aText)
    {
    _AKNTRACE_FUNC_ENTER;
    TInt converted = 0;
    iConvertBuffer.Zero();

    CSmileyTextTreeNode* node = iTextSearchTree;
    TInt matchedLength = 0;

    // deal all
    TInt pos = 0;
    while(pos < aText.Length())
        {
        TChar character = aText[pos++];
        iConvertBuffer.Append(character);

            CSmileyTextTreeNode* find = node->Child(character);
            if(find)
                {
                matchedLength++; // character is mathed
                
                CSmileyTextTreeNode* child = find->Child(0);
            TBool notFinished = (child && child->ChildCount());
            if(notFinished) // not ended
                    {
                node = find; // match next 
                continue;
                }
            else if(child) // whole combination is matched and ended
                {
                    TChar code = child->Char();

                    // replace with code
                    iConvertBuffer.SetLength(iConvertBuffer.Length() - matchedLength);
                    iConvertBuffer.Append(code);
                    iConvertBuffer.Append('i');
                converted++; // returned value added
                    // load thumnail
                    LoadStillImageL(code);

                    // restart
                    matchedLength = 0;
                    node = iTextSearchTree;
                continue;
                    }
            else // in this case matchedLength already increased by 1
                {
                matchedLength--;
                }
            }
        
        // matching failed
        if(matchedLength)
            {
            // back to the 2nd char
            TInt rollBack = matchedLength;
            iConvertBuffer.SetLength(iConvertBuffer.Length() - rollBack);
            pos -= rollBack;

            // reset matching context
            matchedLength = 0;
            node = iTextSearchTree;
            }
        }
    
    // replace
    if(converted)
        {
        aText.Copy(iConvertBuffer);
        }

    _AKNTRACE_FUNC_EXIT;
    return converted;
    }

TBool CSmileyModel::IsSmiley(TChar aCode) const
    {
    TInt smileyCodeIndex = (TUint16)aCode - KBaseCode;
    return (smileyCodeIndex>=0 && smileyCodeIndex<iSmileyCodeIndexArray.Count());
    }

const TDesC& CSmileyModel::Text(TChar aCode) const
    {
    if(IsSmiley(aCode))
        {
        TInt smileyCodeIndex = (TUint16)aCode - KBaseCode;
        return iSmileyCodeIndexArray[smileyCodeIndex].Text();
        }
    else
        {
        return KNullDesC;
        }
    }

void CSmileyModel::SetSize(const TSize& aSize)
    {
    if(ArrayCount() && iSmileyIconArray[0]->Size()!=aSize)
        {
        for(TInt i(0); i<ArrayCount(); i++)
            {
            iSmileyIconArray[i]->SetSize(aSize);
            }
        }
    }

void CSmileyModel::SetSizeByFont(const CFont* aFont)
    {
    TSize size(aFont->TextWidthInPixels(KPlaceHolder),aFont->HeightInPixels());
    SetSize(size);
    }

void CSmileyModel::DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TPoint& aPosition) const
    {
    TPtrC ptr = aText;
    TPoint pos = aPosition;
    
    aGc.UseFont(aFont);
    
    TBool metSmileyNotReady = EFalse;
 
    while(ptr.Length())
        {
        TInt i = 0;
        for(; i<ptr.Length(); i++) // find next smiley code
            {
            if(IsSmiley(ptr[i]))
                {
                break;
                }
            }
        
        if(i > 0) // have text
            {
            TPtrC txt = ptr.Left(i);
            aGc.DrawText(txt, pos);
            pos += TPoint(aFont->TextWidthInPixels(txt),0);

            ptr.Set(ptr.Right(ptr.Length()-i));
            i = 0;
            }
        
        if(ptr.Length()) // breaked by smiley code
            {
            CAknSmileyIcon* icon = Smiley(ptr[i]);
            if(icon)
                {
                TSize size = icon->Size();
                TPoint tl = pos;
                tl.iY = tl.iY - (size.iHeight + aFont->HeightInPixels()) / 2;
                if(!metSmileyNotReady && icon->ReadyToDraw())
                    {
                    aGc.BitBltMasked(tl, icon->Image(), TRect(size), icon->Mask(), EFalse);
                    }
                else
                    {
                    metSmileyNotReady = ETrue;
                    }
                pos += TPoint(aFont->TextWidthInPixels(ptr.Left(2)),0);
                }
            
            ptr.Set(ptr.Right(ptr.Length()-2));
            }
        }
    }

void CSmileyModel::DrawText(CWindowGc& aGc, const TDesC& aText, const TAknLayoutText& aLayout, TBool aUseLogicalToVisualConversion) const
    {
    _AKNTRACE_FUNC_ENTER;
    // adapter variables
    const CFont* font = aLayout.Font();
    TRect textRect = aLayout.TextRect();
    TInt offset = aLayout.BaselineOffset();
    CGraphicsContext::TTextAlign align = aLayout.Align();
    
    // belows are all from 
    // void TAknLayoutText::DrawText(CGraphicsContext& aGc,const TDesC& aText,TBool aUseLogicalToVisualConversion, const TRgb &aColor) const
    
    __ASSERT_DEBUG(font, Panic(EAknPanicLayoutTextNotCalled));
    
    //aGc.UseFont( font );
    //aGc.SetPenColor( aColor );
    if ( aText.Length() )
        {
        HBufC* visualBuf = NULL;
        TPtrC text( aText );
        
        if ( aUseLogicalToVisualConversion )
            {
            visualBuf = HBufC::New( aText.Length() + KAknBidiExtraSpacePerLine );
            
            // In OOM, logical to visual conversion is not performed...
            
            if ( visualBuf )
                {
                *visualBuf = aText; // copy
                TPtr ptr = visualBuf->Des();
                
                TInt maxWidth = textRect.Size().iWidth;
                // Logical to visual conversion.
                AknBidiTextUtils::ConvertToVisualAndClip(
                    aText,
                    ptr,
                    *font,
                    maxWidth,
                    maxWidth );
                // for smiley begin
                const TInt length = ptr.Length();
                if(length>1 && IsSmiley(ptr[length-2]))
                    {
                    if(ptr[length-1] != 'i')
                        {
                        // smiley is clipped for visual, del this smiley
                        ptr.Delete(length-2, 1);
                        }
                    }
                // for smiley end

                text.Set( ptr );
                }
            }
        
        // Calculate x-offset based on the used alignment
        TInt margin = 0;
        if ( align != CGraphicsContext::ELeft )
            {
            // Measure the full width of the text (ie. what DrawText needs)
            TInt textWidth = AknBidiTextUtils::MeasureTextBoundsWidth( *font, text,CFont::TMeasureTextInput::EFVisualOrder );
            
            const TInt extraWidth = textRect.Width() - textWidth;
            if ( align == CGraphicsContext::ECenter )
                {
                margin = extraWidth / 2;
                }
            else // right aligned
                {
                margin = extraWidth;
                }
            }

        // Need to make the drawing rectangle bigger to account for underlines
        TRect drawRect(textRect);
        TInt height = drawRect.Height();
        // The underline position is not available from the GC. The following code imitates what Symbian CFbsBitGC implements.
        // (height-offset) is the part below the baseline. Check if it sufficient
        TInt extraHeightForUnderlining =   1 + Max(1, height/10)-(height-offset);
        if ( extraHeightForUnderlining > 0 )
            drawRect.iBr.iY += extraHeightForUnderlining;

        // for smiley
        //aGc.DrawText( text, drawRect, offset, CGraphicsContext::ELeft, margin );
        DrawText(aGc, text, font, drawRect, offset, CGraphicsContext::ELeft, margin);
        
        delete visualBuf;
        }
    
    //aGc.DiscardFont(); // Release the font cache
    _AKNTRACE_FUNC_EXIT;
    }

void CSmileyModel::DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, TInt aBaselineOffset, 
                            CGraphicsContext::TTextAlign aAlignment, TInt aLeftMargin) const
    {
    TInt boxWidth = aBox.Width();
    TInt textWidth = aFont->TextWidthInPixels(aText);
    
    TPoint offset;
    offset.iY = aBaselineOffset;
    
    switch(aAlignment)
        {
        case CGraphicsContext::ELeft:
            offset.iX = aLeftMargin;
            break;
            
        case CGraphicsContext::ERight:
            offset.iX = boxWidth - textWidth - aLeftMargin;
            break;
            
        case CGraphicsContext::ECenter:
            offset.iX = (boxWidth - textWidth) / 2;
            break;
            
        default:
            break;
        }
    
    DrawText(aGc, aText, aFont, aBox, offset);
    }

void CSmileyModel::DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, const TPoint& aOffset) const
    {
    TPtrC ptr = aText;
    TPoint offset = aOffset;
    
    aGc.UseFont(aFont);
    
    TInt fontH = aFont->FontMaxHeight();
    
    TBool metSmileyNotReady = EFalse;
 
    while(ptr.Length())
        {
        TInt i = 0;
        for(; i<ptr.Length(); i++) // find next smiley code
            {
            if(IsSmiley(ptr[i]))
                {
                break;
                }
            }
        
        if(i > 0) // have text
            {
            TPtrC txt = ptr.Left(i);
            aGc.DrawText(txt, aBox, offset.iY, CGraphicsContext::ELeft, offset.iX);
            offset.iX += aFont->TextWidthInPixels(txt);

            ptr.Set(ptr.Right(ptr.Length()-i));
            i = 0;
            }
        
        if(ptr.Length()) // breaked by smiley code
            {
            CAknSmileyIcon* icon = Smiley(ptr[i]);
            if(icon)
                {
                TSize size = icon->Size();
                TPoint tl = aBox.iTl;
                tl.iX += offset.iX;
                //tl.iY = tl.iY - size.iHeight/*(size.iHeight + fontH) / 2*/;
                TRect imgWindow(tl, size);
                imgWindow.Intersection(aBox);
                if(!imgWindow.IsEmpty())
                    {
                    TRect innerRect = TRect(imgWindow.iTl-tl,imgWindow.Size());
                    if(!metSmileyNotReady && icon->ReadyToDraw())
                        {
                        aGc.BitBltMasked(imgWindow.iTl, icon->Image(), innerRect, icon->Mask(), EFalse);
                        }
                    else
                        {
                        metSmileyNotReady = ETrue;
                        }
                    }

                //offset += TPoint(aFont->TextWidthInPixels(ptr.Left(2)),0);
                offset.iX += size.iWidth;
                }
            
            ptr.Set(ptr.Right(ptr.Length()-2));
            }
        }
    }

CAknSmileyIcon* CSmileyModel::Smiley(TChar aCode) const
    {
    if(IsSmiley(aCode))
        {
        TInt smileyCodeIndex = (TUint16)aCode - KBaseCode;
        return iSmileyCodeIndexArray[smileyCodeIndex].Smiley();
        }
    else
        {
        return NULL;
        }
    }

CAknSmileyIcon* CSmileyModel::operator[](TInt aIndex) const
    {
    if(aIndex>=0 && aIndex<ArrayCount())
        {
        return iSmileyIconArray[aIndex];
        }
    else
        {
        return NULL;
        }
    }

TInt CSmileyModel::Count() const
    {
    return iSmileyIconArray.Count() - 2;
    }

CAknSmileyIcon* CSmileyModel::SwitchToSmileyIcon() const
    {
    return (*this)[Count()];
    }

CAknSmileyIcon* CSmileyModel::SwitchToSctIcon() const
    {
    return (*this)[Count()+1];
    }

TChar CSmileyModel::SwitchToSmileyCode() const
    {
    return SmileyCode(Count());
    }

TChar CSmileyModel::SwitchToSctCode() const
    {
    return SmileyCode(Count()+1);
    }

TChar CSmileyModel::SmileyCode(TInt aIndex, TInt aVariant) const
    {
    const CAknSmileyIcon* iconWrapper = (*this)[aIndex];
    const CSmileyIcon* icon = static_cast<const CSmileyIcon*>(iconWrapper);
    if(icon)
        {
        return icon->Code(aVariant);
        }
    else
        {
        return 0;
        }
    }

TChar CSmileyModel::SmileyCode(const CAknSmileyIcon* aSmileyIcon) const
    {
    if(aSmileyIcon)
        {
        const CSmileyIcon* icon = static_cast<const CSmileyIcon*>(aSmileyIcon);
        return icon->Code();
        }
    else
        {
        return 0;
        }
    }

void CSmileyModel::LoadStillImagesL(const TDesC& aText)
    {
    for(TInt i(0); i<aText.Length(); i++)
        {
        LoadStillImageL(aText[i]);
        }
    }

void CSmileyModel::LoadStillImageL(TChar aChar)
    {
    CSmileyIcon* icon = static_cast<CSmileyIcon*>(Smiley(aChar));
    iSmileyLoader.AddTaskL(icon);
    }

const TDesC& CSmileyModel::Text(TInt aIndex, TInt aVariant) const
    {
    CSmileyIcon* icon = static_cast<CSmileyIcon*>((*this)[aIndex]);
    if(icon)
        {
        return icon->Text(aVariant);
        }
    else
        {
        return KNullDesC;
        }
    }

TInt CSmileyModel::ArrayCount() const
    {
    return iSmileyIconArray.Count();



    }

void CSmileyModel::SmileyStillImageLoaded(CAknSmileyIcon* aSmileyIcon)
    {
    TRAP_IGNORE(iSmileyLoader.DoNextTaskL());

    if(iSmileyIconObserver) iSmileyIconObserver->SmileyStillImageLoaded(aSmileyIcon);
    }

void CSmileyModel::SmileyAnimationChanged(CAknSmileyIcon* aSmileyIcon)
    {
    if(iSmileyIconObserver) iSmileyIconObserver->SmileyAnimationChanged(aSmileyIcon);
    }


// end of file

