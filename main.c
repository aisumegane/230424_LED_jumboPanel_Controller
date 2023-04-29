/*
 * File:   main.c
 * Author: HGS01
 *
 * Created on 2023/04/23, 6:14
 */

// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000



//プロトタイプ宣言
void init(void);
void ADConversion(void);

//ロータリースイッチの閾値判定
const float  VCC = 5;
const float Input_division = 10.0f;    //floatと一緒に計算したらfloat値として代入される(この変数自体はint範囲でよい．) -> X
const float Input_accuracy = 0.3f;
const float Input_resolution = Input_accuracy * 1.0f / Input_division;   //入力値の振れ幅設定．キャストが必要になるとconstが外れるので全部型は統一した方が良い. 

const float Vth1 = VCC * 1.0f / Input_division;
const float Vth2 = VCC * 2.0f / Input_division;
const float Vth3 = VCC * 3.0f / Input_division;
const float Vth4 = VCC * 4.0f / Input_division;
const float Vth5 = VCC * 5.0f / Input_division;             // = 2.5V
const float Vth6 = VCC * 6.0f / Input_division;
const float Vth7 = VCC * 7.0f / Input_division;
const float Vth8 = VCC * 8.0f / Input_division;
const float Vth9 = VCC * 9.0f / Input_division;
const float Vth10 = VCC * 10.0f / Input_division;           // = 5.0V

void main(void) {
    unsigned short Vin_ADRES=0;
    float Vin=0;
    
    init();
    
    //main関数無限ループ
    while(1){
        ADConversion();                 //A/D変換実行
        Vin_ADRES = ADRESH;
        Vin_ADRES = (Vin_ADRES << 8) + ADRESL;      //ADRESHの内容を8bitシフトして16bitペアとして使う
        Vin = (float)Vin_ADRES / 1023.0f * 5.0f;           //実際の電圧値への変換
        
        
        //分岐設定
        if(Vin < Input_resolution ){                                     //case0
          //PORTA=0b76543210;   //RA1
            PORTA=0b00000000;   
          //PORTB=0b76543210;
            PORTB=0b00000000;
        }else if(Vin > (Vth1 - Input_resolution)  && Vin < (Vth1 + Input_resolution) ){                 //case1
          //PORTA=0b76543210;
            PORTA=0b00000010;
          //PORTB=0b76543210;
            PORTB=0b01110000;
        }else if(Vin > (Vth2 - Input_resolution)  && Vin < (Vth2 + Input_resolution) ){                 //case2
          //PORTA=0b76543210;
            PORTA=0b00000001;   //RA7
          //PORTB=0b76543210;
            PORTB=0b01110000;
        }else if(Vin > (Vth3 - Input_resolution)  && Vin < (Vth3 + Input_resolution) ){                 //case3
          //PORTA=0b76543210;
            PORTA=0b10000000;
          //PORTB=0b76543210;
            PORTB=0b01110000;
        }else if(Vin > (Vth4 - Input_resolution)  && Vin < (Vth4 + Input_resolution) ){                 //case4
          //PORTA=0b76543210;
            PORTA=0b01000000;
          //PORTB=0b76543210;
            PORTB=0b01110000;
        }else if(Vin > (Vth5 - Input_resolution)  && Vin < (Vth5 + Input_resolution) ){                 //case5
          //PORTA=0b76543210;
            PORTA=0b00000000;
          //PORTB=0b76543210;
            PORTB=0b11110000;
        }else if(Vin > (Vth6 - Input_resolution)  && Vin < (Vth6 + Input_resolution) ){                 //case6
          //PORTA=0b76543210;
            PORTA=0b11000011;
          //PORTB=0b76543210;
            PORTB=0b11000000;
        }else if(Vin > (Vth7 - Input_resolution)  && Vin < (Vth7 + Input_resolution) ){                 //case7
          //PORTA=0b76543210;
            PORTA=0b11000011;
          //PORTB=0b76543210;
            PORTB=0b10100000;
        }else if(Vin > (Vth8 - Input_resolution)  && Vin < (Vth8 + Input_resolution) ){                 //case8
          //PORTA=0b76543210;
            PORTA=0b11000011;
          //PORTB=0b76543210;
            PORTB=0b10010000;
        }else if(Vin > (Vth9 - Input_resolution)  && Vin < (Vth9 + Input_resolution) ){                //case9
          //PORTA=0b76543210;
            PORTA=0b11000011;
          //PORTB=0b76543210;
            PORTB=0b11010000;
        }else if(Vin > (Vth10 - Input_resolution) ){                              //case10
          //PORTA=0b76543210;
            PORTA=0b11000011;
          //PORTB=0b76543210;
            PORTB=0b11110000;
        }
    }
}


void ADConversion(void){
    GO=1;                   //ここに記載すれば関数呼ばれた時しかA/D変換しない（ADRESH/Lがバグらない）
    while(GO==1);
}

void init(void){
    OSCCON = 0b01110000;   //datasheet_P678MHz
    
    ANSELA = 0b00000100;   //datasheet_P122
    ANSELB = 0b00000000;   //datasheet_P128
    TRISA  = 0b00100100;    //datasheet_P120
    TRISB  = 0b00000000;
    PORTA  = 0b00000000;    //datasheet_P119
    PORTB  = 0b00000000;    //PORTB
    
    ADCON0 = 0b00001001;    //datasheet_P143
    ADCON1 = 0b11010000;    //Device Frequency(FSOC)が4MHzの時は1.0us、2.0us、4.0usしか選択できない。
}