# avrgeigerctr
This is an AVR-based Geiger Counter that works with the Russian-build very nice
SI-8B pancake probe. I had originally built that circuit in 2013 and also [made
a YouTube video about it](https://www.youtube.com/watch?v=VTvxW6B8epQ), but
revisited the whole thing in 2018 and re-built the entire circuit (albeit
re-using some of the components). Notably the tube current is now not exceeding the specifications
anymore (in my early design I used a 10 MOhm resistor, now it's 30 MOhms) and replaced the
feedback by a LM311 comparator. The updated schematic is also included.

It uses a Tiny13 as a SMPS controller (actually a dead simple one) with a fixed
frequency of around 5 kHz. The Tiny2313 does the counting and conversion to
RS232 (actually USB via an FTDI232).

# Schematic
The schematic is Open Hardware and the PDF of the schematic is included. It has
been created with Altium CircuitMaker and therefore is also available at
[Altium Vault](https://workspace.circuitmaker.com/Projects/Details/Johannes-Bauer/Geiger-Counter).

# License
GNU General Public License v3.
