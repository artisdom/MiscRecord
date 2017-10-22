import win32api as api
import win32con as con
for disk in "CDEF":
	F=api.GetDiskFreeSpace(disk+":")
	rest=F[0]*F[1]*F[2]/1e9
	total=F[0]*F[1]*F[3]/1e9
	print "Rest:",rest,"G","Total:",total,"G"
print api.GetComputerName()
print api.GetConsoleTitle()
print api.GetCommandLine()
print api.GetCursorPos()
print api.GetDomainName()
print api.GetEnvironmentVariable('path')
print api.GetFileAttributes('.')
print api.GetFileVersionInfo('C:\\windows\\system32\\cmd.exe', "\\")
print api.GetFullPathName('.')
print api.GetLocalTime()
print api.GetLogicalDriveStrings().replace('\x00',' ')
print api.GetLogicalDrives()
print api.GetLongPathName('C:')
print api.GetModuleFileName(0)
print api.GetNativeSystemInfo()
print hex(api.GetSysColor(con.COLOR_WINDOW))
print api.GetSystemDirectory()
print api.GetSystemInfo()
print api.GetSystemMetrics(con.SM_CXSCREEN)
print api.GetSystemTime()
print api.GetTickCount()
print api.GetTimeZoneInformation()
print api.GetUserDefaultLangID()
print api.GetUserName()
print api.GetVersion()
print api.GetVolumeInformation('C:')
print api.GetWindowsDirectory()
print api.GlobalMemoryStatus()
print api.MessageBeep()
# print api.MessageBox(0,'hello','world',con.MB_OK)
size= api.RegQueryInfoKey(con.HKEY_LOCAL_MACHINE)
print size
for i in range(size[0]):print api.RegEnumKey(con.HKEY_LOCAL_MACHINE,i)
try:print api.SearchPath('.','win32con.txt')
except:print 'error'
print api.WinExec('Notepad')