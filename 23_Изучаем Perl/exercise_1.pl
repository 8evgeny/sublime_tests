$pi = 3.14159;
print $l_circle = 12.5*2*$pi,"\n";
print "input radius:\n";
$r_circle =<STDIN>;
if ($r_circle <0){print 0,"\n"
}else{
print $l_circle = $r_circle*2*$pi,"\n";}

print "input number one:\n";
$one =<STDIN>;
print "input number two:\n";
$two =<STDIN>;
print $one*$two, "\n";

print "input string:\n";
chomp($in =<STDIN>);
print "input number :\n";
$number =<STDIN>;
while ($number>0){
print $in,"\n";
$number -=1;
}