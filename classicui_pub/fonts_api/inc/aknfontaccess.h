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
*  Access to Series 60 font system
* 
*
*/


#ifndef __AKNFONTACCESS_H__
#define __AKNFONTACCESS_H__

class CAknLayoutFont;
class CFbsFont;

#include <AknFontSpecification.h>

class AknFontAccess
    {
public:
    
    /**
    * Generic font family enumeration. These can be used in place of the family name descriptors
    */
    enum TAknFontFamily
        {
        EAknFontFamilyNotSpecified = 0,
        EAknFontFamilySansSerif,
        EAknFontFamilySerif,
        EAknFontFamilyMonospace
        };

public:

    /**
    * Returns a font that matches the metrics supplied. The provider can return a scaled 
    * or bitmap font as long as it meets the provided criteria. If an exact match isn't 
    * found then a null is returned.
    *
    * @since Series 60 release 2.8
    * 
    * @param aBitmapDevice Device for which the font will be requested 
    * @param aFontStyle of type TFontStyle. Use to set weight and posture of the font
    * @param aFontSize  Font size in twips. 
    * @param aFontFamily Font is one of the enumerations in TAknFontFamily
    *        Note that serif and sansSerif are proportional fonts 
    * 
    * @return A font pointer. CBitmapDevice::ReleaseFont must be called to release the font resource on the
    * device context when the font is no longer required. If an exact match isn't found NULL is returned
    */
    IMPORT_C static CFbsFont* GetFont(
        CBitmapDevice& aBitmapDevice,        
        const TFontStyle aFontStyle,
        TInt aFontSizeInTwips, 
        TAknFontFamily aFontFamily); 
    /**
    * Returns a font that matches the metrics supplied. The provider can return a scaled 
    * or bitmap font as long as it meets the provided criteria. If an exact match isn't 
    * found than a null is returned.
    *
    * @since Series 60 release 2.8
    * 
    * @param aBitmapDevice Device for which the font will be requested 
    * @param aFontStyle of type TFontStyle. Use to set weight and posture of the font
    * @param aFontSize Font size in twips. 
    * @param aFontFamilyname Font family is the text name of the font family and may be, for example:
    *               "courier", "helvetica", "times roman" etc. Font names are not case-sensitive. 
    * 
    * @return A font pointer. CBitmapDevice::ReleaseFont must be called to release the font resource on the
    * device context when the font is no longer required. If an exact match isn't found NULL is returned
    */
    IMPORT_C static CFbsFont* GetFont(
        CBitmapDevice& aBitmapDevice,        
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        const TDesC& aFontFamilyName); 
    /**
    * Returns a font that matches the metrics supplied. The provider can return a scaled 
    * or bitmap font as long as it meets the provided criteria. A best fit is used that 
    * is prioritized as follows: fontSize, fontStyle, fontFamily 
    * This will succeed as long as there is at least one font on the phone. 
    * @since Series 60 release 2.8
    * 
    * @param aBitmapDevice Device for which the font will be requested 
    * @param aFontStyle of type TFontStyle. Use to set weight and posture of the font
    * @param aFontSize Font size in twips. 
    * @param aFontFamily Font is one of the following emumerations values: 
    *         monospace, sansSerif, serif 
    *        Note that serif and sansSerif are proportional fonts 
    * 
    * @return A font pointer. CBitmapDevice::ReleaseFont must be called to release the font resource on the
    * device context when the font is no longer required.  A font is always returned.
    */
    IMPORT_C static CFbsFont* GetClosestFont(
        CBitmapDevice& aBitmapDevice,        
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        TAknFontFamily aFontFamily); 
    /**
    * Returns a font that matches the metrics supplied. The provider can return a scaled 
    * or bitmap font as long as it meets the provided criteria. A best fit is used that 
    * is prioritized as follows: fontSize, fontStyle, fontFamily 
    * This will succeed as long as there is at least one font on the phone.
    * @since Series 60 release 2.8
    * 
    * @param aBitmapDevice Device for which the font will be requested 
    * @param aFontStyle of type TFontStyle. Use to set weight and posture of the font
    * @param aFontSize Font size in twips. 
    * @param aFontFamilyname Font family is the text name of the font family and may be, for example:
    *               "courier", "helvetica", "times roman" etc. Font names are not case-sensitive. 
    * 
    * @return A font pointer. CBitmapDevice::ReleaseFont must be called to release the font resource on the
    * device context when the font is no longer required.  A font is always returned.
    */
    IMPORT_C static CFbsFont* GetClosestFont(
        CBitmapDevice& aBitmapDevice,        
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        const TDesC& aFontFamilyName); 
            
    /**
    * Return a fully constructed CAknLayoutFont object based upon the specification passed in.
    * The Avkon font specifiation object uses TAknFontCategory to determine the font. 
    *
    * The font object is returned as non-const, since it is owned and will eventually be deleted by the client.
    * 
    * This method can only be used for TAknFontSpecification objects that are stored in Pixels. 
    * (See TAknFontSpecification::Units() )
    *
    * @since Series 60 release 2.8
    * @param aBitmapDevice  Device for which the font is required (not used in 2.8; CEikonEnv::ScreenDevice() is used)
    * @param aSpec          Series 60 font specification object
    * @return               pointer to a CAknLayoutFont object, owned by the caller
    */
    IMPORT_C static CAknLayoutFont* CreateLayoutFontFromSpecificationL(
        CBitmapDevice& aBitmapDevice,   
        const TAknFontSpecification& aSpec );

    /**
    * Return a fully constructed CAknLayoutFont object based upon the typeface and specification passed in.
    * The TTypeface object contains a typeface name that is used as the primary key to select a font.  
    * The Series 60  font specifiation object is also used, but any value of TAknFontCategory passed in is reset to 
    * EAknFontCategoryUndefined, and is not used to select the font. 
    *
    * The font object is returned as non-const, since it is owned and will eventually be deleted by the client.
    * 
    * This method can only be used for TAknFontSpecification objects that are stored in Pixels
    * (See TAknFontSpecification::Units() )
    *
    * @since Series 60 release 2.8
    * @param aBitmapDevice  Device for which the font is required (not used in 2.8; CEikonEnv::ScreenDevice() is used)
    * @param aTypeface      Symbian Typface object
    * @param aSpec             Series 60 font specification object
    * @return                       pointer to a CAknLayoutFont object, owned by the caller
    */
    IMPORT_C static CAknLayoutFont* CreateLayoutFontFromSpecificationL(
        CBitmapDevice& aBitmapDevice,        
        const TTypeface& aTypeface, 
        const TAknFontSpecification& aSpec);

           
private:
    /**
    * Method containing all the real implementation for the GetFontXXX APIs
    */
    static CFbsFont* DoGetFont( 
        CBitmapDevice& aBitmapDevice,        
        const TFontStyle aFontStyle, 
        TInt aFontSizeInTwips, 
        const TTypeface& aFontFamilyTypeface,
        TBool aExactMatchRequired);                 
    };

#endif //  __AKNFONTACCESS_H__

// End of file









