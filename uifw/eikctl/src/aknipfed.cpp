/*
* Copyright (c) 1999 Nokia Corporation and/or its subsidiary(-ies).
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



#include <basched.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikmsg.h>
#include <aknipfed.h>
#include <in_sock.h>
#include <gulfont.h>
#include <avkon.hrh>
#include <AknUtils.h>
#include <aknextendedinputcapabilities.h>
#include <AknTasHook.h> // for testability hooks


//
// CAknIpFieldEditor
//


const TInt KNumAddressFields=4;
const TInt KNumDelimiterFields=3;
const TInt KFieldA=0;
const TInt KFieldB=2;
const TInt KFieldC=4;
const TInt KFieldD=6;
// const TInt KTotalNumChars=15;// IPv4 is 4x3 numbers + 3x1 delimiter

_LIT(KDelimiter, "."); // In IPv4 the delimiter is always a dot


/**
 * Public method for constructing a CAknIpFieldEditor object.
 * Gets four parameters:
 * TInetAddr& aMinimumFieldValues - Reference to a TInetAddr struct. Defines lower limits for
 * IP editor fields.
 * TInetAddr& aMaximumFieldValues - Reference to a TInetAddr struct. Defines upper limits for
 * IP editor fields.
 * TInetAddr& aInitialAddress - Reference to a TInetAddr struct. Defines the initial address
 * the IP editor.
 * 
 */
EXPORT_C CAknIpFieldEditor* CAknIpFieldEditor::NewL(TInetAddr& aMinimumFieldValues,
                                                    TInetAddr& aMaximumFieldValues,
                                                    TInetAddr& aInitialAddress)
    {
    CAknIpFieldEditor* editor=new(ELeave)CAknIpFieldEditor;
    CleanupStack::PushL(editor);
    editor->ConstructL(aMinimumFieldValues,aMaximumFieldValues,aInitialAddress);
    CleanupStack::Pop(); // editor
    AKNTASHOOK_ADDL( editor, "CAknIpFieldEditor" );
    return editor;
    }

/**
 * Public method for constructing a CAknIpFieldEditor object. Requires a call for
 * ConstructFromResourcesL method to finish construction.
 * 
 */
EXPORT_C CAknIpFieldEditor* CAknIpFieldEditor::NewL()
    {
    CAknIpFieldEditor* editor=new(ELeave)CAknIpFieldEditor;
    AKNTASHOOK_ADDL( editor, "CAknIpFieldEditor" );
    return editor;
    }

EXPORT_C CAknIpFieldEditor::CAknIpFieldEditor()
	{
	}

void CAknIpFieldEditor::ConstructL(TInetAddr& aMinimumFieldValues,
                                   TInetAddr& aMaximumFieldValues,
                                   TInetAddr& aInitialAddress,
                                   const TInt aFlags)
	{
    TInt numFields=KNumAddressFields+KNumDelimiterFields;
	CreateFieldArrayL(numFields); // MFNE with 7 fields

    TUint8 minValueFieldA=0;
    TUint8 minValueFieldB=0;
    TUint8 minValueFieldC=0;
    TUint8 minValueFieldD=0;

    TUint8 maxValueFieldA=0;
    TUint8 maxValueFieldB=0;
    TUint8 maxValueFieldC=0;
    TUint8 maxValueFieldD=0;
        
    TUint8 initialValueFieldA=0;
    TUint8 initialValueFieldB=0;
    TUint8 initialValueFieldC=0;
    TUint8 initialValueFieldD=0;
        
    SplitAddressIntoFields(aMinimumFieldValues, minValueFieldA, minValueFieldB, minValueFieldC, minValueFieldD);
    SplitAddressIntoFields(aMaximumFieldValues, maxValueFieldA, maxValueFieldB, maxValueFieldC, maxValueFieldD);
    SplitAddressIntoFields(aInitialAddress, initialValueFieldA, initialValueFieldB, initialValueFieldC, initialValueFieldD);

    // Set each number field to the correct minimum, maximum and initial values
    CEikMfneField* field;
    field=CEikMfneNumber::NewL(*Font(),
                               minValueFieldA,
                               maxValueFieldA,
                               initialValueFieldA,
                               aFlags);
    AddField(field);

    HBufC* delimiterText=HBufC::NewLC(3);
    delimiterText->Des().Append(KDelimiter);
    AddField(CEikMfneSeparator::NewL(delimiterText));
    CleanupStack::Pop(); // delimiterText

    field=CEikMfneNumber::NewL(*Font(),
                               minValueFieldB,
                               maxValueFieldB,
                               initialValueFieldB,
                               aFlags);
    AddField(field);

    delimiterText=HBufC::NewLC(1);
    delimiterText->Des().Append(KDelimiter);
    AddField(CEikMfneSeparator::NewL(delimiterText));
    CleanupStack::Pop(); // delimiterText

    field=CEikMfneNumber::NewL(*Font(),
                               minValueFieldC,
                               maxValueFieldC,
                               initialValueFieldC,
                               aFlags);
    AddField(field);

    delimiterText=HBufC::NewLC(1);
    delimiterText->Des().Append(KDelimiter);
    AddField(CEikMfneSeparator::NewL(delimiterText));
    CleanupStack::Pop(); // delimiterText
    
    field=CEikMfneNumber::NewL(*Font(),
                               minValueFieldD,
                               maxValueFieldD,
                               initialValueFieldD,
                               aFlags);
    AddField(field);

	SetMinimumAndMaximum(aMinimumFieldValues, aMaximumFieldValues);
	
	MObjectProvider* mop = InputCapabilities().ObjectProvider();
	
	if ( mop )
	    {
	    CAknExtendedInputCapabilities* extendedInputCapabilities =
	        mop->MopGetObject( extendedInputCapabilities );
	    
	    if ( extendedInputCapabilities ) 
	        {
	        extendedInputCapabilities->SetCapabilities(
	            CAknExtendedInputCapabilities::ESupportsOnlyASCIIDigits );
	        }
	    }
	}

