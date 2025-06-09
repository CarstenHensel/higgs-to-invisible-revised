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

