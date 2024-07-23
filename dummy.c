// system_LPC17xx path: "/Applications/ARM/Startup/NXP/LPC17xx/system_LPC17xx.c"

// Presentation link: https://rpubs.com/karthik_14R/1204014
#include "LPC17xx.h"

#define DOT_DURATION 200   // Duration of a dot in milliseconds
#define DASH_DURATION 600  // Duration of a dash in milliseconds
#define SYMBOL_GAP 200     // Gap between symbols in milliseconds
#define CHAR_GAP 600       // Gap between characters in milliseconds

// Morse code mapping (A-Z and 0-9)
const char* morse_code[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",  // A-J
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",    // K-T
    "..-", "...-", ".--", "-..-", "-.--", "--..",                         // U-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."  // 0-9
};

// Function to initialize GPIO for LED
void GPIO_Init() {
		LPC_PINCON->PINSEL4 = 0x000000;  //Configure the PORT2 Pins as GPIO;
    LPC_GPIO2->FIODIR |= (1 << 25);  // Set P2.0 as output (assuming LED is connected to P2.0)
}

// Function to toggle LED
void LED_On() {
    LPC_GPIO2->FIOSET = (1 << 25);
}

void LED_Off() {
    LPC_GPIO2->FIOCLR = (1 << 25);
}

void delay_ms(unsigned int ms)
{
    unsigned int i,j;

    for(i=0;i<ms;i++)
        for(j=0;j<2000;j++);
}

// Function to give LED output by iterating over each character in the string:
void output_morse_code(const char* code) {
    while (*code) {
        if (*code == '.') {
            LED_On();
            delay_ms(DOT_DURATION);
        } else if (*code == '-') {
            LED_On();
            delay_ms(DASH_DURATION);
        }
        LED_Off();
        delay_ms(SYMBOL_GAP);
        code++;
    }
}

// Function to get Morse code for a character from ALPHABET
const char* get_morse_code(char c) {
    if (c >= 'A' && c <= 'Z') {
        return morse_code[c - 'A'];
    } else if (c >= '0' && c <= '9') {
        return morse_code[c - '0' + 26];
    }
    return "";
}

int main() {
    // Declare variables
    char input[] = "ABC";  // Example input
    char* p;

    // Initialize system and GPIO after variable declarations
    SystemInit();
    GPIO_Init();

    // Use declared variables in the code
    for (p = input; *p; p++) {
        if (*p == ' ') {
            delay_ms(CHAR_GAP);  // Gap between words
        } else {
            const char* code = get_morse_code(*p);
            output_morse_code(code);
            delay_ms(CHAR_GAP);  // Gap between characters
        }
    }

    // Infinite loop to keep the program running
    while (1);
    return 0;  // Unreachable code in embedded systems, but needed for completeness
}
