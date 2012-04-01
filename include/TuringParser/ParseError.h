#ifndef _TuringParser_ParseError_H_
#define _TuringParser_ParseError_H_

#include <string>
#include <vector>

#include "TuringParser/SourceLoc.h"

namespace OTParser {
	/* LICENSE NOTE: 
		The FixItHint class is copied (with modifications) from the Clang compiler source.
		It is released under the University of Illinois Open Source License.
	*/
	//! \brief Annotates a diagnostic with some code that should be
	//! inserted, removed, or replaced to fix the problem.
	//!
	//! This kind of hint should be used when we are certain that the
	//! introduction, removal, or modification of a particular (small!)
	//! amount of code will correct a compilation error. The compiler
	//! should also provide full recovery from such errors, such that
	//! suppressing the diagnostic output can still result in successful
	//! compilation.
	class FixItHint {
	public:
	  //! \brief Code that should be replaced to correct the error. Empty for an
	  //! insertion hint.
	  SourceRange RemoveRange;

	  //! \brief Code in the specific range that should be inserted in the insertion
	  //! location.
	  SourceRange InsertFromRange;

	  //! \brief The actual code to insert at the insertion location, as a
	  //! string.
	  std::string CodeToInsert;

	  bool BeforePreviousInsertions;

	  //! \brief Empty code modification hint, indicating that no code
	  //! modification is known.
	  FixItHint() : BeforePreviousInsertions(false) { }

	  bool isNull() {
	    return !RemoveRange.isValid();
	  }
	  
	  //! \brief Create a code modification hint that inserts the given
	  //! code string at a specific location.
	  static FixItHint CreateInsertion(SourceLoc InsertionLoc,
	                                   const std::string &Code,
	                                   bool BeforePreviousInsertions = false) {
	    FixItHint Hint;
	    Hint.RemoveRange = SourceRange(InsertionLoc, InsertionLoc);
	    Hint.CodeToInsert = Code;
	    Hint.BeforePreviousInsertions = BeforePreviousInsertions;
	    return Hint;
	  }
	  
	  //! \brief Create a code modification hint that inserts the given
	  //! code from \arg FromRange at a specific location.
	  static FixItHint CreateInsertionFromRange(SourceLoc InsertionLoc,
	                                            SourceRange FromRange,
	                                        	bool BeforePreviousInsertions = false) {
	    FixItHint Hint;
	    Hint.RemoveRange = SourceRange(InsertionLoc, InsertionLoc);
	    Hint.InsertFromRange = FromRange;
	    Hint.BeforePreviousInsertions = BeforePreviousInsertions;
	    return Hint;
	  }

	  //! \brief Create a code modification hint that removes the given
	  //! source range.
	  static FixItHint CreateRemoval(SourceRange RemoveRange) {
	    FixItHint Hint;
	    Hint.RemoveRange = RemoveRange;
	    return Hint;
	  }
	  
	  //! \brief Create a code modification hint that replaces the given
	  //! source range with the given code string.
	  static FixItHint CreateReplacement(SourceRange RemoveRange,
	                                     const std::string &Code) {
	    FixItHint Hint;
	    Hint.RemoveRange = RemoveRange;
	    Hint.CodeToInsert = Code;
	    return Hint;
	  }
	};
	//! Basic parser error struct
	class ParseError {
    public:
    	enum ErrType {
    		UNKNOWN // mostly exists so commas work
#define PARSE_ERROR(id,err) ,id
#include "TuringParser/ParseErrors.h"
#undef PARSE_ERROR
    	};
		ParseError(SourceLoc loc,ErrType type) :  Begin(loc), Type(type) {}
		//! Formats the error message from the components
		std::string getMessage();
		FixItHint getHint() const {return FixHint;}
		ErrType getType() const {return Type;}
		void setHint(FixItHint hint) {FixHint = hint;}
		void setEnd(SourceLoc end) {End = end;}
        
        //! Stream operator to add a string arg
        ParseError& operator<<(std::string arg);
        ParseError& operator<<(int arg);
        ParseError& operator<<(char arg);
        
        //! Location of the error. Must never be invalid.
		SourceLoc Begin;
		//! The end of the error range. may be invalid
		SourceLoc End;
	private:
		//! gets the format for a specific error type. 
		//! Components are referenced by %n starting at %0
		static std::string getFormatForType(ErrType type);
		//! The type of the error
		ErrType Type; 
		//! The formatting components to be inserted into the error string
		std::vector<std::string> Args;
		//! The FixItHint, if there is one. May be null. Use isNull to check.
		FixItHint FixHint;
	};
}

#endif