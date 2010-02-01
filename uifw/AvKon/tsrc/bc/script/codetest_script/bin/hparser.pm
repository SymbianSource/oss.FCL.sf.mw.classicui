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

package hparser;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
    parse_file
);

use strict;
use warnings;
use Cwd;

sub parse_file{
    my($filename)=@_;

    return if(&filter($filename)==0);

    print "parse $filename\n";
    #system("pause");
    open HEADER_FILE, $filename || die "can not open $filename \n";
    my @lines=<HEADER_FILE>;
    close HEADER_FILE;

    @lines=&remove_comments(@lines);

    my @api=();
    for(my $i=0; $i<=$#lines; $i++){
        my $line=$lines[$i];
        my @sub_api=();

        if($line =~ /NONSHARABLE_CLASS\((.+)\)/){
            my $classname=$1;
            $line =~ s/(NONSHARABLE_CLASS\(.+\))/class $classname/;
            $lines[$i]=$line;
        }

        if($line =~ /class/){
            @sub_api=&parse_class($i, \@lines);
            $i=pop(@sub_api);
            push(@api, @sub_api);
        }
    }

    return @api;
}

sub parse_class{
    my($i, $line_ref)=@_;

    my $name="";
    my $bracket=0;
    my @api=();
    while($i<=@{$line_ref}){
        my $line=${$line_ref}[$i];

        #print ">$line";
        #system("pause");

        if($line =~ /class\s+([\w_]+)/){
            if($bracket==0){
                $name=$1;
                $line =~ s/(class\s+[\w_]+)//;  #eat it
                print "class $name\n";
            }
            else{
                print "an inner class\n";
                $i=&parse_class($i, $line_ref);
            }
        }

        ($line, $bracket)=&parse_bracket($line, $bracket);

        if($line =~ /;\w*/ && $bracket==0){
            print "class done.\n";
            #$i++;
            return (@api, $i);
        }

        ################################################
        if($line =~ /IMPORT_C/){
            my $func_name="";
            ($i, $func_name)=&parse_function($i, $line_ref, $name);
            push(@api, $func_name);
        }

        $i++;
    }
    print "unexpected class exit, i=$i\n";
    return (@api, $i);
}

sub parse_function{
    my($i, $line_ref, $classname)=@_;

    my $name="";
    my $bracket=0;
    while(1){
        my $line=${$line_ref}[$i];
        until($line =~ /;\w*/){
            $i++;
            $line=$line.${$line_ref}[$i];
        }

        #print ">$line";
        #system("pause");

        my @tokens=split(/\(/, $line);
        $name=$name.&last_words($tokens[0]);
        if(@tokens==1){
            #print "\ttoken =1, ";
        }
        elsif(@tokens==2){
            #found it!
            #print "\ttoken =2, ";
        }
        elsif(@tokens==3){
            #print "\ttoken =3, ";
            # special cases:
            # 1). operator()(args){};
            # 2). (*funcptr)(args){};
            $name=$name."(".shift(@tokens);
        }

        ($line, $bracket)=&parse_bracket($line, $bracket);

        if($line =~ /;\w*/ && $bracket==0){
            $name =~ s/\*//g;       # change *NewL ==> NewL
            my $func_name=$classname."::".$name;
            #print "$func_name...func done.\n";
            return($i, $func_name);
        }

        $i++;
    }
    die "unexpected function exit, i=$i\n";
}

sub last_words{
    my($line)=@_;

    my @list=split(/\s+/, $line);
    if(@list!=0){
        return $list[$#list];
    }
    return "";
}

sub parse_bracket{
    my($line, $bracket)=@_;

    if($line =~/\{/){
        $bracket++;
        #print "\t$bracket, \n";
        $line =~ s/\{//;    #eat it
    }

    if($line =~/\}/){
        $bracket--;
        #print "\t$bracket, ";
        $line =~ s/\}//;    #eat it
    }
    return ($line, $bracket);
}

sub filter{
    my($filename)=@_;
    return 1 if($filename =~ /\.h/);
    return 0;
}

sub remove_comments{
    my @lines = @_;
    my @res=();
    my $iscomments=0;
    foreach my $line(@lines){
        #
        # remove /*...*/
        #
        $line=~s/(\/\*.*\*\/)//g;

        #
        # remove // comments
        #
        $line=~s/(\/\/.*)//g;

        #
        # remove /*
        #         */
        #
        if($line =~ /\/\*/){
            $line =~s/(\/\*.*)//g;
            $iscomments=1;
        }
        if($line =~ /\*\//){
            $iscomments=0;
            $line =~s/(.*\*\/)//g;
        }
        if($iscomments ==1 ){
            next;
        }

        push(@res, $line);
    }
    return @res;
}

1;
