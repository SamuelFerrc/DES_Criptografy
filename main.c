#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
    unsigned char b7;

}  block8b;

typedef union {
    block8b x;
    unsigned long int y;
} block;



void PrintqBit(unsigned long int value) {
    unsigned long long int x = 1;

}
unsigned long int IP(unsigned long int x)
{
    unsigned long int bits[64];
    unsigned long int PC1[] = {57,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7};

    bits[0] = 1;
    for (int i=1; i<64;i++) { bits[i] = bits[i-1] << 1; }
    //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

    for (int j=1; j<64; j++) { PC1[j]--;   }

    unsigned long int y = 0;

    for (int j=0; j<64;j++) {
        if ((x & bits[PC1[j] ]) ==bits[PC1[j]] )
        {
            y += bits[j];
        }
    }


    return y;
}
unsigned long int IP_1(unsigned long int x)
{
    unsigned long int bits[64];
    unsigned long int PC1[] = {39,8,48,15,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25};

    bits[0] = 1;
    for (int i=1; i<64;i++) { bits[i] = bits[i-1] << 1; }
    //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

    for (int j=1; j<64; j++) { PC1[j]--;   }


    unsigned long int y = 0;

    for (int j=0; j<64;j++) {
        if ((x & bits[PC1[j] ]) == bits[PC1[j]] )
        {
            y += bits[j];
        }
    }

    return y;
}
unsigned long int PC1_Perm(unsigned long int x)
{
      unsigned long int bits[64];
    unsigned long int PC1[] = {58,49,41,33,25,17, 9,
                                1,58,50,42,34,26,18,
                               10, 2,59,51,43,35,27,
                               19,11, 3,60,52,44,36,
                               63,55,47,39,31,23,15,
                                7,62,54,46,38,30,22,
                               14, 6,61,53,45,37,29,
                               21,13, 5,28,20,12, 4};

    bits[0] = 1;
    for (int i=1; i<64;i++) { bits[i] = bits[i-1] << 1; }
    //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

    for (int j=1; j<56; j++) { PC1[j]--;   }

    unsigned long int y = 0;

    for (int j=0; j<56;j++) {
       if ((x & bits[PC1[j]]) == bits[PC1[j]] )
       {
           y += bits[j];
       }
    }

    return y;
}

unsigned long int PC2_Perm(unsigned long int x)
{
      unsigned long int bits[64];
    unsigned long int PC2[] = {14,17,11,24,1,5,
        3,28,15,6,21,10,
        23,19,12,4,26,8,
        16,7,27,20,13,2,
        41,52,31,37,47,55,
        30,40,51,45,33,48,
        44,49,39,56,34,53,
        46,42,50,36,29,32
    };

    bits[0] = 1;
    for (int i=1; i<64;i++) { bits[i] = bits[i-1] << 1; }
    //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

    for (int j=1; j<48; j++) { PC2[j]--;   }

    unsigned long int y = 0;

    for (int j=0; j<48;j++) {
       if ((x & bits[PC2[j]]) == bits[PC2[j]] )
       {
           y += bits[j];
       }
    }

    return y;
}
block IntToBlock(unsigned long int Value) {
    block value;
    value.y = Value;
    return value;
}
//Tem que trocar todas as permutações
void SlashBits56(block value, block *a, block *b) {

    a->x.b0 = value.x.b0;
    a->x.b1 = value.x.b1;
    a->x.b2 = value.x.b2;

    b->x.b0 = value.x.b3;
    b->x.b1 = value.x.b4;
    b->x.b2 = value.x.b5;

    a->y = a->y << 1;
    a->x.b3 = 0;
    if(a->x.b3 > 0)
        a->x.b0 += 1;

    b->y = b->y << 1;
    b->x.b3 = 0;
    if(b->x.b3 > 0)
        b->x.b0 += 1;
}

void MergeBits56(block *value, block right, block left)
{
    value->x.b0 = right.x.b0;
    value->x.b1 = right.x.b1;
    value->x.b2 = right.x.b2;
    value->x.b3 = left.x.b0;
    value->x.b4 = left.x.b1;
    value->x.b5 = left.x.b2;


}
void GenerateKeys(unsigned long int value, block *out, block*left, block*right)
{
    unsigned long int pc1tValue = PC1_Perm(value);

    printf("\npc1tValue == %lu", pc1tValue);

    block valueA = IntToBlock(pc1tValue);
    SlashBits(valueA, &right,&left);
    printf("\nright == %lu", right.y);
    printf("\nleft == %lu", left.y);
    valueA.y = 0;
    MergeBits(&valueA, right,left);

    printf("\nmergeBits == %lu", valueA.y);

    valueA.y = PC2_Perm(valueA.y);

    out->y = valueA.y;
    out->x.b7 = 0;
    out->x.b6 = 0;

    printf("\npc2Value == %lu", valueA.y);

}



int main() {
    srand(time(NULL));
    block key = {0};
    GenerateKeys(7, &key);
    printf("\nValor da Chave: %lu", key.y);
    // unsigned long int iv = rand() % 100;
    // unsigned long int x = 1;
    // unsigned long int valueToCompare = iv;
    // unsigned long int y = valueToCompare;
    // unsigned long int valueToXor = 0;
    // for(int i =0; i < (sizeof(x) * 8)/64; i++)
    // {
    //     valueToCompare = y;
    //     valueToXor = x ^ valueToCompare;
    //     y = IP(valueToXor);
    //     y = IP_1(y);
    //
    // }
    // printf("\nValor usado de X: %lu", x);
    // printf("\nValor final de Y: %lu", y);
    // printf("\nValor comparador: %lu", valueToCompare);
    // printf("\nValor pos xOR: %lu\n", valueToXor);
    // PrintBit(x);
    // PrintBit(y);
    // PrintBit(valueToCompare);
    // PrintBit(valueToXor);

    return 0;
}

// x ==    1; y = PC1(x) ==               128 = 2^{7}
// x ==    2; y = PC1(x) ==             32768 = 2^{15}
// x ==    4; y = PC1(x) ==           8388608 = 2^{23}
// x ==    8; y = PC1(x) == 36028797018963968 = 2^{55}
// x ==   16; y = PC1(x) ==  2251799813685248 = 2^{51}
// x ==   32; y = PC1(x) ==     8796093022208 = 2^{43}
// x ==   64; y = PC1(x) ==       34359738368 = 2^{35}
// x ==  128; y = PC1(x) ==               256 = 2^{8}
// x ==  512; y = PC1(x) ==             16384 = 2^{14}
// x == 1024; y = PC1(x) ==           4194304 = 2^{22}