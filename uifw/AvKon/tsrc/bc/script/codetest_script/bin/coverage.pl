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
# coverage.pl
#

#use strict;
use warnings;
use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

print "invoking coverage processing...\n";

$xmlfile = $ARGV[0];
$deffile = $ARGV[1];
@def_headers=split(/[\/\\]/,$deffile);
$resfile = $def_headers[1].".result.xml";
$xlsfile = $ARGV[2];

#
# open the xml records
#
open XMLFILE, $xmlfile || die "can not open xmlfile: $xmlfile\n";
print "$xmlfile opened.\n";
@xmllines=<XMLFILE>;

#
# open the def file
#
open DEFFILE, $deffile || die "can not open deffile: $deffile\n";
print "$deffile opened.\n";
@deflines=<DEFFILE>;

#
# open the result file
#
open RESFILE, ">$resfile" || die "can not open deffile: $resfile\n";
print "$resfile opened.\n";
&write_header();

open LOGFILE, ">log.txt" || die "can not open log.\n";

$des_name	="";	# $des_name=$class_name::class_name::...::func_name
			# $class_name	="";
			# $func_name	="";
$file_name	="";
$coverage	=0;
$pass		=0;
$found = $count = $covered = $global = $inner = 0;

#
# 2005-11-18
# The following vars are used for count file-scope coverage
#
$last_file	="";
$cur_count	=0;
$cur_covered	=0;
%file_coverage  =();

foreach $line(@xmllines) {
	if($line =~ /<CoverageRec>/){

		#
		# begin a rec structure.
		#

		$pass = 0;
		$count++;
		next;
	}

	if($line =~ /<funcName>/){

		#
		# get class & function names
		#

		$pass = 1;
		$class_name = $func_name = $des_name = "";

		if($line =~ /\[([\~\w\(\):=\s]+)\]/){
			$des_name=$1;
		}
		@parts = split(/::/, $line);
		$n=@parts;
		if($n == 1){
			$global++;
		}
		elsif($n >2){
			$inner++;
		}

		#
		print LOGFILE "$des_name\n";
		######################################################
		#

		# search if the function name can be find in the *.def file
		if( &find_func($des_name) ){
			$pass = 0;	# found.
		}

		next;
	}

	
	if($line =~ /<fileName>/){
			
		#
		# get header file name
		#

		if((lc $line) =~ /\[(\w+)\.cpp\]/){
			$file_name= $1;
		}
		next;
	}

	if($line =~ /<coverage>/){

		#
		# get coverage 
		#

		if($line =~ /\[(\d+)\.(\d+)\]/){
			$coverage = $1.".".$2;
		}
		next;
	}

	if($line =~ /<\/CoverageRec>/){

		#
		# end of a rec structure.
		#

		if(not $pass){

			#
			# write this rec out
			#
			#
			$found++;
			&count_file_coverage();
			&write_rec($class_name, $func_name, $file_name, $coverage);
		}
	}
}

#
# 2005-11-21
# count the last file coverage
#

$file_name="";
&count_file_coverage();
&write_tailer();
&fill_out();
print "\n========================================\n";
print "$count functions processed.\n";
print "$found functions recorded.\n";
print "\t$covered functions covered.\n";
print "\t$global global functions.\n";
print "\t$inner inner class functions.\n";
print "finish.\n";
print "========================================\n";

#
# close files
#
close XMLFILE;
close DEFFILE;
close RESFILE;

sub write_header{
	print RESFILE "<?xml version=\"1.0\"?>\n";
	print RESFILE "<CoverageData>\n";
}

sub write_rec{
	# local($class_name, $func_name, $file_name, $coverage)=@_;

	#print $class_name."::$func_name\t\t..."."$coverage\n";

	print RESFILE "<CoverageRec>\n";
	print RESFILE "<funcName><![CDATA[$des_name]]></funcName>\n";
	print RESFILE "<fileName><![CDATA[$file_name.h]]></fileName>\n";
	if($coverage+0 > 0){
		print RESFILE "<coverage><![CDATA[1]]></coverage>\n";
		$covered++;
	}
	else {
		print RESFILE "<coverage><![CDATA[0]]></coverage>\n";
	}
	print RESFILE "</CoverageRec>\n";
}

sub write_tailer{
	print RESFILE "</CoverageData>\n";
}

sub count_file_coverage{
	#
	# count the local coverage
	#
	if( $last_file ne $file_name && $cur_count != 0 ){
		$file_coverage{lc "$last_file.h"} = $cur_covered/$cur_count;
		print RESFILE "<CoverageRec>\n";
		print RESFILE "<funcName><![CDATA[-------------------]]></funcName>\n";
		print RESFILE "<fileName><![CDATA[-------------------]]></fileName>\n";
		print RESFILE "<coverage><![CDATA[".$cur_covered/$cur_count."]]></coverage>\n";
		print RESFILE "</CoverageRec>\n";

		$cur_count = $cur_covered = 0;
	}
	$cur_count++;
	$cur_covered += ($coverage+0 >0);
	$last_file=$file_name;
}

sub find_func{
	# print "indexing @_[0]....\n";

	foreach $defline(@deflines){
		if(index($defline, $_[0]) >= 0){
			return 1;
		}
	}
	return 0;
}

sub fill_out{
	$Win32::OLE::Warn = 3;                                # die on errors...

	# get already active Excel application or open new
	my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');  

	# open Excel file
	my $Book = $Excel->Workbooks->Open($xlsfile); 

	# select worksheet number 2 (you can also select a worksheet by name)
	# my $Sheet = $Book->Worksheets(2);
	my $Sheet = $Book->Worksheets->{'Nokia'};

	# iterate the 3rd column...
	foreach my $row (1..1000) {
  		# skip empty cells
  		next unless defined $Sheet->Cells($row,3)->{'Value'};

		# skip the non-exist headers.
		my $header = lc $Sheet->Cells($row,3)->{'Value'};
		next unless defined $file_coverage{$header};

 		# fill out the contents of the cell  
		$value=0;
   		if(defined $Sheet->Cells($row,1)->{'Value'}){
			$value=$Sheet->Cells($row,1)->{'Value'};
			print "the cell[$row][1] for $header: have been filled as $value before.\n";
		}	
		if($file_coverage{$header} > $value){
   			$Sheet->Cells($row,1)->{'Value'} = $file_coverage{$header};        
		}
		# print $Sheet->Cells($row,3)->{'Value'}."\t".$Sheet->Cells($row,1)->{'Value'}."\n"; 
 	}

	$Book->Save;
	# clean up 
	$Book->Close;
}

#end

