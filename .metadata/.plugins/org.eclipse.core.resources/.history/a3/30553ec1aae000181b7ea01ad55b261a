/************************************************************************
Lab 9 Nios Software

Dong Kai Wang, Fall 2017
Christine Chen, Fall 2013

For use with ECE 385 Experiment 9
University of Illinois ECE Department
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "aes.h"

// Pointer to base address of AES module, make sure it matches Qsys
volatile unsigned int * AES_PTR = (unsigned int *) 0x00000040;

// Execution mode: 0 for testing, 1 for benchmarking
int run_mode = 0;

/** charToHex
 *  Convert a single character to the 4-bit value it represents.
 *  
 *  Input: a character c (e.g. 'A')
 *  Output: converted 4-bit value (e.g. 0xA)
 */
char charToHex(char c)
{
	char hex = c;

	if (hex >= '0' && hex <= '9')
		hex -= '0';
	else if (hex >= 'A' && hex <= 'F')
	{
		hex -= 'A';
		hex += 10;
	}
	else if (hex >= 'a' && hex <= 'f')
	{
		hex -= 'a';
		hex += 10;
	}
	return hex;
}

/** charsToHex
 *  Convert two characters to byte value it represents.
 *  Inputs must be 0-9, A-F, or a-f.
 *  
 *  Input: two characters c1 and c2 (e.g. 'A' and '7')
 *  Output: converted byte value (e.g. 0xA7)
 */

char charsToHex(char c1, char c2)
{
	char hex1 = charToHex(c1);
	char hex2 = charToHex(c2);
	return (hex1 << 4) + hex2;
}
void printState (unsigned int* state) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int rep = (state[j] & (0xff << (i*8))) >> (i*8);

			char a = (rep & 0xf0) >> 4;
			char b = (0xf & rep);
			printf("%c ", charsToHex(a,b));
		}
		printf("\n");
	}
}
unsigned int smallWord(unsigned int word)
{
	//printf("%x", word);
	unsigned int res = 0;
	for(int i = 0; i < 4; i++)
	{
		unsigned char key = word >> 8*i & 0xFF;
		res = aes_sbox[((key & 0xF0) >> 4) * 16 + (key & 0xf)] << 8 * i | res;
	}
	//printf("%x", res);
	return res;
}
void KeyExpansion(unsigned char *cipher_key, unsigned int* word)
{
	for (int j = 0; j < 16; j++) {
		//printf("%x", cipher_key[j]);
		//printf("\n");
	}

	for(int i = 0; i < 4; i++) {
		//Assemble word from cipher key
		for (int j = 0; j < 4; j++) {
			//word[j] |= cipher_key[(4 * i) + 4 - j - 1] << j * 8;
			word[j]= (int)cipher_key[j*4]<<24 | (int)cipher_key[j*4+1]<<16 | (int)cipher_key[j*4+2]<<8 | (int)cipher_key[j*4+3];
			//printf("%x", word[j]);
			//printf("\n");
		}
		for(int j = 4; j < 44; j++) {
			unsigned int store = word[j - 1];
			if (j % 4 == 0) {
				// Represents rotated word wrap around
				store = smallWord((store << 8 | store >> 24)) ^ Rcon[(j / 4)];
			}
			word[j] = word[j - 4] ^ store;
			//printf("%x", word[j]);
			//printf("\n");
		}
	}
}

void AddRoundKey(unsigned char* state, unsigned int* w, int round_key_num)
{
	unsigned int * key_num;
	int r_key = 0;
	int key = 0;
	int idx= 0;
	for(int i = round_key_num * 4; i < (round_key_num + 1) * 4; i++)
	{

		key_num[idx++] = w[i];
	}
	for(int i = 0; i < 16; i++)
	{
		state[i] = state[i] ^ ((key_num[key] >> (24 - (8 * r_key))) & 0xFF);

		if(++r_key == 4)
		{
			r_key = 0;
			key++;
		}
	}
}
// Pass in pointer to first elem in 2d char arr
void subBytes(unsigned char* state)
{
	for(int i = 0; i<16; i++){
		// Get top char loc
		int shift = (state[i] & 0xf0) >> 4;
		state[i] = aes_sbox[(shift * 16) + (state[i] & 0xf)];
	}
}

