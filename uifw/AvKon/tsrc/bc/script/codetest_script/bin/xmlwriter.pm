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

package XMLWriter;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";

sub new{
    my ($class, @args) = @_;
    my $mod ="w";
    my $fh = undef;
    my @fields = "";

    my $filename = shift @args;
    $mod = shift @args if @args>0;

    if($mod eq "a"){
        open $fh, ">>$filename" || die "can not open $filename for appending.\n";
    }
    elsif($mod eq "w"){
        open $fh, ">$filename" || die "can not open $filename for writing.\n";
        print $fh "<?xml version=\"1.0\"?>\n";
    }
    else{
        die "unknown mod, please use w for write, a for append\n";
    }

    my $self = bless {
        'FILENAME' => $filename,
        'MOD'      => $mod,
        'HANDLE'   => $fh,
        'FIELDS'   => @fields
    }, $class;
    return $self;
}

sub close{
    my $self = shift @_;
    my @fields = split(/#/, $self->{'FIELDS'});
    foreach my $field (@fields){
        $self->pop_field() if $field ne "";
    }
    close($self->{'HANDLE'});
}

sub push_field{
    my($self, @args)=@_;
    my $fh = $self->handle;

    foreach my $field(@args){
        print $fh "<$field>\n";
        $self->{'FIELDS'}.="#$field";
    }
    return $self;
}

sub pop_field{
    my($self, @args)=@_;
    my $fh = $self->handle;

    my @fields = split(/#/, $self->{'FIELDS'});
    my $field = pop @fields;
    print $fh "</$field>\n" if $field ne "";
    $self->{'FIELDS'}=join("#", @fields);
    return $self;
}

sub handle{
    my $self= shift @_;
    return $self->{'HANDLE'};
}

#
# write a group of data block
# ex:
# <BlockName>
#   <FieldName1><![CDATA[Value1]]></FieldName1>
#   <FieldName2><![CDATA[Value2]]></FieldName2>
#   ...
#   <FieldNameN><![CDATA[ValueN]]></FieldNameN>
# </BlockName>
#
sub write_block{
    my($self, $block_name, %block_data)=@_;
    my $handler=$self->handle;

    print $handler "<$block_name>\n";
    foreach my $field_name (keys %block_data){
        my $field_value=$block_data{$field_name};
        print $handler "<$field_name><![CDATA[".$field_value."]]></$field_name>\n";
    }
    print $handler "</$block_name>\n";
    return $self;
}

1;
