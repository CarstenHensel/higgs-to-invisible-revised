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

#from samples_signal import samples, target_lumi
from samples_background import samples, target_lumi

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

