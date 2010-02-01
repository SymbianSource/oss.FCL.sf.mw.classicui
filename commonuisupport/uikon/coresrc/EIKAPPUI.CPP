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

#include <s32file.h>
#include <basched.h>
#include <w32std.h>
#include <gulcolor.h>
#include <gulutil.h>
#include <coeutils.h>
#include <apgtask.h>
#include <apgwgnam.h>
#include <eikappui.h>
#include <eikenv.h>
#include <eikdef.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <eikproc.h>
#include <eikpanic.h>
#include "EIKSHUT.H"
#include <eikaufty.h>
#include <eikbhelp.h>
#include <uikon.hrh>
#include <uiklafgt/eikcore.rsg>
#include <uiklaf/private/lafappui.h>
#include <apgcli.h>
#include <eikserverapp.h>
#include "eikprivate.h"
#include <uiklaf/private/lafenv.h>
#include "eikdefconst.h"

/** This class provides additional members to CEikAppUi without breaking 
binary compatibility An instance of this is owned by CEikAppUi and is not
meant for external visibility

@see CEikAppUi */
NONSHARABLE_CLASS(CEikAppUiExtra) : public CBase
	{
public:
	CEikAppUiExtra(CEikAppUi& aEikAppUi);
	~CEikAppUiExtra();
private:
	CEikAppUi& iEikAppUi;
	};

CEikAppUiExtra::CEikAppUiExtra(CEikAppUi& aEikAppUi) : iEikAppUi(aEikAppUi)
	{
	}
	
CEikAppUiExtra::~CEikAppUiExtra()
	{	
	}

/** Empty default constructor. */
EXPORT_C CEikAppUi::CEikAppUi()
    {
    }

/** Destructor.

Deletes any resources allocated by this CEikAppUi during its construction. 
*/
EXPORT_C CEikAppUi::~CEikAppUi()
    {
	iCoeEnv->RemoveMessageObserver(*this);
	if (LafEnv::PolicyItem(LafEnv::ELAfEnvPolicyDeferredEnvironmentDeletion))
        {
	    if (!iContainerAppUi)
	        iEikonEnv->PostAppUiDestroy();
        }

	if (iContainerAppUi)
		{
		if(iFlags & EEmbedded)
			{
			MEikAppUiFactory* uiFactory = iEikonEnv->AppUiFactory(*this);
			ASSERT(uiFactory);
			if (uiFactory)
				{
				uiFactory->DestroyEmbedded(*iEikonEnv);				
				}
			}

		iCoeEnv->SetAppUi(iContainerAppUi);
        TWsEvent event;
        event.SetType(EEventNull);
        TRAP_IGNORE(iContainerAppUi->HandleApplicationSpecificEventL( KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes, event));
		}

	if (iDocument)
		iDocument->NullAppUi();
		
	delete iAppUiExtra;
    }

/** Handles changes to the model associated with this CEikAppUi's application. 

The implementation is empty in CEikAppUi. 
*/
EXPORT_C void CEikAppUi::HandleModelChangeL()
	{
	}	

/** Completes construction. 

This simply calls BaseConstructL(). 
*/
EXPORT_C void CEikAppUi::ConstructL()
	{
	BaseConstructL();
	}

/** Initialises this app UI with standard values. 

The application's standard resource file will be read unless either the 
ENoAppResourceFile or ENonStandardResourceFile flag is specified.

@param aAppUiFlags Application user interface flags, EStandardApp for example. 
*/
EXPORT_C void CEikAppUi::BaseConstructL(TInt aAppUiFlags)
    {
    TWsEvent event;
    event.SetType(EEventNull);
    
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
    iContainerAppUi = static_cast<CEikAppUi*>(iCoeEnv->SetAppUi(this));
    iAppUiExtra = new (ELeave) CEikAppUiExtra(*this); 
	if (iContainerAppUi)
		{
        HandleApplicationSpecificEventL( KEikNotifyPreCreateEmbeddedL, event );
		appUiFactory->CreateEmbeddedL(*iEikonEnv);
		iFlags |= EEmbedded;
		HandleApplicationSpecificEventL( KEikNotifyPostCreateEmbeddedL, event );
		TRAP_IGNORE(iContainerAppUi->HandleResourceChangeL(KEikMessageEmbedLevelChange));
		iContainerAppUi->HandleStackedControlsResourceChange(KEikMessageEmbedLevelChange);
		}
		
    CCoeAppUi::ConstructL(iContainerAppUi);
    HandleApplicationSpecificEventL( KEikPostCoeAppUiConstructL, event );
	if (!iContainerAppUi)
		iEikonEnv->ControlStackReadyL();
	
	if (!(aAppUiFlags&(ENoAppResourceFile|ENonStandardResourceFile)))
	    ReadAppInfoResourceL();
	
	else if (!(aAppUiFlags&ENoScreenFurniture))
		CreateResourceIndependentFurnitureL();
	
	iCoeEnv->AddMessageObserverL(*this);
	iEikonEnv->PostAppUiInitializeL();
	iCoeEnv->RootWin().EnableScreenChangeEvents();
    }

