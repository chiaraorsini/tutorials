#!/usr/bin/env perl

# best practices
use strict;
use warnings;

# look for packages in current directory
use FindBin qw($Bin);   # http://perldoc.perl.org/FindBin.html
use lib "$Bin";

# use the AAA::Class module
use AAA::Class;

# create a new class istance: 'a'
my $a = AAA::Class->new();

# run a method of class AAA::Class on istance a
$a->do_something();


