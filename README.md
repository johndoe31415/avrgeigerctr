# avrgeigerctr
This is an AVR-based Geiger Counter with USB counting output that works with
the Russian-build very nice SI-8B pancake probe. I had originally built that
circuit in 2013 and also [made a YouTube video about
it](https://www.youtube.com/watch?v=VTvxW6B8epQ), but revisited the whole thing
in 2018 and re-built the entire circuit (albeit re-using some of the
components). Notably the tube current is now not exceeding the specifications
anymore (in my early design I used a 10 MOhm resistor, now it's 30 MOhms) and
replaced the feedback by a LM311 comparator. The updated schematic is also
included.

It uses a Tiny13 as a SMPS controller (actually a dead simple one) with a fixed
frequency of around 5 kHz. The Tiny2313 does the counting and conversion to
RS232 (actually USB via an FTDI232).

Pictures [can be seen here](https://johndoe31415.github.io/avrgeigerctr/).

# Schematic
The schematic is Open Hardware and the PDF of the schematic is included. It has
been created with Altium CircuitMaker and therefore is also available at
[Altium Vault](https://workspace.circuitmaker.com/Projects/Details/johndoe31415/avrgeigerctr).

# Example output and usage
Here's some example output on the RS232 line using 115200 Baud 8N1:

```
T=5b48 C=77 L=64ae X=f453
T=5b92 C=78 L=6650 X=9203
T=5bae C=79 L=7dc X=95df
T=5bae C=7e L=8779 X=3185
T=5baf C=85 L=38a2 X=357e
T=5baf C=8c L=e9b2 X=9825
T=5bb0 C=92 L=818b X=1448
T=5bb1 C=99 L=32ec X=3aca
T=5bb1 C=9d L=984d X=f5d5
```

The "T" part indicates the timestamp. Time is counted in full overflows of the
16-bit TIMER1 at full frequency of 18.432 MHz. So the last line shows 0x5bb1
ticks which corresponds to about 83.5 seconds. In that time, C=9d, i.e., 157
counts have been registered (~1.8 cts/sec background). The L and X values
indicate the last TCNT1 value (free-running at maximum clock rate) at the time
of the event as well as the cumulative XORed TCNT1 value over all events.  Both
can be used to seed some TRNG source as they should be truly random. When you
hit the "?" key, you will see a help page that should be fairly self-explanatory:

```
Help:
   ?        This help page.
   1 to 9   Change output rate to 5000, 2500, 1000, 500, 250, 100, 50, 25 or 0 milliseconds.
   s        Turn clicker sound off
   S        Turn clicker sound on
   a        Do not emit messages when no change in counts occurred
   A        Always emit messages, even when no change in counts occurred
Message format:
   T=time C=counts L=last_tcnt1 X=xored_tcnt1
   Time in multiples of 4/1125th of a second (approx. 3.56 ms).
   last_tcnt1 and xored_tcnt1 give the last TCNT1 value at an event
   and the cumulative XORed TCNT1 value of all events so far. Regardless
   of timer setting, lines are only printed when event count has changed.
Current state of settings: Sound=off OnlyShowMsgOnChangedCounts=yes
```

With the a or A keys it can be chosen whether or not messages should be emitted
regardless if counts have changed or not. This can be used to disciminate cases
where the counter itself has a malfunction or it's just the tube not emitting
any more counts.

# AVR fuse configuration
ATtiny13: 9.6 MHz internal RC oscillator
```
-U lfuse:w:0x7a:m -U hfuse:w:0xff:m
```

ATtiny2313: 18.432 MHz external crystal, 14 CK + 65ms startup
```
-U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
```

# License
GNU General Public License v3.
