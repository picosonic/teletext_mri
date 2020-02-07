# Teletext MRI
Teletext animation of my MRI brain scan on BBC Micro computer.

![Teletext MRI animation](teletextmri.gif?raw=true "Teletext MRI animation")

In Teletext on the BBC Micro computer (Mode 7) there are 1024 bytes per Teletext page (when aligned to memory page boundaries).

There is space for 40x25 characters to be displayed on screen at once, however to use the graphics characters a special code is needed per line to enable graphics mode for the remaining characters on that line.

The Teletext graphics characters are 2x3 pixels each which leaves the effective useable resolution in Mode 7 at 78x75 pixels.

I had an MRI brain scan in July 2009 and was handed all the scan data as JPG and DICOM files on a CD ROM to take to my consultant for review and luckily got to keep the CD. The JPG images have text data overlaid so aren't as useful for remixing. I read up on the [DICOM](https://en.wikipedia.org/wiki/DICOM) medical imaging file format and wrote code to convert the images contained within them into something more useful.

I've used the dataset previously to create 3D models utilising edge detection, and ribboning but wanted to make an animation which went through the slices but on retro hardware.

The 22 images I used for the Teletext animation were from a set taken on the sagittal plane scanned on a Philips Panorama (1.0 Tesla) MRI scanner.

I wrote a program (img2tt) to convert image files to black and white Teletext pages with graphics.

img2tt can be built using the Makefile, you then give it an image filename as a command line parameter and it outputs a single 1024 byte Teletext page, which can be concattenated to other pages to make a set. The raw Teletext pages converted by img2tt are in the file txmri.

Note that you need to have the [developers image library](http://openil.sourceforge.net/) headers installed to compile img2tt. On Debian these can be found within the libdevil-dev package.

The BBC Micro assembly code can be built using [beebasm](https://github.com/stardot/beebasm). I used [Microsoft Visual Studio code](https://code.visualstudio.com/) for the editing and build/run using the [beeb-vsc](https://github.com/simondotm/beeb-vsc) plugin by [Simon M](https://github.com/simondotm).
