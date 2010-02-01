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

package Logger;
use strict;
use vars qw(@ISA);

sub new{
    my ($class, @args) = @_;
    my $filename = "log.txt";
    $filename = shift @args if @args>0;

    my $self = bless {
        FILENAME => $filename,
    }, $class;
    return $self;
}

sub write{
    my ($self, $line) = @_;
    my $filename= $self->{FILENAME};

    my $fh=undef;
    if(-e $filename){
        open $fh, ">>$filename" || die "can not open $filename for appending.\n";
    }
    else{
        open $fh, ">$filename" || die "can not open $filename for writing\n";
    }
    print $fh $line;
    close $fh;
}

1;
