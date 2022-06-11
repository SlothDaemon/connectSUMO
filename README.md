# connectSUMO
dll to connect Unity with Sumo

This branch utilises two extra libraries which you have to install for Visual Studio:  
- ATL v142/143  
- MFC v142/143  

To open the solution, first modify your Visual Studio installation via the Visual Studio installer.
Find your installation and click Modify.
Click 'Individual Components' in the top bar.
In this large list, use the search bar to search for "C++ ATL for latest v142 build tools (x836 & x64)", where v142 is your current Visual Studio version.
In this same list, search for "C++ MFC for latest v142 build tools (x86 & x64)". 
These libraries together can be around 1.5GB in size.


In order to test the .dll, compile it first.
Should anything go wrong during building, first make sure that the project's properties do NOT prefer x32 bit, and that unsafe code is allowed.
Additionally, should anything go wrong with regards to running the test after compilation, make sure the dll is in the correct folder.
The test program has the location hardcoded in for the sake our time, so just make sure that's all right.
