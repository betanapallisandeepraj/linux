#include "say.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int say(int64_t input, char **ans)
{
    //static char buff[1024]={0};
    unsigned char digits=0;
    char *num[10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    char *tens_num[10] = {"","ten","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"};
    char *teen_num[10] = {"","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen",
                            "eightteen","nineteen"};
    char *num_keys[] = {"hundred","thousand","millon","billion"};
    //int i;
    int64_t temp=input;
    char buff[200]={0};
    if((input<0)||(input>999999999999)) {
        return -1;
    }
    while(temp) {
        digits++;
        temp/=10;
    }
    //printf("%u\n",digits);


    *ans=(char *)calloc(1,200);
    if(digits==0) {
        strcpy(*ans,num[0]);
        return 0;
    }
    else if(digits==1) {
        strcpy(*ans,num[input]);
        return 0;
    }
    else if(digits==2) {
        if((input%10)==0) {
            strcpy(*ans,tens_num[input/10]);
            return 0;
        }else if(input<20){                             // from 11-19
            strcpy(*ans,teen_num[input%10]);
            return 0;
        }else {
            strcpy(buff,tens_num[input/10]);                 // from 22-99
            strcat(buff,"-");
            strcat(buff,num[input%10]);
            strcpy(*ans,buff);
            return 0;
        }
    }
    else if(digits==3) {
        if((input%100)==0) {
            strcpy(buff,num[input/100]);
            strcat(buff," ");
            strcat(buff,num_keys[0]);
            strcpy(*ans,buff);
            return 0;
        }else if((input%10)==0) {
            strcpy(buff,num[input/100]);
            strcat(buff," ");
            strcat(buff,num_keys[0]);
            strcat(buff,tens_num[(input/10)%10]);
            strcpy(*ans,buff);
            return 0;
        }else {
            if((input%100)<20) {                        // from 111-119,211-219,...911-919
                strcpy(buff,num[input/100]);
                strcat(buff," ");
                strcat(buff,num_keys[0]);
                strcat(buff,teen_num[input%10]);
                strcpy(*ans,buff);
                return 0;
            }else {                                      // from _21 - _99       
                strcpy(buff,num[input/100]);
                strcat(buff," ");
                strcat(buff,num_keys[0]);
                strcat(buff," ");
                strcat(buff,tens_num[(input/10)%10]);
                strcat(buff,"-");
                strcat(buff,num[input%10]);
                strcpy(*ans,buff);
                return 0;
            }
            
        }
    }
    else if(digits==4) {
        if((input%1000)==0) {                       // 1000,2000,3000,....9000
            strcpy(buff,num[input/1000]);
            strcat(buff," ");
            strcat(buff,num_keys[1]);
            strcpy(*ans,buff);
            return 0;
        }else if((input%100)==0) {                  // 1100,1200,1300.....9900
            strcpy(buff,num[input/1000]);
            strcat(buff," ");
            strcat(buff,num_keys[1]);
            strcat(buff,num[(input/100)%10]);
            strcat(buff," ");
            strcat(buff,num_keys[0]);
            strcpy(*ans,buff);
            return 0;
        }else if((input%10)==0) {                   // 1110,1120,1130,....9990
            strcpy(buff,num[input/1000]);
            strcat(buff," ");
            strcat(buff,num_keys[1]);
            strcat(buff,num[(input/100)%10]);
            strcat(buff," ");
            strcat(buff,num_keys[0]);
            strcat(buff," ");
            strcat(buff,tens_num[(input/10)%10]);
            strcpy(*ans,buff);
            return 0;
        }else {
            if((input%100)<20) {                        // from 1111-1119,2111-2119,...9111-9119
                strcpy(buff,num[input/1000]);
                strcat(buff," ");
                strcat(buff,num_keys[1]);
                strcat(buff,num[(input/100)%10]);
                strcat(buff," ");
                strcat(buff,num_keys[0]);
                strcat(buff," ");
                strcat(buff,teen_num[input%10]);
                strcpy(*ans,buff);
                return 0;                
            }else {                                      // from 1121-1199,1221-1299,..... 9921-9999       
                strcpy(buff,num[input/1000]);
                strcat(buff," ");
                strcat(buff,num_keys[1]);
                strcat(buff," ");
                strcat(buff,num[(input/100)%10]);
                strcat(buff," ");
                strcat(buff,num_keys[0]);
                strcat(buff," ");
                strcat(buff,tens_num[(input/10)%10]);
                strcat(buff,"-");
                strcat(buff,num[input%10]);
                strcpy(*ans,buff);
                //printf("%s\n",buff);
                return 0;
            }
            
        }
    }
    else if(digits==5) {
        if((input%10000)==0) {                       // 10000,20000,30000,....90000
            strcpy(buff,tens_num[input/10000]);
            strcat(buff," ");
            strcat(buff,num_keys[1]);
            strcpy(*ans,buff);
            return 0;
        }else if((input%1000)==0) {                  
            if((input/1000)<20) {                   // 11000,12000,13000.....19000
                strcpy(buff,teen_num[(input/1000)%10]);
                strcat(buff," ");
                strcat(buff,num_keys[1]);
                strcpy(*ans,buff);
                return 0;
            } else {                                // 21000,22000,23000,....99000
                strcpy(buff,tens_num[input/1000]);
                strcat(buff," ");
                strcpy(buff,num[(input/1000)%10]);
                strcat(buff," ");
                strcat(buff,num_keys[1]);
                strcpy(*ans,buff);
                return 0;
            }
            
        }
    }

    return 0;
}
