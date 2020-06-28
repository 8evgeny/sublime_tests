ѕример 5.3. dutree
#!/usr/bin/perl -w
# dutree Ц печать сортированного иерархического представлени€
# выходных данных du
use strict;
my %Dirsize;
my %Kids;
getdots(my $topdir = input());
output($topdir);
# «апустить du, прочитать входные данные, сохранить размеры и подкаталоги
# ¬ернуть последний прочитанный каталог (файл?)
sub input { 
    my($size, $name, $parent);
    @ARGV = ("du @ARGV |");         # ѕодготовить аргументы
    while (<>)
        ($size, $name) = split;
        $Dirsize{$name} = $size;
        ($parent = $name) =~ s#/[^/]+$##;   # »м€ каталога

    push @{ $Kids{$parent} }, $name unless eof;
    } 
    return $name;
}

# –ассчитать, сколько места занимают файлы каждого каталога,
# не наход€щиес€ в подкаталогах. ƒобавить новый фиктивный 
# подкаталог с именем ".", содержащий полученную величину.
sub getdots {
    my $root = $_[0];
    my($size, $cursize);
    $size = $cursize = $Dirsize{$root};
    if ($Kids{$root}) {
        for my $kid (@{ $Kids{$root} }) { 
            $cursize -= $Dirsize{$kid};
            getdots($kid);
        }
    } 
    if ($size != $cursize) {
        my $dot = "$root/.";
        $Dirsize{$dot} = $cursize;
        push @{ $Kids{$root} }, $dot;
    } 
} 

# –екурсивно вывести все данные, 
# передава€ при рекурсивных вызовах
# выравнивающие пробелы и ширину числа
sub output {
    my($root, $prefix, $width) = (shift, shift || '', shift || 0);
    my $path;
    ($path = $root) =~ s#.*/##;     # Ѕазовое им€
    my $size = $Dirsize{$root};
    my $line = sprintf("%${width}d %s", $size, $path);
    print $prefix, $line, "\n";
    for ($prefix .= $line) {        # ƒополнительный вывод
        s/\d /| /;
        s/[^|]/ /g;
    }
    if ($Kids{$root}) {             # ”зел имеет подузлы
        my @Kids = @{ $Kids{$root} };
        @Kids = sort { $Dirsize{$b} <=> $Dirsize{$a} } @Kids;
        $Dirsize{$Kids[0]} =~ /(\d+)/;
        my $width = length $1;
        for my $kid (@Kids) { output($kid, $prefix, $width) }
    }
} 

