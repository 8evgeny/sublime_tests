#!/usr/bin/perl
 print "PID=$$\n";
 my $child = fork()	;
 die "Can't fork: $!" unless defined $child;
 if ($child > 0) #Родительский процесс
 {
 	print "Parent process: PID=$$, child=$child\n";
 }
 else #Дочерний процесс
 {
 	my $ppid = getppid();
 	print "Child process: PID=$$, parrent=$ppid\n";
 }