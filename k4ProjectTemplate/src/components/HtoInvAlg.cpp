#include <TLorentzVector.h>

#include <vector>

#include "GaudiKernel/MsgStream.h"
#include "HtoInvAlg.h"
#include "edm4hep/ReconstructedParticle.h"
#include "edm4hep/Vector3d.h"
#include "podio/UserDataCollection.h"
#include "podio/Frame.h"


DECLARE_COMPONENT(HtoInvAlg)

HtoInvAlg::HtoInvAlg(const std::string& aName, ISvcLocator* aSvcLoc)
    : Gaudi::Algorithm(aName, aSvcLoc) {
  declareProperty("RecoParticleColl", m_recoParticleCollHandle,
                  "RecoParticle collection");
  declareProperty("IsolatedLeptonsColl", m_isolatedLeptonsCollHandle,
                  "Isolated Leptons collection");
  declareProperty("EventHeaderColl", m_eventHeaderCollHandle,
                  "Event Header collection");
  declareProperty("MCParticleColl", m_mcParticleCollHandle,
                  "MC Particle collection");

  declareProperty("Outputs", m_outMET, "Name of the output MET collection");


  declareProperty("lumi_weight", luminosity_weight,"Lumi_weight");
  declareProperty("process_id", process_id,"process_id");

  std::string filename = "output_tree.root";
  outFile = new TFile(filename.c_str(), "RECREATE");
  tree = new TTree("events", "Higgs to Invisible Analysis Tree");
  setupBranches();
}

HtoInvAlg::~HtoInvAlg() {}

StatusCode HtoInvAlg::initialize() {
  m_event_counter = 0;
  return StatusCode::SUCCESS;
}

StatusCode HtoInvAlg::execute(const EventContext& event) const {
  m_event_counter += 1;

  const auto* isoLeptonColl = m_isolatedLeptonsCollHandle.get();
  const auto* recoColl = m_recoParticleCollHandle.get();
  const auto* eventHeaderColl = m_eventHeaderCollHandle.get();
  const auto* mcParticleColl = m_mcParticleCollHandle.get();


  auto userMET = m_outMET.createAndPut();
  userMET->push_back(50.0 + m_event_counter);


  if (eventHeaderColl && !eventHeaderColl->empty()) {
    eventNumber = eventHeaderColl->at(0).getEventNumber();
    runNumber = eventHeaderColl->at(0).getRunNumber();
    // sqrtS = eventHeaderColl->at(0).getEnergy();
    sqrtS = 250.0;
    lumiWeight = luminosity_weight;
    proc_id = process_id;
  }

  // calculate MET
  float sum_px = 0.0f;
  float sum_py = 0.0f;

  for (const auto p : *recoColl) {
      sum_px += p.getMomentum().x;
      sum_py += p.getMomentum().y;
  }

  float met_x = -sum_px;
  float met_y = -sum_py;
  MET = std::sqrt(met_x * met_x + met_y * met_y);
  MET_phi = std::atan2(met_y, met_x); 

  // look for muons
  int muonsFound = 0;
  double sqrts = 250.0;
  std::vector<TLorentzVector> muons;
  std::vector<edm4hep::ReconstructedParticle> muonCandidates;
  TLorentzVector totalVisibleP4(0, 0, 0, 0);

  for (const auto reco : *recoColl) {
    float energy = reco.getEnergy();
    TLorentzVector p4;
    p4.SetPxPyPzE(reco.getMomentum()[0], reco.getMomentum()[1],
                  reco.getMomentum()[2], energy);
    totalVisibleP4 += p4;

    if (std::abs(reco.getType()) == 13) {
      muonCandidates.push_back(reco);
      TLorentzVector muon = TLorentzVector();
      muon.SetPxPyPzE(reco.getMomentum()[0], reco.getMomentum()[1],
                      reco.getMomentum()[2], reco.getEnergy());
      muons.push_back(muon);
      muonsFound++;
    }
  }

  visible_mass = totalVisibleP4.M();
  visible_pt = totalVisibleP4.Pt();
  visible_energy = totalVisibleP4.E();

  nLeptons = muonsFound;

  if (nLeptons > 0) {
    for (int i = 0; i < nLeptons; i++) {
      lep_pt[i] = muons[i].Pt();
      lep_eta[i] = muons[i].Eta();
      lep_phi[i] = muons[i].Phi();
      lep_e[i] = muons[i].E();
      lep_charge[i] = muonCandidates[i].getCharge();
    }
  }

  if (muonsFound > 1) {
    double dphi = TVector2::Phi_mpi_pi(muons[0].Phi() - muons[1].Phi());
    deltaPhi = dphi;
    acoplanarity = M_PI - std::abs(dphi);

    double angle =
        muons[0].Vect().Angle(muons[1].Vect());  // returns angle in radians
    acollinearity = M_PI - angle;

    float deltaEta = muons[0].Eta() - muons[1].Eta();
    deltaR = std::sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);

    TLorentzVector dilepton_p4 = muons[0] + muons[1];

    dilepton_mass = dilepton_p4.M();
    dilepton_pt = dilepton_p4.Pt();

    TLorentzVector initial_p4(0, 0, 0, sqrtS);
    TLorentzVector recoil_p4 = initial_p4 - dilepton_p4;
    recoil_mass = recoil_p4.M();
    recoil_pt = recoil_p4.Pt();
    recoil_cosTheta = recoil_p4.CosTheta();
  }

  // MC particles
  for (const auto& mc : *mcParticleColl) {
    auto parents = mc.getParents();
    int parentPDG;
    if (!parents.empty()) {
      const auto& parent = parents[0];  // if you just want the first parent
      parentPDG = parent.getPDG();
    } else {
      parentPDG = 0;
    }

    TLorentzVector p4;
    auto mom = mc.getMomentum();
    p4.SetPxPyPzE(mom.x, mom.y, mom.z, mc.getEnergy());
    addMCParticle(p4, mc.getPDG(), mc.getSimulatorStatus(), parentPDG);
  }

  fillEvent();
  return StatusCode::SUCCESS;
}

