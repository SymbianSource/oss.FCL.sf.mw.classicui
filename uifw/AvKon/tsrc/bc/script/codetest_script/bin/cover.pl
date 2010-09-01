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
# June, 2006
#
# Calculate the coverage data from code test result and api table.
# If the api table doesn't exist, please run api_table first to
# genterate one.
#

use strict;
use warnings;
use Cwd;
use FindBin;

use lib "$FindBin::Bin";

use util;
use coverutil;

&main();

sub main(){
    my $api_group = &get_api_group();
    if($api_group ne ""){
        coverutil::process_api($api_group);
    }
    else{
        &process_all();
    }

    coverutil::summarize();
}

sub get_api_group{
    my $ARGC=@ARGV;

    if( $ARGC==0 ){
        return "";
    }

    if ($ARGC>1){
        &usage();
        exit;
    }

    return $ARGV[0];
}

sub process_all{
    my $module_path=util::get_root_path()."/modules";
    opendir DIR, "$module_path" || die "can not open $module_path\n";

    while(my $folder_name = readdir(DIR) ){
        next if $folder_name eq "." || $folder_name eq "..";
        coverutil::process_api("$module_path/$folder_name");
    }

    closedir(DIR);
}

sub usage{
    print "usage: run cover [work_dir]\n";
}