EXPORT_C void CEikAppUi::ReadAppInfoResourceL(TInt aResourceFileOffset)
/** Reads the application UI information at the specified offset in the 
app's standard resource file.

This function is called by BaseConstructL(), unless either of the ENoAppResourceFile or 
ENonStandardResourceFile flags was specified.

@param aResourceFileOffset Offset of the application information in the resource file. */
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->ReadAppInfoResourceL(aResourceFileOffset, this);
	}

EXPORT_C TRect CEikAppUi::ClientRect() const
/** Gets the area of the screen available to the application for drawing. 

This does not include the space available for UI components like the 
menu bar.

The co-ordinates of the rectangle are relative to the whole screen 
area so, for example, the co-ordinate for the top, left point of the area 
available for drawing may be (0, 45).

@return The area of the screen available to the application for drawing. */
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	return(appUiFactory->ClientRect());
	}

EXPORT_C TRect CEikAppUi::ApplicationRect() const
/** Gets the total area of the screen available to the application. 

This includes the space available for UI components like the menu bar.

@return The total area of the screen available to the application. */
	{
	TRect rect(iCoeEnv->ScreenDevice()->SizeInPixels());
	LafAppUi::ReduceRect(rect);
	return rect;
	}

/**
Checks for, and closes, popups and menubars before calling HandleCommandL()
@see MEikCommandObserver::ProcessCommandL( TInt aCommand )
@see CEikAppUi::HandleCommandL( TInt aCommand ) 
*/
EXPORT_C void CEikAppUi::ProcessCommandL(TInt aCommand)
    {
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	if (appUiFactory->Popup())
	    ClosePopup();
    else if (appUiFactory->MenuBar())
        StopDisplayingMenuBar();
    if (aCommand!=EEikCmdCanceled)
	    HandleCommandL(aCommand);
    }

/**
Wrapper for MEikAppUiFactory::CreateResourceIndependentFurnitureL
@internalComponent
@see MEikAppUiFactory::CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi)
*/
void CEikAppUi::CreateResourceIndependentFurnitureL()
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->CreateResourceIndependentFurnitureL(this);
	}

EXPORT_C void CEikAppUi::HandleCommandL(TInt /*aCommand*/)
/** Handles user commands. 

This is overridden by subclasses to handle commands passed on by the 
application framework. This function is called by CEikAppUi::ProcessCommandL(), 
and has an empty implementation. Commands can be invoked using a menu item, 
a hotkey, or a button (for instance in a toolbar or dialog).

@param aCommand The ID of the command. */
    {
    }

EXPORT_C void CEikAppUi::CreateHotKeyControlL(TInt aResourceId)
/** Creates a hotkey control.

Constructs a CEikHotKeyControl whose CEikHotKeyTable is specified by a resource 
ID, and adds it to the control stack.

@param aResourceId ID of a hotkey table resource. */
    {
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->CreateHotKeyControlL(aResourceId, this);
    }

EXPORT_C void CEikAppUi::LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType,const CEikHotKeyTable* aHotKeyTable)
/** Launches a popup menu. 

This function is called by CEikAppUI::HandleSideBarMenuL(). 

@param aResourceId ID of the menu resource. 
@param aTargetPos Position of the corner of the menu identified by aTargetType. 
@param aTargetType The corner of the menu by which the menu will be positioned. 
@param aHotKeyTable Optional menu hotkey table. */
    {
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->LaunchPopupMenuL(aResourceId,aTargetPos,aTargetType,aHotKeyTable, this);
    }

