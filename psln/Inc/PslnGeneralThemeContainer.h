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
* Description:  General theme container.
*
*/



#ifndef PSLNGENERALTHEMECONTAINER_H
#define PSLNGENERALTHEMECONTAINER_H

#include "PslnBaseContainer.h"

class CAknLocalSkinInstance;

/**
*  Observer interface for theme preview state changes.
*  aPreviewMode new mode for theme preview - ETrue preview is active
*                                            EFalse preview is now ready
*
*  @since S60 v5.0
*/
class MPslnThemePreviewObserver
    {
    public:
        virtual void HandlePreviewStateChange( const TBool& aPreviewMode ) = 0;
    };

/**
*  General theme container.
*  Contains available skins.
*
*  @since S60 v3.1
*/
class CPslnGeneralThemeContainer : public CPslnBaseContainer
    {
    public:  // Constructors and destructor   
    
        /**
        * C++ default constructor.
        */
        CPslnGeneralThemeContainer();

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aRect client rect.
        */
        void ConstructL( const TRect& aRect );        
        
        /**
        * Destructor.
        */
        virtual ~CPslnGeneralThemeContainer();
        
    public: // New methods
    
        /**
        * Is embedded link visible. 
        * @return ETrue if link should be shown.
        */
        TBool IsEmbeddedLinkVisible() const;
        
        /**
        * Updates skin list.
        */
        void UpdateSkinListItemsL( const TInt& aNewIndex );

        /**
        * From CPslnBaseContainer.
        * Constructs list box and items.
        * @param aResLbxId used resource ID.
        */
        void ConstructListBoxL( TInt aResLbxId );
        
        /**
        * From CPslnBaseContainer.
        * Creates listbox items.
        */
        void CreateListBoxItemsL();

        /**
        * Updates D column icons when skin preview activates.
        *
        * @since 5.0
        */
        void UpdateSkinListItemsDColumnOnlyL();

        /**
        * Starts theme preview.
        *
        * @since 5.0
        */
        void StartThemePreviewL( TBool aTouch = ETrue );
                
        
        /**
        * Cancel theme preview.
        *
        * @since 5.0
        */
        void CancelThemePreviewL();


        /**
        * Sets theme preview change observer (MPslnThemePreviewObserver).
        * aObserver observer for theme preview changes.
        *
        * @since 5.0
        */
        void SetThemePreviewObserver( MPslnThemePreviewObserver* aObserver );

        /**
        * Locks/enables up and down key events to this container.
        *
        * @since 5.0
        */
        void LockUpAndDownKeys( const TBool& aLocked );
        
        /**
        * Restart Quick Preview
        */
        void RestartQuickPreviewL();

        /**
        * Set theme preview state active.
        */    
        void SetPreviewStateActive();
        
        /**
        * Is current focus theme in preview state. 
        * @return ETrue if theme is in preview state.
        */    
        TBool CurrentThemeInPreviewState();
        

    private:            
        
        // Gets Help context.        
        void GetHelpContext( TCoeHelpContext& aContext ) const;
        // From CPslnBaseContainer
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent, 
            TEventCode aType );
        // From CCoeControl
        void HandlePointerEventL( const TPointerEvent &aPointerEvent );

        /* Creates (&initializes) a locally skinnable item list.*/
        void CreateSkinItemList();
        
        /* Adds skin item to locally skinnable item list. */
        TInt AddItemToList( const TAknsItemID& aSkinID );

        /* Callback interface for idle time. */
        static TInt DoHandleIdleTimeL( TAny* aAny );

        /* Callback interface for theme effect ending. */
        static TInt DoHandleEffectEndL( TAny* aAny );

        /* Handle idle time. */
        void HandleIdleTimeL();

        /* Handle theme effect ending. */
        void HandleEffectEndL();
        
        /*
        * Get Preview Skin Index.
        */
        TInt PreviewSkinIndex();

        /* Initialize theme preview delay time settings. */
        void InitPreviewTime();
        
        /* Show Error Note. */
        void ShowErrorNoteL( TInt  aResourceId  ); 

    private: // data

        /*
        * List of skin items to skin locally.
        */
        RArray<TAknsItemID> iSkinItemList;

        /*
        * Timer for delay.
        * Own.
        */
        CPeriodic* iPreviewIdle;

        /*
        * Skin preview library instance.
        * Own.
        */
        CAknLocalSkinInstance* iLocalSkinInstance;

        /*
        * Theme preview state change observer.
        * Not own.
        */
        MPslnThemePreviewObserver* iObserver;

        /*
        * To be used index in highlight when container is updated.
        * This is used when skin is activated and user has already
        * highlighted some other theme.
        */
        TInt iToBeUsedIndex;

        /*
        * Up and down key events are ignored while a skin is activating.
        * This is to avoid drawing of container when the skin items might
        * not be valid.
        */
        TBool iLockedKeys;
                
        /*
        * Current preview theme index in listbox.
        */
        TInt iActiveSkinItemIndex;
        
        /*
        * Theme preview delay time.
        */
        TInt iPreviewDelayTime;
        
        /*
        * Theme preview delay time, arisen by navigation key.
        */
        TInt iPreviewDelayTimeOnHardKey;
        
        /*
        * Theme preview interval time.
        */
        TInt iPreviewIntervalTime;
        
        /*
        * Old Skin Num.
        */
        TInt iOldSkinNum;
    };

#endif      // PSLNGENERALTHEMECONTAINER_H  
            
// End of File
