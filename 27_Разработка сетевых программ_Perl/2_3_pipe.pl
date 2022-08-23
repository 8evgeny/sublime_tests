#!/usr/bin/perl
 use strict;
 my $arg = shift || 10;
 pipe(READER,WRITER) or die "Can't open pipe: $!\n";
 if (fork ==0)
 {
    #Первый дочерний процесс выводит данные на устройство WRITER
    close READER;
 }
