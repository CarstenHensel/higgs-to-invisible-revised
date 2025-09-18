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
#ifndef TREEWRITER_H
#define TREEWRITER_H

// GAUDI
#include "Gaudi/Algorithm.h"
#include "Gaudi/Property.h"

#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/ServiceHandle.h"
#include "k4FWCore/DataHandle.h"

#include "podio/UserDataCollection.h"

class ITHistSvc;

class TreeWriter : public Gaudi::Algorithm {
public:
  explicit TreeWriter(const std::string& name, ISvcLocator* svcLoc);
  virtual ~TreeWriter();

  StatusCode initialize() override;
  StatusCode execute(const EventContext&) const override;
  StatusCode finalize() override;

private:
  // Input collection names
  //  mutable DataHandle<podio:UserDataCollection> m_METHandle {
  //    "MET", Gaudi::DataHandle::Reader, this};
  mutable DataHandle<podio::UserDataCollection<float>> m_inMET{"MET", Gaudi::DataHandle::Reader, this};
};

#endif // TREEWRITER_H
