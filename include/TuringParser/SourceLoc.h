#ifndef _TuringParser_SourceLoc_H_
#define _TuringParser_SourceLoc_H_

namespace TuringParser {
    class SourceFile;
	struct SourceLoc {
		SourceLoc() : Index(0) {}
		SourceLoc(SourceFile *f, int index) : Index(index), File(f) {}
		bool isValid() {return Index >= 0;}
		unsigned int getLine();
        unsigned int getColumn();
        SourceLoc advance(int chars) {
            return SourceLoc(File,Index+chars);
        }
                             
		
		int Index;
        SourceFile *File;
	};
	struct SourceRange {
        SourceRange() {}
		SourceRange(SourceLoc begin, SourceLoc end) : Begin(begin), End(end) {}
		bool isValid() {return Begin.isValid() && End.isValid();}
		SourceLoc Begin;
		SourceLoc End;
	};
}

#endif