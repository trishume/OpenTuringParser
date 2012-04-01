include_directories (. ${QUEX_PATH} ${MAIN_INCLUDE_DIR})

set(ParserSources
	File.cpp
	ParseError.cpp
	SourceLoc.cpp
	ASTNode.cpp
	Token.cpp
	Lexer.cpp
	Parser.cpp
	TuringParser.cpp
	Main.cpp
	)

set(ParserHeaders
	${MAIN_INCLUDE_DIR}/TuringParser/ParseError.h
	${MAIN_INCLUDE_DIR}/TuringParser/ParseErrors.h
	${MAIN_INCLUDE_DIR}/TuringParser/File.h
	${MAIN_INCLUDE_DIR}/TuringParser/SourceLoc.h
	${MAIN_INCLUDE_DIR}/TuringParser/Token.h
	${MAIN_INCLUDE_DIR}/TuringParser/LexerTokens.h
	${MAIN_INCLUDE_DIR}/TuringParser/Lexer.h
	${MAIN_INCLUDE_DIR}/TuringParser/ASTNode.h
	${MAIN_INCLUDE_DIR}/TuringParser/ASTTokens.h
	${MAIN_INCLUDE_DIR}/TuringParser/Parser.h
	${MAIN_INCLUDE_DIR}/TuringParser/TuringParser.h
	)

# here so they can be edited in the xcode project
set(ParserExtras
	)

add_executable(TuringParser ${ParserSources} ${ParserHeaders} ${ParserExtras})

# install
set(PARSER_INSTALL_DIR ${INSTALL_DIR})
install(TARGETS TuringParser DESTINATION ${PARSER_INSTALL_DIR})
