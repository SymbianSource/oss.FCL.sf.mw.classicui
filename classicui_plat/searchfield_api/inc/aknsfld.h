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
*  Search Field support. 
*
*
*/


#ifndef __AKNSFLD_H__
#define __AKNSFLD_H__

// INCLUDES
#include <AknControl.h>
#include <gulicon.h>
#include <eikgted.h>
#include <aknappui.h>
#include <e32property.h>  // for subscriber/publisher

// FORWARD DECLARATIONS
class CEikEdwin;
class CGlobalText;
class CAknInputFrame;
class CAknSearchFieldIndicator;
class CAknsListBoxBackgroundControlContext;
class CAknsFrameBackgroundControlContext;
class CEikListBox;
class CAknAdaptiveSearch;
class MAdaptiveSearchTextObserver; 
class CAknSearchField;
class CHwKbSubscriber;

/** 
 * Adaptive search text observer will be notified when adaptive search 
 * text/language are changed. Notify about text changing when adaptive search 
 * grid is opened for the first time (empty search text is generated) or when 
 * user taps the grid so that new character is inputted. Notify about language
 * chnging when got information from CenRep.  
 * 
 * @since 5.0 
 */ 
class MAdaptiveSearchTextObserver 
    { 
    public: 
       /** 
        * Notification and handling of an adaptive search text change. 
        * 
        * @param aSearchField The source search field of this message. 
        */ 
        virtual void AdaptiveSearchTextChanged( CAknSearchField* aSearchField ) = 0; 
    }; 

 
// CLASS DECLARATION

/**
 * The CAknSearchField class implements a Search field control. There are 
 * different styles for the search field defined by a TSearchFieldStyle.
 *
 * @since Series 60 0.9
 */
