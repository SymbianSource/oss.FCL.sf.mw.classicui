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
* Description:  This is the API used by Theme server to control the
*                appearence of transitions.
*
*/


#ifndef AKNLISTBOXTFXPLUGIN_H
#define AKNLISTBOXTFXPLUGIN_H

class CEikListBox;
class CWindowGc;
class CEikMenuPane;
class CCoeControl;

/**
 * API for ECOM plugins. 
 * The API is used to retrieve the APIs needed for listbox effects
 * as well as for creating the CTfxGc.
 *
 *  @since S60 3.2
 */
class MAknListBoxTfxPlugin
	{
public:
	/**
	 * If aGc is a CTfxGc this function will return the MAknListBoxTfx instance
	 * belonging to this gc otherwise it will return NULL
	 * 
     * @since S60 3.2
     * @param aGc the gc for which the MAknListBoxTfx instance should be retrieved
     * @return A MAknListBoxTfx instance or NULL if it can't be found
     */
	virtual MAknListBoxTfx *AknListBoxTfx(CWindowGc *aGc) = 0;
	
	/**
	 * If aGc is a CTfxGc this function will return the MAknListBoxTfxInternal instance
	 * belonging to this gc otherwise it will return NULL
	 * 
     * @since S60 3.2
     * @param aGc the gc for which the MAknListBoxTfxInternal instance should be retrieved
     * @return A MAknListBoxTfxInternal instance or NULL if it can't be found
     */
	virtual MAknListBoxTfxInternal *AknListBoxTfxInternal(CWindowGc *aGc) = 0;
	
	/**
	 * Creates a CTfxGc that should replace the normal gc on aListBox. 
	 * If it fails to create the gc the normal gc will be returned 
	 * and no list effects will be available.
	 * 
     * @since S60 3.2
     * @param aListBox the listbox for which this gc should be used
     * @return A TfxGc if successfull, otherwise the normal aListBox gc
     */
    virtual CWindowGc* CreateTfxGc( CEikListBox& aListBox ) = 0;


    /**
     * Creates a CTfxGc that should replace the normal gc on aMenuPane. 
     * If it fails to create the gc the normal gc will be returned 
     * and no list effects will be available.
     * 
     * @since S60 3.2
     * @param aMenuPane The menupane for which the gc that is returned should be used.
     * @param aTopIndex A value containing the top item index.
     * @param aItemsThatFitInView A value containing number of items that fit
     *                            in view.
     * @param aScrollBarRect A rectangle describing the position and size of
     *                       the scrollbar.
     *
     * @return A TfxGc if successfull, otherwise the normal aListBox gc
     */
    virtual CWindowGc* CreateTfxGc( CEikMenuPane& aMenuPane,
                                    TInt& aTopIndex, TInt& aItemsThatFitInView ) = 0;

    /**
     * Creates a CTfxGc that should replace the normal gc on aTreeList. 
     * If it fails to create the gc the normal gc will be returned 
     * and no list effects will be available.
     * 
     * @since S60 5.0
     * @param aTreeList The treelist for which the gc that is returned should be used.
     * @param aTopIndex A value containing the top item index.
     * @param aItemsThatFitInView A value containing number of items that fit
     *                            in view.
     * @param aScrollBarRect A rectangle describing the position and size of
     *                       the scrollbar.
     *
     * @return A TfxGc if successfull, otherwise the normal aListBox gc
     */
    virtual CWindowGc* CreateTfxGc( CAknTreeList& aTreeList,
				                    TInt& aTopIndex,
                                    TInt& aBottomIndex,
                                    TInt& aHighlightIndex,
                                    TInt& aRows ) = 0;

    /**
     * Creates a CTfxGc that should replace the normal gc on aAdapter.
     * If it fails to create the gc the normal gc will be returned
     * and no list effects will be available.
     *
     * @since S60 5.0
     * @param aAdapter The adapter for which the gc that is returned should be used.
     *
     * @return A TfxGc if successfull, otherwise the normal gc
     */
    virtual CWindowGc* CreateTfxGc( CCoeControl& aAdapter ) = 0;
};

#endif //AKNLISTBOXTFXPLUGIN_H
