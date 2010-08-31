/*
* Copyright (c) 2001-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Command button class interfaces. Contains a common base class
*  for command-generating buttons, plus several concrete, specialized classes
* 
*
*/


#if !defined(__EIKCMBUT_H__)
#define __EIKCMBUT_H__

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

#if !defined(__GULUTIL_H__)
#include <gulutil.h>
#endif

class CEikLabel;
class CEikImage;
class CEikAlignedControl;
class TResourceReader;
class CEikCommandStack;

/**
 *  Base class for buttons that generate commands.
 *
 *  MControlContext is mixed in. This class is used as the interface to the button member of 
 *  CEikLabeledButton, as well as being the base class for CEikCommandButton, CEikTextButton, and CEikBitmapButton
 *
 *  @lib eikcoctl.dll
 *  @since S60 1.0
 */
class CEikCommandButtonBase : public CEikButtonBase, public MCoeControlContext
	{
public:
    /**
    * Enumeration to tag the components of a command button (text or image)
    */
    enum TWhichComponent
        {
        EFirst,
        ESecond
        };
    
    /**
    * Controls which of the components of the command button are shown.
    */    
    enum TDisplayContent
        {
        EFirstOnly	=0x0100,
        ESecondOnly	=0x0200,
        EBoth		=0x0300
        };

    /*
    * Layout and font options for the components of the command button
    */
    enum TLayout
        {
        EFirstRightSecondLeft=0x0000,
        EFirstBottomSecondTop=0x0001,
        EFirstTopSecondBottom=0x0002,
        EFirstLeftSecondRight=0x0003,
        EDenseFont			 =0x0008
    };
    
    /**
    * Options for where excess space between the two components of the command button is distrubuted
    */
    enum TExcess
		{
		EShare	=0x0000,
		EToFirst	=0x0010,
		EToSecond =0x0020
		};

public: // new functions

    /**
    * C++ destructor
    */
    IMPORT_C ~CEikCommandButtonBase();

    /**
    * Sets the layout of the button
    * @param aLayout    Layout enumeration
    */
    IMPORT_C void SetButtonLayout(TLayout aLayout);

    /**
    * Sets where excess space is to be put
    * @param aExcess    Excess space enumeration
    */
    IMPORT_C void SetExcessSpace(TExcess aExcess);
    
    /**
    * Sets the content of the button
    *
    * @param aContent
    */
    IMPORT_C void SetDisplayContent(TDisplayContent aContent);
    
    /**
    * Causes the content to be (re-)laid out.
    */
    IMPORT_C void LayoutComponents();

    /**
    * Read preamble part of the resource. This call can be followed by calls to 
    * ConstructLabelFromResourceL and/or ConstructImageFromResourceL to complete contruction.
    */
    IMPORT_C void StartConstructFromResourceL(TResourceReader& aReader);

    /**
    * Constructs a label component for the button
    * 
    * @aparam aWhich    Which component to construct in this call
    */
    IMPORT_C void ConstructLabelFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);

    /**
    * Constructs an image component for the button
    *
    * @aparam aWhich    Which component to construct in this call
    */
    IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);

    /**
    * Cause a recalculation of the components alignment
    */
    IMPORT_C virtual void UpdateComponentAlignment();

    /**
    * Sets this button to be the default.
    */
    IMPORT_C void SetDefault(TBool aIsDefault);
    
public:	// from CCoeControl. See base class documentation
    /**
    * From CCoeControl
    *
    * Sets the button to be inactive. The button is drawn with a dimmed effect. 
    *
    *  @param aDimmed   If not EFalse, set the state to dimmed. Otherwise set to non-dimmed
    */
    IMPORT_C void SetDimmed(TBool aDimmed);
    
    /**
    * From CCoeControl
    *
    * Reports to the caller the minimum size that the control can be, given its contents.
    *
    *  @return  The minimum size
    */
    IMPORT_C TSize MinimumSize();
    
    /**
    * From CCoeControl
    *
    * Returns the number of component controls
    *
    *  @return  Number of component controls
    */
    IMPORT_C TInt CountComponentControls() const;
    
    /**
    * From CCoeControl
    *
    * Return a pointer to the component control at the give index.
    *
    *  @return  Pointer to the conponent control. No ownership is transferred
    */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /**
    * From CCoeControl
    *
    * Make the control ready for display.
    */
    IMPORT_C void ActivateL();

    /**
    * From CCoeControl
    *
    * Sets the control whose window is to be used as a container for this control
    *
    *  @param aContainer control
    */
    IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
    
    /**
    * From CCoeControl
    *
    * Called when the focus has changed
    *
    *  @param aDrawNow  Iff not EFalse, then the control is requested to redraw.
    */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    
    /**
    * From CCoeControl
    *
    * CONE framework is requesting that the passed-in key be handled.
    *
    *  @param aKeyEvent     Wserv event type
    *  @param aKeyCode      Key code
    */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/);
    
    /**
    * From CCoeControl
    *
    * Obtain the list of colors to be used by this control
    *
    *  @param aColorUseList
    */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

    /**
    * From CCoeControl
    *
    * This is called when resource or layout or other display-affecting setting has changed.
    * Change the internals of the control so that it is ready for a subsequent SizeChanged call.
    *
    *  @param aType  Type of resource or setting that has changed
    */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
    * From CCoeControl
    *
    * Handle a pointer event that has been routed to this control
    *
    *  @param aPointerEvent   Pointer event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    