NONSHARABLE_CLASS(CAknSearchField) : public CAknControl,
		                             public MCoeControlObserver,			
                		             public MEikCommandObserver
{
public:
   /**
    * Search field style.
    */
    enum TSearchFieldStyle 
        {
        /** Use only ESearch in Series 60 */
        ESearch,
        /** (Not used) */        
        EInput,
        /** (Not used) */
        EUrl,  
        /** (Not used) */
        EPhone,
        /** (Not used) */
        EPlain,
        /** Use as popup search field. */
        EPopup,         
        /** Use as pinb search field. */
        EPinb,          
        /** For Clock application/list_single_heading_pane. */
        EClockApp,      
        /** Same as ESearch, but using CreateWindowL(). */
        EFixed,         
        /** Layout where no line is used. */
        ESearchWithoutLine, 
        /** Popup window layout. */
        EPopupWindow,
	    /** For adaptive search grid */
	    /** @since 5.0 */
	    EAdaptiveSearch,
	    /** For adaptive search grid */
	    /** Same as EAdaptiveSearch, but using CreateWindowL(). */
	    /** @since 5.0 */
	    EAdaptive,
        /** For adaptive search grid */
	    /** Same as EAdaptiveSearch, but using popup find pane. */
	    /** @since 5.0 */
	    EPopupAdaptiveSearch,
        /** For adaptive search grid */
	    /** Popup window layout */
	    /** @since 5.0 */
	    EPopupAdaptiveSearchWindow
        };
  
public:

   /**
    * Destructor.
    */
    IMPORT_C ~CAknSearchField();

   /**
    * Two-phased constructor.
    * @param aParent Reference to parent control.
    * @param aFieldStyle Defines the UI style.
    * @param aIcon A pointer to the icon to be shown in the search box frame.
    *              Takes ownerships. Can be @c NULL.
    * @param aTextLimit Defines the maximum text length.
    * @return A pointer to contructed @c CAknSearchField object.
    */
    IMPORT_C static CAknSearchField* NewL( const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit );

public:                 // for search string manipulation
   /**
    * Returns the length of search text.
    * @return The length of search text.
    */
    IMPORT_C TInt TextLength() const;

   /**
    * Returns the text of search field by writing it into the 
    * buffer aSearchTxt.
    * @param aSearchTxt Reference to the text buffer. Buffer size must be same
    *                   or greater than maximum text length, which is given in 
    *                   constructor.
    */
    IMPORT_C void GetSearchText( TDes& aSearchTxt ) const;

   /**
    * Sets text into search field.
    * @param aSearchTxt Reference to the text buffer.
    */
    IMPORT_C void SetSearchTextL( const TDesC& aSearchTxt );

   /**
    * Selects the whole search text.
    */
    IMPORT_C void SelectSearchTextL();

   /**
    * Clears text in the search field.
    */
    IMPORT_C void ResetL();

   /**
    * Sets additional info text to the search field.
    * @param aText Reference to the text buffer.
    */
    IMPORT_C void SetInfoTextL( const TDesC& aText );

   /**
    * Calls editor's @c ClipboardL() function.
    * @param aClipboardFunc Clipboard function.
    */
    IMPORT_C void ClipboardL( CEikEdwin::TClipboardFunc aClipboardFunc );

   /**
    * Return search field style
    * @since 5.0
    * @return style of search field 
    */   
    IMPORT_C CAknSearchField::TSearchFieldStyle SearchFieldStyle() const;

public: // new methods for Avkon Skins support

   /**
    * Sets whether skins are enabled on this control. The default value is 
    * determined from global setting from @c CAknAppUi.
    * @since Series 60 2.0 
    * @param aEnabled @c ETrue if skins are enabled, @c EFalse if not.
    */
    IMPORT_C void SetSkinEnabledL( const TBool aEnabled );

public: // from MCoeControlObserver

   /**
    * From @c MCoeControlObserver, Acts upon changes in the hosted control's state.
    * This class's implementation is trivial and should be able to be safely 
    * re-implemented in directly client-derived classes. For non-base setting
    * page classes, a call to the base class should be made.
    * @param aControl Control that caused the event. (not used in default implementation)
    * @param aEventType Type of the event. 
    */
    void HandleControlEventL( CCoeControl* aControl,TCoeEvent aEventType );

public: // From CCoeControl

   /**
    * From @c CCoeControl, Handles key event.
    * @param aKeyEvent The key event. 
    * @param aType The type of the event.
    * @return Indicates whether the key event was used by this control or not.
    */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,TEventCode aType );

   /**
    * From @c CCoeControl, Handles pointer event.
    * @since 5.0
    * @param aPointerEvent The pointer event. 
    *	Invert adaptive search grid by tapping search field.    
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

   /**
    * From @c CCoeControl, Returns minimum size. Minimum size depends on 
    * zoom factor. 
    * @return Minimum size.
    */
    IMPORT_C TSize MinimumSize();

   /**
    * Sets this control as visible or invisible.
    *
    * @since S60 3.2
    * @param aVisible ETrue to make the control visible, EFalse to make
    *                 it invisible.
    */
    IMPORT_C void MakeVisible( TBool aVisible );
    
    /**
     * From @c CCoeControl, Resource change handling.
     *
     * @param aType Message type.
     */
    void HandleResourceChange( TInt aType );

public:

   /**
    * Sets position of the line on main pane.
    * @since Series 60 2.0
    * @param aLinePos The position as defined in @c TAknSeparatorLinePos
    */
    IMPORT_C void SetLinePos( TInt aLinePos );

   /**
    * Access to the edwin owned by the search field.
    * @since Series 60 2.6
    * @return Reference to the edwin owned by the search field.
    */
    IMPORT_C CEikEdwin& Editor() const;

   /**
    * Set adaptive search grid characters.
    * @since 5.0
    * @param aGridChars The characters for adaptive search grid.
    */
    IMPORT_C void SetAdaptiveGridChars( const TDesC& aGridChars ) const;

   /**
    * Show adaptive search grid. 
    * Application can activate adaptive search grid from the option menu.
    * @since 5.0
    */
    IMPORT_C void ShowAdaptiveSearchGrid() const;   
    
   /**
    * Set column filter flag for adaptive search grid  
    * @since 5.0
    * @param aFlag The bit flag shows which columns take into account
    * during filtering.
    */
    IMPORT_C void SetListColumnFilterFlags( const TBitFlags32 aFlag );

   /**
    * Send column filter flag for adaptive search grid  
    * @since 5.0
    * @return aFlag The bit flag shows which columns take into account
    * during filtering.
    */
    IMPORT_C TBitFlags32 ListColumnFilterFlags() const;

   /** 
    * Adds an adaptive search text observer. Duplicates are not checked 
    * (i.e. adding the same observer multiple times is not prevented). 
    * @since 5.0 
    * @param aObserver Must be non-NULL. 
    */ 
    IMPORT_C void AddAdaptiveSearchTextObserverL( MAdaptiveSearchTextObserver* aObserver );

   /** 
    * Removes an adaptive search text observer. 
    * @since 5.0 
    * @param aObserver The observer to be removed. 
    * @return ETrue if removal ok, EFalse if observer was not removed (not 
    * found from the list of observers). 
    */ 
    IMPORT_C TBool RemoveAdaptiveSearchTextObserver( MAdaptiveSearchTextObserver* aObserver );

   /** 
    * Returns information whether adaptive search is enabled or not
    * @since 5.0   
    * @return ETrue if adaptive search is enabled, EFalse otherwise.
    */ 
    IMPORT_C TBool AdaptiveSearchEnabled();

   /** 
    * Notify client if input language changed in settings, for adaptive search
    * @since 5.0       
    * @return ETrue if language has changed, EFalse otherwise.
    */
    IMPORT_C TBool LanguageChanged() const;

