#!/bin/bash
##
## Copyright (c) 2020-2024 Key4hep-Project.
##
## This file is part of Key4hep.
## See https://key4hep.github.io/key4hep-doc/ for further info.
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
procid=$1
weight=$2
inputfile=$3
outfile=$4

source source /cvmfs/sw.hsf.org/key4hep/setup.sh -r 2025-01-28
k4run ../k4ProjectTemplate/options/higgsToInvisible_dev.py
  "InputFiles=${inputfile}" \
  "LumiWeight=${weight}" \
  "ProcessID=${procid}" \
  "OutputFile=local_output.root"

xrdcp -f local_output.root root://eosuser.cern.ch/${outfile}
