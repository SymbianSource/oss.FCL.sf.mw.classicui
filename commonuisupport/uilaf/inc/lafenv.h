// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __LAFENV_H__
#define __LAFENV_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulalign.h>
#include <lafmain.h>
#include <apgcli.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikinfomsgwin.h>
#include <eikbusymsgwin.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikmsg.h>

class MParser;
class CCoeEnv;
class CFont;
class TLogicalFont;
class CLafSystemFont;
class MEikInfoMsgWin;
class MEikBusyMsgWin;

class LafEnv
/** Application environment level LAF functions.

@publishedPartner 
@released */
	{
public:
	/** Creates an EText parser.
	
	@param aIndex Index of parser to retrieve. A LAF can supply multiple parsers, 
	indexed from 0.
	@return EText parser */
	IMPORT_C static MParser* CreateTextParserL(TInt aIndex);
	/** Draws a logical border.
	
	@param aBorder Border specification to draw
	@param aGc Graphics context to which to draw
	@param aRect Drawing rectangle
	@param aBorderColors Colours with which to draw */
	IMPORT_C static void DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aRect,const TGulBorder::TColors& aBorderColors);
	/** Gets the margins of a specified logical border.
	
	@param aBorder Border specification
	@return Border's margins */
	IMPORT_C static TMargins LogicalBorderMargins(const TGulBorder& aBorder);
	/** Populates an array with a set of system bitmaps.
	
	CEikonEnv calls this to get system bitmaps, and uses the array in subsequent 
	calls to MatchBitmap().
	
	@param aEnv Application's control environment
	@param aBitmaps On return, array of system bitmaps */
	IMPORT_C static void CreateSystemBitmapsL(CCoeEnv& aEnv, CArrayPtrFlat<CFbsBitmap>& aBitmaps);
	/** Populates an array with a set of system fonts.
	
	CEikonEnv calls this to get system fonts, and uses the array in subsequent 
	calls to MatchFont().
	
	A minimum of one font must be created. 
	
	@param aEnv Application's control environment
	@param aFonts On return, array of system fonts */
	IMPORT_C static void CreateSystemFontsL(CCoeEnv& aEnv,CArrayPtr<CLafSystemFont>& aFonts);
	/** Gets the nearest match in the specified fonts for a specified logical system 
	font.
	
	The return value must be non-NULL.
	
	@param aFonts Fonts from which to select the match
	@param aLogicalFont The logical font to match
	@return Font that is the best match to aLogicalFont */
	IMPORT_C static const CFont* MatchFont(CArrayPtr<CLafSystemFont>& aFonts,const TLogicalFont& aLogicalFont);
	/** Gets the nearest match in the specified bitmaps for a specified system bitmap 
	type.
	
	The desired bitmap is specified by the identifer aBmpUid: for possible UIDs, 
	see KLafUidEikonTexturedVal etc.
	
	The return value must be non-NULL.
	
	@param aSystemBmps Bitmaps from which to select the match
	@param aBmpUid The bitmap type to match
	@return Bitmap that is the best match to aBmpUid */
	IMPORT_C static CFbsBitmap* MatchBitmap(const CArrayPtrFlat<CFbsBitmap>& aSystemBmps, TUid aBmpUid);
	/** Gets the corner of the screen which the busy message should appear in by default 
	on the device. 
	
	@return Default corner
	@see CEikonEnv::BusyMsgL() */
	IMPORT_C static TGulAlignment DefaultBusyMsgCorner();
	/** Tests if the specified key corresponds to the hardware default key.
	
	@param aCharCode Key to test
	@return True if the key is the default */
	IMPORT_C static TBool IsDefaultKey(TUint aCharCode);
	/** Gets the default line spacing used to format text paragraphs.
	
	@return Default line spacing in twips */
	IMPORT_C static TInt DefaultLineSpacingInTwips();
	/** Gets the height of single-line edit control for the system normal font.
	
	@param aLafEnv Environment access
	@return Height of single-line edit control */
	IMPORT_C static TInt EditableControlStandardHeight(const MLafEnv& aLafEnv);
	/** Sets any device-specific font attributes to be applied to the system character 
	formatting layer.
	
	Applications can access the format layer through CEikonEnv::SystemCharFormatLayerL(). 
	This format layer is also used in Edwins.
	
	@param aCharFormat On return, the character formatting to apply
	@param aCharFormatMask On return, the character formatting mask to apply */
	IMPORT_C static void PrepareCharFormatAndMask(TCharFormat& aCharFormat,TCharFormatMask& aCharFormatMask);
	/** Specifies (and creates if necessary) a default directory for documents.
	
	The function is called on application startup. The parameters provided are 
	to allow an implementation to generate a document directory based on the application 
	being launched.
	
	@param aFilePath On return, the default / generated directory path
	@param aAppUid UID of application being launched
	@param aLs Application's session with the Application Architecture server
	@param aEnv Thread's control environment */
	IMPORT_C static void GetDefaultPath(TDes& aFilePath,TUid aAppUid,RApaLsSession& aLs,CCoeEnv& aEnv);
	/** Loads the system resource file.
	
	The system resource file defines resources required by the system environment, 
	and which can also be used by applications. The function is called by CCoeEnv's 
	construction function.
	
	@param aEnv Thread's control environment
	@return System wide error code */
	IMPORT_C static TInt LoadCoreResFileL(CCoeEnv& aEnv);
	/** Loads the private resource file.
	
	The private resource file defines resources required by the system environment, 
	but not intended for application use. The function is called by CCoeEnv's 
	construction function.
	
	@param aEnv Thread's control environment
	@return System wide error code */
	IMPORT_C static TInt LoadPrivResFileL(CCoeEnv& aEnv);
	/** Gets the name of the resource file that contains resources for the EIKCOCTL 
	component.
	
	@return Resource file for the EIKCOCTL component */
	IMPORT_C static const TDesC& CoctlResourceFile();
	/** Allows the LAF to update the list of system bitmaps, in response to a colour 
	settings change.
	
	@param aEnv Thread's control environment
	@param aBitmaps On return, updated array of system bitmaps
	@param aColorList New colour settings */
	IMPORT_C static void UpdateSystemBitmapsL(CCoeEnv& aEnv, CArrayPtrFlat<CFbsBitmap>& aBitmaps, const CColorList& aColorList);
	
	/**	Performs the releasing of the fonts but doesn't delete the array itself
	
	@param aSystemFontArray array of fonts to release
	*/
	IMPORT_C static void ReleaseSystemFonts( CArrayPtr<CLafSystemFont>& aSystemFontArray);
	
	/** Creates busy message window.
	
	@param aEnv Thread's control environment
	@return Busy message window */
	IMPORT_C static MEikBusyMsgWin* NewBusyMsgWinL(CCoeEnv& aEnv);
	/** Creates info message window.
	
	@param aEnv Thread's control environment
	@return Info message window */
	IMPORT_C static MEikInfoMsgWin* NewInfoMsgWinL(CCoeEnv& aEnv);
		
	/** Creates info message window, overridden function to allow another RWindowGroup to be
	used rather the the the CCoeEnv's RootWin() function.
		
	@param aEnv Thread's control environment
	@param aWinGroup window group for displaying the Info Msg
	@return Info message window */
    	IMPORT_C static MEikInfoMsgWin* NewInfoMsgWinL(CCoeEnv& aEnv, RWindowGroup& aWinGroup);
	/** Asks if display of the task list is disabled during initialization

	@return ETrue if task list is disabled, otherwise EFalse */
	IMPORT_C static TBool IsTaskListDisabledAtInitialization();
	/** Displays a one or two line alert as a notifier window customisable by the system GUI.

	@param aMsg1 Line one of the message to be displayed.
	@param aMsg2 Line two of the message to be displayed */
	IMPORT_C static void DisplayAlertAsNotifier(const TDesC& aMsg1, const TDesC& aMsg2);
	
	/** Updates an existing color list
	
	@param aColorList The color list to be updated. */
	IMPORT_C static void UpdateColorListL(CColorList* aColorList);
	
	/** Plays an audible alert, if supported by the system GUI. */
	IMPORT_C static void Beep();
	
	/** Updates an existing array of system fonts.
	
	@param aEnv Thread's control environment
	@param aSystemFontArray The array of fonts to be updated */
	IMPORT_C static void UpdateSystemFontsL(CCoeEnv* aEnv, CArrayPtr<CLafSystemFont>& aSystemFontArray);

	/** A list of events that are handled by the HandleExtensionEventL() function.*/
	enum TLafEnvExtensionEvent 
        {
        /** Event sent in CEikonEnv::ConstructL right before CCoeEnv::ConstructL() */
        ELafEnvPreCoeEnvConstructL,
        /** Event sent in CEikonEnv::ConstructL right after CCoeEnv::ConstructL() */
        ELafEnvPostCoeEnvConstructL
        };
	
	/** Handles events listed by TLafEnvExtensionEvent
	@param aEnv The instance of CEikonEnv from which this function has been called
	@param aEvent The event
	*/
	IMPORT_C static void HandleExtensionEventL(CEikonEnv& aEnv, TLafEnvExtensionEvent aEvent);
	
    /** Allows debug keys to display output.
    @param aResourceId The resource to use for the note
    */
    IMPORT_C static void InfoNote(TInt aResourceId,...);

	/** Creates a default system colour list. 
	@param aEnv The instance of CEikonEnv from which this function has been called
	@return A list of colours
	*/
	IMPORT_C static CColorList* CreateColorListL(CEikonEnv& aEnv);
	
	/** Gets the name of the clock DLL
	@return The name of the clock DLL
	*/
	IMPORT_C static const TDesC& ClockDllName();

	/** The behaviour of CEikonEnv can be customized. This enum lists
	the things that can be customized. */
	enum TLafEnvPolicyItem
        {
        /** The action to take when there is an error during startup. */
        ELafEnvPolicyExitIfErrorDuringStartup,
        /** The action to take when the document is corrupt. */
        ELafEnvPolicyDeleteCorruptDocumentAndContinue,
        /** This affects the way the environment is deleted. */
        ELAfEnvPolicyDeferredEnvironmentDeletion,
        };

	/** CEikonEnv will use this function to find out how it should behave.
	The list of things that can be customized this way are listed by 
	TLafEnvPolicyItem.
	@param aItem The policy item.
	@return An integer that indicates what the action should be.
	*/
    IMPORT_C static TInt PolicyItem(TLafEnvPolicyItem aItem);

