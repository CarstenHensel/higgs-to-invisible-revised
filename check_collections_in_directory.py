import os
import uproot
from pathlib import Path

# Optional: import LCIO only if available
try:
    from pyLCIO import IOIMPL
    lcio_available = True
except ImportError:
    print("⚠️ pyLCIO not available. LCIO files will be skipped.")
    lcio_available = False

# Collections to check for
collections_to_check = ["PandoraClusters", "MarlinTrkTracks"]

def check_edm4hep_file(filepath):
    print(f"\n📦 EDM4hep file: {os.path.basename(filepath)}")
    try:
        with uproot.open(filepath) as f:
            tree = f["events"]
            keys = tree.keys()
            present = [col for col in collections_to_check if any(k.startswith(col) for k in keys)]
            for col in collections_to_check:
                status = "✅ present" if col in present else "❌ missing"
                print(f"  - {col}: {status}")
    except Exception as e:
        print(f"  ❌ Error opening EDM4hep file: {e}")

def check_lcio_file(filepath):
    print(f"\n📦 LCIO file: {os.path.basename(filepath)}")
    if not lcio_available:
        print("  ❌ pyLCIO not available — skipping")
        return
    try:
        reader = IOIMPL.LCFactory.getInstance().createLCReader()
        reader.open(filepath)
        evt = reader.readNextEvent()
        if evt is None:
            print("  ⚠️ No events found.")
            return
        names = list(evt.getCollectionNames())
        for col in collections_to_check:
            status = "✅ present" if col in names else "❌ missing"
            print(f"  - {col}: {status}")
    except Exception as e:
        print(f"  ❌ Error reading LCIO file: {e}")
    finally:
        try:
            reader.close()
        except:
            pass

def main(directory):
    directory = Path(directory)
    if not directory.is_dir():
        print("❌ Not a valid directory.")
        return

    for filepath in directory.glob("**/*"):
        if filepath.suffix == ".slcio":
            check_lcio_file(str(filepath))
        elif filepath.suffix == ".root":
            check_edm4hep_file(str(filepath))

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python check_collections_in_directory.py /path/to/files")
    else:
        main(sys.argv[1])
