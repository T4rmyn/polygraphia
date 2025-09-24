# polygraphia
*"Rg gh, Oehgr?"*

## About
**polygraphia** is a terminal program that supports simple cryptographic encryption and decryption using [classical cipher](https://en.wikipedia.org/wiki/Classical_cipher) methods. Classical ciphers are ciphers which are rendered obsolete due to their simplicity and and are easily solvable by modern computational technology.

However, these simple ciphers offer excellent use as a recreational way to encode secrets for various activies such as a puzzle, an ARG, or an escape room. Just please don't use these to actually secure anything important.

## Implemented Ciphers
Currently supported ciphers included in this program:
- Monoalphabetic Substitution
    - [Atbash](https://en.wikipedia.org/wiki/Atbash)
    - [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher)
- Polyalphabetic Subtstitution
    - [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)
    - [Beaufort cipher](https://en.wikipedia.org/wiki/Beaufort_cipher)

## Planned Ciphers
- Transposition
    - [Rail fence cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher)
- ... and more.

## Build Instructions
This projects utilize CMake for building, below are the instructions (make sure to have CMake installed first).
1. `mkdir src/build`
2. `cd src/build`
3. `cmake ..`
4. `make`
5. To run, do `./polygraphia [ARGS]` on UNIX systems, and `polygraphia.exe [ARGS]` on Windows systems.

## Usage
1. Caesar cipher: `polygraphia caesar (--text <argument>) (--key <argument>) [--mode (<encrypt> | <decrypt>)]`
2. Atbash: `polygraphia atbash (--text <argument>) [--mode (<encrypt> | <decrypt>)]`
3. Vigenère cipher: `polygraphia vigenere (--text <argument>) (--key <argument>) [--mode (<encrypt> | <decrypt>)]`
4. Beaufort cipher: `polygraphia beaufort (--text <argument>) (--key <argument>)`

(A more comprehensive help system is going to be implemented later)
