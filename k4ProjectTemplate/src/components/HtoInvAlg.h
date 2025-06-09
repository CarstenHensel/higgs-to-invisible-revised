#pragma once

// GAUDI
#include "Gaudi/Property.h"
#include "Gaudi/Algorithm.h"
#include "Gaudi/Property.h"


#include "edm4hep/ReconstructedParticleCollection.h"
#include "edm4hep/EventHeaderCollection.h"
#include "edm4hep/MCParticleCollection.h"
#include "k4FWCore/DataHandle.h"
#include "podio/UserDataCollection.h"

#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <vector>
#include <string>

class HtoInvAlg : public Gaudi::Algorithm {
public:
  explicit HtoInvAlg(const std::string&, ISvcLocator*);
  virtual ~HtoInvAlg();
  /**  Initialize.
   *   @return status code
   */
  StatusCode initialize() override;
  /**  Execute.
   *   @return status code
   */
  StatusCode execute(const EventContext&) const override;
  /**  Finalize.
   *   @return status code
   */
  StatusCode finalize() override;

  //write to tree
  void fillEvent() const; // call once per event

  // Helper method to add an MC particle
  void addMCParticle(float pt, float eta, float phi, float e,
                     int pdgId, int status, int motherPdgId) const;
  void addMCParticle(const TLorentzVector& p4,
                     int pdgId, int status, int motherPdgId) const;



  // Public variables to be filled before calling fillEvent()
  mutable int runNumber;
  mutable int eventNumber;
  mutable float lumiWeight;
  mutable float weight;
  mutable float sqrtS;
  mutable int channelType;  // 1 = leptonic Z, 2 = hadronic Z
  mutable int proc_id;


  // Jets
  mutable int nJets;
  mutable float jet_pt[2];
  mutable float jet_eta[2];
  mutable float jet_phi[2];
  mutable float jet_e[2];
  mutable float dijet_mass;
  mutable float dijet_pt;
 

  // leptons
  mutable int nLeptons;
  mutable float lep_pt[2];
  mutable float lep_eta[2];
  mutable float lep_phi[2];
  mutable float lep_e[2];
  mutable int lep_charge[2];
  mutable float dilepton_mass;
  mutable float dilepton_pt;
  
  // MET/Recoil
  mutable float MET;
  mutable float MET_phi;
  mutable float recoil_mass;
  mutable float recoil_pt;
  mutable float recoil_cosTheta;
 
  // kinematics
  mutable float acoplanarity;
  mutable float acollinearity;
  mutable float deltaPhi;
  mutable float deltaR;
  mutable float visible_mass;
  mutable float visible_energy;
  mutable float visible_pt;

  // MC Truth
  mutable int nMCParticles;
  mutable std::vector<float> mc_pt;
  mutable std::vector<float> mc_eta;
  mutable std::vector<float> mc_phi;
  mutable std::vector<float> mc_e;
  mutable std::vector<int> mc_pdgId;
  mutable std::vector<int> mc_status;
  mutable std::vector<int> mc_motherPdgId;



private:
  // member variable
  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_recoParticleCollHandle{
      "ReconstructedParticleCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_isolatedLeptonsCollHandle {
      "IsolatedLeptonsCollection", Gaudi::DataHandle::Reader, this};
  
  mutable DataHandle<edm4hep::EventHeaderCollection> m_eventHeaderCollHandle {
      "EventHeaderCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::MCParticleCollection> m_mcParticleCollHandle {
      "MCParticleColl", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<podio::UserDataCollection<float>> m_outMET{"MET", Gaudi::DataHandle::Writer, this};


  Gaudi::Property<std::vector<std::string>> m_outputs{this, "Outputs", {}, "Output collection names"};

  mutable double luminosity_weight;
  mutable int process_id;

  mutable int m_event_counter = 0;	

  mutable int m_member = 0;


  //tree related
  TFile* outFile;
  TTree* tree;

  void setupBranches();
};
