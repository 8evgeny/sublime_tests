use strict;
use warnings;
print "I'm $^X, $^V, on $^O\n";
print"I'm $^X, ";
print "Script: $0 (@ARGV);\n";
print "Pid $$ by uid $<\n";
open my $f, '<','/etc/shadow'
or die "No shadow: $!\n";				