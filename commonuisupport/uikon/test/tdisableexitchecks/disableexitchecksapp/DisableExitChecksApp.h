/**
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* CExampleAppUi handles the system events and menu events
* 
*
*/



/**
 @file
 @internalComponent
 @test
*/
class CExampleAppUi : public CEikAppUi
    {
public:
    void ConstructL();
	~CExampleAppUi();

private:
    // Inherited from class CEikAppUi
	void HandleCommandL(TInt aCommand);
	TBool ProcessCommandParametersL(CApaCommandLine& aCommandLine);
	};


/**
 *	CExampleDocument for creating the application UI
 *	
 */  
class CExampleDocument : public CEikDocument
	{
public:
	// creates a CExampleDocument object
	static CExampleDocument* NewL(CEikApplication& aApp);
	CExampleDocument(CEikApplication& aApp);
	void ConstructL();
private: 
	// Inherited from CEikDocument for creating the AppUI
	CEikAppUi* CreateAppUiL();
	};
	
	
	
/**
 *	CExampleApplication creates a new instance of the document 
 *   associated with this application
 *	
 */  
class CExampleApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication to create a new instance of the document
	CApaDocument* CreateDocumentL();
	//gets the Application's UID
	TUid AppDllUid() const;
	};

