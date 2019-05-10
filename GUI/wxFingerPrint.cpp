#include "wxFingerPrint.h"

wxFingerPrint::wxFingerPrint()
{

}

wxFingerPrint::~wxFingerPrint()
{

}

// we just need this for purposes of unique machine id. 
// So any one or two mac's is fine.
u16 wxFingerPrint::hashMacAddress(PIP_ADAPTER_INFO info)
{
   u16 hash = 0;
   for ( u32 i = 0; i < info->AddressLength; i++ )
   {
      hash += ( info->Address[i] << (( i & 1 ) * 8 ));
   }
   return hash;
}

void wxFingerPrint::getMacHash( u16& mac1, u16& mac2 )
{
   IP_ADAPTER_INFO AdapterInfo[32];
   DWORD dwBufLen = sizeof( AdapterInfo );
 
   DWORD dwStatus = GetAdaptersInfo( AdapterInfo, &dwBufLen );
   if ( dwStatus != ERROR_SUCCESS )
      return; // no adapters.
 
   PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
   mac1 = hashMacAddress( pAdapterInfo );
   if ( pAdapterInfo->Next )
      mac2 = hashMacAddress( pAdapterInfo->Next );
 
   // sort the mac addresses. We don't want to invalidate
   // both macs if they just change order.
   if ( mac1 > mac2 )
   {
      u16 tmp = mac2;
      mac2 = mac1;
      mac1 = tmp;
   }
}

u16 wxFingerPrint::getVolumeHash()
{
   DWORD serialNum = 0;
   //Determine if this volume uses an NTFS file system.
   GetVolumeInformation("c:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0 );
   u16 hash = (u16)(( serialNum + ( serialNum >> 16 )) & 0xFFFF );
   return hash;
}
 
u16 wxFingerPrint::getCpuHash()
{
   int cpuinfo[4] = { 0, 0, 0, 0 };
   __cpuid( cpuinfo, 0 );
   u16 hash = 0;
   u16* ptr = (u16*)(&cpuinfo[0]);
   for ( u32 i = 0; i < 8; i++ )
      hash += ptr[i];
   return hash;
}

const char* wxFingerPrint::getMachineName()
{
   static char computerName[1024];
   DWORD size = 1024;
   GetComputerName( computerName, &size );
   return &(computerName[0]);
}

void wxFingerPrint::smear(std::string BaseSN, std::string MacAddr, std::string &SN1, std::string &SN2)
{
    int n1 = BaseSN.length();
	int n2 = MacAddr.length();
	char* str1 = new char[n1];
	char* str2 = new char[n2];
	strcpy(str1, BaseSN.c_str());
	strcpy(str2, MacAddr.c_str());
    
    u32 nMask1 = 18;
    u32 nMask2 = 7;
    char* Mask1 = new char[nMask1];
    char* Mask2 = new char[nMask2];
    
    Mask1[0] = 23;
    Mask1[1] = 3;
    Mask1[2] = 26;
    Mask1[3] = 230;
    Mask1[4] = 223;
    Mask1[5] = 221;
    Mask1[6] = 23;
    Mask1[7] = 3;
    Mask1[8] = 26;
    Mask1[9] = 130;
    Mask1[10] = 221;
    Mask1[11] = 222;
    Mask1[12] = 203;
    Mask1[13] = 30;
    Mask1[14] = 126;
    Mask1[15] = 210;
    Mask1[16] = 123;
    Mask1[17] = 189;
    
    Mask2[0] = 230;
    Mask2[1] = 13;
    Mask2[2] = 126;
    Mask2[3] = 250;
    Mask2[4] = 123;
    Mask2[5] = 222;
    Mask2[6] = 200;
    
    for (u32 i = 0; i < n1; i++) str1[i] ^= Mask1[i%nMask1];
    for (u32 i = 0; i < n2; i++) str2[i] ^= Mask2[i%nMask2];
    for (u32 i = 0; i < n1; i++) str1[i] ^= str2[i%n2];
    SN1 = std::string(str1);
    SN2 = std::string(str2);
}

void wxFingerPrint::unsmear(std::string SN1, std::string SN2, std::string &BaseSN, std::string &MacAddr)
{
    
    int n1 = SN1.length();
	int n2 = SN2.length();
	char* str1 = new char[n1];
	char* str2 = new char[n2];
	strcpy(str1, SN1.c_str());
	strcpy(str2, SN2.c_str());
    
    u32 nMask1 = 18;
    u32 nMask2 = 7;
    char* Mask1 = new char[nMask1];
    char* Mask2 = new char[nMask2];
    
    Mask1[0] = 23;
    Mask1[1] = 3;
    Mask1[2] = 26;
    Mask1[3] = 230;
    Mask1[4] = 223;
    Mask1[5] = 221;
    Mask1[6] = 23;
    Mask1[7] = 3;
    Mask1[8] = 26;
    Mask1[9] = 130;
    Mask1[10] = 221;
    Mask1[11] = 222;
    Mask1[12] = 203;
    Mask1[13] = 30;
    Mask1[14] = 126;
    Mask1[15] = 210;
    Mask1[16] = 123;
    Mask1[17] = 189;
    
    Mask2[0] = 230;
    Mask2[1] = 13;
    Mask2[2] = 126;
    Mask2[3] = 250;
    Mask2[4] = 123;
    Mask2[5] = 222;
    Mask2[6] = 200;
    
    for (u32 i = 0; i < n1; i++) str1[i] ^= str2[i%n2];
    for (u32 i = 0; i < n2; i++) str2[i] ^= Mask2[i%nMask2];
    for (u32 i = 0; i < n1; i++) str1[i] ^= Mask1[i%nMask1];
    BaseSN = std::string(str1);
    MacAddr = std::string(str2);
}




