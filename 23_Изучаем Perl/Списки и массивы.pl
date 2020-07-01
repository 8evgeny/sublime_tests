$fred[0] = "yabba";
$fred[1] = "dabba";
$fred[2] = "doo";
print $fred[0],"\n";
$fred[2] = "diddley";
$fred[1] .= "whatsis"; #конкактенация
$number = 2.71828;
print $fred[$number - 1],"\n"; # Равносильно print $fred[1]

$blank = $fred[ 142_857 ]; # Неиспользованный элемент массива содержит undef
$blanc = $mel;  # Неиспользованный скаляр $mel также содержит undef

$rocks[0] = 'bedrock'; # Один элемент...
$rocks[1] = 'slate'; # другой...
$rocks[2] = 'lava'; # еще один...
$rocks[3] = 'crushed rock'; # и еще...
$rocks[99] = 'schist'; # А теперь 95 элементов undef

$end = $#rocks;  # 99, индекс последнего элемента
print $number_of_rocks = $end + 1; # Допустимо, но можно и лучше (см. далее)
$rocks[ $#rocks ] = 'hard rock'; # Последний элемент

print "\n",$rocks[ -1 ] = 'hard rock'; # Проще, чем в предыдущем примере
print "\n",$dead_rock = $rocks[-100]; # Возвращает 'bedrock'
# $rocks[ -200 ] = 'crystal';  # Фатальная ошибка!

(1, 2, 3); # Список из трех значений 1, 2 и 3
(1, 2, 3,); # Те же три значения (последняя запятая игнорируется)
("fred", 4.5); # Два значения, "fred" и 4.5
( ); # Пустой список - ноль элементов
(1..100); # Список из 100 целых чисел

(1..5); # То же, что (1, 2, 3, 4, 5)
(1.7..5.7);# То же самое - оба значения усекаются
(5..1); # Пустой список - .. работает только "вверх"
(0, 2..6, 10, 12); # То же, что (0, 2, 3, 4, 5, 6, 10, 12)
($m..$n); # Диапазон определяется текущими значениями $m и $n
(0..$#rocks); # Индексы массива из предыдущего раздела

("fred", "barney", "betty", "wilma", "dino"); #список строк
qw( fred barney betty wilma dino ); # То же, что прежде, но короче
qw(fred
barney
 betty
wilma dino ); # То же самое, но со странными пропусками
my @list = qw(fred barney betty wilma dino);
print "\n",$list[0],"\n";
print @list,"\n";

qw! fred barney betty wilma dino !;
qw/ fred barney betty wilma dino /;
qw# fred barney betty wilma dino #;
qw( fred barney betty wilma dino );
qw{ fred barney betty wilma dino };
qw[ fred barney betty wilma dino ];
qw< fred barney betty wilma dino >;

qw! yahoo\! google ask msn !; # yahoo! включается как элемент списка
($fred, $barney, $dino) = ("flintstone", "rubble", undef);#списочное присваивание
print $fred,$barney,"\n";
($fred, $barney) = ($barney, $fred); # Значения меняются местами
print $fred,$barney,"\n";
($betty[0], $betty[1]) = ($betty[1], $betty[0]);

($fred, $barney) = qw< flintstone rubble slate granite >; # Два значения проигнорированы
($wilma, $dino) = qw[flintstone];  # $dino присваивается undef

@rocks  =  qw/ bedrock slate lava /;
@tiny  =  ( ); # Пустой список
@giant  =  1..1e5;  # Список из 100 000 элементов
@stuff  =  (@giant, undef, @giant); # Список из 200 001 элемента
$dino  =  "granite";
@quarry =  (@rocks, "crushed rock", @tiny, $dino);
@copy = @quarry; # Копирование списка из одного массива в другой

print @array = 5..9,"\n";
$fred = pop(@array); # $fred присваивается 9, в @array остаются элементы (5, 6, 7, 8)
$barney = pop @array; # $barney присваивается 8, в @array остаются элементы (5, 6, 7)
pop @array; # @array теперь содержит (5, 6). (Элемент 7 удален).
print @array ,"\n";

push(@array, 0); # @array  теперь содержит (5, 6, 0)
push @array, 8; # @array теперь содержит (5, 6, 0, 8)
push @array, 1..10;  #  @array  теперь содержит десять новых элементов
@others = qw/ 9 0 2 1 0 /;
push @array, @others; # @array теперь содержит пять новых элементов (итого  19)
print @array ,"\n";

@array = qw# dino fred barney #;
$m = shift(@array); # $m присваивается "dino", @array теперь содержит ("fred", "barney")
$n = shift @array; # $n присваивается "fred", @array теперь содержит ("barney")
shift @array; # @array остается пустым
$o = shift @array; # $o присваивается undef, @array по-прежнему пуст
unshift(@array, 5); # @array содержит список из одного элемента (5)
unshift @array, 4; # @array теперь содержит (4, 5)
@others = 1..3;
unshift @array, @others; # @array теперь содержит (1, 2, 3, 4, 5)
print @array ,"\n";

@rocks = qw{ flintstone slate rubble };
print "quartz @rocks limestone\n"; # печатает пять слов, разделенных пробелами
$" = "^^"; #разделитель массива - специальная переменная $", которая по умолчанию содержит пробел
print "quartz @rocks limestone\n";
print "Three rocks are: @rocks.\n";
$email = "fred\@bedrock.edu"; # Правильно
$email = 'fred@bedrock.edu'; # Другой способ с тем же результатом

@fred = qw(hello dolly);
$y = 2;
print $x = "This is $fred[1]'s place \n";  # "This is dolly's place"
print $x = "This is $fred[$y-1]'s place \n"; # То же самое

@fred  = qw(eating rocks is wrong);
$fred  = "right";  # Мы пытаемся вывести "this is right[3]"
print  "this is $fred[3]\n";  # Выводит "wrong" из-за $fred[3]
print  "this is ${fred}[3]\n"; # Выводит "right" (защита в виде фигурных скобок)
print "this is $fred"."[3]\n"; # Снова "right" (другая строка)
print "this is $fred\[3]\n"; # Снова "right" (экранирование обратной косой чертой)

foreach $rock (qw/ bedrock slate lava /) {
print "One rock is $rock.\n"; # Выводит три слова
}

@rocks = qw/ bedrock slate lava /;
foreach $rock (@rocks) {
$rock = "\t$rock";  # Поставить символ табуляции перед каждым элементом @rocks
$rock .= "\n"; # После каждого элемента ставится символ новой строки
}
print "The rocks are:\n", @rocks; # Элементы выводятся с отступами и в разных строках

foreach (1..10) { # По умолчанию используется $_
print "I can count to $_!\n";
}
$_ = "Yabba dabba doo\n";
print; # По умолчанию выводит $_

print @fred =  6..10, "\n";
print @barney = reverse(@fred), "\n"; # Содержит 10, 9, 8, 7, 6
@wilma = reverse 6..10; # То же без использования другого массива
@fred = reverse @fred; # Результат снова возвращается к исходному состоянию

@rocks  =  qw/ bedrock slate rubble granite /;
print @sorted  =  sort(@rocks) ,"\n"; # Получаем bedrock, granite, rubble, slate
print @back  =  reverse sort @rocks,"\n"; # Последовательность от slate до bedrock
@rocks  =  sort @rocks;  # Отсортированный результат снова сохраняется в @rocks
print @numbers = sort 97..102 ,"\n"; # Получаем 100, 101, 102, 97, 98, 99

sort @rocks;  # ОШИБКА, @rocks не изменяется
@rocks = sort @rocks; # Теперь коллекция упорядочена

