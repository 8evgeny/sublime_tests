#!/usr/bin/perl
 
 use strict;
 my %who;        #Информация о регистрации пользователей

 open (WHOFH, "who |") or die "Can't open who: $!"; #Открытие канала в команду who
 while (<WHOFH>)
 { 
    next unless  /^(\S+)/;
    $who{$1}++;
 }
 foreach (sort {$who{$b}<=>$who{$a}} keys %who)
 {
    printf "%10s %d\n",$_,$who{$_};
 }
 close WHOFH or die "Close error: $!";

  open (WHOFH, "| who") or die "Can't open who: $!"; #Открытие канала в команду who
 while (<WHOFH>)
 {
    print WHOFH "\n";
 }