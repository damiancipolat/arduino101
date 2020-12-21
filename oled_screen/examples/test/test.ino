
 //****************************************************************************
 //
 // sketch displaying an animated wire frame representation of a 
 // 3d model on a mini oled screen ( SSDI1306 ) via i2c.
 // hidden surface removal is used; non-visible polgons are not displayed.
 // code is made for arduino nano - 2kb(!) ram & 30kb sram - just for curiousity
 // purpose; is it possible to display 3d graphics and if so how fast 
 // will it run.
 // 
 // 2018 / version 0.02
 // arjan westerdiep / www.drububu.com 
 //
 // generate an arduino sketch with your own 3D model at drububu.com
 //
 //****************************************************************************

 #include <Wire.h>
 #include <avr/pgmspace.h>

 //****************************************************************************
 // slave address
 // find your device at http://playground.arduino.cc/Main/I2cScanner
 //****************************************************************************

 #define   SLAVE                   0x3C

 //****************************************************************************
 // 
 //****************************************************************************

 #define   OBJECT_SIZE             140   

 #define   ROTATE_X_AXIS           true
 #define   ROTATE_Y_AXIS           true
 #define   ROTATE_Z_AXIS           true
 #define   SHOW_FRAMES_PER_SECOND  true
 #define   PROFILING               false

 //****************************************************************************
 // set to true if backside of object is displayed instead of front.
 //****************************************************************************

 #define  FLIP_NORMAL              true 

 //****************************************************************************
 // 
 //****************************************************************************

 #define WIDTH                     128
 #define HEIGHT                    64
 #define ROWS                      8
 #define OFFSET_HORIZONTAL         64
 #define OFFSET_VERTICAL           32

 //****************************************************************************
 // 
 //****************************************************************************

 #if OBJECT_SIZE >= ( WIDTH - 2 ) || OBJECT_SIZE >= ( HEIGHT - 2 ) 
  #define isMeshInsideScreen       false
 #else 
  #define isMeshInsideScreen       true
 #endif

 //****************************************************************************
 // 
 //****************************************************************************


 #if ROTATE_X_AXIS 
  byte _frameXAxis = 0;
 #endif

 #if ROTATE_Y_AXIS 
  byte _frameYAxis = 0;
 #endif

 #if ROTATE_Z_AXIS 
  byte _frameZAxis = 0;
 #endif

 //****************************************************************************
 // 
 //****************************************************************************

 byte          _bitmapData[ WIDTH * ( HEIGHT >> 3 ) ];
 byte          _lookupMinimumcolumn[ ROWS ];
 byte          _lookupMaximumcolumn[ ROWS ];
 byte          _minimumRow = 0;
 byte          _maximumRow = ROWS - 1;
 word          _lookupOledRefresh[ ROWS ];

 #if PROFILING
  unsigned long _timePreprocessing = 0;
  unsigned long _timeScanConvert   = 0;
  unsigned long _timeRendering     = 0;
 #endif
 
 //****************************************************************************
 // frames per second code
 //****************************************************************************

 #if SHOW_FRAMES_PER_SECOND

  #define       FPS_ROW_POSITION 7

  word          _totalOfFrameRates = 0.0;
  byte          _numberOfFrames = 0;
  unsigned long _time = millis();

  //***************************************************************************
  // 
  //***************************************************************************

  const static byte _lookupFps[ 65 ] PROGMEM = {
   14, 17, 17, 14,  0, // 0
    0, 17, 31, 16,  0, // 1
   29, 21, 21, 23,  0, // 2  
   21, 21, 21, 31,  0, // 3  
   12, 10,  9, 31,  0, // 4  
   23, 21, 21, 29,  0, // 5  
   31, 21, 21, 29,  0, // 6
    1, 25,  5,  3,  0, // 7
   31, 21, 21, 31,  0, // 8
   23, 21, 21, 31,  0, // 9
   31,  5,  5,  5,  0, // F
   31,  5,  5,  7,  0, // P
   23, 21, 21, 29,  0  // S
  };

 #endif
 //*******************************************************************************
 // sine & cosine data 
 //*******************************************************************************

 const static word _lookupSineCosine[ 256 ] PROGMEM = {
  0x7FFE, 0x82FD, 0x85FD, 0x88FD, 0x8BFD, 0x8EFD, 0x91FC, 0x94FC, 0x97FB, 0x9AFA, 
  0x9DFA, 0xA0F9, 0xA3F8, 0xA6F7, 0xA9F6, 0xACF5, 0xAFF4, 0xB2F3, 0xB5F1, 0xB8F0, 
  0xBAEF, 0xBDED, 0xC0EB, 0xC2EA, 0xC5E8, 0xC8E6, 0xCAE5, 0xCDE3, 0xCFE1, 0xD1DF, 
  0xD4DD, 0xD6DA, 0xD8D8, 0xDAD6, 0xDDD4, 0xDFD1, 0xE1CF, 0xE3CD, 0xE5CA, 0xE6C8, 
  0xE8C5, 0xEAC2, 0xEBC0, 0xEDBD, 0xEFBA, 0xF0B8, 0xF1B5, 0xF3B2, 0xF4AF, 0xF5AC, 
  0xF6A9, 0xF7A6, 0xF8A3, 0xF9A0, 0xFA9D, 0xFA9A, 0xFB97, 0xFC94, 0xFC91, 0xFD8E, 
  0xFD8B, 0xFD88, 0xFD85, 0xFD82, 0xFD7F, 0xFD7B, 0xFD78, 0xFD75, 0xFD72, 0xFD6F, 
  0xFC6C, 0xFC69, 0xFB66, 0xFA63, 0xFA60, 0xF95D, 0xF85A, 0xF757, 0xF654, 0xF551, 
  0xF44E, 0xF34B, 0xF148, 0xF045, 0xEF43, 0xED40, 0xEB3D, 0xEA3B, 0xE838, 0xE635, 
  0xE533, 0xE330, 0xE12E, 0xDF2C, 0xDD29, 0xDA27, 0xD825, 0xD623, 0xD420, 0xD11E, 
  0xCF1C, 0xCD1A, 0xCA18, 0xC817, 0xC515, 0xC213, 0xC012, 0xBD10, 0xBA0E, 0xB80D, 
  0xB50C, 0xB20A, 0xAF09, 0xAC08, 0xA907, 0xA606, 0xA305, 0xA004, 0x9D03, 0x9A03, 
  0x9702, 0x9401, 0x9101, 0x8E00, 0x8B00, 0x8800, 0x8500, 0x8200, 0x7F00, 0x7B00, 
  0x7800, 0x7500, 0x7200, 0x6F00, 0x6C01, 0x6901, 0x6602, 0x6303, 0x6003, 0x5D04, 
  0x5A05, 0x5706, 0x5407, 0x5108, 0x4E09, 0x4B0A, 0x480C, 0x450D, 0x430E, 0x4010, 
  0x3D12, 0x3B13, 0x3815, 0x3517, 0x3318, 0x301A, 0x2E1C, 0x2C1E, 0x2920, 0x2723, 
  0x2525, 0x2327, 0x2029, 0x1E2C, 0x1C2E, 0x1A30, 0x1833, 0x1735, 0x1538, 0x133B, 
  0x123D, 0x1040, 0x0E43, 0x0D45, 0x0C48, 0x0A4B, 0x094E, 0x0851, 0x0754, 0x0657, 
  0x055A, 0x045D, 0x0360, 0x0363, 0x0266, 0x0169, 0x016C, 0x006F, 0x0072, 0x0075, 
  0x0078, 0x007B, 0x007E, 0x0082, 0x0085, 0x0088, 0x008B, 0x008E, 0x0191, 0x0194, 
  0x0297, 0x039A, 0x039D, 0x04A0, 0x05A3, 0x06A6, 0x07A9, 0x08AC, 0x09AF, 0x0AB2, 
  0x0CB5, 0x0DB8, 0x0EBA, 0x10BD, 0x12C0, 0x13C2, 0x15C5, 0x17C8, 0x18CA, 0x1ACD, 
  0x1CCF, 0x1ED1, 0x20D4, 0x23D6, 0x25D8, 0x27DA, 0x29DD, 0x2CDF, 0x2EE1, 0x30E3, 
  0x33E5, 0x35E6, 0x38E8, 0x3BEA, 0x3DEB, 0x40ED, 0x43EF, 0x45F0, 0x48F1, 0x4BF3, 
  0x4EF4, 0x51F5, 0x54F6, 0x57F7, 0x5AF8, 0x5DF9, 0x60FA, 0x63FA, 0x66FB, 0x69FC, 
  0x6CFC, 0x6FFD, 0x72FD, 0x75FD, 0x78FD, 0x7BFD 
 };

 //****************************************************************************
 //
 //****************************************************************************

 #define  NUMBER_OF_VERTEX_INDICES           660
 #define  NUMBER_OF_POLYGON_INDICES          350

 //****************************************************************************
 // lookup entries unique segments ( = bitfield ( word ( 2 bytes ) ) ) 
 // maximum 97 unique segments per chunck
 //****************************************************************************

 #define  LOOKUP_ENTRIES_UNIQUE_SEGMENTS  7

 //****************************************************************************
 // lookup entries transformed vertices ( = bitfield ( word ( 2 bytes ) ) ) 
 // maximum 95 unique vertices per chunck
 //****************************************************************************

 #define  LOOKUP_ENTRIES_TRANSFORMED_VERTICES  6

 word     _lookupTransformedVerticesBitfield[ LOOKUP_ENTRIES_TRANSFORMED_VERTICES ];
 char     _lookupTransformedVertices[ 190 ];

 //****************************************************************************
 // lookup vertex ( & normal ) data
 //****************************************************************************

 const static word _lookupVertices[ 660 ] PROGMEM = {
  0x0033, 0x7F7F, 0x0000, 0x1B76, 0x007F, 0x2375, 0x007F, 0x2171, 0x007F, 0x1E6E, 
  0x007F, 0x196C, 0x007F, 0x146B, 0x007F, 0x116C, 0x007F, 0x0E6D, 0x007F, 0x0C6E, 
  0x007F, 0x0870, 0x007F, 0x0674, 0x007F, 0x047A, 0x007F, 0x047D, 0x007F, 0x0480, 
  0x007F, 0x0486, 0x007F, 0x058C, 0x007F, 0x0890, 0x007F, 0x0B92, 0x007F, 0x0F94, 
  0x007F, 0x1495, 0x007F, 0x1695, 0x007F, 0x1B94, 0x007F, 0x1E91, 0x007F, 0x218E, 
  0x007F, 0x238C, 0x007F, 0x2487, 0x007F, 0x2583, 0x007F, 0x2580, 0x007F, 0x247A, 
  0x007F, 0x1C78, 0x007F, 0x1C7C, 0x007F, 0x1D81, 0x007F, 0x1C86, 0x007F, 0x1B89, 
  0x007F, 0x198C, 0x007F, 0x168E, 0x007F, 0x128E, 0x007F, 0x0F8C, 0x007F, 0x0E8B, 
  0x007F, 0x0D88, 0x007F, 0x0C84, 0x007F, 0x0C80, 0x007F, 0x0C7C, 0x007F, 0x0D78, 
  0x007F, 0x0E76, 0x007F, 0x0F74, 0x007F, 0x1272, 0x007F, 0x1572, 0x007F, 0x1773, 
  0x007F, 0x1974, 0x007F, 0x000B, 0x7F7F, 0x0000, 0x476C, 0x007F, 0x406C, 0x007F, 
  0x4089, 0x007F, 0x326C, 0x007F, 0x296C, 0x007F, 0x2994, 0x007F, 0x3094, 0x007F, 
  0x3077, 0x007F, 0x3D94, 0x007F, 0x4794, 0x007F, 0x000D, 0x7F7F, 0x0000, 0x4F6C, 
  0x007F, 0x4F72, 0x007F, 0x5872, 0x007F, 0x588E, 0x007F, 0x4F8E, 0x007F, 0x4F94, 
  0x007F, 0x6994, 0x007F, 0x698E, 0x007F, 0x608E, 0x007F, 0x6072, 0x007F, 0x6972, 
  0x007F, 0x696C, 0x007F, 0x0021, 0x7F7F, 0x0000, 0x8778, 0x007F, 0x8794, 0x007F, 
  0x8E94, 0x007F, 0x8E78, 0x007F, 0x8E76, 0x007F, 0x8E74, 0x007F, 0x8D71, 0x007F, 
  0x8A6F, 0x007F, 0x876D, 0x007F, 0x836C, 0x007F, 0x806B, 0x007F, 0x7D6C, 0x007F, 
  0x7A6C, 0x007F, 0x766E, 0x007F, 0x7371, 0x007F, 0x7273, 0x007F, 0x7176, 0x007F, 
  0x7079, 0x007F, 0x7094, 0x007F, 0x7894, 0x007F, 0x7879, 0x007F, 0x7877, 0x007F, 
  0x7975, 0x007F, 0x7A73, 0x007F, 0x7C72, 0x007F, 0x7E72, 0x007F, 0x8072, 0x007F, 
  0x8272, 0x007F, 0x8373, 0x007F, 0x8574, 0x007F, 0x8675, 0x007F, 0x8677, 0x007F, 
  0x002E, 0x7F7F, 0x0000, 0x9E6E, 0x007F, 0x9F75, 0x007F, 0xA273, 0x007F, 0xA573, 
  0x007F, 0xA772, 0x007F, 0xAA72, 0x007F, 0xAA8E, 0x007F, 0xA68E, 0x007F, 0xA38D, 
  0x007F, 0xA08D, 0x007F, 0x9E8B, 0x007F, 0x9C88, 0x007F, 0x9C86, 0x007F, 0x9B83, 
  0x007F, 0x9B80, 0x007F, 0x9B7E, 0x007F, 0x9C7C, 0x007F, 0x9C7A, 0x007F, 0x9D78, 
  0x007F, 0x9B6F, 0x007F, 0x9970, 0x007F, 0x9773, 0x007F, 0x9575, 0x007F, 0x9478, 
  0x007F, 0x937B, 0x007F, 0x937E, 0x007F, 0x9381, 0x007F, 0x9383, 0x007F, 0x9385, 
  0x007F, 0x9488, 0x007F, 0x9489, 0x007F, 0x958B, 0x007F, 0x968E, 0x007F, 0x988F, 
  0x007F, 0x9991, 0x007F, 0x9C92, 0x007F, 0xA094, 0x007F, 0xA394, 0x007F, 0xA694, 
  0x007F, 0xB294, 0x007F, 0xB26C, 0x007F, 0xA86C, 0x007F, 0xA56C, 0x007F, 0xA26D, 
  0x007F, 0xA06D, 0x007F, 0x002E, 0x7F7F, 0x0000, 0xC38C, 0x007F, 0xC28B, 0x007F, 
  0xBD92, 0x007F, 0xC093, 0x007F, 0xC294, 0x007F, 0xC594, 0x007F, 0xC894, 0x007F, 
  0xD594, 0x007F, 0xD56C, 0x007F, 0xCD6C, 0x007F, 0xCD7D, 0x007F, 0xCB7D, 0x007F, 
  0xCA7D, 0x007F, 0xC87C, 0x007F, 0xC67B, 0x007F, 0xC579, 0x007F, 0xC06C, 0x007F, 
  0xB66C, 0x007F, 0xBE7B, 0x007F, 0xBE7C, 0x007F, 0xC07D, 0x007F, 0xC17E, 0x007F, 
  0xC27F, 0x007F, 0xC080, 0x007F, 0xBE81, 0x007F, 0xBC82, 0x007F, 0xBB84, 0x007F, 
  0xBA85, 0x007F, 0xBA87, 0x007F, 0xB989, 0x007F, 0xB98B, 0x007F, 0xBA8C, 0x007F, 
  0xBA8E, 0x007F, 0xBC90, 0x007F, 0xC288, 0x007F, 0xC286, 0x007F, 0xC385, 0x007F, 
  0xC484, 0x007F, 0xC683, 0x007F, 0xC883, 0x007F, 0xCD83, 0x007F, 0xCD8E, 0x007F, 
  0xC88E, 0x007F, 0xC78E, 0x007F, 0xC58D, 0x007F, 0x000C, 0x7F7F, 0x0000, 0xF094, 
  0x007F, 0xFC6C, 0x007F, 0xF07A, 0x007F, 0xEB8D, 0x007F, 0xE57A, 0x007F, 0xF46C, 
  0x007F, 0xF274, 0x007F, 0xE474, 0x007F, 0xE16C, 0x007F, 0xD96C, 0x007F, 0xE594, 
  0x007F, 0x0005, 0x7F7F, 0x00FE, 0x2D86, 0x007F, 0x2D7A, 0x007F, 0x527A, 0x007F, 
  0x5286, 0x007F, 0x005F, 0x7F7F, 0x00FE, 0xD3B7, 0x007F, 0xCCA3, 0x007F, 0xD79E, 
  0x007F, 0xE095, 0x007F, 0xE68B, 0x007F, 0xE87E, 0x007F, 0xE672, 0x007F, 0xE068, 
  0x007F, 0xD75F, 0x007F, 0xCC5A, 0x007F, 0xC458, 0x007F, 0xB958, 0x007F, 0xAF5A, 
  0x007F, 0xA460, 0x007F, 0x9B68, 0x007F, 0x9373, 0x007F, 0x8B7F, 0x007F, 0x938C, 
  0x007F, 0x9C96, 0x007F, 0xA69E, 0x007F, 0xB1A3, 0x007F, 0xBFA5, 0x007F, 0xBFBA, 
  0x007F, 0xB5B9, 0x007F, 0xA2B4, 0x007F, 0x99AF, 0x007F, 0x91A8, 0x007F, 0x89A0, 
  0x007F, 0x8297, 0x007F, 0x7F93, 0x007F, 0x7B97, 0x007F, 0x74A0, 0x007F, 0x6CA8, 
  0x007F, 0x64AF, 0x007F, 0x5BB4, 0x007F, 0x48B9, 0x007F, 0x3EBA, 0x007F, 0x2AB7, 
  0x007F, 0x1AAE, 0x007F, 0x0CA2, 0x007F, 0x0491, 0x007F, 0x007E, 0x007F, 0x046C, 
  0x007F, 0x0C5B, 0x007F, 0x194F, 0x007F, 0x2A46, 0x007F, 0x3643, 0x007F, 0x4543, 
  0x007F, 0x5245, 0x007F, 0x5B49, 0x007F, 0x5960, 0x007F, 0x4E5A, 0x007F, 0x4758, 
  0x007F, 0x3E58, 0x007F, 0x315A, 0x007F, 0x265F, 0x007F, 0x1D68, 0x007F, 0x1772, 
  0x007F, 0x157E, 0x007F, 0x178B, 0x007F, 0x1D95, 0x007F, 0x269E, 0x007F, 0x31A3, 
  0x007F, 0x3EA5, 0x007F, 0x4CA3, 0x007F, 0x579E, 0x007F, 0x6196, 0x007F, 0x6A8C, 
  0x007F, 0x727F, 0x007F, 0x6A73, 0x007F, 0x6268, 0x007F, 0x644E, 0x007F, 0x6C55, 
  0x007F, 0x745D, 0x007F, 0x7862, 0x007F, 0x7B67, 0x007F, 0x7F6C, 0x007F, 0x8267, 
  0x007F, 0x8562, 0x007F, 0x895D, 0x007F, 0x9155, 0x007F, 0x984E, 0x007F, 0xA049, 
  0x007F, 0xA946, 0x007F, 0xB244, 0x007F, 0xBF43, 0x007F, 0xD346, 0x007F, 0xE44F, 
  0x007F, 0xF15B, 0x007F, 0xF96C, 0x007F, 0xFD7E, 0x007F, 0xF991, 0x007F, 0xF1A2, 
  0x007F, 0xE3AE, 0x007F, 0x000D, 0x7F7F, 0x00FE, 0xAB86, 0x007F, 0xAB7A, 0x007F, 
  0xB67A, 0x007F, 0xB66F, 0x007F, 0xC26F, 0x007F, 0xC27A, 0x007F, 0xCD7A, 0x007F, 
  0xCD86, 0x007F, 0xC286, 0x007F, 0xC292, 0x007F, 0xB692, 0x007F, 0xB686, 0x007F 
 };

 //****************************************************************************
 // polygon data
 //****************************************************************************

 const static word _lookupPolygons[ 350 ] PROGMEM = {
  0x3301, 0x0034, 0x0001, 0x0202, 0x0303, 0x0404, 0x0505, 0x0606, 0x0707, 0x0808, 
  0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 0x0D0D, 0x0E0E, 0x0F0F, 0x1010, 0x1111, 0x1212, 
  0x1313, 0x1414, 0x1515, 0x1616, 0x1717, 0x1818, 0x1919, 0x1A1A, 0x1B1B, 0x1C1C, 
  0x1D1D, 0x0002, 0x1E01, 0x1F1E, 0x201F, 0x2120, 0x2221, 0x2322, 0x2423, 0x2524, 
  0x2625, 0x2726, 0x2827, 0x2928, 0x2A29, 0x2B2A, 0x2C2B, 0x2D2C, 0x2E2D, 0x2F2E, 
  0x302F, 0x3130, 0x3231, 0x3332, 0x0A01, 0x000A, 0x0101, 0x0202, 0x0303, 0x0404, 
  0x0505, 0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0C01, 0x000C, 0x0101, 0x0202, 
  0x0303, 0x0404, 0x0505, 0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 
  0x2001, 0x0020, 0x0101, 0x0202, 0x0303, 0x0404, 0x0505, 0x0606, 0x0707, 0x0808, 
  0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 0x0D0D, 0x0E0E, 0x0F0F, 0x1010, 0x1111, 0x1212, 
  0x1313, 0x1414, 0x1515, 0x1616, 0x1717, 0x1818, 0x1919, 0x1A1A, 0x1B1B, 0x1C1C, 
  0x1D1D, 0x1E1E, 0x1F1F, 0x2020, 0x2E01, 0x002F, 0x0001, 0x0202, 0x0303, 0x0404, 
  0x0505, 0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 0x0D0D, 0x0E0E, 
  0x0F0F, 0x1010, 0x1111, 0x1212, 0x1313, 0x0002, 0x1401, 0x1514, 0x1615, 0x1716, 
  0x1817, 0x1918, 0x1A19, 0x1B1A, 0x1C1B, 0x1D1C, 0x1E1D, 0x1F1E, 0x201F, 0x2120, 
  0x2221, 0x2322, 0x2423, 0x2524, 0x2625, 0x2726, 0x2827, 0x2928, 0x2A29, 0x2B2A, 
  0x2C2B, 0x2D2C, 0x2E2D, 0x2F01, 0x0031, 0x0101, 0x0002, 0x0303, 0x0404, 0x0505, 
  0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 0x0D0D, 0x0E0E, 0x0F0F, 
  0x1010, 0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616, 0x0017, 0x0017, 0x1817, 
  0x1918, 0x1A19, 0x1B1A, 0x1C1B, 0x1D1C, 0x1E1D, 0x1F1E, 0x201F, 0x2120, 0x2221, 
  0x2322, 0x0003, 0x2402, 0x2523, 0x2624, 0x2725, 0x2826, 0x2927, 0x2A28, 0x2B29, 
  0x2C2A, 0x2D2B, 0x2E2C, 0x2F2D, 0x0C01, 0x000D, 0x0101, 0x0002, 0x0303, 0x0404, 
  0x0505, 0x0003, 0x0602, 0x0706, 0x0807, 0x0908, 0x0A09, 0x0B0A, 0x0C0B, 0x0401, 
  0x0004, 0x0101, 0x0202, 0x0303, 0x0404, 0x6101, 0x0063, 0x0001, 0x0202, 0x0303, 
  0x0404, 0x0505, 0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0B0B, 0x0C0C, 0x0D0D, 
  0x0E0E, 0x0F0F, 0x1010, 0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616, 0x0002, 
  0x1701, 0x1817, 0x1918, 0x1A19, 0x1B1A, 0x1C1B, 0x1D1C, 0x1E1D, 0x1F1E, 0x201F, 
  0x2120, 0x2221, 0x2322, 0x2423, 0x2524, 0x2625, 0x2726, 0x2827, 0x2928, 0x2A29, 
  0x2B2A, 0x2C2B, 0x2D2C, 0x2E2D, 0x2F2E, 0x302F, 0x3130, 0x3231, 0x0032, 0x3433, 
  0x3534, 0x3635, 0x3736, 0x3836, 0x3937, 0x3A38, 0x3B39, 0x3C3A, 0x3D3B, 0x3E3C, 
  0x3F3D, 0x403E, 0x413F, 0x4240, 0x4341, 0x4442, 0x4543, 0x4644, 0x4745, 0x4846, 
  0x4947, 0x0033, 0x4A32, 0x4B48, 0x4C49, 0x4D4A, 0x4E4B, 0x4F4C, 0x504D, 0x514E, 
  0x524F, 0x5350, 0x5451, 0x5552, 0x5653, 0x5754, 0x5855, 0x5956, 0x5A57, 0x5B58, 
  0x5C59, 0x5D5A, 0x5E5B, 0x5F5C, 0x605D, 0x615E, 0x0C01, 0x000C, 0x0101, 0x0202, 
  0x0303, 0x0404, 0x0505, 0x0606, 0x0707, 0x0808, 0x0909, 0x0A0A, 0x0B0B, 0x0C0C 
   
 };


 //****************************************************************************
 //
 //****************************************************************************

 void initialize(){
   
  Wire.begin(); 
  TWBR = 12;
  while( !Serial ); 
    
  delay( 50 ); 
  
  Wire.beginTransmission( SLAVE ); 
  Wire.write( 0x00 );
  Wire.write( 0xAE ); // set display Off
  Wire.write( 0xD5 ); // set display clock divide ratio/oscillator frequency
  Wire.write( 0x80 );
  Wire.write( 0xA8 ); // set multiplex ratio
  Wire.write( 0x3F );
  Wire.write( 0xD3 ); // set display offset
  Wire.write( 0x00 );
  Wire.write( 0x40 ); // set display start line
  Wire.write( 0x8D ); // set charge pump
  Wire.write( 0x14 ); // VCC generated by internal DC/DC circuit
  Wire.write( 0xA1 ); // set segment re-map 
  Wire.write( 0xC0 ); // 
  Wire.write( 0xC8 ); // 
  Wire.write( 0x12 );
  Wire.write( 0x81 ); // set contrast control
  Wire.write( 0x88 ); // 0 ... 255
  Wire.write( 0xD9 ); // set pre-changed period
  Wire.write( 0xF1 );
  Wire.write( 0xDB ); // set VCOMH Deselected level
  Wire.write( 0x40 );
  Wire.write( 0xA4 ); // set entire display on/off
  Wire.write( 0xA6 ); // set normal display 
  Wire.write( 0x20 ); // set memory address mode
  Wire.write( 0x00 ); // horizontal
  Wire.write( 0xAF ); // set display on
  Wire.endTransmission(); 
 }

 //****************************************************************************
 //
 //****************************************************************************

 void clearScreen() {
  int  a, entries;
  byte lookup[ 16 ] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

  setOledPosition( 0, 0 );

  entries = ( WIDTH * ( HEIGHT >> 3 ) ) >> 4;

  for( a = 0; a < entries; a += 1 ){
   Wire.beginTransmission( SLAVE ); 
   Wire.write( 0x40 ); 
   Wire.write( &lookup[ 0 ], 16 );
   Wire.endTransmission();
  }
  
  memset( _bitmapData, 0, sizeof( _bitmapData ) );
 }
     
 //****************************************************************************
 //
 //****************************************************************************
     
 void setup() {
  byte row;

  Serial.begin( 115200 );
 
  initialize(); 

  for( row = 0; row < ROWS; row += 1 ) {
   _lookupMinimumcolumn[ row ] = WIDTH - 1;
   _lookupMaximumcolumn[ row ] =         0;
   _lookupOledRefresh  [ row ] =         0;
  }

  Wire.setClock( 400000L );

  clearScreen();
 }

 //****************************************************************************
 //
 //****************************************************************************

 void loop() {

  render();

  #if SHOW_FRAMES_PER_SECOND
   drawFps();
  #endif   
 
//  delay( 1000 );
//  clearScreen();

#if PROFILING
  Serial.println( F(" - profiling -----------------------") );
  Serial.print( F(" time preprocessing : ") );
  Serial.println( _timePreprocessing, DEC );

  Serial.print( F(" time scanconversion: ") );
  Serial.println( _timeScanConvert, DEC );

  Serial.print( F(" time rendering     : ") );
  Serial.println( _timeRendering, DEC );
  Serial.print( F("
") );
#endif
  
 }

 //****************************************************************************
 //
 //****************************************************************************

 void setOledPosition( byte row,  byte collum ) {

  byte oledSetPosition[ 7 ] = {
   0x00,   // [ 0 ] command stream
   0x22,   // [ 1 ] ver
   row,    // [ 2 ] vertical start
   7,      // [ 3 ] vertical end
   0x21,   // [ 4 ] hor
   collum, // [ 5 ] start collum 
   0x7F    // [ 6 ] end collum
  };

  Wire.beginTransmission( SLAVE ); 
  Wire.write( &oledSetPosition[ 0 ], 7 ); 
  Wire.endTransmission();
 }
     
  
 //****************************************************************************
 // 
 //****************************************************************************

 void render() {
  bool  isVisible;
  word  i0, i1, indexLookupVertices, indexLookupPolygons, vertex,
        segmentLookup[ LOOKUP_ENTRIES_UNIQUE_SEGMENTS ];
  byte  a, b, row, rowStart, rowEnd, width, offset, column, vertexIndex,
        polygon, spanHeight, spanWidth, rowData, minimumRow, maximumRow,
        indexNormal, numberOfSegments, numberOfVertices, numberOfUniqueVertices,
        numberOfPolygons, lookupMinimumcolumn[ ROWS ],
        lookupMaximumcolumn[ ROWS ], *pBitmapData;
  int   xs, ys, xe, ye, x0, y0, x1, y1, x, y, z, tmp, entries, deltaX, deltaY,
        bitmapDataAdres;
  char  *pTransformedVertex;
  word  bitfield, lookupOledRefresh[ ROWS ];
  const word *pLookupSineCosine, *pLookupVertices, *pLookupPolygons;
  byte  oledSetPosition[ 6 ] = {
   0x22,   // [ 0 ] ver
   0,      // [ 1 ] vertical start
   7,      // [ 2 ] vertical end
   0x21,   // [ 3 ] hor
   0,      // [ 4 ] start collum 
   0x7F    // [ 5 ] end collum
  };          


  #if PROFILING
   unsigned long tt;
  #endif 
  
  //***************************************************************************
  // 
  //***************************************************************************

  #if ROTATE_X_AXIS
   int  sinXAxis, cosXAxis;
  #endif

  #if ROTATE_Y_AXIS
   int  sinYAxis, cosYAxis;
  #endif

  #if ROTATE_Z_AXIS
   int sinZAxis, cosZAxis;
  #endif

  //***************************************************************************
  // 
  //***************************************************************************

  memset( lookupMinimumcolumn, WIDTH - 1, sizeof( lookupMinimumcolumn ) );
  memset( lookupMaximumcolumn,         0, sizeof( lookupMaximumcolumn ) ); 
  memset( lookupOledRefresh  ,         0, sizeof( lookupOledRefresh   ) );

  minimumRow          = ROWS - 1;
  maximumRow          = 0;
  indexLookupVertices = 0;
  indexLookupPolygons = 0;
  pTransformedVertex  = &_lookupTransformedVertices[ 0 ];
  pLookupVertices     = &_lookupVertices[ 0 ];
  pLookupPolygons     = &_lookupPolygons[ 0 ];
  pBitmapData         = &_bitmapData[ 0 ];

  //***************************************************************************
  // initialize rotation variables
  //***************************************************************************

  pLookupSineCosine = &_lookupSineCosine[ 0 ];

  #if ROTATE_X_AXIS
   i0       = pgm_read_word( pLookupSineCosine + _frameXAxis );
   sinXAxis = ( ( i0 >> 8 ) & 255 ) - 127;
   cosXAxis = (   i0        & 255 ) - 127;
  #endif

  #if ROTATE_Y_AXIS
   i0       = pgm_read_word( pLookupSineCosine + ( 255 - _frameYAxis ) );
   sinYAxis = ( ( i0 >> 8 ) & 255 ) - 127;
   cosYAxis = (   i0        & 255 ) - 127;
  #endif

  #if ROTATE_Z_AXIS
   i0       = pgm_read_word( pLookupSineCosine + _frameZAxis );
   sinZAxis = ( ( i0 >> 8 ) & 255 ) - 127;
   cosZAxis = (   i0        & 255 ) - 127;
  #endif

  //***************************************************************************
  // 
  //***************************************************************************

  do { 
       
   numberOfUniqueVertices  = ( byte )( pgm_read_word( pLookupVertices + indexLookupVertices ) & 255 );

   //**************************************************************************
   // number of transformed vertices per chunk is equals to 
   // numberOfUniqueVertices. number of bitfields never exceeds
   // numberOfUniqueVertices / 16.
   //**************************************************************************

   a = ( numberOfUniqueVertices >> 4 ) + 1 - !( numberOfUniqueVertices % 16 );
   memset( _lookupTransformedVerticesBitfield, 0, a << 1 );        
       
   //**************************************************************************
   // number of polygons per chunk
   // number of unique segments indices per chunk
   //**************************************************************************

   i0               = pgm_read_word( pLookupPolygons + indexLookupPolygons );
   numberOfPolygons = ( byte )( i0 & 255 );
   b                = ( byte )( ( i0 >> 8 ) & 255 );
   a                = ( b >> 4 ) + 1 - !( b % 16 );
       
   memset( segmentLookup, 0, a << 1 );

   //**************************************************************************
   // 
   //**************************************************************************
      
   indexLookupVertices += 1;
   indexLookupPolygons += 1;

   //**************************************************************************
   //
   // loop polygons 
   //
   // the arduino nano has 2kb ram.
   // the 3D model data is stored in sram ( 30kb ) and retrieved in
   // chunks. per chunk a couple of polygons are drawn.
   //
   //**************************************************************************

   for( polygon = 0; polygon < numberOfPolygons; polygon += 1 ) {

    i0                   = pgm_read_word( pLookupPolygons + indexLookupPolygons );
    numberOfVertices     = i0 & 255;
    indexLookupPolygons += 1;
    isVisible            = true;

    //*************************************************************************
    // 
    // preproces polygon; transform polygon normal & vertices
    //
    //*************************************************************************

    #if PROFILING
     tt = micros();
    #endif

    for( vertex = 0; vertex < numberOfVertices + 1; vertex += 1 ) {

     //************************************************************************
     // get vertex index
     //************************************************************************

     if( vertex != 0 ) { 
      vertexIndex = pgm_read_word( pLookupPolygons + indexLookupPolygons + vertex - 1 ) & 255;
     } else { 
      vertexIndex = ( i0 >> 8 ) & 255;
     }

     i1 = 1 << ( vertexIndex % 16 );

     //************************************************************************
     // check if verter ( or polygon normal ) is transformed previously
     // if alreay calculated do not re-calculate transformation
     //************************************************************************

     if( !( _lookupTransformedVerticesBitfield[ vertexIndex >> 4 ] & i1 ) ) {

      //***********************************************************************
      // set bit ( vertex is processed )
      //***********************************************************************

      _lookupTransformedVerticesBitfield[ vertexIndex >> 4 ] |= i1;

      //***********************************************************************
      // transform/rotate
      // fixed point math
      //***********************************************************************

      tmp = indexLookupVertices + ( vertexIndex << 1 );
         
      i0  = pgm_read_word( pLookupVertices + tmp    );
      i1  = pgm_read_word( pLookupVertices + tmp + 1 );

      x   = ( char )( ( ( i0 >> 8 ) & 255 ) - 127 ); 
      y   = ( char )(   ( i0        & 255 ) - 127 ); 
      z   = ( char )(   ( i1        & 255 ) - 127 ); 
 
      #if ROTATE_X_AXIS 
       tmp  = y;
       y    = (   y * cosXAxis -   z * sinXAxis ) >> 7;
       z    = ( tmp * sinXAxis +   z * cosXAxis ) >> 7; 
      #endif

      #if ROTATE_Y_AXIS 
       tmp  = x;
       x    = ( z * sinYAxis +   x * cosYAxis ) >> 7;
       z    = ( z * cosYAxis - tmp * sinYAxis ) >> 7;   
      #endif

      #if ROTATE_Z_AXIS 
       tmp  = x;
       x    = (   x * cosZAxis -   y * sinZAxis ) >> 7;
       y    = ( tmp * sinZAxis +   y * cosZAxis ) >> 7;  
      #endif

      //***********************************************************************
      // if position is vertex data use vertical position to set 
      // minimum & maximum row.
      //***********************************************************************

      if( vertex != 0 ) {

       x = ( WIDTH  >> 1 ) - ( ( x * OBJECT_SIZE ) >> 8 ) - 64;
       y = ( HEIGHT >> 1 ) - ( ( y * OBJECT_SIZE ) >> 8 );

       //**********************************************************************
       // horizontal correction ( screen is 0 ... WIDTH )
       // width = 128, char maximum is 127
       // correction is undone during drawing
       //**********************************************************************
          
       *( pTransformedVertex + ( vertexIndex << 1 )     ) = ( char )max( -117, min( x, 127 ) );
       *( pTransformedVertex + ( vertexIndex << 1 ) + 1 ) = ( char )max( -127, min( y, 127 ) );

       row        = max( 0, min( ROWS - 1, y >> 3 ) );
       minimumRow = min( row, minimumRow );
       maximumRow = max( row, maximumRow );

       x = max( 0, min( *( pTransformedVertex + ( vertexIndex << 1 ) ) + 64, WIDTH - 1 ) );
           
       if( x < lookupMinimumcolumn[ row ] ) { lookupMinimumcolumn[ row ] = x; }
       if( x > lookupMaximumcolumn[ row ] ) { lookupMaximumcolumn[ row ] = x; }
          
      } else {
       *( pTransformedVertex + ( vertexIndex << 1 ) ) = z;
      }
     } 

     //************************************************************************
     // if position is polygon normal check sign z position ( stored in
     // [ 0 ] ) for visibility; hidden surface removal.
     //************************************************************************
 
     if( vertex == 0 && ( *( pTransformedVertex + ( vertexIndex << 1 ) ) <= 0 ) == FLIP_NORMAL ) {
      isVisible = false;
      break;
     } 
    } // end loop polygon vertices

    #if PROFILING
     _timePreprocessing += micros() - tt;
    #endif

    //*************************************************************************
    //
    // 
    // scanconvert polygon if visible
    //
    //
    //*************************************************************************

    if( isVisible ) {

     #if PROFILING
      tt = micros();
     #endif

     //************************************************************************
     // scan convert segments polygons
     //************************************************************************
         
     for( vertex = 0; vertex < numberOfVertices ; vertex += 1 ) {
 
      //***********************************************************************
      // start position becomes previous end 
      //***********************************************************************
 
      i0 = pgm_read_word( pLookupPolygons + indexLookupPolygons + vertex );

      //***********************************************************************
      // check if segment is already drawn
      // if segment index == 0 no need to draw segment.
      // segment == 0 is used for poly lists to hide the segment which
      // closes the polygon which doesn''t like nice on the screen.
      //***********************************************************************

      row = ( i0 >> 8 ) & 255;
 
      if( row == 0 ) {
       continue;
      }

      xs = 1 << ( ( row - 1 ) % 16 );
      xe =        ( row - 1 ) >> 4  ; 

      //***********************************************************************
      // check if segment is drawn previously; avoid multiple draws 
      // of the same polygon segment
      //***********************************************************************

      if( !( segmentLookup[ xe ] & xs ) ) { 

       //**********************************************************************
       // set bitfield bit; do not proces segment a next time
       //**********************************************************************
     
       segmentLookup[ xe ] |= xs;

       //**********************************************************************
       // init start & end position segment
       //**********************************************************************

       i0 = ( i0 & 255 ) << 1;
       x0 = *( pTransformedVertex + i0     ) + 64;
       y0 = *( pTransformedVertex + i0 + 1 );

       i0 = ( pgm_read_word( pLookupPolygons + indexLookupPolygons + ( ( vertex + 1 ) % numberOfVertices ) ) & 255 ) << 1;
       x1 = *( pTransformedVertex + i0     ) + 64;
       y1 = *( pTransformedVertex + i0 + 1 );

       //**********************************************************************
       //
       //**********************************************************************

       deltaX = x1 - x0;
       deltaY = y1 - y0;

       //**********************************************************************
       //
       //**********************************************************************

       #if !isMeshInsideScreen
        if( ( deltaX < 0 && x1 < WIDTH && x0 >= 0 ) || ( deltaX >= 0  && x0 < WIDTH && x1 >= 0 ) ) {
         if( ( deltaY < 0 && y1 < HEIGHT && y0 >= 0 ) || ( deltaY >= 0  && y0 < HEIGHT && y1 >= 0 ) ) {
       #endif

       //**********************************************************************
       //
       // delta y line greater delta x line; draw scanlines vertical 
       // per byte ( 0 ... 255 )
       //
       //  .....+............  scanline 0
       //  .....|+...........  scanline 1
       //  .....||...........  scanline 2
       //  .....+|...........  scanline 3
       //  ......+...........  scanline 4
       //   
       //**********************************************************************

       if( abs( deltaY ) >= abs( deltaX ) ) {

        entries   = abs( deltaX );   
        deltaY    = ( ( y1 - y0 ) << 8 ) / ( entries == 0 ? 1 : entries );
        y0      <<= 8;
        ys        = ( y0 + 128 ) >> 8;

        for( a = 0; a <= entries ; a += 1 ) { 

         ye = x0 == x1 ? y1 : ( ( y0 + deltaY ) + 128 ) / 256;
 
         #if !isMeshInsideScreen
          if( x0 >= 0 && x0 < WIDTH ) {
         #endif

          spanHeight = max( 1, abs( ys - ye ) + ( x0 == x1 ? 1 : 0 ) );
          y          = ys - ( ys <= ye ? 0 : ( spanHeight - 1 ) );

          //*******************************************************************
          // check if scanline horizontal start & end position is in screen
          //*******************************************************************

          #if !isMeshInsideScreen
           if( y < HEIGHT && ( y + spanHeight ) >= 0 ) {
          #endif

           spanHeight      = y + spanHeight;  
           y               = max( 0, y );  
           spanHeight      = min( spanHeight - y, HEIGHT - y );
               
           rowStart        = max( 0, min(   y                    >> 3, ROWS - 1 ) );
           rowEnd          = max( 0, min( ( y + spanHeight - 1 ) >> 3, ROWS - 1 ) );
           bitmapDataAdres = ( rowStart * WIDTH ) + x0;

           for( row = rowStart; row <= rowEnd; row += 1, bitmapDataAdres += WIDTH ) {

            i0      = row == rowStart ? y % 8: 0; 
            i1      = min( min( spanHeight, ( y + spanHeight ) - ( row * 8 ) ), 8 - i0 ); 
            rowData = ( ( 1 << i1 ) - 1 ) << i0;
                
            *( pBitmapData + bitmapDataAdres ) |= rowData;

            if( x0 < lookupMinimumcolumn[ row ] ) { lookupMinimumcolumn[ row ] = x0; }    
            if( x0 > lookupMaximumcolumn[ row ] ) { lookupMaximumcolumn[ row ] = x0; }    
 
            lookupOledRefresh[ row ] |= 1 << ( x0 >> 3 );
           } 

         #if !isMeshInsideScreen
           } // end check vertical interval
          } // end check horizontal minimum & maximum
         #endif 

         //********************************************************************
         //
         //********************************************************************

         ys  = ye;
         x0 += ( x1 < x0 ) ? -1 : 1;
         y0 += deltaY;

         //********************************************************************
         //
         //********************************************************************

         #if !isMeshInsideScreen

          if( ( deltaY >= 0 && y >= ( HEIGHT - 1 ) ) || ( deltaY < 0 && y <= 0 ) ) {
           break;
          }

         #endif

        } // end loop entries
       } // end check delta y

       //**********************************************************************
       //
       // delta x line greater delta y line; draw scanlines horizontal
       //
       //  .....+------+......  scanline 0
       //  ..........+------+.  scanline 1
       //
       //**********************************************************************
   
       else  { 

        entries   = abs( deltaY );   
        deltaX    = ( ( ( x1 - x0 ) << 8 ) / ( entries == 0 ? 1 : entries ) );
        x0      <<= 8;
        xs        = ( x0 + 128 ) >> 8;

        //*********************************************************************
        // loop vertical
        //*********************************************************************

        for( a = 0; a <= entries ; a += 1 ) { 
 
         xe = y0 == y1 ? x1 : ( ( x0 + deltaX ) + 128 ) / 256;

         //********************************************************************
         // check if scanline vertical position is in screen
         //********************************************************************

         #if !isMeshInsideScreen
          if( y0 >= 0 && y0 < HEIGHT ) {
         #endif

          spanWidth = max( 1, abs( xs - xe ) + ( y0 == y1 ? 1 : 0 ) );
          x         = xs - ( xs <= xe ? 0 : ( spanWidth - 1 ) );

          //*******************************************************************
          // check if scanline horizontal start & end position is in screen
          //*******************************************************************

          #if !isMeshInsideScreen
           if( x >= 0 && x < WIDTH && ( x + spanWidth ) >= 0 ) {
          #endif

           spanWidth       = x + spanWidth;  
           x               = max( 0, x );  
           spanWidth       = min( spanWidth - x, WIDTH - x );
       
           row             = y0 >> 3;
           bitmapDataAdres = ( row * WIDTH ) + x;
           rowData         = 1 << ( y0 % 8);

           if( ( rowData & 129 ) != 0 ) { 
            if(   x                   < lookupMinimumcolumn[ row ] ) { lookupMinimumcolumn[ row ] = x                ; }    
            if( ( x + spanWidth - 1 ) > lookupMaximumcolumn[ row ] ) { lookupMaximumcolumn[ row ] = x + spanWidth - 1; }    
           }
 
           //******************************************************************
           // loop vertical
           //******************************************************************
  
           for( b = 0; b < spanWidth; b += 1, x += 1 ) {
            *( pBitmapData + bitmapDataAdres + b ) |= rowData;
            lookupOledRefresh[ row ] |= 1 << ( x >> 3 );
           }

         #if !isMeshInsideScreen
           } 
          }
         #endif 

         //*******************************************************************
         //
         //*******************************************************************

         xs  = xe;
         y0 += ( y1 < y0 ) ? -1 : 1;
         x0 += deltaX;

         //********************************************************************
         //
         //********************************************************************

         #if !isMeshInsideScreen

          if( ( deltaX >= 0 && x >= ( WIDTH - 1 ) ) || ( deltaX < 0 && x <= 0 ) ) {
           break;
          }

         #endif

        } // end loop entries
       } // end check delta x
   
       #if !isMeshInsideScreen
         }
        }
       #endif

      } // end is segment already drawn check
     } // end loop vertices

     #if PROFILING
      _timeScanConvert += micros() - tt;
     #endif
     
    } // end check is polygon visible

    //*************************************************************************
    // update indices
    //*************************************************************************

    indexLookupPolygons += numberOfVertices;
    
    } // end loop polygons

    indexLookupVertices += numberOfUniqueVertices << 1;

  } while( indexLookupPolygons < NUMBER_OF_POLYGON_INDICES );

  //***************************************************************************
  //
  // draw & remove data per row
  // render content bitmapdata to oled screen.
  //
  //  min +------+ max // previous drawn row
  //    min +--+ max   // current row
  //
  // previous drawn row is still visible on screen.
  // previous minimum is compared againt current row minimum. the lowest
  // value is used to remove previous drawn row ( and draw ) current row.
  // same applies for maximum.
  //
  // draw from top row to bottom row; fps is drawn at bottom row
  // bottom row is drawn last so time between fps draw and 3d object
  // draw is minimumal ( less flickering )
  //
  //***************************************************************************

  #if PROFILING
   tt = micros();
  #endif
  
  a = max( _maximumRow, maximumRow ) ; 

  for( row = min( _minimumRow, minimumRow ) ; row <= a ; row += 1 ) {

   xs = min( _lookupMinimumcolumn[ row ], lookupMinimumcolumn[ row ] )    ;
   xe = max( _lookupMaximumcolumn[ row ], lookupMaximumcolumn[ row ] ) + 1;
   
   if( xs < xe ) {

    //*************************************************************************
    // display minimum and maximum area needed for oled screen removal.
    //*************************************************************************

    // *( pBitmapData + ( row * WIDTH ) + lookupMinimumcolumn[ row ] ) |= 255;
    // *( pBitmapData + ( row * WIDTH ) + lookupMaximumcolumn[ row ] ) |= 255;

    oledSetPosition[ 1 ] = row; 
    oledSetPosition[ 2 ] = row;
    oledSetPosition[ 4 ] = xs ;

    Wire.beginTransmission( SLAVE ); 
    Wire.write( 0x00 );
    Wire.write( &oledSetPosition[ 0 ], 6 ); 
    Wire.endTransmission();

    column   = xs;
    width    = 8 - ( column & 7 ); 
    bitfield = _lookupOledRefresh[ row ] | lookupOledRefresh[ row ];
    i1       = row * WIDTH;

    do { //********************************************************************
         // draw span
         //********************************************************************

         i0 = bitfield >> ( column >> 3 );
 
         if( i0 & 1 ) {

          //*******************************************************************
          // check lsb if oled position needs to be set
          //*******************************************************************

          if( ( bitfield & 1 ) == 0 ) {
           oledSetPosition[ 4 ] = column ;
           Wire.beginTransmission( SLAVE ); 
           Wire.write( 0x00 );
           Wire.write( &oledSetPosition[ 3 ], 3 ); 
           Wire.endTransmission();
          }

          //*******************************************************************
          // send data in packages of 8, 16 or 24 
          // ( 32 is one too many for 32 bytes since 0x40 is send aswell )
          //*******************************************************************

          switch( i0 & 7 ) {
           case 7:
            spanWidth = 16;
            break;
           case 3:
            spanWidth = 8;
            break;
           default:
            spanWidth = 0;
            break;
          };

          Wire.beginTransmission( SLAVE ); 
          Wire.write( 0x40 ); 
          Wire.write( ( pBitmapData + i1 + column ), min( width + spanWidth, xe - column ) );
          Wire.endTransmission();
 
          //*******************************************************************
          // lsb is used as data send 
          //*******************************************************************
      
          bitfield |= 1;
         } 

         //********************************************************************  
         // skip span(s)
         //********************************************************************
     
         else {

          switch(  ~i0 & 127  ) {
           case 127:
            spanWidth = 48;
            break;
           case 63:
            spanWidth = 40;
            break;
           case 31:
            spanWidth = 32;
            break;
           case 15:
            spanWidth = 24;
            break;
           case 7:
            spanWidth = 16;
            break;
           case 3:
            spanWidth = 8;
            break;
           default:
            spanWidth = 0;
            break;
          };

          //*******************************************************************
          // lsb is used as no-data send.
          // if 0 - zero - and data needs to be send on same row adjust 
          // oled screen position 
          //*******************************************************************
 
          bitfield -= bitfield & 1;
         }

        column += width + spanWidth;
        width   = 8;

      } while( column < xe );
 

    //*************************************************************************
    // 
    //*************************************************************************

    #if SHOW_FRAMES_PER_SECOND
     if( row != FPS_ROW_POSITION ) {
      memset( ( pBitmapData + ( row * WIDTH ) + xs ), 0, xe - xs ); 
     }
    #else 
      memset( ( pBitmapData + ( row * WIDTH ) + xs ), 0, xe - xs ); 
    #endif

    _lookupMinimumcolumn[ row ] = lookupMinimumcolumn[ row ];
    _lookupMaximumcolumn[ row ] = lookupMaximumcolumn[ row ];
    _lookupOledRefresh  [ row ] = lookupOledRefresh  [ row ];
   }
  }

  //***************************************************************************
  // 
  //***************************************************************************
  
  #if PROFILING
   _timeRendering += micros() - tt;
  #endif
 
  //***************************************************************************
  // 
  //***************************************************************************

  _minimumRow = minimumRow;
  _maximumRow = maximumRow;

  //***************************************************************************
  // 
  //***************************************************************************

  #if ROTATE_Y_AXIS
   _frameYAxis = ( _frameYAxis + 3 ) & 255;
  #endif
 
  #if ROTATE_X_AXIS
   _frameXAxis = ( _frameXAxis + 1 ) & 255;
  #endif

  #if ROTATE_Z_AXIS
   _frameZAxis = ( _frameZAxis + 1 ) & 255;
  #endif
 }

 //****************************************************************************
 // 
 // draw frames per second
 //
 //****************************************************************************

 #if SHOW_FRAMES_PER_SECOND

  void drawFps() {
   byte a, i, fps, index, *pBitmapData;
   word bitmapPos;
   const byte *pLookupFps;

   pBitmapData         = &_bitmapData[ 0 ];
   pLookupFps          = &_lookupFps[ 0 ];
   index               = WIDTH - 1 - 30;
   _numberOfFrames     = ( _numberOfFrames + 1 ) % 32;
   fps                 = 1000 / ( millis() - _time );
   _time               = millis();

   if( !_numberOfFrames ) {
    _totalOfFrameRates  = ( _totalOfFrameRates / 32 ) << 4;
    _numberOfFrames     = 16;
   } else {
    _totalOfFrameRates += fps;
   }

   fps       = byte( _totalOfFrameRates  / _numberOfFrames );
   bitmapPos = ( FPS_ROW_POSITION * WIDTH ) + index;

   for( a = ( fps > 99 ? 0 : fps > 9 ? 5 : 10 ); a < 30; a += 1 ) {

    if( !( a % 5 ) ) {    
 
     i = a / 5;

     if( i < 3 ) {
      i = ( ( fps / ( i == 0 ? 100 : i == 1 ? 10 : 1 ) ) % 10 ) * 5;
     } else {
      i = 50 + ( i - 3 ) * 5;
     }
    }
    
    *( pBitmapData + bitmapPos + a ) |= pgm_read_byte( pLookupFps + i + ( a % 5 ) ); 
   }
   
   //**************************************************************************
   // 
   //**************************************************************************

   byte oledSetPosition[ 7 ] = {
    0x00,             // [ 0 ] command stream
    0x22,             // [ 1 ] ver
    FPS_ROW_POSITION, // [ 2 ] vertical start
    FPS_ROW_POSITION, // [ 3 ] vertical end
    0x21,             // [ 4 ] hor
    index,            // [ 5 ] start collum 
    0x7F              // [ 6 ] end collum
   };
  
   Wire.beginTransmission( SLAVE ); 
   Wire.write( &oledSetPosition[ 0 ], 7 ); 
   Wire.endTransmission();

   for( a = 0;  a < 30; a += 24 ) {
    Wire.beginTransmission( SLAVE ); 
    Wire.write( 0x40 ); 
    Wire.write( ( pBitmapData + bitmapPos + a ), min( 24, 30 - a ) ); 
    Wire.endTransmission();
   }

   //**************************************************************************
   // clear bitmapdata
   //**************************************************************************

   index = min( _lookupMinimumcolumn[ FPS_ROW_POSITION ], index );
   memset( ( pBitmapData + ( FPS_ROW_POSITION * WIDTH ) + index ), 0, WIDTH - index ); 
  }

 #endif

  
