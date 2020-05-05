#include "SoLoudCommonUtility.h"

namespace ToyRenderer {

	std::string soLoudErrorToString(int id)
	{
		switch (id) {
		case 0: return "SO_NO_ERROR"      ;     // No error
		case 1: return "INVALID_PARAMETER";	    // Some parameter is invalid
		case 2: return "FILE_NOT_FOUND"   ;	    // File not found
		case 3: return "FILE_LOAD_FAILED" ;	    // File found, but could not be loaded
		case 4: return "DLL_NOT_FOUND"    ;		// DLL not found, or wrong DLL
		case 5: return "OUT_OF_MEMORY"    ;		// Out of memory
		case 6: return "NOT_IMPLEMENTED"  ;	    // Feature not implemented
		case 7: return "UNKNOWN_ERROR"    ;		// Other error
		default:return "UNKNOWN_ERROR ID" ;
		};
	}
}