StatusCode HtoInvAlg::finalize() {
  if (outFile && tree) {
    outFile->cd();
    tree->Write();
    outFile->Close();

    delete outFile;
    outFile = nullptr;
    tree = nullptr;
  }

  return StatusCode::SUCCESS;
}

void HtoInvAlg::setupBranches() {
  tree->Branch("runNumber", &runNumber, "runNumber/I");
  tree->Branch("eventNumber", &eventNumber, "eventNumber/I");
  tree->Branch("lumiWeight", &lumiWeight, "lumiWeight/F");
  tree->Branch("weight", &weight, "weight/F");
  tree->Branch("sqrtS", &sqrtS, "sqrtS/F");
  tree->Branch("channelType", &channelType, "channelType/I");
  tree->Branch("processID", &proc_id, "processID/I");

  // Jets
  tree->Branch("nJets", &nJets, "nJets/I");
  tree->Branch("jet_pt", jet_pt, "jet_pt[nJets]/F");
  tree->Branch("jet_eta", jet_eta, "jet_eta[nJets]/F");
  tree->Branch("jet_phi", jet_phi, "jet_phi[nJets]/F");
  tree->Branch("jet_e", jet_e, "jet_e[nJets]/F");
  tree->Branch("dijet_mass", &dijet_mass, "dijet_mass/F");
  tree->Branch("dijet_pt", &dijet_pt, "dijet_pt/F");

  // leptons
  tree->Branch("nLeptons", &nLeptons, "nLeptons/I");
  tree->Branch("lep_pt", lep_pt, "lep_pt[nLeptons]/F");
  tree->Branch("lep_eta", lep_eta, "lep_eta[nLeptons]/F");
  tree->Branch("lep_phi", lep_phi, "lep_phi[nLeptons]/F");
  tree->Branch("lep_e", lep_e, "lep_e[nLeptons]/F");
  tree->Branch("lep_charge", lep_charge, "lep_charge[nLeptons]/I");

  tree->Branch("dilepton_mass", &dilepton_mass, "dilepton_mass/F");
  tree->Branch("dilepton_pt", &dilepton_pt, "dilepton_pt/F");

  tree->Branch("MET", &MET, "MET/F");
  tree->Branch("MET_phi", &MET_phi, "MET_phi/F");
  tree->Branch("recoil_mass", &recoil_mass, "recoil_mass/F");
  tree->Branch("recoil_pt", &recoil_pt, "recoil_pt/F");
  tree->Branch("recoil_cosTheta", &recoil_cosTheta, "recoil_cosTheta/F");
  // kinematics
  tree->Branch("acoplanarity", &acoplanarity, "acoplanarity/F");
  tree->Branch("acollinearity", &acollinearity, "acollinearity/F");
  tree->Branch("deltaPhi", &deltaPhi, "deltaPhi/F");
  tree->Branch("deltaR", &deltaR, "deltaR/F");
  tree->Branch("visible_mass", &visible_mass, "visible_mass/F");
  tree->Branch("visible_energy", &visible_energy, "visible_energy/F");
  tree->Branch("visible_pt", &visible_pt, "visible_pt/F");

  // MC truth
  tree->Branch("nMCParticles", &nMCParticles, "nMCParticles/I");
  tree->Branch("mc_pt", &mc_pt);
  tree->Branch("mc_eta", &mc_eta);
  tree->Branch("mc_phi", &mc_phi);
  tree->Branch("mc_e", &mc_e);
  tree->Branch("mc_pdgId", &mc_pdgId);
  tree->Branch("mc_status", &mc_status);
  tree->Branch("mc_motherPdgId", &mc_motherPdgId);
}

void HtoInvAlg::addMCParticle(const TLorentzVector& p4, int pdgId, int status,
                              int motherPdgId) const {
  addMCParticle(p4.Pt(), p4.Eta(), p4.Phi(), p4.E(), pdgId, status,
                motherPdgId);
}

void HtoInvAlg::addMCParticle(float pt, float eta, float phi, float e,
                              int pdgId, int status, int motherPdgId) const {
  mc_pt.push_back(pt);
  mc_eta.push_back(eta);
  mc_phi.push_back(phi);
  mc_e.push_back(e);
  mc_pdgId.push_back(pdgId);
  mc_status.push_back(status);
  mc_motherPdgId.push_back(motherPdgId);
  nMCParticles = mc_pt.size();
}

void HtoInvAlg::fillEvent() const {
  tree->Fill();
  // Clear MC truth vectors
  mc_pt.clear();
  mc_eta.clear();
  mc_phi.clear();
  mc_e.clear();
  mc_pdgId.clear();
  mc_status.clear();
  mc_motherPdgId.clear();
}


