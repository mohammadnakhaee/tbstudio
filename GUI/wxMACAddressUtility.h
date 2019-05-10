#ifndef _WX_MACADDRESS_UTILITY_H
#define _WX_MACADDRESS_UTILITY_H

#include "MACAddressUtility.h"
#include <wx/wx.h>

class wxMACAddressUtility
{
public:
	static wxString GetMACAddress()
	{
		unsigned char result[7];
		if(MACAddressUtility::GetMACAddress(result) == 1)
		{
			return wxString::Format(wxT("%02X:%02X:%02X:%02X:%02X:%02X"),
				(unsigned int)result[0], (unsigned int)result[1], (unsigned int)result[2],
				(unsigned int)result[3], (unsigned int)result[4], (unsigned int)result[5]);
		}
		return wxEmptyString;
	}
};

#endif
