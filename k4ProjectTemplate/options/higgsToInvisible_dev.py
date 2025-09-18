#
# Copyright (c) 2020-2024 Key4hep-Project.
#
# This file is part of Key4hep.
# See https://key4hep.github.io/key4hep-doc/ for further info.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
from Gaudi.Configuration import *
import os


# INSERT_CUSTOM_CONFIG_HERE

from Configurables import k4DataSvc
from Configurables import MarlinProcessorWrapper, EDM4hep2LcioTool, Lcio2EDM4hepTool


evtSvc = k4DataSvc('EventDataSvc')
evtSvc.inputs = input_files

from Configurables import PodioInput
input = PodioInput("InputReader")
input.collections = ["PandoraPFOs", "PrimaryVertex", "PandoraClusters", "MarlinTrkTracks", "EventHeader", "MCParticlesSkimmed", "MET"]

from Configurables import LcioEvent
lcio_read = LcioEvent()
lcio_read.OutputLevel = DEBUG
lcio_read.Files = ["/eos/experiment/clicdp/grid/ilc/user/t/tjunping/data/slcio/E250_overlay/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00001.slcio"]


from Configurables import HtoInvAlg
myalg = HtoInvAlg()
myalg.RecoParticleColl = 'PandoraPFOs'
myalg.IsolatedLeptonsColl = 'IsolatedLeptons'
myalg.EventHeaderColl = 'EventHeader'
myalg.MCParticleColl = 'MCParticlesSkimmed'

# All values should be in compatible units
myalg.lumi_weight = lumi_weight
myalg.process_id = process_id
myalg.Outputs = "MET"

#myalg.MuonColl = 'Muons'
myalg.OutputLevel = INFO

# TreeWriter
from Configurables import TreeWriter
treewriter = TreeWriter()
treewriter.InputCollection = "MET"


# Isolated Lepton Processor

MyIsolatedLeptonTaggingProcessor = MarlinProcessorWrapper("MyIsolatedLeptonTaggingProcessor")
MyIsolatedLeptonTaggingProcessor.OutputLevel = DEBUG
MyIsolatedLeptonTaggingProcessor.ProcessorType = "IsolatedLeptonTaggingProcessor"
MyIsolatedLeptonTaggingProcessor.Parameters = {
                                               "CosConeLarge": ["0.95"],
                                               "CosConeSmall": ["0.98"],
                                               "CutOnTheISOElectronMVA": ["2.0"],
                                               "CutOnTheISOMuonMVA": ["0.7"],
                                               "DirOfISOElectronWeights": ["/cvmfs/ilc.desy.de/sw/x86_64_gcc82_centos7/v02-02-03/MarlinReco/v01-32/Analysis/IsolatedLeptonTagging/example/isolated_electron_weights"],
                                               "DirOfISOMuonWeights": ["/cvmfs/ilc.desy.de/sw/x86_64_gcc82_centos7/v02-02-03/MarlinReco/v01-32/Analysis/IsolatedLeptonTagging/example/isolated_muon_weights_woYoke"],
                                               "InputPandoraPFOsCollection": ["PandoraPFOs"],
                                               "InputPrimaryVertexCollection": ["PrimaryVertex"],
                                               "IsSelectingOneIsoLep": ["false"],
                                               "MaxD0SigForElectron": ["50"],
                                               "MaxD0SigForMuon": ["20"],
                                               "MaxEOverPForElectron": ["1.3"],
                                               "MaxEOverPForMuon": ["0.3"],
                                               "MaxZ0SigForElectron": ["50"],
                                               "MaxZ0SigForMuon": ["20"],
                                               "MinEOverPForElectron": ["0.5"],
                                               "MinEecalOverTotEForElectron": ["0.9"],
                                               "MinEyokeForMuon": ["1.2"],
                                               "MinPForElectron": ["5"],
                                               "MinPForMuon": ["5"],
                                               "OutputIsoLeptonsCollection": ["IsolatedLeptons"],
                                               "OutputPFOsWithoutIsoLepCollection": ["PandoraPFOsWithoutIsoLep"],
                                               "UseYokeForMuonID": ["false"]
                                               }




edm4hep2LcioConv = EDM4hep2LcioTool("EDM4hep2Lcio")
lcio2edm4hepConv = Lcio2EDM4hepTool("Lcio2EDM4hep")
edm4hep2LcioConv.convertAll = False
edm4hep2LcioConv.collNameMapping = {
        'PrimaryVertex':                   'PrimaryVertex',
        'PandoraPFOs':                     'PandoraPFOs',
        "PandoraClusters": "PandoraClusters",
        "MarlinTrkTracks": "MarlinTrkTracks"
      }


lcio2edm4hepConv.convertAll = False
lcio2edm4hepConv.collNameMapping = {
     'PandoraPFOs': 'PandoraPFOs',
     'IsolatedLeptons': 'IsolatedLeptons',
     'PandoraPFOsWithoutIsoLep': 'PandoraPFOsWithoutIsoLep',
     "PandoraClusters": "PandoraClusters",
     "MarlinTrkTracks": "MarlinTrkTracks"
     }




MyIsolatedLeptonTaggingProcessor.EDM4hep2LcioTool = edm4hep2LcioConv
MyIsolatedLeptonTaggingProcessor.Lcio2EDM4hepTool = lcio2edm4hepConv



# Lepton Pairing Processor
from Configurables import LeptonPairingAlg

MyLeptonPairing = LeptonPairingAlg()
MyLeptonPairing.RecoParticleColl = 'PandoraPFOs'
MyLeptonPairing.IsolatedLeptonsColl = 'IsolatedLeptons'
MyLeptonPairing.PFOsWOIsoLepColl = 'PandoraPFOsWithoutIsoLep'
MyLeptonPairing.doPhotonRecovery = True
MyLeptonPairing.diLeptinInvariantMass = 91.1876




from Configurables import PodioOutput
output = PodioOutput('output')
output.filename = 'tst.root'


from Configurables import ApplicationMgr
ApplicationMgr( TopAlg=[input, MyIsolatedLeptonTaggingProcessor, MyLeptonPairing, myalg, treewriter, output],
                EvtSel="NONE",
                EvtMax=3,
		        ExtSvc=[evtSvc],
                OutputLevel=DEBUG,
               )
