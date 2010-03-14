/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Status pane's combined subpane component.
*
*/

#ifndef C_AKNCOMBINEDPANE_H
#define C_AKNCOMBINEDPANE_H

#include <aknbutton.h>

class CEikStatusPaneBase;

/**
 *  Combined status pane subpane for binding multiple subpanes under single
 *  window. This enables e.g. common pointer event handling between associated
 *  subpanes.
 *  
 *  Combined pane is currently used for combining the universal indicator pane
 *  and small digital clock pane as one subpane in the landscape status pane
 *  layout with bottom softkeys.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknCombinedPane ) : public CAknButton
    {
public: // Constructors

    /**
     * Two-phased constructor.
     */
    static CAknCombinedPane* NewL();

    /**
     * Destructor.
     */
    ~CAknCombinedPane();

protected: // From base class CCoeControl

    /**
     * Returns number of controls inside this control.
     * 
     * The container controls (@c CEikStatusPaneContainer) of the combined
     * subpanes are component controls of combined pane. 
     *
     * @return Number of component controls.
     */
    TInt CountComponentControls() const;

    /**
     * Returns a control determined by control index.
     *
     * @param aIndex Index of a control to be returned.
     *
     * @return Pointer to control.
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * Handles a change to the control's resources.
     *
     * @param  aType  Resource change type.
     */
    void HandleResourceChange( TInt aType );

protected: // From base class CAknButton

    /**
     * Constructs the control from a resource file.
     *
     * @param aReader Resource reader.
     */
    void ConstructFromResourceL( TResourceReader& aReader );

    /**
     * Handles pointer events inside the control.
     *
     * @param aPointerEvent The pointer event to be handled.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // Private constructors

    /**
     * Default C++ constructor.
     */
    CAknCombinedPane();

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();
    
private: // New methods

    /**
     * Sets the pressed down state of the subpanes.
     * 
     * @param  aPressedDown  @c ETrue to set the subpane pressed down,
     *                       @c EFalse otherwise.
     */
    void SetSubPanesPressedDown( TBool aPressedDown );

private: // data

    /**
     * Subpane information.
     */
    struct TSubPaneData
        {
        TUint iUid;         ///< UID of the subpane (defined in @c avkon.hrh).
        TBool iPressedDown; ///< Whether or not currently pressed down.
        };

    /**
     * Holds information about embedded subpanes.
     */
    RArray<TSubPaneData> iSubPanes;

    /**
     * Pointer to the status pane.
     * Not own.
     */
    CEikStatusPaneBase* iStatusPane;
    
    /**
     * Whether or not the pointer down event has been received in the
     * combined pane area.
     */
    TBool iPointerDownInCombinedArea;
    
    /**
     * Amount of pixels that a subpane control is shifted right and bottom
     * for the pressed down effect.
     */
    TInt iPressedDownDelta;
    };

#endif // C_AKNCOMBINEDPANE_H
