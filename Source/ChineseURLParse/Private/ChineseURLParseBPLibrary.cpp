// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChineseURLParseBPLibrary.h"
#include "ChineseURLParse.h"

#include <string>

#include <iostream>


using namespace std;
UChineseURLParseBPLibrary::UChineseURLParseBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

static const char safe[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

FString UChineseURLParseBPLibrary::EncodeCNCharacterURL(const FString& encodeString)
{
	std::string cstr(TCHAR_TO_UTF8(*encodeString));
	string ret;	
	const unsigned char *ptr = (const unsigned char *)cstr.c_str();
	ret.reserve(cstr.length());
 
	for (; *ptr ; ++ptr)
	{
		if (!safe[*ptr]) 
		{
			char buf[5];
			memset(buf, 0, 5);
#ifdef WIN32
			_snprintf_s(buf, 5, "%%%X", (*ptr));
#else
			snprintf(buf, 5, "%%%X", (*ptr));
#endif
			ret.append(buf); 	
		}
		else if (*ptr==' ')
		{
			ret+='+';
		}
		else{
			ret += *ptr;
		}
	}
	FString result = FString(UTF8_TO_TCHAR(ret.c_str()));

	return result;
}

FString UChineseURLParseBPLibrary::DecodeCNCharacterURL(const FString& decodeString)
{


	std::string cstr(TCHAR_TO_UTF8(*decodeString));


	const unsigned char* ptr = (const unsigned char*)cstr.c_str();

	string ret;

	ret.reserve(cstr.length());

	for (; *ptr; ++ptr)

	{

		if (*ptr == '%')

		{

			if (*(ptr + 1))

			{

				char a = *(ptr + 1);

				char b = *(ptr + 2);

				if (!((a >= 0x30 && a < 0x40) || (a >= 0x41 && a < 0x47))) continue;

				if (!((b >= 0x30 && b < 0x40) || (b >= 0x41 && b < 0x47))) continue;

				char buf[3];

				buf[0] = a;

				buf[1] = b;

				buf[2] = 0;

				ret += (char)strtoul(buf, NULL, 16);

				ptr += 2;

				continue;

			}

		}

		if (*ptr == '+')

		{

			ret += ' ';

			continue;

		}

		ret += *ptr;

	}


	//std::string to FString

	FString result = FString(UTF8_TO_TCHAR(ret.c_str()));

	return result;


}
