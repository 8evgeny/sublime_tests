#!/usr/bin/perl
use strict;
use IO::File;

my $file = shift;
my $counter = 0;
my $fh = IO::File->new($file)
			or die "Can't open $file: $!\n"; 
while (defined (my $line = $fh->getline))
{
	$counter++;
}
STDOUT->print ("Counted $counter lines\n");