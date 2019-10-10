//
// Created by Michael Chacko on 2019-06-24.
//

#ifndef MAIN_CPP_TESTG4DETECTORCONSTRUCTION_H
#define MAIN_CPP_TESTG4DETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class testG4DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    testG4DetectorConstruction();
    virtual ~testG4DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

protected:
    G4LogicalVolume*  fScoringVolume;
};

#endif //MAIN_CPP_TESTG4DETECTORCONSTRUCTION_H
