#include "TuringParser/File.h"

#include <algorithm>
namespace OTParser {
    SourceFile::SourceFile(const std::string &data) : Data(data) {
        // build the line cache
        LineCache.push_back(0);
        const char *Buf = Data.c_str();
        unsigned Offs = 0;
        while (1) {
            const char *NextBuf = Buf;
            while (*NextBuf != '\n' && *NextBuf != '\r' && *NextBuf != '\0')
                ++NextBuf;
            Offs += NextBuf-Buf;
            Buf = NextBuf;
            
            if (Buf[0] == '\n' || Buf[0] == '\r') {
                // If this is \n\r or \r\n, skip both characters.
                if ((Buf[1] == '\n' || Buf[1] == '\r') && Buf[0] != Buf[1])
                    ++Offs, ++Buf;
                ++Offs, ++Buf;
                LineCache.push_back(Offs);
            } else {
                // Otherwise, this is a null.  And we are done.
                break;
            }
        }
    }
    unsigned int SourceFile::getLine(unsigned int index) {
        // binary search the line cache to find the correct line
        std::vector<unsigned int>::iterator line;
        line = std::lower_bound(LineCache.begin(), LineCache.end(), index+1);
        size_t pos = line - LineCache.begin(); // get position of line iterator
        return pos;
    }
    unsigned int SourceFile::getColumn(unsigned int index) {
        unsigned LineStart = index;
        while (LineStart && Data[LineStart-1] != '\n' && Data[LineStart-1] != '\r')
            --LineStart;
        return index-LineStart+1;
    }
}