/*  Pcsx - Pc Psx Emulator
 *  Copyright (C) 1999-2003  Pcsx Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "..\xbox\xbox.h"
#include "..\libpcsxcore\psxcommon.h"
#include "..\libpcsxcore\plugins.h"

#include "input\sysxboxinput.h"
#include "gui\xboxguiexport.h"

int iRunning = 0;
int iPSXIamgeLoaded = 0;
char PcsxrDir[MAXPATHLEN];

int SysInit()
{
	if (EmuInit() == -1)
		return -1;

#ifdef EMU_LOG
	emuLog = fopen("D:\\emuLog.txt","w");
	setvbuf(emuLog, NULL,  _IONBF, 0);
#endif

	LoadMcds(Config.Mcd1, Config.Mcd2);

	if (Config.Debug) StartDebugger();

	return 0;
}

void SysReset()
{
	EmuReset();
}

void SysClose()
{
	LD_LAUNCH_DASHBOARD LaunchData =
	{ XLD_LAUNCH_DASHBOARD_MAIN_MENU };

	if (iRunning)
		ClosePlugins(TRUE);

	EmuShutdown();
	ReleasePlugins();

	if(IsXBoxGUIActive())
		CloseXBoxGUI();

	XLaunchNewImage(NULL, (LAUNCH_DATA*)&LaunchData);
}

void SysPrintf(const char *fmt, ...)
{
	va_list list;
	char tmp[512];

	va_start(list,fmt);
	vsprintf(tmp,fmt,list);
	va_end(list);

	OutputDebugString(tmp);
}

void SysMessage(const char *fmt, ...)
{
	va_list list;
	char tmp[512];

	va_start(list,fmt);
	vsprintf(tmp,fmt,list);
	va_end(list);

	OutputDebugString(tmp);
}

void SysUpdate()
{
#if 0
	MEMORYSTATUS stat;
#endif

	if(CheckQuit())
		SysClose();

#if 0
	// Check Memory
	GlobalMemoryStatus( &stat );
	SysMessage("%4d mb free\n", stat.dwAvailPhys / (1024*1024));
#endif
}

int RunCommand(int iCommand, const char* strIsoFile)
{
	switch(iCommand)
	{
		case ID_FILE_RUNBIOS: //FIXME		
			CloseXBoxGUI();

			if (strcmp(Config.Bios, "HLE") == 0)
			{
				SysMessage(_("Running BIOS is not supported with Internal HLE Bios."));
				return TRUE;
			}
			
			SetIsoFile(NULL);
			LoadPlugins();

			if (OpenPlugins(/*hWnd*/) == -1)
			{
				ClosePlugins(FALSE);
				return TRUE;
			}

			SysReset();
			CdromId[0] = '\0';
			CdromLabel[0] = '\0';
			iRunning = 1;
			return TRUE;	

		case ID_EMULATOR_RUN:
			if(iPSXIamgeLoaded)
			{
				CloseXBoxGUI();
				OpenPlugins(/*hWnd*/);
				iRunning = 1;
//				CheatSearchBackupMemory(); //TODO
				psxCpu->Execute();
				return TRUE;
			}
			return FALSE;

		case ID_FILE_RUN_ISO:
			CloseXBoxGUI();
			iPSXIamgeLoaded = TRUE;
			SetIsoFile(strIsoFile);

			LoadPlugins();
			if (OpenPlugins() == -1)
			{
				ClosePlugins(FALSE);
				return TRUE;
			}
			if (CheckCdrom() == -1)
			{
				ClosePlugins(FALSE);
				SysMessage(_("The CD does not appear to be a valid Playstation CD"));
				return TRUE;
			}

			// Auto-detect: region first, then rcnt reset
			SysReset();
					
#if 0 // Enable to stop bios screen showing
			if (LoadCdrom() == -1)
			{
				ClosePlugins();
				SysMessage(_("Could not load CD-ROM!"));
				return TRUE;
			}
#endif
			iRunning = 1;
			psxCpu->Execute();
			return TRUE;

		default:
			return FALSE;
	}

	return FALSE;
}

void SysRunGUI()
{
	if(iRunning)
	{
		ClosePlugins(FALSE);
		iRunning = 0;
	}

	InitializeXBoxGUI();

	while(1)
	{
		RunXBoxGUI();
		SysUpdate();
	}
}

int main()
{
	iRunning = 0;
	iPSXIamgeLoaded = 0;

#ifndef _XBOX
	GetCurrentDirectory(256, PcsxrDir);
#else
	strcpy( PcsxrDir, "D:\\") ;
#endif
	strcpy(cfgfile, "config.cfg");

	memset(&Config, 0, sizeof(PcsxConfig));
	strcpy(Config.Net, "Disabled");

	if(LoadCoreConfig(&Config) == -1)
	{
		// Uh oh, no config file found, use some defaults
		Config.PsxAuto = 1; 

#ifndef _HARDLINKED
		strcpy(Config.PluginsDir, "Plugins\\");
#endif
		strcpy(Config.BiosDir,    "Bios\\");
		strcpy(Config.Bios,    "scph1001.bin");

#ifdef ENABLE_SIO1API
		set_default_plugin(Sio1ConfS.plist[0], Config.Sio1);
#endif
		strcpy(Config.Mcd1, "memcards\\Mcd001.mcr");
		strcpy(Config.Mcd2, "memcards\\Mcd002.mcr");

		SaveCoreConfig();
	}

	if (SysInit() == -1) return 1;

	// We need to do this here for the GUI
	wglCreateContext(NULL);
	wglMakeCurrent(NULL, NULL);

	SysRunGUI();
}