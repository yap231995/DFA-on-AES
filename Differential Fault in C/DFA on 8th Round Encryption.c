#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <inttypes.h>
#include <time.h>
#include "AES.h"



uint8_t ***DFA_round8Phase1(state_t* y, state_t* y_fault, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3) {
	uint8_t ***KeyHypothesisSet = (uint8_t ***)malloc(4*sizeof(uint8_t **));
	KeyHypothesisSet[0] = (uint8_t **)malloc(1000*sizeof(uint8_t *)); // For key k_1,k_8,k_11,k_14
	KeyHypothesisSet[1] = (uint8_t **)malloc(1000*sizeof(uint8_t *)); // For key k_2,k_5,k_12,k_15
	KeyHypothesisSet[2] = (uint8_t **)malloc(1000*sizeof(uint8_t *)); // For key k_3,k_6,k_9,k_16
	KeyHypothesisSet[3] = (uint8_t **)malloc(1000*sizeof(uint8_t *)); // For key k_4,k_7,k_10,k_13
   	int counter0 = 0;
   	int counter1 = 0;
   	int counter2 = 0;
   	int counter3 = 0;
   	
   	
    unsigned long long key = 0;
	while (key <= 4294967295u) {
		unsigned int key_1 = (key& 0XFF) ;
		unsigned int key_2 = ((key& 0XFF00)>>8);
		unsigned int key_3 = ((key& 0XFF0000)>>16);
		unsigned int key_4 = ((key& 0XFF000000)>>24);
		//printf("key_1: %d key_2: %d key_3: %d key_4: %d \n",key_1,key_2,key_3,key_4);
		
		
		//Column 1
		uint8_t f1 = InvSBox((*y)[3][1]^key_4)^InvSBox((*y_fault)[3][1]^key_4);  // 14
	    uint8_t eq_1 = InvSBox((*y)[2][2]^key_3)^InvSBox((*y_fault)[2][2]^key_3); //11
        uint8_t eq_2 = InvSBox((*y)[0][0]^key_1)^InvSBox((*y_fault)[0][0]^key_1); //1
        uint8_t eq_3 = InvSBox((*y)[1][3]^key_2)^InvSBox((*y_fault)[1][3]^key_2); //8
        uint8_t twof1 = xtimes(f1);
        uint8_t threef1 = xtimes(f1)^f1;
        //printf("test1: %d \n", key);
        if (((f1 == eq_1 && twof1 == eq_2) && threef1 == eq_3)) {
        	printf("test1: %llu \n", key);
        	KeyHypothesisSet[0][counter0] = (uint8_t*) malloc(4*sizeof(uint8_t));
        	KeyHypothesisSet[0][counter0][0] = key_1;//1
			KeyHypothesisSet[0][counter0][1] = key_2;//8
			KeyHypothesisSet[0][counter0][2] = key_3;//11
			KeyHypothesisSet[0][counter0][3] = key_4;//14
			counter0++;
		}
		
		
		//Column 2
		uint8_t f2 = InvSBox((*y)[1][0]^key_2)^InvSBox((*y_fault)[1][0]^key_2);  //5
	    eq_1 = InvSBox((*y)[0][1]^key_1)^InvSBox((*y_fault)[0][1]^key_1); //2
        eq_2 = InvSBox((*y)[2][3]^key_3)^InvSBox((*y_fault)[2][3]^key_3); //12
        eq_3 = InvSBox((*y)[3][2]^key_4)^InvSBox((*y_fault)[3][2]^key_4); //15
        uint8_t twof2 = xtimes(f2);
        uint8_t threef2 = xtimes(f2)^f2;
		
		if (((f2 == eq_1 && twof2 == eq_2) && threef2 == eq_3)) {
			printf("test2: %llu \n", key);
			KeyHypothesisSet[1][counter1] = (uint8_t*) malloc(4*sizeof(uint8_t));
        	KeyHypothesisSet[1][counter1][0] = key_1;//2
			KeyHypothesisSet[1][counter1][1] = key_2;//5
			KeyHypothesisSet[1][counter1][2] = key_3;//12
			KeyHypothesisSet[1][counter1][3] = key_4;//15
			counter1++;
		}
		
		
		
		//Column 3
		uint8_t f3 =  InvSBox((*y)[2][0]^key_3)^InvSBox((*y_fault)[2][0]^key_3);  //9
	    eq_1 = InvSBox((*y)[3][3]^key_4)^InvSBox((*y_fault)[3][3]^key_4); //16
        eq_2 = InvSBox((*y)[0][2]^key_1)^InvSBox((*y_fault)[0][2]^key_1); //3
        eq_3 = InvSBox((*y)[1][1]^key_2)^InvSBox((*y_fault)[1][1]^key_2); //6
        uint8_t twof3 = xtimes(f3);
        uint8_t threef3 = xtimes(f3)^f3;
		
		if (((f3 == eq_1 && twof3 == eq_2) && threef3 == eq_3)) {
			printf("test3: %llu \n", key);
			KeyHypothesisSet[2][counter2] = (uint8_t*) malloc(4*sizeof(uint8_t));
        	KeyHypothesisSet[2][counter2][0] = key_1;//3
			KeyHypothesisSet[2][counter2][1] = key_2;//6
			KeyHypothesisSet[2][counter2][2] = key_3;//9
			KeyHypothesisSet[2][counter2][3] = key_4;//16
			counter2++;
		}
		
		//Column 4
		uint8_t f4 =  InvSBox((*y)[0][3]^key_1)^InvSBox((*y_fault)[0][3]^key_1);  //4
	    eq_1 = InvSBox((*y)[1][2]^key_2)^InvSBox((*y_fault)[1][2]^key_2); //7
        eq_2 = InvSBox((*y)[2][1]^key_3)^InvSBox((*y_fault)[2][1]^key_3); //10
        eq_3 = InvSBox((*y)[3][0]^key_4)^InvSBox((*y_fault)[3][0]^key_4); //13
        uint8_t twof4 = xtimes(f4);
        uint8_t threef4 = xtimes(f4)^f4;
		
		if (((f4 == eq_1 && twof4 == eq_2) && threef4 == eq_3)) {
			printf("test4: %llu \n", key);
			KeyHypothesisSet[3][counter3] = (uint8_t*) malloc(4*sizeof(uint8_t));
        	KeyHypothesisSet[3][counter3][0] = key_1;//4
			KeyHypothesisSet[3][counter3][1] = key_2;//7
			KeyHypothesisSet[3][counter3][2] = key_3;//10
			KeyHypothesisSet[3][counter3][3] = key_4;//13
			counter3++;
		}
		key++;
	}
	*SizeKeySet0 = counter0;
	*SizeKeySet1 = counter1;
	*SizeKeySet2 = counter2;
	*SizeKeySet3 = counter3;

	printf("Size of KeyHypothesisSet0: %d \n", counter0);
	printf("Size of KeyHypothesisSet1: %d \n", counter1);
	printf("Size of KeyHypothesisSet2: %d \n", counter2);
	printf("Size of KeyHypothesisSet3: %d \n", counter3);
	return KeyHypothesisSet;	
}


uint8_t times9(uint8_t x) {
	return xtimes(xtimes(xtimes(x)))^x;
}

uint8_t times11(uint8_t x) {
	return xtimes(xtimes(xtimes(x)))^xtimes(x)^x;
}

uint8_t times13(uint8_t x) {
    return xtimes(xtimes(xtimes(x)))^xtimes(xtimes(x))^x;
}
        
uint8_t times14(uint8_t x) {
    return xtimes(xtimes(xtimes(x)))^xtimes(xtimes(x))^xtimes(x);
}    


