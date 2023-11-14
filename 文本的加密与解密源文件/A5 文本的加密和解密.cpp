#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include <cmath>
#include<cstring>
#include<fstream>
#pragma warning(disable:4996)
#define ERROR -1
static const unsigned char Rcon[10] ={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
//s�о��� Substitution Table
static const unsigned char sbox[256] = {
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,
    0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,
    0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,
    0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,
    0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,
    0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,
    0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,
    0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,
    0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,
    0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,
    0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,
    0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,
    0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,
    0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,
    0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,
    0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,
    0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16,
};
//����S�о���
static const unsigned char contrary_sbox[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,
    0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,
    0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,
    0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,
    0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,
    0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,
    0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,
    0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,
    0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,
    0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,
    0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,
    0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,
    0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,
    0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,
    0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,
    0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,
    0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d,
};

using namespace std;
class WheelEncryption
{
private:
    int flag1 = 0, flag2 = 0;                                            //ת��ת����־λ
    int slowL[26] = { 24,25,26,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
    int slowR[26] = { 21,3,15,1,19,10,14,26,20,8,16,7,22,4,11,5,17,9,12,23,18,2,25,6,24,13 };                                     //������
    int midL[26] = { 26,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
    int midR[26] = { 20,1,6,4,15,3,14,12,23,5,16,2,22,19,11,18,25,24,13,7,10,8,21,9,26,17 };                                      //������
    int fastL[26] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 ,20,21,22,23,24,25,26 };
    int fastR[26] = { 8,18,26,17,20,22,10,3,13,11,4,23,5,24,9,12,25,16,19,6,15,21,2,7,1,14 };                                        //������
    char input[27] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };//����ת������ת��Ϊ���ֵĲ��ձ�
    char output[27] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };//������������±�ת�����ַ��Ĳ��ձ�
public:
    void roatewheel(int wheel[26]) 
    {                                                                  //ʵ������ת����ÿ������ת��һ��
        int temp = wheel[25];
        for (int i = 24; i >= 0; i--) {
            wheel[i + 1] = wheel[i];
        }
        wheel[0] = temp % 26; // ��������ֵ�ںϷ���Χ��
        return;
    }

    int searchindex(int wheel[26], int figure) 
    {                                                                    //�����������͵����ӵ��±�,�������±�
        for (int i = 0; i < 26; i++) 
        {
            if (wheel[i] == figure)
                return i;
        }
        cout << "��ѯʧ�ܣ�" << endl;
        return ERROR;
    }

    int searchindex(char wheel[27], char figure) 
    {                       //�����ַ����͵����ӵ��±꣬�������±�                 
        for (int i = 0; i < 26; i++) 
        {
            if (wheel[i] == figure)
                return i;
        }
        cout << "��ѯʧ�ܣ�" << endl;
        return ERROR;
    }
    void OutputCipertext(string plaintext)
    {                                                                     //�������
        int len = plaintext.length();
        int ind1, ind2, ind3, ind4;                                       //�����ĸ��±���
        for (int i = 0; i < len; i++) 
        {
            ind1 = searchindex(input, plaintext[i]);                      //�����ַ�ת��Ϊ��Ӧ���֣������������±�
            ind2 = searchindex(slowR, slowL[ind1]);                       //����������  
            ind3 = searchindex(midR, midL[ind2]);                         //���������
            ind4 = searchindex(fastR, fastL[ind3]);                       //���������ַ���Ӧ���±�                                 //����ַ���Ӧ������
            flag1++;
            cout << input[ind4];
            roatewheel(fastL);                                            //ÿ���һλ��������ת��һ��
            roatewheel(fastR);
            if (flag1 % 26 == 0 && flag1 != 0) 
            {                          //������ÿת��26�Σ�������ת��һ��
                roatewheel(midL);
                roatewheel(midR);
                flag2++;
            }
            if (flag2 % 26 == 0 && flag2 != 0) 
            {                          //������ÿת��26�Σ�������ת��һ��
                roatewheel(slowL);
                roatewheel(slowR);
            }
        }
        flag1 = flag2 = 0;//���ܽ�������־λ��ʼ��Ϊ0
        plaintext = input[ind4];
    }

    void OutputPlaintext(string cipertext) 
    {                                           //��������
        int len = cipertext.length();
        int ind1, ind2, ind3, ind4;
        for (int i = 0; i < len; i++) 
        {
            ind1 = searchindex(output, cipertext[i]);
            ind2 = searchindex(fastL, fastR[ind1]);
            ind3 = searchindex(midL, midR[ind2]);
            ind4 = searchindex(slowL, slowR[ind3]);
            flag1++;
            roatewheel(fastL);
            roatewheel(fastR);
            if (flag1 % 26 == 0 && flag1 != 0) {
                roatewheel(midL);
                roatewheel(midR);
                flag2++;
            }
            if (flag2 % 26 == 0 && flag2 != 0) {
                roatewheel(slowL);
                roatewheel(slowR);
            }
            cout << input[ind4];

        }
       
        flag1 = flag2 = 0;
    }
void show()
        {
        int choice;
        string plaintext;
        string cipertext;
            cout << "    1 -> ��������  " << endl;
            cout << "    2 -> ��������  " << endl;
            cout << "    0 -> �˳�      " << endl;              
            cout <<endl<< "��ѡ����һ������: " << endl;
            cin >> choice;
            switch (choice) {
            case 2:
                cout << "��������Ҫ���ܵ�����" << endl;
                cin >> cipertext;
                cout << "���ܺ������:";
                OutputPlaintext(cipertext);
                break;
            case 1:
                cout << "��������Ҫ���ܵ����ģ�" << endl;
                cin >> plaintext;
                cout << "���ܺ������:";
                OutputCipertext(plaintext);
                break;
            case 0:
                return;
            default:
                cout << "�������������0��1��2��" << endl;
            }
        }

};
class AES
{
public:

