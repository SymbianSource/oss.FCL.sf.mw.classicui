/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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



#include <uiklaf/private/lafenv.h>
#include <lafpanic.h>
#include "LAFSTD.H"
#include <barsread.h>
#include <w32std.h>
#include <gulutil.h>
#include <coemain.h>
#include <eikpriv.rsg>
#include <aknborders.h>
#include "lafAknBorders.h"

#include <AknUtils.h>
#include <eikenv.h>

#include <bautils.h>
#include <aknnotewrappers.h>
#include <fontids.hrh>
#include <gulfont.h>
#include <uiklaf/private/lafmsg.h>

#include <AknFontIdLayoutFont.h>
#include <AknSystemFont.h>
#include <AknFontId.h>
#include <aknlayoutscalable_avkon.cdl.h> // Scalable layout API
#include <AknFontProvider.h>

const TUint EKeyDefault = EKeyDelete;	//setup as EKeyF11 (#defined in E32Keys.h)
const TInt KLafShadowHeight = 3;
const TInt KLafEnvDefaultLineSpacingInTwips = 158;
const TInt KDefaultFontIndex = 0;

_LIT(KRDSupport, "c:\\resource\\errrd" );
_LIT(KAknFirstStartedAppThreadName, "akncapserver");

const TUint8 KLogicalToAvkonColorMap[] =
	{
	0,		// EEikColorWindowBackground
	215,	// EEikColorWindowText
	0,		// EEikColorControlBackground
	215,	// EEikColorControlText
	0,		// EEikColorControlSurroundBackground
	215,	// EEikColorControlSurroundText
	244,	// EEikColorControlHighlightBackground
	215,	// EEikColorControlHighlightText
	0,		// EEikColorControlDimmedBackground
	215,	// EEikColorControlDimmedText
	244,	// EEikColorControlDimmedHighlightBackground
	215,	// EEikColorControlDimmedHighlightText
	0,		// EEikColorDialogBackground
	215,	// EEikColorDialogText
	0,		// EEikColorDialogTitle
	0,		// EEikColorDialogTitlePressed
	215,	// EEikColorDialogTitleText
	215,	// EEikColorDialogTitleTextPressed
	0,		// EEikColorMenubarBackground
	215,	// EEikColorMenubarText
	0,		// EEikColorMenubarTitleBackground
	215,	// EEikColorMenubarTitleText
	0,		// EEikColorMenuPaneBackground
	215,	// EEikColorMenuPaneText
	244,	// EEikColorMenuPaneHighlight
	215,	// EEikColorMenuPaneTextHighlight
	244,	// EEikColorMenuPaneDimmedHighlight
	215,	// EEikColorMenuPaneDimmedText
	244,	// EEikColorMenuPaneDimmedTextHighlight
	43,		// EEikColorButtonFaceClear
	0,		// EEikColorButtonFaceSet
	43,		// EEikColorButtonFaceSetPressed
	0,		// EEikColorButtonFaceClearPressed
	215,	// EEikColorButtonText
	215,	// EEikColorButtonTextPressed
	222,	// EEikColorButtonTextDimmed
	215,	// EEikColorMsgWinForeground
	244,	// EEikColorMsgWinBackground
	215,	// EEikColorScrollBarBorder
	0,		// EEikColorScrollBarShaft
	0,		// EEikColorScrollBarShaftDimmed
	222,	// EEikColorScrollBarShaftPressed
	0,		// EEikColorScrollBarNoShaftOrThumb
	215,	// EEikColorScrollButtonIcon
	215,	// EEikColorScrollButtonIconPressed
	222,	// EEikColorScrollButtonIconDimmed
	43,		// EEikColorScrollButtonThumbBackground
	0,		// EEikColorScrollButtonThumbBackgroundPressed
	216,	// EEikColorScrollThumbDimmed
	215,	// EEikColorScrollThumbEdge
	0,		// EEikColorToolbarBackground
	215,	// EEikColorToolbarText
	0,		// EEikColorStatusPaneBackground
	215,	// EEikColorStatusPaneText
	215,	// EEikColorLabelText
	215,	// EEikColorLabelTextEmphasis
	222,	// EEikColorLabelDimmedText
	222,	// EEikColorLabelHighlightPartialEmphasis
	215		// EEikColorLabelHighlightFullEmphasis
	};


