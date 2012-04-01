#ifndef _TuringParser_File_H_
#define _TuringParser_File_H_

#include <string>
#include <vector>

namespace OTParser {
	//! Container of a file. Manages source locations
	class SourceFile {
        public:
        SourceFile(const std::string &data);
        //! gets the line number from a character index
        unsigned int getLine(unsigned int index);
        //! gets the column number from a character index
        unsigned int getColumn(unsigned int index);
        
        //! The contents of the file, must not be modified
        const std::string Data;
        private:
        //! an array of the character positions of all the line endings
        //! used to binary search line numbers using a character index
        std::vector<unsigned int> LineCache;
	};
}

#endif