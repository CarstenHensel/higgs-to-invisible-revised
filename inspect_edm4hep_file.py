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
import sys

# Customize your expected collections here:
expected_collections = [
    "EventHeader",
    "MCParticles",
    "MCParticlesSkimmed",
    "PandoraPFOs",
    "PandoraClusters",
    "MarlinTrkTracks",
    "PrimaryVertex",
    "IsolatedLeptons",
    "MET"
]

def list_file_collections(filename):
    try:
        with uproot.open(filename) as file:
            # Grab the first event tree
            tree = file["events"] if "events" in file else next(iter(file.values()))
            branches = tree.keys()
            present = set(b.split('.')[0] for b in branches)

            print(f"\n📂 File: {filename}")
            print("📋 Collection presence check:")
            for col in expected_collections:
                status = "✅" if col in present else "❌"
                print(f"  {status} {col}")

            # Optionally: list all available collections
            print("\n🗂️  All available collections:")
            for col in sorted(present):
                print(f"  - {col}")
    except Exception as e:
        print(f"❌ Error reading {filename}: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python inspect_edm4hep_file.py <your_file.root>")
    else:
        list_file_collections(sys.argv[1])