/**
 * Creates an EText parser
 */
EXPORT_C MParser* LafEnv::CreateTextParserL(TInt /*aIndex*/)
	{ // static
	MParser* parser=NULL;
	return parser;
	}

// Local utility for loading resource file
LOCAL_C TInt LoadResFileL(CCoeEnv& aEnv, const TDesC& aFileName)
	{
	TFileName fileName(aFileName);
	BaflUtils::NearestLanguageFile(aEnv.FsSession(), fileName);
	return aEnv.AddResourceFileL(fileName);
	}

//This should only be called by MatchFont() in those cases where it is given a TLogicalFont
//without a Uid. In those cases this figures out what font to use based on the category
//and calls the relevant FontName() function. All switching by subvariant
//occurs in those FontName() functions (e.g. LatinPlain12() ) which then call
//MatchFont (so it's a call within a call), but this time
//with a Uid. 
LOCAL_C const CFont* GetRightFontFromCategory(const TLogicalFont::TFontCategory aCategory)
    {    
    switch (aCategory)
        {
        case TLogicalFont::EView:
            return CEikonEnv::Static()->NormalFont();
        case TLogicalFont::EButton:
            return CEikonEnv::Static()->DenseFont();
        case TLogicalFont::EAnnotation:
            return CEikonEnv::Static()->AnnotationFont();
        case TLogicalFont::ETitle:
            return CEikonEnv::Static()->TitleFont();
        default: //this should never happen as long as TLogicalFont always has
            // either Uid or a category and not further categories are defined
            // See the constructor for TLogicalFont
            __ASSERT_ALWAYS(0,Panic(ELafPanicFontUidUnknownOrMissing));	
            return NULL;//for compiler
        }        
    }
	


// Fetches the CFont* from the system font array.  THis will return NULL in the
// following cases: 
// - UID is not found
// - UID is found, but the CFont* there is NULL 
// (Panics where necessary will happen in MatchFont)
LOCAL_C const CFont* GetFontFromSystemArray( CArrayPtr<CAknSystemFont>& aSystemFonts, TInt aIdToBeMatched)
	{
	TInt count = aSystemFonts.Count();
	for ( TInt i = 0; i < count; ++i )
		{
		const CAknSystemFont* font = aSystemFonts[i];
		if ((font) && (font->Uid().iUid == aIdToBeMatched))
			{
			return font->Font();
			}
		}

    // Font was not found
    CAknFontIdLayoutFont* layoutFont=NULL;
    CWsScreenDevice& screenDev=*(CEikonEnv::Static()->ScreenDevice());

    TRAPD(err, 
        {layoutFont = CAknFontIdLayoutFont::NewL( screenDev , aIdToBeMatched);
        } );

    if ( err == KErrNone )
    	{
    	CleanupStack::PushL( layoutFont );
    	// Create font and add to font array
    	TUid uid = TUid::Uid( aIdToBeMatched);
    	CAknSystemFont* systemFont = CAknSystemFont::NewL( uid, layoutFont ); 
    	CleanupStack::Pop( layoutFont );
		CleanupStack::PushL( systemFont );
    	aSystemFonts.AppendL( systemFont );
    	CleanupStack::Pop( systemFont );
    	return systemFont->Font();
    	}
    else if ( count > KDefaultFontIndex )
    	{
    	// return a default font if loading fails
		return aSystemFonts[KDefaultFontIndex]->Font();
    	}	
    else 
    	return NULL;

	}

LOCAL_C TBool IsFirstApp()
    {
    RThread thread;
    return ( thread.Name().CompareF( KAknFirstStartedAppThreadName) == 0 );
    }

/**
 * Returns the corner of the screen which the busy message should appear in
 * by default on the device.
 */