EXPORT_C void CEikAppUi::ClosePopup()
/** Closes any currently visible popup menu. */
    {
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->ClosePopup(this);
    }

EXPORT_C void CEikAppUi::StopDisplayingMenuBar()
/** Stops displaying the application's menu bar. 

If the application has no menu bar, or if the menu bar is not visible, 
this function has no effect. */
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->StopDisplayingMenuBar();
	}

EXPORT_C TBool CEikAppUi::FadeWhenInBackground()
/** Tests whether the application is set to fade when in the background.

@return ETrue if the application is set to fade when in the background, EFalse 
if not. */
	{
	return LafAppUi::FadeWhenInBackground();
	}


/**
This is a virtual function.
The base class implemenatiation causes the root window and all of its children to change to the desired faded state.
@param aFaded  The desired faded state
*/
EXPORT_C void CEikAppUi::SetFadedL(TBool aFaded)
	{
	const TInt message=(aFaded? KEikMessageFadeAllWindows : KEikMessageUnfadeWindows);
	HandleResourceChangeL(message);
	HandleStackedControlsResourceChange(message);
	iCoeEnv->RootWin().SetFaded(aFaded,RWindowTreeNode::EFadeIncludeChildren);
	}

/**
@see MEikMenuObserver::SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis)
*/
EXPORT_C void CEikAppUi::SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis)
    {
    UpdateStackedControlFlags(aMenuWindow,aEmphasis? 0: ECoeStackFlagRefusesFocus,ECoeStackFlagRefusesFocus);
    HandleStackChanged();
    }

EXPORT_C void CEikAppUi::SetDocument(CEikDocument* aDocument)
/** Sets this app UI's document. 

The document associated with the app UI is initially owned by 
CEikProcess, and there is usually no reason to change it with this function.

@param aDocument The app UI's document. */
	{
	iDocument=aDocument;
	}

EXPORT_C void CEikAppUi::SetEmbeddedDocInfo(MApaEmbeddedDocObserver* aDoorObserver,TBool aReadOnly)
/** Sets the embedded document's observer and read only state.

@param aObserver Observer for the embedded document. 
@param aReadOnly ETrue to set the embedded document as read-only. EFalse if not. */
	{
	iDoorObserver=aDoorObserver;
	iEmbeddedAndReadOnly=aReadOnly;
	}

EXPORT_C CEikDocument* CEikAppUi::Document() const
/** Gets a pointer to the app UI's associated document. 

@return Pointer to the app UI's associated document. */
	{
	return iDocument;
	}

EXPORT_C void CEikAppUi::SetDocChanged()
/** Marks the app UI's associated document as having changed. */
	{
	iDocument->SetChanged(ETrue);
	}

EXPORT_C void CEikAppUi::SaveAnyChangesL()
/** Saves any changes made to the app UI's associated document, 
if the document is marked as having changed. */
	{
	if (iDocument->HasChanged())
		iDocument->SaveL();
	}

EXPORT_C CEikApplication* CEikAppUi::Application() const
/** Gets a pointer to the application associated with this app UI.

@return A pointer to the application associated with this app UI. */
	{
	CEikApplication* ret = NULL;
	if (iDocument)
		ret = ((CEikApplication*)(iDocument->Application()));
	return ret;
	}

EXPORT_C void CEikAppUi::Exit()
/** Closes the app UI. */
	{
	if (iContainerAppUi)
		{
		CEikAppUi* appUi=iContainerAppUi;
		delete this;
		TRAP_IGNORE(appUi->HandleResourceChangeL(KEikMessageEmbedLevelChange));
		appUi->HandleStackedControlsResourceChange(KEikMessageEmbedLevelChange);
		}
	else
		{
		// default reason for exiting is EEikCmdExit. If server exists,
		// clients must be told. Other exit reasons should be notified
		// before they call Exit().
		CEikAppServer* server = iEikonEnv->AppServer();
		if (server)
			server->NotifyServerExit(EEikCmdExit);
		
		CBaActiveScheduler::Exit();
		}
	}

