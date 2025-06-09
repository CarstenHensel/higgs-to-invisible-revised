from samples_signal import samples, target_lumi
import json
import subprocess

file_list = []
weight_list = []
for sample in samples:
    file_list.extend(sample["files"])
    weight = (target_lumi * sample["xsec"]) / (sample["nevents"] / len(sample["files"]))
    weight_list.append(weight)

with open("../k4ProjectTemplate/options/higgsToInvisible_dev.py", "r") as infile:
    lines = infile.readlines()


file_list_string = json.dumps(file_list)

new_lines = []
for line in lines:
    if "# INSERT_CUSTOM_CONFIG_HERE" in line:
        new_lines.append(f"""
input_files = {file_list_string}
output_file = \"local_test.root\"
process_id = {sample['id']}
lumi_weight = {weight}
""")
    else:
        new_lines.append(line)

with open("steering_job.py", "w") as outfile:
    outfile.writelines(new_lines)

cmd = ["k4run", "steering_job.py"]
subprocess.run(cmd)

