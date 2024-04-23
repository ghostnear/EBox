# CHIP8

## Compatibility:

### Tests:

- Timendus' CHIP8 test suite:
    - [x] 1-chip8-logo.ch8
    - [x] 2-ibm-logo.ch8
    - [x] 3-corax+.ch8
    - [x] 4-flags-4.0.ch8
    - [ ] 4-flags-4.1.ch8
        - Looks like a regression in the ROM as I couldn't find anything wrong myself.
    - [ ] 5-quirks.ch8
    - [x] 6-keypad.ch8
        - Key 0x3 specifically doesn't work for some reason, probably another regression in the test ROM.
    - [ ] 7-beep.ch8
    - [ ] 8-scrolling.ch8