uint8_t **equation1and4(state_t* y,state_t* y_fault, uint8_t** Key1Ptr, int* Key1Size, uint8_t** Key2Ptr, int* Key2Size, uint8_t **PartKey, int* PartKeySize, int* SaveSize, int index) {
	uint8_t ** Key = (uint8_t **)malloc(5000000*sizeof(uint8_t *));
	int KeySize = 0;
	int k_1,k_2,part;
	for(k_1 = 0; k_1 < *Key1Size; k_1++) {
		for(k_2 = 0; k_2 < *Key2Size; k_2++) {
			for(part = 0; part < *PartKeySize; part++) {
				uint8_t k1 = Key1Ptr[k_1][0];
				uint8_t k2 = Key2Ptr[k_2][0];
				uint8_t k3 = PartKey[part][0];
				uint8_t k4 = PartKey[part][1];
				uint8_t k5 = PartKey[part][2];
				uint8_t k6 = PartKey[part][3];
				uint8_t k7 = PartKey[part][4];
				uint8_t k8 = PartKey[part][5];
				uint8_t k9 = PartKey[part][6];
				uint8_t k10 = PartKey[part][7];
				uint8_t k11 = PartKey[part][8];
				uint8_t k12 = PartKey[part][9];
				uint8_t k13 = PartKey[part][10];
				uint8_t k14 = PartKey[part][11];
				uint8_t k15 = PartKey[part][12];
				uint8_t k16 = PartKey[part][13];
				/*printf(" k1: %"SCNd32 " k2: %"SCNd32 " k3: %"SCNd32 " k4: %"SCNd32 " \n", k1, k2, k3, k4);
				printf(" k5: %"SCNd32 " k6: %"SCNd32 " k7: %"SCNd32 " k8: %"SCNd32 " \n", k5, k6, k7, k8);
				printf(" k9: %"SCNd32 " k10: %"SCNd32 " k11: %"SCNd32 " k12: %"SCNd32 " \n", k9, k10, k11, k12);
				printf(" k13: %"SCNd32 " k14: %"SCNd32 " k15: %"SCNd32 " k16: %"SCNd32 " \n", k13, k14, k15, k16);*/
				if (Key1Ptr[k_1][1] == k8 && Key1Ptr[k_1][2] == k11 && Key1Ptr[k_1][3] == k14 && Key2Ptr[k_2][1] == k5 && Key2Ptr[k_2][2] == k12 && Key2Ptr[k_2][3] == k15) {
					uint8_t eq1 = InvSBox(times14(InvSBox((*y)[0][0] ^ k1) ^ (k1 ^ SBox(k14 ^ k10) ^ Rcon(10)))
						^ times11(InvSBox((*y)[3][1] ^ k14) ^ (k2 ^ SBox(k15 ^ k11)))
						^ times13(InvSBox((*y)[2][2] ^ k11) ^ (k3 ^ SBox(k16 ^ k12)))
						^ times9(InvSBox((*y)[1][3] ^ k8) ^ (k4 ^ SBox(k13 ^ k9))))
						^ InvSBox(times14(InvSBox((*y_fault)[0][0] ^ k1) ^ (k1 ^ SBox(k14 ^ k10) ^ Rcon(10)))
							^ times11(InvSBox((*y_fault)[3][1] ^ k14) ^ (k2 ^ SBox(k15 ^ k11)))
							^ times13(InvSBox((*y_fault)[2][2] ^ k11) ^ (k3 ^ SBox(k16 ^ k12)))
							^ times9(InvSBox((*y_fault)[1][3] ^ k8) ^ (k4 ^ SBox(k13 ^ k9))));

					uint8_t eq2 = InvSBox(times9(InvSBox((*y)[3][0] ^ k13) ^ (k13 ^ k9))
						^ times14(InvSBox((*y)[2][1] ^ k10) ^ (k14 ^ k10))
						^ times11(InvSBox((*y)[1][2] ^ k7) ^ (k15 ^ k11))
						^ times13(InvSBox((*y)[0][3] ^ k4) ^ (k16 ^ k12)))
						^ InvSBox(times9(InvSBox((*y_fault)[3][0] ^ k13) ^ (k13 ^ k9))
							^ times14(InvSBox((*y_fault)[2][1] ^ k10) ^ (k14 ^ k10))
							^ times11(InvSBox((*y_fault)[1][2] ^ k7) ^ (k15 ^ k11))
							^ times13(InvSBox((*y_fault)[0][3] ^ k4) ^ (k16 ^ k12)));

					uint8_t eq4 = InvSBox(times11(InvSBox((*y)[1][0] ^ k5) ^ (k5 ^ k1))
						^ times13(InvSBox((*y)[0][1] ^ k2) ^ (k6 ^ k2))
						^ times9(InvSBox((*y)[3][2] ^ k15) ^ (k7 ^ k3))
						^ times14(InvSBox((*y)[2][3] ^ k12) ^ (k8 ^ k4)))
						^ InvSBox(times11(InvSBox((*y_fault)[1][0] ^ k5) ^ (k5 ^ k1))
							^ times13(InvSBox((*y_fault)[0][1] ^ k2) ^ (k6 ^ k2))
							^ times9(InvSBox((*y_fault)[3][2] ^ k15) ^ (k7 ^ k3))
							^ times14(InvSBox((*y_fault)[2][3] ^ k12) ^ (k8 ^ k4)));
				
					if ((xtimes(eq2) == eq1) && ((xtimes(eq2) ^ eq2) == eq4)) {
						printf("index: %d k_1: %d k_2: %d part: %d KeySize: %d \n", index, k_1, k_2, part, KeySize);
						Key[KeySize] = (uint8_t*)malloc(16 * sizeof(uint8_t));
						Key[KeySize][0] = k1;
						Key[KeySize][1] = k2;
						Key[KeySize][2] = k3;
						Key[KeySize][3] = k4;
						Key[KeySize][4] = k5;
						Key[KeySize][5] = k6;
						Key[KeySize][6] = k7;
						Key[KeySize][7] = k8;
						Key[KeySize][8] = k9;
						Key[KeySize][9] = k10;
						Key[KeySize][10] = k11;
						Key[KeySize][11] = k12;
						Key[KeySize][12] = k13;
						Key[KeySize][13] = k14;
						Key[KeySize][14] = k15;
						Key[KeySize][15] = k16;
						KeySize++;
					}
				}
			}
		}
	}
	*SaveSize = KeySize;
	printf("SaveSize inside: %d index: %d \n", *SaveSize, index);
	return Key;
}


uint8_t** DFA_round8Phase2_1(state_t* y, state_t* y_fault, uint8_t*** KeyHypothesisSet, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3,
	int* PartSize, uint8_t** Key11, int* Size11Ptr, uint8_t** Key12, int* Size12Ptr, uint8_t** Key21, int* Size21Ptr, uint8_t** Key22, int* Size22Ptr) {
	// Spliting the keys set;

	uint8_t** PartialKeySet1 = (uint8_t**)malloc(256 * sizeof(uint8_t*));
	uint8_t** PartialKeySet2 = (uint8_t**)malloc(256 * sizeof(uint8_t*));
	int i, j, k, l;
	int counter11 = 0;
	int counter12 = 0;
	int counter21 = 0;
	int counter22 = 0;
	int PartialKeySize1 = 0;
	int PartialKeySize2 = 0;
	bool duplicate1;
	bool duplicate2;
	for (i = 0; i < *SizeKeySet0; i++) {
		duplicate1 = false;
		for (j = 0; j < PartialKeySize1; j++) {
			if (((PartialKeySet1[j][0] == KeyHypothesisSet[0][i][1] && PartialKeySet1[j][1] == KeyHypothesisSet[0][i][2])
				&& PartialKeySet1[j][2] == KeyHypothesisSet[0][i][3])) {//If k8,k11,;14 are inside PartialKey1, then put the k1 in Key12.
				Key12[counter12] = (uint8_t*)malloc(4 * sizeof(uint8_t));
				Key12[counter12][0] = KeyHypothesisSet[0][i][0];//1
				Key12[counter12][1] = KeyHypothesisSet[0][i][1];//8
				Key12[counter12][2] = KeyHypothesisSet[0][i][2];//11
				Key12[counter12][3] = KeyHypothesisSet[0][i][3];//14
				counter12++;
				duplicate1 = true;
			}
		}

		if (duplicate1 == false) {//k8,k11,;14 are not inside PartialKey1 (new partial subkey) 
			Key11[counter11] = (uint8_t*)malloc(4 * sizeof(uint8_t));
			Key11[counter11][0] = KeyHypothesisSet[0][i][0];//1
			Key11[counter11][1] = KeyHypothesisSet[0][i][1];//8
			Key11[counter11][2] = KeyHypothesisSet[0][i][2];//11
			Key11[counter11][3] = KeyHypothesisSet[0][i][3];//14
			counter11++;

			bool PartDuplicate1 = false;
			for (l = 0; l < PartialKeySize1; l++) {// Make sure no duplicates in PartialKeySet1
				if (PartialKeySet1[l][0] == KeyHypothesisSet[0][i][1] && PartialKeySet1[l][1] == KeyHypothesisSet[0][i][2] && PartialKeySet1[l][2] == KeyHypothesisSet[0][i][3]) {
					printf("There is duplicates in PartialKeySize1");
					PartDuplicate1 = true;
				}
			}


			if (PartDuplicate1 == false) {
				PartialKeySet1[PartialKeySize1] = (uint8_t*)malloc(3 * sizeof(uint8_t));
				PartialKeySet1[PartialKeySize1][0] = KeyHypothesisSet[0][i][1];//8
				PartialKeySet1[PartialKeySize1][1] = KeyHypothesisSet[0][i][2];//11
				PartialKeySet1[PartialKeySize1][2] = KeyHypothesisSet[0][i][3];//14
				PartialKeySize1++;
			}
			
		}
	}

	for (i = 0; i < *SizeKeySet1; i++) {
		duplicate2 = false;
		for (j = 0; j < PartialKeySize2; j++) {
			if (((PartialKeySet2[j][0] == KeyHypothesisSet[1][i][1] && PartialKeySet2[j][1] == KeyHypothesisSet[1][i][2]) &&
				PartialKeySet2[j][2] == KeyHypothesisSet[1][i][3])) {//If k8,k11,;14 are inside PartialKey2, then put the k2 in Key22.
				Key22[counter22] = (uint8_t*)malloc(4 * sizeof(uint8_t));
				Key22[counter22][0] = KeyHypothesisSet[1][i][0];//2
				Key22[counter22][1] = KeyHypothesisSet[1][i][1];//5
				Key22[counter22][2] = KeyHypothesisSet[1][i][2];//12
				Key22[counter22][3] = KeyHypothesisSet[1][i][3];//15
				counter22++;
				duplicate2 = true;
			}
		}

		if (duplicate2 == false) {
			Key21[counter21] = (uint8_t*)malloc(4 * sizeof(uint8_t));
			Key21[counter21][0] = KeyHypothesisSet[1][i][0];//2
			Key21[counter21][1] = KeyHypothesisSet[1][i][1];//5
			Key21[counter21][2] = KeyHypothesisSet[1][i][2];//12
			Key21[counter21][3] = KeyHypothesisSet[1][i][3];//15
			counter21++;
		

			bool PartDuplicate2 = false;
			for (j = 0; j < PartialKeySize2; j++) {// Make sure no duplicates in PartialKeySet2
				//printf("flagpart2 j: %d i: %d\n", j, i);
				if (PartialKeySet2[j][0] == KeyHypothesisSet[1][i][1] && PartialKeySet2[j][1] == KeyHypothesisSet[1][i][2] && PartialKeySet2[j][2] == KeyHypothesisSet[1][i][3]) {
					printf("There is duplicates in PartialKeySize2");
					PartDuplicate2 = true;
				}
			}

			if (PartDuplicate2 == false) {
				//printf("Help3 flagpart2==false\n");
				PartialKeySet2[PartialKeySize2] = (uint8_t*)malloc(3 * sizeof(uint8_t));
				PartialKeySet2[PartialKeySize2][0] = KeyHypothesisSet[1][i][1];//5
				PartialKeySet2[PartialKeySize2][1] = KeyHypothesisSet[1][i][2];//12
				PartialKeySet2[PartialKeySize2][2] = KeyHypothesisSet[1][i][3];//15
				PartialKeySize2++;
			}
		}
	}
	
	printf("PartialKeySize1: %d PartialKeySize2: %d \n", PartialKeySize1, PartialKeySize2);
	printf("Done with splitting \n");

	//Test if it satisfy equation 2 and 3
	int counter = 0;
	uint8_t** PartKey = (uint8_t**)malloc(33554432u * sizeof(uint8_t*)); //k_3,k_4,k_5,k_6,k_7,k_8,k_9, k_10,k_11,k_12,k_13,k_14,k_15,k_16
	
	int column1, column2, column3, column4;

	for (column1 = 0; column1 < PartialKeySize1; column1++) {
		for (column2 = 0; column2 < PartialKeySize2; column2++) {
			for (column3 = 0; column3 < *SizeKeySet2; column3++) {
				for (column4 = 0; column4 < *SizeKeySet3; column4++) {
					
					uint8_t k8 = PartialKeySet1[column1][0];//8
					uint8_t k11 = PartialKeySet1[column1][1];//11
					uint8_t k14 = PartialKeySet1[column1][2];//14

					uint8_t k5 = PartialKeySet2[column2][0];//5
					uint8_t k12 = PartialKeySet2[column2][1];//12
					uint8_t k15 = PartialKeySet2[column2][2];//15


					uint8_t k3 = KeyHypothesisSet[2][column3][0];//3
					uint8_t k6 = KeyHypothesisSet[2][column3][1];//6
					uint8_t k9 = KeyHypothesisSet[2][column3][2];//9
					uint8_t k16 = KeyHypothesisSet[2][column3][3];//16

					uint8_t k4 = KeyHypothesisSet[3][column4][0];//4
					uint8_t k7 = KeyHypothesisSet[3][column4][1];//7
					uint8_t k10 = KeyHypothesisSet[3][column4][2];//10
					uint8_t k13 = KeyHypothesisSet[3][column4][3];//13
					//printf(" k3: %"SCNd32 " k4: %"SCNd32 " \n", k3, k4);
					//printf(" k5: %"SCNd32 " k6: %"SCNd32 " k7: %"SCNd32 " k8: %"SCNd32 " \n", k5, k6, k7, k8);
					//printf(" k9: %"SCNd32 " k10: %"SCNd32 " k11: %"SCNd32 " k12: %"SCNd32 " \n", k9, k10, k11, k12);
					//printf(" k13: %"SCNd32 " k14: %"SCNd32 " k15: %"SCNd32 " k16: %"SCNd32 " \n", k13, k14, k15, k16);

					uint8_t eq2 = InvSBox(times9(InvSBox((*y)[3][0] ^ k13) ^ (k13 ^ k9))
						^ times14(InvSBox((*y)[2][1] ^ k10) ^ (k14 ^ k10))
						^ times11(InvSBox((*y)[1][2] ^ k7) ^ (k15 ^ k11))
						^ times13(InvSBox((*y)[0][3] ^ k4) ^ (k16 ^ k12)))
						^ InvSBox(times9(InvSBox((*y_fault)[3][0] ^ k13) ^ (k13 ^ k9))
							^ times14(InvSBox((*y_fault)[2][1] ^ k10) ^ (k14 ^ k10))
							^ times11(InvSBox((*y_fault)[1][2] ^ k7) ^ (k15 ^ k11))
							^ times13(InvSBox((*y_fault)[0][3] ^ k4) ^ (k16 ^ k12)));

					uint8_t eq3 = InvSBox(times13(InvSBox((*y)[2][0] ^ k9) ^ (k9 ^ k5))
						^ times9(InvSBox((*y)[1][1] ^ k6) ^ (k10 ^ k6))
						^ times14(InvSBox((*y)[0][2] ^ k3) ^ (k11 ^ k7))
						^ times11(InvSBox((*y)[3][3] ^ k16) ^ (k12 ^ k8)))
						^ InvSBox(times13(InvSBox((*y_fault)[2][0] ^ k9) ^ (k9 ^ k5))
							^ times9(InvSBox((*y_fault)[1][1] ^ k6) ^ (k10 ^ k6))
							^ times14(InvSBox((*y_fault)[0][2] ^ k3) ^ (k11 ^ k7))
							^ times11(InvSBox((*y_fault)[3][3] ^ k16) ^ (k12 ^ k8)));

					if (eq2 == eq3) {
						printf("column1: %d column2: %d column3: %d column4: %d \n", column1, column2, column3, column4);
						PartKey[counter] = (uint8_t*)malloc(14 * sizeof(uint8_t));
						PartKey[counter][0] = k3;//3
						PartKey[counter][1] = k4;//4
						PartKey[counter][2] = k5;//5
						PartKey[counter][3] = k6;//6
						PartKey[counter][4] = k7;//7
						PartKey[counter][5] = k8;//8
						PartKey[counter][6] = k9;//9
						PartKey[counter][7] = k10;//10
						PartKey[counter][8] = k11;//11
						PartKey[counter][9] = k12;//12
						PartKey[counter][10] = k13;//13
						PartKey[counter][11] = k14;//14
						PartKey[counter][12] = k15;//15
						PartKey[counter][13] = k16;//16
						counter++;
					}
				}
			}
		}
	}

	printf("Phase2.1 Intensive Part ends \n");

	/// Free PartialKey1 and PartialKey2 and KeyHypothesis
	for (k = 0; k < PartialKeySize1; k++) {
		free(PartialKeySet1[k]);
	}
	for (k = 0; k < PartialKeySize2; k++) {
		free(PartialKeySet2[k]);
	}
	free(PartialKeySet1);
	free(PartialKeySet2);

	//Allocate all the size
	*PartSize = counter;
	*Size11Ptr = counter11;
	*Size12Ptr = counter12;
	*Size21Ptr = counter21;
	*Size22Ptr = counter22; 
	return PartKey;
}

