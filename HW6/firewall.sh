#!/bin/bash

PACKET_F=$(cat | tr -d "[:blank:]")
RULES=$(grep -o "^[^#].*" $1 | sed 's/#.*/ /' | sed '/^$/d' | tr -d "[:blank:]")
#rm final_results.txt
while read -r RULE;
do
	DST_IP=$(echo $RULE | grep "dst-ip[\.=0-9/]\+" -o)
	SRC_IP=$(echo $RULE | grep "src-ip[\.=0-9/]\+" -o)
	SRC_PORT=$(echo $RULE | grep "src-port[\.=0-9\-]\+" -o)
	DST_PORT=$(echo $RULE | grep "dst-port[\.=0-9\-]\+" -o)
	echo "$PACKET_F" | ./firewall.exe "$DST_IP"| ./firewall.exe "$SRC_IP"\
	|./firewall.exe "$SRC_IP"| ./firewall.exe "$DST_PORT">>out.txt
done <<< "$RULES"
cat out.txt | sort | uniq 

rm out*
