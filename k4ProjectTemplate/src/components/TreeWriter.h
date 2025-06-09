#ifndef TREEWRITER_H
#define TREEWRITER_H

// GAUDI
#include "Gaudi/Property.h"
#include "Gaudi/Algorithm.h"
#include "Gaudi/Property.h"

#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/NTuple.h"
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
