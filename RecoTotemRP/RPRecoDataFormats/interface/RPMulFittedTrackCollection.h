/****************************************************************************
* This module is directly copied from 
* RPRecoDataFormats/RPFittedTrackCollection and expanded to hold 
* multiple fitted tracks.
*   
* Original Authors:
*   Hubert Niewiadomski (Hubert.Niewiadomski@cern.ch)
* Secondary Authors:
*   Zhang Zhengkui (zhang.zhengkui.fin@gmail.com)
*
****************************************************************************/


#ifndef RecoTotemRP_RPRecoDataFormats_RPMulFittedTrackCollection_h
#define RecoTotemRP_RPRecoDataFormats_RPMulFittedTrackCollection_h


#include "RecoTotemRP/RPRecoDataFormats/interface/RPFittedTrack.h"

#include <vector>
#include <map>


class RPMulFittedTrackCollection : public std::map<unsigned int, std::vector<RPFittedTrack> >
{
};

class RPMulFittedTrackSetsCollection : public std::map<unsigned int, std::vector<std::vector<RPFittedTrack> > >
{
};


#endif
