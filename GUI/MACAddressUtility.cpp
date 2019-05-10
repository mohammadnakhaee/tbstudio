#include "MACAddressUtility.h"

#include <stdio.h>

#if defined(WIN32) || defined(UNDER_CE)
#	include <windows.h>
#	if defined(UNDER_CE)
#		include <Iphlpapi.h>
#	endif
#elif defined(__APPLE__)
#	include <CoreFoundation/CoreFoundation.h>
#	include <IOKit/IOKitLib.h>
#	include <IOKit/network/IOEthernetInterface.h>
#	include <IOKit/network/IONetworkInterface.h>
#	include <IOKit/network/IOEthernetController.h>
#elif defined(LINUX) || defined(linux)
#	include <string.h>
#	include <net/if.h>
#	include <sys/ioctl.h>
#   include <sys/socket.h>
#   include <arpa/inet.h>
#endif

long MACAddressUtility::GetMACAddress(unsigned char * result)
{
	// Fill result with zeroes
	memset(result, 0, 6);
	// Call appropriate function for each platform
#if defined(WIN32) || defined(UNDER_CE)
	return GetMACAddressMSW(result);
#elif defined(__APPLE__)
	return GetMACAddressMAC(result);
#elif defined(LINUX) || defined(linux)
	return GetMACAddressLinux(result);
#endif
	// If platform is not supported then return error code
	return -1;
}

#if defined(WIN32) || defined(UNDER_CE)

inline long MACAddressUtility::GetMACAddressMSW(unsigned char * result)
{
	
#if defined(UNDER_CE)
	IP_ADAPTER_INFO AdapterInfo[16]; // Allocate information
	DWORD dwBufLen = sizeof(AdapterInfo); // Save memory size of buffer
	if(GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_SUCCESS) 
	{
		memcpy(result, AdapterInfo->Address, 6);
	}
	else return -1;
#else
	UUID uuid;
	if(UuidCreateSequential(&uuid) == RPC_S_UUID_NO_ADDRESS) return -1;
	memcpy(result, (char*)(uuid.Data4+2), 6);
#endif
	return 0;
}

#elif defined(__APPLE__)

static kern_return_t FindEthernetInterfaces(io_iterator_t *matchingServices)
{
    kern_return_t		kernResult;
    CFMutableDictionaryRef	matchingDict;
    CFMutableDictionaryRef	propertyMatchDict;

    matchingDict = IOServiceMatching(kIOEthernetInterfaceClass);

    if (NULL != matchingDict)
	{
        propertyMatchDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
													  &kCFTypeDictionaryKeyCallBacks,
													  &kCFTypeDictionaryValueCallBacks);

        if (NULL != propertyMatchDict)
		{
            CFDictionarySetValue(propertyMatchDict, CFSTR(kIOPrimaryInterface), kCFBooleanTrue);
            CFDictionarySetValue(matchingDict, CFSTR(kIOPropertyMatchKey), propertyMatchDict);
            CFRelease(propertyMatchDict);
        }
    }
    kernResult = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, matchingServices);
    return kernResult;
}

static kern_return_t GetMACAddress(io_iterator_t intfIterator, UInt8 *MACAddress, UInt8 bufferSize)
{
    io_object_t		intfService;
    io_object_t		controllerService;
    kern_return_t	kernResult = KERN_FAILURE;
	
	if (bufferSize < kIOEthernetAddressSize) {
		return kernResult;
	}
	
    bzero(MACAddress, bufferSize);
	
    while (intfService = IOIteratorNext(intfIterator))
    {
        CFTypeRef	MACAddressAsCFData;        
		
        // IONetworkControllers can't be found directly by the IOServiceGetMatchingServices call, 
        // since they are hardware nubs and do not participate in driver matching. In other words,
        // registerService() is never called on them. So we've found the IONetworkInterface and will 
        // get its parent controller by asking for it specifically.
        
        // IORegistryEntryGetParentEntry retains the returned object, so release it when we're done with it.
        kernResult = IORegistryEntryGetParentEntry(intfService,
												   kIOServicePlane,
												   &controllerService);
		
        if (KERN_SUCCESS != kernResult) {
            printf("IORegistryEntryGetParentEntry returned 0x%08x\n", kernResult);
        }
        else {
            // Retrieve the MAC address property from the I/O Registry in the form of a CFData
            MACAddressAsCFData = IORegistryEntryCreateCFProperty(controllerService,
																 CFSTR(kIOMACAddress),
																 kCFAllocatorDefault,
																 0);
            if (MACAddressAsCFData) {
                CFShow(MACAddressAsCFData); // for display purposes only; output goes to stderr
                
                // Get the raw bytes of the MAC address from the CFData
                CFDataGetBytes((CFDataRef)MACAddressAsCFData, CFRangeMake(0, kIOEthernetAddressSize), MACAddress);
                CFRelease(MACAddressAsCFData);
            }
			
            // Done with the parent Ethernet controller object so we release it.
            (void) IOObjectRelease(controllerService);
        }
        
        // Done with the Ethernet interface object so we release it.
        (void) IOObjectRelease(intfService);
    }
	
    return kernResult;
}

long MACAddressUtility::GetMACAddressMAC(unsigned char * result)
{
	io_iterator_t	intfIterator;
	kern_return_t	kernResult = KERN_FAILURE;
	do
	{
		kernResult = ::FindEthernetInterfaces(&intfIterator);
		if (KERN_SUCCESS != kernResult) break;
	    kernResult = ::GetMACAddress(intfIterator, (UInt8*)result, 6);
    }
	while(false);
    (void) IOObjectRelease(intfIterator);
}

#elif defined(LINUX) || defined(linux)
//nothing

#endif
