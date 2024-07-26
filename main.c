    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdint.h>
    #include <math.h>
    #define my_max (INT64_MAX)

    int roundsShift[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    unsigned long int bits[64];


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

    int bitson() {
        bits[0] = 1;
        for(int i =1 ; i < 64;i++){
            bits[i]= bits[i -1] << 1;
        }
        return (0);
    }

    void PrintqBit(unsigned long int value) {
        unsigned long int x = 1;
        //printf("\n");
        for(int i = 63; i > -1;i--) {
            if((i + 1) % 8 == 0) printf(" ");
            printf((value & (x << i)) == (x << i) ?  "1": "0");
        }
    }
    unsigned long int IP(unsigned long int x)
    {
        unsigned long int PC1[] = {57,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7};

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
        unsigned long int PC1[] = {39,8,48,15,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25};

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
        unsigned long int PC1[] = {58,49,41,33,25,17, 9,
                                    1,58,50,42,34,26,18,
                                   10, 2,59,51,43,35,27,
                                   19,11, 3,60,52,44,36,
                                   63,55,47,39,31,23,15,
                                    7,62,54,46,38,30,22,
                                   14, 6,61,53,45,37,29,
                                   21,13, 5,28,20,12, 4};

        //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

        for (int j=1; j<56; j++) { PC1[j]--;   }

        unsigned long int y = 0;

        for (int j=0; j<56;j++) {
           if ((x & bits[PC1[j]]) == bits[PC1[j]] )
           {
               y += bits[j];
           }
        }
        printf("\npc1Bits == ");
        PrintqBit(y);
        return y;
    }

    unsigned long int PC2_Perm(unsigned long int x)
    {
        unsigned long int PC2[] = {14,17,11,24,1,5,
            3,28,15,6,21,10,
            23,19,12,4,26,8,
            16,7,27,20,13,2,
            41,52,31,37,47,55,
            30,40,51,45,33,48,
            44,49,39,56,34,53,
            46,42,50,36,29,32
        };

        //for (int i=0; i<64;i++) { printf("\n%d %lu ",i, bits[i]); }

        for (int j=1; j<48; j++) { PC2[j]--;   }

        unsigned long int y = 0;

        for (int j=0; j<48;j++) {
           if ((x & bits[PC2[j]]) == bits[PC2[j]] )
           {
               y += bits[j];
           }
        }
        printf("\npc2Bits   == ");

        PrintqBit(y);
        printf("         :     %lu", y);
        return y;

    }

    unsigned int P(int value) {
        unsigned long int P[] = {16,7,20,21,
            29,12,28,17,
            1,15,23,26,
            5,18,31,10,
            2,8,24,14,
            32,27,3,9,
            19,13,30,6,
            22,11,4,25
        };

        for (int j=0; j<32; j++) { P[j]--;   }

        unsigned long int y = 0;

        for (int j=0; j<32;j++) {
            if ((value & bits[P[j]]) == bits[P[j]] )
            {
                y += bits[j];
            }
        }
        printf("\nBits Normais     == ");
        PrintqBit(value);
        printf("\nBits Permutados  == ");
        PrintqBit(y);
    }

    block IntToBlock(unsigned long int Value) {
        block value = {0};
        value.y = Value;
        return value;
    }
    void LeftShift(block *a, int shift)
    {
        a->y = a->y << shift;

        if((a->x.b3 & 1 << 4) > 0)
        {
            a->x.b0 += 1;
            a->x.b3 -= 1 << 4;
        }

    }

    //Tem que trocar todas as permutações
    void SlashBits56(block value, block *a, block *b) {

        a->x.b0 = value.x.b0;
        a->x.b1 = value.x.b1;
        a->x.b2 = value.x.b2;
        a->x.b3 += (value.x.b3 & (int)pow(2,0));
        a->x.b3 += (value.x.b3 & (int)pow(2,1));
        a->x.b3 += (value.x.b3 & (int)pow(2,2));
        a->x.b3 += (value.x.b3 & (int)pow(2,3));


        b->x.b0 += (value.x.b3 & (int)pow(2,4));
        b->x.b0 += (value.x.b3 & (int)pow(2,5));
        b->x.b0 += (value.x.b3 & (int)pow(2,6));
        b->x.b0 += (value.x.b3 & (int)pow(2,7));
        b->x.b1 = value.x.b4;
        b->x.b2 = value.x.b5;
        b->x.b3 = value.x.b6;
        b->y = b->y >> 4;
    }

    void MergeBits56(block *value, block Ci, block Di )
    {
        value->y = 0;
        value->x.b0 = Ci.x.b0;
        value->x.b1 = Ci.x.b1;
        value->x.b2 = Ci.x.b2;
        value->x.b3 += (Ci.x.b3 & 1 << 0);
        value->x.b3 += (Ci.x.b3 & 1 << 1);
        value->x.b3 += (Ci.x.b3 & 1 << 2);
        value->x.b3 += (Ci.x.b3 & 1 << 3);

        Di.y = Di.y << 28;
        value->x.b3 += (Di.x.b3 & 1 << 4);
        value->x.b3 += (Di.x.b3 & 1 << 5);
        value->x.b3 += (Di.x.b3 & 1 << 6);
        value->x.b3 += (Di.x.b3 & 1 << 7);
        value->x.b4 = Di.x.b4;
        value->x.b5 = Di.x.b5;
        value->x.b6 = Di.x.b6;

        printf("\nMergedBits== ");
        PrintqBit(value->y);

    }
    block keys[16];
    unsigned long int InvertToPrint(block value)
    {
        block newBlock = value;
        newBlock.y = newBlock.y << 28;
        return newBlock.y;
    }

    void GenerateKeys(unsigned long int key, block*left, block*right)
    {
        unsigned long int pc1tValue = 36028797018963968 + 268435456  ; //PC1_Perm(value);

        printf("\npc1tValue == %lu    :   ", pc1tValue);
        PrintqBit(pc1tValue);
        block keyA = IntToBlock(pc1tValue);
        SlashBits56(keyA, right,left);
        printf("\nright == %lu", right->y);
        printf("\nleft == %lu", left->y);
        keyA.y = 0;

        printf("\n");

        printf("\nrightBits == ");
        PrintqBit(right->y);  //Right

        printf("\nleftBits  == ");
        PrintqBit(InvertToPrint(*left));
        printf("\n");

        printf("\nInicio da Geração de Chave");
        for(int i=0 ; i < 16; i++)
        {
            LeftShift(right, roundsShift[i]);
            LeftShift(left, roundsShift[i]);
            printf("\n");

            printf("\nrightBits == ");
            PrintqBit(right->y);  //Right


            printf("\nleftBits  == ");
            PrintqBit(InvertToPrint(*left));

            MergeBits56(&keyA, *right,*left);
            printf("\nMergeValue==  %lu", keyA.y);
            keyA.y = PC2_Perm(keyA.y);
            keys[i] = keyA;

        }
    }
    block E(block R)
    {
        block NewValue = {0};
        int EBit[] = {32,1,2,3,4,5,
            4,5,6,7,8,9,
            8,9,10,11,12,13,
            12,13,14,15,16,17,
            16,17,18,19,20,21,
            20,21,22,23,24,25,
            24,25,26,27,28,29,
            28,29,30,31,32,1
        };

        for(int i =0 ; i < 48;i++) EBit[i]--;

        unsigned long int x = 1;
        for(int i =0 ; i < 48;i++)
        {
            if((R.y & (x << EBit[i])) ==  (x << EBit[i]))
                NewValue.y +=  (x << i);
        }

        printf("\nInitial Value  == ");
        PrintqBit(R.y);
        printf("\nNew Value      == ");
        PrintqBit(NewValue.y);
        return NewValue;
    }
    void FestAlgoritm(unsigned int R, block Key )
    {
        block rExpansion = E(IntToBlock(R));
        block XorValue;
        XorValue.y = rExpansion.y ^ Key.y;

        block8b s1;
        block8b s2;
        block8b s3;
        block8b s4;
        block8b s5;
        block8b s6;
        block8b s7;
        block8b s8;

    //To com sono demais pra pensar
    }


    int main() {
        bitson();

         // block right = {0};
         // block left = {0};
         // long unsigned int iv = 4611686018427387903  ;
         // GenerateKeys(iv, &left, &right);
         // printf("\nivBits    == ");
         // PrintqBit(iv );
         //
         // for(int i =0 ; i < 16;i++)
         // {
         //     printf("\nChave %i == %lu",i + 1, keys[i].y);
         // }
        for(int i = 5; i < 32; i++) {
            printf("\n\n2 ^ {%i}", i);
            P(pow(2, i));
            E(IntToBlock(pow(2,i)));

        }

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