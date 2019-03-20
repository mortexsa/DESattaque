#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* itoa(long value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		long tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		//if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

void strToIntBin(int *tab,char *string,int nbrBit){	
	int b = nbrBit-strlen(string);
	for(int j=0;j<nbrBit;j++)
		tab[j] = 0;
	for(int i=b;i<nbrBit;i++){
		tab[i] = string[i-b]-48;
	}
}

long puissance(int a,int b){
	if(b == 0){
		return 1;
	} else {
		return a*puissance(a,b-1);
	}
}

long TabtoLong(int *tab,int nbrBit){	
	long nombre=0;
	int i=0,j=nbrBit-1;
	while(j>=0){
		if(tab[j] != 0){
			nombre += puissance(2,i);
		}
		i++;
		j--;
	}
	return nombre;
}

void Permutation(int *resultat,const int *tableDePermutation, int *aPermuter, int nbrBit){
	for(int i=0;i<nbrBit;i++){
		resultat[i] = aPermuter[tableDePermutation[i]-1];
	}
}

void split32bit(int *completTab,int *leftTab,int *rightTab){
	for(int i=0;i<32;i++){
		leftTab[i] = completTab[i];
		rightTab[i] = completTab[i+32];
	}
}

void expansion(int *tabResultant,const int *tabExpansion,int *tabAvantExpansion){
	Permutation(tabResultant,tabExpansion,tabAvantExpansion,48);
}

void xor(int *tabResult, int *premierK, int *deuxiemeK, int nbrBit){
	for(int i=0;i<nbrBit;i++){
		tabResult[i] = premierK[i] ^ deuxiemeK[i];
	}
}

void longToBin(int *tabResult, long hexa, int nbrBit){
	char str[80]={0};
	itoa(hexa,str,2);
	strToIntBin(tabResult,str,nbrBit);
}

int main(){

	const int ip[65] = {
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
	};

	const int e[49] = {
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1
	};

	long claire = 0x864C804BB6B905BA;
	printf("%lx\n", claire);
	int b[65];
	longToBin(b,claire,64);
	for(int j=0;j<64;j++){
		printf("%d", b[j]);
	}
	printf("\n");
	
	long claire2 = 0x8448800BB6B805BE;
	printf("%lx\n", claire2);
	int b2[65];
	longToBin(b2,claire2,64);
	for(int j=0;j<64;j++){
		printf("%d", b2[j]);
	}
	printf("\n\n\n");
	Permutation(b,ip, b,64);
	Permutation(b2,ip, b2,64);
	int rightTab1[33] = {0};
	int leftTab1[33] = {0};
	split32bit(b,leftTab1,rightTab1);
	for(int j=0;j<32;j++){
		printf("%d",rightTab1[j]);
	}
	printf("\n");
	int rightTab2[33] = {0};
	int leftTab2[33] = {0};
	split32bit(b2,leftTab2,rightTab2);
	for(int j=0;j<32;j++){
		printf("%d",rightTab2[j]);
	}
	printf("\n");
	int resultExpXor[33] = {0};
	xor(resultExpXor,rightTab1, rightTab2,32);
	for(int j=0;j<32;j++){
		printf("%d",resultExpXor[j]);
	}
	printf("\n");
	printf("expension !!!!! \n\n");

	int resultExpRight[49] = {0};
	int resultExpRight2[49] = {0};
	
	expansion(resultExpRight,e,rightTab1);
	expansion(resultExpRight2,e,rightTab2);
	for(int j=0;j<48;j++){
		printf("%d",resultExpRight[j]);
	}
	printf("\n");
	for(int j=0;j<48;j++){
		printf("%d",resultExpRight2[j]);
	}
	printf("\n");


	// int permut[65] = {0};
	// Permutation(permut,ip,b,64);
	// for(int j=0;j<64;j++){
	// 	printf("%d",permut[j]);
	// }
	// printf("\n");


	return 0;
}