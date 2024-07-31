            #include <stdio.h>
            #include <stdlib.h>
            #include <time.h>
            #include <stdint.h>
            #include <math.h>
            #define my_max (INT64_MAX)

            int roundsShift[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
            unsigned long int bits[64];

           int S1[4][16] = {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
        };

        int S2[4][16] = {
            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
            {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
            {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
            {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
        };

        int S3[4][16] = {
            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
            {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
        };

        int S4[4][16] = {
            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
            {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
            {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
            {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
        };

        int S5[4][16] = {
            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
            {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
            {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
        };

        int S6[4][16] = {
            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
            {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
            {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
        };

        int S7[4][16] = {
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
            {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
        };

        int S8[4][16] = {
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
            {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
        };

            typedef unsigned char byte;
            typedef unsigned int  hwrd;

            typedef struct {
                byte b0;
                byte b1;
                byte b2;
                byte b3;
            } bytex04;

            typedef union {
            bytex04 b4tes;
            hwrd    hhw;

            } hblck;
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
            unsigned long int IPinv(unsigned long int x)
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
            unsigned long int PC1(unsigned long int x)
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

            unsigned long int PC2(unsigned long int x)
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

            void KeySchedule(unsigned long int key, block*left, block*right)
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
                    keyA.y = PC2(keyA.y);
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
            int GetSixBits(unsigned long int value, int start, int end)
            {
                unsigned long int x = 1;
                unsigned long int y = 0;
                for(int i = start; i < end;i++) {
                    y += (value & (x << i)) >> start;
                }
                return y;
            }
            byte MergeBits8(byte byteA, byte byteB) {
                byte newByte = 0;
                newByte += (byteA & 1) + (byteA &2) + (byteA &4) + (byteA &8);
                newByte += ((byteB & 1) << 4) + ((byteB &2) << 4) + ((byteB &4) << 4) + ((byteB &8) << 4);
                printf("\n\nbyteA   ==  %2i :", byteA);
                PrintqBit(byteA);

                printf("\nbyteB   ==  %2i :", byteB);
                PrintqBit(byteB);
                printf("\nResult  ==  %2i :", newByte);
                PrintqBit(newByte);
                return newByte;

            }
            unsigned int Fiestel(unsigned int R, block Key) {
                block rExpansion = E(IntToBlock(R));
                block XorValue;
                XorValue.y = rExpansion.y ^ Key.y;
                PrintqBit(XorValue.y);

                byte s1 = (GetSixBits(XorValue.y, 0, 6));
                byte s2 = (GetSixBits(XorValue.y, 6, 12));
                byte s3 = (GetSixBits(XorValue.y, 12, 18));
                byte s4 = (GetSixBits(XorValue.y, 18, 24));
                byte s5 = (GetSixBits(XorValue.y, 24, 30));
                byte s6 = (GetSixBits(XorValue.y, 30, 36));
                byte s7 = (GetSixBits(XorValue.y, 36, 42));
                byte s8 = (GetSixBits(XorValue.y, 42, 48));

                byte b0 = 0;
                byte b1 = 0;
                byte b2 = 0;
                byte b3 = 0;
                byte b4 = 0;
                byte b5 = 0;
                byte b6 = 0;
                byte b7 = 0;
                for(int i = 0; i < 8; i++) {
                    printf("\n\nValor do XOR              ==  ");
                    PrintqBit(XorValue.y);

                    int iV, j, value;

                    switch (i) {
                        case 0:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s1);
                        iV = ((s1 & (1 << 5)) >> 4) + (s1 & 1);
                        j = ((s1 & 1 << 4) + (s1 & 1 << 3) + (s1 & 1 << 2) + (s1 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        // b0 = S1[iV][j];
                        b0 = 1;
                        printf("\nValor a partir da S1Table ==  %i", b0);
                        continue;
                        case 1:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s2);
                        iV = ((s2 & (1 << 5)) >> 4) + (s2 & 1);
                        j = ((s2 & 1 << 4) + (s2 & 1 << 3) + (s2 & 1 << 2) + (s2 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b1 = S2[iV][j];
                        printf("\nValor a partir da S2Table ==  %i", b1);
                        break;
                        case 2:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s3);
                        iV = ((s3 & (1 << 5)) >> 4) + (s3 & 1);
                        j = ((s3 & 1 << 4) + (s3 & 1 << 3) + (s3 & 1 << 2) + (s3 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b2 = S3[iV][j];
                        printf("\nValor a partir da S3Table ==  %i", b2);
                        break;
                        case 3:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s4);
                        iV = ((s4 & (1 << 5)) >> 4) + (s4 & 1);
                        j = ((s4 & 1 << 4) + (s4 & 1 << 3) + (s4 & 1 << 2) + (s4 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b3 = S4[iV][j];
                        printf("\nValor a partir da S4Table ==  %i", b3);
                        break;
                        case 4:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s5);
                        iV = ((s5 & (1 << 5)) >> 4) + (s5 & 1);
                        j = ((s5 & 1 << 4) + (s5 & 1 << 3) + (s5 & 1 << 2) + (s5 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b4 = S5[iV][j];
                        printf("\nValor a partir da S5Table ==  %i", b4);
                        break;
                        case 5:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s6);
                        iV = ((s6 & (1 << 5)) >> 4) + (s6 & 1);
                        j = ((s6 & 1 << 4) + (s6 & 1 << 3) + (s6 & 1 << 2) + (s6 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b5 = S6[iV][j];
                        printf("\nValor a partir da S6Table ==  %i", b5);
                        break;
                        case 6:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s7);
                        iV = ((s7 & (1 << 5)) >> 4) + (s7 & 1);
                        j = ((s7 & 1 << 4) + (s7 & 1 << 3) + (s7 & 1 << 2) + (s7 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b6 = S7[iV][j];
                        printf("\nValor a partir da S7Table ==  %i", b6);
                        break;
                        case 7:
                            printf("\nValor de Teste            ==  ");
                        PrintqBit(s8);
                        iV = ((s8 & (1 << 5)) >> 4) + (s8 & 1);
                        j = ((s8 & 1 << 4) + (s8 & 1 << 3) + (s8 & 1 << 2) + (s8 & 1 << 1)) >> 1;
                        printf("\nValor de I == %i", iV);
                        printf("\nValor de J == %i", j);
                        b7 = S8[iV][j];
                        printf("\nValor a partir da S8Table ==  %i", b7);
                        break;
                        default: ;
                    }
                }
                hblck value32 = {0};
                value32.b4tes.b0 = MergeBits8(b0,b1);
                value32.b4tes.b1 = MergeBits8(b2,b3);
                value32.b4tes.b2 = MergeBits8(b4,b5);
                value32.b4tes.b3 = MergeBits8(b6,b7);

                printf("\nConcatenar Resultado == ");
                PrintqBit(value32.hhw);

                return P(value32.hhw);
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
                // for(int i = 5; i < 32; i++) {
                //     printf("\n\n2 ^ {%i}", i);
                //     P(pow(2, i));
                //     E(IntToBlock(pow(2,i)));
                //
                // }
                block key = {0};
                key.y = 4215;
                Fiestel(1023,key);
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