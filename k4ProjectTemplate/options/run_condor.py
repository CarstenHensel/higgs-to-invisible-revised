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
from samples import samples, target_lumi

eos_out_dir = "/eos/user/c/chensel/HinvOutput"

with open("jobs.txt", "w") as f:
    for sample in samples:
        for i, file in enumerate(sample["files"]):
            weight = (target_lumi * sample["xsec"]) / (sample["nevents"] / len(sample["files"]))
            output = f"{eos_out_dir}/{sample['name']}_{i}.root"
            f.write(f"{sample['id']} {weight} {file} {output}\n")
