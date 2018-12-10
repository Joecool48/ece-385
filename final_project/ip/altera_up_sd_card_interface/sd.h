#ifndef _SD_H_
#define _SD_H_

#ifdef __cplusplus
extern "C" {
#endif



unsigned int SD_Init();
unsigned int SD_ReadBlock(unsigned int block, unsigned char* buf);


#ifdef __cplusplus
}
#endif


#endif // _SD_H_

