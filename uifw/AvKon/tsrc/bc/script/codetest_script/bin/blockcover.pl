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
# March, 2006
#

use strict;
use warnings;
use Cwd;
use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

&main();

sub main{
    my $root_path = &get_root_path();
    my @api_groups = &get_apis($root_path);

    # iterate all modules count the function coverage
    &iterate_modules($root_path, \@api_groups);

    &write_output($root_path, \@api_groups);
}

sub write_output(){
    my ($root_path, $group_ref) = @_;

    my $xml="$root_path/output/blockcover.xml";
    open XML_FILE, ">$xml" || die "can not open $xml.\n";
    print XML_FILE "<?xml version=\"1.0\"?>\n";
    print XML_FILE "<CoverageData>\n";

    foreach my $item(@{$group_ref}){
        my @list=split(/#/, $item);
        print XML_FILE "<CoverageRec>\n";
        my $api_name = $list[0];
        print "$api_name:\n\t";
        print XML_FILE "<APIName><![CDATA[$api_name]]></APIName>\n";
        my $blocks  = $list[$#list-1];
        my $covered = $list[$#list];
        print "$covered/$blocks=";
        print XML_FILE "<Blocks><![CDATA[$blocks]]></Blocks>\n";
        print XML_FILE "<CoveredNumber><![CDATA[$covered]]></CoveredNumber>\n";
        if($blocks >0){
            my $coverage=$covered/$blocks;
            print $coverage;
            print XML_FILE "<Coverage><![CDATA[$coverage]]></Coverage>\n";
        }
        else{
            print XML_FILE "<Coverage><![CDATA[0]]></Coverage>\n";
        }
        print "\n";
        print XML_FILE "</CoverageRec>\n";
    }
    print XML_FILE "</CoverageData>\n";
    close XML_FILE;
}

sub iterate_modules{
    my ($root_path, $group_ref) = @_;
    my $mod_path = "$root_path/modules";

    opendir MOD_DIR, "$mod_path" || die "can not open dir $mod_path.\n";
    my @dirs=();
    while(my $item=readdir(MOD_DIR)){
        push(@dirs, "$mod_path/$item");

    }
    closedir MOD_DIR;

    foreach my $dir(@dirs){
        &process_dir($dir, $group_ref);
    }
}

sub process_dir{
    my ($dir, $group_ref) = @_;

    opendir MOD_DIR, "$dir" || die "can not open dir $dir.\n";
    my @defs=();
    my @xmls=();
    while(my $filename=readdir(MOD_DIR)){
        if(lc($filename) =~ /\.def/){
            push(@defs, "$dir/$filename");
            next;
        }
        if(lc($filename) =~ /\.xml/){
            push(@xmls, "$dir/$filename");
            next;
        }
    }
    closedir MOD_DIR;

    foreach my $xml(@xmls){
        &count_coverage($xml, \@defs, $group_ref);
    }
}

sub count_coverage{
    my ($xml, $def_ref, $group_ref) = @_;
    print "count coverage for $xml\n";

    my $def_context="";
    foreach my $def(@{$def_ref}){
        open DEFFILE, $def || die "can not open deffile: $def\n";
        print "$def opened.\n";
        my @lines=<DEFFILE>;
        close DEFFILE;
        $def_context.=join("", @lines);
    }

    open XMLFILE, $xml || die "can not open xmlfile: $xml\n";
    print "$xml opened.\n";

    my $pass = 0;
    my $coverage = 0;
    my $blocks = 0;
    my $file_name = "";
    my $des_name = "";

    while( my $line=<XMLFILE>){
        if($line =~ /<CoverageRec>/){
            $pass = 0;
            next;
        }

        if($line =~ /<funcName>/){
            $pass = 1;
            #my $des_name = "";

            if($line =~ /\[([\~\w\(\):=\s]+)\]/){
                $des_name=$1;
            }
            # search if the function name can be find in the *.def file
            if( index($def_context, $des_name) >=0 ){
                $pass = 0;  # found.
            }

            next;
        }


        if($line =~ /<fileName>/){
            if((lc $line) =~ /\[(\w+)\.cpp\]/){
                $file_name= $1;
            }
            next;
        }

        if($line =~ /<coverage>/){
            if($line =~ /\[(\d+)\.(\d+)\]/){
                $coverage = $1.".".$2;
                $coverage = int($blocks*$coverage/100+0.4);
            }
            next;
        }

        if($line =~ /<blocks>/){
            if($line =~ /\[(\d+)\]/){
                $blocks = $1;
            }
            next;
        }

        if($line =~ /<\/CoverageRec>/){
            if(not $pass){
                &update_block_coverage_data($file_name, $blocks, $coverage, $group_ref);
            }
        }
    }
    close XMLFILE;
}

sub update_block_coverage_data{
    my ($filename, $blocks, $coverage, $group_ref) = @_;

    foreach my $group(@{$group_ref}){
        if(lc($group) =~ /#$filename#/){
            $group =~ /#(\d+)#(\d+)#/;
            my $block_number=$1;
            $block_number+=$blocks;
            my $covered = $2;
            $covered+=$coverage;
            $group =~ s/#(\d+)#(\d+)#/#$block_number#$covered#/;
            #last;      # because some header belongs to different API at the same time.
        }
    }
}

sub get_apis{
    my ($root_path) = @_;
    my $mod_path= "$root_path/conf/OriginalExcel";

    my @api_groups=();
    opendir MOD_DIR, "$mod_path" || die "can not open dir $mod_path.\n";
    while(my $filename=readdir(MOD_DIR)){
        if(lc($filename) =~ /\.xls/){
            my $mod_file = "$mod_path/$filename";
            push(@api_groups, &get_api_groups($mod_file));
            sleep(1);
        }
    }
    closedir MOD_DIR;
    return @api_groups;
}

sub get_api_groups{
    my ($filename)=@_;

    print "process file: $filename\n";

    $Win32::OLE::Warn = 3;

    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open($filename);
    my $Sheet = $Book->Worksheets->{'Nokia'};

    my @res=();
    my $group="";
    foreach my $row (2..1000) {
        if(defined $Sheet->Cells($row,2)->{'Value'}){

            my $api_name=&trim_string($Sheet->Cells($row,2)->{'Value'});
            if($api_name ne ""){
                if($group ne ""){
                    push(@res, "$group"."0#0#");    #the last 2 number is: #Functions, #CoveredFunctions
                }
                $group=$api_name;
                $group.="#";
                next;
            }
        }

        if(defined $Sheet->Cells($row,3)->{'Value'} ){
            my $mod_name = $Sheet->Cells($row,3)->{'Value'};
            $mod_name =~ s/(\.h)//i;
            $mod_name =~ s/(\.rh)//i;
            #some filename is as uiklaf\private\xxxx.h
            my @list=split(/\\/, $mod_name);
            $mod_name=$list[$#list];
            $group.="$mod_name#";
        }
    }
    $Book->Close;
    #push the last group
    push(@res, $group."0#0#");

    foreach my $item(@res){
        my @list=split(/#/, $item);
        print "api name: ". $list[0] . "\n";
        print "api mods: \n";
        for my $i(1..$#list){
            print "\t".$list[$i].".h\n";
        }
        print "\n";
    }

    return @res;
}

sub trim_string{
    my($string)=@_;
    my @list = split(/\s+/, $string);
    if(@list>0){
        return join(' ', @list);
    }
    return "";
}

sub get_root_path{
    my $path=cwd;
    $path =~ tr/\\/\//;
    $path =~ s/(\/bin.*)//ig;     #trim the right \Group or \Group\
    print "root path = $path\n";
    return $path;
}
