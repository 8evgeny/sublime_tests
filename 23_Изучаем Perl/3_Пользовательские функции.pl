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

foreach (1..12) {
my($square) = $_ * $_; # Приватная переменная для этого цикла
print "$_ squared is $square.\n";
}

my @names = qw/ fred barney betty dino wilma pebbles bamm-bamm /;
print my $result = &which_element_is("dino", @names),"\n";
sub which_element_is {
my($what, @array) = @_;
foreach (0..$#array) { # Индексы элементов @array
if ($what eq $array[$_]) {
return $_; # Ранний возврат при успешном поиске
}
}
-1; # Элемент не найден (включение return не обязательно)
}

sub division {
$_[0] / $_[1];  # Первый параметр делится на второй
}
print my $quotient = division 355, 113; # Использует &division
print "\n";

sub chomp {
print "Munch, munch!\n";
}
&chomp; # Знак & обязателен!

sub list_from_fred_to_barney {
if ($fred < $barney) {
# Отсчет по возрастанию от $fred к $barney
$fred..$barney;
} else {
# Отсчет по убыванию от $fred к $barney
reverse $barney..$fred;
}
}
$fred = 11;
$barney = 6;
@c = &list_from_fred_to_barney; # @c содержит (11, 10, 9, 8, 7, 6)
print "@c","\n";

use 5.010;
sub marine {
state $n = 0; # private, persistent variable $n
$n += 1;
print "Hello, sailor number $n!\n";
}
&marine; #  Hello, sailor number 1!
&marine; #  Hello, sailor number 2!
&marine; #  Hello, sailor number 3!
&marine; #  Hello, sailor number 4!

use 5.010;
running_sum( 5, 6 );
running_sum( 1..3 );
running_sum( 4 );
sub running_sum {
state $sum = 0;
state @numbers;
foreach my $number ( @_ ) {
push @numbers, $number;
$sum += $number;
}
say "The sum of (@numbers) is $sum";
}
