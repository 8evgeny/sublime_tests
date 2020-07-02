sub marine {
$n += 1; # Глобальная переменная $n
print "Hello, sailor number $n!\n";
}

&marine; #  Hello, sailor number 1!
&marine; #  Hello, sailor number 2!
&marine; #  Hello, sailor number 3!
&marine; #  Hello, sailor number 4!

sub sum_of_fred_and_barney {
print "Hey, you called the sum_of_fred_and_barney subroutine!\n";
$fred + $barney; # Возвращаемое значение
}

$fred = 3;
$barney = 4;
$wilma = &sum_of_fred_and_barney;  # $wilma присваивается 7
print "\$wilma is $wilma.\n";
$betty = 3 * &sum_of_fred_and_barney; # $betty присваивается 21
print "\$betty is $betty.\n";

sub larger_of_fred_or_barney {
if ($fred > $barney) {
$fred;
} else {
$barney;
}
}

print &larger_of_fred_or_barney,"\n";

sub max {  # Сравните с &larger_of_fred_or_barney
if ($_[0] > $_[1]) {
$_[0];
} else {
$_[1];
}
}

print &max ($fred,$barney),"\n";
print &max ($barney,$fred),"\n";

sub max {
# my($m, $n);  # Новые, приватные переменные для этого блока
# ($m, $n) = @_;  # Присваивание имен параметрам
my($m, $n) = @_; # заменяет 2строки
if ($m > $n) { $m } else { $n }
}

print &max ($fred,$barney),"\n";
print &max ($barney,$fred),"\n";

$maximum = &max(3, 5, 10, 4, 6);
sub max {
my($max_so_far) = shift @_;    # Пока сохраняем как максимальный первый элемент
foreach (@_) {                 # Просмотреть все остальные аргументы
if ($_ > $max_so_far) {        # Текущий аргумент больше сохраненного?
$max_so_far = $_;
}
}
$max_so_far;                   # Возвращается
}

print $maximum,"\n";