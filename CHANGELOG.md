### Original Code

This code was essentially just a very basic front end for the EDC/ECC checker.

### June 29th - 12:45

A lot of changes made today. Mostly knocking items off the to-do list, and making the program more usable.

### July 3rd - 15:00

Better interface, more usable, total number of errors, sectors, and error rate, BMP creation (no exporting yet). Multiple instances can run at the same time. Absolute paths are supported.

### July 5th - 15:00

Better interface again, more usable again, now can export images. Updated README as well with mention of requirements for the GTK interface.

### July 10th - 14:00

It can read full-size disc images now. I misunderstood and thought CDs were 330k sectors, not 333k. 

### July 12th - 11:43

Fixed an issue that was causing it to improperly handle getting the hex data of a sector. It can now properly read 333k sector images.

### July 25th 10:00

Added better licensing information.

### August 1st 10:15

Attempted to make it able to visualize disc images with standards-breaking numbers of sectors, but failed to complete that and just reverted changes, noting it as a known issue in README.
