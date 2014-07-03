#!/usr/bin/env perl

# class definitions

# define package name
package AAA::Class;

# best practices
use strict;
use warnings;

# constructor
sub new { 
  # associate class with first operator (i.e. class name AAA:class)
  my $class = shift;
  my $self = {};
  # bind self and class  (only in constructor)
  bless $self, $class;
  # init class internal parameters
  # (new parameters can be added afterwards)
  $self->{"test"}{"a"}{"b"} = 3;
  $self->{"test"}{"a"}{"c"} = 3;
  $self->{"test"}{"d"}{"c"} = 3;
  # return the class created, 
  # i.e. a pointer to the instance created
  return $self;
}


sub do_something {
  # first parameter (implicit) is the istance
  my $self = shift;
  # print the type of object referenced by 
  # $self->{"test"}
  print ref($self->{"test"}) . "\n";
  my %test = %{$self->{"test"}};
  my ($a,$b);
  foreach $a (keys %test) {
    foreach $b (keys $test{$a}) {
      print $test{$a}{$b} . "\n";
    }
  }
}

# every package file terminates with 1;
1;

