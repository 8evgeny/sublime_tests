# use strict;
# use warnings;
my $str ="Camel";
print $str = $str . " "; # Присоединить пробел к $str
print $str .= " ";  # То же с оператором присваивания
my $fred =5;
print $fred **= 3; #означает «возвести $fred в третью степень
print "\nThe answer is ";
print 6 * 7;
print ".\n";
print "The answer is ", 6 * 7, ".\n";

$meal = "brontosaurus steak";
print $barney = "fred ate a $meal\n";  # Теперь $barney содержит  "fred ate a brontosaurus steak"
print $barney = 'fred ate a ' . $meal , "\n"; # Другой способ добиться того же результата

$fred = 'hello';
print "The name is \$fred.\n";  # Выводит строку со знаком доллара
print 'The name is $fred' . "\n"; # То же самое
print "The name is $fred" . "\n"; 

$what = "brontosaurus steak";
$n = 3;
print "fred ate $n $whats.\n";  # Не steaks, а значение $whats
print "fred ate $n ${what}s.\n";  # Теперь используется $what
print "fred ate $n $what" . "s.\n"; # Другой способ с тем же результатом
print 'fred ate ' . $n . ' ' . $what . "s.\n"; # Особенно неудобный способ

$line = <STDIN>;
if ($line eq "\n") {
print "That was just a blank line!\n";
} else {
print "That line of input was: $line";
}

chomp($text = <STDIN>); # Прочитать текст без символа новой строки
$text = <STDIN>;  # То же самое...
chomp($text);  # ...но в два этапа

$count = 0;
while ($count < 10) {
$count += 2;
print "count is now $count\n"; # Выводит 2 4 6 8 10
}

# Суммирование нечетных чисел
$n = 1;
while ($n < 10) {
$sum += $n;
$n += 2; # Переход к следующему нечетному числу
}
print "The total was $sum.\n";

$madonna = <STDIN>;
# $madonna = undef;
if ( defined($madonna) ) {
print "The input was $madonna";
} else {
print "No input available!\n";
}
