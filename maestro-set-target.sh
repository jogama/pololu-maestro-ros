#!/bin/bash

# Copied from https://www.pololu.com/docs/0J40/5.h.4

# Sends a Set Target command to a Pololu Maestro servo controller
# via its virtual serial port.
# Usage: maestro-set-target.sh DEVICE CHANNEL TARGET
# Linux example: bash maestro-set-target.sh /dev/ttyACM0 0 6000
# Mac OS X example: bash maestro-set-target.sh /dev/cu.usbmodem00234567 0 6000
# Windows example: bash maestro-set-target.sh '\\.\USBSER000' 0 6000
# Windows example: bash maestro-set-target.sh '\\.\COM6' 0 6000
# CHANNEL is the channel number
# TARGET is the target in units of quarter microseconds.
# The Maestro must be configured to be in USB Dual Port mode.

DEVICE=$1
CHANNEL=$2
TARGET=$3

byte() {
  printf "\\x$(printf "%x" $1)"
  
}

stty raw -F $DEVICE

{
  byte 0x84
    byte $CHANNEL
      byte $((TARGET & 0x7F))
        byte $((TARGET >> 7 & 0x7F))
	
} > $DEVICE
