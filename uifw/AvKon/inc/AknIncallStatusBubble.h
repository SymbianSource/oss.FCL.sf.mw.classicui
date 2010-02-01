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
*     Declares container control for application.
*
*/


#ifndef INCALLSTATUSBUBBLE_H
#define INCALLSTATUSBUBBLE_H

// INCLUDES
#include <coecntrl.h>
#include <avkon.hrh>

#include <callstatus.mbg>

#include    <AknsItemID.h>
#include    <AknsConstants.h>
#include    <AknsItemData.h>
   
// FORWARD DECLARATIONS
class CIncallAnim;
class CEikImage;
class CIncallMuted;

// CLASS DECLARATION

/**
*  CIncallStatusBubble  container control class.
*  
*/
NONSHARABLE_CLASS(CIncallStatusBubble) : public CCoeControl
    {
    public:
        
    /**
    *   Bit             Explanation
    *   0 and 1         Call state
    *   2               No Ciphering
    *   3               Is muted               
    *   4               Is Visible
    *   5               Is a Fax       
    *   6               Is a Data call  
    *   7               Is a Hscsd data call  
    *   8               Line 2 indication
    *   9               Is a Video call
    *   10              Is an emergency call
    *   11              Is a VoIP call
    *   12              Is a full screen touch input window show
    *   12              Is a full screen touch input window Hide

    *   ...
    *   ...
    *   31              Reserved for incall bubble notifier internal use. 
    */
    enum TCallStatusBubbleFlags 
        {
        ESBAlerting     = EAknStatusBubbleAlerting,     //  One of
        ESBActive       = EAknStatusBubbleActive,       //  these
        ESBOnHold       = EAknStatusBubbleOnHold,       //  to set 
        ESBDisconnected = EAknStatusBubbleDisconnected, //  the call state  
        ESBNoCiphering  = EAknStatusBubbleNoCiphering,      
        ESBMuted        = EAknStatusBubbleMuted,
        ESBVisible      = EAknStatusBubbleVisible,
        ESBFax          = EAknStatusBubbleFax,
        ESBData         = EAknStatusBubbleData,
        ESBDataHscsd    = EAknStatusBubbleDataHscsd,
        ESBLine2        = EAknStatusBubbleLine2,
        ESBVideo        = EAknStatusBubbleVideo,
        ESBEmergency    = EAknStatusBubbleEmergency,    
        ESBVoIPCall     = EAknStatusBubbleVoIP,          
        ESBTouchShow    = EAknStatusBubbleInputShow,
        ESBTouchHide    = EAknStatusBubbleInputHide,
        
        ESBReservedInternal = EAknStatusBubbleReservedInternal         
        };

    public: // Constructors and destructor

        /**
        * Constructor
        * @aRect Used rectangle
        * @return New instance
        */
        static CIncallStatusBubble* NewL( const TRect& aRect );

        /**
        * Destructor.
        */
        ~CIncallStatusBubble();

    public: // New functions

        /**
        * Use this function to set the state of the bubble
        * @param aFlags Bits that define the outlook.
        */
        void SetFlags( const TInt& aFlags );

        /**
        * Use this function to get the state of the bubble
        * @return Bits that define the outlook.
        */
    #ifdef __WINS__
        const TInt Flags();
    #else
    	TInt Flags();
    #endif

        /**
        * Fades incall status bubble window group.
        *
        * @param aFaded Fade state to be set.
        */
        void SetFaded(TBool aFaded);

        /**
        * Gets given image (skinned if possible)
        * @param aImage This is where the bitmaps are set.
        * @param aImageId Id of the bitmap (see enum in AknIncallStatusBubble.h)
        * @param aImageMaskId Id of mask. KErrNotFound(-1) stands for 
        *                     no mask.
        */ 
        void GetImage( 
            CEikImage& aImage, 
            const TInt& aImageId,
            const TInt aImageMaskId = KErrNotFound );

    public: // Functions from base classes

        /**
        * Use this function to set the place of the bubble
        * @param aRect A rectangle which define the drawing area.
        */
        void SetRect( const TRect& aRect );

        /**
        * From CCoeControl,HandleResourceChange.
        */
        void HandleResourceChange( TInt aType );

        /**
        * From CCoeControl,HandlePointerEventL.
        */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    private: // Functions from base classes

        /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

        /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl,Draw.
        */
        void Draw( const TRect& aRect ) const;

       
    private: //new functions

        // Data
        struct SSkinnedImage
            {
            public:
                SSkinnedImage(): iId( KAknsIIDNone ), iItemData( NULL ) {}
                ~SSkinnedImage() { delete iItemData; }

            public:
                TAknsItemID iId;
                CAknsItemData* iItemData;
            };


        CIncallStatusBubble();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Loads images into cache.
        */
        void LoadImagesL();

        /**
        * Creates new CEikImage instance
        * @return New instance. Ownership given.
        */
        CEikImage* CreateNewEikImageL() const;

        /**
        * Selects used bitmaps according the state flags.
        */
        void SelectImages();
        
        /**
        * Maps bitmap enumeration into skin id
        * @param aBmIcon Bitmap enumeration from AknIncallStatusBubble.h
        * @param aID Skinned ID.
        */
        static void MapEnumToSkin( 
            const TInt aBmIcon, TAknsItemID& aID );

        /**
        * Gets skin data for given ID
        * @param aBmIcon Bitmap enumeration from AknIncallStatusBubble.h
        * return Skin data. NULL if not found.
        */
        CAknsItemData* GetSkinForIcon( const TInt aBmIcon );

        /**
        * Allocated new skinned image into the cache. Leaves in OOM case.
        * @param aId Skin id.
        * @return Skin data.
        */
        CAknsItemData* LoadAndAppendSkinL( const TAknsItemID& aId );

        /**
        * Sets skin to image if found.
        * @param aImage Used image.
        * @param aBmIcon Bitmap enumeration from CallStatus.mbg
        * @return Was skin set? ETrue if skin found and set. Else EFalse.
        */
        TBool GetSkin( CEikImage& aImage, const TInt aBmIcon );

        /**
        * Comparision function for two skin item
        */
        static TInt CompareSkinnedData( 
            const SSkinnedImage& aSkin1, 
            const SSkinnedImage& aSkin2 );

        /**
        * Loads a non-masked image and appends it in the image array.
        */
        void LoadImageL( TInt aBitmapId );

        /**
        * Loads a masked image and appends it in the image array.
        */
        void LoadImageL( TInt aBitmapId, TInt aMaskId );

        /**
        * Creates color skinned bitmap.
        */
        CFbsBitmap* CreateSkinnedColourBitmapL();

    private: //data
      
        TInt                        iFlags;

        CArrayPtrFlat<CFbsBitmap>*  iBitmaps;

        RWindowGroup                iMyWindowGroup;

        CEikImage*                  iSmallCallIndication;
        CIncallAnim*                iSmallIndiAnim;
        CEikImage*                  iBubble;
        CEikImage*                  iTypeIndication1;
        CEikImage*                  iTypeIndication2;
        CEikImage*                  iCyphOffIcon;

        CIncallMuted*               iMutedIcon;

        RPointerArray<SSkinnedImage> iSkins;
        TLinearOrder<SSkinnedImage> iOrder;
        CFbsBitmap* iSkinnedColourBitmap;
        TBool iPressedDown;         // Whether we've pressed down the incall bubble. 
    };

#endif // INCALLSTATUSBUBBLE_H

// End of File
