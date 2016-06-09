//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: TestEm8.cc,v 1.8 2007/07/27 15:29:38 vnivanch Exp $
// GEANT4 tag $Name: geant4-09-00-patch-02 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - TestEm8 
//
// --------------------------------------------------------------
// Comments
//     
//   
// --------------------------------------------------------------

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "Em8DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "Em8PrimaryGeneratorAction.hh"
#include "Em8RunAction.hh"
#include "Em8EventAction.hh"
#include "Em8SteppingAction.hh"
#include "Em8SteppingVerbose.hh"

int main(int argc,char** argv) 
{

  //choose the Random engine

  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  //my Verbose output class

  G4VSteppingVerbose::SetInstance(new Em8SteppingVerbose);
    
  // Construct the default run manager

  G4RunManager * runManager = new G4RunManager;

  // set mandatory initialization classes

  Em8DetectorConstruction* detector;
  detector = new Em8DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);
  
#ifdef G4VIS_USE
  G4VisManager* visManager = 0;
#endif 
 
  // set user action classes

  runManager->SetUserAction(new Em8PrimaryGeneratorAction(detector));

  Em8RunAction* runAction = new Em8RunAction;

  runManager->SetUserAction(runAction);

  Em8EventAction* eventAction = new Em8EventAction(runAction);

  runManager->SetUserAction(eventAction);

  Em8SteppingAction* steppingAction = new Em8SteppingAction(detector,
                                                            eventAction, 
                                                            runAction);
  runManager->SetUserAction(steppingAction);
  
  G4UImanager* UI = G4UImanager::GetUIpointer();  
 
  if (argc==1)   // Define UI terminal for interactive mode  
    { 
#ifdef G4VIS_USE
      visManager = new G4VisExecutive;
      visManager->Initialize();
#endif 
      G4UIsession * session = new G4UIterminal;
      UI->ApplyCommand("/control/execute init.mac");    
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }
    
  // job termination
  
#ifdef G4VIS_USE
  delete visManager;
#endif  
  delete runManager;

  return 0;
}

