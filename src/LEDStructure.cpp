#include "LEDStructure.h"


/*

ASCII DIAGRAM

                              22                                            23                                            24
                       __--‾‾   ‾‾--__                               __--‾‾   ‾‾--__                               __--‾‾   ‾‾--__
                __34‾‾                 ‾‾35__                 __36‾‾                 ‾‾37__                 __38‾‾                 ‾‾39__
         __--‾‾                               ‾‾--__   __--‾‾                               ‾‾--__   __--‾‾                               ‾‾--__
       18                                            19                                            2O                                            21
       │ ‾‾--__                               __--‾‾ │ ‾‾--__                               __--‾‾ │ ‾‾--__                               __--‾‾ │
       │        ‾‾28__                 __29‾‾        │        ‾‾30__                 __31‾‾        │        ‾‾32__                 __33‾‾        │
       │               ‾‾--__   __--‾‾               │               ‾‾--__   __--‾‾               │               ‾‾--__   __--‾‾               │
       │                      15                     │                      16                     │                      17                     │
       21                     │                      23                     │                      25                     │                      27
       │                      │                      │                      │                      │                      │                      │
       │                      │                      │                      │                      │                      │                      │ 
       │                      │                      │                      24                     │                      │                      │
       11                     22                     12                     │                      13                     26                     14
         ‾‾--__               │               __--‾‾   ‾‾--__               │               __--‾‾   ‾‾--__               │               __--‾‾
                ‾‾15__        │        __16‾‾                 ‾‾17__        │        __18‾‾                 ‾‾19__        │        __20‾‾
                       ‾‾--__ │ __--‾‾                               ‾‾--__ │ __--‾‾                               ‾‾--__ │ __--‾‾
                              08                                            09                                            1O
                              │ ‾‾--__                               __--‾‾ │ ‾‾--__                               __--‾‾ │
                              │        ‾‾11__                 __12‾‾        │        ‾‾13__                 __14‾‾        │
                              │               ‾‾--__   __--‾‾               │               ‾‾--__   __--‾‾               │
                              │                      06                     │                      07                     │
                              06                     │                      08                     │                      10
                              │                      │                      │                      │                      │
                              │                      │                      │                      │                      │
                              │                      │                      │                      │                      │
                              03                     07                     04                     09                     05
                                ‾‾--__               │               __--‾‾   ‾‾--__               │               __--‾‾
                                       ‾‾02__        │        __03‾‾                 ‾‾04__        │        __05‾‾
                                              ‾‾--__ │ __--‾‾                               ‾‾--__ │ __--‾‾
                                                     01                                            02
                                                       ‾‾--__                               __--‾‾
                                                              ‾‾00__                 __01‾‾
                                                                     ‾‾--__   __--‾‾
                                                                            00

There are 25 Nodes in this graph labeled [0-24]
There are 40 Edges in this graph labeled [0-39]
Each edge has 14 LEDs they will be indexed from 0 to 13 in the following directions ↖ ↑ ↗

Examples:
Edge 00: edge[0].leds[0] will be the LED closest to nodes[0]
         edge[0].leds[NUM_LEDS_PER_EDGE-1] will be the LED closest to nodes[1]

Edge 01: edge[1].leds[0] will be the LED closest to nodes[0]
         edge[1].leds[NUM_LEDS_PER_EDGE-1] will be the LED closest to nodes[2]

Edge 06: edge[6].leds[0] will be the LED closest to nodes[3]
         edge[6].leds[NUM_LEDS_PER_EDGE-1] will be the LED closest to nodes[8]

*/

CRGB leds_1[NUM_LEDS_1];
CRGB leds_2[NUM_LEDS_2];

Node nodes[NUM_NODES];
Edge edges[NUM_EDGES];

// Initialize the datastructure mapping LED physical addresses to Edges and Nodes.
//
//
// Correct direction &leds_[(14 * number)  + x];
// Wrong direction &leds_[(14 * number+1) - (x + 1)];

