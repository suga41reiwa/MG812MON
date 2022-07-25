/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18326
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdint.h>
#include "stdio.h"
#include "math.h"

/*
                         Main application
 */


#define ADCCH_ANA2 0b000010     

#define AVE_NUM 1000
#define VCC 5.0f
#define TABLE_TOPV 3.028f // 400ppm

const uint16_t co2_table[]={
 400, 404, 408, 411, 415, 419, 423, 427, 431, 435,
 439, 443, 448, 452, 456, 460, 465, 469, 473, 478,
 482, 487, 492, 496, 501, 506, 510, 515, 520, 525,
 530, 535, 540, 545, 550, 555, 560, 566, 571, 576,
 582, 587, 593, 598, 604, 610, 616, 621, 627, 633,
 639, 645, 651, 657, 663, 670, 676, 682, 689, 695,
 702, 708, 715, 722, 729, 735, 742, 749, 756, 764,
 771, 778, 785, 793, 800, 808, 815, 823, 831, 839,
 846, 854, 862, 871, 879, 887, 895, 904, 912, 921,
 930, 938, 947, 956, 965, 974, 983, 993,1002,1011,
1021,1030,1040,1050,1060,1070,1080,1090,1100,1111,
1121,1132,1142,1153,1164,1175,1186,1197,1208,1220,
1231,1243,1255,1266,1278,1290,1302,1315,1327,1340,
1352,1365,1378,1391,1404,1417,1430,1444,1457,1471,
1485,1499,1513,1527,1542,1556,1571,1586,1601,1616,
1631,1646,1662,1677,1693,1709,1725,1741,1758,1774,
1791,1808,1825,1842,1859,1877,1895,1912,1930,1949,
1967,1985,2004,2023,2042,2061,2081,2100,2120,2140,
2160,2180,2201,2222,2243,2264,2285,2307,2328,2350,
2372,2395,2417,2440,2463,2486,2509,2533,2557,2581,
2605,2630,2655,2680,2705,2730,2756,2782,2808,2835,
2861,2888,2915,2943,2970,2998,3027,3055,3084,3113,
3142,3172,3202,3232,3262,3293,3324,3355,3387,3419,
3451,3483,3516,3549,3583,3616,3650,3685,3719,3754,
3790,3825,3861,3898,3935,3972,4009,4047,4085,4123,
4162,4201,4241,4281,4321,4362,4403,4444,4486,4528,
4571,4614,4657,4701,4745,4790,4835,4881,4927,4973,
5020,5067,5115,5163,5211,5261,5310,5360,5411,5461,
5513,5565,5617,5670,5723,5777,5832,5887,5942,5998,
6054,6111,6169,6227,6286,6345,6404,6465,6526,6587,
6649,6712,6775,6839,6903,6968,7033,7100,7167,7234,
7302,7371,7440,7510,7581,7652,7724,7797,7870,7944,
8019,8095,8171,8248,8326,8404,8483,8563,8643,8725,
8807,8890,8974,9058,9143,9229,9316,9404,9492,9582,
9672,9763,9855,9948,10041
};



void putstr( char * p )
{
        while(*p){ 
            EUSART_Write(*p);
            p++;
        }   
}

void main(void)
{
    uint16_t btn_cnt=0;
    float tbltop_v = TABLE_TOPV;
    SYSTEM_Initialize();
    
    __delay_ms(1000);
    putstr("\n\n\r\nMG812MONITOR V1.00\r\n");
    while (1)
    {
        char s[20];
        float ftotal;
        long total;
        int n;
        float fco2v;
        uint16_t co2ppm ;

        ftotal = 0.0f;
        total = 0;
        for(int i= 0;i< AVE_NUM ;i++){
            total +=  ADC_GetConversion(ADCCH_ANA2);
        }     
        ftotal = (float)total * (VCC/1023);
        fco2v = ftotal / AVE_NUM;
        n =  (tbltop_v-fco2v)/(1E-3);

        if(n<0) n= 0;
        else if( n>= (sizeof(co2_table)/2))n=sizeof(co2_table)/2-1;
        co2ppm = co2_table[n];
        sprintf(s,"%d,%5.3fV\r\n",co2ppm,fco2v);
        putstr(s);

        // LED Drive
        if(co2ppm < 700){  // GREEN 
            IO_RC1_SetHigh();            IO_RC0_SetLow();
        }else{      //RED
            IO_RC1_SetLow();            IO_RC0_SetHigh();            
        }    
        
        // manual Calibration
        if(IO_RC2_PORT ==0){
            btn_cnt++;
            if(btn_cnt == 3){
                tbltop_v = fco2v - 0.005;
                btn_cnt =3;
            }
        }else{
            btn_cnt=0;
        }

        __delay_ms(1000);
    }
}


/**
 End of File
*/