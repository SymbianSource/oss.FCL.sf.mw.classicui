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
#!/usr/bin/perl

#
# coverutil.pm
#

package coverutil;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
    process_api
    summarize
);

use strict;
use warnings;
use Cwd;

use lib "$FindBin::Bin";
use util;
use apiutil;
use apidata;
use xmlutil;
use xmlwriter;
use xmlreader;
use FuncCoverData;
use BranchCoverData;
use ProgressBar;
use CodeTestData;
use APITable;

#
# fill out API coverage data
# the  data comes from specified folder.
# the result is root/output/api_table.xml
#
# @param, $dir, the folder contains code test coverage result data xml file.
#
sub process_api{
    my($dir) = @_;
    print "$dir\n";

    opendir MOD_DIR, "$dir" || die "can not open dir $dir.\n";
    my @xmls=();
    while(my $filename=readdir(MOD_DIR)){
        if(lc($filename) =~ /\.xml/){
            push(@xmls, "$dir/$filename");
            next;
        }
    }
    closedir MOD_DIR;

    foreach my $xml_file (@xmls){
        &process_file(@xmls);
    }
}

sub process_file{
    my($xml)=@_;

    my $table  = APITable->new();
    my $reader = XMLReader->new($xml);

    my $last_record=CodeTestData->new();
    my $override=0;
    while( my %item= $reader->read_block(CodeTestData->tag_name()) ){
        my $record = CodeTestData->copy(%item);
        if($record->is_override($last_record)){
            $override++;
        }
        else{
            $override=0;
        }

        $table->replace($record, $override);

        $last_record=$record;
    }

    $reader->close();

    apiutil::write_api_table($table->as_hash());
}

#
# Calculate the coverage metrix
# write both in the api_table.xml & api_metrix.xml
#
sub summarize{
    my $reader = XMLReader->new(util::get_root_path."/output/api_table.xml");

    my @res=();
    my($func_cover, $branch_cover) = (FuncCoverData->new(), BranchCoverData->new());
    my($api_func_cover, $api_branch_cover) = (FuncCoverData->new(), BranchCoverData->new());
    my($total_func_cover, $total_branch_cover) = (FuncCoverData->new(), BranchCoverData->new());

    while( my %item=$reader->read_block(APIData->tag_name()) ){
        my $api_item=APIData->copy(%item);

        my $summary=0;

        #file scope summary
        if($api_item->function() =~ /----/){
            $api_item->set_data(0, $branch_cover->denominator(),
                0, $branch_cover->coverage(),
                $func_cover->denominator(), $func_cover->coverage(), 0);
            $func_cover->reset();
            $branch_cover->reset();
            $summary=1;
        }

        #api scope summary
        if($api_item->filename() =~ /----/){
            $api_item->set_data(0, $api_branch_cover->denominator(),
                0, $api_branch_cover->coverage(),
                $api_func_cover->denominator(), $api_func_cover->coverage(), $api_func_cover->numerator());
            $api_func_cover->reset();
            $api_branch_cover->reset();
            $summary=1;
        }

        #total summary
        if($api_item->name() =~ /----/){
            $api_item->set_data(0, $total_branch_cover->denominator(),
                0, $total_branch_cover->coverage(),
                $total_func_cover->denominator(), $total_func_cover->coverage(), $total_func_cover->numerator());
            $summary=1;
        }

        if($summary == 0){
            $func_cover->add_data($api_item);
            $branch_cover->add_data($api_item);
            $api_func_cover->add_data($api_item);
            $api_branch_cover->add_data($api_item);
            $total_func_cover->add_data($api_item);
            $total_branch_cover->add_data($api_item);
        }

        push @res, $api_item;
    }

    $reader->close();

    my $writer = XMLWriter->new($reader->filename)->push_field("APITABLE");
    foreach my $api_item(@res){
        $writer->write_block($api_item->as_xml());
    }

    $writer->close();
}

1;
