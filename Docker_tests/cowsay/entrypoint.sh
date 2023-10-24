#!/bin/bash
if [ $# -eq 0 ]; then
#/usr/games/fortune | /usr/games/cowsay
echo "while true; do clear && /usr/games/fortune | /usr/games/cowsay && sleep 3; done" > /usr/games/test.sh && chmod +x /usr/games/test.sh && /usr/games/test.sh
else
/usr/games/cowsay "$@"
fi
