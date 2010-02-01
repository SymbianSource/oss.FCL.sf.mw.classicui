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
* Description:  CAknListLoader is used to load the APIs needed for listbox effects
*
*/


#ifndef AKNLISTLOADERTFX_H
#define AKNLISTLOADERTFX_H

#include <w32std.h>
#include <coemain.h>
#include <aknlistboxtfxinternal.h>

class MAknListBoxTfx;
class MAknListBoxTfxPlugin;
class CEikListBox;
class CEikMenuPane;
class CAknTreeList;
class CCoeControl;

/**
 * CAknListLoader is a CCoeStatic class with only
 * static functions. When the static functions are used
 * CAknListLoader tries to find the singleton using CCoeEnv::Static().
 *
 * If the singleton is not yet created when calling CreateTfxGc this function
 * will create the singleton and try to load the ECOM plugin that implements the
 * MAknListBoxTfxPlugin API. This ECOM plugin instance is then used by static functions.
 *
 * @since S60 v3.2
 */
class CAknListLoader: public CCoeStatic
    {
public:

    ~CAknListLoader();

    /**
    * Used to get the instance of MAknListBoxTfx that belongs to the CWindowGc aGc.
    * If aGc is a CTfxGc this function will return the MAknListBoxTfx instance,
    * otherwise it will return NULL
    *
     * @since S60 3.2
     * @param aGc the gc for which the MAknListBoxTfx instance should be retrieved
     * @return A MAknListBoxTfx instance or NULL if it can't be found
     */
    IMPORT_C static MAknListBoxTfx* TfxApi( CWindowGc* aGc );

    /**
    * Used to get the instance of MAknListBoxTfxInternal that belongs to the CWindowGc aGc.
    * If aGc is a CTfxGc this function will return the MAknListBoxTfxInternal instance,
    * otherwise it will return NULL
    *
     * @since S60 3.2
     * @param aGc the gc for which the MAknListBoxTfxInternal instance should be retrieved
     * @return A MAknListBoxTfxInternal instance or NULL if it can't be found
     */
    IMPORT_C static MAknListBoxTfxInternal* TfxApiInternal( CWindowGc* aGc );

    /**
    * If the singleton instance of CAknListLoader is not already created this function
    * will try to create it, it will then try to load an ECOM implementation of the
    * MAknListBoxTfxPlugin API. The singleton will own the ECOM instance.
    * The function used the ECOM instance to create a CTfxGc.
    *
     * @since S60 3.2
     * @param aListBox The ListBox for which the gc that is returned should
                       be used.
     * @return A CTfxGc is it is successfully created, otherwise it returns
               the aListBox gc.
     */
    IMPORT_C static CWindowGc* CreateTfxGc( CEikListBox& aListBox );

    /**
    * If the singleton instance of CAknListLoader is not already created this function
    * will try to create it, it will then try to load an ECOM implementation of the
    * MAknListBoxTfxPlugin API. The singleton will own the ECOM instance.
    * The function used the ECOM instance to create a CTfxGc.
    *
     * @since S60 3.2
     * @param aMenuPane The menupane for which the gc that is returned should be used.
     * @param aTopIndex A value containing the top item index.
     * @param aItemsThatFitInView A value containing number of items that fit
     *                            in view.
     * @param aScrollBarRect A rectangle describing the position and size of
     *                       the scrollbar.
     * @return A CTfxGc is it is successfully created, otherwise it returns
               NULL.
     */
    IMPORT_C static CWindowGc* CreateTfxGc( CEikMenuPane& aMenuPane,
                                            TInt& aTopIndex,
                                            TInt& aItemsThatFitInView );

    /**
     * Create a transition graphics context.
     *
     * @param aTreeList The treelist to animate.
     * @param aTopIndex A value containing the top item index.
     * @param aItemsThatFitInView A value containing number of items that fit
     *                            in view.
     *
     * @return A graphics context for listbox effects.  On error,
     *         the listbox' regular CWindowGc will be returned instead,
     *         which means the listbox will be rendered in the regular way,
     *         without animations.
     */
    IMPORT_C static CWindowGc* CreateTfxGc( CAknTreeList& aTreeList,
                                            TInt& aTopIndex,
                                            TInt& aBottomIndex,
                                            TInt& aHighlightIndex,
                                            TInt& aRows );

    /**
     * Create a transition graphics context.
     *
     * @param aAdapter The adapter to animate.
     *
     * @return A graphics context for listbox effects. On error,
     *         the adapter regular CWindowGc will be returned instead,
     *         which means the adapter will be rendered in the regular way,
     *         without animations.
     */
    IMPORT_C static CWindowGc* CreateTfxGc( CCoeControl& aAdapter );

    /**
    * Removes the CWindowGc from the list of TfxGc:s.
    *
    * This function is called when a CTfxGc is deleted, and should not be called from anywere else.
    *
     * @since S60 3.2
     * @param aGc The gc to be removed.
     */
    IMPORT_C static void RemoveTfxGc ( CWindowGc* aGc );

    /**
     * Invalidates all images in all lists.
     */
     IMPORT_C static void InvalidateAll();

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
    IMPORT_C static TInt LongTap( MAknListBoxTfxInternal::TLongTapEvent aEvent,
                                  TInt aDuration = 0,
                                  const TPoint* aPoint = NULL );
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2

private:
    static CAknListLoader *Static();
    CAknListLoader();
private: //data
    MAknListBoxTfxPlugin *iListBoxPlugin;
    TUid iListBoxPluginEComDtorUID;
    RPointerArray<CWindowGc> iGcArray;
    };

#endif // AKNLISTLOADERTFX_H
