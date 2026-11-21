#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

/* Design A: Plain Structure containing all three fields */
struct packet_struct {
    enum kind type;
    float celsius;
    int percent;
    char status[8];
};

/* Design B: Tagged Union */
struct packet_union {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

int main(void) {
    printf("Size Comparison on 64-bit GCC:\n");
    printf("sizeof(struct packet_struct) = %zu bytes\n", sizeof(struct packet_struct));
    printf("sizeof(struct packet_union)  = %zu bytes\n", sizeof(struct packet_union));

    /* Task 3.4: Misuse Experiment */
    struct packet_union pkt;
    pkt.type = TEMPERATURE;
    pkt.value.celsius = 31.5f;

    printf("\n--- Misuse Experiment ---\n");
    printf("Stored temperature (float): %.1f\n", pkt.value.celsius);
    printf("Read humidity (int) without checking tag: %d (0x%08X)\n",
           pkt.value.percent, (unsigned int)pkt.value.percent);
    return 0;
}
