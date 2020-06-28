sub Cow::speak {
print "Корова: му-у-у-у!\n";
}
sub Horse::speak {
print "Лошадь: иг-о-го!\n";
}
sub Sheep::speak {
print "Овца: бе-е-е-е!\n";
}
my @pasture = qw(Cow Cow Horse Sheep Sheep);
foreach my $beast (@pasture) {
&{$beast."::speak"}; # символическая ссылка на подпрограмму
}
