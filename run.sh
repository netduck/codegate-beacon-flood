#!/bin/bash

if [ -z $1 ]
then
	echo "[!] No parameter passed"
	echo "[*] Usgae : $0 <interface>"
	exit
fi

cd backend/c
./backend $1 &
cd ../../frontend
python3 client.py