EXPORT_C void CEikAppUi::SaveL()
/** Saves the app UI's associated document, or sets the document as changed, if 
the app UI is embedded. */
	{
	if (iContainerAppUi)
		iContainerAppUi->iDocument->SetChanged(ETrue);
	else
		iDocument->SaveL();
	}

EXPORT_C void CEikAppUi::HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt /*aModifiers*/,const CEikHotKeyTable* aHotKeyTable)
/** Handles sidebar menu commands. 

This is called by the Uikon framework to handle invocation of a 
sidebar menu. See also MEikMenuObserver::HandleSideBarMenuL().

Note that not all UIs support a sidebar.

@param aResourceId ID of the menu resource. 
@param aPos Position of the menu's reference point. For sidebar menus, this 
is the top-right corner. 
@param aModifiers Bitwise OR of the modifiers held when the menu was invoked 
by the user. 
@param aTable Hotkey table for the menu. */
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->HandleSideBarMenuL(aResourceId,aPos,aHotKeyTable, this);
	}

EXPORT_C TBool CEikAppUi::ProcessCommandParametersL(CApaCommandLine& aCommandLine)
/** Processes shell commands. 

This is the ProcessCommandParametersL() method that the Uikon application framework 
will call at application startup. The implementation will extract the command, 
document file name, and tail parameteres from the command line and call the 
3-parameter version of this method. 

The default implementation will simply returns whether or not the file aDocumentName exists. 

@param aCommandLine The command line used to initialise the new application.
@return Whether the final value of aDocumentName represents an existing file. 
@see CEikAppUi::ProcessCommandParametersL(TApaCommand aCommand ,TFileName& aDocumentName, const TDesC8& aTail) */
	{
	const TPtrC documentName = aCommandLine.DocumentName();
	
	// Make a copy of the document file name from the command line
	// using the TUnlimitedFileName to allow names longer than the usual TFileName
	TUnlimitedFileName* const modifiedDocumentName = TUnlimitedFileName::NewLC(documentName);
	// ...and allow the application code to modify it
	const TBool documentFileExists = ProcessCommandParametersL(aCommandLine.Command(), modifiedDocumentName->AsFileName(), aCommandLine.TailEnd());
	// ...then set it back on the command line
	aCommandLine.SetDocumentNameL(*modifiedDocumentName);
	
	CleanupStack::PopAndDestroy(modifiedDocumentName);
	return documentFileExists;
	}

EXPORT_C TBool CEikAppUi::ProcessCommandParametersL(TApaCommand /*aCommand*/ ,TFileName& aDocumentName, const TDesC8& /*aTail*/)
/** Processes shell commands. 

The Uikon application framework calls this overload when an application is 
launched by the user opening a file from the shell or when a Create new file 
command is issued.

This overload simply returns whether or not the file aDocumentName exists. 

Many document based applications will override this function to invoke the 2-parameter 
utility version of this methid. 

@param aCommand The shell command sent to the application. Not used in this implementation.
@param aDocumentName At call time, the name of the document as specified on 
the command line. On return, the name for the file which will be created by 
the calling framework. 
@param aTail Command line tail.  Not used in this implementation.
@return Whether the final value of aDocumentName represents an existing file. 
@see CEikAppUi::ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName) */
	{
	Application()->GetDefaultDocumentFileName(aDocumentName);
	return ConeUtils::FileExists(aDocumentName);
	}

