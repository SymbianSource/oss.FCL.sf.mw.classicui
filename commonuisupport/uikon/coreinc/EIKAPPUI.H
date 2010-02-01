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

#ifndef __EIKAPPUI_H__
#define __EIKAPPUI_H__

#include <coeaui.h>
#include <coemain.h>
#include <eikmobs.h>
#include <apadef.h>
#include <vwsdef.h>
#include <eikdef.h>
#include <baerrhan.h>
#include <eikaufty.h>
#include <coemop.h>

class CEikDocument;
class CEikApplication;
class CEikAppUiExtra;
class MApaEmbeddedDocObserver;
struct SExtendedError;
class CApaCommandLine;

/** Handles application-wide aspects of the application's user interface such 
as the menu bar, toolbar pop-up menus, opening and closing files and exiting the 
application cleanly. 

Every GUI application should use its own class derived from CEikAppUi. 

An app UI's main role is to handle commands, in its HandleCommandL() function. 
These may be invoked using the menu bar, toolbar, or hotkeys; the commands 
that an app UI handles are specified in the application's resource file.

In addition, the app UI normally needs to respond to other kinds of events, by 
providing suitable implementations of the following virtual functions, all 
inherited from CCoeAppUi: 

- HandleKeyEventL(): Key events.

- HandleForegroundEventL(): Application switched to foreground.

- HandleSwitchOnEventL(): Machine switched on.

- HandleSystemEventL(): System events.

- HandleApplicationSpecificEventL(): Application-specific events.

@publishedAll
@released */
class CEikAppUi : public CCoeAppUi, public MEikMenuObserver, public MCoeMessageObserver, public MObjectProvider
	{
public:
	IMPORT_C ~CEikAppUi();
	IMPORT_C CEikAppUi();
public: // new functions
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void HandleModelChangeL();
	IMPORT_C TLanguage ApplicationLanguageL() const;
	IMPORT_C CEikApplication* Application() const;
	IMPORT_C CEikDocument* Document() const;
	IMPORT_C void SetDocument(CEikDocument* aDocument);
	inline CEikAppUi* ContainerAppUi() const;
	IMPORT_C void SetEmbeddedDocInfo(MApaEmbeddedDocObserver* aObserver, TBool aReadOnly);
	IMPORT_C virtual TBool ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName, const TDesC8& aTail);
	IMPORT_C virtual TBool ProcessCommandParametersL(CApaCommandLine& aCommandLine);
	// Application screen extent
	IMPORT_C TRect ClientRect() const;
	IMPORT_C virtual TRect ApplicationRect() const;
	// Menu utilities
	IMPORT_C void LaunchPopupMenuL(TInt aResourceId, const TPoint& aTargetPos, TPopupTargetPosType aTargetType, const CEikHotKeyTable* aHotKeyTable = NULL);
	IMPORT_C virtual void StopDisplayingMenuBar();
	// Fading effect
	IMPORT_C TBool FadeWhenInBackground();
	IMPORT_C virtual void SetFadedL(TBool aFaded);
	inline void SetFaded(TBool aFaded);			//mm: has no implementation
public: // new function
	IMPORT_C virtual void ReportResourceChangedToAppL(TInt aType);
	IMPORT_C virtual void HandleCommandL(TInt aCommand);
	IMPORT_C virtual void ProcessMessageL(TUid aUid, const TDesC8& aParams);
	IMPORT_C virtual void OpenFileL(const TDesC& aFileName);
	IMPORT_C virtual void CreateFileL(const TDesC& aFileName);
	IMPORT_C virtual TErrorHandlerResponse HandleError(TInt aError, const SExtendedError& aExtErr, TDes& aErrorText, TDes& aContextText);
	IMPORT_C virtual void HandleResourceChangeL(TInt aType);
public: // from CCoeAppUi
	IMPORT_C void PrepareToExit();
protected: // new functions
	// Construction
	IMPORT_C void BaseConstructL(TInt aAppUiFlags = 0);
	IMPORT_C void ReadAppInfoResourceL(TInt aResourceFileOffset = 0);
	IMPORT_C void CreateHotKeyControlL(TInt aResourceId);
	IMPORT_C TBool ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName);
	// User data change management
	IMPORT_C void SetDocChanged();
	IMPORT_C void SaveAnyChangesL();
	IMPORT_C void SaveL();
	IMPORT_C virtual void Exit();
	// Utility
	IMPORT_C void ClosePopup();		//mm: deprecate?
protected: // from MEikMenuObserver
	IMPORT_C void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
protected: // from CCoeAppUi
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C void HandleScreenDeviceChangedL();
protected: // from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommand);
private: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis);
protected: // from MCoeMessageObserver
	IMPORT_C MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
protected:	// from MObjectProvider
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	IMPORT_C virtual MObjectProvider* MopNext();
private: 
	// Validate document file type
	IMPORT_C virtual TBool ValidFileType(TUid aFileUid) const;
private: // spare virtuals	
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void Reserved_4();
public:
	/** Application resource file and screen furniture flags, passed to BaseConstructL(). */
	enum
		{
		/** Application uses a standard resource file. */
		EStandardApp			= 0x00,
		/** Application has no resource file. */
		ENoAppResourceFile		= 0x01,
		/** Application uses a different resource file from the standard. */
		ENonStandardResourceFile= 0x02,
		/** Application uses no screen furniture. */
		ENoScreenFurniture		= 0x04,
		/** Indicates the last value in the enum. */
		ELastReservedEikAppUiFlag = 0x8000
		};
public:
	IMPORT_C void ReportResourceChangedToAppStackL(CEikAppUi* aTopApp, TInt aEventId);
	CEikAppUiExtra* AppUiExtra();
private:
	void CreateResourceIndependentFurnitureL();
	TBool ValidFileExistsL(const TDesC& aFileName);
protected:
	/** A pointer to the application's document. */
	CEikDocument* iDocument;
	/** A pointer to the containing app UI. This is NULL for non-embedded 
	apps. */
	CEikAppUi* iContainerAppUi;
	/** Embedded document observer. */
	MApaEmbeddedDocObserver* iDoorObserver;
	/** Indicates whether or not this is the app UI for an embedded, 
	read-only document. */
	TBool iEmbeddedAndReadOnly;
	TInt iFlags;
private:
	enum
		{
		EEmbedded = 0x01
		};
private:
	CEikAppUiExtra* iAppUiExtra;
	};



/** Returns the app UI inside which this app UI is embedded.
Embedded app UIs are used for editing embedded documents.

@return A pointer to this object's container app UI. NULL if this app 
UI is not embedded */
inline CEikAppUi* CEikAppUi::ContainerAppUi() const
	{ return iContainerAppUi; }

#endif	// __EIKAPPUI_H__
