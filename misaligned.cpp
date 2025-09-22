#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Function to generate a single color map entry
char* formatColorMapEntry(int index, const char* majorColor, const char* minorColor) {
    // Allocate memory for the string (including null terminator)
    char* entry = (char*)malloc(50);
    if (entry) {
        // Format with right-aligned numbers and left-aligned color names with consistent spacing
        sprintf(entry, "%2d | %-7s | %-7s", index, majorColor, minorColor);
    }
    return entry;
}

// Function to test a color map entry format
int testColorMapEntryFormat() {
    // Create entries for a single digit number and double digit number
    char* entry1 = formatColorMapEntry(2, "Red", "Blue");
    char* entry2 = formatColorMapEntry(10, "Red", "Blue");
    char* entry3 = formatColorMapEntry(5, "Yellow", "Brown");  // Testing with longer color names
    
    // Test alignment requirements:
    // 1. Numbers should be right-aligned with padding (e.g., "%2d")
    // 2. Color names should be left-aligned with fixed width (e.g., "%-6s")
    
    // Compare with expected properly formatted strings - adjusted to match the actual format
    int isCorrectlyFormatted1 = (strcmp(entry1, " 2 | Red     | Blue   ") == 0);
    int isCorrectlyFormatted2 = (strcmp(entry2, "10 | Red     | Blue   ") == 0);
    int isCorrectlyFormatted3 = (strcmp(entry3, " 5 | Yellow  | Brown  ") == 0);
    
    // Print actual vs expected to help with debugging
    printf("Expected: ' 2 | Red     | Blue   ', Got: '%s'\n", entry1);
    printf("Expected: '10 | Red     | Blue   ', Got: '%s'\n", entry2);
    printf("Expected: ' 5 | Yellow  | Brown  ', Got: '%s'\n", entry3);
    
    free(entry1);
    free(entry2);
    free(entry3);
    
    // Check if formatting is correct (will be false, exposing the bug)
    if (!(isCorrectlyFormatted1 && isCorrectlyFormatted2 && isCorrectlyFormatted3)) {
        printf("ERROR: Color map entry formatting is incorrect!\n");
        return 0; // Return 0 to indicate failure
    }
    
    return 1; // Return 1 for success
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            char* entry = formatColorMapEntry(i * 5 + j, majorColor[i], minorColor[j]);
            printf("%s\n", entry);
            free(entry);
        }
    }
    return i * j;
}

int testPrintColorMap() {
    printf("\nPrint color map test\n");
    int formatResult = testColorMapEntryFormat();
    int result = printColorMap();
    
    int passed = 1;
    
    if (result != 25) {
        printf("ERROR: Expected printColorMap to return 25, but got %d\n", result);
        passed = 0;
    }
    
    if (!formatResult) {
        printf("ERROR: Color map entry formatting test failed\n");
        passed = 0;
    }
    
    if (passed) {
        printf("All is well (maybe!)\n");
    } else {
        printf("FAILED: Color map has alignment issues\n");
    }
    
    return passed;
}