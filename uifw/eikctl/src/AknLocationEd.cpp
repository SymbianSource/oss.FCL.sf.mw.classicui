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
* Description: 
*       Location editors   
*     
*
*/

#include <aknlocationed.h>
#include <lbsposition.h>
#include <barsread.h>
#include <eikon.hrh>
#include <e32math.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <eikenv.h>
#include <eikctl.rsg>
#include <cenrepnotifyhandler.h>
#include <AknUtils.h>
#include "aknmfneseparator.h"

#include <AknTasHook.h>
struct CLocationStrings : public CBase, public MCenRepNotifyHandlerCallback
{
    HBufC *iDegree;
    HBufC *iMinMark;
    HBufC *iSecMark;
    HBufC *iNorth;
    HBufC *iSouth;
    HBufC *iEast;
    HBufC *iWest;
    ~CLocationStrings()
        {
        delete iDegree;
        delete iMinMark;
        delete iSecMark;
        delete iNorth;
        delete iSouth;
        delete iEast;
        delete iWest;
        }

    TInt iType;

    // From MCenRepNotifyHandlerCallback
    void HandleNotifyInt(TUint32 aId, TInt aNewValue);     
    CAknLocationEditor *iParent;     
    // Handle to Central Repository.
    CRepository* iCenRep;    
    // For Central Repository value change notifications. 
    CCenRepNotifyHandler* iCenRepNotifyHandler;
    TBool iMirroredLayoutUsed;
};


void CLocationStrings::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    TRAP_IGNORE( iParent->HandleCenRepChangedL(aId, aNewValue));
    }


_LIT(KRLM, "\x200F"); // Directionality marker: Right-to-Left Marker.
_LIT(KLRE, "\x202A"); // Directionality marker: Left-to-Right Embedding.
_LIT(KPDF, "\x202C"); // Directionality marker: Pop Directional Format

EXPORT_C CAknLocationEditor::CAknLocationEditor()
    {
    }
EXPORT_C CAknLocationEditor::~CAknLocationEditor()
    {
    AKNTASHOOK_REMOVE();
    // Stop listening CenRep.
    if (iStrings)
        {
        if (iStrings->iCenRepNotifyHandler)
            {
            iStrings->iCenRepNotifyHandler->StopListening();
            }
        delete iStrings->iCenRepNotifyHandler;
        delete iStrings->iCenRep;    
        }
    delete iStrings;
    }


EXPORT_C CAknLocationEditor *CAknLocationEditor::NewL(TPosition &aValue, TLocationContext aContext)
    {
    CAknLocationEditor *editor = new(ELeave)CAknLocationEditor;
    CleanupStack::PushL(editor);
    editor->LoadStringsL(R_EIK_LATITUDE_AND_LONGITUDE);
    editor->ConstructL(aValue, aContext);
    CleanupStack::Pop(editor);
    AKNTASHOOK_ADDL( editor, "CAknLocationEditor" );
    return editor;
    }

static void AppendString(TPtr aBuf, TPtrC aString)
    {
    aBuf.Append(aString);
    }
static void AppendString(TPtr aBuf, TChar aChar)
	{
	aBuf.Append(aChar);
	}
static void AppendNum(TPtr aBuf, TInt aValue, TInt aNumOfDigits)
    {
    aBuf.AppendNumFixedWidthUC(aValue, EDecimal, aNumOfDigits); 
    }
static void AppendNumFst(TPtr aBuf, TInt aValue, TInt /*aNumOfDigits*/)
    {
    aBuf.AppendNum(aValue);
    }

static HBufC *CopyDesL(HBufC *aOrig)
    {
    HBufC *buf = HBufC::NewL(aOrig->Length());
    *buf = aOrig->Des();
    return buf;
    }
static TChar DecimalSeparator()
	{
	TLocale t;
	TChar c = t.DecimalSeparator();
	return c;
	}

