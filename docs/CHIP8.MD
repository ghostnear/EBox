# CHIP8

## Compatibility:

### Tests:

- Timendus' CHIP8 test suite:
    - [x] 1-chip8-logo.ch8
    - [x] 2-ibm-logo.ch8
    - [x] 3-corax+.ch8
    - [x] 4-flags.ch8
        - Looks like there is a regression in the 4.1 ROM as I couldn't find anything wrong myself? And 4.0 works properly.
    - [ ] 5-quirks.ch8
        - Fails the 60hz display test, everything else works.
    - [x] 6-keypad.ch8
        - Key 0x3 specifically doesn't work for some reason in v. 4.1, probably another regression in the test ROM.
    - [ ] 7-beep.ch8
        - Audio not implemented.
    - [ ] 8-scrolling.ch8
        - NOT PLANNED.