void shiftRow(unsigned char* state)
{
	for(int s = 0; s < 4; s++) {
		for (int i = 0; i < s; i++) {
			// Save char at s
			unsigned char begin = state[s];
			// Shift to the right position
			for (int j = 0; j < 3; j++) {
				state[j * 4 + s] = state[((j + 1) * 4) + s];
			}
			// Assign back the saved char
			state[12 + s] = begin;
		}
	}
}

void mixColumns(unsigned char* state)
{
	for (int i = 0; i < 4; i++) {
		unsigned int num;
		//Assemble current row
		num = (int)state[i*4]<<24 | (int)state[i*4+1]<<16 | (int)state[i*4+2]<<8 | (int)state[i*4+3];
		// Follow mixing algorithm
		state[4 * i] = gf_mul[(num >> 24) & 0xff][0] ^ gf_mul[(num >> 16) & 0xff][1] ^ ((num >> 8) & 0xff) ^ (num & 0xff);
		state[(4 * i)+1] = ((num >> 24) & 0xff) ^ gf_mul[(num >> 16) & 0xff][0] ^ gf_mul[(num >> 8) & 0xff][1] ^ (num & 0xff);
		state[(4 * i)+2] = ((num >> 24) & 0xff) ^ ((num >> 16) & 0xff) ^ gf_mul[(num >> 8) & 0xff][0] ^ gf_mul[num & 0xff][1];
		state[(4 * i)+3] = gf_mul[(num >> 24) & 0xff][1] ^ ((num >> 16) & 0xff) ^ ((num >> 8) & 0xff) ^ gf_mul[num & 0xff][0];
	}
}

/** encrypt
 *  Perform AES encryption in software.
 *
 *  Input: msg_ascii - Pointer to 32x 8-bit char array that contains the input message in ASCII format
 *         key_ascii - Pointer to 32x 8-bit char array that contains the input key in ASCII format
 *  Output:  msg_enc - Pointer to 4x 32-bit int array that contains the encrypted message
 *               key - Pointer to 4x 32-bit int array that contains the input key
 */
void encrypt(unsigned char * msg_ascii, unsigned char * key_ascii, unsigned int * msg_enc, unsigned int * key)
{
	//printState(msg_enc);
	unsigned int word[44];
	unsigned char msg_hex[16];
	unsigned char key_hex[16];

	for(int i = 0; i<16;i++){
		msg_hex[i] = charsToHex(msg_ascii[i*2],msg_ascii[i*2+1]);
		key_hex[i] = charsToHex(key_ascii[i*2],key_ascii[i*2+1]);
		//printf("%x", key_hex[i]);
		//printf("\n");
	}
	for(int i = 0; i<16; i++){
		printf("%x", msg_hex[i]);
		if(i%4 ==3){
			printf("\n");
		}
	}
	printf("\n");
	//printf("***** \n");
	for(int i = 0; i<4; i++){
		key[i] = (int)key_hex[i*4]<<24 | (int)key_hex[i*4+1]<<16 | (int)key_hex[i*4+2]<<8 | (int)key_hex[i*4+3];
	}
	KeyExpansion(key_hex, word);
	AddRoundKey(msg_hex, word, 0);
	for(int i = 0; i<16; i++){
		printf("%x", msg_hex[i]);
		if(i%4 ==3){
			printf("\n");
		}
	}
	printf("\n");
	for(int r = 1; r < 10; r++)
	{
		subBytes(msg_hex);
		for(int i = 0; i<16; i++){
			printf("%x", msg_hex[i]);
			if(i%4 ==3){
				printf("\n");
			}
		}
		printf("\n");
		shiftRow(msg_hex);
		for(int i = 0; i<16; i++){
			printf("%x", msg_hex[i]);
			if(i%4 ==3){
				printf("\n");
			}
		}
		printf("\n");
		mixColumns(msg_hex);
		for(int i = 0; i<16; i++){
			printf("%x", msg_hex[i]);
			if(i%4 ==3){
				printf("\n");
			}
		}
		printf("\n");
		AddRoundKey(msg_hex, word, r);
		for(int i = 0; i<16; i++){
			printf("%x", msg_hex[i]);
			if(i%4 ==3){
				printf("\n");
			}
		}
		printf("\n");
	}
	subBytes(msg_hex);
	shiftRow(msg_hex);
	AddRoundKey(msg_hex, word, 10);
	for(int i = 0; i<16; i++){
		printf("%x", msg_hex[i]);
		if(i%4 ==0){
			printf("\n");
		}
	}
	for(int i = 0; i<4; i++){
		msg_enc[i] = (int)msg_hex[i*4]<<24 | (int)msg_hex[i*4+1]<<16 | (int)msg_hex[i*4+2]<<8 | (int)msg_hex[i*4+3];
	}

}
/** decrypt
 *  Perform AES decryption in hardware.
 *
 *  Input:  msg_enc - Pointer to 4x 32-bit int array that contains the encrypted message
 *              key - Pointer to 4x 32-bit int array that contains the input key
 *  Output: msg_dec - Pointer to 4x 32-bit int array that contains the decrypted message
 */