private: // from MObjectProvider
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
private:
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void SizeChanged();
    void FocusChanged( TDrawNow aDrawNow );
private:
    void ConstructL( const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit );
    CAknSearchField(); 
private:
    void ZoomEditorL();
private: // from MEikCommandObserver
    IMPORT_C void ProcessCommandL( TInt aCommandId );
private:
    void UpdatePopupCBAL();
    void RestorePopupCBA();
    void SetupSkinContextL();
public:

   /**
    * Sets a list box for this control.
    * @since Series 60 2.6
    * @param aListBox A pointer to a list box object.
    */
    void SetListbox( CEikListBox* aListBox );

   /**
    * Sets the parent control for this control.
    * @since Series 60 2.6
    * @param aParent A pointer to the parent control.
    */
    void SetParentCtrl( CCoeControl* aParent );

   /**
    * Indicates that is the control popup or not.
    * @since Series 60 2.6
    * @return @c ETrue if it is a popup, @c EFalse if not.
    */
    TBool IsPopup();

   /**
    * Sets index, where listbox focus should return when popup findbox is
    * canceled.
    * @since Series 60 3.1
    * @internal
    */
    void SetOldItemIndex( TInt aOldItemIndex );

   /**
    * Returns index, where listbox focus should return when popup findbox is
    * canceled
    * @since Series 60 3.1
    * @internal
    */
    TInt OldItemIndex();

   /** 
    * Set the language changed flag, for adaptive search
    * @since 5.0       
    * @param aLanguageChanged ETrue if language has changed, EFalse otherwise.
    */
    void SetLanguageChangedFlag( TBool aLanguageChanged );
    
    /**
     * Handle HW keyboard active/deactive event.
     * @since 5.0
     */
    void HandleHWKeyboardModeChangeL();

    /**
     * A helper methord used in ContructL().
     * Get Adaptive Search setting and subscribe hardware 
     * keyboard layout changing.
     *
     * @param aShowIndicator, ETrue if indicator need be shown
     * @return ETrue if Adaptive is enabled in cenrep/
     * @since 5.0
     */
    TBool GetASStatusAndSubKbLayoutL( TBool& aShowIndicator );

private:	
    // The bit flag shows which collumns take into account during filltering  
    TBitFlags32 iColumnFlag;
    CEikEdwin* iEditor;   
    CGlobalText* iGlobalText;
    CAknInputFrame* iInputFrame;
    CAknSearchFieldIndicator* iIndicator; 
    CAknsListBoxBackgroundControlContext* iSkinContext;
    TInt iFlags;  
    TInt iLinePos;
    CAknsFrameBackgroundControlContext* iInputContext;
    TBool iIsPopup;
    TBool iCBAObserverUpdated;
    CEikListBox *iListBox; // not owned
    CCoeControl *iParent; // not owned
    CEikButtonGroupContainer *iCba; // this is only for checking whether cba changed 
    TInt iOldItemIndex;
    CAknAppUi* iBackedAppUi;
    CAknAdaptiveSearch* iAdaptiveSearch; 
    TSearchFieldStyle iStyle;    
    TBool iLanguageChanged; // flag shows was input language changed or not

    // For hybird keyborad
    RProperty iHwKeyboardPro;
    CHwKbSubscriber* iHwKbSub;
    };
 
#endif


