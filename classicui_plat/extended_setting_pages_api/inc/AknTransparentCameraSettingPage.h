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
*     Support for transparent camera setting page.
*
*/


#ifndef __AKNTRANSPARENTCAMERASETTINGPAGE_H__
#define __AKNTRANSPARENTCAMERASETTINGPAGE_H__ 

#include <fbs.h>
// For coecontrol
#include <coecntrl.h>
#include <eikdef.h>

#include <AknListBoxSettingPage.h>

class CAknTransparentCameraSettingPageExtension;

/** 
*  This class sets out a transparent radio button listbox within a setting page.
*  Transparency is created by giving the setting page a background bitmap from the camera app.
*  The setting page will then draw itself on the bitmap.
*  @since 2.6
*/
class CAknTransparentCameraSettingPage : public CAknListBoxSettingPage
{
public:
    IMPORT_C CAknTransparentCameraSettingPage(
        TInt aResourceID, 
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.  
 *
 *      Editor Resource     Setting Page Resource
 *          present             present             Both are used (but text & number overridden)
 *           = 0                present             Editor resource is used via SP resource
 *          present             = 0                 Default Avkon SP resource if used
 *           = 0                = 0                 Not permitted 
 *
 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 * Note that the setting title provided here must be owned by the client.
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText Text at top of setting pane; EXTERNALLY OWNED
 * @param aSettingNumber        Number at top left (if present)
 * @param aControlType          Determines the type constructed and how its resource is read
 * @param aEditorResourceId Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId        Setting Page to use (if present)
 * @param aCurrentSelectionIndex    THe currently selected index
 * @param aItemArray            List of option texts and their selection states
 * @since 2.6
 */
    IMPORT_C CAknTransparentCameraSettingPage(  const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,
                                TInt& aCurrentSelectionIndex, 
                                const MDesCArray* aItemArray );

    /** 
    * 2nd stage contruction for this type.  Calls CAknSettingPage::BaseConstuctL() where the object is constructed
    * from resource.
    *  @since 2.6
    */
    IMPORT_C virtual void ConstructL();

    /** 
    * Type specific access to the hosted "editor"
    *
    * @return   pointer to contained listbox
    * @since 2.6
    */
    IMPORT_C CAknSetStyleListBox* ListBoxControl() const; 

    /**
    * Display the setting page and wait for users selection
    *
    * @param aMode The update mode of the class
    * @param aReplaceNaviPane if this param is EFalse, The navi pane will not be replaced,
    * User can still touch all components in navipane for setting. if it is ETue, the navi
    * pane will be replaced with empty contents
    * @return ETrue if user accept the setting, EFalse if user cancel.
    * @since 5.0
    */
    IMPORT_C TBool ExecuteLD( enum CAknSettingPage::TAknSettingPageUpdateMode aMode, 
                              TBool aReplaceNaviPane = ETrue );

    /** 
    * From MEikListBoxObserver
    * @param    listbox generating the event
    * @param    type of listbox event
    * @since 2.6
    */
    IMPORT_C virtual void HandleListBoxEventL(CEikListBox* aListBox,
                 MEikListBoxObserver::TListBoxEvent aEventType);

    /**
    * Method to update the item array after a change in content and to re-select 
    * the "pushed in" index
    * @param CDesCArrayFlat*    aItemArray  The new item array; array of texts
    * @param TInt                   aPushed     A valid 0-based index.  -1 is also legal
    * indicating nothing is pushed
    * @since 2.6
    */
    IMPORT_C void SetItemArrayAndSelectionL( const MDesCArray* aItemArray, TInt aPushed );
    
    /**
    * Function to update the setting page background. Calling this will force
    * the setting page to redraw itself.
    * See SetBitmapPositionAndClipRect() comments for more info.
    * @param aBitmap   Bitmap which is used as the background for the whole setting page.
    * @since 2.6
    */
    IMPORT_C void ChangeBackground(CFbsBitmap* aBitmap);

    /**
    * C++ destructor
    * @since 2.6
    */
    IMPORT_C virtual ~CAknTransparentCameraSettingPage();

    /**
    * Sets the correct position & clipping rect for the background bitmap.
    * This function MUST BE CALLED before calling ChangeBackground!
    * @param aPoint Position of bitmap's top left corner
    * @param aRect  Clipping rect
    * @since 2.6
    */
    IMPORT_C void SetBitmapPositionAndClipRect(const TPoint aPoint, const TRect aRect);
    
    IMPORT_C void HandleResourceChange(TInt aType);
    
    IMPORT_C void SetBitmapPositionAndClipRect(const TPoint aPoint, const TRect aRect, 
        const TBool aFullScreenUsed);
    
protected:

    /**
    * Called when the external setting is to be updated
    * @since 2.6
    */
    IMPORT_C virtual void UpdateSettingL();

    /**
    * Called immediately prior to activation, but after all construction
    * @since 2.6
    */
    IMPORT_C void DynamicInitL();

    /**
     * This method overrides the default implementation in order to do the special 
     * processing of selecting an item
     *
     * @since 2.6
     */
    IMPORT_C virtual void SelectCurrentItemL();

//From MCoeControlObserver

    /**
    * Acts upon changes in the hosted control's state. 
    *
    * @param    aControl    The control changing its state (not used)
    * @param    aEventType  The type of control event 
    * @since 5.0
    */
    IMPORT_C void HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent aEventType);

//From MEikCommandObserver

