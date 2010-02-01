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

package util;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
    trim_string
    get_root_path
    unix2win
    progress_bar
);

use strict;
use warnings;
use Cwd;

sub trim_string{
    my($string)=@_;
    my @list = split(/\s+/, $string);
    if(@list>0){
        return join(' ', @list);
    }
    return "";
}

sub get_root_path{
    my $path=Cwd::cwd;
    $path =~ tr/\\/\//;
    $path =~ s/(\/bin.*)//ig;     #trim the right \bin or \bin\
    #print "root path = $path\n";
    return $path;
}

sub unix2win{
    my ($path) = @_;
    $path =~ tr/\//\\/;
    return $path;
}

#
# @param $msg, the message show before the progress bar.
# @param $progress, the percentage range[1~100]
#
sub progress_bar{
    my($msg, $progress)=@_;
    print STDERR "[$msg: $progress"."\%]";
    foreach my $i(1..($progress/3)){
        print STDERR ".";
    }
    print STDERR "\r";
}

#
# change the special chars in a string to plain chars for regex
#
sub plain_regex{
    my($str)=@_;
    #$str =~ s/(\\)/(\\\\)/g;
    #$str =~ s/(\/)/(\\\/)/g;
    $str =~ s/(\+)/\\\+/g;
    $str =~ s/(\*)/\\\*/g;
    #$str =~ s/(\.)/(\\\.)/g;
    $str =~ s/(\[)/\\\[/g;
    $str =~ s/(\])/\\\]/g;
    $str =~ s/(\()/\\\(/g;
    $str =~ s/(\))/\\\)/g;

    return $str;
}

1;
