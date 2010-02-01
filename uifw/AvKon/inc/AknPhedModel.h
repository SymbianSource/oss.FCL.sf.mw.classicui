/*
* Copyright (c) 2002 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNPHEDMODEL_H
#define AKNPHEDMODEL_H

#include <e32base.h>

#include "AknPhedDataObserver.h"
#include "NumberGrouping.h"


class CAknPhedBuffers;
class CAknPhedModel;
class TAknPhedDataMirror;


NONSHARABLE_CLASS(CAknPhedScratchBuffer) : public CBase
    {
    public:
        CAknPhedScratchBuffer();
        ~CAknPhedScratchBuffer();
        void ConstructL(TInt aMaxLen);
        
        // Writable access to the scratch area
        inline TPtr ScratchBuffer() const;
    protected:
        HBufC* iBuf;
        TPtr iPtr;
    };




//
// CAknPhedModel
//
// The editor model combines a two way text buffer with cursor and selection logic
//
NONSHARABLE_CLASS(CAknPhedModel) : public CBase
    {
    public:
        // construction & destruction
        static CAknPhedModel* NewL(TInt aMaxLen);
        ~CAknPhedModel();
        
        // Observer interface
        inline MPhedDataObserver* Observer();
        inline void SetObserver(MPhedDataObserver* aObserver);
        
        // Text access
        inline TInt Length() const;
        inline TInt MaxDisplayLength() const;
        inline TPtrC Text(TInt aFrom=0) const;
        inline TPtrC Text(TInt aFrom, TInt aTo) const;
        inline TPtrC ReverseText(TInt aFrom=0) const;
        inline TPtrC ReverseText(TInt aFrom, TInt aTo) const;
        
        inline TPtrC UnFormattedText(TInt aFrom=0) const;
        inline TPtrC UnFormattedText(TInt aFrom, TInt aTo) const;
        
        inline TBool IsSpace(TInt aPos) const;
        TInt Spaces(TInt aTo, TInt aFrom) const;
        TInt Spaces( TInt aToPos ) const;
        inline TPtr TranslationBuffer() const;
        
        // Text setting
        void SetText(const TDesC& aText);
        
        enum TDirection{EDown, EUp};
        
        // Cursor/selection relative text manipulation
        void Insert(TText aChar);
        void DeleteLeft();
        void DeleteLeft(TInt aIndex, TInt aCount=1);
        void Cut(TDes& aCutText);
        void Copy(TDes& aCopiedText) const;
        void Paste(const TDesC& aText);
        
        // Cursor manipulation
        inline TInt CursorPosition() const;
        // The following three functions clear any selection
        // Now return a TInt indicating the new cursor position
        TInt SetRealCursorPosition(TInt aCursorPos);  
        TInt SetCompensatedCursorPosition(TInt aCursorPos); 
        TInt CursorLeft();
        TInt CursorRight();
        
        // Selection manipulation
        TPtrC           Selection() const;
        inline TBool    SelectionExists() const;
        inline TInt     AnchorPosition() const;
        TInt            SetAnchorPosition(TInt aAnchorPos);
        inline void     SelectLeft();
        inline void     SelectRight();
        inline TInt     LeftMark() const;
        inline TInt     RightMark() const;
        inline TInt     SelectionWidth() const;
        
        // testing support
        inline TBool InvariantOk() const;
        inline void ForceLanguage(TLanguage aLanguage);
        TInt Language()  const;
        TInt   Uncompensate( TInt aCompensatedPosition ) const;
        friend class TAknPhedDataMirror;
        
    private:
        void    ConstructL(TInt aMaxLen);
        void    Insert(const TDesC& aText);
        TBool   ClearAnySelection();
        void    SelectMove(TInt aInc);
        TBool   CursorPositionIsSpace();
        TInt    Compensate(TInt aRealPosition) const;
        
        void StartEvent();
        void ReportEvent(const MPhedDataObserver::TAknPhedDataEvent& aEvent);
        
    private:
        TDirection          iCursorDirection;
        CAknPhedScratchBuffer* iBuf;            // owned
        CPNGNumberGrouping* iNumberGroupingBuffer;
        TInt                iRealLength;
        
        TInt                iRealCursor;
        TInt                iRealAnchor;
        TPtrC               iSelection;
        
        TInt iCount;
        
        MPhedDataObserver* iObserver;
        MPhedDataObserver::TAknPhedDataEvent iEvent;
        TInt iEventDepth;
    };


//
// TAknPhedDataMirror
//
// CAknPhedModel position indexing is from the left hand side. This class reverses
// all the positioning functions so that they index from the right hand side.
//
    NONSHARABLE_CLASS(TAknPhedDataMirror) : public MPhedDataObserver
        {
public:
    inline TAknPhedDataMirror();
    inline void SetPhedModel(CAknPhedModel* aPhed);
    
    // Position mirror+ iBuf    0x13c42088
    
    inline TInt Mirror(TInt aPos) const;
    inline TInt Compensate(TInt aMirroredPosition, TInt aRealPosition) const;
    
    // Text access
    inline TPtrC Text(TInt aFrom=0) const;
    inline TPtrC Text(TInt aFrom, TInt aTo) const;
    inline TPtrC ReverseText(TInt aFrom=0) const;
    inline TPtrC ReverseText(TInt aFrom, TInt aTo) const;
    
    // Observer interface
    inline MPhedDataObserver* Observer();
    inline void SetObserver(MPhedDataObserver* aObserver);
    
    // Cursor manipulation
    inline TInt CursorPosition() const;
    inline TInt SetCompensatedCursorPosition(TInt aCursorPos);
    inline TInt SetRealCursorPosition(TInt aCursorPos);
    
    // Selection manipulation
    inline TInt AnchorPosition() const;
    inline TInt SetAnchorPosition(TInt aAnchorPos);
    inline TInt LeftMark() const;
    inline TInt RightMark() const;
    
    void HandlePhedDataEvent(const TAknPhedDataEvent& aEvent, 
                             CAknPhedModel* aPhedData);

    TInt Compensate(TInt aMirrorPosition) const;
    
private:
    CAknPhedModel*      iPhed;
    MPhedDataObserver*  iObserver;
        };
    
    inline TPtr CAknPhedScratchBuffer::ScratchBuffer() const 
        { return iPtr; }
    // MPhedDataObserver inlines
    inline MPhedDataObserver::TAknPhedDataEvent::TAknPhedDataEvent() 
        : iType(0), iStart(0), iEnd(0) 
        {}
    
    inline MPhedDataObserver::TAknPhedDataEvent::TAknPhedDataEvent(TInt aType) 
        : iType(aType), iStart(0), iEnd(0) 
        {}
    
    inline MPhedDataObserver::TAknPhedDataEvent::TAknPhedDataEvent( TInt aType, 
        TInt aStart, 
        TInt aEnd ) 
        : iType(aType), iStart(aStart), iEnd(aEnd) 
        {}
    
    inline void MPhedDataObserver::TAknPhedDataEvent::Reset() 
        { iType = iStart = iEnd = 0; }
    
    inline TBool MPhedDataObserver::TAknPhedDataEvent::TextChanged() const 
        { return iType & EText; }
    
    inline TBool MPhedDataObserver::TAknPhedDataEvent::CursorChanged() const 
        { return iType & ECursor; }
    
    inline TBool MPhedDataObserver::TAknPhedDataEvent::SelectionChanged() const 
        { return iType & ESelection; }
    
    inline void MPhedDataObserver::TAknPhedDataEvent::TextChangeRange( TInt& aStart, 
                                                                       TInt& aEnd ) const 
        { aStart = iStart; aEnd = iEnd; }
    
    inline TInt MPhedDataObserver::TAknPhedDataEvent::Type() const
        { return iType; }
    
    
    // CAknPhedModel inlines
    inline MPhedDataObserver* CAknPhedModel::Observer()
        { return iObserver; }
    
    inline void CAknPhedModel::SetObserver(MPhedDataObserver* aObserver)
        { iObserver = aObserver; }
    
    inline TInt CAknPhedModel::Length() const
        { return iNumberGroupingBuffer->Length();}
    
    inline TInt CAknPhedModel::MaxDisplayLength() const
        { return iNumberGroupingBuffer->MaxDisplayLength(); }
    
    inline TPtr CAknPhedModel::TranslationBuffer() const
        { return iBuf->ScratchBuffer(); }
    
    inline TInt CAknPhedModel::CursorPosition() const
        { return Compensate(iRealCursor); }
    
    inline TBool CAknPhedModel::SelectionExists() const
        { return CursorPosition() != AnchorPosition(); }
    
    inline TInt CAknPhedModel::AnchorPosition() const
        { return Compensate(iRealAnchor); }
    
    inline TBool CAknPhedModel::IsSpace(TInt aPos) const
        { return iNumberGroupingBuffer->IsSpace(aPos); }
    
    inline TInt CAknPhedModel::LeftMark() const
        { return (iRealAnchor < iRealCursor) 
        ? iRealAnchor 
        : iRealCursor; }
    
    inline TInt CAknPhedModel::RightMark() const
        { return (iRealAnchor > iRealCursor) 
        ? iRealAnchor
        : iRealCursor; }
    
    inline TInt CAknPhedModel::SelectionWidth() const
        { return RightMark() - LeftMark(); }
    
    inline void CAknPhedModel::SelectLeft()
        { SelectMove(-1); }
    
    inline void CAknPhedModel::SelectRight()
        { SelectMove(+1); }
    
    inline TPtrC CAknPhedModel::Text(TInt aFrom) const
        { return Text(aFrom, iNumberGroupingBuffer->Length() - 1); }
    
    inline TPtrC CAknPhedModel::Text(TInt aFrom, TInt aTo) const
        { return iNumberGroupingBuffer->FormattedNumber(aFrom, aTo); }
    
    inline TPtrC CAknPhedModel::ReverseText(TInt aFrom) const
        { return ReverseText(aFrom, iNumberGroupingBuffer->Length() - 1); }
    
    inline TPtrC CAknPhedModel::ReverseText(TInt aFrom, TInt aTo) const
        { return iNumberGroupingBuffer->ReverseFormattedNumber(aFrom, aTo); }
    
    inline TPtrC CAknPhedModel::UnFormattedText(TInt aFrom) const
        { return iNumberGroupingBuffer->UnFormattedNumber(aFrom, iNumberGroupingBuffer->UnFormattedLength() - 1); }
    
    inline TPtrC CAknPhedModel::UnFormattedText(TInt aFrom, TInt aTo) const
        { return iNumberGroupingBuffer->UnFormattedNumber(aFrom, aTo); }
    
    inline TBool CAknPhedModel::InvariantOk() const
    { /*return 
      0 <= iCompensatedCursor && iCompensatedCursor <= Length() && 
      0 <= iCompensatedAnchor && iCompensatedAnchor <= Length() &&
    iEventDepth == 0; */
    return ETrue; }
    
    void CAknPhedModel::ForceLanguage(TLanguage aLanguage)
        { iNumberGroupingBuffer->iForceLanguage = aLanguage; }
    
    // TAknPhedDataMirror inlines
    inline TAknPhedDataMirror::TAknPhedDataMirror() : iPhed(0), iObserver(0)
        {}
    
    inline void TAknPhedDataMirror::SetPhedModel(CAknPhedModel* aPhed)
        { iPhed = aPhed; }
    
    inline TInt TAknPhedDataMirror::Mirror(TInt aPos) const
        { return iPhed->iNumberGroupingBuffer->Length() - aPos; }
    
    inline TPtrC TAknPhedDataMirror::Text(TInt aFrom) const
        { return iPhed->ReverseText(aFrom); }
    
    inline TPtrC TAknPhedDataMirror::Text(TInt aFrom, TInt aTo) const
        { return iPhed->ReverseText(aFrom, aTo); }
    
    inline TPtrC TAknPhedDataMirror::ReverseText(TInt aFrom) const
        { return iPhed->Text(aFrom); }
    
    inline MPhedDataObserver* TAknPhedDataMirror::Observer()
        { return iObserver; }
    
    inline void TAknPhedDataMirror::SetObserver(MPhedDataObserver* aObserver)
        { iObserver = aObserver; iPhed->SetObserver(this); }
    
    inline TInt TAknPhedDataMirror::CursorPosition() const
        { return Compensate(Mirror(iPhed->iRealCursor), iPhed->iRealCursor); }
    
    // This function is defective. It uses Mirror, 
    // which does not work in real space see MRED-5GPJQQ
    inline TInt TAknPhedDataMirror::SetRealCursorPosition(TInt aCursorPos)
        { return iPhed->SetRealCursorPosition(Mirror(aCursorPos)); }
    
    inline TInt TAknPhedDataMirror::SetCompensatedCursorPosition(TInt aCursorPos)
        { return iPhed->SetCompensatedCursorPosition(Mirror(aCursorPos)); }
    
    inline TInt TAknPhedDataMirror::AnchorPosition() const
        { return Compensate(Mirror(iPhed->iRealAnchor), iPhed->iRealAnchor); }
    
    inline TInt TAknPhedDataMirror::SetAnchorPosition(TInt aAnchorPos)
        { return iPhed->SetAnchorPosition(Mirror(aAnchorPos)); }
    
    inline TInt TAknPhedDataMirror::LeftMark() const
        { return Compensate(Mirror(iPhed->LeftMark()), iPhed->LeftMark()); }
    
    inline TInt TAknPhedDataMirror::RightMark() const
        { return Compensate(Mirror(iPhed->RightMark()), iPhed->RightMark()); }
    
    inline TInt TAknPhedDataMirror::Compensate(TInt aMirrorPosition, TInt aRealPosistion) const
        {
        if ( iPhed->Language() )
        	{
            return aMirrorPosition - iPhed->Spaces(0, aRealPosistion); 
        	}
        else
        	{
        	return aMirrorPosition; 
        	}
        }
    
#endif
    
