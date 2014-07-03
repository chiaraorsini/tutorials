

# How to catch signals in perl


use strict;
use warnings;

# 1) define the signals you need to catch
#    and the handler to associate with that 
#    signal
$SIG{INT}  = \&signal_handler;
$SIG{TERM} = \&signal_handler;
$SIG{KILL} = \&signal_handler;
$SIG{STOP} = \&signal_handler;


# 2) execute some code
sleep(20);


# 3) define the handler to run when a signal is caught
sub signal_handler {
    die "Caught a signal $!";
}

