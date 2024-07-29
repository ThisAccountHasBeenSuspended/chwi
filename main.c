// STD C
#include <stdio.h>

// Custom
#include "ccpu.h"

// Test without struct ccpu_s
static void test() {
    unsigned char maxLvl = 0;
    unsigned char family = CCPU_FAMILY_UNKNOWN;
    if (ccpu_info(&maxLvl, &family) == 0) {
        printf("ccpu_info() could not be loaded!");
        return;
    }
    printf("CPU information loaded successfully! (0x%.2x)\n", maxLvl);

    unsigned int features[2] = { 0 };
    int _ = ccpu_features(features);
    printf("[SSE4.2 %s]\n", ccpu_has_feature(features, CCPU_FEATURE_SSE4_2) == 0 ? "unsupported" : "supported");

    char vendor[64] = { 0 };
    if (ccpu_vendor(vendor) == 0) {
        printf("ccpu_brand() could not be loaded!");
        return;
    }

    unsigned short frequencies[3] = { 0 };
    if (ccpu_frequencies(maxLvl, frequencies) == 0) {
        printf("ccpu_frequencies() could not be loaded!");
        return;
    }

    switch (family) {
    case CCPU_FAMILY_UNKNOWN:
        printf("- family:            UNKNOWN\n");
        break;
    case CCPU_FAMILY_GENUINEINTEL:
        printf("- family:            GenuineIntel\n");
        break;
    case CCPU_FAMILY_AUTHENTICAMD:
        printf("- family:            AuthenticAMD\n");
        break;
    }
    printf("- vendor:            %s\n", vendor);
    printf("- base frequency:    %hu MHz\r\n", frequencies[0]);
    printf("- maximum frequency: %hu MHz\r\n", frequencies[1]);
    printf("- bus frequency:     %hu MHz\r\n", frequencies[2]);
}

// Test with struct ccpu_s
static void test_s() {
    ccpu_s ccpu = CCPU_S_DEFAULT;
    if (ccpu_info_x(&ccpu) == 0) {
        printf("ccpu_info() could not be loaded!");
        return;
    }
    printf("CPU information loaded successfully! (0x%.2x)\n", ccpu.maxLvl);

    int _ = ccpu_features_x(&ccpu);
    printf("[SSE4.2 %s]\n", ccpu_has_feature_x(&ccpu, CCPU_FEATURE_SSE4_2) == 0 ? "unsupported" : "supported");

    if (ccpu_vendor_x(&ccpu) == 0) {
        printf("ccpu_brand() could not be loaded!");
        return;
    }

    if (ccpu_frequencies_x(&ccpu) == 0) {
        printf("ccpu_frequencies() could not be loaded!");
        return;
    }

    switch (ccpu.family) {
    case CCPU_FAMILY_UNKNOWN:
        printf("- family:            UNKNOWN\n");
        break;
    case CCPU_FAMILY_GENUINEINTEL:
        printf("- family:            GenuineIntel\n");
        break;
    case CCPU_FAMILY_AUTHENTICAMD:
        printf("- family:            AuthenticAMD\n");
        break;
    }
    printf("- vendor:            %s\n", ccpu.vendor);
    printf("- base frequency:    %hu MHz\r\n", ccpu.frequencies[0]);
    printf("- maximum frequency: %hu MHz\r\n", ccpu.frequencies[1]);
    printf("- bus frequency:     %hu MHz\r\n", ccpu.frequencies[2]);
}

int main()
{
    test();
    printf("\n===========================================\n\n");
    test_s();
    return 0;
}