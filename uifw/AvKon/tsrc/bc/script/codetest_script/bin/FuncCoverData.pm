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

package FuncCoverData;
use strict;
use vars qw(@ISA);

use lib "$FindBin::Bin";
use apidata;
use coverdata;

@ISA = ("CoverData");

# overriden function here
sub add_data{
    my ($self, $apidata)=@_;
    $self->{'NUMERATOR'} += $apidata->func_cover();
    $self->{'DENOMINATOR'} ++ ;
}

1;
