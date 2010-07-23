/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  implementation of setting list box
*
*/


// EIKSLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSLB_H__)
#define __EIKSLB_H__

#include <eikfrlb.h>

class MTextListBoxModel;
class CFont;
class CSettingsListBoxData;
class CSettingsListBoxView;

/**
* Item drawer class for CEikSettingsListBox. This class is not intended for user derivation.
* @since S60 1.0
* @lib   Avkon.lib
*/

class CSettingsListBoxItemDrawer : public CFormattedCellListBoxItemDrawer
    {
    public:
        /**
        * Default constructor.
        * @param aTextListBoxModel The model whose items will be drawn.
        * @param aFont             The font in which the items will be drawn. Usually overriden by layouts.
        * @param aSettingsData     The listbox data class to be used.
        */
        IMPORT_C CSettingsListBoxItemDrawer( MTextListBoxModel* aTextListBoxModel,
                                             const CFont* aFont,
                                             CSettingsListBoxData* aSettingsData );

        /**
        * destructor
        */
        IMPORT_C ~CSettingsListBoxItemDrawer();

        /**
        * @return pointer to listbox data class
        */
        IMPORT_C CSettingsListBoxData* SettingsData() const;
    public:
        /**
        * from CTextListItemDrawer
        * @param aItemIndex        Index of the item to draw.
        * @param aItemTextRect     Area to draw into.
        * @param aItemIsCurrent    ETrue if the item is current.
        * @param aViewIsEmphasized ETrue if the view is emphasized.
        * @param aItemIsSelected   ETrue if the item is selected.
        */
        IMPORT_C void DrawItemText( TInt aItemIndex,
                                    const TRect& aItemTextRect,
                                    TBool aItemIsCurrent,
                                    TBool aViewIsEmphasized,
                                    TBool aItemIsSelected ) const;
    private:
        IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();

    };



/**
* List box base class. Creates listbox view and item drawer classes. This class
* is used throughout @c AknListBoxLinesTemplate< T > class. 
* The @c CEikSettingsListBox uses @c CSettingsListBoxView as a list box view 
* class and a @c CSettingsListBoxItemDrawer as an item drawer.
* @since S60 1.0
* @lib   Avkon.lib
*/
class CEikSettingsListBox : public CEikFormattedCellListBox
    {
    public:

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikSettingsListBox();

    public:

        /**
        * Gets an item drawer of @c CEikSettingListBox which handles drawing of 
        * single list box items and manages their properties.
        * 
        * @return Pointer to the item drawer instance.
        */
        IMPORT_C CSettingsListBoxItemDrawer* ItemDrawer() const;

    protected:

        /**
        * Creates an item drawer for @c CEikSettingsListBox.
        */
        IMPORT_C void CreateItemDrawerL();

    public: // from CEikListBox

        /**
        * From @c CEikListBox. 
        *
        * Creates the list box view. The function is called 
        * by @c ConstructL() to create an instance of the appropriate list box 
        * view class for this list box. The returned instance is owned by this 
        * object, and does not have to have its second-phase constructor run. 
        * This function is called by @c CreateViewL().
        *
        * @return Pointer to a newly constructed list box view for this object.
        */
        IMPORT_C CListBoxView* MakeViewClassInstanceL();

    public: // from CCoeControl

        /**
        * From @c CCoeControl. 
        * 
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event.
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected:

        /**
        * Gets a list box view class as @c CSettingsListBoxView.
        *
        * @return Pointer to the list box view class object.
        */
        CSettingsListBoxView* View() { return (CSettingsListBoxView*)iView; }

    private:

        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private: // listbox use only
        IMPORT_C virtual void CEikListBox_Reserved();
    
    };

/**
* View class for CEikSettingsListBox
*
* This class is not intended for user derivation.
*/

class CSettingsListBoxView : public CFormattedCellListBoxView
    {
    public: // from CListBoxView
        /**
        * Empty default constructor.
        */
        CSettingsListBoxView() {}

        /**
        * Draws all items.
        * @param aClipRect Area to draw.
        */
        IMPORT_C void Draw(const TRect* aClipRect = NULL) const;

        /**
        * Draws specified item.
        * @param aItemIndex Item index to draw.
        */
        IMPORT_C void DrawItem(TInt aItemIndex) const;

        /**
        * @return pointer to item drawer class.
        */
        inline CSettingsListBoxItemDrawer *ItemDrawer() const;
    private: // overridden from CListBoxView
        IMPORT_C virtual TAny* Reserved_1();
    };


inline CSettingsListBoxItemDrawer* CSettingsListBoxView::ItemDrawer() const
    { return (CSettingsListBoxItemDrawer*)iItemDrawer; }


#endif // __EIKSLB_H__



