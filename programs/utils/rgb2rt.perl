#!/usr/bin/perl
#
# colorgen:- a Perl script to convert the X color names
#            in rgb.txt into the Panorama file format.
#            Output defaults to stdout.

$RGBFILE = "/usr/X11R6/lib/X11/rgb.txt";

open RGBFILE or die "Can't open $RGBFILE: $\n";
@textin = <RGBFILE>;
close RGBFILE;

shift @textin;    	# lose the first line
chomp @textin;    	# and the trailing CR on all the remaining lines 

# parse r,g,b, and description from each line.
# Names with embedded spaces are ignored, because
# there will be a mixed-case alternative.
# Each name has its first character forced to uppercase,
# and a 'C' is prepended to follow the existing naming
# convention.

foreach(@textin)
{
  ($red,$green,$blue,$desc) = m/(\d+\s*)(\d+\s*)(\d+\s*)(.*)/o;
  $red   /= 255;
  $green /= 255;
  $blue  /= 255;
  unless ($desc =~ /\s+/) # skip descriptions containing spaces
  {
    printf "define color C%-21s{ red %7.6f green %7.6f blue %7.6f }\n",ucfirst $desc,$red,$green,$blue;
  }
}
