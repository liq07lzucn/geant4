#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : 
# Package: Geant4.src.G4visualization.
#
# Intermediate level CMakeLists.txt - just process subdirectories
#
# Generated on : 24/9/2010
#
#
#------------------------------------------------------------------------------

#
# GL2PS built for GL and Inventor drivers
#
if(GEANT4_USE_OPENGL OR GEANT4_USE_INVENTOR)
    add_subdirectory(gl2ps)
endif()
