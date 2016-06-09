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
// $Id: pyG4Orb.cc,v 1.5 2007/07/13 04:57:50 kmura Exp $
// $Name: geant4-09-00-patch-02 $
// ====================================================================
//   pyG4Orb.cc
//
//                                         2005 Q
// ====================================================================
#include <boost/python.hpp>
#include "G4Orb.hh"

using namespace boost::python;

// ====================================================================
// wrappers
// ====================================================================
namespace pyG4Orb {

G4Orb* CreateOrb(const G4String& name, G4double pRmax)
{
  return new G4Orb(name, pRmax);
}

}

using namespace pyG4Orb;

// ====================================================================
// module definition
// ====================================================================
void export_G4Orb()
{
  class_<G4Orb, G4Orb*, bases<G4VSolid> >
    ("G4Orb", "Orb solid class", no_init)
    // constructors
    .def(init<const G4String&, G4double>())
    // ---
    .def("GetRadius", &G4Orb::GetRadius)
    .def("SetRadius", &G4Orb::SetRadius)
    // operators
    .def(self_ns::str(self))
    ;

    // Create solid
    def("CreateOrb", CreateOrb, return_value_policy<manage_new_object>());

}
