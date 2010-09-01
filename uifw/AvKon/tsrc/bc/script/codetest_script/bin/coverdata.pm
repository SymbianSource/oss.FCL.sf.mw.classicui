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

package CoverData;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";
use apidata;

sub new{
    my ($class, @args) = @_;

    my $self = bless {
        'NUMERATOR'        => 0,
        'DENOMINATOR'      => 0
    }, $class;
    return $self;
}

# virtual function here
sub add_data{}

sub reset{
    my $self = shift;
    $self->{'NUMERATOR'}=0;
    $self->{'DENOMINATOR'}=0;
    return $self;
}

sub coverage{
    my $self= shift @_;
    return 0 if $self->{'DENOMINATOR'}==0;
    return $self->numerator()/$self->denominator();
}

sub numerator{
    my $self = shift;
    return $self->{'NUMERATOR'};
}

sub denominator{
    my $self = shift;
    return $self->{'DENOMINATOR'};
}

sub as_string{
    my $self = shift @_;
    return $self->numerator()."/".$self->denominator()."=".$self->coverage();
}

1;
