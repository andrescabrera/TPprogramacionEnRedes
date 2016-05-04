//
//  threads.c
//  pthreads
//
//  Created by Diego Marafetti on 3/28/16.
//  Copyright (c) 2016 diego. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


PVOID printNumbers(PVOID args) {

    pthread_t hThread = pthread_self();
    
    for(int i = 0; i < 1000; i++) {
    
        printf("thread %ld: %d\n", (long)hThread, i);
    }
    return NULL;
}



INT main(INT argc, PCHAR *argv {
    
    pthread_t thread1;
    pthread_t thread2;
    
    pthread_create(&thread1, NULL, printNumbers, NULL);
    pthread_create(&thread2, NULL, printNumbers, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    

    return FALSE;
}
