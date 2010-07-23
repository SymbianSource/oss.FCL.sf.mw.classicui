/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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

   
#if !defined(__EIKTXLBX_H__)
#define __EIKTXLBX_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKLBX_H__)
#include <eiklbx.h>
#endif

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

class CTextListBoxModel;

/**
* List box for displaying text.
*
* Text list boxes use the standard list box view, @c CListBoxView, and a 
* customised item drawer and list box model.
*
* @since Symbian 5.0
*/
class CEikTextListBox : public CEikListBox
	{
public:

    /**
     * Destructor.
     */
    IMPORT_C ~CEikTextListBox();

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikTextListBox();
    
    /**
     * Second phase construction from a resource.
     *
     * This constructor initialises the list box model, flags, required 
     * dimensions etc. from a resource. The function fully constructs the 
     * associated list box model and item drawer for this list box.
     *
     * @param aReader A resource reader initialised to point at a list box
     *        resource
     */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	
    /**
     * By default Symbian 2nd phase constructor is private
     *
     * This initializes the C-classes of a newly-created @c CEikTextListBox 
     * from supplied arguments. This function fully constructs the associated 
     * list box model and item drawer for this list box, and then invokes 
     * @c CEikListBox::ConstructL().
     *
     * @param aParent Parent control for this control. 
     * @param aFlags Flags for the list box.
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);

    /**
     * Gets the text list box model.
     *
     * @return The text list box model used by this list box.
     */
    IMPORT_C CTextListBoxModel* Model() const;

public:	// from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Gets the list of logical colours employed in the drawing of the control,
     * paired with an explanation of how they are used. Appends the list to 
     * @c aColorUseList.
     *
     * @deprecated
     * @param aColorUseList List of logical colours.
     */
    IMPORT_C virtual void GetColorUseListL(
                                CArrayFix<TCoeColorUse>& aColorUseList) const; 
                                // not available before Release 005u

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources. These resources are of 
     * type aType, which are shared across the environment, for example 
     * colours or fonts.
     *
     * @param aType The type of resource that has changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);			
                    // not available before Release 005u
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events. 
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: //from CCoeControl

    /**
     * From @c CCoeControl
     *
     * Write internal state of the @c CEikTextListBox to the given stream.
     * NOTE: Only operational in debug mode.
     *
     * @param aWriteStream Target stream.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

protected:
	
    /**
     * Creates @c CTextListItemDrawer for @c CListBoxView for drawing
     * individual list box items .
     */
    IMPORT_C virtual void CreateItemDrawerL();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
protected:
	TInt iRequiredCellCharWidth;
private:
	
    TInt iSpare;		// Unused
	};

/**
* Horizontal snaking text list box.
* 
* This snaking list box is intended for displaying text. The list box lays its 
* items out using the @c CEikSnakingListBox algorithms, and uses a 
* @c CTextListItemDrawer to draw its items.
*
* @since Symbian 5.0
*/
class CEikSnakingTextListBox : public CEikSnakingListBox
	{
public:
	
    /**
     * Destructor.
     */
    IMPORT_C ~CEikSnakingTextListBox();

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikSnakingTextListBox();
	
    /**
     * By default Symbian 2nd phase constructor is private.
     *
     * Completes the construction of a default-constructed snaking text list 
     * box, initialising its heap-stored members from the supplied arguments. 
     * This function will leave if any of the pointer members being 
     * constructed leave.
     *
     * @param aParent Parent control. 
     * @param aFlags Flags for the control. 
     * @see @c CEikListBox::TFlags
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);

    /**
     * Gets a pointer to the model used by this list box.
     *
     * @return This list box model.
     */
    IMPORT_C CTextListBoxModel* Model() const;

public:	// from CCoeControl
	
    /**
     * From @c CCoeControl.
     *
     * Not implemented or used in S60.
     *
     * @param aColorUseList On return, a list of logical colours.
     */
    IMPORT_C virtual void GetColorUseListL(
                        CArrayFix<TCoeColorUse>& aColorUseList) const; 
                        // not available before Release 005u

    /**
     * From @c CCoeControl.
     *
     * Handles a change in a resource.
     *
     * The types (@c aType) of list box resources handled are those which 
     * are shared across the environment, for example, colours or fonts.
     *
     * @param aType The type of resource that has changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);			
                        // not available before Release 005u

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events. 
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    };


#endif  // __EIKTXLBX_H__
