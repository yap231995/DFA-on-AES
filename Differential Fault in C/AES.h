#ifndef _AES_H
#define _AES_H



typedef uint8_t state_t[4][4];

uint8_t InvSBox(uint8_t);
uint8_t SBox(uint8_t);
uint8_t Rcon(uint8_t);

uint8_t xtimes(uint8_t);
uint8_t** CreateKeys(state_t*); 
void RoundKey(uint8_t**, int, state_t*);
void PrintMatrix(state_t*);




state_t * AESEncryption(state_t*, state_t*);
state_t * AESDecryption(state_t*, state_t*);
state_t * AESEncryptionFaultyROUND9(state_t*, state_t*);
state_t * AESEncryptionFaultyROUND8(state_t*, state_t*);

#endif	
