// RGB565 8 bit, for LCD
// Google material                     R     G    B
#define Black           0x0000      // 0, 0, 0
#define Red             0xE38E      // 229, 115, 115
#define Pink            0xF312      // 240, 98, 146
#define Purple          0xBB59      // 186, 104, 200
#define DeepPurple      0x93B9      // 149, 117, 205
#define Indigo          0x7C39      // 120, 134, 204
#define Blue            0x65BE      // 96, 180, 244
#define LightBlue       0x4E1E      // 79, 194, 247
#define Cyan            0x4E7C      // 76, 207, 224
#define Teal            0x4DB5      // 75, 181, 171
#define Green           0x8630      // 128, 198, 131
#define LightGreen      0xAEB0      // 173, 214, 129
#define Lime            0xDF4E      // 221, 232, 117
#define Yellow          0xFF8E      // 255, 241, 118
#define Amber           0xFEA9      // 255, 213, 79
#define Orange          0xFDA9      // 255, 183, 77
#define DeepOrange      0xFC4C      // 255, 138, 101
#define Brown           0xA42F      // 160, 135, 126
#define Grey            0xE71C      // 224, 224, 224
#define BlueGrey        0x8D15      // 143, 163, 173
#define White           0xFFFF      // 255, 255, 255
//Light
#define LRed            0xFD34      // 255, 164, 162
#define LPink           0xFCB8      // 255, 148, 194
#define LPurple         0xECDF      // 238, 152, 251
#define LDeepPurple     0xC53F      // 199, 164, 255
#define LIndigo         0xADBF      // 170, 182, 255
#define LBlue           0x973F      // 151, 230, 255
#define LLightBlue      0x8FBF      // 139, 245, 255
#define LCyan           0x87FF      // 135, 255, 255
#define LTeal           0x875B      // 128, 232, 221
#define LGreen          0xB7D6      // 177, 249, 179
#define LLightGreen     0xE7F6      // 224, 225, 177
#define LLime           0xFFF4      // 255, 255, 166
#define LYellow         0xFFF5      // 255, 255, 168
#define LAmber          0xFFF0      // 255, 255, 129
#define LOrange         0xFF4F      // 255, 233, 125
#define LDeepOrange     0xFDD2      // 255, 187, 147
#define LBrown          0xD5B5      // 209, 83, 173
// Light Grey is White
#define LBlueGrey       0xBEBB      // 191, 212, 223
//Dark
#define DRed            0xAA29      // 175, 68, 72
#define DPink           0xB96C      // 186, 45, 101
#define DPurple         0x89D2      // 136, 57, 151
#define DDeepPurple     0x6253      // 101, 73, 156
#define DIndigo         0x42D3      // 71, 89, 155
#define DBlue           0x1C38      // 25, 133, 193
#define DLightBlue      0x0498      // 0, 146, 196
#define DCyan           0x04F5      // 0, 158, 174
#define DTeal           0x042F      // 0, 133, 124
#define DGreen          0x54AA      // 80, 149, 86
#define DLightGreen     0x7D2A      // 124, 164, 83
#define DLime           0xADA8      // 169, 182, 69
#define DYellow         0xCDE8      // 202, 191, 69
#define DAmber          0xCD22      // 200, 164, 21
#define DOrange         0xCC23      // 200, 135, 25
#define DDeepOrange     0xC2C7      // 199, 91, 57
#define DBrown          0x72CA      // 113, 90, 82
#define DGrey           0xAD75      // 174, 174, 174
#define DBlueGrey       0x63AF      // 97, 116, 126

// RGB 32 bit, LED WS2818
#define BLUE            0X2196F3
#define RED             0xF44336

/*
convert hex color value to (r,g,b) format
usage:
color.value = Red;
color.color(color.rgb.R, color.rgb.G, color.rgb.B)
bug blue color always 0
*/
// struct RGB_COLOR {
//     byte R;
//     byte G;
//     byte B;
//     byte A;
// };

// union COLOR{
//     RGB_COLOR rgb;
//     unsigned int value;
// } color;

/*
Convert hex color to RGB
*/
// uint8_t getRed(uint32_t c){
//     return c >> 16;
// }
// uint8_t getGreen(uint32_t c){
//     return c >> 8;
// }
// uint8_t getBlue(uint32_t c){
//     return c;
// }