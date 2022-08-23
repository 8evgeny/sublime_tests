#!/usr/bin/perl
use IO::Socket;
my $server = shift;                      #Читаем параметр командной строки в переменную $server
my $fh = IO::Socket::INET->new($server); #Дескриптор присваивается переменной
my $line = <$fh>;                        #Чтение строки из дескриптора сокета
print $line;