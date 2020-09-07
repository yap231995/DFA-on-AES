#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "AES.h"



uint8_t **DFA_round9(state_t* y, state_t* y_fault) {
	uint8_t **KeyHypothesis = (uint8_t **)malloc(512*sizeof(uint8_t *));
   	int counter = 0;

    unsigned long long key = 0;
	while (key <= 4294967295u) {
		unsigned int key_1 = (key& 0XFF) ;
		unsigned int key_2 = ((key& 0XFF00)>>8);
		unsigned int key_3 = ((key& 0XFF0000)>>16);
		unsigned int key_4 = ((key& 0XFF000000)>>24);
		//printf("key_1: %d key_2: %d key_3: %d key_4: %d \n",key_1,key_2,key_3,key_4);
		uint8_t f = InvSBox((*y)[3][1]^key_2)^InvSBox((*y_fault)[3][1]^key_2);
	    uint8_t eq_1 = InvSBox((*y)[2][2]^key_3)^InvSBox((*y_fault)[2][2]^key_3);
        uint8_t eq_2 = InvSBox((*y)[0][0]^key_1)^InvSBox((*y_fault)[0][0]^key_1);
        uint8_t eq_3 = InvSBox((*y)[1][3]^key_4)^InvSBox((*y_fault)[1][3]^key_4);
        uint8_t twof = xtimes(f);
        uint8_t threef = xtimes(f)^f;
        //printf("test1: %d \n", key);
        if (((f == eq_1 && twof == eq_2) && threef == eq_3)) {
        	printf("test2: %llu \n", key);
//        	printf("f: %x \n", f);
//	        printf("eqn1: %x should be equal to f \n", InvSBox((*y)[2][2]^key_3)^InvSBox((*y_fault)[2][2]^key_3));
//	        printf("2f: %x \n", xtimes(f));
//	        printf("eqn2: %x  should be equal to 2f \n", InvSBox((*y)[0][0]^key_1)^InvSBox((*y_fault)[0][0]^key_1));
//	        printf("3f: %x \n", xtimes(f)^f);
//	        printf("eqn3: %x  should be equal to 3f \n", InvSBox((*y)[1][3]^key_4)^InvSBox((*y_fault)[1][3]^key_4));
        	KeyHypothesis[counter] = (uint8_t*) malloc(4*sizeof(uint8_t));
        	KeyHypothesis[counter][0] = key_1;
			KeyHypothesis[counter][1] = key_2;
			KeyHypothesis[counter][2] = key_3;
			KeyHypothesis[counter][3] = key_4;
			counter++;
		}
		key++;
	}
	printf("Size of KeyHypothesis: %d \n", counter);
	return KeyHypothesis;	
}
    
void PrintKeyHypothesis(uint8_t** matrix) {
	int i,j;
	for (i = 0; i < 4; i++) {
        for (j = 0; j < 512; j++) {
            printf("%d ", (matrix)[j][i]);
        }
        printf("\n");
    }
    printf("\n");
} 




//int main() {
//    //printf() displays the string inside quotation
//	state_t MasterKey = {{0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53}};
//	state_t* MasKeyPtr = &MasterKey;
//	state_t matrix1 = {{0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53}};
//	state_t matrix2 = {{0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53}};
//	
//	state_t *ptrMatrix1 = &matrix1;
//	state_t *ptrMatrix2 = &matrix2;
//	
//	
//	printf("Original Text1: \n");
//	PrintMatrix(ptrMatrix1);
//	printf("\n");
//	
//	
//	state_t* ciphertext;
//	ciphertext = AESEncryption(ptrMatrix1,MasKeyPtr);
//	printf("Encrypted Text: \n");
//	PrintMatrix(ciphertext);
//	
//	state_t* ciphertextFaulty;
//	ciphertextFaulty = AESEncryptionFaultyROUND9(ptrMatrix2,MasKeyPtr);
//	printf("Faulty Encrypted Text: \n");
//	PrintMatrix(ciphertextFaulty);
//	
//	uint8_t **KeyHypothesis = DFA_round9(ciphertext, ciphertextFaulty);
////	PrintKeyHypothesis(KeyHypothesis);
//	
// //	Check if the actual key in Round 10 is inside. 

//	//Key Schedule
//	uint8_t** W;
//	W = CreateKeys(MasKeyPtr);
//	
//	state_t key = {{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00}};
//	state_t* keyptr = &key;
//	RoundKey(W, 10 , keyptr);
//	PrintMatrix(ptrMatrix1);
//	
//
//	int j;
//	printf("going in to test \n");
//    for (j = 0; j < 512; j++) {
//    	if( (((KeyHypothesis[j][0] == (*keyptr)[0][0] && KeyHypothesis[j][1] == (*keyptr)[3][1]) 
//		&& KeyHypothesis[j][2] == (*keyptr)[2][2]) 
//		&& KeyHypothesis[j][3] == (*keyptr)[1][3])) {
//			printf("Hurray \n");
//		}
//    }
//	
//	
//
//	return 0;
//}



