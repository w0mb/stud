#!/bin/bash

clear

echo -e "\033[5;10H"

echo -e "\033(0"

echo "┌────────────────────┐"
for ((i=0; i<=8; i++)); do
    echo "│                    │"
done
echo "└────────────────────┘"
echo -e "\033[9;7H"
echo "│      aaaaaaaa"
echo "│      aa    aa"
echo "│      aaaaaaaa"
echo "│            aa"
echo "│      aaaaaaaa"


echo -e "\033[1;23H"
echo -e "\033(B"