    /**
    * Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyBack
    * to accept or cancel the pop-up.
    *
    * @param    aCommandId  Event Id from the soft-key
    * @since 5.0
    */
    IMPORT_C void ProcessCommandL(TInt aCommandId);


private:
    /**
    * Method to move the selection to position aPushed
    *
    * @since 2.6
    */
    void SetRadioButtonSelectionL( TInt aPushed );

    /**
    * Internal method to re-generate the internal, "decorated" text array used in the
    * real listbox. 
    * @since 2.6
    */
    void GenerateInternalArrayAndGiveToListBoxL();
    
    void CreateBitmapArrayAndGiveToListBoxL();

//
// CoeControl Framework and reserved methods
//
public:

    /** 
    *
    * This routine routes the keys to the editor. 
    * However, if the menu is showing, then events are sent to the menu. 
    *
    * @param    aKeyEvent   event information   
    * @param    aType       type of event being handled
    *
    * @since 3.1
    */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

protected:

    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param   aWriteSteam     A connected write stream
     * @since 2.6
     */ 
    IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

    /**
    * Handles the size change events.
    * @since 2.6
    */
    IMPORT_C virtual void SizeChanged();

    /** 
    * Draws the setting page on top of the camera view 
    *
    * @param aRect  rectangle within which to draw
    * @since 2.6
    */
    IMPORT_C void Draw(const TRect& aRect) const;
    
private:
    /**
    *   Reserved method derived from CCoeControl
    *   @since 2.6
    */
    IMPORT_C virtual void Reserved_2();

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
    IMPORT_C virtual void CAknSettingPage_Reserved_1();
    IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
    /**
     * New reserved method from CAknListBoxSettingPage
     * @since 2.6
     *
     */
    IMPORT_C virtual void CAknListBoxSettingPage_Reserved_1();

    /**
    * Called when the user accepts or cancels the setting. Default implementation
    * sets the return value and exists. 
    * 
    * @param   aAccept ETrue if the user accepted. EFalse if the user cancelled.
    */
    void AttemptExitL(TBool aAccept);

private:
    // Back up copy of the selection index
    TInt iOldSelectionIndex;

    // This CBase object is owned.  Note that this depends upon the ownership flag given 
    // to the CTextListBoxModel object
    CDesCArrayFlat* iInternalItemArray; 

    // The objects pointed to or referenced by these are not owned
    TInt& iCurrentSelectionIndex; 
    const MDesCArray* iItemArray; 

    CAknTransparentCameraSettingPageExtension* iExtension;

};

#endif 
