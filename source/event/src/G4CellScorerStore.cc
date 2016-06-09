//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4CellScorerStore.cc,v 1.3 2004/07/01 10:05:40 gcosmo Exp $
// GEANT4 tag $Name: geant4-06-02-patch-01 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4CellScorerStore.cc
//
// ----------------------------------------------------------------------

#include "G4CellScorerStore.hh"

#include "G4CellScorer.hh"

G4CellScorerStore::G4CellScorerStore() :
  fAutoCreate(false)
{}

G4CellScorerStore::~G4CellScorerStore()
{}

void G4CellScorerStore::SetAutoScorerCreate(){
  fAutoCreate = true;
}

G4CellScorer *G4CellScorerStore::
AddCellScorer(G4VPhysicalVolume &vol, G4int repnum) {
  G4CellScorer *s = 0;
  s = new G4CellScorer;
  if (!s) {
    G4Exception("ERROR:G4CellScorerStore::AddCellScorer new failed to create G4CellScorer!");
  }  
  fMapGeometryCellCellScorer[G4GeometryCell(vol, repnum)] = s;
  return s;
}

G4CellScorer *G4CellScorerStore::
AddCellScorer(const G4GeometryCell &gCell) {
  G4CellScorer *s = 0;
  s = new G4CellScorer;
  if (!s) {
    G4Exception("ERROR:G4CellScorerStore::AddCellScorer new failed to create G4CellScorer!");
  }  
  fMapGeometryCellCellScorer[gCell] = s;
  return s;
}

const G4MapGeometryCellCellScorer &G4CellScorerStore::GetMapGeometryCellCellScorer() const {
  return fMapGeometryCellCellScorer;
}

G4VCellScorer *G4CellScorerStore::
GetCellScore(const G4GeometryCell &gCell){
  G4VCellScorer *s=0;
  G4MapGeometryCellCellScorer::iterator it = fMapGeometryCellCellScorer.find(gCell);
  if (it != fMapGeometryCellCellScorer.end()) {
    s = (*it).second;
  }
  else {
    if (fAutoCreate) {
      s =  AddCellScorer(gCell);
    }
  }
  return s;
}

void G4CellScorerStore::DeleteAllScorers(){
  for(G4MapGeometryCellCellScorer::iterator it = 
	fMapGeometryCellCellScorer.begin(); 
      it!=fMapGeometryCellCellScorer.end();
      ++it){
    delete it->second;
  }
  fMapGeometryCellCellScorer.clear();
}