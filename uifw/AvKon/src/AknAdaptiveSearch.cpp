/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include "AknAdaptiveSearch.h"
#include <aknsfld.h>
#include <centralrepository.h>      // CenRep for AS
#include <AvkonInternalCRKeys.h>    // CenRep for AS
#include <akntrace.h>               //for trace


// CONSTANTS
const TInt KAknStringBufferSize = 256;
const TInt KLitHyphen('-');

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearch* CAknAdaptiveSearch::NewL( const TInt aTextLimit, TInt aFieldStyle )
    {
    CAknAdaptiveSearch* self = CAknAdaptiveSearch::NewLC( aTextLimit, aFieldStyle);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearch* CAknAdaptiveSearch::NewLC( const TInt aTextLimit, TInt aFieldStyle )
    {
    CAknAdaptiveSearch* self = new ( ELeave ) CAknAdaptiveSearch ();
    CleanupStack::PushL( self );
    self->ConstructL( aTextLimit, aFieldStyle );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::CAknAdaptiveSearch
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearch::CAknAdaptiveSearch()     
    : iBlockFlag( EFalse )      
    {    
    }     

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::~CAknAdaptiveSearch
// Destructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearch::~CAknAdaptiveSearch()
    {  
    _AKNTRACE_FUNC_ENTER;
    if ( iAdaptiveSearchGrid )
	    {
	    delete iAdaptiveSearchGrid;	
	    }
	if( iGridChars )
		{
		delete iGridChars;
		iGridChars = NULL;
		}
	iAdaptiveSearchTextObserver = NULL;	
	// Stop listening CenRep.
    if ( iCenRepNotifyHandlerChinese )
    	{
    	iCenRepNotifyHandlerChinese->StopListening();
    	}
    delete iCenRepNotifyHandlerChinese;
    if ( iCenRepNotifyHandlerPRC )
    	{
    	iCenRepNotifyHandlerPRC->StopListening();
    	}
    delete iCenRepNotifyHandlerPRC;
    if ( iCenRepNotifyHandlerTW )
    	{
    	iCenRepNotifyHandlerTW->StopListening();
    	}
    delete iCenRepNotifyHandlerTW;
    if ( iCenRepNotifyHandlerHongkong )
    	{
    	iCenRepNotifyHandlerHongkong->StopListening();
    	}
    delete iCenRepNotifyHandlerHongkong;
    delete iCenRep;    
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::ConstructL( const TInt aTextLimit, TInt aSearchField )
    {
    _AKNTRACE_FUNC_ENTER;
    iAdaptiveSearchGrid = CAknAdaptiveSearchGrid::NewL( aTextLimit, aSearchField );  
    iAdaptiveSearchGrid->SetAdaptiveSearchGridObserver( this );
    iGridChars = NULL;
    iTextLimit = aTextLimit;
    iAdaptiveSearchTextObserver = NULL;  
    
    // Start listening a CenRep key indicating input language 
    TRAPD( err, iCenRep = CRepository::NewL( KCRUidAvkon ) );
    if ( err == KErrNone )
        {
        iCenRepNotifyHandlerChinese = CCenRepNotifyHandler::NewL( *this, *iCenRep,
                                      CCenRepNotifyHandler::EIntKey,
                                      KAknAdaptiveSearchLastChinese );
        iCenRepNotifyHandlerChinese->StartListeningL(); 
        
        iCenRepNotifyHandlerPRC = CCenRepNotifyHandler::NewL( *this, *iCenRep,
                                  CCenRepNotifyHandler::EIntKey,
                                  KAknAdaptiveSearchChinesePRC );
        iCenRepNotifyHandlerPRC->StartListeningL(); 
        
        iCenRepNotifyHandlerTW = CCenRepNotifyHandler::NewL( *this, *iCenRep,
                                 CCenRepNotifyHandler::EIntKey,
                                 KAknAdaptiveSearchChineseTW);
        iCenRepNotifyHandlerTW->StartListeningL();
        
        iCenRepNotifyHandlerHongkong = CCenRepNotifyHandler::NewL( *this, *iCenRep,
                                       CCenRepNotifyHandler::EIntKey,
                                       KAknAdaptiveSearchChineseHongkong );
        iCenRepNotifyHandlerHongkong->StartListeningL(); 
        }  
    _AKNTRACE_FUNC_EXIT;
    }
           
// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::HandleControlEventL
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::HandleControlEventL( CCoeControl */*aControl*/, 
                                              TCoeEvent /*aEventType*/ )
	{	
	}
	
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the last character entered is a Indic halant character.
// @param aCh - character to be checked  
// @return ETrue if this is a halant character EFalse otherwise.                        
// -----------------------------------------------------------------------------
inline TBool IsIndicHalantChar( const TChar aCh )
    {
    //Devanagari halant character check:
    return ( aCh == 0x094D );
    }	

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::SetButtonCharsL
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::SetButtonCharsL( const TDesC& aGridChars )
    {  
    _AKNTRACE_FUNC_ENTER;
    _AKNDEBUG(
            _LIT( KClassName, "CAknAdaptiveSearch" );
            _LIT( KFunctionName, "SetButtonCharsL" );
            _LIT( KFormat, "[%S][%S] The text is: %S");
            _AKNTRACE( KFormat, 
            &KClassName, &KFunctionName, &aGridChars );
            );
	if( iGridChars )
		{
		delete iGridChars;
		iGridChars = NULL;
		}   

    TBuf<KAknStringBufferSize> criteria;
    iSearchField->GetSearchText( criteria );
    TInt length = criteria.Length();   
	if( !iTextLimit || length < iTextLimit )
	    {
	    iGridChars = HBufC::NewL( aGridChars.Length() );
	    iGridChars->Des().Copy( aGridChars );	
	    iAdaptiveSearchGrid->SetButtonGridChars( aGridChars );	
					
        // To do lower case for search pane
        iGridChars->Des().LowerCase();          
        iBlockFlag = EFalse;   	
	    }
	else
	    {	    
	    TPtrC nullText( KNullDesC );
	    iAdaptiveSearchGrid->SetButtonGridChars( nullText );
	    iBlockFlag = EFalse;   		
	    }
	_AKNTRACE_FUNC_EXIT;
   	}
	    	    	
// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the last character entered is a Indic independent character.
// @param aCh      - character to be checked  
// @return ETrue if this is an independent character EFalse otherwise                        
// -----------------------------------------------------------------------------
inline TBool IsIndicIndependentChar( const TChar aCh )
	{
	if (( aCh >= 0x0905 && aCh <= 0x0939 ) || ( aCh >= 0x0958 && aCh <= 0x0961 ))
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
	}



// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::ProcessCommandL
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::ProcessCommandL( TInt aCommand )
	{
	_AKNTRACE_FUNC_ENTER;
	 _AKNTRACE( "[%s][%s] Command ID: %d", "CAknAdaptiveSearch",
	         __FUNCTION__, aCommand);
	if( aCommand == CAknAdaptiveSearchGrid::ECloseGridPressed )
		{
		//hide grid
        HideAdaptiveSearchGridL();
		iSearchField->MakeVisible( ETrue );	
		iSearchField->SetFocus( ETrue );	
	
		}
    else if( aCommand == CAknAdaptiveSearchGrid::EDeleteLastCharPressed )
		{
		//do search text update
		if( iSearchField )
			{
			TBuf<KAknStringBufferSize> criteria;
            if ( iSearchField->Editor().SelectionLength() > 0 )
                {
                iAdaptiveSearchGrid->SetSearchTextToFindPane( criteria );
                iSearchField->SetSearchTextL( criteria );
                iSearchField->HandleControlEventL( iSearchField, EEventStateChanged );
                }
            else
                {
                iSearchField->GetSearchText( criteria );
                }
			TInt length = criteria.Length();
			if( length > 0 )
				{
				// If Devanagari
				if ( (criteria[length-1] == KLitHyphen) && length>1 && IsIndicIndependentChar(criteria[length-2]) )
					{						
					// First check if this is one of the four special ligatures, in which
					// case, there will be a halant prior to 'criteria[length-2]'			
					if ( (length > 3) && IsIndicHalantChar(criteria[length-3]) )
					    {
					    // hyphen should be removed along with the preceding 3 characters 
					    criteria = criteria.Mid( 0, (length-4) ); 
					    }
					else
					    {
					    // normal Indic character - remove the preceding character.
					    criteria = criteria.Mid( 0, (length-2) );
					    }
					}
				else
					{
					criteria = criteria.Mid( 0, (length-1) );		
					}					
				// Update the AS search field first to be ready for redraw
				iAdaptiveSearchGrid->SetSearchTextToFindPane( criteria );				
                iSearchField->SetSearchTextL( criteria );   
                iSearchField->HandleControlEventL( iSearchField, EEventStateChanged );      
				iSearchField->SetFocus( EFalse );		        			
				iSearchField->MakeVisible ( EFalse );
				iAdaptiveSearchGrid->SetSearchTextToFindPane( criteria );	
				iSearchField->DrawNow();
				if( iAdaptiveSearchTextObserver )
					{
					iSearchField->SetLanguageChangedFlag( EFalse );
					iAdaptiveSearchTextObserver->AdaptiveSearchTextChanged( iSearchField );		
					}						
				}
			}
		}
	else if ( iBlockFlag == EFalse )
	    {
	    iBlockFlag = ETrue; 	       
        TBuf<KAknStringBufferSize> criteria;
        if ( iSearchField->Editor().SelectionLength() == 0 )
            {
            iSearchField->GetSearchText( criteria );            
            }
        // Check if Devanagari 
        TInt indicHalantPos( KErrNotFound );
        TInt gridCharsLength = iGridChars->Length();
        // Search for the first appearing halant character. 
        for ( TInt index = 1; index < gridCharsLength ; ++index )
            {
            if ( IsIndicHalantChar((*iGridChars)[index]) )
                {
                indicHalantPos = index;
                break;
                }
            }
        if ( indicHalantPos < 0 || aCommand < (indicHalantPos-1) )
            {
            // Western search
            criteria.Append( iGridChars->Mid(aCommand,1) );
            }
        else
            {
            // Devanagari search
            for ( TInt index = (indicHalantPos-1); index < gridCharsLength ; ++index )
                {
                if ( aCommand == index )
                    {
                    // check if this is an Indic special ligature
                    if ( index+1 < gridCharsLength && IsIndicHalantChar((*iGridChars)[index+1]) )
                        {
                        // append the next 2 characters as well to the search criteria
                        criteria.Append( iGridChars->Mid(index,3) );
                        }
                    else
                        {
                        // send just the one character
                        criteria.Append( iGridChars->Mid(index,1) );
                        }
                    break;
                    }
                } // for
             }            
        TInt length = criteria.Length();  
        // If Devanagri Append the placeholder for dependent vowels 
    	if ( IsIndicIndependentChar( criteria[length-1] ) )
        	criteria.Append( KLitHyphen );
        	
      	// Update the AS search field first to be ready for redraw
        iAdaptiveSearchGrid->SetSearchTextToFindPane( criteria );       
        iSearchField->SetSearchTextL( criteria );   
        iSearchField->HandleControlEventL( iSearchField, EEventStateChanged );      
    	iSearchField->SetFocus( EFalse );    	
    	iSearchField->MakeVisible ( EFalse );
        iSearchField->DrawNow();
        if( iAdaptiveSearchTextObserver )
        	{
        	iSearchField->SetLanguageChangedFlag( EFalse );
        	iAdaptiveSearchTextObserver->AdaptiveSearchTextChanged( iSearchField );	
	        }
	    }
	_AKNTRACE_FUNC_EXIT;
	}
	
// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::SetSearchField
// -----------------------------------------------------------------------------
//	
void CAknAdaptiveSearch::SetSearchField( CAknSearchField* aSearchField )
	{
	iSearchField = aSearchField; 
    iAdaptiveSearchGrid->SetMopParent( aSearchField );
	}

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::ShowAdaptiveSearchGridL
// Shows adaptive search grid.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::ShowAdaptiveSearchGridL()
	{
	if( !iAdaptiveSearchGrid->IsShown() )
        {
        iAdaptiveSearchGrid->ShowL();
        }
	}

// ----------------------------------------------------------------------------- 
// CAknAdaptiveSearch::HandleNotifyInt
// Check adaptive search availability from cenrep
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::HandleNotifyInt( TUint32 aId, TInt /*aNewValue*/ )
    {
    _AKNTRACE( "[%s][%s] The input method for adaptive search: %d", 
                               "CAknAdaptiveSearch", __FUNCTION__, aId );
    if ( aId == KAknAdaptiveSearchLastChinese )
        {
        TRAP_IGNORE( iSearchField->HandleControlEventL(iSearchField, EEventStateChanged) );          	
        }
    if ( aId == KAknAdaptiveSearchChinesePRC )
        {
        TRAP_IGNORE( iSearchField->HandleControlEventL(iSearchField, EEventStateChanged) );  
        }   
    if ( aId == KAknAdaptiveSearchChineseTW )
        {
        TRAP_IGNORE( iSearchField->HandleControlEventL(iSearchField, EEventStateChanged) );  	
        }
    if ( aId == KAknAdaptiveSearchChineseHongkong )
       {
       TRAP_IGNORE( iSearchField->HandleControlEventL(iSearchField, EEventStateChanged) );  	
       }       
    if( iAdaptiveSearchTextObserver )
       {
       iSearchField->SetLanguageChangedFlag( ETrue ); 
       iAdaptiveSearchTextObserver->AdaptiveSearchTextChanged( iSearchField );
       }    
    }
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::HideAdaptiveSearchGrid
// Hides adaptive search grid.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::HideAdaptiveSearchGridL()
	{
	_AKNTRACE_FUNC_ENTER;
	if( iAdaptiveSearchGrid->IsShown() )
	    {
        iAdaptiveSearchGrid->HideL();      
	    }	
	 _AKNTRACE_FUNC_EXIT;
	}
	
// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::InvertAdaptiveSearchGridVisibility
// Hides adaptive search grid if it shown, and shows if it is hide.
// -----------------------------------------------------------------------------
//	
void CAknAdaptiveSearch::InvertAdaptiveSearchGridVisibilityL( TBool aSelectAll )
	{
	 _AKNTRACE_FUNC_ENTER;
	// update the search text here if showing
	TInt textLength = 0;
	if( !iAdaptiveSearchGrid->IsShown() && &(iSearchField->Editor()) )
	    {
	    textLength = iSearchField->Editor().TextLength();
	    HBufC* searchText = NULL;
	    TPtrC finalText( KNullDesC );
	    if( textLength > 0 )
	        {
	        TRAP_IGNORE( searchText = iSearchField->Editor().GetTextInHBufL() );
    	    if( searchText )
    	        {
    	        finalText.Set( *searchText ); // set the value
    	           _AKNDEBUG(
    	                    _LIT( KClassName, "CAknAdaptiveSearch" );
    	                    _LIT( KFunctionName, "InvertAdaptiveSearchGridVisibilityL" );
    	                    _LIT( KFormat, "[%S][%S] Final text is: %S");
    	                    _AKNTRACE( KFormat, 
    	                    &KClassName, &KFunctionName, &finalText );
    	                    );
    	        }
	        }	    
    	iAdaptiveSearchGrid->SetSearchTextToFindPane( finalText );    
    	if( searchText )
    	    {
    	    delete searchText;
    	    searchText = NULL;
    	    }
	    }
	TBool shown( !(iAdaptiveSearchGrid->IsShown()) );
	if ( shown )
	    {
	    iSearchField->SetFocus( EFalse );	 
	    iSearchField->MakeVisible( EFalse );   
	    }
	else
	    {
	    iSearchField->Editor().RemoveFlagFromUserFlags( CEikEdwin::EAvkonDisableVKB );
	    iSearchField->MakeVisible( ETrue );      
	    iSearchField->SetFocus( ETrue );	         
	    }
    iAdaptiveSearchGrid->SetVisibilityL( shown, aSelectAll );
    _AKNTRACE_FUNC_EXIT;
	}

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::AddAdaptiveSearchTextObserverL
// Adds an adaptive search text observer.
// -----------------------------------------------------------------------------
// 
void CAknAdaptiveSearch::AddAdaptiveSearchTextObserverL( MAdaptiveSearchTextObserver* aObserver )
	{
	iAdaptiveSearchTextObserver = aObserver;  	
	}

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::RemoveAdaptiveSearchTextObserver
// Removes an adaptive search text observer. 
// -----------------------------------------------------------------------------
//
TBool CAknAdaptiveSearch::RemoveAdaptiveSearchTextObserver( MAdaptiveSearchTextObserver* aObserver )
	{
	if( iAdaptiveSearchTextObserver == aObserver )
		{
		iAdaptiveSearchTextObserver = NULL;
		return ETrue;
		}
	else
		{
		return EFalse;
		}
	}

// -----------------------------------------------------------------------------
// CAknAdaptiveSearch::UpdateGridSkinL()
// Update adaptive search grid skin, since it can't recieve any messages
// if it is hidden.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearch::UpdateGridSkinL()
	{
	// only update its skin when it is hidden.
	if (iAdaptiveSearchGrid && !iAdaptiveSearchGrid->IsShown())
		{
		iAdaptiveSearchGrid->HandleResourceChange(KAknsMessageSkinChange);
		}
	}
// End of File

