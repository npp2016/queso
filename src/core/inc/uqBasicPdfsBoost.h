//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// QUESO - a library to support the Quantification of Uncertainty
// for Estimation, Simulation and Optimization
//
// Copyright (C) 2008,2009,2010,2011,2012,2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, 
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
// 
// $Id$
//
//--------------------------------------------------------------------------

#ifndef __UQ_BASIC_PDFS_BOOST_H__
#define __UQ_BASIC_PDFS_BOOST_H__

#include <uqBasicPdfsBase.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp> 

class uqBasicPdfsBoostClass : public uqBasicPdfsBaseClass
{
public:
  uqBasicPdfsBoostClass();
  uqBasicPdfsBoostClass(int worldRank);
 ~uqBasicPdfsBoostClass();

  double betaPdfActualValue (double x, double alpha, double beta) const;
  double gammaPdfActualValue(double x, double a,     double b   ) const;
	
private:  
};

#endif // __UQ_BASIC_PDFS_BOOST_H__
