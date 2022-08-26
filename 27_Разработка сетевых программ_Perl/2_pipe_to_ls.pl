#!/usr/bin/perl
use strict;

open (LS, "| ls -l") or die "Can't open ls: $!";
 while (<LS>)
 {
    print LS "\n";
 }

open (CAT, "| cat textFile") or die "Can't open cat: $!";
 while (<CAT>)
 {
    print CAT "\n";
 }
 
my $wc_output = `wc textFile`;
print "\n$wc_output\n" ;