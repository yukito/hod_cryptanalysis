#include <stdio.h>

void genkey(unsigned char *rkey, const unsigned char *mkey);
void setText(unsigned char *ptext, unsigned char *L1, unsigned char *L2);
void outputText(unsigned char *ptext, unsigned char *L1, unsigned char *L2);
void katan48_encrypt(unsigned char *ptext, const unsigned char *mkey);
void katan64_encrypt(unsigned char *ptext, const unsigned char *mkey);
void katan64_decrypt(unsigned char *ptext, const unsigned char *mkey);

void print_mesg(char *mesg);
void dumpText(unsigned char *text);
void hexa_to_bin(int *hexatext, unsigned char *bintext);

void initPlaintext(int *ptext);

#define BLOCK 64
#define ROUND 32

static const int L1_size=BLOCK-BLOCK/16*10+1;
static const int L2_size=BLOCK/16*10-1;

const unsigned char IR[254]={
	1,1,1,1,1,1,1,0,0,0,
	1,1,0,1,0,1,0,1,0,1,
	1,1,1,0,1,1,0,0,1,1,
	0,0,1,0,1,0,0,1,0,0,
	0,1,0,0,0,1,1,0,0,0,
	1,1,1,1,0,0,0,0,1,0,
	0,0,0,1,0,1,0,0,0,0,
	0,1,1,1,1,1,0,0,1,1,
	1,1,1,1,0,1,0,1,0,0,
	0,1,0,1,0,1,0,0,1,1,
	0,0,0,0,1,1,0,0,1,1,
	1,0,1,1,1,1,1,0,1,1,
	1,0,1,0,0,1,0,1,0,1,
	1,0,1,0,0,1,1,1,0,0,
	1,1,0,1,1,0,0,0,1,0,
	1,1,1,0,1,1,0,1,1,1,
	1,0,0,1,0,1,1,0,1,1,
	0,1,0,1,1,1,0,0,1,0,
	0,1,0,0,1,1,0,1,0,0,
	0,1,1,1,0,0,0,1,0,0,
	1,1,1,1,0,1,0,0,0,0,
	1,1,1,0,1,0,1,1,0,0,
	0,0,0,1,0,1,1,0,0,1,
	0,0,0,0,0,0,1,1,0,1,
	1,1,0,0,0,0,0,0,0,1,
	0,0,1,0};
/*
int main()
{
	unsigned char ptext[BLOCK];
	unsigned char mkey[80];
	int i;

	for(i=0;i<80;i++)
		mkey[i]=0;
	for(i=0;i<64;i++)
		ptext[i]=1;
	katan64_encrypt(ptext,mkey);
//	katan64_decrypt(ptext,mkey);
	dumpText(ptext);
}
*/

void genkey(unsigned char *rkey, const unsigned char *mkey)
{
	int cntr=0;

	for(;cntr<80;cntr++){
		rkey[cntr]=mkey[cntr];
	}
	for(;cntr<ROUND*2;cntr++){
		rkey[cntr]=rkey[cntr-80]^rkey[cntr-61]^rkey[cntr-50]^rkey[cntr-13];
	}
}

void setText(unsigned char *ptext, unsigned char *L1, unsigned char *L2)
{
	int i=0;
	for(;i<L2_size;i++)
		L2[i]=ptext[i];
	for(;i<BLOCK;i++)
		L1[i-L2_size]=ptext[i];
}

void outputText(unsigned char *ptext, unsigned char *L1, unsigned char *L2)
{
	int i=0;
	for(;i<L1_size;i++)
		ptext[i]=L1[L1_size-1-i];
	for(;i<BLOCK;i++)
		ptext[i]=L2[L2_size-1-i+L1_size];
}

void outputText2(unsigned char *ptext, unsigned char *L1, unsigned char *L2)
{
	int i=0;
	for(;i<L1_size;i++)
		L1[i]=ptext[i];
	for(;i<BLOCK;i++)
		L2[i+L1_size]=ptext[i];
}
	
void katan48_encrypt(unsigned char *ptext, const unsigned char *mkey)
{
	unsigned char L1[L1_size],L2[L2_size];
	unsigned char rkey[ROUND*2];
	int i;
	int r;
	unsigned char fa_0, fa_1, fb_0, fb_1;
	unsigned char ka,kb;

	setText(ptext, L1, L2);
	genkey(rkey, mkey);

	for(r=0;r<254;r++){
		ka=rkey[r*2];
		kb=rkey[r*2+1];

		fa_1=L1[18]^L1[12]^(L1[15]&L1[7])^(L1[6]&IR[r])^ka;
		fb_1=L2[28]^L2[19]^(L2[21]&L2[13])^(L2[15]&L2[6])^kb;
		fa_0=L1[17]^L1[11]^(L1[14]&L1[6])^(L1[5]&IR[r])^ka;
		fb_0=L2[27]^L2[18]^(L2[20]&L2[12])^(L2[14]&L2[5])^kb;

		for(i=L1_size-1;i>1;i--)
			L1[i]=L1[i-2];
		for(i=L2_size-1;i>1;i--)
			L2[i]=L2[i-2];

		L1[0]=fb_0;
		L1[1]=fb_1;
		L2[0]=fa_0;
		L2[1]=fa_1;
	}	
	outputText(ptext, L1, L2);
}

