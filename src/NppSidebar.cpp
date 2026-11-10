#include "NppApi.h"
#include <commctrl.h>
#include <shlobj.h>
#include <initializer_list>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

static NppData g_npp{};
static HWND g_panel{};
static HWND g_tabs{}, g_list{}, g_input{};
static std::wstring g_root;
static constexpr int CMD_SHOW=0, CMD_COUNT=1;
static FuncItem g_funcs[CMD_COUNT]{};
static const wchar_t* kTitle=L"NppSidebar";
static const wchar_t* kModule=L"NppSidebar.dll";
static LRESULT CALLBACK PanelProc(HWND,UINT,WPARAM,LPARAM);

static void refreshFiles() {
    if (!g_list || g_root.empty()) return;
    SendMessageW(g_list, LB_RESETCONTENT, 0, 0);
    try { for (auto const& e : std::filesystem::recursive_directory_iterator(g_root))
        if (e.is_regular_file()) { auto p=e.path().wstring(); SendMessageW(g_list,LB_ADDSTRING,0,(LPARAM)p.c_str()); }
    } catch (...) {}
}
static void showPanel() { if(!g_panel) { HMODULE mod=GetModuleHandleW(kModule); g_panel=CreateWindowExW(0,L"NppSidebarPanel",kTitle,WS_CHILD|WS_CLIPCHILDREN,0,0,300,550,g_npp._nppHandle,nullptr,mod,nullptr); if(g_panel){ NppTbData d{}; d.hClient=g_panel; d.pszName=kTitle; d.dlgID=0; d.uMask=0; d.pszModuleName=kModule; SendMessageW(g_npp._nppHandle,NPPM_DMMREGASDCKDLG,0,(LPARAM)&d); } } if(g_panel) SendMessage(g_npp._nppHandle,NPPM_DMMSHOW,0,(LPARAM)g_panel); }
static void openWorkspace() {
    BROWSEINFOW bi{}; bi.lpszTitle=L"Choose workspace folder"; bi.ulFlags=BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
    PIDLIST_ABSOLUTE id=SHBrowseForFolderW(&bi); if(!id)return;
    wchar_t path[MAX_PATH]{}; if(SHGetPathFromIDListW(id,path)) { g_root=path; refreshFiles(); } CoTaskMemFree(id);
}
static void openSelected() { int i=(int)SendMessageW(g_list,LB_GETCURSEL,0,0); if(i==LB_ERR)return; wchar_t p[32768]{}; SendMessageW(g_list,LB_GETTEXT,i,(LPARAM)p); SendMessageW(g_npp._nppHandle,NPPM_DOOPEN,0,(LPARAM)p); }
static void searchFiles() {
    wchar_t q[512]{}; GetWindowTextW(g_input,q,512); if(!*q||g_root.empty())return;
    SendMessageW(g_list,LB_RESETCONTENT,0,0);
    try { for(auto const&e:std::filesystem::recursive_directory_iterator(g_root)) if(e.is_regular_file()&&e.file_size()<4*1024*1024) {
        std::wifstream f(e.path()); std::wstring line; size_t n=0; while(std::getline(f,line)&&++n<100000) if(line.find(q)!=std::wstring::npos) {
            std::wstring r=e.path().wstring(); SendMessageW(g_list,LB_ADDSTRING,0,(LPARAM)r.c_str()); break;
        }
    }} catch(...){}
}
static LRESULT CALLBACK PanelProc(HWND h,UINT m,WPARAM w,LPARAM l) {
    if(m==WM_CREATE) {
        g_tabs=CreateWindowW(WC_TABCONTROLW,L"",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,6,6,280,28,h,(HMENU)10,GetModuleHandleW(nullptr),nullptr);
        for(auto s:{L"Explorer",L"Search",L"Extensions"}) { TCITEMW t{};t.mask=TCIF_TEXT;t.pszText=(LPWSTR)s;TabCtrl_InsertItem(g_tabs,TabCtrl_GetItemCount(g_tabs),&t); }
        CreateWindowW(L"BUTTON",L"Open Folder",WS_CHILD|WS_VISIBLE,6,40,100,26,h,(HMENU)11,0,0);
        CreateWindowW(L"BUTTON",L"Search",WS_CHILD|WS_VISIBLE,112,40,70,26,h,(HMENU)12,0,0);
        g_input=CreateWindowW(L"EDIT",L"",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,6,72,275,24,h,(HMENU)13,0,0);
        g_list=CreateWindowW(L"LISTBOX",L"",WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_NOTIFY|WS_VSCROLL,6,102,275,430,h,(HMENU)14,0,0); return 0;
    }
    if(m==WM_COMMAND) { if(LOWORD(w)==11)openWorkspace(); if(LOWORD(w)==12)searchFiles(); if(LOWORD(w)==14&&HIWORD(w)==LBN_DBLCLK)openSelected(); return 0; }
    if(m==WM_NOTIFY && ((LPNMHDR)l)->hwndFrom==g_tabs && ((LPNMHDR)l)->code==TCN_SELCHANGE) {
        int tab=TabCtrl_GetCurSel(g_tabs); if(tab==2) { HMENU menu=(HMENU)SendMessageW(g_npp._nppHandle,NPPM_GETMENUHANDLE,NPPPLUGINMENU,0); if(menu) { // Extensions uses the native Plugins menu; user may open Plugins Admin there.
                MessageBoxW(h,L"Use Plugins > Plugins Admin to manage extensions.",L"NppSidebar",MB_OK|MB_ICONINFORMATION); } }
    }
    return DefWindowProcW(h,m,w,l);
}
static void showCommand(){showPanel();}
extern "C" __declspec(dllexport) const TCHAR* getName(){return kTitle;}
extern "C" __declspec(dllexport) void setInfo(NppData data){g_npp=data;}
extern "C" __declspec(dllexport) FuncItem* getFuncsArray(int* n){ lstrcpyW(g_funcs[0]._itemName,L"Show Sidebar");g_funcs[0]._pFunc=showCommand;g_funcs[0]._cmdID=0;*n=CMD_COUNT;return g_funcs; }
extern "C" __declspec(dllexport) void beNotified(void*){}
extern "C" __declspec(dllexport) LRESULT messageProc(UINT,WPARAM,LPARAM){return TRUE;}
extern "C" __declspec(dllexport) BOOL isUnicode(){return TRUE;}
BOOL APIENTRY DllMain(HMODULE mod,DWORD reason,LPVOID) { if(reason==DLL_PROCESS_ATTACH){ InitCommonControls(); WNDCLASSW wc{}; wc.lpfnWndProc=PanelProc; wc.hInstance=mod; wc.lpszClassName=L"NppSidebarPanel"; wc.hCursor=LoadCursor(nullptr,IDC_ARROW); RegisterClassW(&wc); } return TRUE; }