EXPORT_C TGulAlignment LafEnv::DefaultBusyMsgCorner()
	{// static
	return EHRightVBottom;
	}

/**
 * Populates aBitmaps with a set of system bitmaps.
 */
EXPORT_C void LafEnv::CreateSystemBitmapsL(CCoeEnv& /*aEnv*/, CArrayPtrFlat<CFbsBitmap>& /*aBitmaps*/)
	{ 
	// Empty implementation in Avkon
	}

LOCAL_C void AddStartupFontToSystemFontArrayL( CArrayPtr<CAknSystemFont>& aSystemFonts )
    {
    // Construct a font that is the same as the system startup font.  
    CWsScreenDevice& screenDev=*(CEikonEnv::Static()->ScreenDevice());
    TInt startupId = TAknFontId::FontIdForStartupNormalFont();
    CAknFontIdLayoutFont* layoutFont = CAknFontIdLayoutFont::NewL( screenDev , startupId);
    
    CleanupStack::PushL( layoutFont );
    // Create font and add to font array
    TUid uid = TUid::Uid( startupId); // Tag with the encoded font ID and not the logical
    CAknSystemFont* systemFont = CAknSystemFont::NewL( uid, layoutFont ); 
    CleanupStack::Pop( layoutFont );
    CleanupStack::PushL( systemFont );
    aSystemFonts.AppendL( systemFont );
    CleanupStack::Pop( systemFont );
    // Always should have 2 fonts at this point
    __ASSERT_ALWAYS( aSystemFonts.Count() == 2, Panic(ELafPanicFontCreationFailure));
    
    }
/**
 * Populate aFonts with a set of system fonts defined in eikpriv.rss
 * A minimum of one font must be created.
 */

EXPORT_C void LafEnv::CreateSystemFontsL(CCoeEnv& aEnv, CArrayPtr<CAknSystemFont>& aFonts)
	{
    // Ensure the system font array is set in Avkon extension
    CEikonEnv* env = static_cast<CEikonEnv*>(&aEnv);
    CAknEnv* aAknEnv = static_cast<CAknEnv*>(env->Extension());
    if (aAknEnv)
        {
        aAknEnv->iSystemFontArray = &aFonts;  // Friend class setting access to private member
        }
#ifdef AVKON_RDEBUG_INFO
    if (!aAknEnv)
        RDebug::Print(_L("LafEnv::CreateSystemFontsL - System Font Array pointer NOT set into AknEnv"));
#endif      
    TBool isFirstApp = IsFirstApp();
    
    // We will want NormalFont at index 0. Add it here by doing what CEikEnv will do
    TLogicalFont lf;
    lf.iFontId=TUid::Uid(KLafUidNormalFontVal);
    (void)LafEnv::MatchFont( aFonts, lf ); // Creates the future iNormalFont
	    	
    if ( isFirstApp )
        {
        // Create a 2nd system font in this app that will hold permanently open the dummy 
    	// font that all apps start up with (the initial iNormalFont)
    	AddStartupFontToSystemFontArrayL(aFonts);
    	
    	// Also set the system defaults and aliases
    	// AknFontProvider::InitializeSystemL needs WriteDeviceData, and it only a co-incidence that the first app started 
    	// is AknCapServer with its high capabilities. These checks added for maintainability and debugability

    	RProcess process;
#ifdef AVKON_RDEBUG_INFO
    	if ( !process.HasCapability( ECapabilityWriteDeviceData) )
    	    {
    	    RDebug::Print(_L("LafEnv::CreateSystemFontsL - Not in high enough capability app to initialize fonts system-wide"));
    	    }
#endif 
        __ASSERT_ALWAYS( process.HasCapability( ECapabilityWriteDeviceData) , Panic(ELafPanicFontCreationFailure) );
   
        AknFontProvider::InitializeSystemL( static_cast<CEikonEnv&>(aEnv) );
        }   
        
    return; // nothing created from resource.
    }

