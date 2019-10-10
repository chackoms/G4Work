//
// Created by Michael Chacko on 2019-06-24.
//

#include "testG4DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

testG4DetectorConstruction::testG4DetectorConstruction()
: G4VUserDetectorConstruction(),
    fScoringVolume(0)
{ }

testG4DetectorConstruction::~testG4DetectorConstruction()
{ }

G4VPhysicalVolume* testG4DetectorConstruction::Construct()
{
// Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;
    G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

    G4double world_sizeXY = 1.2*env_sizeXY;
    G4double world_sizeZ  = 1.2*env_sizeZ;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld =
            new G4Box("World",                       //its name
                      0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

    G4LogicalVolume* logicWorld =
            new G4LogicalVolume(solidWorld,          //its solid
                                world_mat,           //its material
                                "World");            //its name

    G4VPhysicalVolume* physWorld =
            new G4PVPlacement(0,                     //no rotation
                              G4ThreeVector(),       //at (0,0,0)
                              logicWorld,            //its logical volume
                              "World",               //its name
                              0,                     //its mother  volume
                              false,                 //no boolean operation
                              0,                     //copy number
                              checkOverlaps);        //overlaps checking
    G4Box* solidEnv =
            new G4Box("Envelope",                    //its name
                      0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

    G4LogicalVolume* logicEnv =
            new G4LogicalVolume(solidEnv,            //its solid
                                env_mat,             //its material
                                "Envelope");         //its name

    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicEnv,                //its logical volume
                      "Envelope",              //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking

    // Shape 1
    //
    G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_Ti");
    G4ThreeVector pos1 = G4ThreeVector(0, 0, -7*cm);

    // Conical section shape
    G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
    G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
    G4double shape1_hz = 1.*cm;
    G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
    G4Cons* solidShape1 =
            new G4Cons("Shape1",
                       shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
                       shape1_phimin, shape1_phimax);

    G4LogicalVolume* logicShape1 =
            new G4LogicalVolume(solidShape1,         //its solid
                                shape1_mat,          //its material
                                "Shape1");           //its name

    new G4PVPlacement(0,                       //no rotation
                      pos1,                    //at position
                      logicShape1,             //its logical volume
                      "Shape1",                //its name
                      logicEnv,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking

    fScoringVolume = logicShape1;
    return physWorld;

}