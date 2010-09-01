/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ScreenSaverAnimPluginInfo exports the list of enumerations 
*                to format specific plugins
*
*/

#ifndef NPNEXTENSIONS_H
#define NPNEXTENSIONS_H

/* 
* Enumerations for setting the information from Screensaver Animation
* plugin to format specific plugins
*/

enum
    {
    /* Defines the interaction mode with the plugin */  
    NPNInteractionMode = 100,
    
    /* Defines Start/end animation event */
    NPNScreenSaverAnimationEvent=101
    };
    
/* 
* Enumerations for getting the information from format specific plugins 
* by Screen saver animation plugin  
*/    
    
enum
    {
    /* Gets the file validity, Int - KErrNone if the file is valid 
     * other error codes if not
     */
    NPPCheckFileIsValid=100,
    
    /* Gets the last error encountered by the plugin. 
     * Int - System wide error code
     */
    NPPScreenSaverGetLastError=101,
    
    /* Checks whether the error is fatal 
     * Bool True if the error is fatal, false if not
     */
    NPPScreenSaverIsErrorFatal=102
    };
    
typedef enum 
    {
    /* Default Mode */
    NPDefaultMode = 1,
    
    /* Set when the plugin is started for ScreenSaver */ 
    NPScreenSaverMode
    } NPInteractionMode;    
    
typedef enum 
    {
    /* Sent to the plugin when the ScreenSaver is activated */
    NPStartAnimation = 1,
    
    /* Sent to the plugin when the ScreenSaver is deactivated */
    NPEndAnimation
    } NPAnimationEvent;
        
typedef struct _NPCheckFile
    {
    /* Error returned by the plugin after validity check */
    TInt  fileValidityCheckError;
    
    /* Name of the file to be checked for Validity */
    HBufC* fileName;
    } NPCheckFile;
  
  
/* 
 * The NPInteractionMode needs to be sent to the Flash Plugin
 * in the newp call, The interaction mode attribute name is passed 
 * in argn and the attribute value is passed in argv parameter.
 * The mode parameter of newp is not used in Screensaver mode.
 */
_LIT( KAttributeInteractionMode , "interactionmode" );
_LIT( KValueScreensaver, "screensaver" );
    
    

#endif // NPNEXTENSIONS_H
// End Of file