public: // but not exported
    /**
    * Access to the command stack
    *
    * @return   pointer to the command stack
    */
    CEikCommandStack* CommandStack() const;
    
    /**
    * Access to the button flags
    * 
    *  @return  The button flag pattern
    */
    TInt ButFlags() const;
    
    /**
    * Access to whether the button is default
    * 
    * @return EFalse iff the button is not default.
    */
    TBool IsDefault() const;

protected: 

    /**
    * From CEikButtonBase
    *
    * Framework method called when the state changes
    */ 
    IMPORT_C void StateChanged();

protected:
    /**
    * Constructor
    */
    IMPORT_C CEikCommandButtonBase();

    /**
    *  Sets the label text for the button.
    * 
    *  @param aText                 The text to set
    *  @param aComponent      The component for which the text is to be set.
    */
    IMPORT_C void SetTextL(const TDesC& aText,CEikAlignedControl*& aComponent);

    /**
    *  Sets the bitmap and optional mask for the button
    * 
    *  @param aMain               The bitmap to use
    *  @param aMask               The mask. If null, then no mask will be used
    *  @param aComponent      The component for which the picture is to be set.
    */
    IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,CEikAlignedControl*& aComponent);

    /**
    * Sets the bitmap and optional mask from an mbm file.
    *
    *  @param aFile                 Mbm filename 
    *  @param aMain               Index of the bitmap to use
    *  @param aMask               Index of the mask. If -1, then a null mask will be used
    *  @param aComponent      The component for which the picture is to be set.
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,CEikAlignedControl*& aComponent);

    /**
    * Utility routine. Calling this without a leave will ensure the internal command stack is constructed.
    */
    inline void CheckCreateCommandStackL();
    
protected: // from CCoeControl
    /**
    * From CCoeControl
    *
    * Request for the control to draw itself within the given rectangle
    *
    * @param aRect TRect to draw
    */
    IMPORT_C void Draw(const TRect& aRect) const;

protected:

    /**
    *  Utility routine. Sets additional look and feel attributes for the image
    */
    void SetImageAttributes(CEikImage* aImage);

    /**
    *  Access the behaviour set into the button
    */
    inline TInt Behavior() const;

protected:
    /**
    * From CCoeControl
    *
    * Serialize the state of the control
    *
    * @param aWriteStream   Output stream for the serialization
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
private:
    /**
    * From CCoeControl
    *
    * Framework method called when the size or layout changes
    */ 
    IMPORT_C void SizeChanged();
    IMPORT_C void Reserved_2();

private: // from CEikButtonBase
    IMPORT_C void Reserved_3();

private: 
    /**
    * From MCoeControlContext
    * 
    * Modify the passed-in graphics context ready for use in this control
    * 
    * @param aGc    Graphics context to set up
    */
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    
private:
    IMPORT_C virtual void Reserved_4();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

// New methods
private:
    void SetComponentExtents(const TRect& aRect);
    void SetNewComponentExtentL();
    TBool LayoutIsVertical() const;
protected:
    TMargins8 iMargins;
    /**
    * The components of the button: the image or the text (order determined by construction)
    */
    CEikAlignedControl* iComponents[2];
    TInt iCmdFlags;
private:
    TInt iDrawOffset;
    /**
    * Owned
    */
    CEikCommandStack* iCommandStack; 
    TInt iDummy;
    TBool iDefault;
    };

