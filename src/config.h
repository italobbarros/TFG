#ifndef CONFIG_H
#define CONFIG_H


#define DEBUG 

#define BRANCAS 0
#define PRETAS 1

#define SUCESS 1
#define FAILED 0

#ifdef DEBUG 
void debugSerial(const char* debug){
    Serial.print(debug);
}
#endif

#endif /*CONFIG_H*/    