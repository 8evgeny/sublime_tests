chomp(@list =<STDIN>);
print @back = reverse @list;

chomp(@nums =<STDIN>);
print "@nums\n";
	@list =(qw\fred betty barney dino wilma pebbles bamm-bamm\);
	foreach (@nums) {
		print $list[$_],"\n"
	};

chomp(@list =<STDIN>);
@sorted = sort @list;
print "@sorted";