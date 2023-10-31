# Extended-CyScope
This is an extention to the CyScope design for Infineon/Cypress PSoC 5LP processor development boards.
#
This project is an extention of original work from here: https://github.com/Infineon/CyScope

Using this extention of CyScope is probably best started by reading the original docs from Infineon/Cypress in the above Repo on how to program the boards before jumping in the middle this activity.

There is also another adaptation of the original work here: http://eepmagic.mit.edu/page/efirst-oscilloscope.html which is alos a good place to gain understanding.
#
The project (firmware) for the oscilloscope is written using PSoC Creator. The primary target development kit for this activity is the CY8CKIT-059. The CY8CKIT-059 kit has two PSoC 5 LP chips. One for the programmer end and one that is the target of the programmer. So in the case of the -059 board you leave the programmer end running the programmer firmware (what is loaded from the factory) i.e. do not hold down the reset switch when plugging in the USB cable. The Creator software will then use the programmer to down load the scope firmware to the chip on the other (longer) end of the board. Once programed the other mico-usb connector is used to communicate with the chip now programmed with the scope firmware.

The -059 version of the firware supports up to 4 analog scope input channels (12 bit ADC resolution) and up to 2 analog AWG output channels (8 bit DAC resolution). Along with 5 static digital output and input pins.

There are other development boards from Infineon that include the PSoC 5 LP chip as the KitProg programmer. The other two example projects in this repo, for the CY8CKIT-043 and the CY8CKIT-044, are targeted at the PSoC 5 LP chips which are used for the KitProg programmers on these kits. The fact that the CY8CKIT-043 and the CY8CKIT-044 also contain PSoC 4 chips is irrelevant to this activity. We are only interested in the Programmer end of the kits. Thus why you need to put the board into the bootloader by holding down the reset switch. Now the bootloader is used to put the scope firmware in the chip.

The -044 version has the 4 input and 2 output channels and some of the other functions using the 14 pins on the dual row header but not all of what the -059 has.  The -043 version only has 3 scope inputs and 2 analog outputs because of what pins are are available. The -043 and -044 kits have limited utility without installing the de-coupling cap on the second ADC reference pin.

There are two ways to program the project into the kit. You can either open the project in PSoC Creator to program the kit from inside the tool, or you can use PSoC Programmer to download an existing project’s build file to the kit. If you want to modify the project for any reason, PSoC Creator is the tool that you would use.

The creator development software is all free and is available from the following locations. Each row is a superset of the row above it so if you want everything, just download and run the CY8CKIT-059 kit setup installer.
Purpose	/ Web Site:

View and modify the project or create your own custom project and program it to the kit. (The installer includes PSoC Programmer)	

https://www.infineon.com/cms/en/design-support/tools/sdk/psoc-software/psoc-creator/

View kit documentation and design. 
(Kit Setup includes PSoC Creator and PSoC Programmer, Kit Only includes just the kit file)	

https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-059
