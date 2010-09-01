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

use strict;
use FindBin;
use lib "$FindBin::Bin";

use apidata;
use xmlwriter;
use xmlreader;
use FuncCoverData;
use BranchCoverData;
use util;
use APIFileDict;
use apiutil;
use APITable;
use hparser;

&main();

sub main{
    #&test_APIData();
    #&test_XMLWriter();
    #&test_XMLReader();
    #&test_CoverData();
    #&test_Regex();
    #&test_APIFileDict();
    #&test_ReformAPITable();
    #&test_APITable();
    #&test_Override();
    &test_HParser();
}

sub test_HParser{
    my $filename = "aknsfld.h";
    my @api=hparser::parse_file($filename);
    foreach my $item(@api){
        print $item."\n";
    }
}

sub test_Override{
    my $prefix = "#fasldfjiasd";
    my $case1 = "#File\@Class::method\@0\@0\@0\@0\@0\@0.00\@0";
    my $case2 =$prefix.$case1.$case1;
    $case1=$case2;

    my $search_regex = APIData->search_regex("Class::method", 1);
    print "search regex: $search_regex\n";

    print "before: $case1\n";
    if($case1 =~ /$search_regex/){
        my $same_part = $1;
        my @data= ($2, $3, $4, $5, $6, $7);

        foreach my $i(0..5){
            $data[$i]++;
        }

        my $replace_regex = $same_part."\@".join("\@",
                @data, 1 );
        print "replace regex: $replace_regex\n";

        $case1 =~ s/$search_regex/$replace_regex/;
    }
    print "after : $case1\n";
}

sub test_APITable{
    my %hash=APITable->new()->as_hash();
    my $key="";
    foreach $key (keys %hash){
        print "API: $key\n";
        print $hash{$key}."\n";
    }
}

sub test_ReformAPITable{
    apiutil::reform_api_table();
}

sub test_APIFileDict{
    my $dict = APIFileDict->new();

    #$dict->add_api("API 1", "file1#file2#file3");
    #$dict->add_api("API 2", "file1#file2#file3");
    #$dict->add_api("API 3", "file1#file2#file3");
    #$dict->add_api("API 4", "file1#file2#file3");

    my %hash = $dict->as_hash();
    foreach my $key (keys %hash){
        #print "$key ==> ".$hash{$key}."\n";
    print "$key ==> \n";
    }
    my $case="AknCommonDialogs.h";
    print "AIP name of $case is ".$dict->find($case)."\n";
}

sub test_Regex{
    my @testcases=();
    push @testcases, my $case1="class::func";
    push @testcases, my $case1="class::operator++";
    push @testcases, my $case2="class::operator()";
    push @testcases, my $case3="class::operator*";
    push @testcases, my $case4="class::operator/";
    push @testcases, my $case5="class::operator&";
    push @testcases, my $case6="class::operator[]";
    push @testcases, my $case7="class::operator=";
    push @testcases, my $case8="class::operator==";
    push @testcases, my $case8="class::operator-";
    my $postfix="\@1\@2\@3";

    foreach my $case (@testcases){
        my $regex = util::plain_regex($case);
        my $str   = $case.$postfix;
        print $str;

        if($str =~ /$regex\@(\d+)\@(\d+)\@(\d+)/){
            print "==>";
            $str =~ s/$regex\@(\d+)\@(\d+)\@(\d+)/$case\@9\@9\@9/;
            print $str."\n";
        }
    }
}

sub test_XMLWriter{
    my $writer=XMLWriter->new("L:\\foo.xml")->push_field("OUT");
    $writer->push_field("MYData");
    $writer->write_block("BName", ("name"=>"tom", "sex"=>"male", "age"=>29));
    $writer->write_block("BName", ("name"=>"Alice", "sex"=>"female", "age"=>5));
    $writer->close();
}

sub test_XMLReader{
    my $reader=XMLReader->new("L:\\foo.xml");
    while(my %hash=$reader->read_block("BName")){
        &print_api(%hash);
    }
}

sub test_CoverData{
    my $func_cover  =FuncCoverData->new();
    my $branch_cover=BranchCoverData->new();

    my $data = APIData->new("API name", "header.h", "func()", 0,4,0,0.75,0,1,0);
    $func_cover->add_data($data);
    $branch_cover->add_data($data);
    $data = APIData->new("API name", "header.h", "func()", 0,4,0,0,0,0,0);
    $func_cover->add_data($data);
    $branch_cover->add_data($data);
    print "func cover =".$func_cover->as_string()."\n";
    print "branch cover =".$branch_cover->as_string()."\n";
}

sub test_APIData{
    my @testcase=();
    push @testcase, APIData->new();
    push @testcase, APIData->new("only name");
    push @testcase, APIData->new("API Name", "header");
    push @testcase, APIData->new('NONAME', 'foo.h', 'func');
    push @testcase, APIData->new("API name", "header.h", "func()", 1,2,3,4,5,6,7);

    my $case5 = APIData->new('case 5', 'foo.h', 'func');
    my @data=(1,1,1,4,5,6,7);
    $case5->set_data(@data);
    push @testcase, $case5;

    push @testcase, APIData->copy($case5->as_hash);

    foreach my $item (@testcase){
        &print_api( $item->as_hash );
    }
}

sub print_api{
    my (%hash)=@_;
    print "=======================>\n";
    for my $key (keys %hash){
        print "$key = ".$hash{$key}."\n";
    }
}

