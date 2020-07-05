
use 5.010;
sub total{
	my $summ_total = 0;
	my @sum;
foreach my $number( @_ ){
	chomp $number;
	push @sum,$number;
	$summ_total += $number;
}
print "@sum","\n";
$summ_total;
}

my @fred = qw{ 1 3 5 7 9 };
my $fred_total = total(@fred);
print "The total of \@fred is $fred_total.\n";
print "Enter some numbers on separate lines: ";
my $user_total = total(<STDIN>);
print "The total of those numbers is $user_total.\n";

print total (1..1000),"\n";