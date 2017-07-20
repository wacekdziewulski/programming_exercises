#include <stdio.h>
#include <limits.h>
#include <malloc.h>

static short bmhSearchSanityCheck(const char* haystack, const char* needle) {
    if (!needle || !haystack) {
        return -1;
    }
    return 0;
}

/* Contract: needle and haystack are not null */
static int bmhSearchImpl(const char* haystack, int haystackLength, const char* needle, int needleLength) {
    if (needleLength == 0 || haystackLength == 0 || needleLength > haystackLength) {
        return -1;
    }
}

/* Contract: Haystack and Needle should be null-terminated */
int bmhSearch(const char* haystack, const char* needle) {
    if (bmhSearchSanityCheck(haystack, needle)) {
        return -1;
    }

    int needleLength = strlen(needle);
    int haystackLength = strlen(needle);

    return bmhSearchImpl(haystack, haystackLength, needle, needleLength);
}

int bmhSearch(const char* haystack, int haystackLength, const char* needle, int needleLength) {
    if (bmhSearchSanityCheck(haystack, needle)) {
        return -1;
    }

    return bmhSearchImpl(haystack, haystackLength, needle, needleLength);
}
