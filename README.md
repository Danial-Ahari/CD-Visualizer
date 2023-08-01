# CD-Visualizer
A visualization program for CD .BIN files that shows errors (detected via Natalia Portillo's EDC/ECC Checker).
This visualizer is being completed as part of a project for an RCEU in 2023 regarding CD-ROM's and Data Recovery.

## Acknowledgements

- EDC/ECC Checker - https://github.com/claunia/edccchk (License in source file)  

## Licensing

- Natalia Portillo's EDC/ECC Checker's license is included in the file edcchk.cpp (under /src/)
	- The license requires a declaration of changes made. Out of the original project, only the one file was included. The main function entry point has been commented out. Only the business code is being utilized. No alterations to that code have been made.
	
- This program is released under the GPL v3 license as required and wished for by the copyright holders.

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

## Known Issues

- It can't visualize images larger than 333k sectors. I have found some CDs that break this limit for some reason. Fixing this would require deviating from round numbers and adjusting the code accordingly. It is not especially useful for the use case I intend it for. I might fix it eventually, but it's not on my to-do list.

## Changelog

[CHANGELOG](CHANGELOG.md)
