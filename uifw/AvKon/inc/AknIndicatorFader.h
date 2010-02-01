/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/
 

#ifndef AKNINDICATORFADER_H
#define AKNINDICATORFADER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CAknIndicatorContainer;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

// CLASS DECLARATION

/**
* This class is not intended for further derivation.
*
* @since 2.8
*
* @internal
*/
NONSHARABLE_CLASS(CAknIndicatorFader) : public CBase
    {
    public:
        enum TFadeEffect
            {
            EEffectNone,
            EEffectFadeToLeft,
            EEffectFadeToRight
            };


    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @since 2.8
        *
        * @return Newly constructed object.
        */
        static CAknIndicatorFader* NewL(TSize aSize);

        /**
        * Destructor.
        */
        virtual ~CAknIndicatorFader();

    public: // New functions
        
        CFbsBitmap* FadeMask(CFbsBitmap* aOriginalMask) const;
    
        void SetActiveFadeEffect(TInt aActiveEffect);

        void SetActiveFadeSize(TSize aSize);

    private:

        /**
        * C++ default constructor.
        */
        CAknIndicatorFader(TSize aSize);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();


        void CreateEffect(TInt aEffect);

        void InitializeL();

        TBool Initialized() const;


    private: // Data

        TSize              iSize;
        TInt               iActiveEffect;

        CFbsBitmap*        iFadingBitmap; // Used in fading
        CFbsBitmapDevice*  iFadingDevice;
        CFbsBitGc*         iFadingGc;
        
        CFbsBitmap*        iInvertingBitmap; // Used in inverting
        CFbsBitmapDevice*  iInvertingDevice;
        CFbsBitGc*         iInvertingGc;

        CFbsBitmap*        iInvertedBitmap; // Inverted bitmap
        CFbsBitmapDevice*  iInvertedDevice;
        CFbsBitGc*         iInvertedGc;

        CFbsBitmap*        iFadedBitmap; // Faded bitmap
        CFbsBitmapDevice*  iFaderDevice;
        CFbsBitGc*         iFaderGc;
    };

#endif // AKNINDICATORFADER_H

// End of File