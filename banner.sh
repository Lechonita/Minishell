#!/bin/bash

colors=()

# Generate a random starting angle between 0 and 360
start_angle=$(shuf -i 0-359 -n 1)

# in r : 127 & 128 are used to shift the range from [-1, 1] to [0, 255]
# in g :0.01745 is the conversion factor from degrees to radians
# in b : 120 and 240 are used to get the other 2 colors of the RGB color wheel
for (( i = 0; i < 100; i++ )); do
    angle=$((start_angle + 360 * i / 100))
    r=$(printf "%.0f" $(bc -l <<< "s(0.01745 * $angle) * 127 + 128"))
    g=$(printf "%.0f" $(bc -l <<< "s(0.01745 * ($angle + 120)) * 127 + 128"))
    b=$(printf "%.0f" $(bc -l <<< "s(0.01745 * ($angle + 240)) * 127 + 128"))
    colors+=("${r};${g};${b}")

done

lines=(
"	 ________________________________________________________ 	                   	"
"	/\                                                       \	                   	"
"	\_|                                                      |	                   	"
"	  |                ▙▗▌▗    ▗ ▞▀▖▌     ▜▜                 |	                   	"
"	  |                ▌▘▌▄ ▛▀▖▄ ▚▄ ▛▀▖▞▀▖▐▐                 |	                   	"
"	  |                ▌ ▌▐ ▌ ▌▐ ▖ ▌▌ ▌▛▀ ▐▐                 |	                   	"
"	  |                ▘ ▘▀▘▘ ▘▀▘▝▀ ▘ ▘▝▀▘ ▘▘                |	                   	"
"	  |                                                      |	                   	"
"	  |   ___________________________________________________|_                   	"
"	   \_/_____________________________________________________/	★ Lechon & BeBig ★"
)

# lines=(
# "                                                                      "
# "         /\^/\`\                                                      "
# "        | \/   |                                                      "
# "        | |    |                                                      "
# "        \ \    /                                         _ _          "
# "         '\\\//'   ░█▄█░▀█▀░█▀█░▀█▀░█▀▀░█░█░█▀▀░█░░░█░░ _{ ' }_       "
# "           ||     ░█░█░░█░░█░█░░█░░▀▀█░█▀█░█▀▀░█░░░█░░{ \`.!.\` }     "
# "           ||     ░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀',_/Y\_,'       "
# "           ||  ,                                        {_,_}         "
# "       |\  ||  |\                                         |           "
# "       | | ||  | |                                      (\|  /)       "
# "       | | || / /                                        \| //        "
# "        \ \||/ /                                          |//         "
# "         \`\\\//\`   \   \./    \\\   \./    \\\   \./    \ \\\ |/ /  "
# "        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^       "
# )

for (( line = 0; line < ${#lines[@]}; line++ )); do
    for (( col = 0; col < ${#lines[0]}; col++ )); do
        color=(${colors[$col % ${#colors[@]}]//;/ })
        r=${color[0]}
        g=${color[1]}
        b=${color[2]}
        char="${lines[$line]:$col:1}" # Get the character at the current column
        echo -ne "\033[38;2;${r};${g};${b}m${char}"
    done
    echo -e "\033[0m" # Move to the next line after each row
done
echo -e "\033[0m" # Reset the terminal after printing the rainbow
