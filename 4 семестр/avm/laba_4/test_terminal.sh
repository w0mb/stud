#!/bin/bash

clear_screen="\033[2J"
set_red="\033[48;5;9m\033[38;5;9m"
set_green="\033[48;5;15m\033[38;5;2m"
default_colors="\033[0m"
cursor_pos="\033[10;1H"

echo -e "${clear_screen}"
echo -e "\n\n\n\n\n${set_red} Даниил Ледин ${default_colors}"
echo -e "\n\n\n\n\n\n${set_green} ИП-214 ${default_colors}"
echo -e "${cursor_pos}"
