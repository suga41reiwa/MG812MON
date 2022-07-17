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
#define TABLE_TOPV 3.15f // 400ppm

const uint16_t co2_table[]={
400  ,403  ,406  ,409  ,412  ,414  ,417  ,420  ,422  ,425  ,
428  ,431  ,434  ,436  ,439  ,442  ,445  ,448  ,451  ,454  ,
457  ,460  ,463  ,466  ,469  ,472  ,475  ,478  ,481  ,484  ,
487  ,491  ,494  ,497  ,500  ,503  ,507  ,510  ,513  ,517  ,
520  ,523  ,527  ,530  ,534  ,537  ,541  ,544  ,548  ,551  ,
555  ,559  ,562  ,566  ,570  ,573  ,577  ,581  ,585  ,588  ,
592  ,596  ,600  ,604  ,608  ,612  ,616  ,620  ,624  ,628  ,
632  ,636  ,640  ,644  ,649  ,653  ,657  ,661  ,666  ,670  ,
674  ,679  ,683  ,688  ,692  ,697  ,701  ,706  ,710  ,715  ,
720  ,724  ,729  ,734  ,739  ,743  ,748  ,753  ,758  ,763  ,
768  ,773  ,778  ,783  ,788  ,793  ,798  ,804  ,809  ,814  ,
819  ,825  ,830  ,836  ,841  ,846  ,852  ,858  ,863  ,869  ,
874  ,880  ,886  ,892  ,897  ,903  ,909  ,915  ,921  ,927  ,
933  ,939  ,945  ,951  ,958  ,964  ,970  ,977  ,983  ,989  ,
996  ,1002  ,1009  ,1015  ,1022  ,1029  ,1035  ,1042  ,1049  ,
1056  ,1063  ,1069  ,1076  ,1083  ,1091  ,1098  ,1105  ,1112  ,
1119  ,1127  ,1134  ,1141  ,1149  ,1156  ,1164  ,1171  ,1179  ,
1187  ,1194  ,1202  ,1210  ,1218  ,1226  ,1234  ,1242  ,1250  ,
1258  ,1266  ,1274  ,1283  ,1291  ,1300  ,1308  ,1317  ,1325  ,
1334  ,1342  ,1351  ,1360  ,1369  ,1378  ,1387  ,1396  ,1405  ,
1414  ,1423  ,1433  ,1442  ,1451  ,1461  ,1470  ,1480  ,1489  ,
1499  ,1509  ,1519  ,1529  ,1539  ,1549  ,1559  ,1569  ,1579  ,
1589  ,1600  ,1610  ,1621  ,1631  ,1642  ,1653  ,1663  ,1674  ,
1685  ,1696  ,1707  ,1718  ,1729  ,1741  ,1752  ,1764  ,1775  ,
1787  ,1798  ,1810  ,1822  ,1834  ,1846  ,1858  ,1870  ,1882  ,
1894  ,1906  ,1919  ,1931  ,1944  ,1957  ,1969  ,1982  ,1995  ,
2008  ,2021  ,2034  ,2048  ,2061  ,2074  ,2088  ,2102  ,2115  ,
2129  ,2143  ,2157  ,2171  ,2185  ,2199  ,2214  ,2228  ,2243  ,
2257  ,2272  ,2287  ,2302  ,2317  ,2332  ,2347  ,2362  ,2378  ,
2393  ,2409  ,2424  ,2440  ,2456  ,2472  ,2488  ,2504  ,2521  ,
2537  ,2554  ,2570  ,2587  ,2604  ,2621  ,2638  ,2655  ,2672  ,
2690  ,2707  ,2725  ,2743  ,2761  ,2779  ,2797  ,2815  ,2833  ,
2852  ,2870  ,2889  ,2908  ,2927  ,2946  ,2965  ,2984  ,3024  ,
3063  ,3103  ,3144  ,3185  ,3226  ,3269  ,3311  ,3355  ,3399  ,
3443  ,3488  ,3534  ,3580  ,3627  ,3674  ,3722  ,3771  ,3820  ,
3870  ,3921  ,3972  ,4024  ,4076  ,4130  ,4184  ,4238  ,4294  ,
4350  ,4407  ,4464  ,4523  ,4582  ,4642  ,4703  ,4764  ,4826  ,
4889  ,4953  ,5018  ,5084  ,5150  ,5218  ,5286  ,5355  ,5425  ,
5496  ,5568  ,5640  ,5714  ,5789  ,5865  ,5941  ,6019  ,6098  ,
6177  ,6258  ,6340  ,6423  ,6507  ,6592  ,6678  ,6765  ,6854  ,
6944  ,7034  ,7126  ,7220  ,7314  ,7410  ,7506  ,7605  ,7704  ,
7805  ,7907  ,8010  ,8115  ,8221  ,8328  ,8437  ,8548  ,8659  ,
8773  ,8887  ,9004  ,9121  ,9241  ,9361  ,9484  ,9608  ,9733  ,
9861  ,9990  ,10120  
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
    SYSTEM_Initialize();
    
    putstr("MG812MONITOR V1.00\r\n");
    while (1)
    {
        char s[20];
        float ftotal;
        long total;
        int n;
        adc_result_t co2val;
        float fco2v;
        uint16_t co2ppm ;

        ftotal = 0.0f;
        total = 0;
        for(int i= 0;i< AVE_NUM ;i++){
            co2val =  ADC_GetConversion(ADCCH_ANA2);
            total += co2val;
        }     
        ftotal = total;
        ftotal = ftotal * (VCC/1023);
        fco2v = ftotal / AVE_NUM;
        n =  (TABLE_TOPV-fco2v)/(1E-3);

        if(n<0) n= 0;
        else if( n>= (sizeof(co2_table)/2))n=sizeof(co2_table)/2-1;
        co2ppm = co2_table[n];
        sprintf(s,"%d,%5.3fV\r\n",co2ppm,fco2v);
        putstr(s);
        __delay_ms(1000);
    }
}


/**
 End of File
*/