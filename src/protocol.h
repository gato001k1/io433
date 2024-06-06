#define CAME 0
#define NICE 1
#define FAAC 2

struct HighLow {
  uint16_t high;
  uint16_t low;
};

struct Protocol {
  String name;
  uint8_t nbits;
  uint16_t high;
  HighLow one;
  HighLow zero;
  uint16_t preamble;
  uint8_t repetition;
};

/*
A protocol is defined by a few parameters passed to the constructor in the following order:
name: the name of the protocol
n_bits: the number of bits for a single key
timings_table: the timings for encoding the zero and the one
preamble, a recurring pattern at the beginning of each key
repetition: number of transmissions per key in the bruteforce
*/
static const Protocol protocols[] {
    {"CAME", 12, 250, {500, 250}, {250, 500}, 9000, 3},
    {"FAAC", 12, 330, {660, 330}, {330, 660}, 11220, 3},
    {"NICE", 12, 700, {1400, 700}, {700, 1400}, 25200, 3}
};

const uint8_t signalRepetitions = 5;
const uint16_t teslaPulseWidth = 400;
const uint16_t teslaMessageDistance = 23;
const uint8_t teslaMessageLength = 43;
const uint8_t sequence[teslaMessageLength] = {
  0x02,0xAA,0xAA,0xAA,  // Preamble of 26 bits by repeating 1010
  0x2B,                 // Sync byte
  0x2C,0xCB,0x33,0x33,0x2D,0x34,0xB5,0x2B,0x4D,0x32,0xAD,0x2C,0x56,0x59,0x96,0x66,
  0x66,0x5A,0x69,0x6A,0x56,0x9A,0x65,0x5A,0x58,0xAC,0xB3,0x2C,0xCC,0xCC,0xB4,0xD2,
  0xD4,0xAD,0x34,0xCA,0xB4,0xA0};
