/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup Volume Indicator
*
*/


#ifndef AKN_VOLUME_POPUP_H
#define AKN_VOLUME_POPUP_H

//  INCLUDES
#include <coecntrl.h>
#include <avkon.rsg>

// CONSTANTS
const TInt KTextLen        = 64;
const TInt KWindowPosition = 10;           // window group's priority
const TInt KInactivityTime = 2000000;      // 2 seconds - close window after this
_LIT( KVolumePopupWgName, "VolumePopup" ); // window groups name

/**
* AknVolume is showed, press speaker icon with the pen, speaker
* icon will be replaced to the mute icon. Value() should reurn 
* KVolumePopupMutedValue, but volume level before muted should
* be saved. After press the  mute icon again, speaker icon  
* should display again and Value()should return the saved value.
*/
const TInt KVolumePopupMutedValue = 0;  
const TInt KVolumePopupLevelNotFound = 0;
// FORWARD DECLARATIONS
class CAknVolumeControl;
class CEikLabel;
class CFbsBitmap;
class CAknsBasicBackgroundControlContext;
class CAknButton;
class CAknSlider;
class CAknControl;
class CAknVolumePopupExtension;
// CLASS DECLARATION

/**
* Sidekey Popup volume indicator
* 
* @lib avkon.lib
* @since 2.8
*
* How to use: <br>
* ----------- <br>
* // create control <br>
* iVolumePopup = CAknVolumePopup::NewL();
*
* // set title text <br>
* iVolumePopup->SetTitleText( _L("Ringer / Profile") );
*
* // set range <br>
* iVolumePopup->SetRange( iMinimumValue, iMaximumValue ); //iMinimumValue<=iVolume && iVolume<=iMaximumValue <br>
*
* // set value <br>
* iVolumePopup->SetValue( iVolume );
*
* // display it  <br>
* iVolumePopup->ShowVolumePopupL(); // will close itself after 1s unless another call to ShowVolumePopupL() is made <br>
*
* // if non volume key is pressed <br>
* iVolumePopup->CloseVolumePopup();
*
*/

NONSHARABLE_CLASS(CAknVolumePopup) : public CCoeControl, 
                                     public MCoeControlObserver,
                                     public MCoeControlBackground
    {
public: // Enumerations
    /**
    * Elements that currently support custom graphics.
    *
    * @since 5.0
    */
    enum TVolumeGfxElements
        {

        /**
        * Speaker component of the volume when unmute.
        */
        EElemSpeaker = 100,

        /**
        * Mute component of the volume when mute.
        */
        EElemMute,

        /**
        * Plus Button component of the volume when button active.
        */ 
        EElemPlusButtonActive,

        /**
        * Plus Button component of the volume when button dimmed.
        */
        EElemPlusButtonInActive,

        /**
        * Plus Button component of the volume when button pressed.
        */
        EElemPlusButtonSelected,

        /**
        * Minus Button component of the volume when button active.
        */
        EElemMinusButtonActive,

        /**
        * Minus Button component of the volume when button dimmed.
        */
        EElemMinusButtonInActive,

        /**
        * Minus Button component of the volume when button pressed.
        */
        EElemMinusButtonSelected      
        };
// Constructors and destructor    
    public:  
        /** deprecated */
        IMPORT_C static CAknVolumePopup* NewL( const TUid aSharedDataVolumeUid,
                                               const TDesC& aKey, 
                                               TInt aMinimumValue = 0 );

        /** 
        * deprecated.
        * Two-phased constructor.
        * Use NewL() to create old volume popup control.
        * @param aMinimumValue deprecated
        */
        IMPORT_C static CAknVolumePopup* NewL( TInt aMinimumValue = 0 );

        /** 
        * Two-phased constructor utilizing custom resource defined by client.
        * Use either this or NewL(). 
        * ConstructFromResourceL() can create dynimic_range volume control
        * @param aResourceId Resource ID for DYNAMIC_VOLUME or VOLUME resource.
        * 
        */
        IMPORT_C static CAknVolumePopup* ConstructFromResourceL( TInt aResourceId );

        /**
        * Two-phased constructor utilizing custom resource defined by client.
        * if aIsVertical is ETrue, there would be a vertical slider
        * if aIsVertical is EFalse, there would be a volume control, but not
        * dynimic_range volume control 

        * @since 5.0
        * @param aParent Pointer to the parent control. 
        * @param aIsVertical A flag for create a vertical slider volume or not.       
        */
        IMPORT_C static CAknVolumePopup* NewL( CCoeControl* aParent,
                                               TBool aIsVertical );
                                                                
        /**
        * Destructor
        */
        virtual ~CAknVolumePopup();
        
// from CCoeControl
    public: 
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void Draw(const TRect& aRect) const;        
        void HandlePointerEventL(const TPointerEvent &aPointerEvent);
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                     TEventCode aType );    
        void PositionChanged();
        