public:
	inline static TInt ShadowHeight();
private:
	/** Defines types of constant setting relevant to LAFs. */
	enum TConstantType
		{
		/** Window shadow height. */
		EShadowHeight
		};
private:
	/** Gets the value for a specified constant setting.
	
	@param aConstant Type of constant setting to get
	@return Value for the constant setting */
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

// identifiers for legacy system fonts

/** UID for the system "normal" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidNormalFontVal		0x10005F02

/** UID for the system "title" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidTitleFontVal			0x10005F03

/** UID for the system "annotation" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidAnnotationFontVal	0x10005F04

/** UID for the system "legend" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidLegendFontVal		0x10005F05

/** UID for the system "symbol" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidSymbolFontVal		0x10005F06

/** UID for the system "dense" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidDenseFontVal			0x10005F07

// identifiers for legacy system bitmaps
/** UID for a textured block system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonTexturedVal		0x100048F4

/** UID for a gray block system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonGrayVal			0x100048F5

/** UID for a horizontal option button system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptiVal			0x100048F6

/** UID for a highlighted horizontal option button system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptihVal		0x100048F7

/** UID for a horizontal option button mask system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptimVal		0x100048F8

// Inlines

inline TInt LafEnv::ShadowHeight()
/** Gets the height of shadows to apply to windows. 

@return Shadow height. */
	{//static
	return Constant(EShadowHeight);
	}

#endif
