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

    my @sub_set1= &scan_dup(&build_dict(2));
    my @sub_set2= &scan_dup(&build_dict(3));

    &write_result(@sub_set1);
    &write_result(@sub_set2);
}

sub scan_dup{
    my(@sub_set)=@_;
    my @all_set = &build_dict(1);
    my @res=();
    foreach my $src(@sub_set){
        my ($src_id, $src_row, $src_func)=split(/#/, $src);
        foreach my $dest(@all_set){
            my($dest_id, $dest_row, $dest_func)=split(/#/, $dest);
            if($src_func eq $dest_func){
                push(@res, $src_id."#".$src_row."#");
                last;
            }
        }
        util::progress_bar("scan sheet $src_id", int($src_row/($#sub_set+1)*100));
    }
    my $dup_number=@res;
    print "\n$dup_number functions duplicated\n";
    return @res;
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
            util::progress_bar("build sheet $sheet_id", int($row/$sheet_item_num[$sheet_id-1]*100));
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
    my $dest_file=util::get_root_path()."/output/dup.xls";

    $Win32::OLE::Warn = 3;
    sleep(1);
    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open($dest_file);

    my @sheets=($Book->Worksheets(1), $Book->Worksheets(2), $Book->Worksheets(3));
    my $i=0;
    foreach my $item(@res){
        my ($sheet_num, $row)=split(/#/, $item);

        $sheets[$sheet_num-1]->Cells($row, 5)->{'Value'}="R";

        util::progress_bar("write sheet $sheet_num: $row", int($i/$#res*100));
        $i++;
    }
    print STDERR "\ntotal $i filled\n";
    $Book->Save;
    $Book->Close;
}

sub prepare_output{
    my $root_path = util::get_root_path();
    my $src_file="$root_path/conf/SDK_method_usage2_filtered.xls";
    my $dest_location = "$root_path/output/dup.xls";
    my $cmd = "copy /y ".&unix2win($src_file)." ".&unix2win($dest_location);
    print "$cmd\n";
    system($cmd) == 0 || die "error occured.\n";
}

