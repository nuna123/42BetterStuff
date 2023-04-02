use strict;
use warnings;
use utf8;

print "Enter a string: ";
# my $str = <STDIN>;
# chomp $str;
my $str = uc <STDIN>;
$str =~ s/[^A-Z0-9]//g;

if($str eq reverse($str))
{
	print "The string is a palindrome!\n";
}
else {
	print "The string is not a palindrome.\n";
}