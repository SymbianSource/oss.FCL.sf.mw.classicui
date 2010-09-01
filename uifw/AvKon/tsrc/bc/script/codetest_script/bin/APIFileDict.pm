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

package APIFileDict;
use strict;
use vars qw(@ISA);

use Win32::OLE qw(in with);
use Win32::OLE::Const 'Microsoft Excel';

use lib "$FindBin::Bin";
use xmlwriter;
use xmlreader;
use util;

sub new{
    my ($class) = @_;

    my $self = bless {
        DICT =>undef,
        FILENAME => util::get_root_path."/output/api_dict.xml",
        BLOCKNAME => "DICTITEM",
        TABLENAME => "DICTTABLE"
    }, $class;

    return $self->read_dict();
}

sub build_dict{
    my $self =shift;
    my $mod_path= util::get_root_path."/conf/OriginalExcel";
    print "in build dict\n";

    opendir MOD_DIR, "$mod_path" || die "can not open dir $mod_path.\n";
    my $writer = XMLWriter->new($self->{FILENAME})->push_field($self->{TABLENAME});
    while(my $filename=readdir(MOD_DIR)){
        if(lc($filename) =~ /\.xls/){
            my %hash=$self->process_book("$mod_path/$filename");
            foreach my $name (keys %hash){
                $writer->write_block($self->{BLOCKNAME}, ("APINAME"=>$name, "FILENAME"=>$hash{$name}) );
            }
            sleep(1);
        }
    }
    $writer->close();
    closedir MOD_DIR;

    return $self;
}

sub process_book{
    my ($self, $filename)=@_;

    print "process file: $filename\n";

    $Win32::OLE::Warn = 3;

    my $Excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
    my $Book = $Excel->Workbooks->Open($filename);
    my $Sheet = $Book->Worksheets->{'Nokia'};

    my %res=();
    my $api_name = "";
    foreach my $row (2..1000) {
        if(defined $Sheet->Cells($row,2)->{'Value'}){
            my $name=util::trim_string($Sheet->Cells($row,2)->{'Value'});
            if($name ne ""){
                $api_name=$name;
                $res{$api_name}="#";
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
            $res{$api_name}.="$mod_name#" if( $api_name ne "");
        }
    }
    $Book->Close;

    return %res;
}

#
# read the dict from XML file
#
sub read_dict{
    my $self = shift;

    if(-e $self->{FILENAME}){
        print $self->{FILENAME}." exist.\n";
        my $reader = XMLReader->new($self->{FILENAME});
        while( my %item=$reader->read_block($self->{BLOCKNAME}) ){
            my $api_name  = $item{"APINAME"};
            my $file_name = $item{"FILENAME"};
            $self->add_api($api_name, $file_name) if((defined $api_name) && (defined $file_name));
        }
        $reader->close();
    }
    else{
        print $self->{FILENAME}." doesn't exist. build it.\n";
        $self->build_dict()->read_dict();
    }
    return $self;
}

sub as_hash{
    my $self = shift;
    return %{$self->{DICT}};
}

sub add_api{
    my ($self, $name, $value)=@_;
    $self->{DICT}->{$name}=$value;
    return $self;
}

sub find{
    my ($self, $filename)=@_;

    $filename =~ s/(\.h)//i;
    $filename =~ s/(\.rh)//i;
    $filename =~ s/(\.rsg)//i;
    $filename =~ s/(\.hrh)//i;
    $filename = lc($filename);

    foreach my $name (keys %{$self->{DICT}}){
        return $name if(lc($self->{DICT}->{$name}) =~ /#$filename#/);
    }
    return "";
}

1;
