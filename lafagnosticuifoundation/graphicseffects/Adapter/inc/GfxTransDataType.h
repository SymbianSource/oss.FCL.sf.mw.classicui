// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// GFXTRANSDATATYPES.H
// 
//

#ifndef _GFXTRANSDATATYPES_H_
#define _GFXTRANSDATATYPES_H_

#include <coecntrl.h>

//Various types for data passing between client and adaptor.
//Pointers passed should not transfer ownership, the client is responsible for all data.


enum TPolicy
	{
	ENotSupported, 	// Not supported by the engine, the client will not call MGfxTransEngine::StartTransition
	ESupported,		// Supported by the engine, the client will call MGfxTransEngine::StartTransition
	EAbort			// Not supported by the engine, but the engine wants to be informed so that it can
					// abort other transitions, the client will not call MGfxTransEngine::StartTransition
	};

/**
TControlPolicy
@publishedPartner
@released
*/
class TControlPolicy 
	{
public:
	TUid iId;		// The Uid of the registered control this policy applies to
	TInt iAction;	// The Action of the transition that this policy applies to
	TPolicy iPolicy;// the policy
	};

/**
CParticipantData
 
Contains the data that the client collects for a participant in a transition
 
The data can be queries from the client using MGfxTransClient::GetTransitionData
All the data is available when the client calls MGfxTransEngine::StartTransition() 
unless iFailed is ETrue. 

The client is responsible for deleting the data.
 
@publishedPartner
@released
*/	
class CParticipantData : public CBase
	{
public:
	~CParticipantData()
		{
		if(iBeginCapture)
			{
			iBeginCapture->Close();
			delete iBeginCapture;
			}
		if(iEndCapture && (iBeginCapture != iEndCapture))
			{
			iEndCapture->Close();
			delete iEndCapture;
			}
		}
	TRect iBeginRect;				// The begin rect for this participant
	TRect iEndRect;					// The end rect for this participant
	RWsGraphicMsgBuf* iBeginCapture;// The begin capture for this participant, 0 if not existing
	RWsGraphicMsgBuf* iEndCapture; 	// The begin capture for this participant, 0 if not existing
	TInt iBeginZ; 					// Begin Z depth for this participant, -1 if unknown
	TInt iEndZ;						// End Z depth for this participant, -1 if unknown
	TUid iLayerType;				// the Uid for this particpant set with GfxTransEffect::SetHints()
	TUint iFlags;					// The flags for this participant set with GfxTransEffect::SetHints()
	const CCoeControl* iKey; 		// The control for this participant, not owning
	};
	
	
/**
CTransitionData
 
Contains the data that the client collects for a transition
 
The data can be queries from the client using MGfxTransClient::GetTransitionData
All the data is available when the client calls MGfxTransEngine::StartTransition() 
unless iFailed is ETrue. 

The client is responsible for deleting the data.

@publishedPartner
@released
*/
class CTransitionData : public CBase
	{
public:
	~CTransitionData()
		{
		iSubControls.Reset();
		iSubControls.Close();
		}
	const CCoeControl* iKey;// the registered control, not owning
	TPoint iBeginWOPos;   	// the begin position of the windowowning parent
	TPoint iEndWOPos;		// the end position of the windowowning parent
	TUid  iUid;				// the uid for the registered control
	TBool iNLayered;		// ETrue if the control is NLayered
	TUint iAction;			// the aAction for this transition
	TBool iFailed;			// ETrue if the client have failed in collecting the data,
							// in this case the data might be incorrect
	TPolicy iPolicy;		// The policy for this transition
	const TDesC8* iExData;	// the data set with GfxTransEffect::SetTransitionData(), NULL if no data, not owning
	TUint iExDataType;		// The type of the data set with GfxTransEffect::SetTransitionData()
	const CParticipantData* iBaseControl; //data for the registered control, not owning	
	RPointerArray<const CParticipantData> iSubControls; //data for the layers in a Nlayered control, not owning
	};
//---


#endif



