<img src="/doc/images/leash_logo.png" width="150">

# Leash Debugger

Leash Debugger is a JTAG debug adapter for use over a WiFi connection with GDB. It allows GDB to connect directly to it, as opposed to using additional debugging software such as OpenOCD.

### Platform

Leash debugger runs on the Texas Instruments CC3200 SoC, and was designed for running on the [CC3200 Launchpad](http://processors.wiki.ti.com/index.php/CC32xx_LaunchPad_Hardware) development board or the [RedBearLab WiFi Mini](http://redbearlab.com/) board. There are multiple versions of the LaunchPad which use different chip revisions - not all of them were tested.

**There are still unsolved issues with the RedBearLab WiFi Mini.**

Please check the [**Known Issues**](doc/KnownIssues.md) page for up-to-date information on platform support.

### Supported Target Platforms

Currently, the only supported target configuration is a Texas Instruments CC3200 SoC over a 4-wire JTAG connection.

# More information

* [**Quick-start Guide**](doc/QuickStart.md)
* [**Build Guide**](doc/BuildGuide.md)
* [**User Guide**](doc/UserGuide.md)
* [**Wiring**](doc/Wiring.md)
* [**Report**](doc/Report.md)
* [**Known Issues**](doc/KnownIssues.md)



