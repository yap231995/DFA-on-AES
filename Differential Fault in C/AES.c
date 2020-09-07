#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t state_t[4][4];

static const uint8_t s_box[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
  
static const uint8_t inv_s_box[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };


static const uint8_t r_con[32] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A,
    0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A,
    0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39 };


void static SubBytes(state_t* matrix) {
	uint8_t i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j<4; j++){
			 (*matrix)[i][j] = s_box[(*matrix)[i][j]];
		}	
	}
}

void static InvSubBytes(state_t* matrix) {
	uint8_t i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			 (*matrix)[i][j] = inv_s_box[(*matrix)[i][j]];
		}	
	}
}

static void ShiftRows(state_t* matrix) {
	uint8_t temp;
	// Rotate 2nd row
	temp = (*matrix)[0][1];
	(*matrix)[0][1] = (*matrix)[1][1];
	(*matrix)[1][1] = (*matrix)[2][1];
	(*matrix)[2][1] = (*matrix)[3][1];
	(*matrix)[3][1] = temp;
	
	//Rotate 3rd row 
	temp = (*matrix)[0][2];
	(*matrix)[0][2] = (*matrix)[2][2];
	(*matrix)[2][2] = temp;
	temp = (*matrix)[1][2];
	(*matrix)[1][2] = (*matrix)[3][2];
	(*matrix)[3][2] = temp;
	//Rotate 4th row
	temp = (*matrix)[0][3];
	(*matrix)[0][3] = (*matrix)[3][3];
	(*matrix)[3][3] = (*matrix)[2][3];
	(*matrix)[2][3] = (*matrix)[1][3];
	(*matrix)[1][3] = temp;
}

static void InvShiftRows(state_t* matrix) {
	uint8_t temp;
	// Rotate 2nd row
	temp = (*matrix)[3][1];
	(*matrix)[3][1] = (*matrix)[2][1];
	(*matrix)[2][1] = (*matrix)[1][1];
	(*matrix)[1][1] = (*matrix)[0][1];
	(*matrix)[0][1] = temp;
	
	//Rotate 3rd row 
	temp = (*matrix)[0][2];
	(*matrix)[0][2] = (*matrix)[2][2];
	(*matrix)[2][2] = temp;
	temp = (*matrix)[1][2];
	(*matrix)[1][2] = (*matrix)[3][2];
	(*matrix)[3][2] = temp;
	//Rotate 4th row
	temp = (*matrix)[0][3];
	(*matrix)[0][3] = (*matrix)[1][3];
	(*matrix)[1][3] = (*matrix)[2][3];
	(*matrix)[2][3] = (*matrix)[3][3];
	(*matrix)[3][3] = temp;
}

uint8_t xtimes(uint8_t x) {
  if (x & 0x80) {
  	return (((x << 1)^0x1b) & 0xff);
  }
  else {
  	return (x<<1);
  }
}


static void MixColumn(state_t* matrix) {
	uint8_t i;
	for (i = 0; i < 4; i++) {
		uint8_t  t = (*matrix)[i][0]^(*matrix)[i][1]^(*matrix)[i][2]^(*matrix)[i][3];
    	uint8_t  u = (*matrix)[i][0];
    	(*matrix)[i][0] ^= xtimes((*matrix)[i][0]^(*matrix)[i][1]) ^ t;
    	(*matrix)[i][1] ^= xtimes((*matrix)[i][1]^(*matrix)[i][2]) ^ t;
    	(*matrix)[i][2] ^= xtimes((*matrix)[i][2]^(*matrix)[i][3]) ^ t;
    	(*matrix)[i][3] ^= xtimes((*matrix)[i][3]^u) ^ t;
    }
}


static void InvMixColumn(state_t* matrix) {
	uint8_t i;
	for (i = 0; i < 4; i++) {
        uint8_t u = xtimes(xtimes((*matrix)[i][0]^(*matrix)[i][2]));
        uint8_t v = xtimes(xtimes((*matrix)[i][1]^(*matrix)[i][3]));
        (*matrix)[i][0] ^= u;
        (*matrix)[i][1] ^= v;
        (*matrix)[i][2] ^= u;
        (*matrix)[i][3] ^= v;
    }
    MixColumn(matrix);
}

