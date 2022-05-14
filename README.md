# Lrapava/hcurve
Lrapava/hcurve is a simple command-line utility for generating pseudo Hilbert curves' visualisations.

# --help

Lrapava/hcurve is a simple command-line utility for generating pseudo Hilbert curves' visualisations.\n"
You can view source-code at https://github.com/Lrapava/hcurve\n"
For more informatiob about Hilbert curve view https://youtu.be/3s7h2MHQtxc\n\n"
Usage:\n"
hcurve [OPTION..] ORDER\n\n"
Options:\n"
--help         | -h   displays this message\n"
--ascii        | -a   visualizes the curve in form of ascii art\n"
--color        | -c   visualizes the curve in form of ppm\n"
--grey         | -g   visualizes the curve in form of pgm\n"
--instructions | -i   outputs \"instructions\" for building the curve (F - move forward, + - rotate right by 90 degrees, - - rotate left by 90 degrees)\n"
--rainbow      | -r   the color (if used with -c) or the brightness (if used with -g) of the curve changes depending on the length of the curve\n"
--zero         | -z   sets padding to 0 and weight to 1\n"
--weight=X            sets width of the curve to X\n"
--padding=X           sets padding to X\n"
--background=X        fills the background with X\n"


# Sample images

![demo](https://user-images.githubusercontent.com/46052668/168427006-a58256e9-6414-4b00-9d7c-59d204e5a9a6.png)
