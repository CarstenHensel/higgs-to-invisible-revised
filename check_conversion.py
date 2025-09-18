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
import uproot
from pyLCIO import IOIMPL
import os

def get_lcio_collections(filename):
    reader = IOIMPL.LCFactory.getInstance().createLCReader()
    reader.open(filename)
    event = reader.readNextEvent()
    reader.close()
    return set(event.getCollectionNames())

def get_edm4hep_collections(filename):
    with uproot.open(filename) as file:
        if "events" not in file:
            raise RuntimeError("No 'events' TTree found in EDM4hep file.")
        tree = file["events"]
        branches = set(branch.split(".")[0] for branch in tree.keys())
    return branches

def compare_collections(lcio_file, edm4hep_file):
    lcio_cols = get_lcio_collections(lcio_file)
    edm_cols = get_edm4hep_collections(edm4hep_file)

    print(f"\n📂 LCIO File: {lcio_file}")
    print(f"📂 EDM4hep File: {edm4hep_file}")

    print(f"\n✅ Collections present in both:")
    for col in sorted(lcio_cols & edm_cols):
        print(f"  - {col}")

    print(f"\n⚠️ Collections in LCIO but missing in EDM4hep:")
    for col in sorted(lcio_cols - edm_cols):
        print(f"  - {col}")

    print(f"\n🟡 Collections in EDM4hep but not in LCIO (rare):")
    for col in sorted(edm_cols - lcio_cols):
        print(f"  - {col}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python check_conversion.py <input.slcio> <input.root>")
    else:
        compare_collections(sys.argv[1], sys.argv[2])

