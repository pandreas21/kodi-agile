#pragma once
/*
*      Copyright (C) 2005-2013 Team XBMC
*      http://xbmc.org
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/

#include "DynamicDll.h"
#include "addons/kodi-addon-dev-kit/include/kodi/xbmc_addon_cpp_dll.h"
#include "addons/kodi-addon-dev-kit/include/kodi/versions.h"

class DllAddonInterface
{
public:
  virtual ~DllAddonInterface() {}
  virtual void GetAddon(void* pAddon) =0;
  virtual ADDON_STATUS Create(void *cb, void *info) =0;
  virtual void Destroy() =0;
  virtual ADDON_STATUS GetStatus() =0;
  virtual bool HasSettings() =0;
  virtual unsigned int GetSettings(ADDON_StructSetting*** sSet)=0;
  virtual void FreeSettings()=0;
  virtual ADDON_STATUS SetSetting(const char *settingName, const void *settingValue) =0;
  // Needed to pass return value as 'version' this way to prevent 'error C2059: Syntaxerror: "__declspec(dllexport)"' on Windows
  virtual void GetAddonTypeVersion(int type, const char** version)=0;
};

class DllAddon : public DllDynamic, public DllAddonInterface
{
public:
  DECLARE_DLL_WRAPPER_TEMPLATE(DllAddon)
  DEFINE_METHOD2(ADDON_STATUS, Create, (void* p1, void* p2))
  DEFINE_METHOD0(void, Destroy)
  DEFINE_METHOD0(ADDON_STATUS, GetStatus)
  DEFINE_METHOD0(bool, HasSettings)
  DEFINE_METHOD1(unsigned int, GetSettings, (ADDON_StructSetting ***p1))
  DEFINE_METHOD0(void, FreeSettings)
  DEFINE_METHOD2(ADDON_STATUS, SetSetting, (const char *p1, const void *p2))
  DEFINE_METHOD1(void, GetAddon, (void* p1))
  DEFINE_METHOD2(void, GetAddonTypeVersion, (int p1, const char** p2))
  BEGIN_METHOD_RESOLVE()
    RESOLVE_METHOD_RENAME(get_addon,GetAddon)
    RESOLVE_METHOD_RENAME(ADDON_Create, Create)
    RESOLVE_METHOD_RENAME(ADDON_Destroy, Destroy)
    RESOLVE_METHOD_RENAME(ADDON_GetStatus, GetStatus)
    RESOLVE_METHOD_RENAME(ADDON_HasSettings, HasSettings)
    RESOLVE_METHOD_RENAME(ADDON_SetSetting, SetSetting)
    RESOLVE_METHOD_RENAME(ADDON_GetSettings, GetSettings)
    RESOLVE_METHOD_RENAME(ADDON_FreeSettings, FreeSettings)
    RESOLVE_METHOD_RENAME(ADDON_GetTypeVersion, GetAddonTypeVersion)
  END_METHOD_RESOLVE()
};

