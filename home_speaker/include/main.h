#include <Arduino.h>
#include <Spectrum_Analyzer.h>


#include <math.h>
#include <color_palette.h>
#include <definition.h>




// void color_monitor(uint8_t color_value){
//     COLOR_MONITOR.value = color_value;
//     Serial.println("");
//     Serial.print("   Red: ");
//     Serial.print(COLOR_MONITOR.rgb.R);
//     Serial.print("   Green: ");
//     Serial.print(COLOR_MONITOR.rgb.G);
//     Serial.print("   Blue: ");
//     Serial.println(COLOR_MONITOR.rgb.B);
// }

// void led_manager (int column, int current_level){
//     int led_level = (current_level < 5) ? current_level : current_level % 5;
//     if (current_level == 5){
//         for (int i=0; i < 5; i++){
//             int led_pos = current_level-i;
//             color.value = Blue + 1024 * 5;
//             Led_Array[column].setPixelColor(led_pos-i, color.rgb.R, color.rgb.G, color.rgb.B);
//             color_monitor(color.value);
//         }
//     }
//     else{
//         for (int i=0; i < 5; i++){
//             int led_pos = led_level - i;
//             if (led_pos == 0 && current_level > 5){
//                 led_pos = 5;
//                 // led num 5
//             }
//             else if (led_pos >= 1){
//                 color.value = Blue + (1024 * (current_level-i));
//                 // value = Blue + (1024 * 10), 9, 8, 7, 6
//                 Led_Array[column].setPixelColor(led_pos, color.rgb.R, color.rgb.G, color.rgb.B);
//                 color_monitor(color.value);
//             }
//         }
//     }
// }
