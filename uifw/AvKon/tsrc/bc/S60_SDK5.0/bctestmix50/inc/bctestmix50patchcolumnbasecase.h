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
* Description:  base test case for various list classes
*
*/


#ifndef C_BCTESTMIX50PATCHCOLUMNBASECASE_H
#define C_BCTESTMIX50PATCHCOLUMNBASECASE_H

#include "bctestcase.h"

class CBCTestMix50Container;
class CEikListBox;
class CEikTextListBox;
class CEikColumnListBox;
class CEikFormattedCellListBox;
class CTextListBoxModel;
class CEikonEnv;
class CGulIcon;

const TInt KBCTestListInitListResourceId = 0;
const TInt KBCTestListInitEmptyResourceId = 0;
const TInt KBCTestListMessageInitId = 0;
const TInt KBCTestListAddInitCount = 0;
const TInt KBCTestListRemoveInitCount = 0;
const TInt KBCTestListGraphicGulIconIndex = 10;
const TInt KBCTestListDefaultFlag = 0;
_LIT(KAvkonMbmFileName, "\\resource\\apps\\avkon2.mbm");
_LIT(KBCTestListMbmFileName, "\\resource\\apps\\bctestmix50.mbm");
//Define .mif file for .svg icons
_LIT(KBCTestListMifFileName, "\\resource\\apps\\bctestmix50.mif"); 

/**
* list base case class
* @since S60 v5.0
*/
class CBCTestMix50ListBaseCase: public CBCTestCase
    {
public: 

// constructor and destructor
    
    CBCTestMix50ListBaseCase( CBCTestMix50Container* iContainer, 
        CEikonEnv* aEikEnv = NULL );
    
    ~CBCTestMix50ListBaseCase();
    
// new functions
    
    /**
    * Sets listbox from resource using ConstructFromResourceL() of
    * CEikColumnListBox class.
    * @param aListBox Pointer of listbox.
    * @param aResourceId Resource ID of listbox.
    */
    void SetListBoxFromResourceL( CEikColumnListBox* aListBox,
                                  const TInt aResourceId );
    
    /**
    * Sets listbox from resource using ConstructFromResourceL() of
    * CEikFormattedCellListBox class.
    * @param aListBox Pointer of listbox.
    * @param aResourceId Resource ID of listbox.
    */
    void SetListBoxFromResourceL( CEikFormattedCellListBox* aListBox,
                                  const TInt aResourceId );
                                  
    /**
    * Sets listbox from inner description using ConstructL() of
    * CEikColumnListBox class.
    * @param aListBox Pointer of listbox.
    * @param aFlags Flags of listbox.
    * @param textArray List items as CDesCArray.
    */
    void SetListBoxFromInnerDescriptionL(
        CEikColumnListBox* aListBox,
        const TInt aFlags = KBCTestListDefaultFlag,
        CDesCArray* textArray = NULL );
        
    /**
    * Sets listbox from inner description using ConstructL() of
    * CEikFormattedCellListBox class.
    * @param aListBox Pointer of listbox.
    * @param aFlags Flags of listbox.
    * @param textArray List items as CDesCArray.
    */
    void SetListBoxFromInnerDescriptionL(
        CEikFormattedCellListBox* aListBox,
        const TInt aFlags = KBCTestListDefaultFlag,
        CDesCArray* textArray = NULL );
    
    /**
    * Sets graphic icon using listbox as CEikColumnListBox.
    * @param aListBox Pointer of listbox.
    */
    void SetGraphicIconL( CEikColumnListBox* aListBox );

    /**
    * Sets graphic icon using listbox as CEikFormattedCellListBox.
    * @param aListBox Pointer of listbox.
    */
    void SetGraphicIconL( CEikFormattedCellListBox* aListBox );

    /**
    * Creates the icon and adds it to the array if it was successful
    * @param aIconsArray Pointer of icon using graphics for listbox.
    * @param aIconFile the path of iconfile using graphics for listbox.
    * @param aBitmap the resource id of Bitmap.
    * @param aMask the resource id of MaskBitmap.
    */
    void CreateIconAndAddToArrayL( CArrayPtr<CGulIcon>*& aIconsArray, 
        const TDesC& aIconFile,
        TInt aBitmap, TInt aMask = -1);
    
private: // New Function

    /**
    * Appends graphics data.
    * @param aIcons Pointer of icon using graphics for listbox.
    */
    virtual void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );
    
protected: // data
    
	CBCTestMix50Container* iContainer; // not own
    
    CEikonEnv* iEikEnv; // not own
    
    TInt iOutlineId;
    
    };

#endif /*BCTESTMIX50PATCHCOLUMNBASECASE_H*/
