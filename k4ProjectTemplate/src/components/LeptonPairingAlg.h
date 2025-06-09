#pragma once

// GAUDI
//#include "Gaudi/Property.h"
//#include "GaudiAlg/GaudiAlgorithm.h"
#include "Gaudi/Algorithm.h"
#include "Gaudi/Property.h"


#include "edm4hep/ReconstructedParticleCollection.h"
#include "edm4hep/MutableReconstructedParticle.h"
#include "k4FWCore/DataHandle.h"

#include "TFile.h"
#include "TH1.h"
#include "TNtuple.h"


class LeptonPairingAlg : public Gaudi::Algorithm {
public:
  explicit LeptonPairingAlg(const std::string&, ISvcLocator*);
  virtual ~LeptonPairingAlg();
  /**  Initialize.
   *   @return status code
   */
  StatusCode initialize() final;
  /**  Execute.
   *   @return status code
   */
  StatusCode execute(const EventContext&) const override;
  /**  Finalize.
   *   @return status code
   */
  StatusCode finalize() final;

  void doPhotonRecovery(edm4hep::ReconstructedParticle* lepton,
			const edm4hep::ReconstructedParticleCollection* colPFO,
			edm4hep::MutableReconstructedParticle* recoLepton,
			double cosFSRCut,
			std::vector<const edm4hep::ReconstructedParticle*> &photons) const;

  
private:
  // member variable
  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_recoParticleCollHandle{
      "ReconstructedParticleCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_isolatedLeptonsCollHandle{
      "IsolatedLeptonsCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::ReconstructedParticleCollection>  m_PFOsWOIsoLepCollHandle{
      "PFOsWOIsoLepCollection", Gaudi::DataHandle::Reader, this};

  bool m_doPhotonRecovery; 
  double m_diLepInvMass;
  edm4hep::ReconstructedParticleCollection*  m_LepPairCollection;

  float dotProduct(const edm4hep::Vector3f* v1, const edm4hep::Vector3f* v2) const;
  float getMag(const edm4hep::Vector3f* v) const;
  float getCos(const edm4hep::Vector3f* v1, const edm4hep::Vector3f* v2) const;
  
};
