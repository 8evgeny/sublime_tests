#!/usr/bin/perl
use strict; use Socket;
   while (<>) 
   {
   chomp ;
   my $packed_addr = gethostbyname ($_);
   unless ($packed_addr) {
      print "$_ => ?\n";
      next;
   }
my $dotted_quad = inet_ntoa($packed_addr);
print "$_ => $dotted_quad\n";
}