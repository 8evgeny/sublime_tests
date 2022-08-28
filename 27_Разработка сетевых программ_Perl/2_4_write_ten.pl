#!/usr/bin/perl

 use strict;
open (PIPE, "| 2_5_read_three.pl") or die "Can't open : $!";
select  PIPE; $ | =1; select STDOUT;
my $count = 0;
for (1..10)
{
   warn  "Writing line $_\n";
   print PIPE "This is line number $_\n" and $count++;
   sleep 1;
}
close  PIPE or die "Can't close  pipe: $!";
print "Wrote $count lines of texy\n";