LOCAL_C TInt MapSymbianLogicalFontUidToSeries60Id( TInt aUidToMap )
    {
    switch (aUidToMap)
        {
        case KLafUidNormalFontVal:
        return EAknLogicalFontPrimaryFont;

        case KLafUidAnnotationFontVal:
        return EAknLogicalFontPrimarySmallFont;

        case KLafUidDenseFontVal:
        return EAknLogicalFontSecondaryFont;

        case KLafUidTitleFontVal:
        return EAknLogicalFontTitleFont;

        case KLafUidSymbolFontVal:
        return EAknLogicalFontPrimarySmallFont;

        case KLafUidLegendFontVal:
        return EAknLogicalFontPrimarySmallFont;

        default:		
        return aUidToMap;
        }
    // no return required
    }

/**
 * Return the nearest match to aLogicalFont in aSystemFonts. 
 * If given an ordinary font Uid it returns the font.
 * If it is given one of the LogicalFont Uid's it will
 * effectively map this to a genuine font Uid and recursively call
 * MatchFont but this time with a proper Uid (will not do any further nested calls)
 * If it is given
 * a LogicalFont with no Uid but with a category, it uses the category to
 * figure out what Logical Font Uid to use, and then does a recursive call to MatchFont 
 * (i.e. itself) witha  Logical Font Uid as parameter, 
 * returning you to the situation just discussed above.
 * Thus at worst we get a call within a call within a call.
 * 
 * The return value must be non-NULL
 */
EXPORT_C const CFont* LafEnv::MatchFont( CArrayPtr<CAknSystemFont>& aSystemFonts,const TLogicalFont& aLogicalFont)
	{ 

	const CFont* font = NULL;

	// Need to check if aLogicalFont actually HAS a uid. If not, we  use its category 
	// (Note it is possible to have a TLogicalFont without a uid, but it is impossible 
	// to have one without a category.)
	TInt uidToMatch = aLogicalFont.iFontId.iUid;

	if (uidToMatch == KNullUid.iUid)
	//i.e. if there is no Uid 
		{	
			//this function call involves a call to matchFont itself, but this time WITH a Uid.
			//Should never end up in an infinite recursion
			//In fact should only ever be one call within another.
		font = GetRightFontFromCategory(aLogicalFont.iCategory);
		}
	else //this is the case that should happen nearly all the time
		{
        // Handle Symbian OS Logical Font Uids. Uid is translated to Series 60 logical font
        uidToMatch = MapSymbianLogicalFontUidToSeries60Id( uidToMatch );

        //if the fontid is not in the array or the Uid is there but without a CFont*,
		//it returns NULL
		font = GetFontFromSystemArray(aSystemFonts, uidToMatch);
        }


   	if ( !font )
        {
        // Create a Symbian font spec
        TFontSpec fontSpec;

    //	fontSpec.iTypeface.iName =  (*(productFontTable[foundIndex].iTypefaceName)).Left(KMaxTypefaceNameLength);

        fontSpec.iHeight = 12;
    	CWsScreenDevice& screenDev=*(CEikonEnv::Static()->ScreenDevice());
	    User::LeaveIfError(screenDev.GetNearestFontInPixels((CFont*&)font,fontSpec));
        }

    __ASSERT_ALWAYS( font, Panic(ELafPanicFontUidUnknownOrMissing) );
	return font;
	}

/**
 * Returns the nearest match to aBmpUid in aSystemBitmaps.
 */
EXPORT_C CFbsBitmap* LafEnv::MatchBitmap(const CArrayPtrFlat<CFbsBitmap>& aSystemBmps, TUid aBmpUid)
	{ // static
	CFbsBitmap* bitmap = NULL;
	const TInt32 uid = aBmpUid.iUid;
	if (uid >= KLafUidEikonTexturedVal && uid <= KLafUidEikonOptimVal)
		bitmap = aSystemBmps[uid-KLafUidEikonTexturedVal];
	__ASSERT_DEBUG(bitmap,Panic(ELafPanicBitmapIndexOutOfRange));
	return bitmap;
	}


/**
 * Draw's a logical border for aBorder, onto the graphics context aGc, in the rectangle aRect and using the
 * set of colors aBorderColors.
 */
