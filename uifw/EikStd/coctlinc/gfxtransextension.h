/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class for passing data between controls.
*
*/


#ifndef __GFX_TRANS_EXTENSION_H__
#define __GFX_TRANS_EXTENSION_H__

#include <coemain.h>
#include <gfxtranseffect/gfxtranseffect.h>

const TUid KGfxTransExtensionUid = { 0x10282E4B };

class MAknTransitionUtilsObserver
    {
public:
    virtual TInt AknTransitionCallback(TInt aEvent, TInt aState = 0, 
                                       const TDesC8* aParams = NULL) = 0;
	};

NONSHARABLE_CLASS( CGfxTransExtension ) : public CCoeStatic, 
                                          public MGfxTransEffectObserver
    {
    public:
    enum TEvents
        { 
        // Binary flags
        ENone = 0x0,
        EEventWsBufferRedirection = 0x1,
        EEventControlTransitionFinished = 0x2
		};

    ~CGfxTransExtension();

    static TInt AddObserver( MAknTransitionUtilsObserver* aObserver,
                             TInt aEvent,
                             const TDesC8* aParams = NULL );
    static TInt RemoveObserver( MAknTransitionUtilsObserver* aObserver,
                                TInt aEvent );
    static TInt GetState(TInt aEvent, TInt* aState, TDes8* aParams = NULL);

    // From MGfxTransEffectObserver
    void TransitionFinished( const CCoeControl* aControl, TUint aAction );


    static TInt SetData( const TInt aKey, const TDesC8* aData );
    static const TDesC8* GetData( const TInt aKey );
    static void RemoveData( const TInt aKey );

//    static void SetAllParents( const CCoeControl* aControl );
    
    private:
    CGfxTransExtension();

    /**
     * Returns the CGfxTransExtension singleton.
     *
     * The CGfxTransExtension singleton, or NULL or error.
     */    
    static CGfxTransExtension* Static();


  
    struct TDataEntry
        {
        TDataEntry( const TInt iKey, const TDesC8* aData );
        
        static TBool SameKey( const TDataEntry& aEntry1, 
                              const TDataEntry& aEntry2 );

        const TInt iKey;
        const TDesC8* iData;
        };
        
    struct TTransitionObserver
        {
        TTransitionObserver( const TInt iKey, TInt iEventType,
                             MAknTransitionUtilsObserver* aObserver );
 
        static TBool SameKey( const TTransitionObserver& aObserver1,
                              const TTransitionObserver& aObserver2 );

        static TBool Equal( const TTransitionObserver& aObserver1,
                            const TTransitionObserver& aObserver2 );

        const TEvents iEventType;        
        const TInt iKey;
        MAknTransitionUtilsObserver* iObserver;
        };


    // FIXME: Change these RArrays to RPointerArrays, and we can
    // move TDataEntry and TTransitionObserver to the .cpp file.
    
    // Owns the user data, ownership is transferred with SetData().
    RArray<TDataEntry> iUserData;


    // FIXME: This class shouldn't own the observers!
    RArray<TTransitionObserver> iObservers;
    TInt iNumControlTransitionObservers;
    };

#endif // __GFX_TRANS_EXTENSION_H__
