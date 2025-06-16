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

