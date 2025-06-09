#!/bin/bash
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
