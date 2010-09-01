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

package ProgressBar;
use strict;
use vars qw(@ISA);

sub new{
    my ($class, @args) = @_;
    my ($msg, $total) = ("progress", 100);
    $total = shift @args if @args>0;
    $msg   = shift @args if @args>0;

    my $self = bless {
        TOTAL => $total,
        MSG   => $msg,
        CURRENT =>0
    }, $class;
    return $self;
}

sub increase{
    my $self = shift;
    $self->{CURRENT}++;
    return $self->show($self->{MSG}, int($self->{CURRENT}*100/$self->{TOTAL}));
}

#
# @param $msg, the message show before the progress bar.
# @param $progress, the percentage range[1~100]
#
sub show{
    my($self, $msg, $progress)=@_;
    print STDERR "[$msg: $progress"."\%]";
    foreach my $i(1..($progress/3)){
        print STDERR ".";
    }
    print STDERR "\r";
    return $self;
}

1;
