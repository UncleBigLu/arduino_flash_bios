# Read and write BIOS firmware using arduino

This project is for rewrite my Asrock Z370M Pro4 mother board BIOS firmware. Support read entire flash chip to file and write file to flash chip.

**Notice: The flash model may be different even if the motherboard model is the same. Check your flash chip model is same as mine(mx25l12873f) or not before using this program.**

## Project environment

### hardware requirement

Arduino board: arduino mega 328p. Other arduino board should work if they support *SPIMemory* library. Simply change the port defination then everything should work.

Target flash: mx25l12873f. This project may not work on other flash chips.

### Software requirement 

Arduino library: SPIMemory

Python library: serial

## Notice

Change tty port according your port in python code.