uint8_t** DFA_round8Phase2_2(state_t* y, state_t* y_fault, uint8_t** PartKey, int* PartSize, 
	uint8_t** Key11, int* Size11, uint8_t** Key12, int* Size12, uint8_t** Key21, int* Size21, uint8_t** Key22, int* Size22,int* FinalSize) {
	uint8_t **Results1 = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	uint8_t **Results2 = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	uint8_t **Results3 = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	uint8_t **Results4 = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	int SaveSize1 = 0;
	int SaveSize2 = 0;
	int SaveSize3 = 0;
	int SaveSize4 = 0;
	int* SaveSizePtr1, * SaveSizePtr2, * SaveSizePtr3, * SaveSizePtr4;
	SaveSizePtr1 = &SaveSize1;
	SaveSizePtr2 = &SaveSize2;
	SaveSizePtr3 = &SaveSize3;
	SaveSizePtr4 = &SaveSize4;

	//Parrallel Program second test
	omp_set_num_threads(4);
	#pragma omp parallel 
	{	printf("Help12 num of thread: %d \n", omp_get_num_threads());
		
		if (omp_get_thread_num() == 0) {
			Results1 = equation1and4(y, y_fault, Key11, Size11, Key21, Size21, PartKey, PartSize, SaveSizePtr1, 0);
		}
		if (omp_get_thread_num() == 1) {
			Results2 = equation1and4(y, y_fault, Key12, Size12, Key21, Size21, PartKey, PartSize, SaveSizePtr2, 1);
		}
		if (omp_get_thread_num() == 2) {
			Results3 = equation1and4(y, y_fault, Key11, Size11, Key22, Size22, PartKey, PartSize, SaveSizePtr3, 2);
		}
		if (omp_get_thread_num() == 3) {
			Results4 = equation1and4(y, y_fault, Key12, Size12, Key22, Size22, PartKey, PartSize, SaveSizePtr4, 3);
		}
	}
	
	//Free PartKey
	int i,j;
	for (i = 0; i < *PartSize; i++) {
		free(PartKey[i]);
	}
	free(PartKey);
	printf("SaveSize1 outside: %d \n", *SaveSizePtr1);
	printf("SaveSize2 outside: %d \n", *SaveSizePtr2);
	printf("SaveSize3 outside: %d \n", *SaveSizePtr3);
	printf("SaveSize4 outside: %d \n", *SaveSizePtr4);

	//Consolidate into one Final Key Set
	uint8_t **FinalKey = (uint8_t **)malloc(5000000 *sizeof(uint8_t *));
	int FinalCounter = 0;
	for (i = 0; i < SaveSize1; i++) {
		bool flag1 = false;
		for (j = 0; j < FinalCounter; j++) {
			if (FinalKey[j][0] == Results1[i][0] && FinalKey[j][1] == Results1[i][1] && FinalKey[j][2] == Results1[i][2] && FinalKey[j][3] == Results1[i][3] &&
				FinalKey[j][4] == Results1[i][4] && FinalKey[j][5] == Results1[i][5] && FinalKey[j][6] == Results1[i][6] && FinalKey[j][7] == Results1[i][7] &&
				FinalKey[j][8] == Results1[i][8] && FinalKey[j][9] == Results1[i][9] && FinalKey[j][10] == Results1[i][10] && FinalKey[j][11] == Results1[i][11] &&
				FinalKey[j][12] == Results1[i][12] && FinalKey[j][13] == Results1[i][13] && FinalKey[j][14] == Results1[i][14] && FinalKey[j][15] == Results1[i][15]) {
				printf("There is duplicates in Result1");
				flag1 = true;
			}
		}
		if (flag1 == false) {
			FinalKey[FinalCounter] = Results1[i];
			FinalCounter++;
		}
	}
	printf("FinalCounter1: %d \n", FinalCounter);
	//printf("Help19 \n");	
	for (i = 0; i < SaveSize2; i++) {
		bool flag1 = false;
		for (j = 0; j < FinalCounter; j++) {
			if (FinalKey[j][0] == Results2[i][0] && FinalKey[j][1] == Results2[i][1] && FinalKey[j][2] == Results2[i][2] && FinalKey[j][3] == Results2[i][3] &&
				FinalKey[j][4] == Results2[i][4] && FinalKey[j][5] == Results2[i][5] && FinalKey[j][6] == Results2[i][6] && FinalKey[j][7] == Results2[i][7] &&
				FinalKey[j][8] == Results2[i][8] && FinalKey[j][9] == Results2[i][9] && FinalKey[j][10] == Results2[i][10] && FinalKey[j][11] == Results2[i][11] &&
				FinalKey[j][12] == Results2[i][12] && FinalKey[j][13] == Results2[i][13] && FinalKey[j][14] == Results2[i][14] && FinalKey[j][15] == Results2[i][15]) {
				printf("There is duplicates in Result2");
				flag1 = true;
			}
		}
		if (flag1 == false) {
			FinalKey[FinalCounter] = Results2[i];
			FinalCounter++;
		}
	}
	printf("FinalCounter2: %d \n", FinalCounter);
	for (i = 0; i < SaveSize3; i++) {
		bool flag1 = false;
		for (j = 0; j < FinalCounter; j++) {
			if (FinalKey[j][0] == Results3[i][0] && FinalKey[j][1] == Results3[i][1] && FinalKey[j][2] == Results3[i][2] && FinalKey[j][3] == Results3[i][3] &&
				FinalKey[j][4] == Results3[i][4] && FinalKey[j][5] == Results3[i][5] && FinalKey[j][6] == Results3[i][6] && FinalKey[j][7] == Results3[i][7] &&
				FinalKey[j][8] == Results3[i][8] && FinalKey[j][9] == Results3[i][9] && FinalKey[j][10] == Results3[i][10] && FinalKey[j][11] == Results3[i][11] &&
				FinalKey[j][12] == Results3[i][12] && FinalKey[j][13] == Results3[i][13] && FinalKey[j][14] == Results3[i][14] && FinalKey[j][15] == Results3[i][15]) {
				printf("There is duplicates in Result3");
				flag1 = true;
			}
		}
		if (flag1 == false) {
			FinalKey[FinalCounter] = Results3[i];
			FinalCounter++;
		}
	}
	printf("FinalCounter3: %d \n", FinalCounter);
	for (i = 0; i < SaveSize4; i++) {
		bool flag1 = false;
		for (j = 0; j < FinalCounter; j++) {
			if (FinalKey[j][0] == Results4[i][0] && FinalKey[j][1] == Results4[i][1] && FinalKey[j][2] == Results4[i][2] && FinalKey[j][3] == Results4[i][3] &&
				FinalKey[j][4] == Results4[i][4] && FinalKey[j][5] == Results4[i][5] && FinalKey[j][6] == Results4[i][6] && FinalKey[j][7] == Results4[i][7] &&
				FinalKey[j][8] == Results4[i][8] && FinalKey[j][9] == Results4[i][9] && FinalKey[j][10] == Results4[i][10] && FinalKey[j][11] == Results4[i][11] &&
				FinalKey[j][12] == Results4[i][12] && FinalKey[j][13] == Results4[i][13] && FinalKey[j][14] == Results4[i][14] && FinalKey[j][15] == Results4[i][15]) {
				printf("There is duplicates in Result4");
				flag1 = true;
			}
		}
		if (flag1 == false) {
			FinalKey[FinalCounter] = Results4[i];
			FinalCounter++;
		}

	}
	//printf("Help20 \n");
	*FinalSize = FinalCounter;
	printf("FinalSize Inside: %d \n", FinalCounter);

	return FinalKey;
}

