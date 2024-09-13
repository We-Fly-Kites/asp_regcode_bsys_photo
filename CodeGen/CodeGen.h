/*
 * Copyright 1999-2012 Digital River, Inc. All rights reserved.
 */

#include "ole2.h"
#include "oleauto.h"

#undef CODEGEN_API
#if defined CODEGEN_EXPORTS
	#define CODEGEN_API
#elif defined(CODEGEN_LIB)
	#define CODEGEN_API
#else
	#define CODEGEN_API __declspec(dllimport)
#endif

#if defined __cplusplus
extern "C" {
#endif

/*
	Name:
		CreateCode
		VBCreateCode

	Purpose:
		Generates unsigned (or V1) keys for programs protected by the Armadillo
		Software Protection System.

	Parameters:
		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo
			This is used to specify the number of days/uses for the expiration-
			in-key info, or the number of copies for copies-in-key certificates,
			or the 'extra info' number. If none of these are used, it should be
			zero. See the MakeDate() function for expires-by-date keys.

	Returns: A string containing the 16-digit hexidecimal code, separated into
		four groups of four digits each.
*/

CODEGEN_API const char *CreateCodeA(const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo);
CODEGEN_API const wchar_t *CreateCodeW(const wchar_t *name, const wchar_t *encrypt_template, unsigned long hardwareID, unsigned short otherinfo);
CODEGEN_API BSTR __stdcall VBCreateCode(const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned long otherinfo);

#ifdef UNICODE
	#define CreateCode CreateCodeW
#else
	#define CreateCode CreateCodeA
#endif

/*
	Most implementations can ignore the MakeDate function. It creates an
	Armadillo-formatted date, for use in the "otherinfo" expiration parameter
	of the CreateCode functions for expire-by-date keys. The year should be the
	four-digit year, the month should be 1 to 12, and the day should be 1 to
	31. It returns 0xFFFF on error (bad date or date before 1999.01.01).

	The MakeDate2 function should return the same thing, but calculated
	differently. It is here only for debugging purposes.
*/

CODEGEN_API unsigned short __stdcall MakeDate(unsigned int year, unsigned int month, unsigned int day);
CODEGEN_API unsigned short __stdcall MakeDate2(unsigned int year, unsigned int month, unsigned int day);

/*
	The following function will translate an eight-digit hexadecimal code,
	possibly with formatting, to an unsigned long. Some implementations may
	need this capability to generate hardware locked keys.
*/

CODEGEN_API unsigned long __stdcall HexToIntA(const char *name);
CODEGEN_API unsigned long __stdcall HexToIntW(const wchar_t *name);

#ifdef UNICODE
	#define HexToInt HexToIntW
#else
	#define HexToInt HexToIntA
#endif

/*
	Name:
		CreateCode2
		VBCreateCode2

	Purpose:
		Generates v2 (CreateCode2, VBCreateCode2), v3 (CreateCode3,
		VBCreateCode3), or ShortV3 (CreateCodeShort3, VBCreateCodeShort3)
		signed keys, of any signature level, for programs protected by the
		Armadillo Software Protection System.

	Parameters:
		int level
			The signature level (1 through 4 for CreateCode2, 1 through 9 for
			CreateCode3, or 1 through 10 for CreateCodeShort3) specified for
			this certificate in your Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

			For the ShortV3 format, and when used with Armadillo 3.70 or later,
			this string can be empty to make a "nameless" key -- the earlier
			formats do not permit nameless keys.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5
			These are used to specify the number of days/uses for the
			expiration-in-key info, the number of copies for copies-in-key
			certificates, and/or the 'extra info' number.

			The order of the parameters is:
				Expiration info (if expiration-in-key; see MakeDate() function
					for expires-by-date keys);
				Copies (if copies-in-key);
				Extra info 1 (if desired; the low 16 bits of the extra info);
				Extra info 2 (if desired; the high 16 bits of the extra info).

			The otherinfo5 parameter is not used at present, and is reserved
			for future expansion; it should always be set to zero. Any unused
			parameters must also be set to zero.

		const char *keystring
			For the "WithString" functions, this parameter is the string that
			CodeGen should insert into the key. It must be a maximum of 64
			characters in length, not counting the terminating NULL (required
			in the C version), and can contain any ASCII character except ASCII
			zero. If no string is needed, you can still use the WithString
			functions, and either pass an empty string or a NULL pointer in
			this parameter.

	Returns: A string containing the hexidecimal key-code, separated into
		groups of four digits (for the v2 or v3 formats) or six digits (for the
		ShortV3 format).
*/

CODEGEN_API const char *CreateCode2A(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API const wchar_t *CreateCode2W(int level, const wchar_t *name, const wchar_t *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API BSTR __stdcall VBCreateCode2(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);

#ifdef UNICODE
	#define CreateCode2 CreateCode2W
#else
	#define CreateCode2 CreateCode2A
#endif

/*
	Name:
		CheckUninstallKey

	Purpose:
		Checks an uninstall key for validity. Also does basic checking on
		original key (everything but verifying the signature).

	Parameters:
		int level
			The signature level (zero for unsigned keys, 1 through 4 for v2
			keys, 11 through 19 for v3 keys [level+10], or 21 through 30 for
			ShortV3 keys [level+20]) specified for this certificate in your
			Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation. For "nameless" ShortV3 keys,
			you must separate out the first six digits of the key (not counting
			leading zeros) and pass them to the function in this parameter --
			that's what it uses for the "name" portion.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		const char *origkey
			The user's original key, as a string. The formatting can be
			included or ignored, it doesn't matter.

		const char *uninstkey
			The uninstall key that the user provides, and that you wish to
			check. The formatting can be included or ignored, it doesn't
			matter.

	Returns:
		Non-zero (true) if the key is good and the uninstall key matches it.
		Otherwise zero (false).
*/

CODEGEN_API bool __stdcall CheckUninstallKeyA(int level, const char *name, const char *enc_template, unsigned long hardwareID, const char *origkey, const char *uninstkey);
CODEGEN_API bool __stdcall CheckUninstallKeyW(int level, const wchar_t *name, const wchar_t *enc_template, unsigned long hardwareID, const wchar_t *origkey, const wchar_t *uninstkey);

#ifdef UNICODE
	#define CheckUninstallKey CheckUninstallKeyW
#else
	#define CheckUninstallKey CheckUninstallKeyA
#endif

/*
	Name:
		DateKeyCreated
		VBDateKeyCreated

	Purpose:
		Extracts the date that a key was created from the key. Also does basic
		checking on original key (everything but verifying the signature).

	Parameters:
		int level
			The signature level (zero for unsigned keys, 1 through 4 for v2
			keys, 11 through 19 for v3 keys [level+10], or 21 through 30 for
			ShortV3 keys [level+20]) specified for this certificate in your
			Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation. For "nameless" ShortV3 keys,
			you must separate out the first six digits of the key (not counting
			leading zeros) and pass them to the function in this parameter --
			that's what it uses for the "name" portion.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		const char *origkey
			The user's original key, as a string. The formatting can be
			included or ignored, it doesn't matter.

	Returns:
		A C string (DateKeyCreated) or a BSTR (VBDateKeyCreated) indicating the
		date that the key was created, in the form YYYY.MM.DD, where YYYY is
		the four-digit year, MM is the two-digit month (1..12), and DD is the
		two-digit day. On any error or problem, it returns an empty,
		zero-length string.
*/

CODEGEN_API const char *DateKeyCreatedA(int level, const char *name, const char *enc_template, unsigned long hardwareID, const char *origkey);
CODEGEN_API const wchar_t *DateKeyCreatedW(int level, const wchar_t *name, const wchar_t *enc_template, unsigned long hardwareID, const wchar_t *origkey);
CODEGEN_API BSTR __stdcall VBDateKeyCreated(int level, const char *name, const char *enc_template, unsigned long hardwareID, const char *origkey);

#ifdef UNICODE
	#define DateKeyCreated DateKeyCreatedW
#else
	#define DateKeyCreated DateKeyCreatedA
#endif

/*
	Name:
		CreateFixClockKey
		VBCreateFixClockKey

	Purpose:
		Creates a FixClock key for a program.

	Parameters:
		const char *project_name
			The name of the project, as specified in the project file. Note,
			this is NOT the filename of the file itself -- it is a user-selected
			setting within the project!

	Returns:
		A C string (CreateFixClockKey) or BSTR (VBCreateFixClockKey) containing
		a FixClock key for that program, which is valid only for three days
		after it is created.
*/

CODEGEN_API const char *CreateFixClockKeyA(const char *project_name);
CODEGEN_API const wchar_t *CreateFixClockKeyW(const wchar_t *project_name);
CODEGEN_API BSTR __stdcall VBCreateFixClockKey(const char *project_name);

#ifdef UNICODE
	#define CreateFixClockKey CreateFixClockKeyW
#else
	#define CreateFixClockKey CreateFixClockKeyA
#endif

/*
	Name:
		CreateCode3
		VBCreateCode3
		CreateCodeShort3
		VBCreateCodeShort3

	Purpose:
		Generates v2 (CreateCode2, VBCreateCode2), v3 (CreateCode3,
		VBCreateCode3), or ShortV3 (CreateCodeShort3, VBCreateCodeShort3)
		signed keys, of any signature level, for programs protected by the
		Armadillo Software Protection System.

	Parameters:
		int level
			The signature level (1 through 4 for CreateCode2, 1 through 9 for
			CreateCode3, or 1 through 10 for CreateCodeShort3) specified for
			this certificate in your Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

			For the ShortV3 format, and when used with Armadillo 3.70 or later,
			this string can be empty to make a "nameless" key -- the earlier
			formats do not permit nameless keys.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5
			These are used to specify the number of days/uses for the
			expiration-in-key info, the number of copies for copies-in-key
			certificates, and/or the 'extra info' number.

			The order of the parameters is:
				Expiration info (if expiration-in-key; see MakeDate() function
					for expires-by-date keys);
				Copies (if copies-in-key);
				Extra info 1 (if desired; the low 16 bits of the extra info);
				Extra info 2 (if desired; the high 16 bits of the extra info).

			The otherinfo5 parameter is not used at present, and is reserved
			for future expansion; it should always be set to zero. Any unused
			parameters must also be set to zero.

		const char *keystring
			For the "WithString" functions, this parameter is the string that
			CodeGen should insert into the key. It must be a maximum of 64
			characters in length, not counting the terminating NULL (required
			in the C version), and can contain any ASCII character except ASCII
			zero. If no string is needed, you can still use the WithString
			functions, and either pass an empty string or a NULL pointer in
			this parameter.

	Returns: A string containing the hexidecimal key-code, separated into
		groups of four digits (for the v2 or v3 formats) or six digits (for the
		ShortV3 format).
*/

CODEGEN_API const char *CreateCode3A(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API const wchar_t *CreateCode3W(int level, const wchar_t *name, const wchar_t *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API BSTR __stdcall VBCreateCode3(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API const char *CreateCodeShort3A(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API const wchar_t *CreateCodeShort3W(int level, const wchar_t *name, const wchar_t *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API BSTR __stdcall VBCreateCodeShort3(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);

#ifdef UNICODE
	#define CreateCode3 CreateCode3W
	#define CreateCodeShort3 CreateCodeShort3W
#else
	#define CreateCode3 CreateCode3A
	#define CreateCodeShort3 CreateCodeShort3A
#endif

/*
	Name:
		WriteHardwareChangeLog
		VBWriteHardwareChangeLog
		ConvertHardwareChangeLog

	Purpose:
		Translates an Armadillo Hardware Change Log (*.AHCL) file to text
		format.

	Parameters:
		const char *writefilename
			The path and filename of the file to write.

		const char *ahclfilename
			The path and filename of the *.AHCL file.

	Returns:
		A C++-style Boolean value, true if the hardware change log file is
		acceptable and the output file was written properly, false if there
		was a problem with the file, or an error while reading or writing.
*/

CODEGEN_API bool WriteHardwareChangeLogA(const char *writefilename, const char *ahclfilename);
CODEGEN_API bool WriteHardwareChangeLogW(const wchar_t *writefilename, const wchar_t *ahclfilename);
CODEGEN_API bool __stdcall VBWriteHardwareChangeLog(const char *writefilename, const char *ahclfilename);

#ifdef UNICODE
	#define WriteHardwareChangeLog WriteHardwareChangeLogW
#else
	#define WriteHardwareChangeLog WriteHardwareChangeLogA
#endif

/*
	Name:
		CreateCodeShort3WithString
		VBCreateCodeShort3WithString

	Purpose:
		Generates v2 (CreateCode2, VBCreateCode2), v3 (CreateCode3,
		VBCreateCode3), or ShortV3 (CreateCodeShort3, VBCreateCodeShort3)
		signed keys, of any signature level, for programs protected by the
		Armadillo Software Protection System.

	Parameters:
		int level
			The signature level (1 through 4 for CreateCode2, 1 through 9 for
			CreateCode3, or 1 through 10 for CreateCodeShort3) specified for
			this certificate in your Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

			For the ShortV3 format, and when used with Armadillo 3.70 or later,
			this string can be empty to make a "nameless" key -- the earlier
			formats do not permit nameless keys.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5
			These are used to specify the number of days/uses for the
			expiration-in-key info, the number of copies for copies-in-key
			certificates, and/or the 'extra info' number.

			The order of the parameters is:
				Expiration info (if expiration-in-key; see MakeDate() function
					for expires-by-date keys);
				Copies (if copies-in-key);
				Extra info 1 (if desired; the low 16 bits of the extra info);
				Extra info 2 (if desired; the high 16 bits of the extra info).

			The otherinfo5 parameter is not used at present, and is reserved
			for future expansion; it should always be set to zero. Any unused
			parameters must also be set to zero.

		const char *keystring
			For the "WithString" functions, this parameter is the string that
			CodeGen should insert into the key. It must be a maximum of 64
			characters in length, not counting the terminating NULL (required
			in the C version), and can contain any ASCII character except ASCII
			zero. If no string is needed, you can still use the WithString
			functions, and either pass an empty string or a NULL pointer in
			this parameter.

	Returns: A string containing the hexidecimal key-code, separated into
		groups of four digits (for the v2 or v3 formats) or six digits (for the
		ShortV3 format).
*/

CODEGEN_API const char *CreateCodeShort3WithStringA(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5, const char *keystring);
CODEGEN_API const wchar_t *CreateCodeShort3WithStringW(int level, const wchar_t *name, const wchar_t *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5, const wchar_t *keystring);
CODEGEN_API BSTR __stdcall VBCreateCodeShort3WithString(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5, const char *keystring);

#ifdef UNICODE
	#define CreateCodeShort3WithString CreateCodeShort3WithStringW
#else
	#define CreateCodeShort3WithString CreateCodeShort3WithStringA
#endif

#if defined __cplusplus
};
#endif
