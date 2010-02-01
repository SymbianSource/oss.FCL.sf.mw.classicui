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

/**
 Gets the most recent standard event that was received by the application.
 
 Note: standard events are all events except redraw events and priority key events.
 
 @return The last event. 
*/
inline const TWsEvent& CCoeEnv::LastEvent() const
	{ return(iLastEvent); }

/** Gets the application UI owned by this application.

@return Pointer to the app UI owned by the application. */
inline CCoeAppUi* CCoeEnv::AppUi() const
	{ return(iAppUi); }

/** Gets the file server session owned by this CCoeEnv. 

This session is normally only used for accessing the application's resource 
file.

@return The file server session owned by this CCoeEnv. */
inline RFs& CCoeEnv::FsSession() const
	{ return((RFs&)iFsSession); }

/** Gets the window server session owned by the application. 

This provides access to window server functions not directly accessible via 
the UI control framework.

@return The window server session opened by the application. */
inline RWsSession& CCoeEnv::WsSession() const
	{ return((RWsSession&)iWsSession); }

/** Gets the application's window group.

Note: a window group is an invisible window which acts as the parent window for 
all other windows in an application. Typically, each application has one window 
group. In the window server, window groups are also the unit of keyboard focus.

@return The application's window group. */inline RWindowGroup& CCoeEnv::RootWin() const
	{ return((RWindowGroup&)iRootWin); }

/** Gets the system graphics context. 

This is the graphics context typically used for drawing controls, but an 
alternative graphics context can be created if required using CreateGcL().

@return The system graphics context. */
inline CWindowGc& CCoeEnv::SystemGc() const
	{ return((CWindowGc&)*iSystemGc); }

/** Gets the normal environment font. 

This is the font created during construction of the control environment.

@return Pointer to the normal environment font.
@see InitSystemFontsL() */
inline const CFont* CCoeEnv::NormalFont() const
	{ return(iNormalFont); }

/** Gets the default screen device owned by this CCoeEnv. 

This is typically used as the standard screen device for the CCoeEnv's application.

@return The default screen device owned by this CCoeEnv. */
inline CWsScreenDevice* CCoeEnv::ScreenDevice() const
	{ return(iScreen); }

/** Gets the current error message text.

@return The current error message text. */
inline TDes& CCoeEnv::ErrorText() 
	{ return *iErrorText; }

/** Gets the current error context text.

@return The current error context text. */
inline TDes& CCoeEnv::ErrorContextText() 
	{ return *iErrorContextText; }

#if defined(_UNICODE)
/** Reads a resource into a descriptor. 

The descriptor must be long enough to contain the entire resource. No memory 
is allocated by this function. If the read fails, the function sets an error 
condition and performs any cleanup required. The error condition causes the 
GUI to launch an alert window.

Deprecated - Use CCoeEnv::ReadResourceL() instead.

@deprecated 
@param aDes On return, contains the resource data.
@param aResourceId The numeric ID of the resource to be read.
@see RResourceFile::ReadL()
@see KErrCoeFailedToReadFromProgDisk */
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes16(aDes,aResourceId); }

/** Reads a resource into a descriptor.

The descriptor must be long enough to contain the entire resource. 
No memory is allocated by this function.

@param aDes On return, contains the resource data.
@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource. */
inline void CCoeEnv::ReadResourceL(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes16L(aDes,aResourceId); }

/** Reads a resource into a heap descriptor, allocating memory for it. 

Note: the calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadL() */
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes16L(aResourceId); }

/** Reads a specified resource into a heap descriptor, allocating memory for it, 
and pushing the descriptor onto the cleanup stack. 

The calling program should pop and destroy the heap descriptor when it is 
no longer needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadLC() */
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes16LC(aResourceId); }

/** Reads a resource into a Unicode descriptor array.

@param aResourceId The numeric ID of the resource to be read.
@return A pointer to the descriptor array containing the resource data.
@see TResourceReader::ReadDesCArrayL() */
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC16ArrayResourceL(aResourceId); }
#else  // not UNICODE

/** Deprecated - use CCoeEnv::ReadResourceL() instead.

@deprecated */
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes8(aDes,aResourceId); }

inline void CCoeEnv::ReadResourceL(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes8L(aDes,aResourceId); }
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes8L(aResourceId); }
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes8LC(aResourceId); }
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC8ArrayResourceL(aResourceId); }
#endif // UNICODE

//
// Tests if the Active Scheduler is started in the CCoeEnv::ExecuteD
//
// @return   "TBool"
//            <code>ETrue</code> if Active Scheduler is started in
//								 CCoeEnv::ExecuteD()	
//            <code>EFalse</code> if Active Scheduler is not started in
//								  CCoeEnv::ExecuteD()	
//            
inline TBool CCoeEnv::IsSchedulerRunning() const
	{return iEnvFlags&ESchedulerIsRunning;}
