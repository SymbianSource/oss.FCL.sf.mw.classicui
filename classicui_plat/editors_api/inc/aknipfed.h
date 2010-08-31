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
* Description:  The CAknIpFieldEditor class implements an editor for an 
*                IP address.
*
*/


#if !defined(__AKNIPFED_H_)
#define __AKNIPFED_H_

// INCLUDES
#include <eikmfne.h>

// FORWARD DECLERATIONS
class TInetAddr;

//CLASS DECLERATION
/**
 * The @c CAknIpFieldEditor class implements an editor for an IP address.
 * Based on Crystal @c CCknIpFieldEditor.
 * 
 * @since Series 60 0.9 
 */
class CAknIpFieldEditor : public CEikMfne 
    {
public: // public constructors

    /**
    * C++ default constructor.
    */
	IMPORT_C CAknIpFieldEditor();

    /**
    * Two phased constructor.
    * @param aMinimumAddress Reference to a @c TInetAddr struct. Defines lower 
    * limits for IP editor fields.
    * @param aMaximumAddress Reference to a @c TInetAddr struct. Defines upper 
    * limits for IP editor fields.
    * @param aInitialAddress Reference to a @c TInetAddr struct. Defines the 
    * initial address of the IP editor.
    * @param aFlags The number field's flags. Default is 0.
    * @return Pointer to the fully constructed @c CAknIpFieldEditor object.
    */
	void ConstructL(TInetAddr& aMinimumAddress,
                    TInetAddr& aMaximumAddress,
                    TInetAddr& aInitialAddress,
                    const TInt aFlags=0);

    /**
    * Two phased constructor.
    * Constructs a CAknIpFieldEditor object using given parameters.
    * @param aMinimumAddress Reference to a @c TInetAddr struct. Defines lower
    * limits for IP editor fields.
    * @param aMaximumAddress Reference to a @c TInetAddr struct. Defines upper
    * limits for IP editor fields.
    * @param aInitialAddress Reference to a @c TInetAddr struct. Defines the 
    * initial address of the IP editor.
    * @return Pointer to the fully constructed @c CAknIpFieldEditor object.
    */
	IMPORT_C static CAknIpFieldEditor* NewL(TInetAddr& aMinimumAddress,
                                            TInetAddr& aMaximumAddress,
                                            TInetAddr& aInitialAddress);
	
	/**
	* Two phased constructor.
	* Requires a call for @c ConstructFromResourcesL() method to finish 
	* construction.
	* @return Pointer to the constructed @c CAknIpFieldEditor object.
	*/
	IMPORT_C static CAknIpFieldEditor* NewL();
	
public: // Methods for getting and setting values

	        
    /**
 	* Sets the editor's value dynamically.
    * @param aAddress Reference to a @c TInetAddr struct including the new 
    * address.
    */
	IMPORT_C void SetAddress(const TInetAddr& aAddress);
	
    /**
    * Gets the editor's value.
    * @return TInetAddr struct including the address.
    */
	IMPORT_C TInetAddr Address() const;
	
	/**
    * Sets the minimum and maximum editor values.
    * @param aMinimumAddress Reference to a @c TInetAddr struct defining the
    * lower limits of the editor fields.
    * @param aMaximumAddress Reference to a @c TInetAddr struct defining the
    * upper limits of the editor fields.
    */
	IMPORT_C virtual void SetMinimumAndMaximum(
	                                    const TInetAddr& aMinimumAddress,
                                        const TInetAddr& aMaximumAddress); // only values inside the initial minimum and maximum are permitted

    /**
    * Gets the minimum and maximum editor values.
    * @param aMinimumAddress Reference to a @c TInetAddr struct in which the
    * lower limits are wanted to be returned.
    * @param aMaximumAddress Reference to a @c TInetAddr struct in which the
    * upper limits are wanted to be returned.
    */
	IMPORT_C virtual void GetMinimumAndMaximum(
	                                    TInetAddr& aMinimumAddress,
                                        TInetAddr& aMaximumAddress) const;
    
    /**
    * Gets an IP address from resources.
    * @param aResourceReader  Reference to a resource reader associated to the
    * @c IP_FIELD resource.
    * @return TInetAddr struct including the address.
    */
	IMPORT_C TInetAddr ReadIPAddress(TResourceReader& aResourceReader);
	
public: // from CCoeControl

	/**
    * From @c CCoeControl. Constructs controls from a resource file.
    * Essential for Dialog/Form construction.
    * @param aResourceReader The resource reader with which to access 
    * @c IP_FIELD_EDITOR
    * resource.
    */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	
	/**
    * From @c CCoeControl. Handles key events.
    * Called by framework when a key event occurs.
    * @param aKeyEvent The key event that occured.
	* @param aType The type of key event that occured.
    * @return @c EKeyWasConsumed if the event was processed, 
    * @c EKeyWasNotConsumed if the event was not processed
    */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
	                                     TEventCode aType);
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
   void SplitAddressIntoFields(
                                const TInetAddr& aAddress,
                                TUint8 &aFieldA,
                                TUint8 &aFieldB,
                                TUint8 &aFieldC,
                                TUint8 &aFieldD) const;
	IMPORT_C virtual void CEikMfne_Reserved();

private:
    TInt iSpare;
    TInt iSpare2;
	};


#endif