/**
 *  Command button with a text and/or an image
 *
 *  This class in S60 does not function without derivation
 *  This class does NOT implement S60 look-and-feel and is not skinned.
 *
 *  @lib eikcoctl.dll
 *  @since S60 1.0
 */
class CEikCommandButton : public CEikCommandButtonBase
	{
public:
    /** Layout options for a command button*/
    enum TLayout
        {
        ETextRightPictureLeft=0x000,
        ETextBottomPictureTop=0x001,
        ETextTopPictureBottom=0x002,
        ETextLeftPictureRight=0x003
        };

    /**
    * Where to put excess space in the layout
    */
    enum TExcess
        {
        EShare		=0x0000,
        EToText		=0x0010,
        EToPicture	=0x0020
        };
    
    /**
    * Content to diplay for this button
    */ 
    enum TDisplayContent
        {
        ETextOnly		=0x0100,
        EPictureOnly	=0x0200,
        ETextAndPicture	=0x0300
        };

public:

    /**
    * Constructor
    */
    IMPORT_C CEikCommandButton();

    /**
    * C++ destructor
    */
    IMPORT_C ~CEikCommandButton();

    /**
    *  Sets the label text for the button.
    * 
    *  @param aText                 The text to set
    */
    IMPORT_C void SetTextL(const TDesC& aText);

    /**
    *  Sets the bitmap and optional mask for the button
    * 
    *  @param aMain               The bitmap to use
    *  @param aMask               The mask. If null, then no mask will be used
    */
    IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL);

    /**
    * Set bitmap and mask from file.
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);

    /**
    * Access the label control that implements the text label of the button.  Ownership is not transferred.
    *
    * @return   A pointer to the CEikLabel control used to implement the text display
    */
    IMPORT_C CEikLabel* Label() const;

    /**
    * Access the CEikImage that implements the picture component of the button.  Ownership is not transferred.
    *
    * @return   A pointer to the CEikImage used to implement the image display.
    */
    IMPORT_C CEikImage* Picture() const;

    /**
    * Set the layout of the button
    *
    * @param aLayout    Layout to be used
    */
    IMPORT_C void SetButtonLayout(TLayout aLayout);

    /**
    * Sets where the excess space in the layout is to be distributed
    *
    * @param aExcess    Enum value to say where the excess space is to go
    */
    IMPORT_C void SetExcessSpace(TExcess aExcess);

    /**
    * Set what content is to be displayed in the button
    *
    * @param aContent   Enum value saying what content to display
    */
    IMPORT_C void SetDisplayContent(TDisplayContent aContent);

    /**
    * Sets the command button's text, bitmap and bitmap mask.
    *
    * @param aCommandId     Command ID to be generated by pressing this button
    * @param aText                 Text to display on the button
    * @param aBitmap             Bitmap to display on the button
    * @param aMask               Mask to use. May be Null
    */	
    IMPORT_C void SetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

    /**
    * Push a command ID + text + image binding onto the command stack.
    * 
    * @param aCommandId     Command ID to be generated by pressing this button
    * @param aText                 Text to display on the button
    * @param aBitmap             Bitmap to display on the button
    * @param aMask               Mask to use. May be Null
    */
    IMPORT_C void AddCommandToStackL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

    /**
    * Find the stacked command with a given command ID and remove it from the stack
    *
    * @param aCommandId      ID of the command to be removed
    * @return                           EFalse iff the comand is not found
    */
    IMPORT_C TBool RemoveCommandFromStack(TInt aCommandId);

    /**
    * Remove the top (most recently added) command binding from the command stack
    * 
    * @return the number of commands left on the stack.
    */
    IMPORT_C TInt PopCommandFromStack();

public: // from CCoeControl
    /**
    * From CCoeControl
    *
    * Construct the object from resource
    * 
    * @param aReader  Fully constructed resource reader
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
     IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

public:
    /**
    * From CEikCommandButtonBase
    *
    * Cause a recalculation of the components alignment
    */
    IMPORT_C void UpdateComponentAlignment();

private:
    void UpdateLabelReserveLengthL(const TDesC* aText);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    TInt iDummy;
    };

/**
 * The CEikTwoPictureCommandButton class is a command button which can hold two pictures as
 * well as label text. If a second picture is set for the button it is shown when the button
 * is pressed.
 *
 * @lib     eikcoctl.dll
 * @since S60 1.0
 */
