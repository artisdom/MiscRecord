bash -c "wget -c https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.9/5.9.4/single/qt-everywhere-opensource-src-5.9.4.tar.xz"

bash -c "tar -xvf qt-everywhere-opensource-src-5.9.4.tar.xz"

REM @call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

REM set PATH=%PATH%;E:\GitHub\vcpkg\downloads\tools\jom\jom-1.1.2;E:\GitHub\Google\depot_tools\win_tools-2_7_6_bin\python\bin;

cd qt-everywhere-opensource-src-5.9.4
REM configure -proprietary-codecs -opensource -confirm-license -nomake examples -nomake tests -release
REM option `-debug-and-release` (Apple and Windows only)
configure -proprietary-codecs -opensource -confirm-license -nomake examples -nomake tests -debug-and-release

jom /j8 module-qtwebengine

REM Fix for Windows
REM Fix 1: std::max/std::min --> using std::max;max(a,b);[For file `windows.h`]
REM Fix 2: use unix2dos to deal with `unicode problem` for MSVC