void LedStructure::initialize() {
  FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds_1, NUM_LEDS_1);
  FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds_2, NUM_LEDS_2);

  for (int x = 0; x < NUM_LEDS_PER_EDGE; x++) {
    edges[0].leds[x] = &leds_1[(14 * 17) - (x + 1)];
    edges[1].leds[x] = &leds_2[(14 * 0)  + x]; // yes "14 * 0 == 0" but I love me some consistentcy. But now only this line has a comment, way to go.
    edges[2].leds[x] = &leds_1[(14 * 13) - (x + 1)];
    edges[3].leds[x] = &leds_1[(14 * 16) - (x + 1)];
    edges[4].leds[x] = &leds_2[(14 * 7) - (x + 1)];
    edges[5].leds[x] = &leds_2[(14 * 1)  + x];
    edges[6].leds[x] = &leds_1[(14 * 12) - (x + 1)];
    edges[7].leds[x] = &leds_1[(14 * 13) + x];
    edges[8].leds[x] = &leds_2[(14 * 6) - (x + 1)];
    edges[9].leds[x] = &leds_2[(14 * 7) + x];
    edges[10].leds[x] = &leds_2[(14 * 2) + x];
    edges[11].leds[x] = &leds_1[(14 * 11) - (x + 1)];
    edges[12].leds[x] = &leds_1[(14 * 14) + x];
    edges[13].leds[x] = &leds_1[(14 * 8) - (x + 1)];
    edges[14].leds[x] = &leds_2[(14 * 8) + x];
    edges[15].leds[x] = &leds_2[(14 * 23) - (x + 1)];
    edges[16].leds[x] = &leds_1[(14 * 10) - (x + 1)];
    edges[17].leds[x] = &leds_1[(14 * 8) + x];
    edges[18].leds[x] = &leds_2[(14 * 5) - (x + 1)];
    edges[19].leds[x] = &leds_2[(14 * 3) + x];
    edges[20].leds[x] = &leds_2[(14 * 9) + x];
    edges[21].leds[x] = &leds_2[(14 * 22) - (x + 1)];
    edges[22].leds[x] = &leds_1[(14 * 0) + x];
    edges[23].leds[x] = &leds_1[(14 * 4) - (x + 1)];
    edges[24].leds[x] = &leds_1[(14 * 7) - (x + 1)];
    edges[25].leds[x] = &leds_2[(14 * 16) + x];
    edges[26].leds[x] = &leds_2[(14 * 16) - (x + 1)];
    edges[27].leds[x] = &leds_2[(14 * 10) + x];
    edges[28].leds[x] = &leds_1[(14 * 1) + x];
    edges[29].leds[x] = &leds_1[(14 * 2) + x];
    edges[30].leds[x] = &leds_1[(14 * 5) - (x + 1)];
    edges[31].leds[x] = &leds_1[(14 * 5) + x];
    edges[32].leds[x] = &leds_2[(14 * 14) - (x + 1)];
    edges[33].leds[x] = &leds_2[(14 * 14) + x];
    edges[34].leds[x] = &leds_2[(14 * 21) - (x + 1)];
    edges[35].leds[x] = &leds_2[(14 * 19) + x];
    edges[36].leds[x] = &leds_2[(14 * 19) - (x + 1)];
    edges[37].leds[x] = &leds_2[(14 * 17) + x];
    edges[38].leds[x] = &leds_2[(14 * 13) - (x + 1)];
    edges[39].leds[x] = &leds_2[(14 * 11) + x];
  }

  // Initialize nodes
  nodes[0].ne = &edges[1];
  nodes[0].nw = &edges[0];
  nodes[1].n = &edges[7];
  nodes[1].ne = &edges[3];
  nodes[1].se = &edges[0];
  nodes[1].nw = &edges[2];
  nodes[2].n = &edges[9];
  nodes[2].ne = &edges[5];
  nodes[2].sw = &edges[1];
  nodes[2].nw = &edges[4];
  nodes[3].n = &edges[6];
  nodes[3].se = &edges[2];
  nodes[4].n = &edges[8];
  nodes[4].se = &edges[4];
  nodes[4].sw = &edges[3];
  nodes[5].n = &edges[10];
  nodes[5].sw = &edges[5];
  nodes[6].ne = &edges[12];
  nodes[6].s = &edges[7];
  nodes[6].nw = &edges[11];
  nodes[7].ne = &edges[14];
  nodes[7].s = &edges[9];
  nodes[7].nw = &edges[13];
  nodes[8].n = &edges[22];
  nodes[8].ne = &edges[16];
  nodes[8].se = &edges[11];
  nodes[8].s = &edges[6];
  nodes[8].nw = &edges[15];
  nodes[9].n = &edges[24];
  nodes[9].ne = &edges[18];
  nodes[9].se = &edges[13];
  nodes[9].s = &edges[8];
  nodes[9].sw = &edges[12];
  nodes[9].nw = &edges[17];
  nodes[10].n = &edges[26];
  nodes[10].ne = &edges[20];
  nodes[10].s = &edges[10];
  nodes[10].sw = &edges[14];
  nodes[10].nw = &edges[19];
  nodes[11].n = &edges[21];
  nodes[11].se = &edges[15];
  nodes[12].n = &edges[23];
  nodes[12].se = &edges[17];
  nodes[12].sw = &edges[16];
  nodes[13].n = &edges[25];
  nodes[13].se = &edges[19];
  nodes[13].sw = &edges[18];
  nodes[14].n = &edges[27];
  nodes[14].sw = &edges[20];
  nodes[15].ne = &edges[29];
  nodes[15].s = &edges[22];
  nodes[15].nw = &edges[28];
  nodes[16].ne = &edges[31];
  nodes[16].s = &edges[24];
  nodes[16].nw = &edges[30];
  nodes[17].ne = &edges[33];
  nodes[17].s = &edges[26];
  nodes[17].nw = &edges[32];
  nodes[18].ne = &edges[34];
  nodes[18].se = &edges[28];
  nodes[18].s = &edges[21];
  nodes[19].ne = &edges[36];
  nodes[19].se = &edges[30];
  nodes[19].s = &edges[23];
  nodes[19].sw = &edges[29];
  nodes[19].nw = &edges[35];
  nodes[20].ne = &edges[38];
  nodes[20].se = &edges[32];
  nodes[20].s = &edges[25];
  nodes[20].sw = &edges[31];
  nodes[20].nw = &edges[37];
  nodes[21].s = &edges[27];
  nodes[21].sw = &edges[33];
  nodes[21].nw = &edges[39];
  nodes[22].se = &edges[35];
  nodes[22].sw = &edges[34];
  nodes[23].se = &edges[37];
  nodes[23].sw = &edges[36];
  nodes[24].se = &edges[39];
  nodes[24].sw = &edges[38];
}

