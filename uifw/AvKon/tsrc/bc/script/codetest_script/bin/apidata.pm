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

package APIData;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";
use xmlutil;

#
# API Data,
# The meaning of coverage is:
# COVER_B_CUR:  Current branch Coverage,
#       this data may be smaller than the Max Bracn cover data. in this case, it
#       means an error, the programmer should modify her program to increase the
#       coverage.
# COVER_B_MAX:  Max bracn Coverage,
#       this data is used for statistics report.
# COVER_F_CUR:  Current function coverage
# COVER_F_MAX:  Max function coverage
#
#
sub new{
    my ($class, @args) = @_;
    my $line = "--------------------------";
    my ($api_name, $file, $func)=($line, $line, $line);
    my @data=($line, $line, $line, 0,0,0,0,0,0,0);
    foreach my $i(0..9){
        $data[$i] = shift @args if @args>0;
    }

    my $self = bless {
        'APINAME'       => $data[0],
        'FILENAME'      => $data[1],
        'FUNCTION'      => $data[2],
        'K_BLOCK'       => $data[3],
        'L_BRANCH'      => $data[4],
        'M_COVER_B_CUR' => $data[5],
        'N_COVER_B_MAX' => $data[6],
        'O_COVER_F_CUR' => $data[7],
        'P_COVER_F_MAX' => $data[8],
        'Q_COMMENTS'    => $data[9]
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
        'K_BLOCK'       => $var[0],
        'L_BRANCH'      => $var[1],
        'M_COVER_B_CUR' => $var[2],
        'N_COVER_B_MAX' => $var[3],
        'O_COVER_F_CUR' => $var[4],
        'P_COVER_F_MAX' => $var[5],
        'Q_COMMENTS'    => $var[6]
    );

    foreach my $key (keys %data){
        $self->{$key}=$data{$key};
    }
}

sub get_data{
    my $self = shift;

    return (
        $self->{'K_BLOCK'},
        $self->{'L_BRANCH'},
        $self->{'M_COVER_B_CUR'},
        $self->{'N_COVER_B_MAX'},
        $self->{'O_COVER_F_CUR'},
        $self->{'P_COVER_F_MAX'},
        $self->{'Q_COMMENTS'});
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
    my @res=();
    push @res, $self->name();
    push @res, $self->filename();
    push @res, $self->function();
    push @res, $self->get_data();
    return @res;
}

#
# search #filename@class::method@d@d@d@d....#filename@class::method@d@d...
#
sub search_regex{
    my ($class, $func_name, $override)=@_;

    my $res="(";
    my $token="#[\\\w\\\._]+\\\@".util::plain_regex($func_name);
    $res.=$token;

    while($override>0){
        foreach my $i(0..6){
            $res.="\\\@[\\\d\\.]+";
        }
        $override--;
        $res.=$token;
    }
    $res.=")";

    foreach my $i(0..6){
        $res.="\\\@([\\\d\\.]+)";
    }

    return $res;
}

#
# getters
#

sub name{
    my $self=shift;
    return $self->{'APINAME'};
}

sub function{
    my $self=shift;
    return $self->{'FUNCTION'};
}

sub filename{
    my $self=shift;
    return $self->{'FILENAME'};
}

sub func_cover{
    my $self = shift;
    return $self->{'P_COVER_F_MAX'};
}

sub branch{
    my $self = shift;
    return $self->{'L_BRANCH'};
}

sub branch_cover{
    my $self = shift;
    return $self->{'N_COVER_B_MAX'};
}

sub tag_name{
    return "APIITEM";
}

1;