EXPORT_C TBool CEikAppUi::ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName)
/** This is a convinience utility method that an application can call from an overriden version
of the virtual ProcessCommandParametersL() taking three arguments. This method will not be called 
unless explicitly used by the application in this way.

This method is useful for applications that are used to view or edit document files, such as
text documents or spreadsheets. 

This method will make an application automatically open the document file that was last open
in the application, unless a document file is explicitly defined as part of the command line, and
the Open or Create commands are specified.

This method will call CEikAppUi::ValidFileType() to find out if the specified document file can 
be opened by this application.

In detail:
If aCommand is EApaCommandCreate, the function simply returns EFalse as the file does not yet exist.

If aCommand is EApaCommandOpen, the function tests whether the specified document is valid and 
exists. If not, the function attempts to generate a valid default filename and returns that in 
aDocumentName provided the file name portion of the specified full path name has valid format.

If aCommand is any other value, the function tests whether the most recently open document that 
is valid for the application exists, and returns that in aDocumentName.

The file must be a valid document file, as indicated by the UID value(s),otherwise the 
function generates a new filename. An application may handle the request by overriding 
CEikAppUi::ValidFileType() if required.

@param aCommand The shell command sent to the application. 
@param aDocumentName The name of the document as specified on the command line. 
On return, this contains the name of the file which will be created by the calling framework. 
@return Whether the returned value of aDocumentName represents an existing, valid file.
@see CEikAppUi::ValidFileType()
*/
	{ 
	if (aCommand==EApaCommandCreate)
		return EFalse; // assume aDocumentName is valid
		
	// Any command but EApaCommandOpen. 
	// These commands are used to open the application without any file spcified,
	// so try to find the file open last time the application ran.
	if (aCommand!=EApaCommandOpen)	
		{
		TFileName fileName=iEikonEnv->Process()->LastUsedFileL(CEikProcess::ELastOpenFile);
		if (ValidFileExistsL(fileName))
			{
			aDocumentName = fileName;
			return ETrue;
			}
		}
		
	// aCommand == EApaCommandOpen
	if (!ValidFileExistsL(aDocumentName))
		CApaApplication::GenerateFileName(iEikonEnv->FsSession(),aDocumentName);
	return ConeUtils::FileExists(aDocumentName);
	}
	
/**
A valid file has fileType which matches the applications Uid.
@internalComponent
@return EFalse if file or path not found.  Standard error code otherwise.
*/
TBool CEikAppUi::ValidFileExistsL(const TDesC& aFileName)

	{
	// If the file doesn't exist, simply return EFalse
	if (!ConeUtils::FileExists(aFileName))
		return EFalse;
	
	// If it does exist, check whether it's valid
	TEntry entry;
	const TInt error = iEikonEnv->FsSession().Entry(aFileName, entry);
	if(error==KErrNotFound || error==KErrPathNotFound)
		return EFalse;

	User::LeaveIfError(error);
	
	const TUid fileType = entry[2];
	const TUid appType = Application()->AppDllUid();
	return (fileType==appType || ValidFileType(fileType));
	}


/** This method is used in combination with CEikAppUi::ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName).

Override this method to return ETure if the application can handle documents associated 
with the UID aFileUid. If not, return EFalse (default).

@publishedAll 
@released 
@see CEikAppUi::ProcessCommandParametersL(TApaCommand aCommand, TFileName& aDocumentName)
*/
EXPORT_C TBool CEikAppUi::ValidFileType(TUid /*aFileUid*/) const
	{
	return EFalse;
	}


/**
@see MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)
*/
EXPORT_C MCoeMessageObserver::TMessageResponse CEikAppUi::HandleMessageL(TUint32, TUid aMessageUid, const TDesC8& aMessageParameters)
	{
	switch (aMessageUid.iUid)
		{
	case KUidApaMessageSwitchOpenFileValue:
	case KUidApaMessageSwitchCreateFileValue:
		CEikShutter::DeferredExecuteL(*iEikonEnv, aMessageUid, aMessageParameters);
		return EMessageHandled;
	default:
		return EMessageNotHandled;
		}
	}

EXPORT_C TTypeUid::Ptr CEikAppUi::MopSupplyObject(TTypeUid /*aId*/)
/** Retrieves an object of the same type as that encapsulated in aId.

This function is used to allow to ask owners for access to 
other objects that they own.

Other than in the case where NULL is returned, the object returned must be 
of the same object type - that is, the ETypeId member of the object pointed 
to by the pointer returned by this function must be equal to the iUid member 
of aId.

@param aId An encapsulated object type ID.
@return Encapsulates the pointer to the object provided. Note that the encapsulated 
pointer may be NULL. */
	{
	return TTypeUid::Null();
	}

EXPORT_C MObjectProvider* CEikAppUi::MopNext()
/** Retrieves the parent.

@return A pointer to an object provider, or NULL if none is defined. 
@publishedAll 
@released */
	{
	CEikonEnv* env=(CEikonEnv*)iCoeEnv;
	return env->AppUiFactory();
	}

