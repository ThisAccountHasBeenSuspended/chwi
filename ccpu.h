#ifndef ccpu_h
#define ccpu_h

typedef enum {
    CCPU_FAMILY_UNKNOWN = 0,
    CCPU_FAMILY_GENUINEINTEL = 1,
    CCPU_FAMILY_AUTHENTICAMD = 2,
} ccpufamily_e;

typedef struct {
    unsigned char maxLvl;
    ccpufamily_e family;

    char vendor[64];

    unsigned short frequencies[3];

    unsigned int features[2];
} ccpu_s;
#define CCPU_S_DEFAULT { .maxLvl = 0x00, .family = CCPU_FAMILY_UNKNOWN, .vendor = { 0 }, .frequencies = { 0 }, .features = { 0 } }

/* https://en.wikipedia.org/wiki/CPUID#EAX=1:_Processor_Info_and_Feature_Bits */
typedef enum {
    CCPU_FEATURE_FPU  = 0,
    CCPU_FEATURE_SSE3 = 32,

    CCPU_FEATURE_VME       = 1,
    CCPU_FEATURE_PCLMULQDQ = 33,

    CCPU_FEATURE_DE     = 2,
    CCPU_FEATURE_DTES64 = 34,

    CCPU_FEATURE_PSE     = 3,
    CCPU_FEATURE_MONITOR = 35,

    CCPU_FEATURE_TSC    = 4,
    CCPU_FEATURE_DS_CPL = 36,

    CCPU_FEATURE_MSR = 5,
    CCPU_FEATURE_VMX = 37,

    CCPU_FEATURE_PAE = 6,
    CCPU_FEATURE_SMX = 38,

    CCPU_FEATURE_MCE = 7,
    CCPU_FEATURE_EST = 39,

    CCPU_FEATURE_CX8 = 8,
    CCPU_FEATURE_TM2 = 40,

    CCPU_FEATURE_APIC  = 9,
    CCPU_FEATURE_SSSE3 = 41,

    CCPU_FEATURE_MTRR_RESERVED    = 10,
    CCPU_FEATURE_CNXT_ID          = 42,

    CCPU_FEATURE_SEP  = 11,
    CCPU_FEATURE_SDBG = 43,

    CCPU_FEATURE_MTRR = 12,
    CCPU_FEATURE_FMA  = 44,

    CCPU_FEATURE_PGE  = 13,
    CCPU_FEATURE_CX16 = 45,

    CCPU_FEATURE_MCA = 14,
    CCPU_FEATURE_XTPR = 46,

    CCPU_FEATURE_CMOV = 15,
    CCPU_FEATURE_PDCM = 47,

    CCPU_FEATURE_PAT       = 16,
    CCPU_FEATURE_RESERVED1 = 48,

    CCPU_FEATURE_PSE_36 = 17,
    CCPU_FEATURE_PCID   = 49,

    CCPU_FEATURE_PSN = 18,
    CCPU_FEATURE_DCA = 50,

    CCPU_FEATURE_CLFSH  = 19,
    CCPU_FEATURE_SSE4_1 = 51,

    CCPU_FEATURE_NX     = 20,
    CCPU_FEATURE_SSE4_2 = 52,

    CCPU_FEATURE_DS     = 21,
    CCPU_FEATURE_X2APIC = 53,

    CCPU_FEATURE_ACPI  = 22,
    CCPU_FEATURE_MOVBE = 54,

    CCPU_FEATURE_MMX    = 23,
    CCPU_FEATURE_POPCNT = 55,

    CCPU_FEATURE_FXSR         = 24,
    CCPU_FEATURE_TSC_DEADLINE = 56,

    CCPU_FEATURE_SSE    = 25,
    CCPU_FEATURE_AES_NI = 57,

    CCPU_FEATURE_SSE2  = 26,
    CCPU_FEATURE_XSAVE = 58,

    CCPU_FEATURE_SS      = 27,
    CCPU_FEATURE_OSXSAVE = 59,

    CCPU_FEATURE_HTT = 28,
    CCPU_FEATURE_AVX = 60,

    CCPU_FEATURE_TM   = 29,
    CCPU_FEATURE_F16C = 61,

    CCPU_FEATURE_IA64  = 30,
    CCPU_FEATURE_RDRND = 62,

    CCPU_FEATURE_PBE        = 31,
    CCPU_FEATURE_HYPERVISOR = 63,
} ccpufeatures_e;

/*
* @return char : true (1) if the function was successfully called otherwhise false (0) will be returned.
*/
extern char ccpu_info(unsigned char* maxLvl, unsigned char* family);
inline char ccpu_info_x(ccpu_s* ccpu) { return ccpu_info(&(*ccpu).maxLvl, &(*ccpu).family); }

/*
* @param features : An array of unsigned int with 2 elements.
* @return char : true (1) if the function was successfully called otherwhise false (0) will be returned.
*/
extern char ccpu_features(unsigned int features[]);
inline char ccpu_features_x(ccpu_s* ccpu) { return ccpu_features((*ccpu).features); }

/*
* TODO
*/
inline char ccpu_has_feature(unsigned int features[], int feature) { return (features[feature > 31] & (1 << (feature % 32))) > 0; }
inline char ccpu_has_feature_x(ccpu_s* ccpu, int feature) { return ccpu_has_feature((*ccpu).features, feature); }

/*
* @param vendor : An array of char with 64 elements.
* @return char : true (1) if the function was successfully called otherwhise false (0) will be returned.
*/
extern char ccpu_vendor(char vendor[]);
inline char ccpu_vendor_x(ccpu_s* ccpu) { return ccpu_vendor((*ccpu).vendor); }

/*
* @param frequencies : An array of unsigned short with 3 elements.
* @return char : true (1) if the function was successfully called otherwhise false (0) will be returned.
*/
extern char ccpu_frequencies(unsigned char maxLvl, unsigned short frequencies[]);
inline char ccpu_frequencies_x(ccpu_s* ccpu) { return ccpu_frequencies((*ccpu).maxLvl, (*ccpu).frequencies); }

#endif // ccpu_h