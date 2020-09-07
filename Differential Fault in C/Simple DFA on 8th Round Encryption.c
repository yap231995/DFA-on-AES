//#include <stdio.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <inttypes.h>
//#include <time.h>
//#include "AES.h"
//
////uint8_t*** DFA_round8Phase1(state_t* y, state_t* y_fault, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3) {
////	uint8_t*** KeyHypothesisSet = (uint8_t***)malloc(4 * sizeof(uint8_t**));
////	KeyHypothesisSet[0] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_1,k_8,k_11,k_14
////	KeyHypothesisSet[1] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_2,k_5,k_12,k_15
////	KeyHypothesisSet[2] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_3,k_6,k_9,k_16
////	KeyHypothesisSet[3] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_4,k_7,k_10,k_13
////	int counter0 = 0;
////	int counter1 = 0;
////	int counter2 = 0;
////	int counter3 = 0;
////
////
////	unsigned long long key = 0;
////	while (key <= 4294967295u) {
////		unsigned int key_1 = (key & 0XFF);
////		unsigned int key_2 = ((key & 0XFF00) >> 8);
////		unsigned int key_3 = ((key & 0XFF0000) >> 16);
////		unsigned int key_4 = ((key & 0XFF000000) >> 24);
////		//printf("key_1: %d key_2: %d key_3: %d key_4: %d \n",key_1,key_2,key_3,key_4);
////
////
////		//Column 1
////		uint8_t f1 = InvSBox((*y)[3][1] ^ key_4) ^ InvSBox((*y_fault)[3][1] ^ key_4);  // 14
////		uint8_t eq_1 = InvSBox((*y)[2][2] ^ key_3) ^ InvSBox((*y_fault)[2][2] ^ key_3); //11
////		uint8_t eq_2 = InvSBox((*y)[0][0] ^ key_1) ^ InvSBox((*y_fault)[0][0] ^ key_1); //1
////		uint8_t eq_3 = InvSBox((*y)[1][3] ^ key_2) ^ InvSBox((*y_fault)[1][3] ^ key_2); //8
////		uint8_t twof1 = xtimes(f1);
////		uint8_t threef1 = xtimes(f1) ^ f1;
////		//printf("test1: %d \n", key);
////		if (((f1 == eq_1 && twof1 == eq_2) && threef1 == eq_3)) {
////			//printf("test1: %llu \n", key);
////			KeyHypothesisSet[0][counter0] = (uint8_t*)malloc(4 * sizeof(uint8_t));
////			KeyHypothesisSet[0][counter0][0] = key_1;//1
////			KeyHypothesisSet[0][counter0][1] = key_2;//8
////			KeyHypothesisSet[0][counter0][2] = key_3;//11
////			KeyHypothesisSet[0][counter0][3] = key_4;//14
////			counter0++;
////		}
////
////
////		//Column 2
////		uint8_t f2 = InvSBox((*y)[1][0] ^ key_2) ^ InvSBox((*y_fault)[1][0] ^ key_2);  //5
////		eq_1 = InvSBox((*y)[0][1] ^ key_1) ^ InvSBox((*y_fault)[0][1] ^ key_1); //2
////		eq_2 = InvSBox((*y)[2][3] ^ key_3) ^ InvSBox((*y_fault)[2][3] ^ key_3); //12
////		eq_3 = InvSBox((*y)[3][2] ^ key_4) ^ InvSBox((*y_fault)[3][2] ^ key_4); //15
////		uint8_t twof2 = xtimes(f2);
////		uint8_t threef2 = xtimes(f2) ^ f2;
////
////		if (((f2 == eq_1 && twof2 == eq_2) && threef2 == eq_3)) {
////			//printf("test2: %llu \n", key);
////			KeyHypothesisSet[1][counter1] = (uint8_t*)malloc(4 * sizeof(uint8_t));
////			KeyHypothesisSet[1][counter1][0] = key_1;//2
////			KeyHypothesisSet[1][counter1][1] = key_2;//5
////			KeyHypothesisSet[1][counter1][2] = key_3;//12
////			KeyHypothesisSet[1][counter1][3] = key_4;//15
////			counter1++;
////		}
////
////
////
////		//Column 3
////		uint8_t f3 = InvSBox((*y)[2][0] ^ key_3) ^ InvSBox((*y_fault)[2][0] ^ key_3);  //9
////		eq_1 = InvSBox((*y)[3][3] ^ key_4) ^ InvSBox((*y_fault)[3][3] ^ key_4); //16
////		eq_2 = InvSBox((*y)[0][2] ^ key_1) ^ InvSBox((*y_fault)[0][2] ^ key_1); //3
////		eq_3 = InvSBox((*y)[1][1] ^ key_2) ^ InvSBox((*y_fault)[1][1] ^ key_2); //6
////		uint8_t twof3 = xtimes(f3);
////		uint8_t threef3 = xtimes(f3) ^ f3;
////
////		if (((f3 == eq_1 && twof3 == eq_2) && threef3 == eq_3)) {
////			//printf("test3: %llu \n", key);
////			KeyHypothesisSet[2][counter2] = (uint8_t*)malloc(4 * sizeof(uint8_t));
////			KeyHypothesisSet[2][counter2][0] = key_1;//3
////			KeyHypothesisSet[2][counter2][1] = key_2;//6
////			KeyHypothesisSet[2][counter2][2] = key_3;//9
////			KeyHypothesisSet[2][counter2][3] = key_4;//16
////			counter2++;
////		}
////
////		//Column 4
////		uint8_t f4 = InvSBox((*y)[0][3] ^ key_1) ^ InvSBox((*y_fault)[0][3] ^ key_1);  //4
////		eq_1 = InvSBox((*y)[1][2] ^ key_2) ^ InvSBox((*y_fault)[1][2] ^ key_2); //7
////		eq_2 = InvSBox((*y)[2][1] ^ key_3) ^ InvSBox((*y_fault)[2][1] ^ key_3); //10
////		eq_3 = InvSBox((*y)[3][0] ^ key_4) ^ InvSBox((*y_fault)[3][0] ^ key_4); //13
////		uint8_t twof4 = xtimes(f4);
////		uint8_t threef4 = xtimes(f4) ^ f4;
////
////		if (((f4 == eq_1 && twof4 == eq_2) && threef4 == eq_3)) {
////			//printf("test4: %llu \n", key);
////			KeyHypothesisSet[3][counter3] = (uint8_t*)malloc(4 * sizeof(uint8_t));
////			KeyHypothesisSet[3][counter3][0] = key_1;//4
////			KeyHypothesisSet[3][counter3][1] = key_2;//7
////			KeyHypothesisSet[3][counter3][2] = key_3;//10
////			KeyHypothesisSet[3][counter3][3] = key_4;//13
////			counter3++;
////		}
////		key++;
////	}
////	*SizeKeySet0 = counter0;
////	*SizeKeySet1 = counter1;
////	*SizeKeySet2 = counter2;
////	*SizeKeySet3 = counter3;
////
////	printf("Size of KeyHypothesisSet0: %d \n", counter0);
////	printf("Size of KeyHypothesisSet1: %d \n", counter1);
////	printf("Size of KeyHypothesisSet2: %d \n", counter2);
////	printf("Size of KeyHypothesisSet3: %d \n", counter3);
////	return KeyHypothesisSet;
////}
//
//
//
//uint8_t times9(uint8_t x) {
//	return xtimes(xtimes(xtimes(x))) ^ x;
//}
//
//uint8_t times11(uint8_t x) {
//	return xtimes(xtimes(xtimes(x))) ^ xtimes(x) ^ x;
//}
//
//uint8_t times13(uint8_t x) {
//	return xtimes(xtimes(xtimes(x))) ^ xtimes(xtimes(x)) ^ x;
//}
//
//uint8_t times14(uint8_t x) {
//	return xtimes(xtimes(xtimes(x))) ^ xtimes(xtimes(x)) ^ xtimes(x);
//}
//
//uint8_t** Simple_DFA_round8Phase2(state_t* y, state_t* y_fault, uint8_t*** KeyHypothesisSet, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3, int* FinalSizePtr) {
//	uint8_t** FinalKey = (uint8_t**)malloc(5000000 * sizeof(uint8_t*));
//	int FinalSize = 0;
//	int column1, column2, column3, column4;
//
//	for (column1 = 0; column1 < *SizeKeySet0; column1++) {
//		for (column2 = 0; column2 < *SizeKeySet1; column2++) {
//			for (column3 = 0; column3 < *SizeKeySet2; column3++) {
//				for (column4 = 0; column4 < *SizeKeySet3; column4++) {
//					uint8_t k1 = KeyHypothesisSet[0][column1][0];//1
//					uint8_t k8 = KeyHypothesisSet[0][column1][1];//8
//					uint8_t k11 = KeyHypothesisSet[0][column1][2];//11
//					uint8_t k14 = KeyHypothesisSet[0][column1][3];//14
//
//					uint8_t k2 = KeyHypothesisSet[1][column2][0];//2
//					uint8_t k5 = KeyHypothesisSet[1][column2][1];//5
//					uint8_t k12 = KeyHypothesisSet[1][column2][2];//12
//					uint8_t k15 = KeyHypothesisSet[1][column2][3];//15
//
//
//					uint8_t k3 = KeyHypothesisSet[2][column3][0];//3
//					uint8_t k6 = KeyHypothesisSet[2][column3][1];//6
//					uint8_t k9 = KeyHypothesisSet[2][column3][2];//9
//					uint8_t k16 = KeyHypothesisSet[2][column3][3];//16
//
//					uint8_t k4 = KeyHypothesisSet[3][column4][0];//4
//					uint8_t k7 = KeyHypothesisSet[3][column4][1];//7
//					uint8_t k10 = KeyHypothesisSet[3][column4][2];//10
//					uint8_t k13 = KeyHypothesisSet[3][column4][3];//13
//
//					uint8_t eq1 = InvSBox(times14(InvSBox((*y)[0][0] ^ k1) ^ (k1 ^ SBox(k14 ^ k10) ^ Rcon(10)))
//						^ times11(InvSBox((*y)[3][1] ^ k14) ^ (k2 ^ SBox(k15 ^ k11)))
//						^ times13(InvSBox((*y)[2][2] ^ k11) ^ (k3 ^ SBox(k16 ^ k12)))
//						^ times9(InvSBox((*y)[1][3] ^ k8) ^ (k4 ^ SBox(k13 ^ k9))))
//						^ InvSBox(times14(InvSBox((*y_fault)[0][0] ^ k1) ^ (k1 ^ SBox(k14 ^ k10) ^ Rcon(10)))
//							^ times11(InvSBox((*y_fault)[3][1] ^ k14) ^ (k2 ^ SBox(k15 ^ k11)))
//							^ times13(InvSBox((*y_fault)[2][2] ^ k11) ^ (k3 ^ SBox(k16 ^ k12)))
//							^ times9(InvSBox((*y_fault)[1][3] ^ k8) ^ (k4 ^ SBox(k13 ^ k9))));
//
//					uint8_t eq2 = InvSBox(times9(InvSBox((*y)[3][0] ^ k13) ^ (k13 ^ k9))
//						^ times14(InvSBox((*y)[2][1] ^ k10) ^ (k14 ^ k10))
//						^ times11(InvSBox((*y)[1][2] ^ k7) ^ (k15 ^ k11))
//						^ times13(InvSBox((*y)[0][3] ^ k4) ^ (k16 ^ k12)))
//						^ InvSBox(times9(InvSBox((*y_fault)[3][0] ^ k13) ^ (k13 ^ k9))
//							^ times14(InvSBox((*y_fault)[2][1] ^ k10) ^ (k14 ^ k10))
//							^ times11(InvSBox((*y_fault)[1][2] ^ k7) ^ (k15 ^ k11))
//							^ times13(InvSBox((*y_fault)[0][3] ^ k4) ^ (k16 ^ k12)));
//
//					uint8_t eq3 = InvSBox(times13(InvSBox((*y)[2][0] ^ k9) ^ (k9 ^ k5))
//						^ times9(InvSBox((*y)[1][1] ^ k6) ^ (k10 ^ k6))
//						^ times14(InvSBox((*y)[0][2] ^ k3) ^ (k11 ^ k7))
//						^ times11(InvSBox((*y)[3][3] ^ k16) ^ (k12 ^ k8)))
//						^ InvSBox(times13(InvSBox((*y_fault)[2][0] ^ k9) ^ (k9 ^ k5))
//							^ times9(InvSBox((*y_fault)[1][1] ^ k6) ^ (k10 ^ k6))
//							^ times14(InvSBox((*y_fault)[0][2] ^ k3) ^ (k11 ^ k7))
//							^ times11(InvSBox((*y_fault)[3][3] ^ k16) ^ (k12 ^ k8)));
//					uint8_t eq4 = InvSBox(times11(InvSBox((*y)[1][0] ^ k5) ^ (k5 ^ k1))
//						^ times13(InvSBox((*y)[0][1] ^ k2) ^ (k6 ^ k2))
//						^ times9(InvSBox((*y)[3][2] ^ k15) ^ (k7 ^ k3))
//						^ times14(InvSBox((*y)[2][3] ^ k12) ^ (k8 ^ k4)))
//						^ InvSBox(times11(InvSBox((*y_fault)[1][0] ^ k5) ^ (k5 ^ k1))
//							^ times13(InvSBox((*y_fault)[0][1] ^ k2) ^ (k6 ^ k2))
//							^ times9(InvSBox((*y_fault)[3][2] ^ k15) ^ (k7 ^ k3))
//							^ times14(InvSBox((*y_fault)[2][3] ^ k12) ^ (k8 ^ k4)));
//					if (eq2 == eq3 && (xtimes(eq2) == eq1) && ((xtimes(eq2) ^ eq2) == eq4)) {
//						//printf("FinalSize: %d \n", FinalSize);
//						//printf("eq2: %"SCNd32 "eq3: %"SCNd32 "\n", eq2, eq3);
//						//printf("eq1: %"SCNd32 "2 of eq2 : %"SCNd32 "\n", eq1, xtimes(eq2));
//						//printf("eq4: %"SCNd32 "3 of eq2 : %"SCNd32 "\n", eq4, (xtimes(eq2) ^ eq2));
//						printf("column1: %d column2: %d column3: %d column4: %d \n", column1,column2,column3,column4);
//						FinalKey[FinalSize] = (uint8_t*)malloc(16 * sizeof(uint8_t));
//						FinalKey[FinalSize][0] = k1;
//						FinalKey[FinalSize][1] = k2;
//						FinalKey[FinalSize][2] = k3;
//						FinalKey[FinalSize][3] = k4;
//						FinalKey[FinalSize][4] = k5;
//						FinalKey[FinalSize][5] = k6;
//						FinalKey[FinalSize][6] = k7;
//						FinalKey[FinalSize][7] = k8;
//						FinalKey[FinalSize][8] = k9;
//						FinalKey[FinalSize][9] = k10;
//						FinalKey[FinalSize][10] = k11;
//						FinalKey[FinalSize][11] = k12;
//						FinalKey[FinalSize][12] = k13;
//						FinalKey[FinalSize][13] = k14;
//						FinalKey[FinalSize][14] = k15;
//						FinalKey[FinalSize][15] = k16;
//						FinalSize++;
//					}
//				}
//			}
//		}
//	}
//
//	*FinalSizePtr = FinalSize;
//
//	return FinalKey;
//}
//
//
////void WriteFileKeyHypothesis(uint8_t*** KeyHypothesis, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3, FILE* fptr) {
////	int i;
////
////	fprintf(fptr, "%d\n", *SizeKeySet0);
////	fprintf(fptr, "%d\n", *SizeKeySet1);
////	fprintf(fptr, "%d\n", *SizeKeySet2);
////	fprintf(fptr, "%d\n", *SizeKeySet3);
////
////	int Size0 = *SizeKeySet0;
////	for (i = 0; i < Size0; i++) {
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][0]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][1]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][2]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[0][i][3]);
////	}
////	int Size1 = *SizeKeySet1;
////	for (i = 0; i < Size1; i++) {
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][0]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][1]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][2]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[1][i][3]);
////	}
////	int Size2 = *SizeKeySet2;
////	for (i = 0; i < Size2; i++) {
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][0]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][1]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][2]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[2][i][3]);
////	}
////	int Size3 = *SizeKeySet3;
////	for (i = 0; i < Size3; i++) {
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][0]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][1]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][2]);
////		fprintf(fptr, "%"SCNd32"\n", KeyHypothesis[3][i][3]);
////	}
////
////}
////
////void ReadFileKeyHypothesis(uint8_t*** KeyHypothesisSet, int* SizeKeySet0, int* SizeKeySet1, int* SizeKeySet2, int* SizeKeySet3, FILE* fptr) {
////
////	fscanf_s(fptr, "%d", SizeKeySet0);
////	printf("Size0: %d \n", *SizeKeySet0);
////	fscanf_s(fptr, "%d", SizeKeySet1);
////	printf("Size1: %d \n", *SizeKeySet1);
////	fscanf_s(fptr, "%d", SizeKeySet2);
////	printf("Size2: %d \n", *SizeKeySet2);
////	fscanf_s(fptr, "%d", SizeKeySet3);
////	printf("Size3: %d \n", *SizeKeySet3);
////
////	printf("Time to start reading. \n");
////	int i, j, k, l;
////	for (i = 0; i < *SizeKeySet0; i++) {
////		KeyHypothesisSet[0][i] = (uint8_t*)malloc(512 * sizeof(uint8_t));
////		//printf("i: %d \n", i);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][0]);
////		//printf("%"SCNu8 "\n", KeyHypothesisSet[0][i][0]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][1]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][1]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][2]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][2]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[0][i][3]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[0][i][3]);
////	}
////	for (j = 0; j < *SizeKeySet1; j++) {
////		//printf("j: %d \n", j);
////		KeyHypothesisSet[1][j] = (uint8_t*)malloc(512 * sizeof(uint8_t));
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][0]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][1]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][2]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[1][j][3]);
////	}
////	for (k = 0; k < *SizeKeySet2; k++) {
////		//printf("k: %d \n", k);
////		KeyHypothesisSet[2][k] = (uint8_t*)malloc(512 * sizeof(uint8_t));
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][0]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][1]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][2]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[2][k][3]);
////
////	}
////	for (l = 0; l < *SizeKeySet3; l++) {
////		//printf("l: %d \n", l);
////		KeyHypothesisSet[3][l] = (uint8_t*)malloc(512 * sizeof(uint8_t));
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][0]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][0]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][1]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][1]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][2]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][2]);
////		fscanf_s(fptr, "%"SCNu8, &KeyHypothesisSet[3][l][3]);
////		//printf("%"SCNu8"\n", KeyHypothesisSet[3][l][3]);
////	}
////
////}
////
////void WriteFileFinalKey(uint8_t** FinalKey, int* FinalSize, FILE* fptr) {
////	int i;
////	fprintf(fptr, "%d\n", *FinalSize);
////
////	int Size = *FinalSize;
////	for (i = 0; i < Size; i++) {
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][0]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][1]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][2]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][3]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][4]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][5]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][6]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][7]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][8]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][9]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][10]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][11]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][12]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][13]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][14]);
////		fprintf(fptr, "%"SCNd32"\n", FinalKey[i][15]);
////	}
////}
////
////void ReadFileFinalKey(uint8_t** FinalKey, int* FinalSize, FILE* fptr) {
////	//Note: The FinalSize is read outside for FinalKey to be initialised.
////	printf("Time to start reading. \n");
////	int i;
////	for (i = 0; i < *FinalSize; i++) {
////		FinalKey[i] = (uint8_t*)malloc(14 * sizeof(uint8_t));
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][0]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][1]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][2]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][3]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][4]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][5]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][6]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][7]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][8]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][9]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][10]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][11]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][12]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][13]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][14]);
////		fscanf_s(fptr, "%"SCNu8, &FinalKey[i][15]);
////	}
////}
////
////int main() {
////	state_t MasterKey = { {0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53} };
////	state_t* MasKeyPtr = &MasterKey;
////	state_t matrix1 = { {0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53} };
////	state_t matrix2 = { {0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53} };
////
////	state_t* ptrMatrix1 = &matrix1;
////	state_t* ptrMatrix2 = &matrix2;
////
////
////	printf("Original Text1: \n");
////	PrintMatrix(ptrMatrix1);
////
////
////	state_t* ciphertext;
////	ciphertext = AESEncryption(ptrMatrix1, MasKeyPtr);
////	printf("Encrypted Text: \n");
////	PrintMatrix(ciphertext);
////
////	state_t* ciphertextFaulty;
////	ciphertextFaulty = AESEncryptionFaultyROUND8(ptrMatrix2, MasKeyPtr);
////	printf("Faulty Encrypted Text: \n");
////	PrintMatrix(ciphertextFaulty);
////	FILE* fptr_time;
////	errno_t err_time;
////	err_time = fopen_s(&fptr_time, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Time.txt", "w+");
////	/************************************************ PHASE 1 **********************************************************************/
////	//printf("Going into DFAPhase1: \n");
////	//clock_t begin_1 = clock();
////	//uint8_t ***KeyHypothesisSet = DFA_round8Phase1(ciphertext, ciphertextFaulty, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3);
////	//clock_t end_1 = clock();
////	//double time_spent_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
////	//printf("time in sec: %f \n", time_spent_1);
////	//fprintf(fptr_time, "Time spent 1: %lf \n", time_spent_1);
////	//printf("Going out of DFAPhase1: \n");
////	//printf("Size0 Outside: %d \n", Size0);
////	//printf("Size1 Outside: %d \n", Size1);
////	//printf("Size2 Outside: %d \n", Size2);
////	//printf("Size3 Outside: %d \n", Size3);
////	
////	//FILE* fptr;
////	//errno_t err;
////	//err = fopen_s(&fptr, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase1KeyHypothesis.txt", "w");
////
////	//if (err == 0) {
////	//	printf("The file'Phase1KeyHypothesis.txt was opened\n");
////	//}
////	//else {
////	//	printf("The file 'Phase1KeyHypothesis.txt' was not opened\n");
////	//}
////	//WriteFileKeyHypothesis(KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, fptr);
////	//fclose(fptr);
////
////
////
////	/************************************************ Initialise KeyHypothesisSet **********************************************************************/
////	uint8_t*** KeyHypothesisSet = (uint8_t***)malloc(4 * sizeof(uint8_t**));
////	KeyHypothesisSet[0] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_1,k_8,k_11,k_14
////	KeyHypothesisSet[1] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_2,k_5,k_12,k_15
////	KeyHypothesisSet[2] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_3,k_6,k_9,k_16
////	KeyHypothesisSet[3] = (uint8_t**)malloc(1000 * sizeof(uint8_t*)); // For key k_4,k_7,k_10,k_13
////	/************************************************* Read file for KeyHypothesisSet **********************************************/
////	int* SizeKeySet0, * SizeKeySet1, * SizeKeySet2, * SizeKeySet3, *FinalSizePtr;
////	int Size0 = 0;
////	int Size1 = 0;
////	int Size2 = 0;
////	int Size3 = 0;
////	int FinalSize = 0;
////	SizeKeySet0 = &Size0;
////	SizeKeySet1 = &Size1;
////	SizeKeySet2 = &Size2;
////	SizeKeySet3 = &Size3;
////	FinalSizePtr = &FinalSize;
////	FILE* fptr;
////	errno_t err;
////	err = fopen_s(&fptr, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase1KeyHypothesis.txt", "r");
////	if (err == 0) {
////		printf("The file'Phase1KeyHypothesis.txt was opened\n");
////	} else {
////		printf("The file 'Phase1KeyHypothesis.txt' was not opened\n");
////	}
////	ReadFileKeyHypothesis(KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, fptr);
////	fclose(fptr);
////
////	printf("Going into Simple Phase 2 \n");
////	clock_t begin = clock();
////	uint8_t** FinalKeyHypothesis = Simple_DFA_round8Phase2(ciphertext, ciphertextFaulty, KeyHypothesisSet, SizeKeySet0, SizeKeySet1, SizeKeySet2, SizeKeySet3, FinalSizePtr);
////	clock_t end = clock();
////	printf("Going out Simple Phase 2 \n");
////
////	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
////	printf("time in sec: %f", time_spent);// 
////	fprintf(fptr_time, "Time spent Simple Phase 2: %f \n", time_spent);
////	/************************************************* Write file for FinalKey **********************************************/
////	FILE* fptr4;
////	errno_t err4;
////	err4 = fopen_s(&fptr4, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase2FinalKey.txt", "w");
////
////	if (err4 == 0) {
////		printf("The file'Phase2FinalKey.txt was opened\n");
////	}
////	else {
////		printf("The file 'Phase2FinalKey.txt' was not opened\n");
////	}
////	WriteFileFinalKey(FinalKeyHypothesis, FinalSizePtr, fptr4);
////	fclose(fptr4);
//
//
//	/******************************************************** Key Schedule ***************************************************/
//	//uint8_t** W;
//	//W = CreateKeys(MasKeyPtr);
//
//	//state_t key = { {0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00} };
//	//state_t* keyptr = &key;
//	//RoundKey(W, 10, keyptr);
//	/****************************************************** TESTING PHASE 2 ****************************************************/
//	//FILE* fptr5;
//	//errno_t err5;
//	//err5 = fopen_s(&fptr5, "C:\\Users\\tempacc\\Documents\\NTU\\Test File\\Test1\\Phase2FinalKey.txt", "r");
//
//	//if (err5 == 0) {
//	//	printf("The file'Phase2FinalKey.txt was opened\n");
//	//}
//	//else {
//	//	printf("The file 'Phase2FinalKey.txt' was not opened\n");
//	//}
//	//int* FinalSizePtr;
//	//int FinalSize = 0;
//	//FinalSizePtr = &FinalSize;
//	//fscanf_s(fptr5, "%d", FinalSizePtr);
//	//printf("FinalSize: %d \n", *FinalSizePtr);
//	//uint8_t** FinalKeyHypothesis = (uint8_t**)malloc((*FinalSizePtr) * sizeof(uint8_t*));
//	//ReadFileFinalKey(FinalKeyHypothesis, FinalSizePtr, fptr5);
//	//fclose(fptr5);
//
//	//printf("going in to test phase 2 \n");
//	//printf("FinalSize outside: %d \n", *FinalSizePtr);
//
//
//
////	int j;
////	for(j = 0; j < *FinalSizePtr; j++) { 
////		if ((FinalKeyHypothesis[j][0] == (*keyptr)[0][0] && FinalKeyHypothesis[j][1] == (*keyptr)[0][1]) && 
////			FinalKeyHypothesis[j][2] == (*keyptr)[0][2] && FinalKeyHypothesis[j][3] == (*keyptr)[0][3] &&
////			FinalKeyHypothesis[j][4] == (*keyptr)[1][0] && FinalKeyHypothesis[j][5] == (*keyptr)[1][1] && 
////			FinalKeyHypothesis[j][6] == (*keyptr)[1][2] && FinalKeyHypothesis[j][7] == (*keyptr)[1][3] &&
////			FinalKeyHypothesis[j][8] == (*keyptr)[2][0] && FinalKeyHypothesis[j][9] == (*keyptr)[2][1] && 
////			FinalKeyHypothesis[j][10] == (*keyptr)[2][2] && FinalKeyHypothesis[j][11] == (*keyptr)[2][3] &&
////			FinalKeyHypothesis[j][12] == (*keyptr)[3][0] && FinalKeyHypothesis[j][13] == (*keyptr)[3][1] && 
////			FinalKeyHypothesis[j][14] == (*keyptr)[3][2] && FinalKeyHypothesis[j][15] == (*keyptr)[3][3] ) {
////			printf("hugehurray! \n");
////		}
////	}
////	fclose(fptr_time);
////	return 0;
////}