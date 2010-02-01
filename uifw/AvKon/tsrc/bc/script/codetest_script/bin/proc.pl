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

# use strict;
use warnings;
use Cwd;
use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

my $cur_dir = cwd;  # while $0 is the $cur_dir/cover.pl
my @sub_dir_list=();
my $res_file="$cur_dir/output.xls";

$Win32::OLE::Warn = 3;
my $excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
my $book = $excel->Workbooks->Open($res_file);
$sheet = $book->Worksheets(1);
#&write_header($sheet);
$i=4;

opendir DIR, "$cur_dir" || die "can not open dir $cur_dir.\n";
while(my $item_name=readdir(DIR)){
    if(lc($item_name) =~ /\./){
        next;
    }
    else{
        @sub_dir_list=(@sub_dir_list, $item_name);
    }
}
closedir(DIR);

foreach my $dirname(@sub_dir_list){
    &proc_dir("$cur_dir/$dirname");
}

$book->Save;
$book->Close;
print "done.\n";

#############################################################
sub proc_dir{
    my $dirname   = $_[0];
    print "process $dirname...\n";

    my @def_list=();
    my @xml_list=();

    opendir SUBDIR, "$dirname" || die "can not open sub dir $dirname.\n";
    while(my $item = readdir(SUBDIR)){
        if(lc($item) =~ /\.def/){
            @def_list=(@def_list, $item);
            next;
        }
        if(lc($item) =~ /\.xml/){
            @xml_list=(@xml_list, $item);
            next;
        }
    }
    closedir(SUBDIR);

    foreach my $xml_file(@xml_list){
        foreach my $def_file(@def_list){
            &proc_data("$dirname/$xml_file", "$dirname/$def_file");
        }
    }

    print "...OK\n";
}

sub proc_data{
    my $xml_file = $_[0];
    my $def_file = $_[1];
    print "\tproc $xml_file and $def_file...\n";

    open XMLFILE, $xml_file || die "can not open xmlfile: $xml_file\n";
    my @xmllines=<XMLFILE>;
    close XMLFILE;

    open DEFFILE, $def_file || die "can not open deffile: $def_file\n";
    my @deflines=<DEFFILE>;
    close DEFFILE;

    my $pass  =0;
    my $file_name = my $func_name = "";
    my $coverage  = my $blocks = 0;
    my $sum_blocks = my $sum_covered_blocks = 0;

    foreach my $line(@xmllines) {
        if($line =~ /<CoverageRec>/){
            # begin a rec structure.
            $pass = 0;
            next;
        }

        if($line =~ /<funcName>/){
            # get Class::Function()
            $pass = 1;

            if($line =~ /\[([\~\w\(\):=\s]+)\]/){
                $func_name=$1;
            }

            # search if the function name can be find in the *.def file
            foreach my $defline(@deflines){
                if(index($defline, $func_name) >= 0){
                    $pass = 0;  #found
                    last;
                }
            }
            next;
        }

        if((not $pass) && $line =~ /<fileName>/){
            # get header file name
            if((lc $line) =~ /\[([\w\.]+)\]/){
                if( $file_name ne $1 && $file_name ne ""){
                    #filename change, count the file scope covage now;
                    &write_file_coverage($sum_blocks, $sum_covered_blocks);
                    $sum_blocks = $sum_covered_blocks = 0;
                }
                $file_name= $1;
            }
            next;
        }

        if((not $pass) && $line =~ /<blocks>/){
            # get blocks
            if($line =~ /\[(\d+)\]/){
                $blocks = $1;
                $sum_blocks += $blocks
            }
            next;
        }

        if((not $pass) && $line =~ /<coverage>/){
            # get coverage
            if($line =~ /\[(\d+)\.(\d+)\]/){
                $coverage = $1.".".$2;
                $sum_covered_blocks += $blocks*($coverage)/100;
            }
            next;
        }

        if((not $pass) && $line =~ /<\/CoverageRec>/){
            # write this rec out
            &write_rec($func_name, $file_name, $blocks, $coverage);
        }
    }
    if($sum_blocks != 0){
        &write_file_coverage($sum_blocks, $sum_covered_blocks);
    }

    print "\t...OK\n";
}

sub write_rec{
    my $func_name  = $_[0];
    my $file_name  = $_[1];
    my $blocks     = $_[2];
    my $coverage   = $_[3];
    $i++;

    $sheet->Cells($i,1)->{'Value'} = $func_name;
    $sheet->Cells($i,2)->{'Value'} = $file_name;
    $sheet->Cells($i,3)->{'Value'} = $blocks;
    $sheet->Cells($i,4)->{'Value'} = $coverage;
    $sheet->Cells($i,5)->{'Value'} = $blocks*$coverage/100;
}

sub write_file_coverage{
    my $sum_blocks = $_[0];
    my $sum_covered_blocks = $_[1];
    $i++;

    $sheet->Cells($i,3)->{'Value'} = $sum_blocks;
    $sheet->Cells($i,5)->{'Value'} = $sum_covered_blocks;
    $sheet->Cells($i,6)->{'Value'} = $sum_covered_blocks / $sum_blocks;
}

sub write_header{
    my $sheet = $_[0];

    $sheet->Cells(1,1)->{'Value'} = "funcName";
    $sheet->Cells(1,2)->{'Value'} = "fileName";
    $sheet->Cells(1,3)->{'Value'} = "blocks";
    $sheet->Cells(1,4)->{'Value'} = "coverage(%)";
    $sheet->Cells(1,5)->{'Value'} = "Covered Blocks";
    $sheet->Cells(1,6)->{'Value'} = "File Coverage";
}

# End of file.
