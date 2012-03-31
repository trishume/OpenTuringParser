//! All the lexer tokens. 
//! This header is included multiple times with a different TURING_TKN macro each time.

TURING_TKN(COMMA,comma)
TURING_TKN(COLON,colon)
TURING_TKN(BRACKET_O,opening parenthesis)
TURING_TKN(BRACKET_C,closing parenthesis)
TURING_TKN(SQUARE_BRACKET_O,opening square bracket)
TURING_TKN(SQUARE_BRACKET_C,closing square bracket)
TURING_TKN(CURLY_BRACKET_O,opening curly bracket)
TURING_TKN(CURLY_BRACKET_C,closing curly bracket)

TURING_TKN(IDENTIFIER,identifier)
TURING_TKN(INTLITERAL,int literal)
TURING_TKN(REALLITERAL,real literal)
TURING_TKN(STRINGLITERAL,string literal)
TURING_TKN(CHARLITERAL,character literal)

TURING_TKN(OP_NOT,'not' operator)
TURING_TKN(OP_PLUS,+ operator)
TURING_TKN(OP_MINUS,- operator)
TURING_TKN(OP_MULT,* operator)
TURING_TKN(OP_EXPONENT,** operator)
TURING_TKN(OP_DIVIDE,/ operator)
TURING_TKN(OP_DEREF,* operator)
TURING_TKN(OP_DIV,'div' operator)
TURING_TKN(OP_MOD,'mod' operator)
TURING_TKN(OP_REM,'rem' operator)
TURING_TKN(OP_ASSIGN_PLUS,+= operator)
TURING_TKN(OP_ASSIGN_MINUS,-= operator)
TURING_TKN(OP_ASSIGN_MULT,*= operator)
TURING_TKN(OP_ASSIGN_DIVIDE,/= operator)
TURING_TKN(OP_ASSIGN,:= operator)
TURING_TKN(OP_EQ,= operator)
TURING_TKN(OP_IMPLIES,=> operator)
TURING_TKN(OP_NOT_EQ,not equal operator)
TURING_TKN(OP_GT,> operator)
TURING_TKN(OP_GE,>= operator)
TURING_TKN(OP_LT,< operator)
TURING_TKN(OP_LE,<= operator)
TURING_TKN(OP_DOT,field reference operator)
TURING_TKN(DOTDOT,'..')
TURING_TKN(OP_AND,'and' operator)
TURING_TKN(OP_OR,'or' operator)