class CEikTwoPictureCommandButton : public CEikCommandButtonBase
    {
public:

    /**
    * Layout options for the Two Picture botton
    */
    enum TLayout
        {
        ETextRightPictureLeft=0x000,
        ETextBottomPictureTop=0x001,
        ETextTopPictureBottom=0x002,
        ETextLeftPictureRight=0x003
        };

    /**
    * Where to put the excess space when laying out the bitmaps or text
    */
    enum TExcess
        {
        EShare		=0x0000,
        EToText		=0x0010,
        EToPicture	=0x0020
        };

    /**
    * Content to display for the text
    */
    enum TDisplayContent
        {
        ETextOnly		=0x0100,
        EPictureOnly	=0x0200,
        ETextAndPicture	=0x0300
        };

private:
    /**
    * Options for the type of button
    */
    enum TPictureButtonType
        {
        EPictureButWithBorders		=0x0000,
        EPictureButWithoutBorders	=0x1000
        };
        
    /**
    * Sets the ownership of the pictures bitmap and mask objects. If owned externally, then no copy is made of the objects
    * in the setter functions.  It must be, in this case, ensured by the client that that the button is destroyed before
    * deleting the externally-owned objects.
    */
    enum TExternalPicture
        {
        EPictureNotOwnedExternally	=0x00,
        EPictureOwnedExternally		=0x01
        };
        
    public:

    /**
    * Two picture command button constructor
    */
    IMPORT_C CEikTwoPictureCommandButton();

    /**
    * Two picture command button C++ destructor
    */
    IMPORT_C ~CEikTwoPictureCommandButton();

    /**
    * Accesses ownership of the second picture' bitmap and mask (if present)
    *
    * @return EFalse iff and if the second picture is not owned externally
    */
    IMPORT_C TBool IsSecondPictureOwnedExternally();

    /**
    * Access the picture image.
    *
    * @return   The picture as a CEikImage. No ownership transferred.
    */
    IMPORT_C CEikImage* Picture() const;

    /**
    * Constructs the two images from resource
    *
    * @param aReader    Constructed resource reader.
    * @param aWhich     Which picture to be constructing
    */
    IMPORT_C void ConstructImagesFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);

    /**
    * Sets the label text on the button
    *
    * @param aText  The text to set
    */
    IMPORT_C void SetTextL(const TDesC& aText);

    /**
    *  Sets the bitmap and optional mask for the button's two pictures. Optionally, only the first button's
    *  picture may be set up.
    * 
    *  @param aMain               The bitmap to use for the first picture
    *  @param aMask               The mask. If null, then no mask will be used
    *  @param aSecondMain     The bitmap to use for the second picture
    *  @param aSecondMask     The mask. If null, then no mask will be used
    */
    IMPORT_C void SetTwoPicturesL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,const CFbsBitmap* aSecondMain=NULL, const CFbsBitmap* aSecondMask=NULL);

    /**
    *  Sets the bitmap and optional mask for the button's second picture
    * 
    *  @param aMain               The bitmap to use
    *  @param aMask               The mask. If null, then no mask will be used
    */
    IMPORT_C void SetSecondPicture(const CFbsBitmap* aSecondMain, const CFbsBitmap* aSecondMask=NULL);

    /**
    * Sets the bitmap and optional mask for the first picture from an mbm file.
    *
    *  @param aFile                 Mbm filename 
    *  @param aMain               Index of the bitmap to use
    *  @param aMask               Index of the mask. If -1, then a null mask will be used
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);

    /**
    * Sets the bitmap and optional mask for the second picture from an mbm file.
    *
    *  @param aFile                 Mbm filename 
    *  @param aMain               Index of the bitmap to use
    *  @param aMask               Index of the mask. If -1, then a null mask will be used
    */
    IMPORT_C void SetSecondPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);

    /**
    * Sets the ownership of the second picture object
    *
    * @param aOwnership     Set to EFalse if bitmaps associated with the object are owned by the button
    */
    IMPORT_C void SetSecondPictureOwnedExternally(TBool aOwnership);

public: // from CCoeControl. 

    /**
    * From CCoeControl
    *
    * @param aReader    Fully constructed resource reader
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * From CCoeControl
    *
    * Make the control ready for display
    */
    IMPORT_C void ActivateL();

    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
    
