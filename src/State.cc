/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   State.cc
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

#include "RestFrames/State.hh"
#include "RestFrames/RestFrame.hh"
#include "RestFrames/Jigsaw.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // State class
  ///////////////////////////////////////////////
  int State::m_class_key = 0;

  // constructor 
  State::State()
    : RFBase("State", "State") 
  {
    Init();
  }

  State::~State(){
    Clear();
  }

  void State::Init(){
    SetKey(GenKey());
    m_ParentJigsawPtr = nullptr;
    m_ChildJigsawPtr = nullptr;
    m_Log.SetSource("State");
  }

  void State::Clear(){
    m_ParentJigsawPtr = nullptr;
    m_ChildJigsawPtr = nullptr;
    m_P.SetPxPyPzE(0.,0.,0.,0.);
    m_Frames.Clear();
  }

  void State::ClearFrames(){
    m_Frames.Clear();
  }

  // State *State::Copy() const {
  //   State* statePtr = new State(m_Key);
  //   statePtr->SetParentJigsaw(m_ParentJigsawPtr);
  //   statePtr->SetChildJigsaw(m_ChildJigsawPtr);
  //   statePtr->SetFourVector(m_P);
  //   int N = GetNFrames();
  //   for(int i = 0; i < N; i++) statePtr->AddFrame(m_Frames.Get(i));
  //   return statePtr;
  // }

  int State::GenKey(){
    int newkey = m_class_key;
    m_class_key++;
    return newkey;
  }

  void State::Boost(const TVector3& B){
    m_P.Boost(B);
  }

  void State::AddFrame(RestFrame* framePtr){
    if(!framePtr) return;
    if(!framePtr->IsVisibleFrame() && !framePtr->IsInvisibleFrame()) return;
    m_Frames.Add(framePtr);
  }

  void State::AddFrame(RFList<RestFrame>* framesPtr){
    if(!framesPtr) return;
    int N = framesPtr->GetN();
    for(int i = 0; i < N; i++) AddFrame(framesPtr->Get(i));
  }

  bool State::IsFrame(const RestFrame* framePtr) const {
    if(!framePtr) return false;
    if(m_Frames.GetN() != 1) return false;
    return m_Frames.Get(0)->IsSame(framePtr);
  }

  bool State::IsFrames(const RFList<RestFrame>* framesPtr) const {
    if(!framesPtr) return false;
    return m_Frames.IsSame(framesPtr);
  }

  RFList<RestFrame>* State::GetFrames() const {
    return m_Frames.Copy();
  }

  RestFrame* State::GetFrame() const {
    if(m_Frames.GetN() != 1) return nullptr;
    return m_Frames.Get(0);
  }

  void State::SetFourVector(const TLorentzVector& V){
    m_P.SetVectM(V.Vect(),V.M());
  }

  TLorentzVector State::GetFourVector() const {
    TLorentzVector V;
    V.SetVectM(m_P.Vect(),m_P.M());
    return V;
  }

  void State::FillGroupJigsawDependancies(RFList<Jigsaw>* jigsawsPtr) const {
    if(!jigsawsPtr) return;
    if(m_ParentJigsawPtr) m_ParentJigsawPtr->FillGroupJigsawDependancies(jigsawsPtr);
  }

  void State::FillStateJigsawDependancies(RFList<Jigsaw>* jigsawsPtr) const {
    if(!jigsawsPtr) return;
    if(m_ParentJigsawPtr) m_ParentJigsawPtr->FillStateJigsawDependancies(jigsawsPtr);
  }

}
