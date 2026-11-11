# NppSidebar (source package)

Native C++ Notepad++ plugin starter project. This package contains source only, not a tested DLL.

## Online build using GitHub Actions
1. Upload the contents of this folder into the root of a GitHub repository. Keep `.github/workflows/build.yml` in place.
2. Push to `main` or `master`, or run **Build NppSidebar** from the repository's **Actions** tab.
3. Download the `NppSidebar-x64` artifact for 64-bit Notepad++, or `NppSidebar-Win32` for 32-bit.
4. Extract the artifact DLL to `<Notepad++>\\plugins\\NppSidebar\\NppSidebar.dll`, fully exit Notepad++, then restart it.

The workflow compiles and links on a GitHub-hosted Windows runner. It does not run Notepad++ or verify that the plugin loads at runtime. A successful build is not proof of runtime compatibility.

## Local build requirements
Windows, Visual Studio 2022 Build Tools with Desktop development with C++ and a Windows SDK. Open `NppSidebar.sln`, choose `Release` and `x64` or `Win32`, and build.

## Included starter features
- Explorer selects a folder, lists files, and opens the selected file.
- Search scans files under the selected workspace for plain text.
- Extensions points users to Notepad++ Plugins Admin.

This is a prototype. Explorer displays a flattened file list; search is synchronous. The source has not been compiled or tested in this environment.

[NPPVim Notepad++](https://github.com/h-jangra/NppVim/tree/master)
