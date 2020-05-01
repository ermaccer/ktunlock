# ktunlock
Allows to load unencrypted car info files in K-Tech games.


# Installation
You'll need Ultimate ASI Loader(https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) renamed as winmm.dll.
Place the ASI in game folder and you're all set.


# Usage
Place carname.ini file inside car folder of any K-Tech game, it will be loaded instead of encrypted carname.dat.
You don't need to replace all DATs with INIs though, plugin will check for availability of .ini file and if not
present, will fallback to loading .dat.

You can decrypt car info data using:
https://github.com/ermaccer/MaluchTool
