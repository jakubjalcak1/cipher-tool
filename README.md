# Cipher Tool

A terminal-based text encryption tool written in C. Supports multiple classical ciphers with an interactive menu, and lets you save results to a file.

## Features

- **Caesar cipher** — encrypt and decrypt with a custom shift
- **ROT13** — quick letter substitution (its own inverse)
- **Vigenère cipher** — keyword-based polyalphabetic encryption and decryption
- Save the last result to a `.txt` file
- Clean interactive menu
- Non-alphabetic characters (spaces, digits, punctuation) are preserved

## Getting Started

### Requirements

- GCC compiler

### Build & Run

```bash
git clone https://github.com/jakubjalcak1/cipher-tool.git
cd cipher-tool
gcc -Wall -Wextra -o cipher main.c cipher.c
./cipher
```

## Usage

```
  [1]  Caesar cipher  (encrypt)
  [2]  Caesar cipher  (decrypt)
  [3]  ROT13
  [4]  Vigenere cipher (encrypt)
  [5]  Vigenere cipher (decrypt)
  [6]  Save last result to file
  [0]  Exit
```

### Example

```
Choose: 1
Enter text: Hello World
Shift (1-25): 3
Result: Khoor Zruog
```

## Project Structure

```
cipher-tool/
├── main.c       # Entry point
├── cipher.c     # Cipher implementations
└── cipher.h     # Function declarations and documentation
```

## Built With

- **C** — standard C99

## Author

**Jakub Jalčak** — [jakubjalcak1.github.io](https://jakubjalcak1.github.io)