EXPORT_C void LafEnv::DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc, const TRect& aRect, const TGulBorder::TColors& aBorderColors)
	{ // static
	if (AknBorderId::EAknBorderNotePopup <= aBorder.Type() && aBorder.Type() < AknBorderId::EAknBorderMax)
		{
		LafAknBorders::DrawLogicalBorder(aBorder, aGc, aRect, aBorderColors);
		return;
		}

		TInt type;

	switch(aBorder.Type())
		{
	case TGulBorder::EWindow:
		type=TGulBorder::EThickDeepRaisedWithOutline;
		break;
	case TGulBorder::EFlatContainer:
		type=TGulBorder::ESingleBlack;
		break;
	case TGulBorder::ERaisedContainer:
		type=TGulBorder::EShallowRaised;
		break;
	case TGulBorder::ESunkenContainer:
		type=TGulBorder::EShallowSunken;
		break;
	case TGulBorder::EFlatControl:
		type=TGulBorder::ESingleGray;
		break;
	case TGulBorder::ERaisedControl:
		type=TGulBorder::EDeepRaisedWithOutline;
		break;
	case TGulBorder::ESunkenControl:
		type=TGulBorder::EDeepSunkenWithOutline;
		break;
	case TGulBorder::EFocusedRaisedControl:
		type=TGulBorder::EDeepRaisedWithOutline;
		break;
	case TGulBorder::EFocusedSunkenControl:
		type=TGulBorder::EDeepSunkenWithOutline;
		break;
	default:
		type=TGulBorder::ENone;
		break;
		}

	TGulBorder border(type);
	border.SetAdjacent(aBorder.Adjacent());
	border.Draw(aGc,aRect,aBorderColors);
	}

/**
 * Returns the margins of a logical border for aBorder.
 */
EXPORT_C TMargins LafEnv::LogicalBorderMargins(const TGulBorder& aBorder)
	{ // static
	if (AknBorderId::EAknBorderNotePopup <= aBorder.Type() && aBorder.Type() < AknBorderId::EAknBorderMax)
		{
		return LafAknBorders::LogicalBorderMargins(aBorder);
		}

	TInt type;

	switch(aBorder.Type())
		{
	case TGulBorder::EWindow:
		type=TGulBorder::EThickDeepRaisedWithOutline;
		break;
	case TGulBorder::EFlatContainer:
		type=TGulBorder::ESingleBlack;
		break;
	case TGulBorder::ERaisedContainer:
		type=TGulBorder::EShallowRaised;
		break;
	case TGulBorder::ESunkenContainer:
		type=TGulBorder::EShallowSunken;
		break;
	case TGulBorder::EFlatControl:
		type=TGulBorder::ESingleGray;
		break;
	case TGulBorder::ERaisedControl:
		type=TGulBorder::EDeepRaisedWithOutline;
		break;
	case TGulBorder::ESunkenControl:
		type=TGulBorder::EDeepSunkenWithOutline;
		break;
	case TGulBorder::EFocusedRaisedControl:
		type=TGulBorder::EDeepRaisedWithOutline;
		break;
	case TGulBorder::EFocusedSunkenControl:
		type=TGulBorder::EDeepSunkenWithOutline;
		break;
	default:
		type=TGulBorder::ENone;
		break;
		}

	TGulBorder border(type);
	border.SetAdjacent(aBorder.Adjacent());
	return border.Margins();
	}

/**
 * Returns the hardware key that corresponds to the default key.
 */
EXPORT_C TBool LafEnv::IsDefaultKey(TUint aCharCode)
	{// static
	return aCharCode==EKeyDefault;
	}

/**
 * Returns the default line spacing used to format text paragraphs.
 */
EXPORT_C TInt LafEnv::DefaultLineSpacingInTwips()
	{//static
	return KLafEnvDefaultLineSpacingInTwips;
	}

