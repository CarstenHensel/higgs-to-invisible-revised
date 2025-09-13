import os
import sys
from pyLCIO import IOIMPL

# Set which collections to check
collections_to_check = ["PandoraClusters", "MarlinTrkTracks"]

def check_collections_in_file(filepath):
    reader = IOIMPL.LCFactory.getInstance().createLCReader()
    try:
        reader.open(filepath)
        evt = reader.readNextEvent()
        if evt is None:
            print(f"{filepath}: ⚠️ No events found.")
            return None
        present = [name for name in collections_to_check if name in evt.getCollectionNames()]
        missing = [name for name in collections_to_check if name not in present]
        print(f"{os.path.basename(filepath)}:")
        for name in collections_to_check:
            status = "✅ present" if name in present else "❌ missing"
            print(f"  - {name}: {status}")
    except Exception as e:
        print(f"{filepath}: ❌ Error reading file: {e}")
    finally:
        reader.close()

def main(directory):
    if not os.path.isdir(directory):
        print("Provided path is not a valid directory.")
        return

    lcio_files = [f for f in os.listdir(directory) if f.endswith(".slcio")]
    if not lcio_files:
        print("No .slcio files found in directory.")
        return

    print(f"\n📂 Checking LCIO files in: {directory}\n")
    for filename in lcio_files:
        full_path = os.path.join(directory, filename)
        check_collections_in_file(full_path)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python check_lcio_collections.py /path/to/lcio/files")
    else:
        main(sys.argv[1])
