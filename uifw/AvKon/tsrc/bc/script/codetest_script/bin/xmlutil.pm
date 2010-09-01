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

package xmlutil;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
    open_xml
    close_xml
    write_xml
    write_xml_block
    write_xml_data
    write_xml_header
    write_xml_tailer
);

use strict;
use warnings;
use Cwd;

use lib "$FindBin::Bin";
use util;

#
# open a xml file for write/read
# @param $filename, xml filename
# @param $mod, "r" read, "w" write. "a"???
# @return the xml file handler
#
sub open_xml{
    my ($filename, $mod) = @_;

    if($mod eq "w"){
        #clear prevois xml
        my $cmd=util::unix2win("del $filename");
        print "$cmd\n";
        system($cmd);
        #system("pause");
        open my $fh, ">>$filename" || die "can not open $filename for writing.\n";
        return $fh;
    }
    if($mod eq "r"){
        open my $fh, "$filename" || die "can not open $filename for reading.\n";
        return $fh;
    }
}

#
# close the xml file
# @param $filename
#
sub close_xml{
    my($handler)=@_;
    close($handler);
}

#
# write a single data
#
sub write_xml_data{
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
sub write_xml_block{
    my($handler, $block_name, %block_data)=@_;

    print $handler "<$block_name>\n";
    foreach my $field_name (keys %block_data){
        my $field_value=$block_data{$field_name};
        print $handler "<$field_name><![CDATA[".$field_value."]]></$field_name>\n";
    }
    print $handler "</$block_name>\n";
}

sub read_xml_block{
    my($handler, $block_name) = @_;
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

sub write_xml_header{
    my($handler, $name)=@_;
    print $handler "<?xml version=\"1.0\"?>\n";
    print $handler "<$name>\n";
}

sub write_xml_tailer{
    my($handler, $name)=@_;
    print $handler "</$name>\n";
}

#
# write raw contents
#
sub write_xml{
}

1;
