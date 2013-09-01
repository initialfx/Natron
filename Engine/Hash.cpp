//  Powiter
//
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/*
*Created by Alexandre GAUTHIER-FOICHAT on 6/1/2012. 
*contact: immarespond at gmail dot com
*
*/

#include "Hash.h"

#if 0
#include <cstdlib> // for malloc(), free()
#else
#include <algorithm>  // for std::for_each
#endif
#ifndef Q_MOC_RUN
#include <boost/crc.hpp>
#endif

#include "Engine/Node.h"
#include "Gui/Knob.h"

using namespace Powiter;

void Hash::computeHash() {
#if 0
    // previous version
    boost::crc_optimal<64,0x42F0E1EBA9EA3693,0,0,false,false> result;
    U64* data=(U64*)malloc(sizeof(U64)*node_values.size());

    for(U32 i=0;i<node_values.size();++i) {
        data[i]=node_values[i];
    }
    result.process_bytes(data,node_values.size()*sizeof(U64));
    hash=result.checksum();
    free(data);
#else
    const unsigned char* data = reinterpret_cast<const unsigned char*>(node_values.data());
    boost::crc_optimal<64,0x42F0E1EBA9EA3693,0,0,false,false> crc_64;
    crc_64 = std::for_each( data, data+node_values.size()*sizeof(node_values[0]), crc_64 );
    hash = crc_64();
#endif
}

void Hash::reset(){
    node_values.clear();
    hash=0;
}


void Hash::appendValueToHash(U64 hashValue){
        node_values.push_back(hashValue);
}

void Hash::appendKnobToHash(Knob* knob){
    std::vector<U64> values= knob->getValues();
    for(U32 i=0;i<values.size();++i) {
        node_values.push_back(values[i]);
    }
}

void Hash::appendQStringToHash(const QString& str){
    for(int i =0 ; i< str.size();++i) {
        node_values.push_back((U64)str.at(i).unicode());
    }
}


