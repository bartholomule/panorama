#!/usr/bin/perl
#
# colorgen:- a Perl script to convert the X color names
#            in rgb.txt into the Panorama file format.
#            Output defaults to stdout.

#
# 23-JUL-1999 Converted by Hugh Sasse <hgs@dmu.ac.uk>
# to produce output suitable for PSL files rather than
# RT files -- hence the change of name.
# 

if ( -f "/usr/X11R6/lib/X11/rgb.txt")
{
    $RGBFILE = "/usr/X11R6/lib/X11/rgb.txt";
}
elsif ( -f "/usr/openwin/lib/X11/rgb.txt")
{
    $RGBFILE = "/usr/openwin/lib/X11/rgb.txt";
}
else
{
    die "Unable to find rgb.txt ";
}


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
    printf "Color C%-21s = Color (%7.6f, %7.6f, %7.6f)\n",ucfirst $desc,$red,$green,$blue;
  }
}
