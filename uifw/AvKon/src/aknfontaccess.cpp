/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
*  Implementation of access to Series 60 font system for 3rd parties.
* 
*
*/

#include "AknFontAccess.h"

#include "avkon.hrh"
#include <aknenv.h>

#include <AknTextDecorationMetrics.h>
#include <AknFontSpecification.h>
#include <AknFontId.h>
#include <AknFontProvider.h>
#include "AknFontSpecificationLayoutFont.h"
#include "AknUtils.h"
#include "AknLayoutFont.h"
#include <AknFontProviderSuppliedMetrics.h>

#include <e32std.h>
#include <eikenv.h>
#include <gulicon.h>
#include <gulfont.h>

    /**
    * Generic font family name descriptors. These act as aliases to the real typefaces or typeface
    * families, if supported on the product.
    * Note: A 0-length descriptor can be used to obtain a default product font family.
    */
    _LIT(KAknFontFamilySansSerif,"SansSerif");
    _LIT(KAknFontFamilySerif,"Serif");
    _LIT(KAknFontFamilyMonospace,"Monospace");

LOCAL_C void MapFontFamilyToGenericAlias( AknFontAccess::TAknFontFamily aFontFamily, TTypeface& aTypeface)
    {

    // State a bias toward proportional. (Default value of TTypeface currently has slight bias toward Monospace)
    aTypeface.SetIsProportional(ETrue);
    
    switch( aFontFamily)
        {
    case AknFontAccess::EAknFontFamilySansSerif:
        aTypeface.iName = KAknFontFamilySansSerif;
        aTypeface.SetIsSerif(EFalse);
        break;
        
    case AknFontAccess::EAknFontFamilySerif:
        aTypeface.iName = KAknFontFamilySerif;
        aTypeface.SetIsSerif(ETrue);
        break;
        
    case AknFontAccess::EAknFontFamilyMonospace:
        aTypeface.iName = KAknFontFamilyMonospace;
        aTypeface.SetIsProportional(EFalse);
        break;
        
    case AknFontAccess::EAknFontFamilyNotSpecified: // fallthrough to default
    default:
        // Wipe name, but still with proportional attribute
        aTypeface.iName = KNullDesC;
        }
    }
    
EXPORT_C CFbsFont* AknFontAccess::GetFont(
        CBitmapDevice& aBitmapDevice, 
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        TAknFontFamily aFontFamily)
    {
    TTypeface typeface; // Buffer is just used for the typeface alias.
    MapFontFamilyToGenericAlias(aFontFamily, typeface);
    return DoGetFont( aBitmapDevice, aFontStyle, aFontSizeInTwips, typeface, ETrue);
    }
  
EXPORT_C CFbsFont* AknFontAccess::GetFont( 
        CBitmapDevice& aBitmapDevice, 
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        const TDesC& aFontFamilyName)
    {
    TTypeface typeface;
    typeface.iName = aFontFamilyName.Left(KMaxTypefaceNameLength);
    typeface.SetIsProportional(ETrue);
    return DoGetFont(aBitmapDevice, aFontStyle, aFontSizeInTwips, typeface, ETrue );
    }
    

EXPORT_C CFbsFont* AknFontAccess::GetClosestFont(
        CBitmapDevice& aBitmapDevice, 
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        TAknFontFamily aFontFamily)
    {
    TTypeface typeface; // Buffer is just used for the typeface alias.
    MapFontFamilyToGenericAlias(aFontFamily, typeface);
    return DoGetFont(aBitmapDevice, aFontStyle, aFontSizeInTwips, typeface, EFalse);
    }
    
EXPORT_C CFbsFont* AknFontAccess::GetClosestFont(
        CBitmapDevice& aBitmapDevice, 
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        const TDesC& aFontFamilyName)
    {
    TTypeface typeface;
    typeface.iName = aFontFamilyName.Left(KMaxTypefaceNameLength);
    typeface.SetIsProportional(ETrue);
    return DoGetFont(aBitmapDevice, aFontStyle, aFontSizeInTwips, typeface, EFalse );
    }

CFbsFont* AknFontAccess::DoGetFont(
    CBitmapDevice& aBitmapDevice,
    const TFontStyle aFontStyle, 
    TInt aFontSizeInTwips, 
    const TTypeface& aTypeface,
    TBool aExactMatchRequired)
    {                 
    TAknFontSpecification spec(KAknFontCategoryUndefined);
    spec.SetUnits(TAknFontSpecification::ETwips); // Causes implicit SetScalesInTwips(ETrue);
    spec.SetTextPaneHeightIsDesignHeight(ETrue);  // Suppresses "font size downscaling"
    spec.SetExactMatchRequired( aExactMatchRequired ); // Supresses fallbacks in FontProvider

    spec.SetTextPaneHeight(aFontSizeInTwips);
    spec.SetWeight( aFontStyle.StrokeWeight());
    spec.SetPosture( aFontStyle.Posture());

    // Unused interfaces:
    TAknFontProviderSuppliedMetrics suppliedMetrics;
    TInt fontProviderIndex;

    return AknFontProvider::CreateFontFromTypefaceAndMetrics (
        aBitmapDevice, aTypeface, spec, suppliedMetrics, fontProviderIndex );
    }
    
EXPORT_C CAknLayoutFont* AknFontAccess::CreateLayoutFontFromSpecificationL( 
        CBitmapDevice& aBitmapDevice,
        const TAknFontSpecification& aSpec )
    {
    return CAknFontSpecificationLayoutFont::NewL( aBitmapDevice, aSpec );
    }

EXPORT_C CAknLayoutFont* AknFontAccess::CreateLayoutFontFromSpecificationL( 
        CBitmapDevice& aBitmapDevice,
        const TTypeface& aTypeface, 
        const TAknFontSpecification& aSpec )
    {
    return CAknFontSpecificationLayoutFont::NewL( aBitmapDevice, aTypeface, aSpec );
    }

// End of file

