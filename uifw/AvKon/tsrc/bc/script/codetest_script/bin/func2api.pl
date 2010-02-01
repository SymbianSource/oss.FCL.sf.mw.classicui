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
# by Liu Xinyu
# April, 2006
#

use strict;
use warnings;
use Cwd;
use FindBin;
use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

use lib "$FindBin::Bin";

use util;
use apiutil;

&main();

sub main{
    &prepare_output();

    foreach my $i(1..3){
        my @res = &map_func2api(&build_dict($i));
        &write_result(@res);
    }
}

sub build_dict{
    my ($sheet_id)=@_;

    my $root_path = util::get_root_path();
    my $src_file="$root_path/conf/SDK_method_usage2_filtered.xls";

    $Win32::OLE::Warn = 3;
    sleep(1);
    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open($src_file);
    print STDERR "building api dictionary...\n";

    my @dict=();
    my @sheet_item_num=(5700, 4100, 2400);
    my $Sheet = $Book->Worksheets($sheet_id);

    foreach my $row (1..$sheet_item_num[$sheet_id-1]) {
        if(defined $Sheet->Cells($row,1)->{'Value'}){
            my $func_name=$Sheet->Cells($row,1)->{'Value'};
            util::progress_bar("sheet $sheet_id", int($row/$sheet_item_num[$sheet_id-1]*100));
            #print "$func_name\n";
            push(@dict, $sheet_id."#".$row."#".$func_name);
        }
        else{
            last;
        }
    }
    print STDERR "\n";

    $Book->Close;
    return @dict;
}

sub write_result{
    my (@res) = @_;
    my $dest_file=util::get_root_path()."/output/SDK_method_usage2_filtered.xls";

    $Win32::OLE::Warn = 3;
    sleep(1);
    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open($dest_file);

    my @sheets=($Book->Worksheets(1), $Book->Worksheets(2), $Book->Worksheets(3));
    my $i=0;
    foreach my $item(@res){
        my ($sheet_num, $row, $func, $header, $api)=split(/#/, $item);

        $sheets[$sheet_num-1]->Cells($row, 5)->{'Value'}=$header;
        $sheets[$sheet_num-1]->Cells($row, 6)->{'Value'}=$api;

        util::progress_bar("sheet $sheet_num: $row", int($i/$#res*100));
        $i++;
    }
    print STDERR "\ntotal $i filled\n";
    $Book->Save;
    $Book->Close;
}

sub prepare_output{
    my $root_path = util::get_root_path();
    my $src_file="$root_path/conf/SDK_method_usage2_filtered.xls";
    my $dest_location = "$root_path/output";
    my $cmd = "copy /y ".&unix2win($src_file)." ".&unix2win($dest_location);
    print "$cmd\n";
    system($cmd) == 0 || die "error occured.\n";
}

sub map_func2api{
    my (@dict) = @_;
    my $root_path=util::get_root_path();
    my $api_table = "$root_path/conf/Public_API.xls";

    $Win32::OLE::Warn = 3;
    sleep(1);
    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open(util::unix2win($api_table));
    print STDERR "mapping func 2 api...\n";

    my $Sheet = $Book->Worksheets(2);
    my $found=0;
    my @res=();
    foreach my $row(1..5300){
        if(defined $Sheet->Cells($row,1)->{'Value'}){
            my $api_name=$Sheet->Cells($row,1)->{'Value'};
            my $header_file = $Sheet->Cells($row,2)->{'Value'};
            my $func_name = $Sheet->Cells($row,3)->{'Value'};

            next if $func_name eq "";

            foreach my $item(@dict){
                if(index($item, $func_name)>0){
                    push(@res, $item."#".$header_file."#".$api_name."#");
                    #util::log_file($item."#".$header_file."#".$api_name."#\n");
                    util::progress_bar("F", int($row/5300*100));
                    $found++;
                    last;
                }
            }
        }
        else{
            last;
        }
    }
    print STDERR "\ntotal $found apis found\n";
    $Book->Close;

    return @res;
}

