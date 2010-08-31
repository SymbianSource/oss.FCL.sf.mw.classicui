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
* Description:  Volume editor class
*
*/


#ifndef AKNVOLUMECONTROL_H
#define AKNVOLUMECONTROL_H

#include <AknNaviDecoratorObserver.h>

#include <AknControl.h>

class CGulIcon;
class MAknsSkinInstance;
class CVolumeExtension;

/**
 * Used for controlling the volume setting on the phone.
 */
class CAknVolumeControl : public CAknControl, public MAknNaviDecoratorObserver
    {

    public:

        /** 
         * C++ default constructor. 
         */
        IMPORT_C CAknVolumeControl();

        /** 
         * Destructor. 
         */
        IMPORT_C ~CAknVolumeControl();

        /** 
         * Sets volume.
         *
         * @param aValue The new volume.
         */
        IMPORT_C void SetValue(TInt aValue);

        /** 
         * Gets volume.
         *
         * @return The volume setting.
         */ 
        IMPORT_C TInt Value() const;

        /**
        * Sets the range of the volume control. Maximum value must be greater 
        * than the minimum value, or the method will Panic.
        *
        * @since 3.2
        * @param aMinimumValue The minimum value of the volume  control
        * @param aMaximumValue The maximum value of the volume control
        * @par Exceptions:
        *   Will panic with EAknPanicInvalidValue if the minimum value is 
        *   greater or equal than maximum value.
        *
        */
        IMPORT_C void SetRange( TInt aMinimumValue, TInt aMaximumValue );
        
        /**
        * Gets the range of the volume control.
        * @since 3.2
        * @param aMinimumValue The minimum value of the volume  control
        * @param aMaximumValue The maximum value of the volume control
        */
        IMPORT_C void GetRange( TInt& aMinimumValue, TInt& aMaximumValue );
        
        void SuppressDrawing( TBool aSuppress );
    public: // from CCoeControl

        /** 
         * From @c CCoeControl.
         * 
         * Gets minimun size of layout rectangle.
         *
         * @return Minimum layout rectangle size. 
         */ 
        TSize MinimumSize();
   
        /** 
         * From @c CCoeControl 
         *
         * Handles key events.
         * 
         * @param aKeyEvent Key event to be handled.
         * @param aType Type of the event.
         * @return Returns @c EKeyConsumed if key event was handled. 
         */ 
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
        
        /**
         * From @c CCoeControl.
         *
         * Construct item from given resource.
         *
         * @param aReader Resource reader reading the wanted resource set. 
         */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /** 
         * From @c CCoeControl.
         *
         * Handles the change of @c CAknVolumeControl's resources. 
         * 
         * @param aType Type of resource to change
         */ 
        IMPORT_C void HandleResourceChange(TInt aType);
        
        /**
         * Creates volume bitmap to "list pane for setting item" 
         * (setting option item volume graphic). Ownership of the returned bitmap
         * is transfered to the caller.
         *
         * @param  aValue Current value (1-10)
         * @return Volume bitmap. Ownership of the bitmap is transfered to 
         *         the caller.
         */
        IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue);
    
        /**
        * Creates general volume icon to "list pane for setting item" 
        * (setting option item volume graphic). Ownership of the returned icon
        * is transfered to the caller.
        *
        * @param  aValue Current value (1-10)
        * @return Volume icon. Ownership of the icon is transfered to 
        *         the caller.
        */
        IMPORT_C static CGulIcon* CreateSetStyleListBoxIconL( TInt aValue );
        
        /**
        * Creates Hi-res volume icon to "list pane for setting item" 
        * (setting option item volume graphic). Ownership of the returned icon
        * is transfered to the caller.
        *
        * @since 3.2
        * @param  aValue Current value (1-10)
        * @param  aMinimum Minimum for Hi-res volume control
        * @param  aMaximum Maximum for Hi-res volume control        
        * @return Volume icon. Ownership of the icon is transfered to 
        *         the caller.
        */
        IMPORT_C static CGulIcon* CreateSetDynRangeStyleListBoxIconL( TInt aValue,
                                                                  TInt aMinimum,
                                                                  TInt aMaximum );

        /**
        * Informs the volume control about whether or not it's placed on the
        * navi pane's control stack
        *
        * @param  aIsOnNaviStack  @c ETrue if the control is on the navi stack,
        *                         @c EFalse otherwise.
        */                                                                  
        void HandleNaviStackChange( TBool aIsOnNaviStack );
        
    protected: // from CCoeControl

        /** 
         * From @c CCoeControl. 
         *
         * Handles layout change. 
         */
        void SizeChanged();
        
        /**
         * From @c CCoeControl.
         *
         * Draws every visible item into the specified rectangle.
         *
         * @param aRect the specified rectangle.
         */ 
        void Draw(const TRect& aRect) const;
        
    public:

        /**
         * From @c CCoeControl. 
         *
         * Handles pointer events.
         * 
         * @param aPointerEvent Pointer event to be handled
         */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
         * From @c MAknNaviDecoratorObserver
         *
         * Handles Navidecorator events (Arrow left and arrow right)
         * 
         * @param aEventID ID of event to be handled
         */
        IMPORT_C void HandleNaviDecoratorEventL( TInt aEventID ); 

    private:
    
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );        
        
    private:
        
        /**
        *
        */
        void SetVolumeLayout(TInt aStyle);
        
        /**
        * Starts a timer for feedback effect visualization 
        */
        void StartTimerL();
        
    	/**
    	 * A callback function for feedback effect.
    	 *
    	 * @param aThis Pointer to this volume control.
    	 */
        static TInt IndicationDrawCallbackL( TAny* aThis );
		
		/**
         * Implementation of the feedback effect (Blinking when the volume value
         * is set to the max/min value).
         */
		void SmallDirectionIndicationL();

        /**
        * (Re)create the navi icon
        */
        void CreateNaviIconL();
        
        // Refactored: Used for drawing different styles.
        void DrawSettingsStyleVolumeControl( const TRect& aRect ) const;
        void DrawDefaultStyleVolumeControl( const TRect& aRect ) const;
        void DrawSkinnedDefaultStyleVolumeControl( const TRect& aRect ) const;
        void DrawDynRangeSettingsStyleVolumeControl( const TRect& aVolumeArea ) const;
    
        /**
        * Calculates the volume icon areas using given volume value.
        *
        * @param aVolume Volume used as the ratio between active and inactive areas.
        * @param aDrawArea The whole drawing area.
        * @param aActiveRect Drawing area for the active icon.
        * @param aInactiveRect Drawing area for the inactive icon.
        */    
        void CalcVolumeIconAreas( const TInt aVolume, 
                                  const TRect& aDrawArea,
                                  TRect& aActiveRect, 
                                  TRect& aInactiveRect ) const;

        /**
        * Utility function for scaling the value between iMiminumValue and 
        * iMaximumValue to a range of [0-10]. This is needed for old drawing 
        * functions that assume only 10 step volume control.
        *
        * @return Colume value scaled to range of [0-10].
        */
        TInt CAknVolumeControl::ScaledValue() const;

       /*
        * Set extended touch area to be used 
        */
        void UseExtendedTouchArea();
        
    private:        
    
        CFbsBitmap*         iBitmap;
        CFbsBitmap*         iMaskBitmap;
        TPoint              iStartPos;
        CVolumeExtension*   iExtension;
        TInt                iSpare1;
        TPoint              iBmpPos;
        TInt                iValue;
        TInt                iStyle;
    };

#endif        // AKNVOLUMECONTROL_H
