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

package CodeTestData;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";
use xmlutil;

sub new{
    my ($class, @args) = @_;
    my $empity = "";
    my ($file, $func, $blocks, $coverage)=($empity, $empity, 0, 0);
    my @data=($file, $func, $blocks, $coverage);
    foreach my $i(0..3){
        $data[$i] = shift @args if @args>0;
    }

    my $self = bless {
        'fileName' => $data[0],
        'funcName' => $data[1],
        'blocks'   => $data[2],
        'coverage' => $data[3]
    }, $class;
    return $self;
}

sub copy{
    my($class, %hash) = @_;
    my $self = bless \%hash, $class;
    return $self;
}

sub set_data{
    my($self, @var)=@_;

    my %data =(
        'blocks'   => $var[0],
        'coverage' => $var[1]
    );

    foreach my $key (keys %data){
        $self->{$key}=$data{$key};
    }
}

sub as_xml{
    my $self= shift @_;
    return ($self->tag_name(), $self->as_hash());
}

sub as_hash{
    my $self = shift;
    my %data = %{$self};
    return %data;
}

sub as_array{
    my $self = shift;
    return ($self->filename(), $self->function(), $self->blocks(), $self->coverage());
}

sub is_override{
    my ($self, $other)=@_;

    return ($self->filename() eq $other->filename()) &&
        ($self->function() eq $other->function());
}
#
# getters
#

sub filename{
    my $self=shift;
    return $self->{'fileName'};
}

sub function{
    my $self=shift;
    return $self->{'funcName'};
}

sub blocks{
    my $self = shift;
    return $self->{'blocks'};
}

sub coverage{
    my $self = shift;
    return $self->{'coverage'};
}

sub tag_name{
    return "CoverageRec";
}

1;
