/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Location editors 
*
*/

#ifndef AKNLOCATIONED_H
#define AKNLOCATIONED_H

#include <eikmfne.h>

class TPosition;
class CLocationStrings;
/**
 * Editor for TPosition type; latitude and longitude editor
 *
 * There exists two ways to construct CAknLocationEditor:
 *
 * @code
 * CAknLocationEditor *editor = CAknLocationEditor::NewL(pos, context);
 * @endcode
 * 
 * Using resources:
 *
 * @code
 * CAknLocationEditor *editor = new (ELeave) CAknLocationEditor
 * TResourceReader reader;
 * iCoeEnv->CreateResourceReaderLC(reader,R_RES_ID_FOR_EDITOR);
 * editor->ConstructFromResourceL(reader);
 * editor->Set(pos);
 * CleanupStack::PopAndDestroy();
 * @endcode
 * 
 * Resource file format is as follows:
 * @code
 *     LATITUDE_EDITOR
 *        {
 *	      flags = ELocationEdFlagLatitude;
 *		  latlongresourceid = R_EIK_LATITUDE_AND_LONGITUDE;
 *        };
 * @endcode
 *  or:
 * @code
 *      LONGITUDE_EDITOR
 *        {
 *		  flags = ELocationEdFlagLongitude;
 *		  latlongresourceid = R_EIK_LATITUDE_AND_LONGITUDE;
 *        };
 * @endcode
 *
 *  @lib eikctl.lib
 *  @lib lbs.lib (for TPosition class)
 *  @since 3.2
 *  @see TPosition
 */
class CAknLocationEditor : public CEikMfne
	{
public:
	/**
	 * TLocationContext determines what part of TPosition class is used for this editor.
     *  ELongitudeOnly means only longitude part of TPosition is used.
     *  ELatitudeOnly means only latitude part of TPosition is used.
	 */
	enum TLocationContext
		{
		ELongitudeOnly = 0x1,
		ELatitudeOnly  = 0x2
		};
    /**
     * Constructor
     */
	IMPORT_C CAknLocationEditor();
    /**
     * Destructor
     */
	IMPORT_C ~CAknLocationEditor();
    /**
     * NewL()
     *    Creates location editor and initializes it's value to value determined by the aValue parameter.
	 *
     * @param aValue Initial value for location editor.
     * @param aContext Which part of the TPosition is used for this location editor
     */
	IMPORT_C static CAknLocationEditor* NewL( TPosition &aValue, TLocationContext aContext );

	/**
	 * ConstructFromResourceL
     *     Constructs location editor using information from resource files
     *
     * @param aResourceReader resource reader
	 */
	IMPORT_C void ConstructFromResourceL( TResourceReader& aResourceReader );

	/**
	 * DisplayableLocationL()
	 *    Converts TPosition into displayable descriptor usable for listboxes
     *
	 * @param aValue value of the location
	 * @param aContext which part of the TPosition is used
	 */
	IMPORT_C static HBufC* DisplayableLocationL( const TPosition &aValue, TLocationContext aContext );


    /**
     * PrepareForFocusLossL()
     *     detects focus changes to validate editor contents
     */
	IMPORT_C virtual void PrepareForFocusLossL();

	/**
     * Set()
     *     Sets either longitude or latitude values of aValue
     *
	 *  @param aValue new value for the editor
     */
	IMPORT_C void Set(const TPosition &aValue);
	/**
	 * Get()
     *      Gets either longitude or latitude values of aValue
     *
     * @param aValue TPosition object that will be modified
     */
	IMPORT_C void Get( TPosition &aValue ) const;
	/**
	 * OfferKeyEventL()
	 *         key event handling of location editor
	 */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
private:
	enum TLocationType
		{
		EDD,
		EDMM,
		EDMSD
		};
	TLocationType Type() const;
	static void Split( const TPosition &aValue, 
					   TLocationContext aContext, 
					   TInt &aDegrees, 
					   TInt &aDeciDegrees, 
					   TInt &aMinutes, 
					   TInt &aDeciMinutes, 
					   TInt &aSeconds, 
					   TInt &aDeciSeconds, 
					   TBool &aNeg, 
					   TBool &aNan );
	static void SplitDD( const TPosition &aValue, 
						 TLocationContext aContext, 
						 TInt &aDegrees,
						 TInt &aDeciDegrees, 
						 TBool &aNeg, 
						 TBool &aNan );
	static void SplitDMM( const TPosition &aValue, 
	                      TLocationContext aContext, 
	                      TInt &aDegrees, 
	                      TInt &aMinutes, 
	                      TInt &aDeciMinutes, 
	                      TBool &aNeg, 
	                      TBool &aNan );
	static void SplitDMSD( const TPosition &aValue, 
						   TLocationContext aContext, 
						   TInt &aDegrees, 
						   TInt &aMinutes, 
						   TInt &aSeconds, 
						   TInt &aDeciSeconds, 
						   TBool &aNeg, 
						   TBool &aNan );
	static void CombineDD( TPosition &aValue, 
						   TLocationContext aContext, 
						   TInt aDegrees, 
						   TInt aDeciDegrees, 
						   TBool aNeg, 
						   TBool aNan );
	static void CombineDMM( TPosition &aValue, 
							TLocationContext aContext, 
							TInt aDegrees, 
							TInt aMinutes, 
							TInt aDeciMinutes, 
							TBool aNeg, 
							TBool aNan );
	static void CombineDMSD( TPosition &aValue, 
							 TLocationContext aContext, 
							 TInt aDegrees, 
							 TInt aMinutes, 
							 TInt aSeconds, 
							 TInt aDeciSeconds, 
							 TBool aNeg, 
							 TBool aNan );
private:
	void SetUninitialised(TBool aInitialised);
	void RefreshFromLocale();
	void ConstructL( TPosition &aValue, TLocationContext aContext );
public:
	void HandleCenRepChangedL(TUint32 aKey, TInt aValue);
	void CreateMfneFieldsL(const TPosition &aValue);
private:
	void LoadStringsL( TInt aResourceId );
	
	/**
	* Maps logical MFNE field order to correct visual order.
	* @param aFieldNumber Field position in logical format.
	* @param aType Used location editor format.
	* @return Field position in visual format.
	*/
	TInt FieldMapping(const TInt aFieldNumber, const TLocationType aType) const;

protected:
	IMPORT_C virtual void* CAknLocationEditor_ExtensionInterface( TUid aInterface ); 
private:
	CLocationStrings* iStrings;
	TLocationContext iContext;
	};


#endif