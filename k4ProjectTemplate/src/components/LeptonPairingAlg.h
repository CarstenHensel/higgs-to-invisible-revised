/*
 * Copyright (c) 2020-2024 Key4hep-Project.
 *
 * This file is part of Key4hep.
 * See https://key4hep.github.io/key4hep-doc/ for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

// GAUDI
// #include "Gaudi/Property.h"
// #include "GaudiAlg/GaudiAlgorithm.h"
#include "Gaudi/Algorithm.h"
#include "Gaudi/Property.h"

#include "edm4hep/MutableReconstructedParticle.h"
#include "edm4hep/ReconstructedParticleCollection.h"
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

  void doPhotonRecovery(edm4hep::ReconstructedParticle* lepton, const edm4hep::ReconstructedParticleCollection* colPFO,
                        edm4hep::MutableReconstructedParticle* recoLepton, double cosFSRCut,
                        std::vector<const edm4hep::ReconstructedParticle*>& photons) const;

private:
  // member variable
  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_recoParticleCollHandle{
      "ReconstructedParticleCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_isolatedLeptonsCollHandle{
      "IsolatedLeptonsCollection", Gaudi::DataHandle::Reader, this};

  mutable DataHandle<edm4hep::ReconstructedParticleCollection> m_PFOsWOIsoLepCollHandle{
      "PFOsWOIsoLepCollection", Gaudi::DataHandle::Reader, this};

  bool m_doPhotonRecovery;
  double m_diLepInvMass;
  edm4hep::ReconstructedParticleCollection* m_LepPairCollection;

  float dotProduct(const edm4hep::Vector3f* v1, const edm4hep::Vector3f* v2) const;
  float getMag(const edm4hep::Vector3f* v) const;
  float getCos(const edm4hep::Vector3f* v1, const edm4hep::Vector3f* v2) const;
};
