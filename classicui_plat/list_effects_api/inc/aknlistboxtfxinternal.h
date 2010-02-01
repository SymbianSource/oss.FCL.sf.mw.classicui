/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This is the API used by listbox implementations
                 in order to enable listbox effects
*
*/


#ifndef AKNLISTBOXTFXINTERNAL_H
#define AKNLISTBOXTFXINTERNAL_H

/**
 * API used by the classes that implements the different
 * types of listboxes. The API can be used to enable listbox effects.
 *
 */
class MAknListBoxTfxInternal
    {
public:
    /**
     * The type of a listbox participant: view, highlight or list item.
     */
    enum TParticipantType
    {
        /**
         * View (background) of the list.
         */
        EListView,

        /**
         * List items, ie. the entries in the list.
         */
        EListItem,

        /**
         * Highlight.
         */
        EListHighlight,

        /**
         * Zoomed text box.
         */
        EListZoomText,

        /**
         * Can be used in Remove to remove all participants.
         */
        EListEverything = 100,

        EListNotSpecified,

        EListUpdateRect,
        
        EListTLMargin,
        
        EListBRMargin,
	
	EHighlightParticipant
    };

    /**
     * The type of movement in a listbox.
     */
    enum TMovementType
    {
        EListNoMovement = 0,
        EListScrollDown,
        EListScrollUp,
        EListWrapDown, // Standing at top and going to the bottom element
        EListWrapUp,// Standing at the bottom  and going to the top element
        EListMoveDown,
        EListMoveUp,
        EListWrapLeft,
        EListWrapRight,
        EListMoveLeft,
        EListMoveRight,
        EListStartUnknownMove,
        EListStopUnknownMove,
        EListContinueMove,
        EListTap,
        EListFastScroll,
        EListHitBorder,
        EListDrag
    };

    /**
     * Types of lists.
     */
    enum TListBoxType
    {
        /**
         * All regular main pane lists, as well as settings lists.
         */
        EListBoxTypeMainPane = 0,

        /**
         * Grids.
         */
        EListBoxTypeGrid,

        /**
         * Lists in setting pages.
         */
        EListBoxTypeSettingPage,

        /**
         * Lists in popups.
         */
        EListBoxTypePopup,

        /**
         * Options menu.
         */
        EListBoxTypeMenuPane,
        
        /**
        * Tree List
        */
        EListBoxTypeTreeList,

        EListBoxTypeIdle
    };

    enum TLongTapEvent
        {
        ELongTapStart,
        ELongTapFinish,
        ELongTapAbort
        };

    /**
     * Begin redrawing a listbox participant bitmap.
     * It's important that EndRedraw is called when the redraw is finished.
     * If more than one BeginRedraw is called, it is only the first that has any
     * effect, but EndRedraw must be called as many times as EndRedraw.
     *
     * @param aType The type of the list participant to be drawn.
     * @param aRect The participant's rect.
     * @param aId The index of the item.
     *
     * @return ETrue if the participant needs drawing, EFalse otherwise.
     */
     virtual TBool BeginRedraw( TParticipantType aType,
                          const TRect& aRect, TInt aId = 0 ) = 0;

    /**
     * End redrawing a listbox participant bitmap.
     *
     * @param aType The type of the list participant that was drawn.
     * @param aId The index of the item.
     */
    virtual void EndRedraw( TParticipantType aType, TInt aId = 0 ) = 0;

    /**
     * End redrawing a listbox view participant bitmap.
     *
     * @param aRect Clipping rectangle (The area that can be drawn).
     */
    virtual void EndViewRedraw( const TRect& aRect ) = 0;

    /**
     * Start actual drawing to the listbox participant. This should be called between
     * BeginRedraw and EndRedraw. Everything that is drawn to the listbox gc must
     * be drawn between StartDrawing and StopDrawing, otherwise effects are disabled.
     *
     * @param aType The type of the list participant to be drawn.
     *
     * @return ETrue if the participant needs drawing, EFalse otherwise.
     */
    virtual TBool StartDrawing( TParticipantType aType ) = 0;

    /**
     * Stop actual drawing to the listbox participant. This should be called between
     * BeginRedraw and EndRedraw. Everything that is drawn to the listbox gc must
     * be drawn between StartDrawing and StopDrawing, otherwise effects are disabled.
     */
    virtual void StopDrawing() = 0;

    /**
     * Tell the listbox to jump to state after a special participant has been drawn.
     *
     * @param aType The type of the list participant that triggers the jump.
     */
    virtual void JumpToStateAfter( TParticipantType aType ) = 0;

    /**
     * Remove the following participant bitmap.
     *
     * @param aType The type of the list participant to remove, ie. item,
     *              highlight, background, or zoomtext.
     * @param aId The index of the item, only used for list items.
     */
    virtual void Remove( TParticipantType aType, TInt aId = 0 ) = 0;

    /**
     * Draw the listbox.
     *
     * @param aRect The rect to draw.
     */
    virtual void Draw( const TRect& aRect ) = 0;

    /**
     * Set the type of the current movement.
     *
     * @param aMoveType The type of the current movement.
     */
    virtual void SetMoveType( MAknListBoxTfxInternal::TMovementType aMoveType ) = 0;

    /**
     * Sets the focus of the listbox.  Should be called when it gains or
     * loses focus.
     *
     * @param aInFocus ETrue if the listbox has focus, EFalse if not.
     */
    virtual void HandleFocusChange( TBool aInFocus ) = 0;

    /**
     * Check if a certain listbox participant needs to be redrawn.
     *
     * @param aType The type of the participant (highlight, background or
     *        item).
     * @param The index of the participant (0 for highlight or background).
     * @param The participant's rect.
     *
     * @return ETrue if the participant needs to be redrawn, otherwise EFalse.
     */
    virtual TBool NeedsUpdate( TParticipantType aType, TUint32 aIndex,
                                const TRect& aRect ) = 0;

    /**
     * Set window gc.
     *
     * @param aGc The new gc that shall be used.
     */
    virtual void SetGc( CWindowGc& aGc ) = 0;

    /**
     * Is effects disabled.
     *
     * @return True if effects are disabled, otherwise false.
     */
    virtual TBool EffectsDisabled() const = 0;

    /**
     * Set the type of listbox.
     *
     * @param aListBoxType The type of the listbox.
     */
    virtual void SetListType( TListBoxType aListBoxType ) = 0;

    /**
     * Add an area that won't be drawn to.
     *
     * @param The area that won't be drawn to.
     */
    virtual void AddNonDrawingRect( const TRect& aRect ) = 0;

    /**
     * Reset areas that won't be drawn to.
     */
    virtual void ResetNonDrawingRects() = 0;

    /**
     * Verify that the server is running and KML is available.
     *
     * @return KErrNone if the server is running and KML are available.
     */
    virtual TInt VerifyKml() const = 0;

    /**
     * Change position of a participant without redrawing it.
     *
     * @return KErrNone If the participant exists.
     *        KErrNotFound If the participant did not exist.
     */
    virtual TInt SetPosition( TParticipantType aType,
                              const TPoint& aPoint, TInt aId = 0 ) = 0;

    /**
     * Invalidate a participant, forces the image to be updated next time it
     * is drawn.
     *
     * @param aType The type of the participant (highlight, background or
     *        item).
     * @param The index of the participant (0 for highlight or background).
     */
    virtual void Invalidate( TParticipantType aType, TInt aId = 0 ) = 0;

    /**
     * Checks if a participant exists.
     *
     * @param aType The type of the participant (highlight, background or
     *        item).
     * @param The index of the participant (0 for highlight or background).
     *
     * @return ETrue if the participant exist.
     *         EFalse if the participant does not exist.
     */
    virtual TBool Exist( TParticipantType aType, TInt aId = 0 ) const = 0;

#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
    /**
     * Supplies long tap information.
     *
     * @since S60 5.0
     * @param aEvent EStart, EFinish, or EAbort
     * @param aDuration The total duration until long tap menu is showing
     *                  ( used if aRun == ETrue )
     * @param aPoint The point that is clicked
     *               ( used if aRun == ETrue )
     * @return KErrNone if all went fine, otherwise KErrNotReady
     */
    virtual TInt LongTap( TLongTapEvent aEvent, TInt aDuration,
                          const TPoint* aPoint) = 0;
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
    };
#endif // AKNLISTBOXTFXINTERNAL_H