/**
@see CCoeAppUi::HandleSystemEventL( const TWsEvent& aEvent )
*/
EXPORT_C void CEikAppUi::HandleSystemEventL(const TWsEvent& aEvent)
/** @see CCoeAppUi::HandleSystemEventL */
	{
	switch (*(TApaSystemEvent*)(aEvent.EventData()))
		{
	case EApaSystemEventShutdown:
		if(static_cast<CEikonEnv*>(iCoeEnv)->IsSystem())
			break;
		// fall-through
	case EApaSystemEventSecureShutdown:
		CEikShutter::DeferredExecuteL(*iEikonEnv);
		break;
	case EApaSystemEventBroughtToForeground:
		{
		RArray<RWsSession::TWindowGroupChainInfo> wgIds;
		User::LeaveIfError(iEikonEnv->WsSession().WindowGroupList(&wgIds));
		CleanupClosePushL(wgIds);
		TInt rootWgId=iEikonEnv->RootWin().Identifier();
		const TInt wgCount=wgIds.Count();
		TBool hasChild=EFalse;
		for (TInt i=0;i<wgCount;i++)
			{
			// If the current app has a child window group in front of it
			if (wgIds[i].iParentId==rootWgId)
				{
				hasChild=ETrue;
				break;
				}
			}
		CleanupStack::PopAndDestroy(&wgIds);
		if (!hasChild)
			{
			ActivateTopViewL();
			}
		}
		break;
	default:
		break;
		}
	}

EXPORT_C void CEikAppUi::HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination)
/** Handles window server events.
@see CCoeAppUi::HandleWsEventL

@param aEvent The window server event that occurred. 
@param aDestination The control associated with the event. */
	{
	switch (aEvent.Type())
		{
	case EEventModifiersChanged:
		if ((aEvent.ModifiersChanged()->iChangedModifiers)&EModifierCapsLock)
			{
			HandleResourceChangeL(KEikMessageCapsLock);
			HandleStackedControlsResourceChange(KEikMessageCapsLock);
			}
		break;
	case EEventPointer:
		if (LafAppUi::CancelBubbleHelpOnEvent(*aEvent.Pointer()))
			{
			EikBubbleHelp::Cancel();
			}
		break;
	default:
		break;
		}
	CCoeAppUi::HandleWsEventL(aEvent, aDestination);
	}

EXPORT_C void CEikAppUi::ProcessMessageL(TUid aUid,const TDesC8& aParams)
/** Processes Application Architecture messages. 

This is overridden by subclasses to handle messages sent from the Application 
Architecture framework. This implementation only recognises the message UIDs 
KUidApaMessageSwitchOpenFileValue and KUidApaMessageSwitchCreateFileValue. 
It performs no action if the message contains other values.

@param aUid The message's unique identifier. 
@param aParams Message parameters. 
@see CCoeAppUi::HandleMessageReadyL()
@see CApaTask::SendMessage() */
	{
	switch (aUid.iUid)
		{
	case KUidApaMessageSwitchOpenFileValue:
		OpenFileL(TPtrC(((TText*)aParams.Ptr()),aParams.Length()/sizeof(TText)));
		break;
	case KUidApaMessageSwitchCreateFileValue:
		CreateFileL(TPtrC(((TText*)aParams.Ptr()),aParams.Length()/sizeof(TText)));
		break;
	default:
		break;
		}
	}

EXPORT_C void CEikAppUi::OpenFileL(const TDesC& /*aFileName*/)
/** Opens the specified file. 

The default implementation is empty. 

@param aFileName The name of the file to open. 
@see CEikAppUi::ProcessMessageL() */
	{
	}

EXPORT_C void CEikAppUi::CreateFileL(const TDesC& /*aFileName*/)
/** Creates and opens a file with the given name. 

The default implementation is empty.

@param aFileName The name of the file to create. 
@see CEikAppUi::ProcessMessageL() */
	{
	}

EXPORT_C TErrorHandlerResponse CEikAppUi::HandleError(TInt /*aError*/,const SExtendedError& /*aExtErr*/,TDes& /*aErrorText*/,TDes& /*aContextText*/)
/** Handles errors. 

The default implementation of this function returns EErrorNotHandled.

@param aError The error code. 
@param aExtErr For extended error messages. 
@param aErrorText Error text.
@param aContextText Text describing the context of the error.
@return How the error was handled. */
	{
	return(EErrorNotHandled);
	}