void WriteFileKeyHypothesis(uint8_t*** KeyHypothesis, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3, FILE* fptr) {
	int i;

	fprintf(fptr, "%d\n", *SizeKeySet0);
	fprintf(fptr, "%d\n", *SizeKeySet1);
	fprintf(fptr, "%d\n", *SizeKeySet2);
	fprintf(fptr, "%d\n", *SizeKeySet3);

	int Size0 = *SizeKeySet0;
	for (i = 0; i < Size0 ; i++) { 
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][0]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][1]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][2]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][3]);
	}
	int Size1 = *SizeKeySet1;
	for (i = 0; i < Size1; i++) {
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][0]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][1]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][2]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][3]);
	}
	int Size2 = *SizeKeySet2;
	for (i = 0; i < Size2; i++) {
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][0]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][1]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][2]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][3]);
	}
	int Size3 = *SizeKeySet3;
	for (i = 0; i < Size3; i++) {
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][0]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][1]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][2]);
		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][3]);
	}

}

void ReadFileKeyHypothesis(uint8_t*** KeyHypothesisSet, int* SizeKeySet0,int *SizeKeySet1, int *SizeKeySet2, int *SizeKeySet3 ,FILE* fptr) {

	fscanf_s(fptr, "%d", SizeKeySet0);
	printf("Size0: %d \n", *SizeKeySet0);
	fscanf_s(fptr, "%d", SizeKeySet1);
	printf("Size1: %d \n", *SizeKeySet1);
	fscanf_s(fptr, "%d", SizeKeySet2);
	printf("Size2: %d \n", *SizeKeySet2);
	fscanf_s(fptr, "%d", SizeKeySet3);
	printf("Size3: %d \n", *SizeKeySet3);

	printf("Time to start reading. \n");
	int i, j, k, l;
	for (i = 0; i < *SizeKeySet0; i++) {
		KeyHypothesisSet[0][i] = (uint8_t*)malloc(512 * sizeof(uint8_t));
		//printf("i: %d \n", i);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][0]);
		//printf("%"SCNu8 "\n", KeyHypothesisSet[0][i][0]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][1]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][1]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][2]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][2]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][3]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][3]);
	}
	for (j = 0; j < *SizeKeySet1; j++) {
		//printf("j: %d \n", j);
		KeyHypothesisSet[1][j] = (uint8_t*)malloc(512 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][0]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][1]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][2]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][3]);
	}
	for (k = 0; k < *SizeKeySet2; k++) {
		//printf("k: %d \n", k);
		KeyHypothesisSet[2][k] = (uint8_t*)malloc(512 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][0]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][1]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][2]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][3]);

	}
	for (l = 0; l < *SizeKeySet3; l++) {
		//printf("l: %d \n", l);
		KeyHypothesisSet[3][l] = (uint8_t*)malloc(512 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][0]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][0]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][1]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][1]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][2]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][2]);
		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][3]);
		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][3]);
	}

}


void WriteFilePartKey(uint8_t** PartKey, int* PartSize, FILE* fptr) {
	int i;
	fprintf(fptr, "%d\n", *PartSize);

	int Size = *PartSize;
	for (i = 0; i < Size; i++) {
		
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][0]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][1]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][2]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][3]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][4]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][5]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][6]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][7]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][8]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][9]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][10]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][11]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][12]);
		fprintf(fptr, "%"SCNd32"\n", PartKey[i][13]);
	}
}

void ReadFilePartKey(uint8_t** PartKey, int* PartSize, FILE* fptr) {
	//Note: The PartSize is read outside for PartKey to be initialised.
	printf("Time to start reading. \n");
	int i;
	for (i = 0; i < *PartSize; i++) {
		//printf("i: %d \n", i);
		PartKey[i] = (uint8_t*)malloc(14 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][0]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][1]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][2]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][3]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][4]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][5]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][6]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][7]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][8]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][9]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][10]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][11]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][12]);
		fscanf_s(fptr, "%"SCNu8, &PartKey[i][13]);

	}
}



void WriteFileFinalKey(uint8_t** FinalKey, int* FinalSize, FILE* fptr) {
	int i;
	fprintf(fptr, "%d\n", *FinalSize);

	int Size = *FinalSize;
	for (i = 0; i < Size; i++) {
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][0]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][1]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][2]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][3]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][4]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][5]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][6]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][7]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][8]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][9]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][10]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][11]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][12]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][13]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][14]);
		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][15]);
	}
}

void ReadFileFinalKey(uint8_t** FinalKey, int* FinalSize, FILE* fptr) {
	//Note: The FinalSize is read outside for FinalKey to be initialised.
	printf("Time to start reading. \n");
	int i;
	for (i = 0; i < *FinalSize; i++) {
		FinalKey[i] = (uint8_t*)malloc(14 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][0]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][1]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][2]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][3]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][4]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][5]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][6]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][7]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][8]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][9]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][10]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][11]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][12]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][13]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][14]);
		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][15]);
	}
}


void WriteFileKeyArray(uint8_t** Key, int* SizePtr, FILE* fptr) {
	int i;
	fprintf(fptr, "%d\n", *SizePtr);
	for (i = 0; i < *SizePtr; i++) {
		fprintf(fptr, "%"SCNd32"\n", Key[i][0]);
		fprintf(fptr, "%"SCNd32"\n", Key[i][1]);
		fprintf(fptr, "%"SCNd32"\n", Key[i][2]);
		fprintf(fptr, "%"SCNd32"\n", Key[i][3]);
	}
}

void ReadFileKeyArray(uint8_t** Key, int* SizePtr, FILE* fptr) {
	//Note: The FinalSize is read outside for FinalKey to be initialised.
	printf("Time to start reading. \n");
	int i;
	for (i = 0; i < *SizePtr; i++) {
		Key[i] = (uint8_t*)malloc(4 * sizeof(uint8_t));
		fscanf_s(fptr, "%"SCNu8, &Key[i][0]);
		fscanf_s(fptr, "%"SCNu8, &Key[i][1]);
		fscanf_s(fptr, "%"SCNu8, &Key[i][2]);
		fscanf_s(fptr, "%"SCNu8, &Key[i][3]);
	}
}



