#include "TuringParser/SourceLoc.h"

#include "TuringParser/File.h"

namespace TuringParser {
    unsigned int SourceLoc::getLine() {
        return File->getLine(Index);
    }
    unsigned int SourceLoc::getColumn() {
        return File->getColumn(Index);
    }
	
}