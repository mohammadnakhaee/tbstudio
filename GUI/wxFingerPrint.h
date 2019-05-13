#ifndef _WX_FingerPrint_H
#define _WX_FingerPrint_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <intrin.h>
#include <iphlpapi.h>
#include <cstdint>

typedef uint16_t u16;
typedef uint32_t u32;

class wxFingerPrint
{
public:
    
    wxFingerPrint();
    ~wxFingerPrint();
	static void getMacHash( u16& mac1, u16& mac2 );
    static u16 getVolumeHash();
	static u16 getCpuHash();
	static const char* getMachineName();
    static void smear(std::string BaseSN, std::string MacAddr, std::string &SN1, std::string &SN2);
    static void unsmear(std::string SN1, std::string SN2, std::string &BaseSN, std::string &MacAddr);
private:
    static u16 hashMacAddress( PIP_ADAPTER_INFO info );
};

#endif