EXPORT_C HBufC *CAknLocationEditor::DisplayableLocationL(const TPosition & aValue, TLocationContext aContext)
    {
    // read cenrep key
    TInt type = EDD;
    CRepository* repository = NULL;
    TRAPD(err, repository = CRepository::NewL(KCRUidAvkon));
    TUint32 key = KAknLocationEditorCoordinateDataFormat;
    if (err == KErrNone)
        {
        err = repository->Get(key, (TInt&)type);
        }
    delete repository;
    
    CLocationStrings *strings = new (ELeave) CLocationStrings;
    CleanupStack::PushL(strings);
    // read resources
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC(reader, R_EIK_LATITUDE_AND_LONGITUDE);
    strings->iDegree = reader.ReadHBufCL();
    strings->iMinMark = reader.ReadHBufCL();
    strings->iSecMark = reader.ReadHBufCL();
    strings->iNorth = reader.ReadHBufCL();
    reader.ReadInt16();
    strings->iSouth = reader.ReadHBufCL();
    reader.ReadInt16();
    strings->iEast = reader.ReadHBufCL();
    reader.ReadInt16();
    strings->iWest = reader.ReadHBufCL();
    reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader

    strings->iMirroredLayoutUsed = AknLayoutUtils::LayoutMirrored();
    HBufC *buffer = HBufC::NewL(200);

    switch(type)
        {
        case EDD:
            {
            TInt degrees;
            TInt decidegrees;
            TBool neg;
            TBool nan;
            SplitDD(aValue, aContext, degrees, decidegrees, neg, nan);
            
            if (nan) 
                {
                CleanupStack::PopAndDestroy(strings);
                return buffer;
                }
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KRLM));
                AppendString(buffer->Des(), TPtrC(KLRE));                
                }
            AppendNumFst(buffer->Des(), degrees, aContext==ELatitudeOnly?2:3);
            AppendString(buffer->Des(), DecimalSeparator());
            AppendNum(buffer->Des(), decidegrees, 5);
            AppendString(buffer->Des(), *strings->iDegree);
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KPDF));                
                }                            
            AppendString(buffer->Des(), neg?(aContext==ELatitudeOnly?*strings->iSouth:*strings->iWest) 
                                     :(aContext==ELatitudeOnly?*strings->iNorth:*strings->iEast));
            break;
            }
        case EDMM:
            {
            int degrees;
            int minutes;
            int deciminutes;
            TBool neg;
            TBool nan;
            SplitDMM(aValue, aContext, degrees, minutes, deciminutes, neg, nan);
            if (nan) 
                {
                CleanupStack::PopAndDestroy(strings);
                return buffer;
                }
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KRLM));
                AppendString(buffer->Des(), TPtrC(KLRE));                
                }                
            AppendNumFst(buffer->Des(), degrees, aContext==ELatitudeOnly?2:3);
            AppendString(buffer->Des(), *strings->iDegree);
            AppendNum(buffer->Des(), minutes, 2);
            AppendString(buffer->Des(), DecimalSeparator());
            AppendNum(buffer->Des(), deciminutes, 4);
            AppendString(buffer->Des(), *strings->iMinMark);
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KPDF));                
                }                
            AppendString(buffer->Des(), neg?(aContext==ELatitudeOnly?*strings->iSouth:*strings->iWest) 
                                     :(aContext==ELatitudeOnly?*strings->iNorth:*strings->iEast));
            

            break;
            }
        case EDMSD:
            {
            int degrees;
            int minutes;
            int secs;
            int deciseconds;
            TBool neg;
            TBool nan;
            SplitDMSD(aValue, aContext, degrees, minutes, secs, deciseconds, neg, nan);
            if (nan) 
                {
                CleanupStack::PopAndDestroy(strings);
                return buffer;
                }
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KRLM));
                AppendString(buffer->Des(), TPtrC(KLRE));                
                }                
            AppendNumFst(buffer->Des(), degrees, aContext==ELatitudeOnly?2:3);
            AppendString(buffer->Des(), *strings->iDegree);
            AppendNum(buffer->Des(), minutes, 2);
            AppendString(buffer->Des(), *strings->iMinMark);
            AppendNum(buffer->Des(), secs, 2);
            AppendString(buffer->Des(), DecimalSeparator());
            AppendNum(buffer->Des(), deciseconds, 2);
            AppendString(buffer->Des(), *strings->iSecMark);
            if (strings->iMirroredLayoutUsed)
                {
                AppendString(buffer->Des(), TPtrC(KPDF));                
                }                
            AppendString(buffer->Des(), neg?(aContext==ELatitudeOnly?*strings->iSouth:*strings->iWest) 
                                     :(aContext==ELatitudeOnly?*strings->iNorth:*strings->iEast));
            break;

            }
        };
    TPtr ptr = buffer->Des();
    AknTextUtils::LanguageSpecificNumberConversion(ptr);

    CleanupStack::PopAndDestroy(strings); // strings

    return buffer;
    }

EXPORT_C void CAknLocationEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TInt flags( aResourceReader.ReadInt32() );
    TInt res_id( aResourceReader.ReadInt32() );    
    TLocationContext context( ELongitudeOnly );
    if (flags & ELocationEdFlagLatitude)
        {
        context = ELatitudeOnly;
        }
    TCoordinate coord( 0.0, 0.0 );    
    TLocality loc(coord, 0.1 );
    TPosition p(loc, TTime(0) );
    LoadStringsL(res_id);
    ConstructL(p, context);
    }
    