EXPORT_C TInt LafEnv::EditableControlStandardHeight(const MLafEnv& /*aLafEnv*/ )
	{
    // primary cursor extent is used as the standard editor height.  This is in agreement with	
    // a text query's editor field.
    TAknWindowLineLayout primaryLayout = 
        AknLayoutScalable_Avkon::cursor_primary_pane().LayoutLine();
    TAknLayoutRect primaryCursor;
    // AknAppUi->ApplicationRect cannot be called yet. Just need any rectangle:
    TRect rectParent(0,0,2048,2048); 
    primaryCursor.LayoutRect( rectParent, primaryLayout );       
    return primaryCursor.Rect().Height();
	}

/**
 * Returns a constant value according to aConstatType.
 * @internal
 */
EXPORT_C TInt LafEnv::Constant(TConstantType aConstantType)
	{//static
	TInt retValue = 0;
	switch (aConstantType)
		{
	case EShadowHeight:
		retValue = KLafShadowHeight;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}

/**
* Sets any device specific font attributes to be applied to CEikonEnv's iCharFormatLayer.
* This format layer is used in Edwins. CEikonEnv's iCharFormatLayer may be used in other
* apps on some devices, so should be changed with care.
*
* @internal
*/
EXPORT_C void LafEnv::PrepareCharFormatAndMask(TCharFormat& aCharFormat,
											   TCharFormatMask& aCharFormatMask)
	{
    //static
    aCharFormat.iFontPresentation.iTextColor=KRgbDarkGreen;
    aCharFormatMask.SetAttrib(EAttColor);
	}


/**
* Allows individual DFRDs to specify a default directory for documents or to generate one.
*
* The parameters provided are not necessary in the UIKLAF implementation but are there
* to allow a DFRD enough information to generate a document directory based on the app being launched
*
* aFilePath receives the default / generated directory path.
*
* @internal
*/
EXPORT_C void LafEnv::GetDefaultPath(TDes& aFilePath,TUid /*aAppUid*/,RApaLsSession& /*aLs*/,CCoeEnv& /*aEnv*/)
	{
	aFilePath = KNullDesC;
	}

 /**
 * Loads the system resource file
 *
 * @internal 
 * @since App-Framework_6.2
 */
EXPORT_C TInt LafEnv::LoadCoreResFileL(CCoeEnv& aEnv)
/**
@publishedPartner
@test
*/
	{
	_LIT(KCoreResFileName,"z:\\Resource\\Uiklaf\\eikcore.rsc");
	return LoadResFileL(aEnv, KCoreResFileName);	
	}

 /**
 * Loads the private resource file
 *
 * @internal  
 * @since App-Framework_6.2
 */
EXPORT_C TInt LafEnv::LoadPrivResFileL(CCoeEnv& aEnv)
/**
@publishedPartner
@test
*/
	{
    // UNBRANCH TODO: Should this path come from a header?
	_LIT(KPrivResFileName,"z:\\Resource\\Uiklaf\\eikpriv.rsc");
	return LoadResFileL(aEnv, KPrivResFileName);
	}

 /**
 * Returns the Coctl Resource File
 * 
 * @internal 
 * @since App-Framework_6.2
 */
EXPORT_C const TDesC& LafEnv::CoctlResourceFile()
/**
@publishedPartner
@test
*/
	{
	_LIT(KCoctlResFileName,"z:\\System\\Data\\eikcoctl.rsc");
	return KCoctlResFileName;
	}

/**
 * Allows to update the list of system bitmaps, aBitmaps, by using aColorList in order to determine what bitmaps
 * need to be un/loaded.
 * 
 * @internal 
 * @since 6.2
 */
EXPORT_C void LafEnv::UpdateSystemBitmapsL(CCoeEnv& /*aEnv*/, CArrayPtrFlat<CFbsBitmap>& /*aBitmaps*/, const CColorList& /*aColorList*/)
/**
@publishedPartner
@test
*/
	{
	}

/**
@publishedAll
@released
*/
const TInt KInfoNoteMaxLen=100;

/** Specifies the maximum length of the message buffer. 

@publishedAll
@released */
typedef TBuf<KInfoNoteMaxLen> TEikInfoNoteBuf;

LOCAL_C void InfoNote(const TDesC& aDes)
	{
	TRAP_IGNORE(
        CAknInformationNote* note = new(ELeave) CAknInformationNote;
        CleanupStack::PushL(note);
        note->ExecuteLD(aDes);
        CleanupStack::Pop(note);
	    );
	}

LOCAL_C void InfoNote(TInt aResourceId,VA_LIST aList)
    {
    TEikInfoNoteBuf formatString;
	CEikonEnv::Static()->ReadResource(formatString,aResourceId);
	TEikInfoNoteBuf messageString;
	messageString.FormatList(formatString,aList);
	InfoNote(messageString);
    }
    

EXPORT_C void LafEnv::InfoNote(TInt aResourceId,...)
    {
    VA_LIST list;
    VA_START(list,aResourceId);
    ::InfoNote(aResourceId,list);
    }


EXPORT_C TBool LafEnv::IsTaskListDisabledAtInitialization()
    {
    return ETrue;
    }

EXPORT_C void LafEnv::Beep()
    {
    }

EXPORT_C CColorList* LafEnv::CreateColorListL( CEikonEnv& /*aEnv*/ )
    {
    CArrayFix<TRgb>* colors=new(ELeave) CArrayFixFlat<TRgb>(8);
	CleanupStack::PushL(colors);
    for (TInt ii=EColorWindowBackground;ii<=EColorLabelHighlightFullEmphasis;ii++)
        {
        colors->InsertL(TLogicalColor(ii), CAknEnv::AvkonColor(KLogicalToAvkonColorMap[ii]));
		}
	CColorList* colorList=CColorList::NewL(colors);
	CleanupStack::Pop(); // colors. Ownership has been transferred away
    return colorList;
    }        

EXPORT_C void LafEnv::UpdateColorListL( CColorList* aColorList )
    {
    for (TInt ii=EColorWindowBackground;ii<=EColorLabelHighlightFullEmphasis;ii++)
		{
        aColorList->SetColor(TLogicalColor(ii), CAknEnv::AvkonColor(KLogicalToAvkonColorMap[ii]));
		}
    }


EXPORT_C void LafEnv::UpdateSystemFontsL( CCoeEnv* /*aEnv*/, CArrayPtr<CAknSystemFont>& aSystemFonts )
    {
	TInt count = aSystemFonts.Count();
	for ( TInt i = 0; i < count; ++i )
		{
		CAknSystemFont* font = aSystemFonts[i];
		CFont* cFont = font->Font();
        if (cFont )
            {
            // Font is always of this type (See constructors in this class)
            CAknFontIdLayoutFont* layoutFont = static_cast<CAknFontIdLayoutFont*>(cFont);
            // Do not update encoded fonts, as you will just get the same font back again
            if ( !TAknFontId::IsEncodedFont( layoutFont->FontId() ) )
                layoutFont->Update();
            }
        }
    }


EXPORT_C void LafEnv::ReleaseSystemFonts( CArrayPtr<CAknSystemFont>& aSystemFonts )
	{
	const TInt fontCount=aSystemFonts.Count();
	for (TInt ii=0;ii<fontCount;ii++)
		{
		delete aSystemFonts[ii];
		}
	}
	
NONSHARABLE_CLASS(CAknBusyMsgWin): public CBase, public MEikBusyMsgWin
    {
public:    
	CAknBusyMsgWin(CEikonEnv& aEikonEnv):iEnv(aEikonEnv)
	    {
	    iRdSupport = BaflUtils::FileExists( iEnv.FsSession(), KRDSupport );
	    }
	    
    ~CAknBusyMsgWin()
        {
        delete iImpl;
        }

    void ConstructL(RWindowGroup& aWindowGroup)
        {
        iImpl = new (ELeave) CEikBusyMsgWin(iEnv);
        iImpl->ConstructL(aWindowGroup);
        }
public:  //from MEikBusyMsgWin
	void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, 
	    TTimeIntervalMicroSeconds32 aInitialDelay)
	    {
#ifdef _DEBUG
	    iImpl->StartDisplaySpecifyingInitialDelay(aText, aCorner, aInitialDelay);
#else
        if(iRdSupport)
            {
            iImpl->StartDisplaySpecifyingInitialDelay(aText, aCorner, aInitialDelay);
            }
#endif
	    }
    
	void StartDisplay(const TDesC& aText, TGulAlignment aCorner)
	    {
#ifdef _DEBUG
	    iImpl->StartDisplay(aText, aCorner);
#else
        if(iRdSupport)
            {
            iImpl->StartDisplay(aText, aCorner);
            }
#endif
	    }	    

	void Release()
	    {
	    delete this;
	    }
private:
    CEikBusyMsgWin* iImpl;
    CEikonEnv&      iEnv;
    TBool           iRdSupport;
    };	

