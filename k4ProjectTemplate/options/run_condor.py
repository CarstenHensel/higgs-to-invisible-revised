from samples import samples, target_lumi

eos_out_dir = "/eos/user/c/chensel/HinvOutput"

with open("jobs.txt", "w") as f:
    for sample in samples:
        for i, file in enumerate(sample["files"]):
            weight = (target_lumi * sample["xsec"]) / (sample["nevents"] / len(sample["files"]))
            output = f"{eos_out_dir}/{sample['name']}_{i}.root"
            f.write(f"{sample['id']} {weight} {file} {output}\n")
