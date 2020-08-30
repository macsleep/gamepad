#!/usr/bin/perl
#
# script logs UART TX ouput to file debug.txt
#

use strict;
use warnings;
use Device::SerialPort;

# use SerialPort to configure
my $devname = '/dev/tty.usbserial-A403JXK2';
my $dev = Device::SerialPort->new($devname);
$dev or die "can't open $devname\n";

# config
$dev->baudrate(100000);
$dev->databits(8);
$dev->parity("odd");
$dev->stopbits(2);
$dev->handshake("none");

# flush
$dev->purge_rx();

# get filehandle
open DH, '+<', $dev->{'NAME'};

my $filename = 'debug.txt';
open(FH, '>', $filename) or die $!;
FH->autoflush(1);

while(<DH>) {
	print;
	print FH;
}

# finish
close FH;
close DH;
$dev->close();

exit 0;