int main() {

	state_t MasterKey = {{0x68, 0x98, 0x10, 0xd4},{0xd5, 0x30, 0x5b, 0xa5},{0x20, 0x8c, 0xbc, 0xd3},{0xab, 0x3c, 0x83, 0x53}};
	state_t* MasKeyPtr = &MasterKey;
	state_t matrix1 = { {0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53} };
	state_t matrix2 = { {0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53} };

	state_t* ptrMatrix1 = &matrix1;
	state_t* ptrMatrix2 = &matrix2;


	printf("Original Text1: \n");
	PrintMatrix(ptrMatrix1);


	state_t* ciphertext;
	ciphertext = AESEncryption(ptrMatrix1, MasKeyPtr);
	printf("Encrypted Text: \n");
	PrintMatrix(ciphertext);

	state_t* ciphertextFaulty;
	ciphertextFaulty = AESEncryptionFaultyROUND8(ptrMatrix2, MasKeyPtr);
	printf("Faulty Encrypted Text: \n");
	PrintMatrix(ciphertextFaulty);

	
	int* SizeKeySet0, *SizeKeySet1, *SizeKeySet2, *SizeKeySet3;
	int Size0 = 0;
	int Size1 = 0;
	int Size2 = 0;
	int Size3 = 0;
	SizeKeySet0 = &Size0;
	SizeKeySet1 = &Size1;
	SizeKeySet2 = &Size2;
	SizeKeySet3 = &Size3;
	FILE* fptr_time;
	errno_t err_time;
	err_time = fopen_s(&fptr_time, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Time.txt", "w+");
	
	/************************************************ PHASE 1 **********************************************************************/
	printf("Going into DFAPhase1: \n");
	clock_t begin_1 = clock();
	uint8_t ***KeyHypothesisSet = DFA_round8Phase1(ciphertext, ciphertextFaulty, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3);
	clock_t end_1 = clock();
	double time_spent_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
	printf("time in sec: %f \n", time_spent_1);
	printf("Going out of DFAPhase1: \n");
	printf("Size0 Outside: %d \n", Size0);
	printf("Size1 Outside: %d \n", Size1);
	printf("Size2 Outside: %d \n", Size2);
	printf("Size3 Outside: %d \n", Size3);
	fprintf(fptr_time, "Time spent 1: %lf \n", time_spent_1);
	FILE* fptr;
	errno_t err;
	err = fopen_s(&fptr, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Phase1KeyHypothesis.txt", "w");

	if (err == 0) {
		printf("The file'Phase1KeyHypothesis.txt was opened\n");
	}
	else {
		printf("The file 'Phase1KeyHypothesis.txt' was not opened\n");
	}
	WriteFileKeyHypothesis(KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, fptr);
	fclose(fptr);


	/************************************************ PHASE 2.1 **********************************************************************/
	/************************************************ Initialise KeyHypothesisSet **********************************************************************/
	//uint8_t*** KeyHypothesisSet = (uint8_t***)malloc(4 * sizeof(uint8_t**));
	//KeyHypothesisSet[0] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_1,k_8,k_11,k_14
	//KeyHypothesisSet[1] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_2,k_5,k_12,k_15
	//KeyHypothesisSet[2] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_3,k_6,k_9,k_16
	//KeyHypothesisSet[3] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_4,k_7,k_10,k_13
	///************************************************* Read file for KeyHypothesisSet **********************************************/
	//FILE* fptr;
	//errno_t err;
	//err = fopen_s(&fptr, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Phase1KeyHypothesis.txt", "r");
	//if (err == 0) {
	//	printf("The file'Phase1KeyHypothesis.txt was opened\n");
	//} else {
	//	printf("The file 'Phase1KeyHypothesis.txt' was not opened\n");
	//}
	//ReadFileKeyHypothesis(KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, fptr);
	//fclose(fptr);
	///************************************************ Apply PHASE 2.1 **********************************************************************/
	printf("Going into DFAPhase2_1: \n");
	uint8_t** Key11 = (uint8_t**)malloc(256 * sizeof(uint8_t*));;//Put outside
	uint8_t** Key12 = (uint8_t**)malloc(256 * sizeof(uint8_t*));;
	uint8_t** Key21 = (uint8_t**)malloc(256 * sizeof(uint8_t*));;
	uint8_t** Key22 = (uint8_t**)malloc(256 * sizeof(uint8_t*));;
	int* Size11Ptr, * Size12Ptr, * Size21Ptr, * Size22Ptr;
	int Size11 = 0;
	int Size12 = 0;
	int Size21 = 0;
	int Size22 = 0;
	Size11Ptr = &Size11;
	Size12Ptr = &Size12;
	Size21Ptr = &Size21;
	Size22Ptr = &Size22;
	int* PartSize;
	int Part = 0;
	PartSize = &Part;

	clock_t begin_2 = clock();
	uint8_t **PartKey = DFA_round8Phase2_1(ciphertext, ciphertextFaulty, KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, PartSize,
		Key11, Size11Ptr, Key12, Size12Ptr, Key21, Size21Ptr, Key22, Size22Ptr);
	clock_t end_2 = clock();
	double time_spent_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
	printf("time in sec: %f", time_spent_2);
	fprintf(fptr_time, "Time spent 2: %f \n", time_spent_2);
	printf(" PartSize: %d \n", *PartSize);
	printf("Going out of DFAPhase2_1: \n"); 
	//Freeing KeyHypothesisSet
	int i;
	for (i = 0; i < *SizeKeySet0; i++) {
		free(KeyHypothesisSet[0][i]);
	}
	for (i = 0; i < *SizeKeySet1; i++) {
		free(KeyHypothesisSet[1][i]);
	}
	for (i = 0; i < *SizeKeySet2; i++) {
		free(KeyHypothesisSet[2][i]);
	}
	for (i = 0; i < *SizeKeySet3; i++) {
		free(KeyHypothesisSet[3][i]);
	}
	free(KeyHypothesisSet[0]);
	free(KeyHypothesisSet[1]);
	free(KeyHypothesisSet[2]);
	free(KeyHypothesisSet[3]);
	free(KeyHypothesisSet);

	printf("Size11Ptr: %d Size12Ptr: %d Size21Ptr: %d Size22Ptr: %d \n", *Size11Ptr, *Size12Ptr, *Size21Ptr, *Size22Ptr);
	///************************************************* Write file for PartKey **********************************************/
	FILE* fptr2;
	errno_t err2;
	err2 = fopen_s(&fptr2, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Phase2PartKey.txt", "w");

	if (err2 == 0) {
		printf("The file'Phase2PartKey.txt was opened\n");
	} else {
		printf("The file 'Phase2PartKey.txt' was not opened\n");
	}
	WriteFilePartKey(PartKey, PartSize, fptr2);
	fclose(fptr2);
	printf("The file 'Phase2PartKey.txt' closed\n");
	/************************************************* Write file for Key11, Key12, Key21 and Key22 **********************************************/
	FILE* fptr2_11;
	errno_t err2_11;
	err2_11 = fopen_s(&fptr2_11, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key11.txt", "w");

	if (err2_11 == 0) {
		printf("The file'Key11.txt' was opened\n");
	} else {
		printf("The file 'Key11.txt' was not opened\n");
	}
	WriteFileKeyArray(Key11, Size11Ptr, fptr2_11);
	fclose(fptr2_11);
	printf("The file 'Key11.txt' closed\n");

	FILE* fptr2_12;
	errno_t err2_12;
	err2_12 = fopen_s(&fptr2_12, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key12.txt", "w");

	if (err2_12 == 0) {
		printf("The file'Key12.txt' was opened\n");
	}
	else {
		printf("The file 'Key12.txt' was not opened\n");
	}
	WriteFileKeyArray(Key12, Size12Ptr, fptr2_12);
	fclose(fptr2_12);
	printf("The file 'Key12.txt' closed\n");

	FILE* fptr2_21;
	errno_t err2_21;
	err2_21 = fopen_s(&fptr2_21, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key21.txt", "w");

	if (err2_21 == 0) {
		printf("The file'Key21.txt' was opened\n");
	}
	else {
		printf("The file 'Key21.txt' was not opened\n");
	}
	WriteFileKeyArray(Key21, Size21Ptr, fptr2_21);
	fclose(fptr2_21);
	printf("The file 'Key21.txt' closed\n");

	FILE* fptr2_22;
	errno_t err2_22;
	err2_22 = fopen_s(&fptr2_22, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key22.txt", "w");

	if (err2_22 == 0) {
		printf("The file'Key22.txt' was opened\n");
	}
	else {
		printf("The file 'Key22.txt' was not opened\n");
	}
	WriteFileKeyArray(Key22, Size22Ptr, fptr2_22);
	fclose(fptr2_22);
	printf("The file 'Key22.txt' closed\n");







	/************************************************ PHASE 2.2 **********************************************************************/
	
	/************************************************* Read file for PartKey **********************************************/
	//FILE* fptr3;
	//errno_t err3;
	//err3 = fopen_s(&fptr3, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Phase2PartKey.txt", "r");
	//if (err3 == 0) {
	//	printf("The file'Phase2PartKey.txt was opened\n");
	//}
	//else {
	//	printf("The file 'Phase2PartKey.txt' was not opened\n");
	//}
	//int* PartSize; 
	//int Part = 0;
	//PartSize = &Part;
	//fscanf_s(fptr3, "%d", PartSize);
	//printf("PartSize: %d \n", *PartSize);
	//uint8_t** PartKey= (uint8_t**)malloc((*PartSize) * sizeof(uint8_t*));
	//ReadFilePartKey(PartKey,PartSize,fptr3);
	//fclose(fptr3);

	///************************************************* Read file for Key11**********************************************/

	//FILE* fptr3_11;
	//errno_t err3_11;
	//err3_11 = fopen_s(&fptr3_11, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key11.txt", "r");
	//if (err3_11 == 0) {
	//	printf("The file'Key11.txt.txt was opened\n");
	//}
	//else {
	//	printf("The file 'Key11.txt.txt' was not opened\n");
	//}
	//int* Size11Ptr;
	//int Size11 = 0;
	//Size11Ptr = &Size11;
	//fscanf_s(fptr3_11, "%d", Size11Ptr);
	//printf("Size11: %d \n", *Size11Ptr);
	//
	//uint8_t** Key11 = (uint8_t**)malloc(Size11 * sizeof(uint8_t*));
	//ReadFileKeyArray(Key11, Size11Ptr, fptr3_11);
	//fclose(fptr3_11);
	///************************************************* Read file for Key12**********************************************/
	//FILE* fptr3_12;
	//errno_t err3_12;
	//err3_12 = fopen_s(&fptr3_12, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key12.txt", "r");
	//if (err3_12 == 0) {
	//	printf("The file'Key12.txt.txt was opened\n");
	//}
	//else {
	//	printf("The file 'Key12.txt.txt' was not opened\n");
	//}
	//int* Size12Ptr;
	//int Size12 = 0;
	//Size12Ptr = &Size12;
	//fscanf_s(fptr3_12, "%d", Size12Ptr);
	//printf("Size12: %d \n", *Size12Ptr);
	//uint8_t** Key12 = (uint8_t**)malloc(Size12 * sizeof(uint8_t*));
	//ReadFileKeyArray(Key12, Size12Ptr, fptr3_12);
	//fclose(fptr3_12);
	///************************************************* Read file for Key21**********************************************/
	//FILE* fptr3_21;
	//errno_t err3_21;
	//err3_21 = fopen_s(&fptr3_21, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key21.txt", "r");
	//if (err3_21 == 0) {
	//	printf("The file'Key21.txt.txt was opened\n");
	//}
	//else {
	//	printf("The file 'Key21.txt.txt' was not opened\n");
	//}
	//int* Size21Ptr;
	//int Size21 = 0;
	//Size21Ptr = &Size21;
	//fscanf_s(fptr3_21, "%d", Size21Ptr);
	//printf("Size21: %d \n", *Size21Ptr);
	//uint8_t** Key21 = (uint8_t**)malloc(Size21 * sizeof(uint8_t*));
	//ReadFileKeyArray(Key21, Size21Ptr, fptr3_21);
	//fclose(fptr3_21);
	///************************************************* Read file for Key22**********************************************/
	//FILE* fptr3_22;
	//errno_t err3_22;
	//err3_22 = fopen_s(&fptr3_22, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Key22.txt", "r");
	//if (err3_22 == 0) {
	//	printf("The file'Key22.txt.txt was opened\n");
	//}
	//else {
	//	printf("The file 'Key22.txt.txt' was not opened\n");
	//}
	//int* Size22Ptr;
	//int Size22 = 0;
	//Size22Ptr = &Size22;
	//fscanf_s(fptr3_22, "%d", Size22Ptr);
	//printf("Size22: %d \n", *Size22Ptr);
	//uint8_t** Key22 = (uint8_t**)malloc(Size22 * sizeof(uint8_t*));
	//ReadFileKeyArray(Key22, Size22Ptr, fptr3_22);
	//fclose(fptr3_22);


	///************************************************ Applying Phase 2.2 **********************************************************************/
	printf("Going in of DFAPhase2_2: \n");
	int* FinalSize;
	int Final = 0;
	FinalSize = &Final;
	clock_t begin_3 = clock();
	uint8_t **FinalKeyHypothesis = DFA_round8Phase2_2(ciphertext, ciphertextFaulty, PartKey, PartSize,
		Key11, Size11Ptr, Key12, Size12Ptr, Key21, Size21Ptr, Key22, Size22Ptr, FinalSize);
	clock_t end_3 = clock();
	double time_spent_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
	printf("time in sec: %f \n", time_spent_3);// ~4359 sec
	//fprintf(fptr_time, "Time spent 3: %f \n", time_spent_3);
	printf("Going out of DFAPhase2_2: \n");

	///************************************************* Write file for FinalKey **********************************************/
	FILE* fptr4;
	errno_t err4;
	err4 = fopen_s(&fptr4, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test2\\Phase2FinalKey.txt", "w");

	if (err4 == 0) {
		printf("The file'Phase2FinalKey.txt was opened\n");
	}
	else {
		printf("The file 'Phase2FinalKey.txt' was not opened\n");
	}
	WriteFileFinalKey(FinalKeyHypothesis, FinalSize, fptr4);
	fclose(fptr4);
	

	free(Key11);
	free(Key12);
	free(Key21);
	free(Key22);





	/************************************************TESTING **********************************************************************/
	//Check if the actual key in Round 10 is inside. 

	
	//Key Schedule
	uint8_t** W;
	W = CreateKeys(MasKeyPtr);
	
	state_t key = {{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00}};
	state_t* keyptr = &key;
	RoundKey(W, 10 , keyptr);
	//PrintMatrix(ptrMatrix1);
	/************************************************TESTING PHASE 1 **********************************************************************/
	//uint8_t*** KeyHypothesisSet = (uint8_t***)malloc(4 * sizeof(uint8_t**));
	//KeyHypothesisSet[0] = (uint8_t**)malloc(512 * sizeof(uint8_t*)); // For key k_1,k_8,k_11,k_14
	//KeyHypothesisSet[1] = (uint8_t**)malloc(512 * sizeof(uint8_t*)); // For key k_2,k_5,k_12,k_15
	//KeyHypothesisSet[2] = (uint8_t**)malloc(512 * sizeof(uint8_t*)); // For key k_3,k_6,k_9,k_16
	//KeyHypothesisSet[3] = (uint8_t**)malloc(512 * sizeof(uint8_t*)); // For key k_4,k_7,k_10,k_13
	///************************************************* Read file for KeyHypothesisSet **********************************************/
	//FILE* fptr;
	//errno_t err;
	//err = fopen_s(&fptr, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Phase1KeyHypothesis.txt", "r");
	//if (err == 0) {
	//	printf("The file'Phase1KeyHypothesis.txt was opened\n");
	//} else {
	//	printf("The file 'Phase1KeyHypothesis.txt' was not opened\n");
	//}
	//ReadFileKeyHypothesis(KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, fptr);
	//fclose(fptr);
	/////************************************************* Check Phase 1 **********************************************/
	//int j;
	//printf("SizeKeySet0: %d \n", *SizeKeySet0);
	//printf("SizeKeySet1: %d \n", *SizeKeySet1);
	//printf("SizeKeySet2: %d \n", *SizeKeySet2);
	//printf("SizeKeySet3: %d \n", *SizeKeySet3);
	//printf("going in to test phase 1 \n");
	//for (j = 0; j < *SizeKeySet0; j++) {
	//	if ((((KeyHypothesisSet[0][j][0] == (*keyptr)[0][0] && KeyHypothesisSet[0][j][1] == (*keyptr)[1][3])
	//		&& KeyHypothesisSet[0][j][2] == (*keyptr)[2][2])
	//		&& KeyHypothesisSet[0][j][3] == (*keyptr)[3][1])) {
	//		printf("Hurray 1 \n");
	//	}
	//}
	//for (j = 0; j < *SizeKeySet1; j++) {
	//	if ((((KeyHypothesisSet[1][j][0] == (*keyptr)[0][1] && KeyHypothesisSet[1][j][1] == (*keyptr)[1][0])
	//		&& KeyHypothesisSet[1][j][2] == (*keyptr)[2][3])
	//		&& KeyHypothesisSet[1][j][3] == (*keyptr)[3][2])) {
	//		printf("Hurray 2 \n");
	//	}
	//}
	//for (j = 0; j < *SizeKeySet2; j++) {
	//	if ((((KeyHypothesisSet[2][j][0] == (*keyptr)[0][2] && KeyHypothesisSet[2][j][1] == (*keyptr)[1][1])
	//		&& KeyHypothesisSet[2][j][2] == (*keyptr)[2][0])
	//		&& KeyHypothesisSet[2][j][3] == (*keyptr)[3][3])) {
	//		printf("Hurray 3 \n");
	//	}
	//}
	//for (j = 0; j < *SizeKeySet3; j++) {
	//	if ((((KeyHypothesisSet[3][j][0] == (*keyptr)[0][3] && KeyHypothesisSet[3][j][1] == (*keyptr)[1][2])
	//		&& KeyHypothesisSet[3][j][2] == (*keyptr)[2][1])
	//		&& KeyHypothesisSet[3][j][3] == (*keyptr)[3][0])) {
	//		printf("Hurray 4 \n");
	//	}
	//}

	/********************************** Misc. Stuff when checking phase1*****************************/
	//state_t* y, *y_fault;
	//y = ciphertext;
	//y_fault = ciphertextFaulty;

	//uint8_t f1 = InvSBox((*y)[3][1] ^ (*keyptr)[3][1]) ^ InvSBox((*y_fault)[3][1] ^ (*keyptr)[3][1]);  // 14
	//uint8_t eq_1 = InvSBox((*y)[2][2] ^ (*keyptr)[2][2]) ^ InvSBox((*y_fault)[2][2] ^ (*keyptr)[2][2]); //11
	//uint8_t eq_2 = InvSBox((*y)[0][0] ^ (*keyptr)[0][0]) ^ InvSBox((*y_fault)[0][0] ^ (*keyptr)[0][0]); //1
	//uint8_t eq_3 = InvSBox((*y)[1][3] ^ (*keyptr)[1][3]) ^ InvSBox((*y_fault)[1][3] ^ (*keyptr)[1][3]); //8
	//uint8_t twof1 = xtimes(f1);
	//uint8_t threef1 = xtimes(f1) ^ f1;
	//printf("f1: %"SCNd32 " eq_1: %"SCNd32 " eq_2: %"SCNd32 " eq_3: %"SCNd32 "\n", f1, eq_1, eq_2, eq_3);
	//printf("twof1: %"SCNd32 " threef1: %"SCNd32 "\n", twof1, threef1);

	//uint8_t f2 = InvSBox((*y)[1][0] ^ (*keyptr)[1][0]) ^ InvSBox((*y_fault)[1][0] ^ (*keyptr)[1][0]);  //5
	//eq_1 = InvSBox((*y)[0][1] ^ (*keyptr)[0][1]) ^ InvSBox((*y_fault)[0][1] ^ (*keyptr)[0][1]); //2
	//eq_2 = InvSBox((*y)[2][3] ^ (*keyptr)[2][3]) ^ InvSBox((*y_fault)[2][3] ^ (*keyptr)[2][3]); //12
	//eq_3 = InvSBox((*y)[3][2] ^ (*keyptr)[3][2]) ^ InvSBox((*y_fault)[3][2] ^ (*keyptr)[3][2]); //15
	//uint8_t twof2 = xtimes(f2);
	//uint8_t threef2 = xtimes(f2) ^ f2;
	//printf("f2: %"SCNd32 " eq_1: %"SCNd32 " eq_2: %"SCNd32 " eq_3: %"SCNd32 "\n", f2, eq_1, eq_2, eq_3);
	//printf("twof2: %"SCNd32 " threef2: %"SCNd32 "\n", twof2, threef2);

	//uint8_t f3 = InvSBox((*y)[2][0] ^ (*keyptr)[2][0]) ^ InvSBox((*y_fault)[2][0] ^ (*keyptr)[2][0]);  //9
	//eq_1 = InvSBox((*y)[3][3] ^ (*keyptr)[3][3]) ^ InvSBox((*y_fault)[3][3] ^ (*keyptr)[3][3]); //16
	//eq_2 = InvSBox((*y)[0][2] ^ (*keyptr)[0][2]) ^ InvSBox((*y_fault)[0][2] ^ (*keyptr)[0][2]); //3
	//eq_3 = InvSBox((*y)[1][1] ^ (*keyptr)[1][1]) ^ InvSBox((*y_fault)[1][1] ^ (*keyptr)[1][1]); //6
	//uint8_t twof3 = xtimes(f3);
	//uint8_t threef3 = xtimes(f3) ^ f3;
	//printf("f3: %"SCNd32 " eq_1: %"SCNd32 " eq_2: %"SCNd32 " eq_3: %"SCNd32 "\n", f3, eq_1, eq_2, eq_3);
	//printf("twof3: %"SCNd32 " threef3: %"SCNd32 "\n", twof3, threef3);

	//uint8_t f4 = InvSBox((*y)[0][3] ^ (*keyptr)[0][3]) ^ InvSBox((*y_fault)[0][3] ^ (*keyptr)[0][3]);  //4
	//eq_1 = InvSBox((*y)[1][2] ^ (*keyptr)[1][2]) ^ InvSBox((*y_fault)[1][2] ^ (*keyptr)[1][2]); //7
	//eq_2 = InvSBox((*y)[2][1] ^ (*keyptr)[2][1]) ^ InvSBox((*y_fault)[2][1] ^ (*keyptr)[2][1]); //10
	//eq_3 = InvSBox((*y)[3][0] ^ (*keyptr)[3][0]) ^ InvSBox((*y_fault)[3][0] ^ (*keyptr)[3][0]); //13
	//uint8_t twof4 = xtimes(f4);
	//uint8_t threef4 = xtimes(f4) ^ f4;
	//printf("f4: %"SCNd32 " eq_1: %"SCNd32 " eq_2: %"SCNd32 " eq_3: %"SCNd32 "\n", f4, eq_1, eq_2, eq_3);
	//printf("twof4: %"SCNd32 " threef4: %"SCNd32 "\n", twof4, threef4);


	/************************************************TESTING PHASE 2.1 **********************************************************************/
	/*FILE* fptr3;
	errno_t err3;
	err3 = fopen_s(&fptr3, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase2PartKey.txt", "r");
	if (err3 == 0) {
		printf("The file'Phase2PartKey.txt' was opened\n");
	}
	else {
		printf("The file 'Phase2PartKey.txt' was not opened\n");
	}
	int* PartSize;
	int Part = 0;
	PartSize = &Part;
	fscanf_s(fptr3, "%d", PartSize);
	printf("Size0: %d \n", *PartSize);
	uint8_t** PartKey= (uint8_t**)malloc((*PartSize) * sizeof(uint8_t*));
	///************************************************* Read file for PartKey **********************************************/
	//ReadFilePartKey(PartKey,PartSize,fptr3);
	//fclose(fptr3);
	//printf("The file 'Phase2PartKey.txt' closed\n");*/
	///************************************************* Check Phase2.1 **********************************************/
	
	//int j;
	//for (j = 0; j < *PartSize; j++) {
	//	//printf("0: %"SCNd32" 1: %"SCNd32" 2: %"SCNd32" 3: %"SCNd32" 4: %"SCNd32" 5: %"SCNd32" 6: %"SCNd32" 7: %"SCNd32" 8: %"SCNd32" 9: %"SCNd32" 10: %"SCNd32" 11: %"SCNd32" 12: %"SCNd32" 13: %"SCNd32"\n",PartKey[j][0], PartKey[j][1], PartKey[j][2], PartKey[j][3], PartKey[j][4], PartKey[j][5], PartKey[j][6], PartKey[j][7], PartKey[j][8], PartKey[j][9], PartKey[j][10], PartKey[j][11], PartKey[j][12], PartKey[j][13]);
	//	//printf("Part %d 0: %"SCNd32 "\n",j, PartKey[j][0]);
	//	if (PartKey[j][0] == (*keyptr)[0][2] && PartKey[j][1] == (*keyptr)[0][3] &&
	//		PartKey[j][2] == (*keyptr)[1][0] && PartKey[j][3] == (*keyptr)[1][1] &&
	//		PartKey[j][4] == (*keyptr)[1][2] && PartKey[j][5] == (*keyptr)[1][3] &&
	//		PartKey[j][6] == (*keyptr)[2][0] && PartKey[j][7] == (*keyptr)[2][1] &&
	//		PartKey[j][8] == (*keyptr)[2][2] && PartKey[j][9] == (*keyptr)[2][3] &&
	//		PartKey[j][10] == (*keyptr)[3][0] && PartKey[j][11] == (*keyptr)[3][1] &&
	//		PartKey[j][12] == (*keyptr)[3][2] && PartKey[j][13] == (*keyptr)[3][3]) {
	//		printf("Hurray for PartKey\n");
	//	}
	//}	
	//printf("out \n");

	//Check for duplicates
	//for (j = 0; j < *PartSize; j++) {
	//	for (i = 0; i < j; i++) {
	//		if (PartKey[j][0] == PartKey[i][0] && PartKey[j][1] == PartKey[i][1] && PartKey[j][2] == PartKey[i][2] && PartKey[j][3] == PartKey[i][3] &&
	//			PartKey[j][4] == PartKey[i][4] && PartKey[j][5] == PartKey[i][5] && PartKey[j][6] == PartKey[i][6] && PartKey[j][7] == PartKey[i][7] &&
	//			PartKey[j][8] == PartKey[i][8] && PartKey[j][9] == PartKey[i][9] && PartKey[j][10] == PartKey[i][10] && PartKey[j][11] == PartKey[i][11] &&
	//			PartKey[j][12] == PartKey[i][12] && PartKey[j][13] == PartKey[i][13]) {
	//			printf("duplicates\n");
	//		}
	//	}
	//}
	//printf("out2\n");

	/********************************** Misc. Stuff when checking phase2.1*****************************/
	//state_t* y, *y_fault;
	//y = ciphertext;
	//y_fault = ciphertextFaulty;

	//uint8_t f = InvSBox( times9( InvSBox((*y)[3][0] ^ (*keyptr)[3][0]) ^ (*keyptr)[3][0] ^ (*keyptr)[2][0]) ^
	//	times14( InvSBox( (*y)[2][1] ^ (*keyptr)[2][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[3][1])) ^
	//	times11( InvSBox((*y)[1][2] ^ (*keyptr)[1][2]) ^ ((*keyptr)[3][2] ^ (*keyptr)[2][2])) ^
	//	times13( InvSBox((*y)[0][3] ^ (*keyptr)[0][3]) ^ ((*keyptr)[3][3] ^ (*keyptr)[2][3]) )) ^
	//	InvSBox ( times9( InvSBox((*y_fault)[3][0] ^ (*keyptr)[3][0]) ^ (*keyptr)[3][0] ^ (*keyptr)[2][0]) ^
	//		times14( InvSBox( (*y_fault)[2][1] ^ (*keyptr)[2][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[3][1])) ^
	//		times11( InvSBox( (*y_fault)[1][2] ^ (*keyptr)[1][2]) ^ ((*keyptr)[3][2] ^ (*keyptr)[2][2])) ^
	//		times13( InvSBox( (*y_fault)[0][3] ^ (*keyptr)[0][3]) ^ ((*keyptr)[3][3] ^ (*keyptr)[2][3])) );

	//uint8_t q = InvSBox(times13(InvSBox((*y)[2][0] ^ (*keyptr)[2][0]) ^ (*keyptr)[2][0] ^ (*keyptr)[1][0]) ^
	//	times9(InvSBox((*y)[1][1] ^ (*keyptr)[1][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[1][1])) ^
	//	times14(InvSBox((*y)[0][2] ^ (*keyptr)[0][2]) ^ ((*keyptr)[2][2] ^ (*keyptr)[1][2])) ^
	//	times11(InvSBox((*y)[3][3] ^ (*keyptr)[3][3]) ^ ((*keyptr)[2][3] ^ (*keyptr)[1][3]))) ^
	//	InvSBox(times13(InvSBox((*y_fault)[2][0] ^ (*keyptr)[2][0]) ^ (*keyptr)[2][0] ^ (*keyptr)[1][0]) ^
	//		times9(InvSBox((*y_fault)[1][1] ^ (*keyptr)[1][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[1][1])) ^
	//		times14(InvSBox((*y_fault)[0][2] ^ (*keyptr)[0][2]) ^ ((*keyptr)[2][2] ^ (*keyptr)[1][2])) ^
	//		times11(InvSBox((*y_fault)[3][3] ^ (*keyptr)[3][3]) ^ ((*keyptr)[2][3] ^ (*keyptr)[1][3])));
	//printf("f: %"SCNd32 " q: %"SCNd32 "\n", f,q);


	
	/************************************************TESTING PHASE 2.2 **********************************************************************/
	/*FILE* fptr5;
	errno_t err5;
	err5 = fopen_s(&fptr5, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase2FinalKey.txt", "r");

	if (err5 == 0) {
		printf("The file'Phase2FinalKey.txt was opened\n");
	}
	else {
		printf("The file 'Phase2FinalKey.txt' was not opened\n");
	}
	int* FinalSize;
	int Final = 0;
	FinalSize = &Final;
	fscanf_s(fptr5, "%d", FinalSize);
	printf("FinalSize: %d \n", *FinalSize);
	uint8_t** FinalKeyHypothesis = (uint8_t**)malloc((*FinalSize) * sizeof(uint8_t*));
	ReadFileFinalKey(FinalKeyHypothesis, FinalSize, fptr5);
	fclose(fptr5);

	printf("going in to test phase 2 \n");
	printf("FinalSize outside: %d \n", *FinalSize);



	int i,j;
	for(j = 0; j < *FinalSize; j++) { 
		if ((FinalKeyHypothesis[j][0] == (*keyptr)[0][0] && FinalKeyHypothesis[j][1] == (*keyptr)[0][1]) && 
			FinalKeyHypothesis[j][2] == (*keyptr)[0][2] && FinalKeyHypothesis[j][3] == (*keyptr)[0][3] &&
			FinalKeyHypothesis[j][4] == (*keyptr)[1][0] && FinalKeyHypothesis[j][5] == (*keyptr)[1][1] && 
			FinalKeyHypothesis[j][6] == (*keyptr)[1][2] && FinalKeyHypothesis[j][7] == (*keyptr)[1][3] &&
			FinalKeyHypothesis[j][8] == (*keyptr)[2][0] && FinalKeyHypothesis[j][9] == (*keyptr)[2][1] && 
			FinalKeyHypothesis[j][10] == (*keyptr)[2][2] && FinalKeyHypothesis[j][11] == (*keyptr)[2][3] &&
			FinalKeyHypothesis[j][12] == (*keyptr)[3][0] && FinalKeyHypothesis[j][13] == (*keyptr)[3][1] && 
			FinalKeyHypothesis[j][14] == (*keyptr)[3][2] && FinalKeyHypothesis[j][15] == (*keyptr)[3][3] ) {
			printf("hugehurray! \n");
		}
	}
	printf("out \n");*/

	////Check for duplicates
	//for (j = 0; j < *FinalSize; j++) {
	//	for (i = 0; i < j; i++) {
	//		if (FinalKeyHypothesis[j][0] == FinalKeyHypothesis[i][0] && FinalKeyHypothesis[j][1] == FinalKeyHypothesis[i][1] && FinalKeyHypothesis[j][2] == FinalKeyHypothesis[i][2] && FinalKeyHypothesis[j][3] == FinalKeyHypothesis[i][3] &&
	//			FinalKeyHypothesis[j][4] == FinalKeyHypothesis[i][4] && FinalKeyHypothesis[j][5] == FinalKeyHypothesis[i][5] && FinalKeyHypothesis[j][6] == FinalKeyHypothesis[i][6] && FinalKeyHypothesis[j][7] == FinalKeyHypothesis[i][7] &&
	//			FinalKeyHypothesis[j][8] == FinalKeyHypothesis[i][8] && FinalKeyHypothesis[j][9] == FinalKeyHypothesis[i][9] && FinalKeyHypothesis[j][10] == FinalKeyHypothesis[i][10] && FinalKeyHypothesis[j][11] == FinalKeyHypothesis[i][11] &&
	//			FinalKeyHypothesis[j][12] == FinalKeyHypothesis[i][12] && FinalKeyHypothesis[j][13] == FinalKeyHypothesis[i][13] && FinalKeyHypothesis[j][14] == FinalKeyHypothesis[i][14] && FinalKeyHypothesis[j][15] == FinalKeyHypothesis[i][15]) {
	//			printf("duplicates\n");
	//		}
	//	}
	//}
	//printf("out2\n");
	//
	/********************************** Misc. Stuff when checking phase2.2*****************************/
	//state_t* y, *y_fault;
	//y = ciphertext;
	//y_fault = ciphertextFaulty;

	////equation 1
	//uint8_t q_1 = InvSBox(		
	//	times14( InvSBox((*y)[0][0] ^ (*keyptr)[0][0]) ^ ((*keyptr)[0][0] ^ SBox((*keyptr)[3][1] ^ (*keyptr)[2][1]) ^ Rcon(10) ) ) ^
	//	times11( InvSBox((*y)[3][1] ^ (*keyptr)[3][1] ) ^ (*keyptr)[0][1] ^ SBox((*keyptr)[3][2] ^ (*keyptr)[2][2]) ) ^
	//	times13( InvSBox( (*y)[2][2] ^ (*keyptr)[2][2] ) ^ (*keyptr)[0][2] ^ SBox( (*keyptr)[3][3] ^ (*keyptr)[2][3] ) ) ^
	//	times9(InvSBox( (*y)[1][3] ^ (*keyptr)[1][3] )^ (*keyptr)[0][3] ^ SBox((*keyptr)[3][0] ^ (*keyptr)[2][0]) ) ) ^
	//	InvSBox(times14(InvSBox( (*y_fault)[0][0] ^ (*keyptr)[0][0] ) ^((*keyptr)[0][0] ^ SBox( (*keyptr)[3][1] ^ (*keyptr)[2][1]) ^ Rcon(10))) ^
	//		times11(InvSBox( (*y_fault)[3][1] ^ (*keyptr)[3][1]) ^ (*keyptr)[0][1] ^ SBox( (*keyptr)[3][2] ^ (*keyptr)[2][2])) ^
	//		times13(InvSBox( (*y_fault)[2][2] ^ (*keyptr)[2][2]) ^ (*keyptr)[0][2] ^ SBox( (*keyptr)[3][3] ^ (*keyptr)[2][3])) ^
	//		times9(InvSBox( (*y_fault)[1][3] ^ (*keyptr)[1][3]) ^ (*keyptr)[0][3] ^ SBox((*keyptr)[3][0] ^ (*keyptr)[2][0])) );
	////equation 4
	//uint8_t q_2 = InvSBox(times11(InvSBox((*y)[1][0] ^ (*keyptr)[1][0]) ^ ((*keyptr)[1][0] ^ (*keyptr)[0][0])) ^
	//	times13(InvSBox((*y)[0][1] ^ (*keyptr)[0][1]) ^ ((*keyptr)[1][1] ^ (*keyptr)[0][1])) ^
	//	times9(InvSBox((*y)[3][2] ^ (*keyptr)[3][2]) ^ ((*keyptr)[1][2]^ (*keyptr)[0][2])) ^
	//	times14(InvSBox((*y)[2][3] ^ (*keyptr)[2][3]) ^ ((*keyptr)[1][3] ^ (*keyptr)[0][3]))) ^
	//	InvSBox(times11(InvSBox((*y_fault)[1][0] ^ (*keyptr)[1][0]) ^ ((*keyptr)[1][0] ^ (*keyptr)[0][0])) ^
	//		times13(InvSBox((*y_fault)[0][1] ^ (*keyptr)[0][1]) ^ ((*keyptr)[1][1] ^ (*keyptr)[0][1])) ^
	//		times9(InvSBox((*y_fault)[3][2] ^ (*keyptr)[3][2]) ^ ((*keyptr)[1][2] ^ (*keyptr)[0][2])) ^
	//		times14(InvSBox((*y_fault)[2][3] ^ (*keyptr)[2][3]) ^ ((*keyptr)[1][3] ^ (*keyptr)[0][3])));

	//uint8_t f = InvSBox( times9( InvSBox((*y)[3][0] ^ (*keyptr)[3][0]) ^ (*keyptr)[3][0] ^ (*keyptr)[2][0]) ^
	//	times14( InvSBox( (*y)[2][1] ^ (*keyptr)[2][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[3][1])) ^
	//	times11( InvSBox((*y)[1][2] ^ (*keyptr)[1][2]) ^ ((*keyptr)[3][2] ^ (*keyptr)[2][2])) ^
	//	times13( InvSBox((*y)[0][3] ^ (*keyptr)[0][3]) ^ ((*keyptr)[3][3] ^ (*keyptr)[2][3]) )) ^
	//	InvSBox ( times9( InvSBox((*y_fault)[3][0] ^ (*keyptr)[3][0]) ^ (*keyptr)[3][0] ^ (*keyptr)[2][0]) ^
	//		times14( InvSBox( (*y_fault)[2][1] ^ (*keyptr)[2][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[3][1])) ^
	//		times11( InvSBox( (*y_fault)[1][2] ^ (*keyptr)[1][2]) ^ ((*keyptr)[3][2] ^ (*keyptr)[2][2])) ^
	//		times13( InvSBox( (*y_fault)[0][3] ^ (*keyptr)[0][3]) ^ ((*keyptr)[3][3] ^ (*keyptr)[2][3])) );

	//uint8_t q = InvSBox(times13(InvSBox((*y)[2][0] ^ (*keyptr)[2][0]) ^ (*keyptr)[2][0] ^ (*keyptr)[1][0]) ^
	//	times9(InvSBox((*y)[1][1] ^ (*keyptr)[1][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[1][1])) ^
	//	times14(InvSBox((*y)[0][2] ^ (*keyptr)[0][2]) ^ ((*keyptr)[2][2] ^ (*keyptr)[1][2])) ^
	//	times11(InvSBox((*y)[3][3] ^ (*keyptr)[3][3]) ^ ((*keyptr)[2][3] ^ (*keyptr)[1][3]))) ^
	//	InvSBox(times13(InvSBox((*y_fault)[2][0] ^ (*keyptr)[2][0]) ^ (*keyptr)[2][0] ^ (*keyptr)[1][0]) ^
	//		times9(InvSBox((*y_fault)[1][1] ^ (*keyptr)[1][1]) ^ ((*keyptr)[2][1] ^ (*keyptr)[1][1])) ^
	//		times14(InvSBox((*y_fault)[0][2] ^ (*keyptr)[0][2]) ^ ((*keyptr)[2][2] ^ (*keyptr)[1][2])) ^
	//		times11(InvSBox((*y_fault)[3][3] ^ (*keyptr)[3][3]) ^ ((*keyptr)[2][3] ^ (*keyptr)[1][3])));
	//printf("f: %"SCNd32 " q: %"SCNd32 "\n", f, q);
	//printf("2f: %"SCNd32 " 3f: %"SCNd32 "\n", xtimes(q), xtimes(q)^q);
	//printf("q_1: %"SCNd32 " q_2: %"SCNd32 "\n", q_1, q_2);
	//printf("2q_2: %"SCNd32 " 3q_1: %"SCNd32 "\n", xtimes(q_2), xtimes(q_1) ^ q_1);
	fclose(fptr_time);
	return 0;
}
