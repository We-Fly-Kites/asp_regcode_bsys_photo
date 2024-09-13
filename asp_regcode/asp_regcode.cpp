// asp_regcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "asp_regcode.h"
#include "CodeGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

#define encrypt_template_DLPro "MXHCZ-BYEAR2-UQ9PQ6-TRHX5P-ZUJ81G-WNW0M4-70RBM"
#define encrypt_template_DSLRRemotePro4Windows "000HXK-THHEJE-BWQAMM-M82HF9-80Z7VX-6RKQN3-K7ZPJN"
#define encrypt_template_Flipbook "BREEZE00002M-062CXR-ZB6CAJ-YMFTW5-V4DR1C-5EM3PQ-1AEBPX-NZAJET"
#define encrypt_template_WebcamPhotobooth "Photobooth22C1B989-64E0-42a8-ADC3-C045E1F2BCA8Webcam"
#define encrypt_template_Hotfolder "PrintingD17515BC-5892-4333-B1D4-6AED5EF23B9CHotfolder"
#define encrypt_template_BreezeKiosk "{4A87DDD5-7A34-4dfd-9CDF-63363C5B3B29}{EE2C1826-4423-4755-9471-9862A4BDEEEF}"
#define encrypt_template_BBPro "000KBK-4QE0AG-HGHA9T-TCNJEG-C76Y9R-KRMNAP-20Z2AR"

CStringA genkeyDLPro(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_DLPro,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyBreezeBrowserPro(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_BBPro,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyDSLRRemotePro4Windows(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_DSLRRemotePro4Windows,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyBreezeKiosk(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_BreezeKiosk,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyWebcam(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_WebcamPhotobooth,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyFlipbook(CStringA name)
{
	return CreateCodeShort3A(
		9,	// level
		name,
		encrypt_template_Flipbook,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

CStringA genkeyHotfolder(CStringA name)
{
	return CreateCodeShort3A(
		6,	// level
		name,
		encrypt_template_Hotfolder,
		0,	// hardwareID
		0,	// otherinfo1
		0,	// otherinfo2
		0,	// otherinfo3
		0,	// otherinfo4
		0	// otherinfo5
		);
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			if (argc != 2)
			{
				printf("Please contact sales@breezesys.com, err=1\n");
				return 0;
			}

			CString arg1 = argv[1];

			// 20190106 - command line is in UTF-16 hex (starts with "R/" in UTF-16 hex)
			if (arg1.Find(L"0052002f") == 0)
			{
				CString queryUTF32;
				while (!arg1.IsEmpty())
				{
					CString charUTF32 = arg1.Left(4);
					arg1 = arg1.Mid(4);
					int ch = 0;
					swscanf_s(charUTF32, L"%04x", &ch);
					queryUTF32 += (wchar_t)ch;
				}
				arg1 = queryUTF32;
			}

			CStringA cmdline = CW2A(arg1);
			if (cmdline.GetLength() < 6 || cmdline.Left(2) != "R/" || !isdigit(cmdline[2]))
			{
				printf("Please contact sales@breezesys.com, err=2\n");
				return 0;
			}

			int product = cmdline[2] - '0';
			CStringA name = cmdline.Mid(4);
			CStringA code;

			switch (product)
			{
			case 1: code = genkeyDSLRRemotePro4Windows(name); break;
			case 2: code = genkeyBreezeBrowserPro(name); break;
			case 3: code = genkeyDLPro(name); break;
			case 4: code = genkeyFlipbook(name); break;
			case 5: code = genkeyHotfolder(name); break;
			case 7: code = genkeyWebcam(name); break;
			case 9: code = genkeyBreezeKiosk(name); break;
			}
			if (code.GetLength() < 6)
			{
				printf("Please contact sales@breezesys.com, err=3\n");
				return 0;
			}

			printf("%s\n", code);
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