EXPORT_C void CAknLocationEditor::Set(const TPosition &aValue)
    {
    TLocationType type = Type();
    switch(type)
        {
        case EDD:
            {
            TInt degrees;
            TInt decidegrees;
            TBool neg;
            TBool nan;
            SplitDD(aValue, iContext, degrees, decidegrees, neg, nan);
            
            CEikMfneNumber *field;
            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetValue(degrees, *Font());
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            field->SetValue(decidegrees, *Font());
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(4, type));
            field2->SetCurrentSymbolicItemToId(neg ? 1 : 0);
            SetUninitialised(nan);
            break;
            }
        case EDMM:
            {
            int degrees;
            int minutes;
            int deciminutes;
            TBool neg;
            TBool nan;
            SplitDMM(aValue, iContext, degrees, minutes, deciminutes, neg, nan);
            
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetValue(degrees, *Font());
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            field->SetValue(minutes, *Font());
            
            field = (CEikMfneNumber*)Field(FieldMapping(4, type));
            field->SetValue(deciminutes, *Font());
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(6, type));
            field2->SetCurrentSymbolicItemToId(neg ? 1 : 0);
            SetUninitialised(nan);
            
            break;
            }
        case EDMSD:
            {
            int degrees;
            int minutes;
            int secs;
            int deciseconds;
            TBool neg;
            TBool nan;
            SplitDMSD(aValue, iContext, degrees, minutes, secs, deciseconds, neg, nan);
            
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetValue(degrees, *Font());
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            field->SetValue(minutes, *Font());
            
            
            field = (CEikMfneNumber*)Field(FieldMapping(4, type));
            field->SetValue(secs, *Font());
            
            field = (CEikMfneNumber*)Field(FieldMapping(6, type));
            field->SetValue(deciseconds, *Font());
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(8, type));
            field2->SetCurrentSymbolicItemToId(neg ? 1 : 0);
            SetUninitialised(nan);
            break;
            
            }
        }
        if ( !IsFocused() )
            {
            TRAP_IGNORE( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
            }
    }

EXPORT_C void CAknLocationEditor::Get(TPosition &aValue) const
    {
    TLocationType type = Type();
    switch(type)
        {
        case EDD:
            {
            TBool nan = ETrue;
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            TInt degrees = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            TInt decidegrees = field->Value();
            nan = nan && field->IsUninitialised();
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(4, type));
            TBool neg = field2->IdOfCurrentSymbolicItem() != 0;
            
            CombineDD(aValue, iContext, degrees, decidegrees, neg, nan);
            break;
            }
        case EDMM:
            {
            TBool nan( ETrue );
            
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            TInt degrees = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            TInt minutes = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(4, type));
            TInt deciminutes = field->Value();
            nan = nan && field->IsUninitialised();
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(6, type));
            TBool neg = field2->IdOfCurrentSymbolicItem() != 0;
            
            
            CombineDMM(aValue, iContext, degrees, minutes, deciminutes, neg, nan);
            break;
            }
        case EDMSD:
            {
            TBool nan( ETrue );
            
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            TInt degrees = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(2, type));
            TInt minutes = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(4, type));
            TInt secs = field->Value();
            nan = nan && field->IsUninitialised();
            
            field = (CEikMfneNumber*)Field(FieldMapping(6, type));
            TInt deciseconds = field->Value();
            nan = nan && field->IsUninitialised();
            
            CEikMfneSymbol *field2 = (CEikMfneSymbol*)Field(FieldMapping(8, type));
            TBool neg = field2->IdOfCurrentSymbolicItem() != 0;
            
            CombineDMSD(aValue, iContext, degrees, minutes, secs, deciseconds, neg, nan);
            break;
            }
        }
    }

void CAknLocationEditor::ConstructL(TPosition &aValue, TLocationContext aContext)
    {
    iContext = aContext;
    if (!iStrings)
        {       
        iStrings = new(ELeave)CLocationStrings;
        }
    iStrings->iParent = this;
    iStrings->iType = -1;

   // Start listening a CenRep key indicating whether hash key selection is active.
    TRAPD(err, iStrings->iCenRep = CRepository::NewL(KCRUidAvkon));
    if (err == KErrNone)
        {
        iStrings->iCenRepNotifyHandler = CCenRepNotifyHandler::NewL(*iStrings,
            *iStrings->iCenRep,
            CCenRepNotifyHandler::EIntKey,
            KAknLocationEditorCoordinateDataFormat);

        iStrings->iCenRepNotifyHandler->StartListeningL();
        }

    // This is for the lifetime of the editor.    
    iStrings->iMirroredLayoutUsed = AknLayoutUtils::LayoutMirrored();
    CreateMfneFieldsL(aValue);
    RefreshFromLocale();
    }

