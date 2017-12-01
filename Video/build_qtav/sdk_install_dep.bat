set Install=install
mkdir %Install%\lib\
mkdir %Install%\bin\
mkdir %Install%\include\QtAV\
mkdir %Install%\mkspecs\features
mkdir %Install%\include\QtAVWidgets\
mkdir %Install%\include\QtAV\5.9.3\QtAV\
mkdir %Install%\mkspecs\modules
mkdir %Install%\qml\QtAV\

copy /y lib_win_x86\*Qt*AV*.lib* %Install%\lib\
copy /y lib_win_x86\QtAV1.lib %Install%\lib\Qt5AV.lib
copy /y lib_win_x86\QtAVd1.lib %Install%\lib\Qt5AVd.lib
copy /y tools\install_sdk\mkspecs\features\av.prf %Install%\mkspecs\features\av.prf
copy /y tools\install_sdk\mkspecs\modules\qt_lib_av*.pri %Install%\mkspecs\modules\
copy /y bin\*.dll %Install%\bin\
copy /y bin\*.exe %Install%\bin\
copy /y lib\*.lib %Install%\lib\
xcopy /s /q /y /i include %Install%\include

copy /y lib_win_x86\*Qt*AV*.lib* %Install%\lib\
copy /y lib_win_x86\QtAVWidgets1.lib %Install%\lib\Qt5AVWidgets.lib
copy /y lib_win_x86\QtAVWidgetsd1.lib %Install%\lib\Qt5AVWidgetsd.lib
copy /y tools\install_sdk\mkspecs\features\avwidgets.prf %Install%\mkspecs\features\avwidgets.prf
copy /y tools\install_sdk\mkspecs\modules\qt_lib_avwidgets*.pri %Install%\mkspecs\modules\
copy /y bin\Qt*AV*.dll %Install%\bin\
copy /y ..\src\QtAV\*.h %Install%\include\QtAV\
copy /y ..\src\QtAV\QtAV %Install%\include\QtAV\
copy /y ..\widgets\QtAVWidgets\*.h %Install%\include\QtAVWidgets\
copy /y ..\widgets\QtAVWidgets\QtAVWidgets %Install%\include\QtAVWidgets\

xcopy /s /q /y /i ..\src\QtAV\private %Install%\include\QtAV\private
xcopy /s /q /y /i ..\src\QtAV\private %Install%\include\QtAV\5.9.3\QtAV\private
xcopy /s /q /y /i bin\QtAV %Install%\qml\QtAV
copy /y ..\qml\plugins.qmltypes %Install%\qml\QtAV\
