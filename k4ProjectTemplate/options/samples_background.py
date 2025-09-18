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
target_lumi = 137000  # in /pb

samples = [
    {
        "name": "2f_lep",
        "id": 2,
        "xsec": 6077.22,
        "nevents": 600,
        "files": [
            "/afs/cern.ch/user/c/chensel/cernbox/ILC/HtoInv/MC/MC_test/edm4hep/rv02-02-01.sv02-02.mILD_l5_o2_v02.E250-SetA.I500078.P4f_zznu_sl.eL.pR.n000_001.d_dst_00015656_146.root",
            "/afs/cern.ch/user/c/chensel/cernbox/ILC/HtoInv/MC/MC_test/edm4hep/rv02-02-01.sv02-02.mILD_l5_o2_v02.E250-SetA.I500078.P4f_zznu_sl.eL.pR.n000_002.d_dst_00015656_70.root",
            "/afs/cern.ch/user/c/chensel/cernbox/ILC/HtoInv/MC/MC_test/edm4hep/rv02-02-01.sv02-02.mILD_l5_o2_v02.E250-SetA.I500078.P4f_zznu_sl.eL.pR.n000_003.d_dst_00015656_201.root",
            "/afs/cern.ch/user/c/chensel/cernbox/ILC/HtoInv/MC/MC_test/edm4hep/rv02-02-01.sv02-02.mILD_l5_o2_v02.E250-SetA.I500078.P4f_zznu_sl.eL.pR.n000_004.d_dst_00015656_167.root",
            "/afs/cern.ch/user/c/chensel/cernbox/ILC/HtoInv/MC/MC_test/edm4hep/rv02-02-01.sv02-02.mILD_l5_o2_v02.E250-SetA.I500078.P4f_zznu_sl.eL.pR.n000_005.d_dst_00015656_91.root"
        ]
    },
]