void CAknLocationEditor::CreateMfneFieldsL(const TPosition &aValue)
    {
    TInt flags = CEikMfneNumber::EFillWithLeadingZeros;
    TInt flags_fst = 0;
    TInt numberOfFields = 0;
    TLocationType type = Type();
    
    switch(type)
        {
        case EDD: numberOfFields = 5; break;
        case EDMM: numberOfFields = 7; break;
        case EDMSD: numberOfFields = 9; break;
        default: break;
        };

    CreateFieldArrayL(numberOfFields);

    switch(type)
        {
        case EDD:
            {
            TInt degrees;
            TInt decidegrees;
            TBool neg;
            TBool nan;
            SplitDD(aValue, iContext, degrees, decidegrees, neg, nan);

            // cardinal point
            CEikMfneSymbol *field3;
            field3 = CEikMfneSymbol::NewL(2);

            CEikMfneSymbol::CItem *item = CEikMfneSymbol::CItem::NewL(0, 
                                                                      iContext == ELatitudeOnly ? 'N' : 'E', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iNorth : iStrings->iEast));
            CEikMfneSymbol::CItem *item2 = CEikMfneSymbol::CItem::NewL(1, 
                                                                      iContext == ELatitudeOnly ? 'S' : 'W', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iSouth : iStrings->iWest));
            field3->AddSymbolicItem(item, !neg);
            field3->AddSymbolicItem(item2, neg);
            
            if ( iStrings->iMirroredLayoutUsed )
                {
                // Add cardinal point field to first field when reading direction is right-to-left.
                AddField(field3);
                }

            // degrees
            CEikMfneNumber *field;
            field = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         iContext==ELatitudeOnly ? 90 : 180,
                                         degrees,
                                         flags_fst);                     
            AddField(field);
            
            // .
            HBufC* delimiterText=HBufC::NewLC(3);
            delimiterText->Des().Append(DecimalSeparator());
            AddField(CAknMfneSeparator::NewL(*delimiterText));
            CleanupStack::PopAndDestroy(); // delimiterText

            // decidegrees
            CEikMfneNumber *field2;
            field2 = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         99999,
                                         decidegrees,
                                         flags);                     
            field2->SetTrailingZeros();
            AddField(field2);
            
            // circle
            HBufC* delimiterText2=HBufC::NewLC(300);
            delimiterText2->Des().Append(*iStrings->iDegree);
            AddField(CAknMfneSeparator::NewL(*delimiterText2));
            CleanupStack::PopAndDestroy(); // delimiterText

            if ( !iStrings->iMirroredLayoutUsed )
                {
                // Add cardinal point field to first field when reading direction is left-to-right.             
                AddField(field3);
                }
            SetUninitialised(nan);          
            break;
            }
        case EDMM:
            {
            int degrees;
            int minutes;
            int deciminutes;
            TBool neg;
            TBool nan;
            SplitDMM(aValue, iContext, degrees, minutes, deciminutes, neg, nan);

            // cardinal point
            CEikMfneSymbol *field4;
            field4 = CEikMfneSymbol::NewL(2);

            CEikMfneSymbol::CItem *item = CEikMfneSymbol::CItem::NewL(0, 
                                                                      iContext == ELatitudeOnly ? 'N' : 'E', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iNorth : iStrings->iEast));
            CEikMfneSymbol::CItem *item2 = CEikMfneSymbol::CItem::NewL(1, 
                                                                      iContext == ELatitudeOnly ? 'S' : 'W', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iSouth : iStrings->iWest));
            field4->AddSymbolicItem(item, !neg);
            field4->AddSymbolicItem(item2, neg);
            field4->SetUninitialised(nan);

            if ( iStrings->iMirroredLayoutUsed )
                {               
                // Add cardinal point field to first field when reading direction is right-to-left.
                AddField(field4);
                }

            // degrees
            CEikMfneNumber *field;
            field = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         iContext==ELatitudeOnly ? 90 : 180,
                                         degrees,
                                         flags_fst);                     
            field->SetUninitialised(nan);
            AddField(field);

            // o
            HBufC* delimiterText=HBufC::NewLC(3);
            delimiterText->Des().Append(*iStrings->iDegree);
            AddField(CAknMfneSeparator::NewL(*delimiterText));
            CleanupStack::PopAndDestroy(); // delimiterText

            // minutes
            CEikMfneNumber *field2;
            field2 = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         59,
                                         minutes,
                                         flags);                     
            field2->SetUninitialised(nan);
            AddField(field2);

            // .
            HBufC* delimiterText2=HBufC::NewLC(3);
            delimiterText2->Des().Append(DecimalSeparator());
            AddField(CAknMfneSeparator::NewL(*delimiterText2));
            CleanupStack::PopAndDestroy(); // delimiterText

            // deciminutes
            CEikMfneNumber *field3;
            field3 = CEikMfneNumber::NewL(*Font(),
                                         0,
                                         9999,
                                         deciminutes,
                                         flags);                     
            field3->SetUninitialised(nan);
            field3->SetTrailingZeros();
            AddField(field3);
            
            // '
            HBufC* delimiterText3=HBufC::NewLC(3);
            delimiterText3->Des().Append(*iStrings->iMinMark );
            AddField(CAknMfneSeparator::NewL(*delimiterText3));
            CleanupStack::PopAndDestroy(); // delimiterText


            if ( !iStrings->iMirroredLayoutUsed )
                {            
                // Add cardinal point field to first field when reading direction is left-to-right.                
                AddField(field4);
                }
            SetUninitialised(nan);          
            
            break;
            }
        case EDMSD:
            {
            int degrees;
            int minutes;
            int secs;
            int deciseconds;
            TBool neg;
            TBool nan;
            SplitDMSD(aValue, iContext, degrees, minutes, secs, deciseconds, neg, nan);

            // cardinal point
            CEikMfneSymbol *field5;
            field5 = CEikMfneSymbol::NewL(2);

            CEikMfneSymbol::CItem *item = CEikMfneSymbol::CItem::NewL(0, 
                                                                      iContext == ELatitudeOnly ? 'N' : 'E', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iNorth : iStrings->iEast));
            CEikMfneSymbol::CItem *item2 = CEikMfneSymbol::CItem::NewL(1, 
                                                                      iContext == ELatitudeOnly ? 'S' : 'W', 
                                                                      CopyDesL(iContext == ELatitudeOnly ? iStrings->iSouth : iStrings->iWest));
            field5->AddSymbolicItem(item, !neg);
            field5->AddSymbolicItem(item2, neg);

            if ( iStrings->iMirroredLayoutUsed )
                {               
                // Add cardinal point field to first field when reading direction is right-to-left.
                AddField(field5);
                }

            // degrees
            CEikMfneNumber *field;
            field = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         iContext==ELatitudeOnly ? 90 : 180,
                                         degrees,
                                         flags_fst);                     
            AddField(field);

            // o
            HBufC* delimiterText=HBufC::NewLC(3);
            delimiterText->Des().Append(*iStrings->iDegree);
            AddField(CAknMfneSeparator::NewL(*delimiterText));
            CleanupStack::PopAndDestroy(); // delimiterText

            // minutes
            CEikMfneNumber *field2;
            field2 = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         59,
                                         minutes,
                                         flags);                     
            AddField(field2);

            
            // '
            HBufC* delimiterText3=HBufC::NewLC(3);
            delimiterText3->Des().Append(*iStrings->iMinMark );
            AddField(CAknMfneSeparator::NewL(*delimiterText3));
            CleanupStack::PopAndDestroy(); // delimiterText

            // seconds
            CEikMfneNumber *field3;
            field3 = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         59,
                                         secs,
                                         flags);                     
            AddField(field3);


            // .
            HBufC* delimiterText2=HBufC::NewLC(3);
            delimiterText2->Des().Append(DecimalSeparator());
            AddField(CAknMfneSeparator::NewL(*delimiterText2));
            CleanupStack::PopAndDestroy(); // delimiterText


            // deciseconds
            CEikMfneNumber *field4;
            field4 = CEikMfneNumber::NewL(*Font(),
                                         00,
                                         99,
                                         deciseconds,
                                         flags);                     
            field4->SetTrailingZeros();
            AddField(field4);


            // "
            HBufC* delimiterText4=HBufC::NewLC(3);
            delimiterText4->Des().Append(*iStrings->iSecMark);
            AddField(CAknMfneSeparator::NewL(*delimiterText4));
            CleanupStack::PopAndDestroy(); // delimiterText

            if ( !iStrings->iMirroredLayoutUsed )
                {
                // Add cardinal point field to first field when reading direction is left-to-right.
                AddField(field5);
                }
            SetUninitialised(nan);          

            break;
            }
        };
    HighlightField(FieldMapping(0, type));
    }

