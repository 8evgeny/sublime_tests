#!/usr/bin/perl
use IO::File;
my $file = shift;              #Читаем параметр командной строки в переменную $file
my $fh = IO::File->new($file); #Дескриптор присваивается переменной
my $line = <$fh>;              #Чтение строки из дескриптора файла
print $line;