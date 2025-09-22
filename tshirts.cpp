#include <stdio.h>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if (cms < 38) {
        sizeName = 'S';
    } else if (cms >= 38 && cms < 42) {
        sizeName = 'M';
    } else if (cms >= 42) {
        sizeName = 'L';
    }
    return sizeName;
}

int testTshirtSize() {
    printf("\nTshirt size test\n");
    int passed = 1; // Track if all tests pass
    
    if (size(37) != 'S') {
        printf("ERROR: size(37) should be 'S' but got '%c'\n", size(37));
        passed = 0;
    }
    
    if (size(38) != 'M') {  // This will fail as 38 is not handled in the size function
        printf("ERROR: size(38) should be 'M' but got '%c'\n", size(38));
        passed = 0;
    }
    
    if (size(40) != 'M') {
        printf("ERROR: size(40) should be 'M' but got '%c'\n", size(40));
        passed = 0;
    }
    
    if (size(43) != 'L') {
        printf("ERROR: size(43) should be 'L' but got '%c'\n", size(43));
        passed = 0;
    }
    
    if (passed) {
        printf("All is well (maybe!)\n");
    } else {
        printf("FAILED: Not all T-shirt sizes are correctly assigned\n");
    }
    
    return passed;
}