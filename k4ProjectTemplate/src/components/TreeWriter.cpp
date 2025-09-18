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
#include "TreeWriter.h"

#include "GaudiKernel/ITHistSvc.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"

#include "edm4hep/EventHeaderCollection.h"
#include "podio/Frame.h"
#include "podio/UserDataCollection.h"

DECLARE_COMPONENT(TreeWriter)

TreeWriter::TreeWriter(const std::string& name, ISvcLocator* svcLoc) : Gaudi::Algorithm(name, svcLoc) {
  declareProperty("InputCollection", m_inMET, "Name of the output MET collection");
}

TreeWriter::~TreeWriter() {}

StatusCode TreeWriter::initialize() {
  info() << "Initializing TreeWriter" << endmsg;
  return StatusCode::SUCCESS;
}

StatusCode TreeWriter::execute(const EventContext& event) const {

  // Retrieve the MET collection from the event store
  const auto& retrievedMET = *m_inMET.get();

  // Access the value
  if (!retrievedMET.empty()) {
    auto value = retrievedMET[0];
    std::cout << "Tree Writer Retrieved MET: " << value << std::endl;
  } else {
    warning() << "MET collection is empty!" << endmsg;
  }

  return StatusCode::SUCCESS;
}

StatusCode TreeWriter::finalize() {
  info() << "Finalizing TreeWriter" << endmsg;
  return StatusCode::SUCCESS;
}