EXPORT_C MEikBusyMsgWin* LafEnv::NewBusyMsgWinL(CCoeEnv& aEnv)
    {
    CAknBusyMsgWin* self = new(ELeave) CAknBusyMsgWin( static_cast<CEikonEnv&>(aEnv) );
    CleanupStack::PushL( self );
    self->ConstructL( aEnv.RootWin() );
    CleanupStack::Pop();//self
    return self;
    }
   
NONSHARABLE_CLASS(CAknInfoMsgWin): public CBase, public MEikInfoMsgWin
    {
public:    
	CAknInfoMsgWin(CEikonEnv& aEikonEnv):iEnv(aEikonEnv)
	    {
	    iRdSupport = BaflUtils::FileExists( iEnv.FsSession(), KRDSupport );    
	    }
	    
    ~CAknInfoMsgWin()
        {
        delete iImpl;
        }

    void ConstructL(RWindowGroup& aWindowGroup, TInt aParam)
        {
        iImpl = new (ELeave) CEikInfoMsgWin(iEnv);
        iImpl->ConstructL(aWindowGroup, aParam);
        }

public:  //from MEikInfoMsgWin
    
	void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration)
	    {
#ifdef _DEBUG
	    iImpl->StartDisplaySpecifyingDuration(aText, aCorner, aDuration);
#else
        if(iRdSupport)
            {
            iImpl->StartDisplaySpecifyingDuration(aText, aCorner, aDuration);
            }
#endif
	    }

	void StartDisplay(const TDesC& aText, TGulAlignment aCorner)
	    {
#ifdef _DEBUG
	    iImpl->StartDisplay(aText, aCorner);
#else	    
        if(iRdSupport)
            {
            iImpl->StartDisplay(aText, aCorner);
            }
#endif
	    }	    

    void CancelDisplay()
        {
        if (iImpl)
            iImpl->CancelDisplay();
        }

	void Release()
	    {
	    delete this;
	    }
    	
