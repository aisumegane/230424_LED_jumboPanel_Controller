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
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
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
//???????
unsigned  Vin=0;

//ロータリースイッチの閾値判定
float Vth1 = 1.0f / 11.0f;
float Vth2 = 2.0f / 11.0f;
float Vth3 = 3.0f / 11.0f;
float Vth4 = 4.0f / 11.0f;
float Vth5 = 5.0f / 11.0f;
float Vth6 = 6.0f / 11.0f;
float Vth7 = 7.0f / 11.0f;
float Vth8 = 8.0f / 11.0f;
float Vth9 = 9.0f / 11.0f;
float Vth10 = 10.0f / 11.0f;


void main(void) {
    int RA[11]={0,0,0,0,0,0,0,0,0,0.0};
    int i;
    
    init();
    
    //main関数無限ループ
    while(1){
        ADConversion();                 //A/D変換実行
        Vin = ADRESH;
        Vin = (Vin << 8) + ADRESL;      //ADRESHの内容を8bitシフトして16bitペアとして使う
        Vin = Vin / 1023 * 5;           //実際の電圧値への変換
        
       
        if(Vin < Vth1){                                     //case1
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth1 && Vin < Vth2){                 //case2
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth2 && Vin < Vth3){                 //case2
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth3 && Vin < Vth4){                 //case4
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth4 && Vin < Vth5){                 //case5
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth5 && Vin < Vth6){                 //case6
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth6 && Vin < Vth7){                 //case7
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth7 && Vin < Vth8){                 //case8
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth8 && Vin < Vth9){                 //case9
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth9 && Vin < Vth10){                //case10
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }else if(Vin > Vth10){                              //case11
          //PORTA=0b76543210;
            PORTA=0b00000001;
          //PORTB=0b76543210;
            PORTB=0b00000001;
        }
    }
}


void ADConversion(void){
    GO=1;                   //ここに記載すれば関数呼ばれた時しかA/D変換しない（ADRESH/Lがバグらない）
    while(GO==1);
}

void init(void){
    OSCCON = 0b01110000;   //datasheet_P67_??????? 8MHz
    
    ANSELA = 0b00000100;   //datasheet_P122 1??????????? -> 1??????????????
    ANSELB = 0b00000000;   //datasheet_P128 B???????????
    TRISA  = 0b00000100;    //datasheet_P120 ??????????????????????TRIS????A1??A2???????????????? -> ??1??(RA2)???????
    TRISB  = 0b00000000;
    PORTA  = 0b00000000;    //?????????????datasheet_P119 PORTA(RA0?RA7)?0????
    PORTB  = 0b00000000;    //?????????????PORTB??????
    
    ADCON0 = 0b00001001;    //datasheet_P143 A/D????????
    //ADCON1 = 0b10100100;    //????????????????????
    ADCON1 = 0b11010000;    //Device Frequency(FSOC)が4MHzの時は1.0us、2.0us、4.0usしか選択できない。
}