// from MCoeControlObserver               
    public: 
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType); 
        
// from MCoeControlBackground 
    public:
        void Draw(CWindowGc &aGc, const CCoeControl &aControl, const TRect &aRect) const; 
                                                              
// New functions
    public: 
        /** deprecated */
        IMPORT_C TKeyResponse HandleVolumeKeyEventL(const TKeyEvent& aEvent, TEventCode aType); 

        /**
        * Set new volume value to volume control or vertical slider control
        * will show muted icon  or text, if value is 0
        * The first call to this method will set the value to be the default value.
        * @param aValue new value 
        */
        IMPORT_C void SetValue(TInt aValue);

        /**
        * Sets the range of the volume control or vertical slider control. 
        * Maximum value must be greater 
        * than the minimum value, or the method will Panic.
        * Volume value should be within the range.
        * If the default value is greater than the Maximum value, it will be set to maximum value.
        * if the default value is smaller than the Minimum value, it will be set to minimum value.
        *
        * @since 3.2
        * @param aMinimumValue The minimum value of the volume/vertical slider  control
        * @param aMaximumValue The maximum value of the volume/vertical slider  control
        * @par Exceptions:
        *   Will panic with EAknPanicInvalidValue if the minimum value is greater
        *   or equal than maximum value.
        *
        */
        IMPORT_C void SetRange( TInt aMinimumValue, TInt aMaximumValue );
        
        /**
        * Gets the range of the volume control or vertical slider.
        * @since 3.2
        * @param aMinimumValue The minimum value of the volume/vertical slider control
        * @param aMaximumValue The maximum value of the volume/vertical slider control
        */
        IMPORT_C void GetRange( TInt& aMinimumValue, TInt& aMaximumValue );

        /**
        * get volume control or vertical slider control value
        */
        IMPORT_C TInt Value() const;

        /**
        * Set title part of label text
        * @param aText title part of text
        */
        IMPORT_C void SetTitleTextL( const TDesC& aText );

        /** deprecated */
        IMPORT_C void ShowProfileName( TBool aShowProfile );

        /**
        * Show the popup window - it will
        * close itself after a second of inactivity
        */
        IMPORT_C void ShowVolumePopupL();

        /**
        * close the popup window - actually this only hides it
        */
        IMPORT_C void CloseVolumePopup();
        
        /**
        * Set value type for vertical slider control
        *
        * @since 5.0
        * @param aValueType A type of value, should be EAknSliderValueNone,
        * EAknSliderValueBareFigure,EAknSliderValuePercentage,
        * EAknSliderValueFraction or EAknSliderValueDecimal.
        *
        * If EAknSliderValueNone is set as value type, the speaker icon will
        * be displayed instead of value text;
        * 
        * If one of other value types except EAknSliderValueNone is set as
        * value type, the speaker icon will not be shown, only the value text
        * can be seen.
        *
        * The default value type is EAknSliderValueNone.
        */
        IMPORT_C void SetValueType( TInt aValueType );
         
        /**
        * Sets the step size. The step size must divide evenly into the Range. This
        * routine should be called after SetRange if either is called.
        *
        * @since 5.0
        * @param aStepSize The value of the step size
        */
        IMPORT_C void SetStepSize( TInt aStepSize );
        
        /**
        * As default adjustment indicator is displayed.
        * this function can be used to sets switch for adjustment indicator on/off.
        *
        * @since 5.0
        * @param aFlag A bool value for switch adjustment indicator on/off.
        */
        IMPORT_C void SetAdjustmentIndicatorDisplay( TBool aFlag );
        
        /**
        * Time out for dispear the volume control can be defined.
        * Only used for floating Slider popup( no Parent defined).
        * If parent is set, Timeout doesn't take effect, the contol
        * is alway shown until user close it manually.
        *
        * @since 5.0
        * @param aSecond A time value as second.
        */
        IMPORT_C void SetTimeOutAsSecond( TInt aSecond ); 
        
        /**
        * Decimal place can be set by the user.
        * Only used for Slider popup, the value must be 0 ~ 9
        *
        * @since 5.0
        * @param aDecimalPlace A decimal place.
        */
        IMPORT_C void SetDecimalPlaces( TInt aDecimalPlaces ); 
                     
        /**
        * Allows setting custom graphics for a certain vertical volume element. 
        * Existing icons (custom or default) for the element are discarded. 
        *
        * Vertical volume takes care of scaling the given icons to the correct size,
        * provided that they have been created with @c AknIconUtils or @c AknsUtils
        * interfaces. It also handles re-scaling the icons if the volume layout
        * changes.
        *
        * If the custom icons are created by using skin items (e.g. using color
        * from skin), remember to change the icons whenever skin changes, see
        * @c CCoeControl::HandleResourceChange.
        *
        * @param aElement The element ID to which the icons are assigned, one of
        *                 @c TVolumeGfxElements and TSliderGfxElements.
        *
        * @param aBitmap The icon used for the element, must be non-NULL,
        *                ownership is transferred to volume.
        *
        * @param aMask Optional mask for the aBitmap, can be NULL, ownership
        *              is transferred to volume.
        *
        * @par Exceptions:
        *   Will panic with EAknPanicInvalidValue if the element ID is invalid or
        *   aBitmap is NULL.
        *
        * @since 5.0
        */
        IMPORT_C void SetGraphics( TInt aElement,
                                   CFbsBitmap* aBitmap,
                                   CFbsBitmap* aMask );
        /** 
        *  If muted icon is used, the speaker icon will change to mute 
        *  icon when volume value is minimized. If not, the speaker icon will 
        *  not be changed.
        *  @since 5.0
        *  @param aFlag  - A flag for changing to mute icon or not.
        */ 
        IMPORT_C void UseMutedIcon( TBool aFlag );
                                                     
        /** 
        *  If enabled, volumepopup will close itself when user touches outside,
        *  Enabled as default.
        *  @since 5.0
        *  @param aEnable  - ETrue then close volumepopup when user touches outside.
        */ 
        IMPORT_C void ClosePopupWhenTappedOutside( TBool aEnable );
        
        /**
        * Set default value for volume popup with value field.
        * Tapping the value field will set the volume value to be the default value,
        * also the first set value with SetValue call will set that value to be 
        * the default value.
        * @since 5.0
        * @param aValue new value
        */
        IMPORT_C void SetDefaultValue( TInt aValue );
        
        /**
        * If enabled, the value field displayed in volumepopup will be inactive. 
        * Enabled as default
        * @since 5.0
        * @param aEnable  - ETrue Disable the default value feature of volumepopup
        */
        IMPORT_C void EnableResetViaValueField( TBool aEnabled=ETrue );



    protected: // From CCoeControl
        void SizeChanged();
        
        void HandleResourceChange( TInt aType );
        
    private:
        /**
        * C++ default constructor.
        */
        CAknVolumePopup(TInt aFlags);

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aParent Pointer to the parent control.
        * @param aIsVertical A flag for create a vertical slider volume or not.
        * @param aResourceId Resource ID for volume.
        */
        void ConstructL( CCoeControl* aParent,
                         TBool aIsVertical,
                         TInt aResourceId = R_AVKON_POPUP_VOLUME_INDICATOR );

        /** Prohibit copy constructor if not deriving from CBase.*/
        CAknVolumePopup( const CAknVolumePopup& );
        
        /** Prohibit assigment operator if not deriving from CBase.*/
        CAknVolumePopup& operator=( const CAknVolumePopup& );

        static void CleanupShowVolumePopup(TAny* aThis);

        void SetSpeakerMuted(TBool aMuted);
        void MutePressed();
        void StartTimer();
        void ResetTimer();
        static TInt TimerExpired(TAny* aPtr);

        /**
        * Show text "Muted" instead of volume slider if volume = 0
        * @param aShowMuteAsLabel ETrue = show text
        *
        * Not exported yet
        */
        /*IMPORT_C*/ void ShowMuteAsLabel( TBool aShowMuteAsLabel );
        
        /**
        * When the volume value is minimum or mute, volume control is 
        * invisible, but the if vertical slider is used, it can be seen.
        * @param aVisibility A flag for the volume control's visiblility.
        */
        void SetVisibilityL( TBool aVisibility );
        
        void CreateControlsL();
        void CreateSpeakerL();
        void SetControlIconL(  TInt aElement,
                               CFbsBitmap* aBitmap,
                               CFbsBitmap* aMask );
        void CreateLeftRightButtonL();
        void CreateUpDownButtonL();
        void SetValueTextL();
        
        void DoSetValueTextL( TDes& aTextBuf, TInt aValue );

        void GetMarkerRect( TRect& aRect );
        
        /**
         * From @c CCoeControl.
         *
         * Retrieves an object of the same type as that encapsulated in aId. Other
         * than in the case where @c NULL is returned, the object returned must be 
         * of the same object type - that is, the @c ETypeId member of the object
         * pointed to by the pointer returned by this function must be equal to the
         * @c iUid member of @c aId.
         *
         * @param aId An encapsulated object type ID.
         * @return Encapsulates the pointer to the object provided. Note that the 
         *         encapsulated pointer may be @c NULL.
         */
        TTypeUid::Ptr MopSupplyObject( TTypeUid aId );       
        void SetVolumeLayout();
        void SetLabelColor();       
        /**
        * Set new volume value to volume control or vertical slider control
        * will show muted icon  or text, if value is 0
        * @param aValue new value (1-10)
        */
        void DoSetValue(TInt aValue);       
