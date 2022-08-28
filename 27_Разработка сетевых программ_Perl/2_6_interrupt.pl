#!/usr/bin/perl

use strict;
my $interruptions = 0;
$SIG{INT} = \&nahdle_interruptions;
while ($interruptions < 3)
{
   print "I'm sleeping.\n";
   sleep(5);
}
sub nahdle_interruptions
{
   $interruptions++;
   warn "Don't interrupt me! You've already interrupted me 
         ${interruptions}x.\n"
}