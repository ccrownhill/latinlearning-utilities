#!/bin/sh
gcc latinlaunch.c -o latinlaunch

cat > "$HOME/.local/bin/firefox" << EOF
#!/bin/sh
exec "$HOME/Repos/productivity-utils/latinutils/latinlaunch" /usr/bin/firefox
EOF

chmod 755 "$HOME/.local/bin/firefox"
