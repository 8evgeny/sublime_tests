print "Howdy, world!\n";
my $phrase = "Howdy, world!\n"; # Create a variable.
print $phrase; # Print the variable.

print my $answer = 42,"\n"; # an integer
my $pi = 3.14159265; # a "real" number
my $avocados = 6.02e23; # scientific notation
my $pet = "Camel"; # string
print my $sign = "I love my $pet\n"; # string with interpolation
my $cost = 'It costs $100'; # string without interpolation
my $thence = $whence; # another variable's value
my $salsa = $moles * $avocados; # a gastrochemical expression
print my $exit = system("vi $file"); # numeric status of a command
print "\n";
print my $cwd = `pwd`; # string output from a command

my $ary = \@myarray; # reference to a named array
my $hsh = \%myhash; # reference to a named hash
my $sub = \&mysub; # reference to a named subroutine

print my $ary = [1,2,3,4,5];# reference to an unnamed array
print "\n";
print $ary[2];
print my $hsh = {Na => 19, Cl => 35};# reference to an unnamed hash
print "\n";
print my $sub = sub { print $state };# reference to an unnamed subroutine
print "\n";
# my $fido = Camel–>new("Amelia"); # reference to an object

my $camels = "123";#The first assigned value of $camels is a string, but it is converted to a number
print $camels + 1, "\n";

print my $Camel ="aaa","\n";
# my $fido = Camel–>new("Amelia");
# if (not $fido) { die "dead camel"; }
# $fido–>saddle();

print my @home = ("couch", "chair", "table", "stove");
print "\n",$home[0];
print "\n",$home[1];
print "\n",$home[2];
print "\n",$home[3];
print "\n",$home[4]; #ничего не выводится