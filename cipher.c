#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cipher.h"

/* ── Caesar ────────────────────────────────────────────────────────────── */

void caesar(const char text[], int shift, char output[]) {
    int len = strlen(text);
    /* normalise shift to 0-25 */
    shift = ((shift % 26) + 26) % 26;

    for (int i = 0; i < len; i++) {
        char c = text[i];
        if (isupper(c)) {
            output[i] = (char)(((c - 'A') + shift) % 26 + 'A');
        } else if (islower(c)) {
            output[i] = (char)(((c - 'a') + shift) % 26 + 'a');
        } else {
            output[i] = c;   /* keep spaces, digits, punctuation */
        }
    }
    output[len] = '\0';
}

/* ── ROT13 ──────────────────────────────────────────────────────────────── */

void rot13(const char text[], char output[]) {
    caesar(text, 13, output);
}

/* ── Vigenere ───────────────────────────────────────────────────────────── */

void vigenere(const char text[], const char key[], int encrypt, char output[]) {
    int text_len = strlen(text);
    int key_len  = strlen(key);
    int key_pos  = 0;

    for (int i = 0; i < text_len; i++) {
        char c = text[i];

        if (isalpha(c)) {
            int shift = tolower(key[key_pos % key_len]) - 'a';
            if (!encrypt) shift = 26 - shift;

            if (isupper(c)) {
                output[i] = (char)(((c - 'A') + shift) % 26 + 'A');
            } else {
                output[i] = (char)(((c - 'a') + shift) % 26 + 'a');
            }
            key_pos++;
        } else {
            output[i] = c;
        }
    }
    output[text_len] = '\0';
}

/* ── File I/O ───────────────────────────────────────────────────────────── */

int save_to_file(const char filename[], const char text[]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file '%s'\n", filename);
        return 1;
    }
    fprintf(fp, "%s\n", text);
    fclose(fp);
    return 0;
}

/* ── Helpers ────────────────────────────────────────────────────────────── */

static void print_banner(void) {
    printf("\n");
    printf("  ██████╗██╗██████╗ ██╗  ██╗███████╗██████╗ \n");
    printf(" ██╔════╝██║██╔══██╗██║  ██║██╔════╝██╔══██╗\n");
    printf(" ██║     ██║██████╔╝███████║█████╗  ██████╔╝\n");
    printf(" ██║     ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗\n");
    printf(" ╚██████╗██║██║     ██║  ██║███████╗██║  ██║\n");
    printf("  ╚═════╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
    printf("         Text Encryption Tool v1.0\n");
    printf("  ─────────────────────────────────────────\n\n");
}

static void print_menu(void) {
    printf("  [1]  Caesar cipher  (encrypt)\n");
    printf("  [2]  Caesar cipher  (decrypt)\n");
    printf("  [3]  ROT13\n");
    printf("  [4]  Vigenere cipher (encrypt)\n");
    printf("  [5]  Vigenere cipher (decrypt)\n");
    printf("  [6]  Save last result to file\n");
    printf("  [0]  Exit\n");
    printf("\n  Choose: ");
}

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ── Main interactive loop ──────────────────────────────────────────────── */

void run_cipher_tool(void) {
    char input[MAX_TEXT];
    char output[MAX_TEXT];
    char key[MAX_KEY];
    char last_result[MAX_TEXT];
    int  choice, shift;

    last_result[0] = '\0';

    print_banner();

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            flush_stdin();
            continue;
        }
        flush_stdin();

        if (choice == 0) {
            printf("\n  Goodbye!\n\n");
            break;
        }

        if (choice == 6) {
            if (last_result[0] == '\0') {
                printf("  Nothing to save yet.\n\n");
                continue;
            }
            char filename[128];
            printf("  Filename: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';

            if (save_to_file(filename, last_result) == 0) {
                printf("  Saved to '%s'\n\n", filename);
            }
            continue;
        }

        /* Get input text */
        printf("  Enter text: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        switch (choice) {
            case 1:
                printf("  Shift (1-25): ");
                scanf("%d", &shift);
                flush_stdin();
                caesar(input, shift, output);
                break;

            case 2:
                printf("  Shift (1-25): ");
                scanf("%d", &shift);
                flush_stdin();
                caesar(input, -shift, output);
                break;

            case 3:
                rot13(input, output);
                break;

            case 4:
                printf("  Key (letters only): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';
                vigenere(input, key, 1, output);
                break;

            case 5:
                printf("  Key (letters only): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';
                vigenere(input, key, 0, output);
                break;

            default:
                printf("  Invalid option.\n\n");
                continue;
        }

        printf("\n  Result: %s\n\n", output);
        strcpy(last_result, output);
    }
}
