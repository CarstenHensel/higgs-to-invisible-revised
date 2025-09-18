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
        "name": "signals",
        "id": 1,
        "xsec": 6077.22,
        "nevents": 600,
        "files": [
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00002.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00003.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00004.root"
        ]
    },
    {
        "name": "2f_lep",
        "id": 2,
        "xsec": 6077.22,
        "nevents": 600,
        "files": [
            "/eos/experiment/clicdp/data/user/l/lreichen/miniDST/2f/2f_leptonic/l5_o1/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500006.P2f_z_l.eL.pR.n199.d_dstm_15457_401_mini-DST.edm4hep.root",
            "/eos/experiment/clicdp/data/user/l/lreichen/miniDST/2f/2f_leptonic/l5_o1/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500006.P2f_z_l.eL.pR.n199.d_dstm_15457_405_mini-DST.edm4hep.root",
            "/eos/experiment/clicdp/data/user/l/lreichen/miniDST/2f/2f_leptonic/l5_o1/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500006.P2f_z_l.eL.pR.n199.d_dstm_15457_406_mini-DST.edm4hep.root"
        ]
    },
]

