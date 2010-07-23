/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __AKNSTATICNOTEDIALOG__
#define __AKNSTATICNOTEDIALOG__

#include <aknnotedialog.h>
#include <AknControl.h>

class CEikImage;
class CAknStackIndicatorAttributes;

/**
 * Static note stack indicator
 */
class CAknStaticNoteStackIndicator : public CAknControl
	{
public:
    /**
     * 2nd stage construction.
     *
    */
	void ConstructL(CCoeControl* aParentNote, TInt aStackDepth);
	
	/**
     * Updates stack depth
     *
    */
	void UpdateDepth(TInt aDepth);
	
	~CAknStaticNoteStackIndicator();
	
    /**
     * From @c CCoeControl.
     * 
     * Handles a change to the control's resources. The types of resources 
     * handled are those which are shared across the environment, e.g. 
     * colours or fonts.
     *
     */
	IMPORT_C void HandleResourceChange(TInt aType);
    
    /**
     * From @c CCoeControl. 
     * Handles pointer events
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    	
private:
	void Draw(const TRect& aRect) const;
	void DoSetExtent();
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	CAknStackIndicatorAttributes* iAttributes;
	CCoeControl* iParentNote;
	};


/**
 * Static note dialog
 */
class CAknStaticNoteDialog : public CAknNoteDialog
	{
	
public:
    /**
     * Default constructor    
     * Just call CAknNoteDialog constructor
    */
	IMPORT_C CAknStaticNoteDialog();
	
	/**
     * Another class constructor
     *
     * Accept self pointer to CEikDialog* in order to NULL 
     * client pointer when a non modal note is dismissed.
     *
     * @param aSelfPtr Address of the dialog pointer
    */
	IMPORT_C CAknStaticNoteDialog(CEikDialog** aSelfPtr);
	
	IMPORT_C virtual ~CAknStaticNoteDialog();

    /**
     * Set the number of borders
     *
     * Update the stack indicator depth to the specified number of borders. 
     * 
     * @param aNumber    The number of borders
    */
    IMPORT_C void SetNumberOfBorders(TInt aNumber);

    /**
     * Handles pointer events
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

protected:
    /**
     * Part of dialog framework, called after layout has been performed
     *
     * Call PostLayoutDynInitL as implemented in the base, CAknNoteDialog
     * and create a stack indicator
     * 
    */
	IMPORT_C void PostLayoutDynInitL();
	
	/**
     * Part of the dialog framework, process a key event.
     *
     * Call the implementation of OfferKeyEventL provided by
     * CEikDialog, bypassing the direct base, CAknNoteDialog.
    */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

protected:
    /**
     * Stack indicator    
     * 
    */
	CAknStaticNoteStackIndicator* iStackIndicator;
	
	/**
     * Indicates stack depth    
     *
    */
	TInt iStackDepth;
	
private:
	TInt iSpare;
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();
		
private: 
	IMPORT_C virtual void CAknNoteDialog_Reserved();
	
private: // new virtual function.
	IMPORT_C virtual void CAknStaticNoteDialog_Reserved();
	};

#endif