private:
    CEikInfoMsgWin* iImpl;
    CEikonEnv&      iEnv;
    TBool           iRdSupport;
    };
       

EXPORT_C MEikInfoMsgWin* LafEnv::NewInfoMsgWinL(CCoeEnv& aEnv, RWindowGroup& aGroup)
    {
    CAknInfoMsgWin* self = new(ELeave) CAknInfoMsgWin( static_cast<CEikonEnv&>(aEnv ));
    CleanupStack::PushL( self );
    self->ConstructL( aGroup, 0);
    CleanupStack::Pop();//self
    return self;
    }

EXPORT_C MEikInfoMsgWin* LafEnv::NewInfoMsgWinL(CCoeEnv& aEnv )
    {
    CAknInfoMsgWin* self = new(ELeave) CAknInfoMsgWin( static_cast<CEikonEnv&>(aEnv ));
    CleanupStack::PushL( self );
    self->ConstructL( aEnv.RootWin(), 0 );
    CleanupStack::Pop();//self
    return self;
    }

/* Return the name of the clock dll */
EXPORT_C const TDesC& LafEnv::ClockDllName()
    {
#if defined(__WINS__)
		_LIT(KClockDllName,"CLOCKA.DLL");
#else
		_LIT(KClockDllName,"Z:\\SYSTEM\\LIBS\\CLOCKA.DLL");
#endif
    return KClockDllName;
    }