void decrypt(unsigned int * msg_enc, unsigned int * msg_dec, unsigned int * key)
{
	// Implement this function
}

/** main
 *  Allows the user to enter the message, key, and select execution mode
 *
 */
int main()
{
	printf("Starting processor\n");
	// Input Message and Key as 32x 8-bit ASCII Characters ([33] is for NULL terminator)
	unsigned char msg_ascii[33];
	unsigned char key_ascii[33];
	// Key, Encrypted Message, and Decrypted Message in 4x 32-bit Format to facilitate Read/Write to Hardware
	unsigned int key[4];
	unsigned int msg_enc[4];
	unsigned int msg_dec[4];

	printf("Select execution mode: 0 for testing, 1 for benchmarking: ");
	scanf("%d", &run_mode);

	if (run_mode == 0) {
		// Continuously Perform Encryption and Decryption
		while (1) {
			int i = 0;
			printf("\nEnter Message:\n");
			scanf("%s", msg_ascii);
			printf("\n");
			printf("\nEnter Key:\n");
			scanf("%s", key_ascii);
			printf("\n");
			AES_PTR[0] = key[0];
			AES_PTR[1] = key[1];
			AES_PTR[2] = key[2];
			AES_PTR[3] = key[3];
			encrypt(msg_ascii, key_ascii, msg_enc, key);
			printf("\nEncrpted message is: \n");
			for(i = 0; i < 4; i++){
				printf("%08x", msg_enc[i]);
			}
			printf("\n");
			decrypt(msg_enc, msg_dec, key);
			printf("\nDecrypted message is: \n");
			for(i = 0; i < 4; i++){
				printf("%08x", msg_dec[i]);
			}
			printf("\n");
		}
	}
	else {
		// Run the Benchmark
		int i = 0;
		int size_KB = 2;
		// Choose a random Plaintext and Key
		for (i = 0; i < 32; i++) {
			msg_ascii[i] = 'a';
			key_ascii[i] = 'b';
		}
		// Run Encryption
		clock_t begin = clock();
		for (i = 0; i < size_KB * 64; i++)
			encrypt(msg_ascii, key_ascii, msg_enc, key);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		double speed = size_KB / time_spent;
		printf("Software Encryption Speed: %f KB/s \n", speed);
		// Run Decryption
		begin = clock();
		for (i = 0; i < size_KB * 64; i++)
			decrypt(msg_enc, msg_dec, key);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		speed = size_KB / time_spent;
		printf("Hardware Encryption Speed: %f KB/s \n", speed);
	}
	return 0;
}
