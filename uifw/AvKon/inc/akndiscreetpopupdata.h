/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Global discreet popup data class.
*
*/

#ifndef T_AKNDISCREETPOPUPDATA_H
#define T_AKNDISCREETPOPUPDATA_H

#include <AknsConstants.h>

const TInt KMaxTextSize( 100 );

/**
 *  Class for storing global discreet popup data.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupData )
    {

public:
    
    /** Popup data type definition. */
    enum TAknDiscreetPopupDataType
        {
        EAknPopupTypeUndefined = 1,
        EAknPopupTypeParam,
        EAknPopupTypeResource,
        EAknPopupTypeCancelRequest,
        EAknPopupTypeQueryInUseRect
        };

    /**
     * C++ constructor.
     */
    inline TAknDiscreetPopupData();

    /**
     * Provides popup data type.
     */
    inline const TInt Type();

protected:

    /**
     * Popup data type.
     */
    TInt iType;

    };


/**
 *  Discreet popup request cancellation data class.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupCancelRequestData ) : public TAknDiscreetPopupData
    {

public:

    /**
     * C++ constructor.
     */
    inline TAknDiscreetPopupCancelRequestData();

    /**
     * Returns request status handle.
     * 
     * @return Request status handle.
     */
    inline const TUint& StatusHandle();

    /**
     * Sets request status handle.
     * 
     * @param aHandle Request status handle.
     */
    void SetStatusHandle( const TUint& aHandle );

private:

    /**
     * Request status handle.
     */
    TUint iStatusHandle;

    };


/**
 *  Super class for global discreet popup data classes.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupLaunchData ) : public TAknDiscreetPopupData
    {
    
public:
    

    /**
     * Provides app uid.
     * 
     * @return App uid.
     */
    inline const TUid& AppUid();

    /**
     * Provides view uid.
     * 
     * @return View uid.
     */
    inline const TUid& ViewUid();

    /**
     * Returns ETrue if popup has action when tapped.
     * 
     * @return ETrue if popup has action when tapped.
     */
    inline const TBool& Action();

    /**
     * Provides popup id.
     * 
     * @return Popup id.
     */
    inline const TInt PopupId();

    /**
     * Sets app uid.
     * 
     * @param aAppUid App uid.
     */
    void SetAppUid( const TUid& aAppUid );

    /**
     * Sets view uid.
     * 
     * @param aViewUid View uid.
     */
    void SetViewUid( const TUid& aViewUid );

    /**
     * Sets action parameter.
     * 
     * @param aAction ETrue if popup has action when tapped.
     */
    void SetAction( const TBool& aAction );

    /**
     * Sets popup id.
     * 
     * @param aPopupId Popup id.
     */
    void SetPopupId( const TInt& aPopupId );
    

private:

    /**
     * Application uid.
     */
    TUid iAppUid;

    /**
     * View uid.
     */
    TUid iViewUid;

    /**
     * ETrue if popup has action when tapped.
     */
    TBool iAction;

    /**
     * Unique popup id.
     */
    TInt iPopupId;

    };


/**
 *  Class for storing global discreet popup parameter data.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupParamData ) : public TAknDiscreetPopupLaunchData
    {
    
public:

    /**
     * C++ constructor.
     */
    inline TAknDiscreetPopupParamData();

    /**
     * Provides title text.
     * 
     * @return Title text.
     */
    inline const TDesC& TitleText();

    /**
     * Provides body text.
     * 
     * @return Body text.
     */
    inline const TDesC& BodyText();

    /**
     * Provides skin id.
     * 
     * @return Skin id.
     */
    inline const TAknsItemID& SkinId();

    /**
     * Provides bitmap file.
     * 
     * @return Bitmap file.
     */
    inline const TDesC& BitmapFile();

    /**
     * Provides bitmap id.
     * 
     * @return Bitmap id.
     */
    inline const TInt BitmapId();

    /**
     * Provides mask id.
     * 
     * @return Mask id.
     */
    inline const TInt MaskId();

    /**
     * Provides flags.
     * 
     * @return Flags.
     */
    inline const TInt Flags();

    /**
     * Sets title text.
     * 
     * @param aTitleText Title text.
     */
    void SetTitleText( const TDesC& aTitleText );
    
    /**
     * Sets body text.
     * 
     * @param aBodyText Body text.
     */
    void SetBodyText( const TDesC& aBodyText );

    /**
     * Sets skin id.
     * 
     * @param aBodyText Skin id.
     */
    void SetSkinId( const TAknsItemID& aSkinId );

    /**
     * Sets bitmap file.
     * 
     * @param aBitmapFile Bitmap file.
     */
    void SetBitmapFile( const TDesC& aBitmapFile );

    /**
     * Sets bitmap id.
     * 
     * @param aBitmapId Bitmap id.
     */
    void SetBitmapId( const TInt& aBitmapId );

    /**
     * Sets mask id.
     * 
     * @param aMaskId Mask id.
     */
    void SetMaskId( const TInt& aMaskId );

    /**
     * Sets flags.
     * 
     * @param aFlags Flags.
     */
    void SetFlags( const TInt& aFlags );

private:

    /**
     * Title text.
     */
    TBuf<KMaxTextSize> iTitleText;
    
    /**
     * Body text.
     */
    TBuf<KMaxTextSize> iBodyText;
    
    /**
     * Skin id.
     */
    TAknsItemID iSkinId;
    
    /**
     * Bitmap file.
     */
    TFileName iBitmapFile;
    
    /**
     * Bitmap id.
     */
    TInt iBitmapId;
    
    /**
     * Mask id.
     */
    TInt iMaskId;
    
    /**
     * Flags.
     */
    TInt iFlags;

    };

/**
 *  Class for storing global discreet popup resource data.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupResourceData ) : public TAknDiscreetPopupLaunchData
    {

public:
    
    /**
     * C++ constructor.
     */
    inline TAknDiscreetPopupResourceData();

    /**
     * Provides resource file.
     * 
     * @return Resource file.
     */
    inline const TDesC& ResourceFile();

    /**
     * Provides resource id.
     * 
     * @return Resource id.
     */
    inline const TInt ResourceId();

    /**
     * Sets resource file.
     * 
     * @param aResourceFile Resource file.
     */
    void SetResourceFile( const TDesC& aResourceFile );

    /**
     * Sets resource id.
     * 
     * @param aResourceId Resource id.
     */
    void SetResourceId( const TInt& aResourceId );

private:

    /**
     * Resource file.
     */
    TFileName iResourceFile;

    /**
     * Resource id.
     */
    TInt iResourceId;

    };

/**
 *  Class for storing in use global discreet popup rectangle data.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( TAknDiscreetPopupRectData ) : public TAknDiscreetPopupData
    {

public:
    
    /**
     * C++ constructor.
     */
    inline TAknDiscreetPopupRectData(const TRect& aRect);

    inline const TRect Rect();
        
private:
    
    TRect iRect;

    };

#include "akndiscreetpopupdata.inl"

#endif // T_AKNDISCREETPOPUPDATA_H
// End of File
