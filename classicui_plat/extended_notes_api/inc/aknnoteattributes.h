/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Stores attributes of note control. Since these attributes are
*                sometimes stored by the dialog before constructing the 
*                control, this class is the interface for passing attributes 
*                from the dialog to the control.
*
*/

#ifndef __AKNNOTEATTRIBUTES__
#define __AKNNOTEATTRIBUTES__ 

#include <e32base.h>

class CEikImage;
class CEikLabel;

class CEikProgressInfo;
class CAknProgressTimer;

class CAknNoteControl;
class CAknTextControl;

class CAknsFrameBackgroundControlContext;
class CCoeBrushAndPenContex;
class TAknsItemID;

/** 
 * Indexes into iFlags.
 * Can't use zero as this is the default behaviour (no flag indexes set).
 */
enum TNoteFlags
    {
    ENoteNoTextWrapping        = 1, ///< EAknNoteNoTextWrapping 
    ENoteNeedLayoutControl     = 2, ///< When this flag is on, the note control needs layout
    ENoteNeedLayoutDialog      = 3, ///< When this flag is on, the dialog needs layout
    ENoteNoTextProcessing      = 4, ///< When this flag is on, the note performs no text processing
    ENoteDoNotAllocateMem      = 5,
    ENoteAnimationStarted      = 6,
    ENoteLeftSKWhenTapped      = 7, ///< EAknNoteLeftSoftkeyWhenTapped
    ENoteWithSkinnableGraphics = 8  ///< EAknNoteFlagWithSkinnableGraphics
    };

NONSHARABLE_CLASS(CAknNoteAttributes) : public CBase
    {
public:
    enum { EMaxNumberOfLabels = 5 };

public:
    CAknNoteAttributes();
    CAknNoteAttributes(CAknNoteControl* aNoteControl);
    ~CAknNoteAttributes();

public:
    CAknNoteAttributes& operator=(CAknNoteAttributes& aAttributes);
    void ConstructFromResourceL(TResourceReader& aRes);

public:
    void SetAnimationL(TInt aResourceId);
    void SetImageL(CEikImage* aImage);
    void SetIconL(CEikImage* aIcon);

    void SetFinalProgressValue(TInt aValue);
    TInt IncrementBarsAndDraw(TInt aIncrement);
    void CreateProgressBarL();

    void SetTextPluralityL(TBool aIsPlural);
    void SetTextNumberL(TInt aNumber);

    void SetTextL(const TDesC& aText);
    void SetTextL(const TDesC& aText, TInt aLineNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths);

    void AttemptOptimizedTextDrawingL(TInt aOldNumberOfLines);
    void AllowOptimizedDrawing();

public:
    void StartAnimationL();
    TInt CancelAnimation();

public:
    TPtrC Text() const;
    void  ParseTextL(const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths);

public:
    ///Layout type
    enum TLayoutType 
        { 
        EDialog = 0, ///Entire dialog needs layout. 
        EControl = 1 ///EControl: only control needs layout 
        };  

    TBool IsLayoutNeeded(const TLayoutType& aType = EDialog) const;                     
    void  SetLayoutDone(const TLayoutType& aType = EDialog);
    void  InvalidateLayout();

private:
    void TransferToControlL();
    void TransferToControlL(CCoeControl* aControl);

    static TInt StaticPictographCallBack( TAny* aPtr );
    void PictographCallBack();

private:
    CAknNoteAttributes(const CAknNoteAttributes&); //not allowed

public:
    CAknTextControl*     iNoteText;    ///The note text
                                          
    CEikImage*           iImage;       ///The note image at top right 
    CEikImage*           iIcon;        ///The small icon at bottom left (number type indic, etc)
                                          
    CEikProgressInfo*    iProgressBar; ///A progress bar for wait notes
    CAknProgressTimer*   iTimer;       ///Time for progress bar
                                          
    CAknBitmapAnimation* iAnimation;   ///An animation replacing the image
    TBitFlags            iFlags;       ///Flags that determine behavior
    TBitFlags            iClearFlags;  ///Flags that inhibit behaviour, used in operator= only 
                                          
    TRect                iBgRect;      ///For nondialog controls
                                          
private:                                  
    CAknNoteControl*     iNoteControl; ///Not owned - The control that owns us or NULL
    
public:
    CAknsFrameBackgroundControlContext* iBgContext; 
    CCoeBrushAndPenContext* iBrushAndPenContext;

public: // New skin utility functions 
    IMPORT_C static TAknsItemID GetSkinnedBitmapID(TInt aIcon);
    void SetAnimationBackGroundFrameL(); 

private: // new data
    TInt iAnimationID;
    TBool iAllowOptimizedDrawing;

public:
    void HandleSkinChangeL();

private:
    HBufC*               iImageFile;
    TInt                 iImageId;
    TInt                 iImageMask;
    TAknsItemID          iSkinIdForImage;
    };

#endif
