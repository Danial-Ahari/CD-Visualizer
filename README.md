# CD-Visualizer
A visualization program for CD .BIN files that shows errors (detected via Natalia Portillo's EDC/ECC Checker).

## Acknowledgements

- EDC/ECC Checker - https://github.com/claunia/edccchk (License in source file)  
- This visualizer is being completed as part of a project for an RCEU in 2023 regarding CD-ROM's and Data Recovery. The main project can be found at: https://github.com/Danial-Ahari/RCEU-2023

## Description

This is essentially a visual front-end and file-loader for Natalia Portillo's EDC/ECC Checker. It reads a raw CD image file, breaks it into sectors, checks each sector using the EDC/ECC checker, then visualizes it using a block diagram made in GTK.

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

- ~~Add a display for how many *total* errors there are in an image.~~
- ~~Make this a lot more usable.~~
- Maybe put all the business code in a place that's not the "MainWindow" class.
- ~~Better interface.~~
- Maybe consider using better numbers.
- Make this compatible with larger images.
- ~~In tandem with better interface, PNG (nope, BMP) exporting.~~

## Changelog

[CHANGELOG](CHANGELOG.md)
