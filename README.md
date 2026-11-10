# NppSidebar (source package)

Native C++ Notepad++ plugin starter project with an Explorer, Search and Extensions sidebar. This repository produces separate 32-bit and 64-bit build artifacts using GitHub Actions. The source ZIP itself does not include a compiled DLL.

## Requirements for a local build
- Windows 10/11
- Visual Studio 2022 with Desktop development with C++
- Windows SDK (10.0.19041 or newer)
- Notepad++ 8.x, 32-bit or 64-bit matching the selected build platform

## Build locally
Open `NppSidebar.sln`, select `Release` and the platform matching your Notepad++ (`x64` or `Win32`), then build the solution. Output: `bin\\<platform>\\Release\\NppSidebar.dll`.

## Build online with GitHub Actions
1. Create a GitHub repository. For private source, set the repository to **Private**.
2. Upload the contents of this folder to the repository root. Make sure `.github/workflows/build.yml` is included.
3. Push to the `main` or `master` branch, or open the repository's **Actions** tab and run **Build NppSidebar** with **Run workflow**.
4. Open the completed run. Under **Artifacts**, download `NppSidebar-x64` or `NppSidebar-Win32`. Each artifact contains the DLL for that architecture.
5. Install the matching DLL by creating `<Notepad++>\\plugins\\NppSidebar\\` and placing `NppSidebar.dll` inside, then restart Notepad++.

GitHub Actions compiles the code; it does not run Notepad++ to test the plugin. A successful build only confirms that the source compiled and linked on the runner, not that the plugin was runtime-tested.

## Features and limits
- Explorer: choose a workspace folder, browse files, double-click a file to open it.
- Search: scan files under the workspace and open a matching file.
- Extensions: directs the user to Notepad++'s native Plugins Admin.
- This is a starter implementation. Explorer displays a flattened file list. Search is synchronous plain-text scanning and skips files that are unreadable or larger than 4 MB.
