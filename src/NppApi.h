#pragma once
#include <windows.h>
#include <tchar.h>
struct NppData { HWND _nppHandle; HWND _scintillaMainHandle; HWND _scintillaSecondHandle; };
struct ShortcutKey { bool _isCtrl; bool _isAlt; bool _isShift; UCHAR _key; };
using PFUNCPLUGINCMD = void (*)();
struct FuncItem { TCHAR _itemName[64]; PFUNCPLUGINCMD _pFunc; int _cmdID; bool _init2Check; ShortcutKey* _pShKey; };
struct NppTbData { HWND hClient; const TCHAR* pszName; int dlgID; UINT uMask; HICON hIconTab; const TCHAR* pszAddInfo; RECT rcFloat; int iPrevCont; const TCHAR* pszModuleName; };
constexpr UINT NPPMSG = WM_USER + 1000;
constexpr UINT NPPM_GETMENUHANDLE = NPPMSG + 25;
constexpr UINT NPPM_DMMREGASDCKDLG = NPPMSG + 33;
constexpr UINT NPPM_DMMSHOW = NPPMSG + 30;
constexpr UINT NPPM_DMMHIDE = NPPMSG + 31;
constexpr UINT NPPM_DOOPEN = NPPMSG + 77;
constexpr int NPPN_READY = 1001;
constexpr int NPPPLUGINMENU = 0;
