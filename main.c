#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* itoa(long int value, char* result, int base) {
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
		if (tmp_value < 0) *ptr++ = '-';
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

	long claire = 0x40A7D989161A6223;
	printf("%ld\n", claire);
	char i[80]={0};
	itoa(claire,i,2);
	int b[65];
	strToIntBin(b,i,64);
	for(int j=0;j<64;j++){
		printf("%d", b[j]);
	}
	printf("\n");

	int rightTab[33] = {0};
	int leftTab[33] = {0};
	split32bit(b,leftTab,rightTab);
	for(int j=0;j<32;j++){
		printf("%d",leftTab[j]);
	}
	printf("\n\n avant expension\n");
	for(int j=0;j<32;j++){
		printf("%d",rightTab[j]);
	}
	printf("\n\n\n");

	printf("expension !!!!! \n\n");

	int resultExp[49] = {0};
	expansion(resultExp,e,rightTab);
	for(int j=0;j<48;j++){
		printf("%d",resultExp[j]);
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