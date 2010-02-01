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
* Description:  List layouts only for MIDP use
*  NOTE: DO NOT USE THESE LISTS in AppSw (these lists break ui-style) !!!
*
*/


#include <aknlists.h>


/**
 * list_double2_graphic_large_graphic_pane
 *
 * list item string format: "1\t2\tFirstLabel\tSecondLabel\t0"
 *
 * where 0 and 1 is an index of small (13x13) icon in icon array
 *   and 2 is an index of a thumbnail image
 */

class CAknDouble2GraphicLargeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDouble2GraphicLargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };

class CAknSingle2GraphicListBoxItemDrawer : public CColumnListBoxItemDrawer
    {
    public:
	CAknSingle2GraphicListBoxItemDrawer( MTextListBoxModel* aTextListBoxModel,
                                             const CFont* aFont,
                                             CColumnListBoxData* aColumnData );
        ~CAknSingle2GraphicListBoxItemDrawer();

    public: // from CTextListItemDrawer
        void DrawItemText( TInt aItemIndex,
                           const TRect& aItemTextRect,
                           TBool aItemIsCurrent,
                           TBool aViewIsEmphasized,
                           TBool aItemIsSelected ) const;
        void UseEmptyIconSpace( TBool aUse );
private:

    TBool iMoveIcon; // to be changed to iFlags if needed
    TInt  iSpare;
    };

/**
 * list_single_2graphic_pane
 *
 * list item string format: "0\t1\tTextLabel\t2\t3"
 * where 0,1,2,3 are index to the icon array 
 */

class CAknSingle2GraphicStyleListBox : public CEikColumnListBoxTypedef
    {
    public: 
        IMPORT_C CAknSingle2GraphicStyleListBox();
        /** SizeChanged()
        * 
        * Determines layout of the listbox
        */
        IMPORT_C void SizeChanged();
        /** MinimumSize()
        * 
        * Determines size of the listbox for use in dialogs.
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Enables using empty icon space in column 2 for text. Will
        * panic, if itemdrawer is not yet constructed, so do not call
        * this unless you have called Construct{FromResource}L()
        * first.
        *
        * @param aUse ETrue, if space taken by icon ought to be used
        * by text when possible.
        *
        * @since 3.2
        */
        IMPORT_C void UseEmptyIconSpace( TBool aUse );
        
        IMPORT_C virtual void CreateItemDrawerL();
    private:
        void SizeChangedL();
    };
