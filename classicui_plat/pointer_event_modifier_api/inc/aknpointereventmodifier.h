/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon pointer event modifier
*
*/


#ifndef AKNPOINTEREVENTMODIFIER_H
#define AKNPOINTEREVENTMODIFIER_H

#include <e32base.h>

class CCoeControl;
struct TPointerEvent;

/**
 *  Utility class used to redirect pointer events.
 *  This class can be used to redirect pointer down events targeted to one
 *  control to another control. Its designed use cases are situations where
 *  a control needs to get pointer events from area larger than its own but
 *  pointer capture is not usable.
 *
 *  @lib avkon
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknPointerEventModifier ) : public CBase
    {
public:
    /**
     * Two-phased constructor.
     */
    static CAknPointerEventModifier* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CAknPointerEventModifier();

    /**
     * Adds a control to the modifier stack. Note that this control must
     * return a valid window-owning parent via @c CCoeControl::Parent or this
     * method will fail silently. Calling this method invalidates the stack.
     * Multiple calls to this method with already stacked control have no
     * effect. Note that client must also pop every control it pushes to the
     * stack!
     *
     * @since S60 v5.0
     * @param aControl - Control to be added to the modifier stack.
     * @param aRect    - Rectangle that is used to determine control's extension
     *                   area. Its coordinates are relative to the control i.e.
     *                   the point 0, 0 corresponds to control's top left corner.
     */
    IMPORT_C void Push( CCoeControl& aControl, const TRect& aRect );

    /**
     * Removes a control from the modifier stack. This also causes the stack
     * to be invalidated.
     *
     * @since S60 v5.0
     * @param aControl - Control to be removed from the modifier stack.
     */
    IMPORT_C void Pop( const CCoeControl& aControl );

    /**
     * Updates already stacked control's extension area. If the control is not
     * found in the stack then nothing happens.
     *
     * @since S60 v5.0
     * @param aControl - Control whose extension area is changed.
     * @param aRect    - Control's new extension area.
     */
    IMPORT_C void Update( const CCoeControl& aControl, const TRect& aRect );

    /**
     * Tests if the given pointer event should be forwarded to some control
     * in the modifier stack. If such a condition is found then either the
     * pointer event, destination control or both will be modified so that
     * pointer event is redirected to correct target control.
     *
     * @since S60 v5.0
     * @param aEvent       - Original pointer event. Its coordinates might be
                             modified by this method.
     * @param aDestination - Pointer event's original target control. This might
     *                       be modified by this method.
     */
     IMPORT_C void HandlePointerEvent( TPointerEvent& aEvent, CCoeControl*& aDestination );
     
    /**
     * Invalidates the modifier stack. As a result it will be re-ordered on 
     * next pointer down event.
     *
     * @since S60 v5.0
     */
     void Invalidate();
     
private:
    struct TStackItem
        {
        CCoeControl* iControl;
        CCoeControl* iParent;
        TRect iExtensionArea;
        };
        
    /**
     * Constructor.
     */
    CAknPointerEventModifier();
    
    /**
     * Checks if an item is already in the stack.
     *
     * @since S60 v5.0
     * @param aControl - Control whose existence is to be checked.
     * @return ETrue if the control is already in the stack, otherwise EFalse.
     */
    TBool ControlIsInStack( const CCoeControl& aControl );

    /**
     * Modifies either pointer event, destination control or both if the event
     * is in @c aItem's extension area.
     *
     * @since S60 v5.0
     * @param aItem        - Stacked control whose extension area the event is
     *                       tested against.
     * @param aEvent       - Pointer event.
     * @param aDestination - Pointer event's destination control.
     * @return ETrue if event or destination control were modified, otherwise EFalse.
     */
    TBool ModifyEvent( TStackItem& aItem, TPointerEvent& aEvent, CCoeControl*& aDestination );

    /**
     * Compares two stacked items. Used to order the stack.
     *
     * @since S60 v5.0
     * @param aFirst  - First item to compare.
     * @param aSecond - Second item to compare.
     * @return Some of the return values expected by @c RArray.
     */
    static TInt Compare( const TStackItem& aFirst, const TStackItem& aSecond );

private: // data
    /**
     * true if the stack is valid
     */
    TBool iIsValid;

    /**
     * control stack
     */
    RArray<TStackItem> iStack;
    };

#endif // AKNPOINTEREVENTMODIFIER_H
