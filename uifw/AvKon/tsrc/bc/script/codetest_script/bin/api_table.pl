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
# build a API table by parsing the SDK header files.
#

use strict;
use warnings;
use Cwd;
use FindBin;
use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

use lib "$FindBin::Bin";

use util;
use hparser;
use Logger;
use APIFileDict;
use xmlwriter;
use ProgressBar;
use apidata;
use apiutil;

use File::stat;
use Fcntl ':mode';

&main();

#
# @param, command,
#   1: build, build api table from very beginning, it will process and parse all header files
#   2: clear, clear all things
#   3: reform, only for internal use, it will filtered NONAME API out, and insert seperators
#
sub main(){
    my $cmd = "";
    $cmd = shift @ARGV if @ARGV>0;

    if($cmd eq "reform"){
        apiutil::reform_api_table();
    }
    elsif($cmd eq "clean"){
        system(util::unix2win("del ".util::get_root_path()."/output/api_table.xml"));
        system(util::unix2win("del ".util::get_root_path()."/output/api_table.bak.xml"));
        system(util::unix2win("del ".util::get_root_path()."/output/api_dict.xml"));
    }
    else{
        &process_headers();
    }
}

sub process_headers{
    my $include_path = util::get_root_path()."/include";
    opendir  INC_ROOT, "$include_path" || die "can not open dir $include_path.\n";
    while(my $item=readdir(INC_ROOT)){
        next if $item eq "." || $item eq "..";
        $include_path.="/$item";
        last;
    }
    closedir INC_ROOT;

    &build_table(&process_dir($include_path));
    apiutil::reform_api_table();
}

#
# build api talbes, the table is in XML format. It contains:
# API name  | File name | Method name | #blocks | #branches |....
#

sub build_table{
    my (%api) = @_;
    my $dict = APIFileDict->new();
    my $api_number=(keys %api);
    my $progress_bar = ProgressBar->new($api_number);
    my $writer = XMLWriter->new(util::get_root_path."/output/api_table.xml")->push_field("APITABLE");

    foreach my $filename (keys %api){
        my $api_name = $dict->find($filename);
        my @functions=split(/#/, $api{$filename});
        foreach my $function (@functions){
            $writer->write_block(APIData->new($api_name, $filename, $function)->as_xml());
        }
        $progress_bar->increase();
    }

    $writer->close();
}

#
# recursively process dir,
# terminate when their is no sub dir,
# @return, %hash={filename=>func1#func2#...#funcN, filename=>...}
#

sub process_dir{
    my($dirname, $api_group_ref)=@_;

    print "process $dirname\n";

    my %res=();
    opendir my $INC_DIR, "$dirname" || die "can not open dir $dirname.\n";
    while(my $filename=readdir($INC_DIR)){
        next if $filename eq "." || $filename eq "..";
        if( -d "$dirname/$filename"){
            my %hash=&process_dir("$dirname/$filename");
            foreach my $key (keys %hash){
                $res{$key} = $hash{$key};
            }
        }
        else{
            Logger->new()->write("$dirname/$filename\n");
            my @api=hparser::parse_file("$dirname/$filename");
            $res{$filename}=join('#', @api) if (@api>0);
        }
    }
    closedir $INC_DIR;

    return %res;
}
