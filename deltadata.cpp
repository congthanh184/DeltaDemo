#include "deltadata.h"

DeltaData::DeltaData() {

}

/*
  Du lieu vao la rBase va rEE, suy ra f/2 = rBase/tan30, tinh ra dc 2 dinh cua Base
  (song song voi Ox) va 1 nam tren 0y. Va tinh dc toa do cua 3 hip.
  */
DeltaData::DeltaData(float f, float e, float rBase, float rEE, float rf, float re){
    this->rf = rf;
    this->re = re;

    if ( f == 0 && e == 0) {
        this->rBase = rBase;
        this->rEE = rEE;

        baseVertex[0].Set( -rBase/tan30, -rBase, 0);
        baseVertex[1].Set(  rBase/tan30, -rBase, 0);
        baseVertex[2].Set( 0, rBase/sin30 , 0);
    }
    else {
        this->f = f;
        this->e = e;

    }

}
