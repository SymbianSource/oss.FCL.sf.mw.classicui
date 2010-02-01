#
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:
#

package XMLReader;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";

sub new{
    my ($class, @args) = @_;
    my $fh = undef;

    my $filename = shift @args;

    open $fh, "$filename" || die "can not open file $filename for reading.\n";

    my $self = bless {
        'FILENAME' => $filename,
        'HANDLE'   => $fh,
    }, $class;
    return $self;
}

sub close{
    my $self = shift @_;
    close($self->{'HANDLE'});
}

sub handle{
    my $self= shift @_;
    return $self->{'HANDLE'};
}

sub read_block{
    my($self, $block_name) = @_;
    my $handler = $self->handle;
    my @res=();
    my $start=0;
    while(my $line = <$handler>){
        if($line =~ /<$block_name>/){
            $start = 1;
            next;
        }

        if( $start ==1 &&
            $line =~ /<(\w+)><!\[CDATA\[(.*)\]\]><\/(\w+)>/){
            if($1 ne $3){
                die "wrong XML format: $line\n";
            }
            my $name =$1;
            my $value=$2;
            push(@res, ($name, $value));
            next;
        }

        if($line =~ /<\/$block_name>/){
            my %hash_res=@res;
            return %hash_res;
        }
    }
    my %hash_res = @res;
    return %hash_res;
}

sub filename{
    my $self = shift @_;
    return $self->{'FILENAME'};
}

1;
