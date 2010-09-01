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

package APITable;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";
use xmlutil;
use util;
use apidata;
use CodeTestData;

#
# API table contains aggregation of API Data
#

sub new{
    my ($class, @args) = @_;
    my $filename = util::get_root_path."/output/api_table.xml";
    $filename = shift @args if @args>0;

    my $self = bless {
        FILENAME => $filename,
        TABLE => undef
    }, $class;
    return $self->read_table();
}

sub read_table{
    my $self = shift;

    my $reader = XMLReader->new($self->{FILENAME});
    while( my %item=$reader->read_block(APIData->tag_name()) ){
        my $api_item = APIData->copy(%item);

        next if $api_item->name() eq "";
        next if($api_item->filename() =~ /----/ || $api_item->function() =~ /----/);


        $self->add_api($api_item);
    }
    $reader->close();
    return $self;
}

sub as_hash{
    my $self = shift;
    return %{$self->{TABLE}};
}

#
# added as APIName => #filename.h@function@1@0@3@....#filename.h@function@3@0....
#
sub add_api{
    my ($self, $item)=@_;
    my @array = $item->as_array();
    my $name = shift @array;
    my $value = "#".join("\@", @array);

    if(defined $self->{TABLE}->{$name}){
        $self->{TABLE}->{$name}.=$value;
    }
    else{
        $self->{TABLE}->{$name}=$value;
    }
    return $self;
}

sub replace{
    my ($self, $record, $override) = @_;

    my ($filename, $function, $blocks, $coverage)=$record->as_array();
    $coverage = 1 if($coverage>0);

    my %api_table = $self->as_hash();
    foreach my $api_name (keys %api_table){

        my $api_list=$api_table{$api_name};

        my $search_regex = APIData->search_regex($function, $override);

        if( $api_list=~ /$search_regex/ ){
            #replace the coverage data here
            my $same_parts = $1;
            my($block, $branch, $cover_b_cur, $cover_b_max, $cover_f_cur, $cover_f_max)=
                    ($2, $3, $4, $5, $6, $7);
            my $wrong = 1;
            if($coverage>=$cover_f_max){
                $cover_f_max = $coverage;
                $wrong = 0;
            }
            $cover_f_cur = $coverage;

            my $replace_regex = $same_parts."\@".join("\@",
                ($block, $branch, $cover_b_cur, $cover_b_max, $cover_f_cur, $cover_f_max, $wrong) );

            $api_list =~ s/$search_regex/$replace_regex/;

            $self->{TABLE}->{$api_name}=$api_list;

            last;
        }
    }

    return $self;
}
1;
