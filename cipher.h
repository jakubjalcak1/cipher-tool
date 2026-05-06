#ifndef CIPHER_H
#define CIPHER_H

#define MAX_TEXT 1024
#define MAX_KEY  64

/**
 * Encrypts/decrypts text using Caesar cipher.
 * Positive shift = encrypt, negative shift = decrypt.
 * @param text   input text
 * @param shift  number of positions to shift (can be negative)
 * @param output buffer for result
 */
void caesar(const char text[], int shift, char output[]);

/**
 * Applies ROT13 substitution to text.
 * ROT13 is its own inverse - applying it twice returns the original.
 * @param text   input text
 * @param output buffer for result
 */
void rot13(const char text[], char output[]);

/**
 * Encrypts/decrypts text using Vigenere cipher.
 * @param text    input text
 * @param key     keyword (letters only)
 * @param encrypt 1 to encrypt, 0 to decrypt
 * @param output  buffer for result
 */
void vigenere(const char text[], const char key[], int encrypt, char output[]);

/**
 * Saves text to a file. Returns 0 on success, 1 on error.
 * @param filename target file
 * @param text     content to write
 */
int save_to_file(const char filename[], const char text[]);

/**
 * Starts the interactive cipher tool menu.
 */
void run_cipher_tool(void);

#endif /* CIPHER_H */