/**
 * Method for getting editor fields' minimum and maximum values.
 * Gets two parameters:
 * TInetAddr& aMinimumFieldValues - Reference to a TInetAddr struct in which the lower limits
 * are wanted to be returned.
 * IP editor fields.
 * TInetAddr& aMaximumFieldValues - Reference to a TInetAddr struct in which the upper limits
 * are wanted to be returned.
 * 
 */
EXPORT_C void CAknIpFieldEditor::GetMinimumAndMaximum(TInetAddr& aMinimumFieldValues,
                                                      TInetAddr& aMaximumFieldValues) const
	{
    TInt firstFieldMin;
    TInt firstFieldMax;
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldA)))->GetMinimumAndMaximum(firstFieldMin,firstFieldMax);
    TInt secondFieldMin;
    TInt secondFieldMax;
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldB)))->GetMinimumAndMaximum(secondFieldMin,secondFieldMax);
    TInt thirdFieldMin;
    TInt thirdFieldMax;
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldC)))->GetMinimumAndMaximum(thirdFieldMin,thirdFieldMax);
    TInt fourthFieldMin;
    TInt fourthFieldMax;
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldD)))->GetMinimumAndMaximum(fourthFieldMin,fourthFieldMax);

	aMinimumFieldValues=TInetAddr(INET_ADDR((TUint32)firstFieldMin,
                                            (TUint32)secondFieldMin,
                                            (TUint32)thirdFieldMin,
                                            (TUint32)fourthFieldMin),
                                  0);
	aMaximumFieldValues=TInetAddr(INET_ADDR((TUint32)firstFieldMax,
                                            (TUint32)secondFieldMax,
                                            (TUint32)thirdFieldMax,
                                            (TUint32)fourthFieldMax),
                                  0);
	}

/**
 * Method for setting editor fields' minimum and maximum values.
 * Gets two parameters:
 * TInetAddr& aMinimumFieldValues - Reference to a TInetAddr struct defining the lower limits
 * of the editor fields.
 * IP editor fields.
 * TInetAddr& aMaximumFieldValues - Reference to a TInetAddr struct defining the upper limits
 * of the editor fields.
 * 
 */
EXPORT_C void CAknIpFieldEditor::SetMinimumAndMaximum(const TInetAddr& aMinimumFieldValues,
                                                      const TInetAddr& aMaximumFieldValues)
	{
    TUint8 minValueFieldA=0;
    TUint8 minValueFieldB=0;
    TUint8 minValueFieldC=0;
    TUint8 minValueFieldD=0;
    TUint8 maxValueFieldA=0;
    TUint8 maxValueFieldB=0;
    TUint8 maxValueFieldC=0;
    TUint8 maxValueFieldD=0;
        
    SplitAddressIntoFields(aMinimumFieldValues, minValueFieldA, minValueFieldB, minValueFieldC, minValueFieldD);
    SplitAddressIntoFields(aMaximumFieldValues, maxValueFieldA, maxValueFieldB, maxValueFieldC, maxValueFieldD);
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldA)))->SetMinimumAndMaximum(minValueFieldA,maxValueFieldA,*Font());
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldB)))->SetMinimumAndMaximum(minValueFieldB,maxValueFieldB,*Font());
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldC)))->SetMinimumAndMaximum(minValueFieldC,maxValueFieldC,*Font());
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldD)))->SetMinimumAndMaximum(minValueFieldD,maxValueFieldD,*Font());
        
    DrawNow();
	}

