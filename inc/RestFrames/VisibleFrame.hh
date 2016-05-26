/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2016, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   VisibleFrame.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2015 Jan
///
//   This file is part of RestFrames.
//
//   RestFrames is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   RestFrames is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with RestFrames. If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#ifndef VisibleFrame_HH
#define VisibleFrame_HH

#include "RestFrames/RestFrame.hh"

namespace RestFrames {

  class RestFrame;

  ///////////////////////////////////////////////
  // VisibleFrame class
  ///////////////////////////////////////////////
  template <class T>
  class VisibleFrame : public T {
  public:
    //constructor and destructor
    VisibleFrame(const std::string& sname, const std::string& stitle);
    VisibleFrame();
    virtual ~VisibleFrame();

    virtual void SetLabFrameFourVector(const TLorentzVector& V);
    virtual TLorentzVector GetLabFrameFourVector() const;

  protected:
    virtual bool IsSoundBody() const;

  private:
    TLorentzVector m_Lab_P;

  };

}

#endif
