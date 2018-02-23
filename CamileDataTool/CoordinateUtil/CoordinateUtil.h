#ifndef _COORDINATE_UTIL_H_
#define _COORDINATE_UTIL_H_

typedef struct
{
	double lng;
	double lat;
}Location;

Location transformFromWGSToGCJ(Location wgLoc);
Location transformFromGCJToWGS(Location gcLoc);
Location bd_encrypt(Location gcLoc);
Location bd_decrypt(Location bdLoc);

#endif  // _COORDINATE_UTIL_H_