# CD-Visualizer
A visualization program for CD .BIN files that shows errors (detected via Natalia Portillo's EDC/ECC Checker).
This visualizer is being completed as part of a project for an RCEU in 2023 regarding CD-ROM's and Data Recovery.

## Acknowledgements

- EDC/ECC Checker - https://github.com/claunia/edccchk (License in source file)  

## Description

This is essentially a visual front-end and file-loader for Natalia Portillo's EDC/ECC Checker. It reads a raw CD image file, breaks it into sectors, checks each sector using the EDC/ECC checker, then visualizes it using a block diagram made in GTK.

## System Requirements

Any reasonably modern computer should be able to run this, but it will take at least a few seconds to load data from the file and check it. If running from a command line, you can see the errors it is detecting as it does so. (The edcchk library uses stderr to output that data.) For general usability, you should be using a monitor of at least 1280x960 and graphics hardware that can display at least 16 colours. For optimum usage, a monitor with width of at least 1080 pixels is encouraged. The application starts at a size of 1280x720 and will display with a width of a bit over 1000 pixels at maximum. A method for shrinking objects on the window hasn't been implemented here yet. I'm not sure if that's a feature in gtk at all.

## Build

This should compile fine on Linux, but I have not tested it on any other system. To build, simply:

- Clone source code or download ZIP file and extract to a folder.

`git clone https://github.com/Danial-Ahari/CD-Visualizer.git`

- Enter folder and run make.

`make cdvisualizer`

Note: Requires libgtkmm (version 3.0 used for testing).

## Usage

Run cdvisualizer, type the file name (full absolute path) in the top left, and click "Open".

## To Do

- ~~Maybe put all the business code in a place that's not the "MainWindow" class.~~ Not sure if I actually want to do this, nor what coding practice says I should do.
- ~~Maybe consider using better numbers.~~ The numbers chosen are working fine and divide evenly.
- Make this compatible with larger images. (This could be done, but does it make sense to do so? EDCCHK only does CD images.)

## Changelog

[CHANGELOG](CHANGELOG.md)
