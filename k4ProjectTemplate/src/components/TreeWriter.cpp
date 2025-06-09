#include "TreeWriter.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/ITHistSvc.h"

#include "edm4hep/EventHeaderCollection.h"
#include "podio/UserDataCollection.h"
#include "podio/Frame.h"

DECLARE_COMPONENT(TreeWriter)

TreeWriter::TreeWriter(const std::string& name, ISvcLocator* svcLoc)
  : Gaudi::Algorithm(name, svcLoc) {
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