protected: 
    /**
    * From CCoeControl
    *
    * Serialize the state of the control
    *
    * @param aWriteStream   Output stream for the serialization
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: // from CCoeControl

    /**
    * From CCoeControl
    *
    * Request for the control to draw itself within the given rectangle
    *
    * @param aRect TRect to draw
    */
    IMPORT_C void Draw(const TRect& /*aRect*/) const;

    /**
    * From CEikButtonBase
    *
    * Framework method called when the state changes
    */ 
    IMPORT_C void StateChanged();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    /**
    * From MCoeControlContext
    * 
    * Modify the passed-in graphics context ready for use in this control
    * 
    * @param aGc    Graphics context to set up
    */
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;

private:
    void SwapPictures(CEikImage* aImage);

private:
    /**
    * Ownership dependent on state of flags
    */
    const CFbsBitmap* iSecondBitmap;
    /**
    * Ownership dependent on state of flags
    */
    const CFbsBitmap* iSecondMaskBitmap;
    TInt iPictureFlags;
    TInt iDummy;
    };

/**
 * The CEikInverterCommandButton class is a command button which swaps the foreground and background
 * colors used to draw the button contents when the button is pressed.
 *
 * @since S60 1.0
 */
class CEikInverterCommandButton : public CEikCommandButton
	{
public:

    /**
    * Constructor
    */
    IMPORT_C CEikInverterCommandButton();

    /**
    * C++ destructor
    */
    IMPORT_C ~CEikInverterCommandButton();
    
public: // From CCoeControl

    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
    
protected:

    /**
    * From CCoeControl
    *
    * Serialize the state of the control
    *
    * @param aWriteStream   Output stream for the serialization
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
private:
    /**
    * From MCoeControlContext
    * 
    * Modify the passed-in graphics context ready for use in this control
    * 
    * @param aGc    Graphics context to set up
    */
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    TInt iFlag; 
    TInt iDummy;
    };

/**
 * A command button with a text label
 * 
 * This specialization of CEikCommandButtonBase supports a single text label.
 *
 *  @lib eikcoctl.dll
 *  @since S60 1.0
 */
class CEikTextButton : public CEikCommandButtonBase
    {
public:

    /**
    * Constructor
    */
    IMPORT_C CEikTextButton();

    /**
    * C++ destructor
    */
    IMPORT_C ~CEikTextButton();

    /**
    *  Sets the label text for the button.
    * 
    *  @param aText             The text to set
    *  @param aWhich          The component for which the text is to be set.
    */
    IMPORT_C void SetTextL(const TDesC& aText,TWhichComponent aWhich=EFirst);

    /**
    * Access the label control that implements the text label of the button.  Ownership is not transferred.
    *
    * @return   A pointer to the CEikLabel control used to implement the text display
    */
    IMPORT_C CEikLabel* Label(TWhichComponent aWhich=EFirst) const;

// from CCoeControl
public: 

    /**
    * From CCoeControl
    *
    * Construct the object from resource
    * 
    * @param aReader  Fully constructed resource reader
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

// From CAknControl
private:
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // data
    TInt iDummy;
    };

/**
 * A command button with a single bitmap
 * 
 * This specialization of CEikCommandButtonBase supports a single bitmap, optionally with a mask.
 *
 *  @lib eikcoctl.dll
 *  @since S60 1.0
 */
class CEikBitmapButton : public CEikCommandButtonBase
    {
public:

    /**
    * Constructor
    */
    IMPORT_C CEikBitmapButton();

    /**
    * C++ Destructor
    */
    IMPORT_C ~CEikBitmapButton();

    /**
    *  Sets the bitmap and optional mask for the button
    * 
    *  @param aMain               The bitmap to use
    *  @param aMask               The mask. If null, then no mask will be used
    *  @param aWhich             The component for which the picture is to be set.
    */
    IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,TWhichComponent aWhich=EFirst);

    /**
    * Sets the bitmap and optional mask from an mbm file.
    *
    *  @param aFile                 Mbm filename 
    *  @param aMain               Index of the bitmap to use
    *  @param aMask               Index of the mask. If -1, then a null mask will be used
    *  @param aWhich             The component for which the picture is to be set.
    */
   IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1,TWhichComponent aWhich=EFirst);

    /**
    * Access to the image
    *
    * @param aWhich     Which picture to access
    * @return                 pointer to the image.  No ownership is transferred
    */
    IMPORT_C CEikImage* Picture(TWhichComponent aWhich=EFirst) const;

// from CCoeControl
public: 
    /**
    * From CCoeControl
    *
    * Construct the object from resource
    * 
    * @param aReader  Fully constructed resource reader
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private: // data
    TInt iDummy;
    };

#endif // __EIKCMBUT_H__
