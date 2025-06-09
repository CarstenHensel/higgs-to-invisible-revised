#include "LeptonPairingAlg.h"
#include "edm4hep/ReconstructedParticle.h"
#include "edm4hep/Vector3f.h"
#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

DECLARE_COMPONENT(LeptonPairingAlg)

using namespace edm4hep;

template<class T>
double inv_mass(T* p1, T* p2){
  double e = p1->getEnergy()+p2->getEnergy() ;
  double px = p1->getMomentum()[0]+p2->getMomentum()[0];
  double py = p1->getMomentum()[1]+p2->getMomentum()[1];
  double pz = p1->getMomentum()[2]+p2->getMomentum()[2];
  return( sqrt( e*e - px*px - py*py - pz*pz  ) );
}


LeptonPairingAlg::LeptonPairingAlg(const std::string& aName, ISvcLocator* aSvcLoc) : Gaudi::Algorithm(aName, aSvcLoc){
  declareProperty("RecoParticleColl", m_recoParticleCollHandle, "RecoParticle collection");
  declareProperty("IsolatedLeptonsColl", m_isolatedLeptonsCollHandle, "Isolated Leptons collection");
  declareProperty("PFOsWOIsoLepColl", m_PFOsWOIsoLepCollHandle, "Isolated Leptons collection");
  declareProperty("doPhotonRecovery", m_doPhotonRecovery, "Do Photon Recovery");
  declareProperty("diLeptinInvariantMass", m_diLepInvMass, "Di-lepton Invariant Mass");
}

LeptonPairingAlg::~LeptonPairingAlg(){
} // destructor

StatusCode LeptonPairingAlg::initialize() {
  return StatusCode::SUCCESS; 
} // initialize()

StatusCode LeptonPairingAlg::execute(const EventContext&) const {
  const auto *isoLeptonColl = m_isolatedLeptonsCollHandle.get();
  int nLeptons = isoLeptonColl->size();
  if (nLeptons > 1) {

    std::vector< ReconstructedParticle > LeptonPair = {};
    int _lepton_type;
     double cosFSRCut; // the angle of BS and FSR around the direction of charged lepton

     if (m_doPhotonRecovery) cosFSRCut = 0.99;

     if (nLeptons == 2) {
       const ReconstructedParticle lepton1 = isoLeptonColl->at( 0 );
       const ReconstructedParticle lepton2 = isoLeptonColl->at( 1 );
       //Check if same type and have opposite charge
       if (lepton1.getType() + lepton2.getType() == 0) {
	 _lepton_type = abs(lepton1.getType());
	 LeptonPair = {lepton1, lepton2};
	 
	 float pairmass = inv_mass(&lepton1, &lepton2);
	 float delta = fabs(pairmass-m_diLepInvMass);
	 info() << "invariant mass " << pairmass << " " << delta << endmsg;      
	
       }
     } else {
       float mindelta = 99999.;
       for ( int i_lep1 = 0 ; i_lep1 < nLeptons - 1; ++i_lep1 ) {
	   const ReconstructedParticle lepton1 = isoLeptonColl->at( i_lep1 );
	   for ( int i_lep2 = i_lep1 + 1 ; i_lep2 < nLeptons ; ++i_lep2 ) {
	     const ReconstructedParticle lepton2 = isoLeptonColl->at( i_lep2 );
	     //Check if same type and have opposite charge 
	     if (lepton1.getType() + lepton2.getType() == 0) {
	       _lepton_type = abs(lepton1.getType());
	       float pairmass = inv_mass(&lepton1, &lepton2);
	       float delta = abs(pairmass-m_diLepInvMass);
	       if (delta > mindelta) continue;
	       mindelta = delta;  
	       LeptonPair = {lepton1, lepton2};
	     } 
	   }
       }
     } // if  (nLeptons == 2)
     std::vector<const ReconstructedParticle*> photons;
     if (LeptonPair.size() == 2) {
       const auto *PFOsWOIsoLepCollection = m_PFOsWOIsoLepCollHandle.get();
       // recovery of FSR and BS
       MutableReconstructedParticle recoLepton1 = LeptonPair[0].clone();
       this->doPhotonRecovery(&(LeptonPair[0]), PFOsWOIsoLepCollection, &recoLepton1,cosFSRCut, photons);
       MutableReconstructedParticle recoLepton2 = LeptonPair[1].clone();
       this->doPhotonRecovery(&(LeptonPair[1]), PFOsWOIsoLepCollection, &recoLepton2,cosFSRCut, photons);


       info() << "cos between leptons " << this->getCos(&(LeptonPair[0].getMomentum()), &(LeptonPair[1].getMomentum())) << endmsg;
       
       //m_LepPairCollection->push_back(recoLepton1);
       //m_LepPairCollection->push_back(recoLepton2);
     }
     
    
  } // if (isoLeptonColl->size() > 1)
  return StatusCode::SUCCESS; 
} // execute()


StatusCode LeptonPairingAlg::finalize() { 
  return StatusCode::SUCCESS; 
} // finalize()


float LeptonPairingAlg::dotProduct(const Vector3f* v1, const Vector3f* v2) const {
  return (*v1)[0] * (*v2)[0] + (*v1)[1] * (*v2)[1] * (*v1)[2] * (*v2)[2];
}

float LeptonPairingAlg::getMag(const Vector3f* v) const {
  return sqrt(this->dotProduct(v, v));
}

float LeptonPairingAlg::getCos(const Vector3f* v1, const Vector3f* v2) const {
  return this->dotProduct(v1, v2) / this->getMag(v1) / this->getMag(v2); 
}

void LeptonPairingAlg::doPhotonRecovery(edm4hep::ReconstructedParticle* lepton,
					const edm4hep::ReconstructedParticleCollection* pfoCollection,
					edm4hep::MutableReconstructedParticle* recoLepton,
					double cosFSRCut,
					std::vector<const edm4hep::ReconstructedParticle*> &photons) const {
  // recover the BS and FSR photons
  TLorentzVector* lorentzLepton = new TLorentzVector(lepton->getMomentum()[0], lepton->getMomentum()[1], lepton->getMomentum()[2], static_cast<double>(lepton->getEnergy()));
  edm4hep::CovMatrix4f _tmpArray = lepton->getCovMatrix();
  std::vector<float> leptonCovMat(_tmpArray.begin(), _tmpArray.end());


  for (const auto pfo : *pfoCollection) {
    if (pfo.getType() == 22) {
      Vector3f photonMomentum = pfo.getMomentum();
      Vector3f leptonMomentum = lepton->getMomentum();
      auto cosLeptonPhoton = this->getCos(&leptonMomentum, &photonMomentum);
      if (cosLeptonPhoton < cosFSRCut) continue;
      photons.push_back(&pfo);
      Vector3f recoLeptonMomentum = recoLepton->getMomentum();
      Vector3f momentumSum = Vector3f(recoLeptonMomentum[0] + photonMomentum[0],
				      recoLeptonMomentum[1] + photonMomentum[1],
				      recoLeptonMomentum[2] + photonMomentum[2]);
      recoLepton->setMomentum(momentumSum);
      recoLepton->setEnergy(recoLepton->getEnergy() + pfo.getEnergy());
      //TODO update particle mass
      //TODO update covariant matrix
    } // pfo == 22
  } // pfo loop
} // doPhotonRecovery

