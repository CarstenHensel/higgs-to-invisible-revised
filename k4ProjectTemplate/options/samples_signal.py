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
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00004.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00005.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00006.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00007.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00008.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00009.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00010.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00011.root",
            "/eos/user/c/chensel/ILC/Input/Signal/Dirac-Dst-E250-e2e2h_inv.eL.pR_bg-00012.root"
        ]
    }
]