EXPORT_C void CAknLocationEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    TLocationType type = Type();
    CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(0, type));
    TInt degrees =  field->Value();
    TInt minimum, maximum;
    field->GetMinimumAndMaximum(minimum, maximum);
    if (degrees == maximum)
        {
        TBool error = EFalse;

        CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(2, type));          
        TInt val = field->Value();
        if (val != 0) error = ETrue;
        TInt cardinalPointFieldNumber = 4;

        if (type != EDD)
            {
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(4, type));          
            TInt val = field->Value();
            if (val != 0) error = ETrue;
            cardinalPointFieldNumber = 6;
            }
            
        if (type == EDMSD)
            {
            CEikMfneNumber *field = (CEikMfneNumber*)Field(FieldMapping(6, type));          
            TInt val = field->Value();
            if (val != 0) error = ETrue;
            cardinalPointFieldNumber = 8;
            }
            
        CEikMfneSymbol* cardinalPointField =
            static_cast<CEikMfneSymbol*>
            ( Field( FieldMapping(cardinalPointFieldNumber, type) ) );

        if ( iContext == ELongitudeOnly && 
             cardinalPointField->IdOfCurrentSymbolicItem() == 0 ) 
            {
            // if represents east..
            error = ETrue;
            cardinalPointField->SetCurrentSymbolicItemToId( 1 );
            }
            
        if (error)
            {
            HighlightField(FieldMapping(0, type));
            ((CEikMfneNumber*)Field(FieldMapping(0, type)))->SetValue(maximum, *Font());
            ((CEikMfneNumber*)Field(FieldMapping(2, type)))->SetValue(0, *Font());
            if (type != EDD) ((CEikMfneNumber*)Field(FieldMapping(4, type)))->SetValue(0, *Font());
            if (type == EDMSD) ((CEikMfneNumber*)Field(FieldMapping(6, type)))->SetValue(0, *Font());
            CEikMfne::InvalidFieldAlert();
            DrawNow();
            CBaActiveScheduler::LeaveNoAlert();
            }
        
        }
    }       

