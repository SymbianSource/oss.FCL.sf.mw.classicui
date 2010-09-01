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

package apiutil;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
    reform_api_table
    write_api_table
);

use strict;
use warnings;
use Cwd;

use lib "$FindBin::Bin";
use util;
use APITable;

#
#   only for internal use, it will filtered NONAME API out, and insert seperators
#

sub reform_api_table{
    &back_up_api_table();
    write_api_table(APITable->new(util::get_root_path."/output/api_table.bak.xml")->as_hash());
}

sub back_up_api_table{
    my $root_path = util::get_root_path();
    my $xml="$root_path/output/api_table.xml";
    my $bak="$root_path/output/api_table.bak.xml";
    my $cmd = util::unix2win("copy $xml $bak");
    print "$cmd\n";
    system($cmd);
}

sub write_api_table{
    my(%api_data)=@_;

    my $xml = util::get_root_path."/output/api_table.xml";
    my $writer = XMLWriter->new($xml)->push_field("APITABLE");

    my $api_number=(keys %api_data);
    my $progress_bar = ProgressBar->new($api_number);

    foreach my $key (keys %api_data){
        $progress_bar->increase();
        next if(($key eq "NONAME") || ($key eq ""));

        my $raw_line = $api_data{$key}; # $raw_line = #file_name@func_name@0@0...#file_name@func_name...
        my @list = sort(split(/#/, $raw_line));
        my $last_file_name = "";
        foreach my $item(@list){
            my($file_name, $func_name, @var) = split(/\@/, $item);
            if( defined($file_name) && defined($func_name)){

                if($last_file_name ne $file_name && $last_file_name ne ""){
                    $writer->write_block(APIData->new($key, $last_file_name)->as_xml());
                }

                $writer->write_block(APIData->new($key, $file_name, $func_name, @var)->as_xml());

                $last_file_name = $file_name;
            }
        }
        $writer->write_block(APIData->new($key, $last_file_name)->as_xml()); #the last file: APIName, lastfilename, ---,
        $writer->write_block(APIData->new($key)->as_xml()); #API gropu end with: APIName, ---, ---,
    }
    $writer->write_block(APIData->new()->as_xml()); # the last one ---, ---, ---

    $writer->close();
}

1;
