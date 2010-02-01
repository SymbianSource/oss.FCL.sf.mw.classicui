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
*     Avkon uiklaf system font and system font array interfaces
*     
*
*/


#ifndef AKNSYSTEMFONT_H
#define AKNSYSTEMFONT_H

#include <s32std.h>

class CAknLayoutFont;
class CFont;

/**
* Avkon specific class that enables matching of font by Uid
* 
* This class has some peculiarities. It is the class which is forward declared in uiklaf as CLaySystemFont
* and used in C++ Templates in Uiklaf Interfaces. This is used as its "real" name. 
* 
* The class name CAknSystemFont is for Avkon identification. Clients should use "CAknSystemFont"
* 
* @since Series 60 3.0
* @internal
*/

NONSHARABLE_CLASS(CLafSystemFont) : public CBase
    {
public:
    /**
    * Create new system font array object fron an ID and the Avkon layout
    * font obtained from the UID
    * 
    * @param aUid   Uid that will uniquely match for this font
    * @param aFont  Avkon layout font to package up. The new object takes ownership.
    */
    IMPORT_C static CLafSystemFont* NewL(TUid aUid, CAknLayoutFont* aFont);
    
    /**
    * CBase-derived destructor
    */
    ~CLafSystemFont();
    
    /**
    * Access the font part of the object.
    *
    * @return the CFont contained in the object
    */
    IMPORT_C CFont* Font() const;
    
    /**
    * Access the Uid that is uniquely assigned to this font.
    *
    * @return the Uid that the system font was constructed with
    */
    IMPORT_C TUid Uid() const;
    
private:   
    CLafSystemFont(TUid aUid, CAknLayoutFont* aFont); // Takes ownership of the CAknLayoutFont
    TUid iUid;
    CAknLayoutFont* iFont;
    };

/**
* Use of this class as CAknSystemFont is encouraged by the means of this typedef.
*/
typedef CLafSystemFont CAknSystemFont;

#endif // AKNSYSTEMFONT_H