CAknLocationEditor::TLocationType CAknLocationEditor::Type() const
    {
    if (!iStrings)
        return EDD;
    if (iStrings->iType == -1)
        {
        CRepository* repository = NULL;
        TRAPD(err, repository = CRepository::NewL(KCRUidAvkon));
        TUint32 key = KAknLocationEditorCoordinateDataFormat;
        if (err == KErrNone)
            {
            err = repository->Get(key, (TInt&)iStrings->iType);
            }
        delete repository;
        }
    
    if (iStrings->iType == 0)
        return EDD;
    if (iStrings->iType == 1)
        return EDMM;
    if (iStrings->iType == 2)
        return EDMSD;
    
    // TODO, shared data keys.
    //return EDMSD;
    //return EDMM;
    return EDD;

    }

void CAknLocationEditor::LoadStringsL(TInt aResourceId)
    {
    if (!iStrings)
        {       
        iStrings = new(ELeave)CLocationStrings;
        }

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aResourceId);
    iStrings->iDegree = reader.ReadHBufCL();
    iStrings->iMinMark = reader.ReadHBufCL();
    iStrings->iSecMark = reader.ReadHBufCL();
    iStrings->iNorth = reader.ReadHBufCL();
    reader.ReadInt16();
    iStrings->iSouth = reader.ReadHBufCL();
    reader.ReadInt16();
    iStrings->iEast = reader.ReadHBufCL();
    reader.ReadInt16();
    iStrings->iWest = reader.ReadHBufCL();
    reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader
    }
    

