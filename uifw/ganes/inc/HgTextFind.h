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


#ifndef HGTEXTFIND_H_
#define HGTEXTFIND_H_

#include <e32base.h>
#include <fepbase.h>
#include <aknedsts.h>

class CHgScroller;

NONSHARABLE_CLASS( CHgTextFind ) :
    public CBase, 
    public MCoeFepAwareTextEditor,
    public MCoeFepAwareTextEditor_Extension1
    {
public:
    static CHgTextFind* NewL(CHgScroller& aScroller);
    virtual ~CHgTextFind();
    
public: // from MCoeFepAwareTextEditor
    void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, 
        TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, 
        MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
    void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText);
    void SetInlineEditingCursorVisibilityL(TBool aCursorVisibility);
    void CancelFepInlineEdit();
    TInt DocumentLengthForFep() const;
    TInt DocumentMaximumLengthForFep() const;
    void SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection);
    void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const;
    void GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const;
    void GetFormatForFep(TCharFormat& aFormat, TInt aDocumentPosition) const;
    void GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine, TInt& aHeight, TInt& aAscent, TInt aDocumentPosition) const;
    MCoeFepAwareTextEditor_Extension1* Extension1(TBool& aSetToTrue);

public: // MCoeFepAwareTextEditor_Extension1
    void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid);
    CState* State(TUid aTypeSafetyUid);

public:
    const TDesC& Text();
    
private: // from MCoeFepAwareTextEditor
    void DoCommitFepInlineEditL();

private:
    CHgTextFind( CHgScroller& aScroller ); 
    void ConstructL();

private:
    static TInt SearchTimerCallback( TAny* aSelf );
    void ClearSearchDesc();


public:
    CAknEdwinState* iState;
    CPeriodic* iTimer; // Used for triggering search string clearing
    CHgScroller& iScroller;

    RBuf iSearchDesc; // Search string
    RBuf iBuf; // Type in buffer
    };




#endif /* HGTEXTFIND_H_ */
