# Teletext MRI
Teletext animation of my MRI brain scan on BBC Micro computer.

In Teletext on the BBC Micro computer (Mode 7) there are 1024 bytes per Teletext page.

There is space for 40x25 characters to be displayed on screen at once, however to use the graphics characters a special code is needed per line to enable graphics mode.

The graphics characters are 2x3 pixels each which leaves the effective useable resolution in Mode 7 at 78x75 pixels.

I had an MRI brain scan in July 2009 and was handed all the scan data as JPG and DICOM files on a CD ROM to take to my consultant for review and luckily got to keep the CD. The JPG images have text data overlaid so aren't as useful for remixing. I read up on the DICOM file format and wrote code to convert the images contained within them into something more useful.

I've used the dataset previously to create 3D models by edge detection, and ribboning but wanted to make an animation which went through the slices.

The 22 images I used for the Teletext animation were from a set taken on the sagittal plane scanned on Philips Panorama (1.0 Telsa) MRI scanner.

I wrote a program (img2tt) to convert images to black and white Teletext pages with graphics.

img2tt can be built using the Makefile, you then give it an image and it outputsa single 1024 byte Teletext page, which can be concattenated to others to make a set. This raw Teletext pages are in the file txmri.