TInt CAknLocationEditor::FieldMapping(const TInt aFieldNumber, const TLocationType aType) const
    {
    if ( iStrings->iMirroredLayoutUsed )
        {
        // Cardinal point field is mapped first field when 
        // reading direction is right-to-left.
        if ( aType == EDD )
            {
            static const TInt fieldMapping[] = { 1, 2, 3, 4, 0 };
            return fieldMapping[aFieldNumber];
            }
        else if ( aType == EDMM)
            {
            static const TInt fieldMapping[] = { 1, 2, 3, 4, 5, 6, 0 };
            return fieldMapping[aFieldNumber];
            }
        else if ( aType == EDMSD )
            {
            static const TInt fieldMapping[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
            return fieldMapping[aFieldNumber];
            }
        }
        
    return aFieldNumber;      
    }


void CAknLocationEditor::Split(const TPosition &aValue, TLocationContext aContext, 
                                TInt &aDegrees, TInt &aDeciDegrees,
                                TInt &aMinutes, TInt &aDeciMinutes,
                                TInt &aSeconds, TInt &aDeciSeconds,
                                TBool &aNeg, TBool &aNan)

    {
    TReal64 value = aContext == ELongitudeOnly ? aValue.Longitude() : aValue.Latitude();
    
    if (Math::IsNaN(value))
        {
        aNan = ETrue;
        aDegrees = 0;
        aDeciDegrees = 0;
        aMinutes = 0;
        aDeciMinutes = 0;
        aSeconds = 0;
        aDeciSeconds = 0;
        return;     
        }
    aNan = EFalse;

    // Negative values
    if (value<0) 
        {
        aNeg = ETrue;
        value = -value;
        }
    else
        {
        aNeg = EFalse;          
        }
    
    // rounding...
    value += TReal64(0.1)/TReal64(360000.0);
    // Positive values
    TInt degrees = TInt(value);
    TReal64 deciDegrees = value - TReal64(degrees);
    TInt mins = TInt(deciDegrees * 60.0);   
    TReal64 deciMins = deciDegrees*60.0 - TReal64(mins);
    TInt secs = TInt(deciMins * 60.0);
    TReal64 deciSecs = deciMins*60.0 - TReal64(secs);
    
    TInt deciDegree2 = deciDegrees * 100000.0;
    TInt deciMins2 = deciMins * 10000.0;
    TInt deciSecs2 = deciSecs * 100.0;
    aDegrees = degrees;
    aDeciDegrees = deciDegree2;
    aMinutes = mins;
    aDeciMinutes = deciMins2;
    aSeconds = secs;
    aDeciSeconds = deciSecs2;
    }
    
void CAknLocationEditor::SplitDD(const TPosition &aValue, TLocationContext aContext, TInt &aDegrees, TInt &aDeciDegrees, TBool &aNeg, TBool &aNan)
    {
    TInt degs, ddegs;
    TInt mins, dmins;
    TInt secs, dsecs;
    Split(aValue, aContext, degs, ddegs, mins, dmins, secs, dsecs, aNeg, aNan);
    aDegrees = degs;
    aDeciDegrees = ddegs;
    }
    
void CAknLocationEditor::SplitDMM(const TPosition &aValue, TLocationContext aContext, TInt &aDegrees, TInt &aMinutes, TInt &aDeciMinutes, TBool &aNeg, TBool &aNan)
    {
    TInt degs, ddegs;
    TInt mins, dmins;
    TInt secs, dsecs;
    Split(aValue, aContext, degs, ddegs, mins, dmins, secs, dsecs, aNeg, aNan);
    aDegrees = degs;
    aMinutes = mins;
    aDeciMinutes = dmins;
    }
    
void CAknLocationEditor::SplitDMSD(const TPosition &aValue, TLocationContext aContext, TInt &aDegrees, TInt &aMinutes, TInt &aSeconds, TInt &aDeciSeconds, TBool &aNeg, TBool &aNan)
    {
    TInt degs, ddegs;
    TInt mins, dmins;
    TInt secs, dsecs;
    Split(aValue, aContext, degs, ddegs, mins, dmins, secs, dsecs, aNeg, aNan);
    aDegrees = degs;
    aMinutes = mins;
    aSeconds = secs;
    aDeciSeconds = dsecs;   
    }

void CAknLocationEditor::CombineDD(TPosition &aValue, TLocationContext aContext, TInt aDegrees, TInt aDeciDegrees, TBool aNeg, TBool aNan)
    {
    TReal64 value = TReal64(aDegrees);
    value += TReal64(aDeciDegrees) / 100000.0;
    if (aNeg)
        {
        value = -value;     
        }
    if (aNan)
        {
        TRealX nan;
        nan.SetNaN();
        value = nan;
        }
        
    if (aContext == ELongitudeOnly)
        {
        aValue.SetCoordinate( aValue.Latitude(), value, aValue.Altitude());
        }
    else
        {
        aValue.SetCoordinate( value, aValue.Longitude(), aValue.Altitude());
        }
    }

void CAknLocationEditor::CombineDMM(TPosition &aValue, TLocationContext aContext, TInt aDegrees, TInt aMinutes, TInt aDeciMinutes, TBool aNeg, TBool aNan)
    {
    TReal64 value = TReal64(aDegrees);
    value += TReal64(aMinutes) / 60.0;
    value += TReal64(aDeciMinutes) / 10000.0 / 60.0;
    if (aNeg)
        {
        value = -value;     
        }
    if (aNan)
        {
        TRealX nan;
        nan.SetNaN();
        value = nan;
        }

    if (aContext == ELongitudeOnly)
        {
        aValue.SetCoordinate( aValue.Latitude(), value, aValue.Altitude());
        }
    else
        {
        aValue.SetCoordinate( value, aValue.Longitude(), aValue.Altitude());
        }

    }
    
void CAknLocationEditor::CombineDMSD(TPosition &aValue, TLocationContext aContext,  TInt aDegrees, TInt aMinutes, TInt aSeconds, TInt aDeciSeconds, TBool aNeg, TBool aNan)
    {
    TReal64 value = TReal64(aDegrees);
    value += TReal64(aMinutes) / 60.0;
    value += TReal64(aSeconds) / 60.0 / 60.0;
    value += TReal64(aDeciSeconds) / 100.0 / 60.0 / 60.0;
    if (aNeg)
        {
        value = -value;     
        }
    if (aNan)
        {
        TRealX nan;
        nan.SetNaN();
        value = nan;
        }

    if (aContext == ELongitudeOnly)
        {
        aValue.SetCoordinate( aValue.Latitude(), value, aValue.Altitude());
        }
    else
        {
        aValue.SetCoordinate( value, aValue.Longitude(), aValue.Altitude());
        }

    }

void CAknLocationEditor::SetUninitialised(TBool aIsUninitialized)
    {
    TBool nan = aIsUninitialized;
    TLocationType type = Type();
    
    switch(type)
        {
        case EDD:
            {   
            CEikMfneNumber *field;
            CEikMfneSymbol *symbol;
            CAknMfneSeparator *sep;

            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(1, type)); // .
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(3, type)); // o
            sep->MakeVisible(!nan);

            symbol = (CEikMfneSymbol*)Field(FieldMapping(4, type));
            symbol->SetUninitialised(nan);
            break;
            }
        case EDMM:
            {   
            CEikMfneNumber *field;
            CAknMfneSeparator *sep;
            CEikMfneSymbol *symbol;

            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(1, type)); // 
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(3, type));
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(4, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(5, type));
            sep->MakeVisible(!nan);

            symbol = (CEikMfneSymbol*)Field(FieldMapping(6, type));
            symbol->SetUninitialised(nan);
            break;  
            }
        case EDMSD:
            {   
            CEikMfneNumber *field;
            CAknMfneSeparator *sep;
            CEikMfneSymbol *symbol;

            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(1, type));
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(3, type));
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(4, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(5, type));
            sep->MakeVisible(!nan);

            field = (CEikMfneNumber*)Field(FieldMapping(6, type));              
            field->SetUninitialised(nan);

            sep = (CAknMfneSeparator*)Field(FieldMapping(7, type));
            sep->MakeVisible(!nan);

            symbol = (CEikMfneSymbol*)Field(FieldMapping(8, type));
            symbol->SetUninitialised(nan);
            break;
            }
        }    
    }