void katan64_encrypt(unsigned char *ptext, const unsigned char *mkey)
{
	unsigned char L1[L1_size],L2[L2_size];
	unsigned char rkey[254*2];
	int i;
	int r;
	unsigned char fa_0, fa_1, fa_2, fb_0, fb_1, fb_2;
	unsigned char ka,kb;

	setText(ptext, L1, L2);
	genkey(rkey, mkey);

	for(r=0;r<ROUND;r++){
		ka=rkey[r*2];
		kb=rkey[r*2+1];

		fa_2=L1[24]^L1[15]^(L1[20]&L1[11])^(L1[9]&IR[r])^ka;
		fb_2=L2[38]^L2[25]^(L2[33]&L2[21])^(L2[14]&L2[9])^kb;
		fa_1=L1[23]^L1[14]^(L1[19]&L1[10])^(L1[8]&IR[r])^ka;
		fb_1=L2[37]^L2[24]^(L2[32]&L2[20])^(L2[13]&L2[8])^kb;
		fa_0=L1[22]^L1[13]^(L1[18]&L1[9])^(L1[7]&IR[r])^ka;
		fb_0=L2[36]^L2[23]^(L2[31]&L2[19])^(L2[12]&L2[7])^kb;

		for(i=L1_size-1;i>2;i--)
			L1[i]=L1[i-3];
		for(i=L2_size-1;i>2;i--)
			L2[i]=L2[i-3];

		L1[0]=fb_0;
		L1[1]=fb_1;
		L1[2]=fb_2;
		L2[0]=fa_0;
		L2[1]=fa_1;
		L2[2]=fa_2;
	}	
	outputText(ptext, L1, L2);
}

void katan64_decrypt(unsigned char *ptext, const unsigned char *mkey)
{
	unsigned char L1[L1_size],L2[L2_size];
	unsigned char rkey[254*2];
	int i;
	int r;
	unsigned char fa_0, fa_1, fa_2, fb_0, fb_1, fb_2;
	unsigned char ka,kb;

	setText(ptext, L1, L2);
	genkey(rkey, mkey);

	for(r=ROUND-1;r>=0;r--){
		kb=rkey[r*2+1];
		ka=rkey[r*2];

		L1[0]=fb_0;
		L1[1]=fb_1;
		L1[2]=fb_2;
		L2[0]=fa_0;
		L2[1]=fa_1;
		L2[2]=fa_2;

		for(i=0;i<L1_size-3;i++)
			L1[i]=L1[i+3];
		for(i=0;i<L2_size-3;i++)
			L2[i]=L2[i+3];

		L1[24]=fa_2^L1[15]^(L1[20]&L1[11])^(L1[9]&IR[r])^ka;
		L2[38]=fb_2^L2[25]^(L2[33]&L2[21])^(L2[14]&L2[9])^kb;
		L1[23]=fa_1^L1[14]^(L1[19]&L1[10])^(L1[8]&IR[r])^ka;
		L2[37]=fb_2^L2[24]^(L2[32]&L2[20])^(L2[13]&L2[8])^kb;
		L1[22]=fa_0^L1[13]^(L1[18]&L1[9])^(L1[7]&IR[r])^ka;
		L2[36]=fb_0^L2[23]^(L2[31]&L2[19])^(L2[12]&L2[7])^kb;

	}	
	outputText(ptext, L1, L2);
}

void print_mesg(char *mesg)
{
	printf("%s",mesg);
}

void dumpText(unsigned char *text)
{
	int i,j;
	for(i=0;i<BLOCK/4;i++){
		for(j=i*4;j<i*4+4;j++){
			printf("%X", text[j]);
		}
		printf(" ");
	}
	printf("\n");
}

void hexa_to_bin(int *hexatext, unsigned char *bintext)
{
	int i=0,j;
	for(;i<BLOCK/16;i++){
		for(j=i*16;j<i*16+16;j++){
			bintext[i*16*2+16-j-1]=hexatext[i]&1;
			hexatext[i] >>= 1;
		}
	}
}

void initPlaintext(int *ptext)
{
	ptext[0]=0x0;
	ptext[1]=0x0;
	ptext[2]=0x0;
	ptext[3]=0x0;
}
	