    //����������*2�˷�
    static unsigned char x2time(unsigned char x)
    {
        if (x & 0x80)
        {
            return (((x << 1) ^ 0x1B) & 0xFF);
        }
        return x << 1;
    }
    //����������*3�˷�
    static unsigned char x3time(unsigned char x)
    {
        return (x2time(x) ^ x);
    }
    //����������*4�˷�
    static unsigned char x4time(unsigned char x)
    {
        return (x2time(x2time(x)));
    }
    //����������*8�˷�
    static unsigned char x8time(unsigned char x)
    {
        return (x2time(x2time(x2time(x))));
    }
    //����������*9�˷�
    static unsigned char x9time(unsigned char x)
    {
        return (x8time(x) ^ x);
    }
    //����������*B�˷�
    static unsigned char xBtime(unsigned char x)
    {
        return (x8time(x) ^ x2time(x) ^ x);
    }
    //����������*D�˷�
    static unsigned char xDtime(unsigned char x)
    {
        return (x8time(x) ^ x4time(x) ^ x);
    }
    //����������*E�˷�
    static unsigned char xEtime(unsigned char x)
    {
        return (x8time(x) ^ x4time(x) ^ x2time(x));
    }
    //�����л�ϲ���
    static void MixColumns(unsigned char* col)
    {
        unsigned char tmp[4];
        int i;
        for (i = 0; i < 4; i++, col += 4)
        {  //col����һ�еĻ���ַ��col+4:��һ�еĻ���ַ
            //xt[n]����*2   xt[n]^col[n]����*3   col[n]����*1
            tmp[0] = x2time(col[0]) ^ x3time(col[1]) ^ col[2] ^ col[3];	//2 3 1 1
            tmp[1] = col[0] ^ x2time(col[1]) ^ x3time(col[2]) ^ col[3];	//1 2 3 1
            tmp[2] = col[0] ^ col[1] ^ x2time(col[2]) ^ x3time(col[3]);	//1 1 2 3
            tmp[3] = x3time(col[0]) ^ col[1] ^ col[2] ^ x2time(col[3]);	//3 1 1 2
            //�޸ĺ��ֵ ֱ����ԭ�������޸�
            col[0] = tmp[0];
            col[1] = tmp[1];
            col[2] = tmp[2];
            col[3] = tmp[3];
        }
    }
    //���������л���
    static void Contrary_MixColumns(unsigned char* col)
    {
        unsigned char tmp[4];
        int x;
        for (x = 0; x < 4; x++, col += 4)
        {
            tmp[0] = xEtime(col[0]) ^ xBtime(col[1]) ^ xDtime(col[2]) ^ x9time(col[3]);
            tmp[1] = x9time(col[0]) ^ xEtime(col[1]) ^ xBtime(col[2]) ^ xDtime(col[3]);
            tmp[2] = xDtime(col[0]) ^ x9time(col[1]) ^ xEtime(col[2]) ^ xBtime(col[3]);
            tmp[3] = xBtime(col[0]) ^ xDtime(col[1]) ^ x9time(col[2]) ^ xEtime(col[3]);
            col[0] = tmp[0];
            col[1] = tmp[1];
            col[2] = tmp[2];
            col[3] = tmp[3];
        }
    }
    //��������λ����������ѭ����λ
    static void ShiftRows(unsigned char* col)
    {//��������λ
        unsigned char t;
        //����1λ
        t = col[1]; col[1] = col[5]; col[5] = col[9]; col[9] = col[13]; col[13] = t;
        //����2λ������2��������ʵ��
        t = col[2]; col[2] = col[10]; col[10] = t;
        t = col[6]; col[6] = col[14]; col[14] = t;
        //����3λ���൱������1��
        t = col[15]; col[15] = col[11]; col[11] = col[7]; col[7] = col[3]; col[3] = t;
        //��4�в���λ
    }
    //��������λ
    static void Contrary_ShiftRows(unsigned char* col)
    {
        unsigned char t;
        t = col[13]; col[13] = col[9]; col[9] = col[5]; col[5] = col[1]; col[1] = t;
        t = col[2]; col[2] = col[10]; col[10] = t;
        t = col[6]; col[6] = col[14]; col[14] = t;
        t = col[3]; col[3] = col[7]; col[7] = col[11]; col[11] = col[15]; col[15] = t;
        //ͬ����4�в���λ
    }
    //����s���ֽڴ����滻����
    static void SubBytes(unsigned char* col)
    {//�ֽڴ���
        int x;
        for (x = 0; x < 16; x++)
        {
            col[x] = sbox[col[x]];
        }
    }
    //�����ֽڴ���
    static void Contrary_SubBytes(unsigned char* col)
    {
        int x;
        for (x = 0; x < 16; x++)
        {
            col[x] = contrary_sbox[col[x]];
        }
    }
    //��Կ���ţ�16�ֽ�--->44��32bit��Կ����--> 11��16�ֽ�:�ֱ�����11�� ����Կ������
    void ScheduleKey(unsigned char* inkey, unsigned char* outkey, int Nk, int Nr)
    {
        //inkey:��ʼ16�ֽ���Կkey
        //outkey��11��*16�ֽ���չ��Կexpansionkey
        //Nk��4��
        //Nr��10��round
        unsigned char temp[4], t;
        int x, i;
        /*copy the key*/
        //��0�飺[0-3]ֱ�ӿ���
        for (i = 0; i < (4 * Nk); i++)
        {
            outkey[i] = inkey[i];
        }
        //��1-10�飺[4-43]
        i = Nk;
        while (i < (4 * (Nr + 1))) //i=4~43 WORD 32bit�����ֽڵ�ַ��ÿһ��4�ֽ�
        {//1��ѭ������1���ֽ���չ��Կ��4��ѭ������һ��WORD
            //temp��4�ֽ����飺����һ��WORD��Կ
            //i����4�ı�����ʱ��
            //ÿ��temp = ÿ��outkey32bit = 4�ֽ�
            for (x = 0; x < 4; x++)
                temp[x] = outkey[(4 * (i - 1)) + x];	//i��32bit�����ֽڵ�ַ
            //i��4�ı�����ʱ��
            if (i % Nk == 0)
            {
                /*��ѭ����ѭ������1�ֽ� RotWord()*/
                t = temp[0]; temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
                /*�ֽڴ�����SubWord()*/
                for (x = 0; x < 4; x++)
                {
                    temp[x] = sbox[temp[x]];
                }
                /*�ֳ������Rcon[j]*/
                temp[0] ^= Rcon[(i / Nk) - 1];
            }
            for (x = 0; x < 4; x++)
            {
                outkey[(4 * i) + x] = outkey[(4 * (i - Nk)) + x] ^ temp[x];
            }
            ++i;
        }
    }
    //��������Կ�Ӳ���
    static void AddRoundKey(unsigned char* col, unsigned char* expansionkey, int round)//��Կ��
    {
        //��չ��Կ��44*32bit =11*4* 4*8 =  16�ֽ�*11�֣�ÿ����16�ֽ���Կ
        //��0�֣�ֻ����һ������Կ��
        //��1-10�֣�����Կ��
        int x;
        for (x = 0; x < 16; x++)
        {	//ÿ1�ֲ�����4*32bit��Կ = 16���ֽ���Կ
            col[x] ^= expansionkey[(round << 4) + x];
        }
    }
    //AES���ܺ���
    void AesEncrypt(unsigned char* blk, unsigned char* expansionkey, int Nr)
    {
        int round;
        //��1��֮ǰ������Կ��
        AddRoundKey(blk, expansionkey, 0);
        //��1-9�֣�4��������ֽڴ���������λ���л�ϡ�����Կ��
        for (round = 1; round <= (Nr - 1); round++)
        {
            SubBytes(blk);		//����16�ֽ����飬ֱ����ԭ�������޸�
            ShiftRows(blk);		//����16�ֽ����飬ֱ����ԭ�������޸�
            MixColumns(blk);	//����16�ֽ����飬ֱ����ԭ�������޸�
            AddRoundKey(blk, expansionkey, round);
        }
        //��10�֣��������л��
        SubBytes(blk);
        ShiftRows(blk);
        AddRoundKey(blk, expansionkey, Nr);
    }
    //AES ���ܺ���
    void Contrary_AesEncrypt(unsigned char* blk, unsigned char* expansionkey, int Nr)
    {
        int x;
        AddRoundKey(blk, expansionkey, Nr);
        Contrary_ShiftRows(blk);
        Contrary_SubBytes(blk);
        for (x = (Nr - 1); x >= 1; x--)
        {
            AddRoundKey(blk, expansionkey, x);
            Contrary_MixColumns(blk);
            Contrary_ShiftRows(blk);
            Contrary_SubBytes(blk);
        }
        AddRoundKey(blk, expansionkey, 0);
    }
    void show(){
        unsigned char pt[17], key[17];
        //��������pt
        //������Կkey
        unsigned char expansionkey[15 * 16];
        int i;
        int choice_aes;
        cout << "    1 -> �ӽ�������  " << endl;
        cout << "    0 -> �˳�      " << endl;
        cout << endl << "��ѡ����һ������: " << endl;
        cin >> choice_aes;
        switch (choice_aes)
        {
        case 1:
        {
            cout << "������16λ����:" << endl;
            cin >> pt;
            cout << "��������Կ:" << endl;
            cin >> key;
            //���ܹ���
            ScheduleKey(key, expansionkey, 4, 10);//��Կ��չ����
            AesEncrypt(pt, expansionkey, 10);//����AES ����
            cout << "���ܺ������Ϊ: " << endl;
            //�������
            for (i = 0; i < 16; i++)
            {
                printf("%02x ", pt[i]);
            }
            cout << endl;
            //���ܹ���
            Contrary_AesEncrypt(pt, expansionkey, 10);//����AES ����
            printf("���ܺ������Ϊ:");
            //�������
            for (i = 0; i < 16; i++)
            {
                printf("%c ", pt[i]);
            }
            printf("\n");
            printf("\n");
            break;
        }
        case 0:
            return;
        default:
            cout << "�������������0��1��2��" << endl;
        }
    }


};
class RSA 
{
private:
    // ѡ��������ͬ������p��q
    int p = 17;
    int q = 19;
    // ����n
    int n = p * q;
    // ����phi(n)
    int phi = (p - 1) * (q - 1);
    // ѡ��һ����phi(n)���ʵ���e
    int e = 7;
public:
    // �����Լ��
    int gcd(int a, int b) 
{
        if (b == 0) {
            return a;
        }
        else {
            return gcd(b, a % b);
        }
    }
    // �ж��Ƿ�Ϊ����
    bool isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        int sqrtNum = sqrt(num);
        for (int i = 2; i <= sqrtNum; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
    // ��ŷ�������չ�㷨�е�˽Կd
    int calculateD(int e, int phi) {
        int d = 1;
        while ((d * e) % phi != 1) {
            d++;
        }
        return d;
    }

    // ���ܺ���
    int encrypt(int plainText, int e, int n) {
        int cipherText = 1;
        for (int i = 0; i < e; i++) {
            cipherText = (cipherText * plainText) % n;
        }
        return cipherText;
    }

    // ���ܺ���
    int decrypt(int cipherText, int d, int n) {
        int plainText = 1;
        for (int i = 0; i < d; i++) {
            plainText = (plainText * cipherText) % n;
        }
        return plainText;
    }

   void show() 
   {
       int plainText_rsa;
       int cipherText_rsa;
        // ��֤e�Ƿ���phi(n)����
        if (gcd(e, phi) != 1) {
            std::cout << "Error: e is not coprime with phi(n)." << std::endl;
            return ;
        }
        // ����d
        int d = calculateD(e, phi);
        // ��ʾ��Կ��˽Կ
        cout << "��ԿΪ: {" << e << ", " << n << "}" << endl;
        cout << "˽ԿΪ: {" << d << ", " << n << "}" << endl;
        int choice_rsa;
        cout << "    1 -> ��������  " << endl;
        cout << "    2 -> ��������  " << endl;
        cout << "    0 -> �˳�      " << endl;
        cout << endl << "��ѡ����һ������: " << endl;
        cin >> choice_rsa;
        switch (choice_rsa) 
        {
        case 2:
        {
            cout << "��������Ҫ���ܵ�����" << endl;
            // ��������
            cin >> cipherText_rsa;
            // ����
            int decryptedText_rsa = decrypt(cipherText_rsa, d, n);
            cout << "���ܺ����ϢΪ: " << decryptedText_rsa << endl;
            break;
        }
        case 1:
        {
            cout << "��������Ҫ���ܵ����ģ�" << endl;
            // ����
            cin >> plainText_rsa;
            int cipherText_rsa = encrypt(plainText_rsa, e, n);
            cout << "���ܺ����ϢΪ: " << cipherText_rsa << endl;
            break;
        }
        case 0:
            return;
        default:
            cout << "�������������0��1��2��" << endl;
        }
    }
};


int main()
{
    WheelEncryption a;
    RSA rsa;
    AES aes;
    while (1)
    {
        cout << endl;
        cout << "�X----------------------------�[" << endl;
        cout << "           �ı��ӽ���ϵͳ   " << endl;
        cout << endl;
        cout << "  ��ѡ����ļӽ��ܷ�ʽ:" << endl;
        cout << " " << endl;
        cout << "  1 -> ת�ֻ��ӽ���" << endl;
        cout << "  2 -> AES�ӽ���" << endl;
        cout << "  3 -> RSA�ӽ���" << endl;
        cout << "  0 > �˳�" << endl;
        cout << "�^----------------------------�a" << endl;
        int OPTION;
        cin >> OPTION;
        if (OPTION == 0) break;
        switch (OPTION)
        {
        case 1:
            a.show();
            break;
        case 2:
            aes.show();
            break;
        case 3:
            rsa.show();
            break;
        default:
            break;
        }
    }
}