void CAknLocationEditor::RefreshFromLocale()
    {
    const CFont &font = *Font();
    TLocationType type = Type();
    switch(type)
        {
        case EDD:
            {   
            CEikMfneNumber *field;
            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->RefreshDigitType(font);
            break;
            }
        case EDMM:
            {   
            CEikMfneNumber *field;
            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(4, type));              
            field->RefreshDigitType(font);
            break;  
            }
        case EDMSD:
            {   
            CEikMfneNumber *field;
            field = (CEikMfneNumber*)Field(FieldMapping(0, type));
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(2, type));              
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(4, type));              
            field->RefreshDigitType(font);

            field = (CEikMfneNumber*)Field(FieldMapping(6, type));              
            field->RefreshDigitType(font);
            break;
            }
        }
    }

EXPORT_C TKeyResponse CAknLocationEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (aType == EEventKey && ((aKeyEvent.iCode >= '0' && aKeyEvent.iCode <= '9') 
                             || aKeyEvent.iCode == EKeyLeftArrow || aKeyEvent.iCode == EKeyRightArrow))
        {
        TInt firstField( FieldMapping( 0, Type() ) );
        CEikMfneNumber* field( (CEikMfneNumber*)Field( firstField ) );
        if ( field->IsUninitialised() )
            {
            SetCurrentField( firstField );
            }
        SetUninitialised(EFalse);        

        DrawNow();  
        }
    return CEikMfne::OfferKeyEventL(aKeyEvent, aType);
    }

void CAknLocationEditor::HandleCenRepChangedL(TUint32, TInt)
    {
    TPosition pos;
    Get(pos);
    iStrings->iType = -1;
    ResetFieldArray();
    CreateMfneFieldsL(pos);
    RefreshFromLocale();
    MfneSize();
    DrawDeferred();
    }

EXPORT_C void* CAknLocationEditor::CAknLocationEditor_ExtensionInterface( TUid /*aInterface*/ )
    {
    return 0;
    }

