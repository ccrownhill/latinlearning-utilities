#!/bin/sh
DEFAULT_NUM_VOC=5
DEFAULT_VOC_FILE="$HOME/.local/share/latinvoc.txt"
declare -a LATINLAUNCH_APPLICATIONS
LATINLAUNCH_APPLICATIONS=("/usr/bin/firefox" "/var/lib/flatpak/exports/bin/com.microsoft.Teams")

gcc latinlaunch.c -o latinlaunch
cp latinlaunch "$HOME/.local/bin"

for app in ${LATINLAUNCH_APPLICATIONS[@]}; do
	cat > "$HOME/.local/bin/$(basename $app)" <<- EOF
	#!/bin/sh
	exec "$HOME/.local/bin/latinlaunch" --numvoc $DEFAULT_NUM_VOC --vocfile $DEFAULT_VOC_FILE $app
	EOF
	chmod 755 "$HOME/.local/bin/$(basename $app)"
done

chmod 755 "latinlearn.py"
cp "latinlearn.py" "$HOME/.local/bin/latinlearn" # get rid of .py extension
