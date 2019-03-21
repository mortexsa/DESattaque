#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexatobinary(int *tabResult, long hexa, int nbrBit){
	long tmp = hexa;
	int entier;
	int compteur = nbrBit*4-1;
	for(int j=0;j<nbrBit;j++){
		entier = tmp & 0xF;
		for(int i=0;i<4;i++){

			tabResult[compteur] = entier % 2;
			entier = entier / 2;
			compteur--;
		}
		tmp = tmp >> 4;
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

int bitFauter(int *tabJuste, int *tabFaux) {
	int tabxor[33] = {0};
	xor(tabxor, tabJuste, tabFaux, 32);
	for(int j=0;j<32;j++){
		if(tabxor[j] == 1){
			return j;
		}
	}
	return -1;
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

	const int pMois1[33] = {
		9,17,23,31,
		13,28,2,18,
		24,16,30,6,
		26,20,10,1,
		8,14,25,3,
		4,29,11,19,
		32,12,22,7,
		5,27,15,21
	};

	const int sbox1[4][16] = {
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	};


	int tab1[64] = {0};
	int tab2[64] = {0};
	int tab1P[64] = {0};
	int tab2P[64] = {0};
	long chiffrer = 0x864C804BB6B905BA;
	hexatobinary(tab1,chiffrer,16);
	Permutation(tab1P, ip, tab1, 64);
	chiffrer = 0x864D804BB6B985BE;
	hexatobinary(tab2,chiffrer,16);
	Permutation(tab2P, ip, tab2, 64);
	
	int tabright1[33] = {0};
	int tabright2[33] = {0};
	int tableft1[33] = {0};
	int tableft2[33] = {0};
	split32bit(tab1P,tableft1,tabright1);
	split32bit(tab2P,tableft2,tabright2);
	int bitfaux = bitFauter(tabright1,tabright2);

	int tabExp1[49] = {0};
	int tabExp2[49] = {0};
	expansion(tabExp1,e,tabright1);
	expansion(tabExp2,e,tabright2);

	//p - 1 pour le left tableau just 
	int tabPmoin1[33] = {0};
	Permutation(tabPmoin1,pMois1, tableft1, 32);
	for(int i=0;i<32;i++){
		printf("%d", tableft1[i]);
	}
	printf("\n");
	for(int i=0;i<32;i++){
		printf("%d", tabPmoin1[i]);
	}
	printf("\n");
	
	



	return 0;
}