// member data
    private:    
        RWindowGroup        iWindowGroup;
        
        /** title & profile text */
        CEikLabel*          iLabel;
        /** text to show instead of volume control */
        CEikLabel*          iMutedLabel;      

        /** spare */
        HBufC*              iSpare;
        /** muted label text */
        HBufC*              iMutedText;       
        
        // icons
        CAknButton*         iSpeaker;

        /** current volume setting */
        TInt                iVolume;          
        // show normal / muted icon */
        TBool               iMuted;           
        /** is control visible? */
        TBool               iVisible;         
        /** show "Muted" instead of volume control */
        TBool               iShowMuteAsLabel; 
        /** saved volume setting */
        TInt                iStoredLevel; 
        /** only used for vertical slider value label format */
        TInt iValueType;
        TInt iDecimalPlaces;
        
        /** controls parent rectangle */
        TRect               iParentRect;              
        
        TRect               iSpeakerRect;
        /** will close window after timeout */
        
        CPeriodic*          iTimer;           
        
        CAknsBasicBackgroundControlContext*  iBgcc;
        
        CAknButton* iDecArrow;
        CAknButton* iIncArrow;
        TInt iFlags;
        
        /** A switch for adjustment indictor icon display.*/ 
        TBool iAdjustmentIndicatorOn; 
        /** A flag for vertical or not.*/  
        TBool iVertical;
         
        /** time for inactivity time.*/
        TInt iTimeout; 
        CAknVolumePopupExtension* iExt;
        TAny* iSpareMember;             

    };


#endif      // AKN_VOLUME_POPUP_H
            
// End of File
