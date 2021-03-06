/*
 *
 * Chinese Academy of Sciences
 * State Key Laboratory of Information Security
 * Institute of Information Engineering
 *
 * Copyright (C) 2016 Chinese Academy of Sciences
 *
 * LuoPeng, luopeng@iie.ac.cn
 * Updated in May 2016
 *
 */

#include <stdio.h>

#include "aes.h"

int main(int argc, char *argv[]) {

	uint8_t i, r;

	/* 128 bit key */
	uint8_t key[] = {
		0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59, 
		0x0c, 0xb7, 0xad, 0xd6, 0xaf, 0x7f, 0x67, 0x98};

	uint8_t plain[] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
		0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};

	uint8_t cipher[BLOCK_SIZE_BYTE];
	
	uint8_t roundkeys[ROUND_KEY_SIZE];

	printf("\n--------------------------------------------------------\n");
	// key schedule
	aes_key_schedule_128(key, roundkeys);
	printf("Key:\n");
	for ( r = 0; r <= ROUNDS; r++ ) {
		for (i = 0; i < BLOCK_SIZE_BYTE; i++) {
			printf("%2x ", roundkeys[r*BLOCK_SIZE_BYTE+i]);
		}
		printf("\n");
	}
	printf("\n\n");


	// encryption
	// cipher text should be: 0x ff  b 84 4a  8 53 bf 7c 69 34 ab 43 64 14 8f b9
	aes_encrypt_128(roundkeys, plain, cipher);
	printf("Cipher text:\n");
	for (i = 0; i < BLOCK_SIZE_BYTE; i++) {
		printf("%2x ", cipher[i]);
	}
	printf("\n\n");


	// decryption
	aes_decrypt_128(roundkeys, cipher, plain);
	printf("Plain text:\n");
	for (i = 0; i < BLOCK_SIZE_BYTE; i++) {
		printf("%2x ", plain[i]);
	}
	printf("\n");

	return 0;

}