/**
 * Method takes a TInetAddr and returns 4 separate 8-bit unsigned fields
 * const TInetAddr& aAddress - Reference to a TInetAddr struct
 * 
 */
void CAknIpFieldEditor::SplitAddressIntoFields(
                                                const TInetAddr& aAddress,
                                                TUint8 &aFieldA,
                                                TUint8 &aFieldB,
                                                TUint8 &aFieldC,
                                                TUint8 &aFieldD) const

    {
    TUint32 temp=0;
        
    temp=((aAddress.Address())&KInetAddrNetMaskA)>>KInetAddrShiftA;
    aFieldA=(TUint8)temp;


    temp=((aAddress.Address())&KInetAddrNetMaskB&~KInetAddrNetMaskA)>>KInetAddrShiftB;
    aFieldB=(TUint8)temp;

 
    temp=((aAddress.Address())&KInetAddrNetMaskC&~KInetAddrNetMaskB)>>KInetAddrShiftC;
    aFieldC=(TUint8)temp;


    temp=(aAddress.Address())&~KInetAddrNetMaskC;
    aFieldD=(TUint8)temp;
    }
/**
 * Method for setting the editor fields dynamically.
 * Gets one parameter:
 * const TInetAddr& aAddress - Reference to a TInetAddr struct including the new address.
 * 
 */
EXPORT_C void CAknIpFieldEditor::SetAddress(const TInetAddr& aAddress)
	{
    TUint8 fieldA=0;
    TUint8 fieldB=0;
    TUint8 fieldC=0;
    TUint8 fieldD=0;

    SplitAddressIntoFields(aAddress, fieldA, fieldB, fieldC, fieldD);
    
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldA)))->SetValue(fieldA,*Font());
	(STATIC_CAST(CEikMfneNumber*,Field(KFieldB)))->SetValue(fieldB,*Font());
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldC)))->SetValue(fieldC,*Font());
    (STATIC_CAST(CEikMfneNumber*,Field(KFieldD)))->SetValue(fieldD,*Font());
    DrawNow();
	}

/**
 * Method for reading the editor value.
 * 
 */
EXPORT_C TInetAddr CAknIpFieldEditor::Address() const
	{
    // TE: The return value can not be a const reference because the
    // TInetAddress that is to be returned exists only withing this function.
    return TInetAddr(INET_ADDR((TUint8)(STATIC_CAST(CEikMfneNumber*,Field(KFieldA)))->Value(),
                               (TUint8)(STATIC_CAST(CEikMfneNumber*,Field(KFieldB)))->Value(),
                               (TUint8)(STATIC_CAST(CEikMfneNumber*,Field(KFieldC)))->Value(),
                               (TUint8)(STATIC_CAST(CEikMfneNumber*,Field(KFieldD)))->Value()),
                     0);
	}

/**
 * Method for constructing the control from resources.
 * Gets one parameter:
 * TResourceReader& aResourceReader - Reference to a resource reader associated to a
 * IP Field Editor control resource.
 * 
 */
EXPORT_C void CAknIpFieldEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
	{
    TInetAddr minFieldValues=ReadIPAddress(aResourceReader);
	TInetAddr maxFieldValues=ReadIPAddress(aResourceReader);
    TUint32 flags=aResourceReader.ReadUint8();
	ConstructL(minFieldValues, maxFieldValues, minFieldValues, flags);
	}

/**
 * Method for reading an IP address from resources.
 * Gets one parameter:
 * TResourceReader& aResourceReader - Reference to a resource reader associated to the
 * IP address resource.
 * 
 */
EXPORT_C TInetAddr CAknIpFieldEditor::ReadIPAddress(TResourceReader& aResourceReader)
	{
	TUint8 firstField=(TUint8)aResourceReader.ReadUint8();
	TUint8 secondField=(TUint8)aResourceReader.ReadUint8();
	TUint8 thirdField=(TUint8)aResourceReader.ReadUint8();
    TUint8 fourthField=(TUint8)aResourceReader.ReadUint8();
	return TInetAddr(INET_ADDR((TUint8)firstField,
                               (TUint8)secondField,
                               (TUint8)thirdField,
                               (TUint8)fourthField),
                     0);
	}

/**
 * Method for handling key events.
 * 
 */
EXPORT_C TKeyResponse CAknIpFieldEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
    TKeyResponse response=EKeyWasNotConsumed;
    TKeyEvent event(aKeyEvent);

    if(aType==EEventKey && event.iCode=='.') // If delimiter key has been pressed. In IPv4 delimiter is always a dot.
        event.iCode=EKeyRightArrow;

    response=CEikMfne::OfferKeyEventL(event, aType);
	
    return response;
	}
	
EXPORT_C void CAknIpFieldEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikMfne::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CAknIpFieldEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CAknIpFieldEditor::CEikMfne_Reserved()
	{
	}