static void AddKeys(state_t* matrix, state_t* key_matrix) {
	uint8_t i,j;
	for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
        	(*matrix)[i][j]^= (*key_matrix)[i][j];
		}
    }
}


uint8_t** CreateKeys(state_t* key_matrix) {   //Look at The Design of Rijndael section 3.6.2
    uint8_t **W = (uint8_t **)malloc(44*sizeof(uint8_t *)); // W = [k_0,k_1,..., k_43] where each k_i is a column for 4. 
    ///// [k_i,k_i+1,k_i+2,k_i+3] is a round key for round i%4+1, where i multiple of 4, i=1,4,..,40
    uint8_t i,k,j,l,m;
    for (i=0 ; i < 4; i++) {
    	W[i] = (uint8_t*) malloc(4*sizeof(uint8_t));
    	for (k=0 ; k < 4; k++) {
    		W[i][k] =  (*key_matrix)[i][k];
		}
	}
    for (j=4 ; j < 4*11; j++) {
    	W[j] = (uint8_t*) malloc(4*sizeof(uint8_t)); 
    	if (j%4 == 0 ) {
    		uint8_t FirstElement =  W[j-4][0] ^ s_box[W[j-1][1]] ^ r_con[j/4];
    		W[j][0] = FirstElement;
    		for (l=1; l < 4; l++) {
    			W[j][l] = W[j-4][l]^s_box[W[j-1][(l+1)%4]];
			}
		} else {
			for (m = 0; m < 4; m++) {
				W[j][m] = W[j-4][m]^W[j-1][m];
			}
		}
	}  
    return W;
}

static uint8_t Random32Bits() {
	uint8_t x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;
	
	return x;
}



void RoundKey(uint8_t** W, int round, state_t* key) {
	uint8_t m,n;
	for (m= 0; m < 4; m++) {
		for (n = 0; n < 4; n++) {
			(*key)[m][n] = W[4*round+m][n];	
		}
	}
}



/////////////////////// Public Functions///////////////////////////////////


uint8_t SBox(uint8_t num) {
  return s_box[num];
}

 uint8_t InvSBox(uint8_t num) {
  return inv_s_box[num];
}

uint8_t Rcon(uint8_t num) {
  return r_con[num];
}




