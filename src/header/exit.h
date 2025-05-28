#ifndef EXIT_H
#define EXIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"



void saveToCSV(User u[], int count) ;
// Menyimpan dari ADT user ke user.csv

char readExit(){
    int n;
    scanf("%s" , &n);
    while(n != 'n' || n != 'N' || n!='y' || n != 'Y'){
        scanf("%s" , &n);
    }
    return n;
}
// Membaca dan memastikan agar input user valid


void exit(User u[], int count,char n){
    n = readExit();
    if(n == 'n' || n =='N'){
        return;
        // lakukan procedure untuk keluar dari program utama
    }
    else if(n == 'Y' || n == 'y'){
        saveToCSV(u,count);
        // lakukan procedure untuk keluar dari program utama
        return;

    }
}
// melakukan exit program

#endif