TURING_TKN(ADDRESSINT,'addressint' keyword)
TURING_TKN(ALL,'all' keyword)
TURING_TKN(ARRAY,'array' keyword)
TURING_TKN(ASM,'asm' keyword)
TURING_TKN(ASSERT,'assert' keyword)
TURING_TKN(BEGIN,'begin' keyword)
TURING_TKN(BIND,'bind' keyword)
TURING_TKN(BITS,'bits' keyword)
TURING_TKN(BODY,'body' keyword)
TURING_TKN(BREAK,'break' keyword)
TURING_TKN(BY,'by' keyword)
TURING_TKN(CASE,'case' keyword)
TURING_TKN(CHEAT,'cheat' keyword)
TURING_TKN(CHECKED,'checked' keyword)
TURING_TKN(CLASS,'class' keyword)
TURING_TKN(CLOSE,'close' keyword)
TURING_TKN(COLLECTION,'collection' keyword)
TURING_TKN(CONDITION,'condition' keyword)
TURING_TKN(CONST,'const' keyword)
TURING_TKN(DECREASING,'decreasing' keyword)
TURING_TKN(DEF,'def' keyword)
TURING_TKN(DEFERRED,'deferred' keyword)
TURING_TKN(ELSE,'else' keyword)
TURING_TKN(ELSEIF,'elseif' keyword)
TURING_TKN(ELSIF,'elsif' keyword)
TURING_TKN(END,'end' keyword)
TURING_TKN(ENUM,'enum' keyword)
TURING_TKN(EXIT,'exit' keyword)
TURING_TKN(EXPORT,'export' keyword)
TURING_TKN(EXTERNAL,'external' keyword)
TURING_TKN(FALSE,'false' keyword)
TURING_TKN(FCN,'fcn' keyword)
TURING_TKN(FLEXIBLE,'flexible' keyword)
TURING_TKN(FOR,'for' keyword)
TURING_TKN(FORK,'fork' keyword)
TURING_TKN(FORWARD,'forward' keyword)
TURING_TKN(FREE,'free' keyword)
TURING_TKN(FUNCTION,'function' keyword)
TURING_TKN(GET,'get' keyword)
TURING_TKN(HANDLER,'handler' keyword)
TURING_TKN(IF,'if' keyword)
TURING_TKN(IMPLEMENT,'implement' keyword)
TURING_TKN(IMPORT,'import' keyword)
TURING_TKN(IN,'in' keyword)
TURING_TKN(INCLUDE,'include' keyword)
TURING_TKN(INHERIT,'inherit' keyword)
TURING_TKN(INIT,'init' keyword)
TURING_TKN(INVARIANT,'invariant' keyword)
TURING_TKN(LABEL,'label' keyword)
TURING_TKN(LOOP,'loop' keyword)
TURING_TKN(MODULE,'module' keyword)
TURING_TKN(MONITOR,'monitor' keyword)
TURING_TKN(NAT,'nat' keyword)
TURING_TKN(NAT1,NAT'1' keyword)
TURING_TKN(NAT2,NAT'2' keyword)
TURING_TKN(NAT4,NAT'4' keyword)
TURING_TKN(NEW,'new' keyword)
TURING_TKN(NOT,'not' keyword)
TURING_TKN(OBJECTCLASS,'objectclass' keyword)
TURING_TKN(OF,'of' keyword)
TURING_TKN(OPAQUE,'opaque' keyword)
TURING_TKN(OPEN,'open' keyword)
TURING_TKN(PACKED,'packed' keyword)
TURING_TKN(PAUSE,'pause' keyword)
TURING_TKN(PERVASIVE,'pervasive' keyword)
TURING_TKN(POINTER,'pointer' keyword)
TURING_TKN(POST,'post' keyword)
TURING_TKN(PRE,'pre' keyword)
TURING_TKN(PRIORITY,'priority' keyword)
TURING_TKN(PROC,'proc' keyword)
TURING_TKN(PROCEDURE,'procedure' keyword)
TURING_TKN(PROCESS,'process' keyword)
TURING_TKN(PUT,'put' keyword)
TURING_TKN(QUIT,'quit' keyword)
TURING_TKN(READ,'read' keyword)
TURING_TKN(RECORD,'record' keyword)
TURING_TKN(REGISTER,'register' keyword)
TURING_TKN(RESULT,'result' keyword)
TURING_TKN(RETURN,'return' keyword)
TURING_TKN(SEEK,'seek' keyword)
TURING_TKN(SELF,'self' keyword)
TURING_TKN(SET,'set' keyword)
TURING_TKN(SHL,'shl' keyword)
TURING_TKN(SHR,'shr' keyword)
TURING_TKN(SIGNAL,'signal' keyword)
TURING_TKN(SKIP,'skip' keyword)
TURING_TKN(STRING,'string' keyword)
TURING_TKN(TAG,'tag' keyword)
TURING_TKN(TELL,'tell' keyword)
TURING_TKN(THEN,'then' keyword)
TURING_TKN(TIMEOUT,'timeout' keyword)
TURING_TKN(TO,'to' keyword)
TURING_TKN(TRUE,'true' keyword)
TURING_TKN(TYPE,'type' keyword)
TURING_TKN(UNCHECKED,'unchecked' keyword)
TURING_TKN(UNION,'union' keyword)
TURING_TKN(UNQUALIFIED,'unqualified' keyword)
TURING_TKN(VAR,'var' keyword)
TURING_TKN(WAIT,'wait' keyword)
TURING_TKN(WHEN,'when' keyword)
TURING_TKN(WRITE,'write' keyword)
TURING_TKN(XOR,'xor' keyword)