void PrintMatrix(state_t* matrix) {
	uint8_t i,j;
	for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", (*matrix)[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}


void PrintKeyArray(uint8_t** matrix) {
	uint8_t i,j;
	for (i = 0; i < 4; i++) {
        for (j = 0; j < 44; j++) {
            printf("%d ", (matrix)[j][i]);
        }
        printf("\n");
    }
    printf("\n");
} 

state_t * AESEncryption(state_t* plaintext, state_t* MasKeyPtr) {
	//Key Schedule
	uint8_t** W;
	W = CreateKeys(MasKeyPtr);
	//PrintKeyArray(W);
	
	//Initialise Round 0 key
	state_t key_matrix =  {{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* key_ptr = &key_matrix;
	RoundKey(W, 0, key_ptr);
	//printf("Round 0 key: \n");
	//PrintMatrix(key_ptr);
	
	//Add Round 0 key.
	AddKeys(plaintext, key_ptr);
	//Round 1-9.
	uint8_t i;
	for (i=1; i <10; i++) {
		SubBytes(plaintext);
		ShiftRows(plaintext);
		MixColumn(plaintext);
		RoundKey(W,i, key_ptr);
		AddKeys(plaintext, key_ptr);
		//printf("Round %d key: \n", i);
		//PrintMatrix(key_ptr);
	}
	
	//Round 10.
	SubBytes(plaintext);
	ShiftRows(plaintext);
	RoundKey(W,10,key_ptr); 
	AddKeys(plaintext, key_ptr);
	
	//printf("Round 10 key: \n");
	//PrintMatrix(key_ptr);
	
	//Free the memory allocation of key Schedule W.
	uint8_t j;
	for (j=0; j<44; ++j) {
  		free(W[j]);
	}
	free(W);
	
	return plaintext;
}

state_t * AESDecryption(state_t* ciphertext, state_t* MasKeyPtr) {

	//Key Schedule
	uint8_t** W;
	W = CreateKeys(MasKeyPtr);
	//PrintKeyArray(W);
	
	//Initialise Round 10 key
	state_t key_matrix =  {{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* key_ptr = &key_matrix;
	RoundKey(W, 10, key_ptr);
	
	//Add Round 10 key.
	AddKeys(ciphertext, key_ptr);
//	printf("Round 10 key: \n");
//	PrintMatrix(key_ptr);
	
	//Round 1-9.
	uint8_t i;
	for(i = 9; i > 0 ; --i) { 
		InvSubBytes(ciphertext);
		InvShiftRows(ciphertext);
		InvMixColumn(ciphertext);
		RoundKey(W, i, key_ptr);
		InvMixColumn(key_ptr);
		AddKeys(ciphertext, key_ptr);

//		printf("Round %d key: \n", 10-i);
//		PrintMatrix(key_ptr);
	}
	
	InvSubBytes(ciphertext);
	InvShiftRows(ciphertext);
	//Round 0 Key and add it.
	RoundKey(W,0,key_ptr); 
	AddKeys(ciphertext, key_ptr);
	
//	printf("Round 0 key: \n");
//	PrintMatrix(key_ptr);
	
	
	
	
	//Free the memory allocation of key Schedule W.
	uint8_t j;
	for(j=0; j< 44; ++j) {
  		free(W[j]);
	}
	free(W);
	
	
	return ciphertext;
}






	//uint8_t error = Random32Bits();
	//state_t error_matrix =  {{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	//state_t* error_ptr = &error_matrix;
	//AddKeys(plaintext, error_ptr);



state_t * AESEncryptionFaultyROUND9(state_t* plaintext, state_t* MasKeyPtr) {
	//Key Schedule
	uint8_t** W;
	W = CreateKeys(MasKeyPtr);
	//PrintKeyArray(W);
	
	//Initialise Round 0 key
	state_t key_matrix =  {{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* key_ptr = &key_matrix;
	RoundKey(W, 0, key_ptr);
//	printf("Round 0 key: \n");
//	PrintMatrix(key_ptr);
	
	//Add Round 0 key.
	AddKeys(plaintext, key_ptr);
	//Round 1-7.
	uint8_t i;
	for (i=1; i < 8; i++) {
		SubBytes(plaintext);
		ShiftRows(plaintext);
		MixColumn(plaintext);
		RoundKey(W,i, key_ptr);
		AddKeys(plaintext, key_ptr);
//		printf("Round %d key: \n", i);
//		PrintMatrix(key_ptr);
	}
	
	//Round 8
	SubBytes(plaintext);
	ShiftRows(plaintext);
	MixColumn(plaintext);
	RoundKey(W,8, key_ptr);
	AddKeys(plaintext, key_ptr);

	//Round 9
	uint8_t error = Random32Bits();
	state_t error_matrix =  {{error,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* error_ptr = &error_matrix;
	AddKeys(plaintext, error_ptr);
	SubBytes(plaintext);
	ShiftRows(plaintext);
	MixColumn(plaintext);
	RoundKey(W,9, key_ptr);
	AddKeys(plaintext, key_ptr);

	
	//Round 10.
	SubBytes(plaintext);
	ShiftRows(plaintext);
	RoundKey(W,10,key_ptr); 
	AddKeys(plaintext, key_ptr);
	
//	printf("Round 10 key: \n");
//	PrintMatrix(key_ptr);
	
	//Free the memory allocation of key Schedule W.
	uint8_t j;
	for (j=0; j<44; ++j) {
  		free(W[j]);
	}
	free(W);
	
	
	return plaintext;
}


state_t * AESEncryptionFaultyROUND8(state_t* plaintext, state_t* MasKeyPtr) {
	//Key Schedule
	uint8_t** W;
	W = CreateKeys(MasKeyPtr);
	//PrintKeyArray(W);
	
	//Initialise Round 0 key
	state_t key_matrix =  {{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* key_ptr = &key_matrix;
	RoundKey(W, 0, key_ptr);
//	printf("Round 0 key: \n");
//	PrintMatrix(key_ptr);
	
	//Add Round 0 key.
	AddKeys(plaintext, key_ptr);
	//Round 1-7.
	uint8_t i;
	for (i=1; i < 8; i++) {
		SubBytes(plaintext);
		ShiftRows(plaintext);
		MixColumn(plaintext);
		RoundKey(W,i, key_ptr);
		AddKeys(plaintext, key_ptr);
//		printf("Round %d key: \n", i);
//		PrintMatrix(key_ptr);
	}
	
	//Round 8
	//Add Error
	uint8_t error = Random32Bits();
	state_t error_matrix =  {{error,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
	state_t* error_ptr = &error_matrix;
	AddKeys(plaintext, error_ptr);
	
	SubBytes(plaintext);
	ShiftRows(plaintext);
	MixColumn(plaintext);
	RoundKey(W,8, key_ptr);
	AddKeys(plaintext, key_ptr);

	//Round 9
	SubBytes(plaintext);
	ShiftRows(plaintext);
	MixColumn(plaintext);
	RoundKey(W,9, key_ptr);
	AddKeys(plaintext, key_ptr);

	
	//Round 10.
	SubBytes(plaintext);
	ShiftRows(plaintext);
	RoundKey(W,10,key_ptr); 
	AddKeys(plaintext, key_ptr);
	
//	printf("Round 10 key: \n");
//	PrintMatrix(key_ptr);
	
	//Free the memory allocation of key Schedule W.
	uint8_t j;
	for (j=0; j<44; ++j) {
  		free(W[j]);
	}
	free(W);
	
	
	return plaintext;
}


//int main() {
//	state_t matrix = {{0x68, 0x98, 0x16, 0xd4},{0xd5, 0x30, 0x36, 0xa5},{0x00, 0x8c, 0xbc, 0xd3},{0xbb, 0x3c, 0x83, 0x53}};
//	state_t *ptrMatrix = &matrix;
//	printf("Original Text: \n");
//	PrintMatrix(ptrMatrix);
//	printf("\n");
//	
//	state_t* ciphertext;
//	ciphertext = AESEncryption(ptrMatrix);
//	printf("Encrypted Text: \n");
//	PrintMatrix(ciphertext);
//	
//	state_t* decryptedtext;
//	decryptedtext = AESDecryption(ptrMatrix);
//	printf("Decrypted Text: \n");
//	PrintMatrix(decryptedtext);
//	
	////Testing for SubByte and InvSubByte.
	//printf("SubByte: \n");
	//SubBytes(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
	//printf("Inverse SubByte: \n");
	//InvSubBytes(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
	////Testing for ShiftRows and InvShiftRows.
	//printf("ShiftRows: \n");
	//ShiftRows(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
	//printf("Inverse ShiftRow: \n");
	//InvShiftRows(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
 //   //Testing for MixColumn and InvMixColumn.
	//printf("MixColumn: \n");
	//MixColumn(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
	//printf("Inverse MixColumn: \n");
	//InvMixColumn(ptrMatrix);
	//PrintMatrix(ptrMatrix);
	//
	////  Testing for AddKeys.
	//state_t matrix1 = {{0x02,0x01, 0x01, 0x01},{0x01, 0x01,0x01, 0x01},{0x01, 0x01,0x01, 0x01},{0x01, 0x01,0x01, 0x01}};
	//state_t matrix2 = {{0x01,0x01, 0x01, 0x01},{0x00, 0x00,0x00, 0x00},{0x01, 0x01,0x01, 0x01},{0x01, 0x01,0x01, 0x01}};
	//state_t *ptrMatrix1 = &matrix1;
	//state_t *ptrMatrix2 = &matrix2;
	//PrintMatrix(ptrMatrix1);
	//PrintMatrix(ptrMatrix2);
	//printf("AddKeys: \n");
	//AddKeys(ptrMatrix1,ptrMatrix2);
	//PrintMatrix(ptrMatrix1);
	//PrintMatrix(ptrMatrix2);
	//
	////Testing for CreateKeys
	//uint8_t** keyschedule;
	//keyschedule = CreateKeys(ptrMatrix);
	//PrintKeyArray(keyschedule);
	//
//	return 0;
//}











