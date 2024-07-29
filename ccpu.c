#include "ccpu.h"

#ifdef _MSC_VER
#include <intrin.h>
#elif __GNUC__
#include <cpuid.h>
#endif // _MSC_VER

#ifdef DEBUG_CCPU
#include <stdio.h>
#endif // DEBUG_CCPU

#include <string.h>

inline static void _cpuid(int* regs, int addr) {
#ifdef _MSC_VER
    __cpuid(regs, addr);
#elif __GNUC__
    __cpuid(addr, regs[0], regs[1], regs[2], regs[3]);
#else
    __asm {
        /* Do the call. */
        mov EAX, addr;
        cpuid;
        /* Save results. */
        mov regs[0], EAX;
        mov regs[1], EBX;
        mov regs[2], ECX;
        mov regs[3], EDX;
    }
#endif // _MSC_VER
}

char ccpu_info(unsigned char* maxLvl, unsigned char* family) {
    unsigned int regs[4];
    memset(regs, 0, sizeof(regs));
    _cpuid(regs, 0x0);

    *maxLvl = regs[0];

    if (regs[1] == 0x756e6547 && regs[2] == 0x6c65746e && regs[3] == 0x49656e69) { // INTEL
        *family = CCPU_FAMILY_GENUINEINTEL;
    }
    else if (regs[1] == 0x68747541 && regs[2] == 0x444d4163 && regs[3] == 0x69746e65) { // AMD
        *family = CCPU_FAMILY_AUTHENTICAMD;
    }
    else {
#ifdef DEBUG_CCPU
        char family[32];
        memset(family, 0, sizeof(family));
        memcpy(family, &regs[1], 4);
        memcpy(family + 4, &regs[3], 4);
        memcpy(family + 8, &regs[2], 4);
        printf("ccpu_info(): Unsupported family! Found: %s (0x%.8x, 0x%.8x, 0x%.8x)\n", family, regs[1], regs[2], regs[3]);
#endif // DEBUG_CCPU
        return 0;
    }

    return 1;
}

char ccpu_features(unsigned int features[]) {
    unsigned int regs[4];
    memset(regs, 0, sizeof(regs));
    _cpuid(regs, 0x1);

    features[0] = regs[3];
    features[1] = regs[2];

    return 1;
}

char ccpu_vendor(char vendor[]) {
    unsigned int regs[4];
    memset(regs, 0, sizeof(regs));
    _cpuid(regs, 0x80000000);
    if (regs[0] < 0x80000004) {
        return 0;
    }

    // As an example, it could be something like this:
    // 12th Gen Intel(R) Core(TM) i5-12400F
    _cpuid(regs, 0x80000002);
    memcpy(vendor, regs, sizeof(regs));
    _cpuid(regs, 0x80000003);
    memcpy(vendor + 16, regs, sizeof(regs));
    _cpuid(regs, 0x80000004);
    memcpy(vendor + 32, regs, sizeof(regs));

    return 1;
}

char ccpu_frequencies(unsigned char maxLvl, unsigned short frequencies[]) {
    if (maxLvl < 0x16) {
#ifdef DEBUG_CCPU
        printf("ccpu_frequencies(): Missing 0x16\n");
#endif // DEBUG_CCPU
        return 0;
    }

    unsigned int regs[4];
    memset(regs, 0, sizeof(regs));
    _cpuid(regs, 0x16);

    frequencies[0] = regs[0]; // Base
    frequencies[1] = regs[1]; // Max
    frequencies[2] = regs[2]; // Bus

    return 1;
}