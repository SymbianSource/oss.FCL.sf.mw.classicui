/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content for stylus activated pop-up.
*
*/


#ifndef CAKNSTYLUSACTIVATEDPOPUPCONTENT_H
#define CAKNSTYLUSACTIVATEDPOPUPCONTENT_H

#include <AknControl.h>

class MEikCommandObserver; 
class CEikLabel;
class CAknTextControl;
class CAknStylusActivatedItem; 

typedef struct
    {
    TDesC* iLinkText; // note: owned by user
    TInt iLinkId;
    TAny* iAny; // Do not use
    } TAknContentLink;



/**
*  Class defining stylus activated pop-up content.
*  
*  This content is intended to be used in connection with preview pop-up
*  component. Content shows a title text, informative text and
*  an optional stylus tappable function link(s). The number of links can
*  variate from 0 to 2. If using links, the user gives link text and
*  corresponding ID for each link in construction. The user must also set
*  itself as an observer for this content when using function links. This
*  way the user gets callbacks (with ID) for its ProcessCommandL() function
*  when the link is tapped.  
*
*  @lib avkon.lib
*  @since S60 v5.0
*/
NONSHARABLE_CLASS( CAknStylusActivatedPopUpContent ) :
    public CAknControl,
    public MCoeControlObserver
    {
public:

    /**
     * Two-phased constructor. Constructs the content
     * with title text and informative text.
     *
     * @param aTitleText The title text for the popup, mandatory.
     * @param aText Descriptive text for the popup.
     * @return Pointer to the created content object.
     */
    IMPORT_C static CAknStylusActivatedPopUpContent* NewL(
                           const TDesC& aTitleText,
                           const TDesC& aText );

    /**
     * Two-phased constructor. Constructs the content
     * with title text, text and function link(s).
     * The number of links can be from 0 to 2.
     *
     * @param aTitleText The title text for the popup, mandatory.
     * @param aText Descriptive text for the popup. Either this or aLinkArray
     *              is mandatory.
     * @param aLinkArray Function link texts and ids. Either this or aText
     *              is mandatory.
     * @return Pointer to the created content object.
     */
    IMPORT_C static CAknStylusActivatedPopUpContent* NewL(
                           const TDesC& aTitleText,
                           const TDesC& aText,
                           const RArray<TAknContentLink>& aLinkArray );

    /**
     * Two-phased constructor. Constructs the content from resources.
     *
     * @param aReader The resource reader with which to access
     *                control's resource values.
     * @return Pointer to the created content object.
     */
    IMPORT_C static CAknStylusActivatedPopUpContent* NewL(
                           TResourceReader& aReader );

    /**
     * Two-phased constructor. Constructs the content from resources.
     *
     * @param aResourceId The ID for this component's resources.
     * @return Pointer to the created content object.
     */
    IMPORT_C static CAknStylusActivatedPopUpContent* NewL(
                           const TInt aResourceId );

    /**
     * Destructor.
     */
    ~CAknStylusActivatedPopUpContent();
    
     /**
      * Constructs controls from a resource file.
      *
      * @param aResourceId The ID for this component's resource.
      */
    IMPORT_C void ConstructFromResourceL( const TInt aResourceId );
    
    /**
     * Sets the command observer of the preview pop-up content. When
     * links that are set to the content are pressed, the command
     * observer's ProcessCommandL() method is called with the command ID
     * of the pressed component.
     *
     * @param aCommandObserver Command observer.
     */
    IMPORT_C void SetCommandObserver( MEikCommandObserver& aCommandObserver );
    
// from base class CCoeControl
    
    /**
     * Constructs controls from a resource file.
     *
     * @param aReader The resource reader, with which to access the 
     *                control's resource values.
     */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    
	/**
	 * Handles a change to the control's resources of type aType which are
	 * shared across the environment.
	 *
	 * @param aType The type of resource that have changed.
	 */
	IMPORT_C void HandleResourceChange( TInt aType );
	
    /**
     * Sets container window.
     *
     * @param aContainer Container.
     */
    IMPORT_C void SetContainerWindowL( const CCoeControl& aContainer );

    /**
     * Handles pointer events
     *
     * @param aPointerEvent information about the pointer event.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );


// from base class MCoeControlObserver
    
    /**
     * Handles an event from an observed control.
     *
     * @param aControl The control that sent the event.
     * @param aEventType The event type.
     */
    IMPORT_C void HandleControlEventL( CCoeControl *aControl,
                                       TCoeEvent aEventType ); 

private:

    /**
     * Default constructor.
     */
    CAknStylusActivatedPopUpContent();

    /**
     * Symbian 2nd phase constructor.
     *
     * @param aTitleText The title text for the popup.
     * @param aText Descriptive text for the popup.
     */
    void ConstructL( const TDesC& aTitleText, const TDesC& aText );

    /**
     * Symbian 2nd phase constructor.
     *
     * @param aTitleText The title text for the popup.
     * @param aText Descriptive text for the popup.
     * @param aLinkArray Function link texts and id's.
     */
    void ConstructL( const TDesC& aTitleText,
                     const TDesC& aText, 
                     const RArray<TAknContentLink>& aLinkArray );

    /**
     * Gets rect from layout data.
     *
     * @param aParent Parent rect.
     * @param aComponentLayout Layout data.
     */
    TRect RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const;

    /**
     * Gets rect from layout data.
     *
     * @param aComponentLayout Layout data.
     */
    TRect PopUpWindowRectFromLayout( const TAknWindowComponentLayout&
        aComponentLayout ) const;

    /**
     * Gets rect from layout data so that it is aligned to this control's
     * borders.
     *
     * @param aComponentLayout Layout data.
     */
    TRect AlignedRectFromLayout( const TAknWindowComponentLayout&
        aComponentLayout ) const;

    /**
     * Resolves the correct variety for popup_touch_info_window.
     *
     * @param aNbrOfLines Number of lines in pop-up. Goes hand in hand with
     *                    variety.
     */
    TInt GetVariety( const TInt aNbrOfLines );

// from base class CCoeControl

    /**
     * Returns a control determined by control index.
     *
     * @param aIndex Index of a control to be returned.
     * @return Pointer to control.
     */
    IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * Returns the number of controls inside the control.
     *
     * @return The number of component controls.
     */
    IMPORT_C TInt CountComponentControls() const;
    
    /**
     * Draws the control.
     *
     * @param aRect The control's area.
     */
    IMPORT_C void Draw( const TRect& aRect ) const;

    /**
     * Returns the control's minimum required size.
     *
     * @return The minimum size required by the control.
     */
    IMPORT_C TSize MinimumSize();

    /**
     * Responds to size changes to set the size and position for 
     * the contents of this control.
     */
    IMPORT_C void SizeChanged();

private: // data
        
    /**
     * Label for title text.
     * Own.
     */
    CEikLabel* iTitleText;
    
    /**
     * Label for informative text.
     * Own.
     */
    CAknTextControl* iText;

    /**
     * Command observer.
     * Not own.
     */
    MEikCommandObserver* iCommandObserver;
    
    /**
     * Array for link items
     */
    RPointerArray<CAknStylusActivatedItem> iLinkArray;
    
    /**
     * Font
     * Not own
     */
    const CFont* iFont;
    
    /**
     * Index of highlighted item.  
     */
    TInt iHighlightedItem; 
    };
    
    
#endif // CAKNSTYLUSACTIVATEDPOPUPCONTENT_H

