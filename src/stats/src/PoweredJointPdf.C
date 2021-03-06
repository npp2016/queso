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

#include <queso/PoweredJointPdf.h>
#include <queso/GslVector.h>
#include <queso/GslMatrix.h>

namespace QUESO {

// Constructor -------------------------------------
template<class V,class M>
PoweredJointPdf<V,M>::PoweredJointPdf(
  const char*                     prefix,
  const BaseJointPdf<V,M>& srcDensity,
        double                    exponent)
  :
  BaseJointPdf<V,M>(((std::string)(prefix)+"pow").c_str(),srcDensity.domainSet()),
  m_srcDensity            (srcDensity),
  m_exponent              (exponent)
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Entering PoweredJointPdf<V,M>::constructor()"
                            << ": prefix = " << m_prefix
                            << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "In PoweredJointPdf<V,M>::constructor()"
                          //<< ", prefix = "     << m_prefix
                            << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Leaving PoweredJointPdf<V,M>::constructor()"
                            << ": prefix = " << m_prefix
                            << std::endl;
  }
}
// Destructor --------------------------------------
template<class V,class M>
PoweredJointPdf<V,M>::~PoweredJointPdf()
{
}
// Math methods-------------------------------------
template<class V,class M>
void
PoweredJointPdf<V,M>::setNormalizationStyle(unsigned int value) const
{
  m_srcDensity.setNormalizationStyle(value);
  return;
}
//--------------------------------------------------
template<class V, class M>
double
PoweredJointPdf<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Entering PoweredJointPdf<V,M>::actualValue()"
                            << ": domainVector = " << domainVector
                            << std::endl;
  }

  UQ_FATAL_TEST_MACRO(domainVector.sizeLocal() != this->m_domainSet.vectorSpace().dimLocal(),
                      m_env.worldRank(),
                      "PoweredJointPdf<V,M>::actualValue()",
                      "invalid input");

  double value = m_srcDensity.actualValue(domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);

  UQ_FATAL_TEST_MACRO((domainDirection || gradVector || hessianMatrix || hessianEffect),
                      m_env.worldRank(),
                      "PoweredJointPdf<V,M>::actualValue()",
                      "incomplete code for domainDirection, gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = pow(value,m_exponent);
  returnValue *= exp(m_logOfNormalizationFactor); // [PDF-08] ???

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Leaving PoweredJointPdf<V,M>::actualValue()"
                            << ": domainVector = " << domainVector
                            << ", returnValue = "  << returnValue
                            << std::endl;
  }

  return returnValue;
}
//--------------------------------------------------
template<class V, class M>
double
PoweredJointPdf<V,M>::lnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Entering PoweredJointPdf<V,M>::lnValue()"
                            << ": domainVector = " << domainVector
                            << std::endl;
  }

  double value = m_srcDensity.lnValue(domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);

  UQ_FATAL_TEST_MACRO((domainDirection || gradVector || hessianMatrix || hessianEffect),
                      m_env.worldRank(),
                      "PoweredJointPdf<V,M>::lnValue()",
                      "incomplete code for domainDirection, gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = m_exponent*value;
  returnValue += m_logOfNormalizationFactor; // [PDF-08] ???

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 54)) {
    *m_env.subDisplayFile() << "Leaving PoweredJointPdf<V,M>::lnValue()"
                            << ": domainVector = " << domainVector
                            << ", returnValue = "  << returnValue
                            << std::endl;
  }

  return returnValue;
}
//--------------------------------------------------
template<class V, class M>
double
PoweredJointPdf<V,M>::computeLogOfNormalizationFactor(unsigned int numSamples, bool updateFactorInternally) const
{
  double value = 0.;

  double volume = m_domainSet.volume();
  if (((boost::math::isnan)(volume)) ||
      (volume == -INFINITY         ) ||
      (volume ==  INFINITY         ) ||
      (volume <= 0.                )) {
    // Do nothing
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "PoweredJointPdf<V,M>::lnValue()",
                        "incomplete code for computeLogOfNormalizationFactor()");
  }

  return value;
}

}  // End namespace QUESO

template class QUESO::PoweredJointPdf<QUESO::GslVector, QUESO::GslMatrix>;
