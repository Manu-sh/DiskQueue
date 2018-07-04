#!/bin/bash

green=$'\033[38;5;10m'
red=$'\033[38;5;9m'
yellow=$'\033[38;5;11m'
cian=$'\033[38;5;36m'
reset=$'\033[0m'

echo "building DiskArray..."
make test_diskarray &>/dev/null
echo -n "Testing..."
./test_diskarray && echo "${green}[OK]${reset}" || { echo "${red}[FAIL]${reset}"; exit 1; }
echo

echo "building DiskQueue..."
make test_diskqueue &>/dev/null
echo -n "Testing..."
./test_diskqueue && echo "${green}[OK]${reset}" || { echo "${red}[FAIL]${reset}"; exit 1; }
echo

echo "Cleaning..."
make clean &>/dev/null