EXPORT_C void CEikAppUi::HandleResourceChangeL(TInt aType)
/** Handles a change to the application's resources which are shared 
across the environment, for instance colours or fonts.

@param aType The type of resources that have changed. */
	{
	MEikAppUiFactory* appUiFactory = iEikonEnv->AppUiFactory(*this);
	ASSERT(appUiFactory);
	appUiFactory->HandleResourceChangeL(aType);
	}

/** Handles an application-specific event. 

This implementation handles a change to the environment's colour scheme 
and informs everything on the control stack of the change.

@param aType The type of the event that occurred. This should be a unique 
identifier constant. 
@param aEvent The window server event that occurred. 
@see CCoeAppUi::HandleApplicationSpecificEventL 
@see KUidValueEikColorSchemeChangeEvent */
EXPORT_C void CEikAppUi::HandleApplicationSpecificEventL(TInt aType, const TWsEvent& /*aEvent*/)
	{
	switch(aType)
		{
		case KUidValueEikColorSchemeChangeEvent:
			{
			TRAPD(err,iEikonEnv->UpdateColorListL());
			if(err==KErrNone)
				{
				HandleResourceChangeL(KEikMessageColorSchemeChange);
				HandleStackedControlsResourceChange(KEikMessageColorSchemeChange);
				if(iEikonEnv->IsEiksrvThread())
					{
					UpdateViewServerBackgroundColor(iEikonEnv->ColorList().Color(EColorWindowBackground));
					}
				}
			}
		case KEikNotifyPreCreateEmbeddedL:
			break;	// do nothing
		case KEikNotifyPostCreateEmbeddedL:
			break;	// do nothing
		case KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes:
			break;	// do nothing
		default:
			break;	// do nothing
		}
	}

EXPORT_C void CEikAppUi::ReportResourceChangedToAppL(TInt aType)
/** Reports a resource change to the application.

@param aType The type of resource that has changed. */
	{
	HandleResourceChangeL(aType);
	HandleStackedControlsResourceChange(aType);
	}

EXPORT_C void CEikAppUi::HandleForegroundEventL(TBool aForeground)
/** Handles changes to the application when it switches to or from 
the foreground. 

For instance it handles changes to the cursor visibility and to the 
fade state.

This function is called from HandleWsEventL() when an event 
occurs of type EEventFocusLost or EEventFocusGained.

Any application overriding this should first call this base implementation.

@param aForeground ETrue to switch to the foreground. EFalse to switch from 
the foreground.. */
	{
	if (LafAppUi::FadeWhenInBackground())
		SetFadedL(!aForeground);
	
	if (aForeground)
		iEikonEnv->VirtualCursor().HandleAppToForeground(*iEikonEnv);
	}

EXPORT_C void CEikAppUi::PrepareToExit()
/** Performs pre-exit processing to ensure the application will exit cleanly. */
	{
	TVwsViewId viewId;
	if (GetActiveViewId(viewId) != KErrNotFound)
		{
		TRAP_IGNORE(DeactivateActiveViewIfOwnerMatchL());
		}
	}

EXPORT_C void CEikAppUi::HandleScreenDeviceChangedL()
	{
	// All status pane stuff must be handled in System Gui
	}

EXPORT_C void CEikAppUi::Reserved_3()
	{}
	
EXPORT_C void CEikAppUi::Reserved_4()
	{}
	
/** Determines the current language the application is using to display its
user interface.

@return The application language.
*/
EXPORT_C TLanguage CEikAppUi::ApplicationLanguageL() const
	{
	return iEikonEnv->ApplicationLanguage();
	}


/**
Calls ReportResourceChangedToAppL( aEventId ) on recursively on each ContainerAppUi.  
For use with embedded applications (where iContanerAppUI != NULL)
@param aTopApp AppUi of an embedded application.
@param aEventId  The type of resource that has changed. 
@see CEikAppUi::ReportResourceChangedToAppL(TInt aType)
*/
EXPORT_C void CEikAppUi::ReportResourceChangedToAppStackL(CEikAppUi* aTopApp, TInt aEventId)
	{
 	for (; aTopApp; aTopApp = aTopApp->iContainerAppUi)
 		 aTopApp->ReportResourceChangedToAppL(aEventId);
 	}



