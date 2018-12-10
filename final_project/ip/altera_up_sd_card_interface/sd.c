#include <stdio.h>
#include <stdlib.h>

#include "sd.h"

//#define printf(...)

#include <system.h>

#define BYPASS_DCACHE   (0x1 << 31)

#define             SDCNT  (*(volatile unsigned int*)((SDCARD_BASE+0x0) | BYPASS_DCACHE))
#define             SDCMD0 (*(volatile unsigned int*)((SDCARD_BASE+0x4) | BYPASS_DCACHE))
#define             SDCMD1 (*(volatile unsigned int*)((SDCARD_BASE+0x8) | BYPASS_DCACHE))
#define             SDCMD2 (*(volatile unsigned int*)((SDCARD_BASE+0xC) | BYPASS_DCACHE))
#define             SDCMD3 (*(volatile unsigned int*)((SDCARD_BASE+0x10) | BYPASS_DCACHE))
#define             SDCMD4 (*(volatile unsigned int*)((SDCARD_BASE+0x14) | BYPASS_DCACHE))
#define             SDDATA (*(volatile unsigned int*)((SDCARD_BASE+0x18) | BYPASS_DCACHE))

#define SD_CMDFINISHED  (1<<1)
#define SD_RESPONSEFINISHED (1<<2)
#define SD_IDLEFINISHED (1<<3)
#define SD_RDFIFOEMPTY (1<<4)
#define SD_RDFIFOFULL (1<<5)


#define CMD0            0
#define CMD55           55
#define CMD2            2
#define CMD3            3
#define CMD7            7
#define CMD9            9
#define CMD10           10
#define CMD16           16
#define CMD17           17
#define ACMD6           6
#define ACMD41          41
#define ACMD51          51



unsigned char SD_CRC7(const unsigned char* in, unsigned int length)
{
    int i,j;

    unsigned char byte, crc=0;

    for(i=0; i < length; i++)
    {
        byte = in[i];

        for(j=0; j<8; j++)
        {
            crc <<= 1;
            if ((crc ^ byte) & 0x80)
                crc ^= 0x09;
            byte<<=1;
        }
        crc &= 0x7f;
    }

    return crc;
}




void SD_ClearFifo()
{
    while( (SDCNT & SD_RDFIFOEMPTY) == 0 ) { int tmp = SDDATA; }
}

unsigned int SD_ReadFifo()
{
    while( SDCNT & SD_RDFIFOEMPTY );
    
    return SDDATA;
}

void SD_WaitIdle()
{
    while( (SDCNT & SD_IDLEFINISHED) == 0 );
}

void SD_WaitCommand()
{
    while( (SDCNT & SD_CMDFINISHED) == 0 );
}

void SD_WaitResponse(unsigned int* response)
{
    while( (SDCNT & SD_RESPONSEFINISHED) == 0 );

//    printf("RES0 = 0x%08X\n", SDCMD0);
//    printf("RES1 = 0x%08X\n", SDCMD1);
//    printf("RES2 = 0x%08X\n", SDCMD2);
//    printf("RES3 = 0x%08X\n", SDCMD3);
//    printf("RES4 = 0x%08X\n", SDCMD4);    
    
    if (response)
    {
        response[0] = ((SDCMD0 & 0x00FFFFFF)<<8) | (SDCMD1 >> 24);
        response[1] = ((SDCMD1 & 0x00FFFFFF)<<8) | (SDCMD2 >> 24);
        response[2] = ((SDCMD2 & 0x00FFFFFF)<<8) | (SDCMD3 >> 24);
        response[3] = ((SDCMD3 & 0x00FFFFFF)<<8) | (SDCMD4 >> 24);
    }
}

void SD_SendCmd(unsigned int cmdid, unsigned int arg, unsigned int *response, unsigned char* data)
{
    unsigned char cmd[6];
    unsigned int word;
    unsigned int i;
    
    cmd[0] = cmdid | 0x40;
    cmd[1] = arg >> 24;
    cmd[2] = arg >> 16;
    cmd[3] = arg >> 8;
    cmd[4] = arg >> 0;
    cmd[5] = (SD_CRC7(cmd, 5)<<1) | 1;
    
    SD_ClearFifo();
    
    
    SDCMD0 = (cmd[2]<<24) | (cmd[3]<<16) | (cmd[4]<<8) | (cmd[5]<<0);
    SDCMD1 = (cmd[0]<<8) | (cmd[1]<<0);
    SDCNT = 1;

    SD_WaitCommand();
    
    
    if (response)
        SD_WaitResponse(response);

    if (data)
    {
        for(i=0; i<128; i++)
        {
            word = SD_ReadFifo();
            
            *data++ = word >> 24;
            *data++ = word >> 16;
            *data++ = word >> 8;
            *data++ = word >> 0;
         }        
    }

    SD_WaitIdle();
}


unsigned int SD_Init()
{
    int i;
    unsigned int status = 0;
    unsigned int ocr = 0;
    unsigned int rca = 0;
    unsigned int response[4];
    unsigned int cid[4];
    unsigned int csd[4];
    unsigned char cmd[5];
    unsigned int address = 0;
    unsigned int buffer[128];
    
    SD_SendCmd(CMD0, 0, 0, 0);
    printf("Sent CMD0\n");
    
    for(i=0; i<9000; i++)
    {
        SD_SendCmd(CMD55, 0, response, 0);       
        printf("Sent CMD55, status = 0x%08X\n", response[0]);
        
        SD_SendCmd(ACMD41, 0x0FF00000, response, 0);
        printf("Sent ACMD41, ocr = 0x%08X\n", response[0]);
        
        if (response[0] & 0x80000000)
            break;
    }

    SD_SendCmd(CMD2, 0, cid, 0);
    printf("Sent CMD2\n");

    SD_SendCmd(CMD3, 0, response, 0);
    rca = response[0];
    printf("Sent CMD3, rca = 0x%08X\n", rca);

    SD_SendCmd(CMD9, rca, csd, 0);
    printf("Sent CMD9, CSD = %08X %08X %08X %08X\n", csd[0], csd[1], csd[2], csd[3]);

    SD_SendCmd(CMD10, rca, cid, 0);
    printf("Sent CMD10, CID = %08X %08X %08X %08X\n", cid[0], cid[1], cid[2], cid[3]);
    
    SD_SendCmd(CMD7, rca, response, 0);
    printf("Sent CMD7, status = 0x%08X\n", response[0]);
    
    SD_SendCmd(CMD16, 0, response, 0);
    printf("Sent CMD16, status = 0x%08X\n", response[0]);

    printf("SD_Init success\n");

    return 1;
}

unsigned int SD_ReadBlock(unsigned int block, unsigned char* buf)
{
    unsigned int response[4];
    
    SD_SendCmd(CMD17, block*512, response, buf);

    return 1;
}

