#include "parse.h"
#include "lex.h"


map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}

bool Prog(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	bool decl = true;
	bool stmt = true;
	string progName;

//checks for program token and then name
	if(tok == PROGRAM){
		tok = Parser::GetNextToken(in, line);
		if (tok == IDENT)
			progName = tok.GetLexeme();
		else{
			ParseError(line, "Missing Program Name");
			return false;
		}
	}
#if 0
//if next token is	
tok = Parser::GetNextToken(in, line);
if (tok == INTEGER || tok == REAL || tok == CHAR){
	Parser::PushBackToken(tok);
	decl = Decl(in, line);
}
#endif
//checks for declarations and statements
//both are optional
	decl = Decl(in, line);
	stmt = Stmt(in, line);
	if (!decl){
		ParseError(line, "Incorrect Declaration in Program");
		return false;
	}
	if (!stmt){
		ParseError(line, "Incorrect Statement in program");
		return false;
	}
//checks for end of program
	tok = Parser::GetNextToken(in, line);
	if (tok == END){
		tok = Parser::GetNextToken(in, line);
		if (tok != PROGRAM){
			ParseError(line, "Missing PROGRAM at the End");
			return false;
		}
	tok = Parser::GetNextToken(in, line);
	if (tok.GetLexeme() != progName){
		ParseError(line, "Missing Program Name");
		return false;
	}

	return true;
}
	ParseError(line, "Missing END of Program");
	return false;
}

bool Decl(istream& in, int& line){
	LexItem type = Parser::GetNextToken(in, line);
	LexItem tok;
	bool status;
	if(type == INTEGER || type == REAL || type == CHAR){
		tok = Parser::GetNextToken(in, line);
		if (tok != COLON){
			return false;
		}
		status = IdList(in, line, type);
		if (status){
			status = Decl(in, line);
			return status;
		}
	}

Parser::PushBackToken(type);
return true;
}

bool Stmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	bool status;
	switch ( tok.GetToken() ){
	
	case IDENT:
		Parser::PushBackToken(tok);
		status = AssignStmt(in, line);
		if (status) status = Stmt(in, line);	
		break;

	case IF: 
		status = IfStmt(in,line);
		if (status) status = Stmt(in, line);
	break;

	case PRINT:
		status = PrintStmt(in,line);
		if (status) status = Stmt(in, line);
	break;

	case READ:
		status = ReadStmt(in,line);
		if (status) status = Stmt(in, line);
	break;
	
	default:
		Parser::PushBackToken(tok);
		return true;
	}

	return status;
}

bool PrintStmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	bool status;

	if (tok != COMA){
		ParseError(line, "Missing a COMA");
			return false;
		}
		status = ExprList(in, line);
		if (!status) return false;


	return true;
}

bool IfStmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in ,line);
	bool status;
	if (tok != LPAREN){
		ParseError(line, "Missing Open Parenthesis");
		return false;
	}

	status = LogicExpr(in, line);
	tok = Parser::GetNextToken(in, line);
	
	if (tok != RPAREN){
		ParseError(line, "Missing Close Parenthesis");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (tok != THEN){
		ParseError(line, "Missing Open THEN");
		return false;
	}

	status = Stmt(in, line);

	if (!status){
		ParseError(line, "Incorrect Statement in IF");
		return false;
	}

	//checks for end of if statement
	tok = Parser::GetNextToken(in, line);
	if (tok == END){
		tok = Parser::GetNextToken(in, line);
		if (tok != IF){
			ParseError(line, "Missing IF at End of IF statement");
			return false;
		}

	return true;
}
	
	ParseError(line, "Missing END of IF");
	return false;
}

bool ReadStmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	bool status;

	if (tok != COMA){
		ParseError(line, "Missing a COMA");
			return false;
		}
		status = ExprList(in, line);
		if (!status) return false;


	return true;
}

bool IdList(istream& in, int& line, LexItem type){
	LexItem tok = Parser::GetNextToken(in, line);
	if (tok == IDENT){
		if (SymTable.find(tok.GetLexeme()) != SymTable.end()){
			ParseError(line, "Variable Redeclaration");
			return false;
		}
		SymTable[tok.GetLexeme()] = type.GetToken();
		tok = Parser::GetNextToken(in, line);
		if (tok == COMA){
			return IdList(in, line, type);
		}
	}
	
		
	Parser::PushBackToken(tok);
	return true;
}

bool VarList(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	bool status = false;
//don't call Var
	if (defVar.find(tok.GetLexeme()) != defVar.end()) status = true;

	if (!status){
		ParseError(line, "Undefined Var");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (status && tok == COMA){
		return VarList(in, line);
	}
		
	Parser::PushBackToken(tok);
	return true;
}

bool Var(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	if (SymTable.find(tok.GetLexeme()) == SymTable.end()){
		ParseError(line, "Undeclared Variable");
		return false;
	}
	Parser::PushBackToken(tok);
	return true;
}

bool AssignStmt(istream& in, int& line){
	bool status = Var(in, line);
	LexItem tok = Parser::GetNextToken(in, line);

	if (defVar[tok.GetLexeme()]){
		ParseError(line, "Variable Redefinition");
		return false;
	}
	defVar[tok.GetLexeme()] = true;
	tok = Parser::GetNextToken(in, line);
	
	
	if (tok == ASSOP && status){
		status = Expr(in, line);
		if(status){
			return true;
		}
	}

	if (tok != ASSOP)
	ParseError(line, "Missing Assignment Operator");
	
	return false;
}

bool ExprList(istream& in, int& line){
	LexItem tok;
	bool status;

	status = Expr(in, line);

	tok = Parser::GetNextToken(in, line);
	if (status && tok == COMA){
		return ExprList(in, line);
	}
	if(!status){
		ParseError(line, "Missing Expression");
	}
	Parser::PushBackToken(tok);
	return status;
}

bool LogicExpr(istream& in, int& line){
	bool status;
	LexItem tok;
	status = Expr(in, line);
	
	if (!status) return false;

	tok = Parser::GetNextToken(in, line);

	if (!(tok == EQUAL || tok == LTHAN)) return false;
	

	status = Expr(in, line);

	if (!status) return false;
	


	return true;
}

bool Expr(istream& in, int& line){
	LexItem tok; //= Parser::GetNextToken(in, line);
	bool status;

	status = Term(in, line);
	tok = Parser::GetNextToken(in, line);
	if(!status){
		ParseError(line, "Missing Term");
		return false;
	}

	if(tok == PLUS || tok == MINUS)
	return Expr(in, line);

	Parser::PushBackToken(tok);
	return true;
}

bool Term(istream& in, int& line){
	LexItem tok; // = Parser::GetNextToken(in, line);
	bool status;


	status = SFactor(in, line);
	tok = Parser::GetNextToken(in, line);

	if (tok == ERR){
		ParseError(line, "Unrecognized Input Pattern\n" + tok.GetLexeme());
		return false;
	}


	if(!status){
		ParseError(line, "Missing Variable");
		return false;
	}

	if(tok == MULT || tok == DIV)
	return Term(in, line);

	Parser::PushBackToken(tok);
	return true;
}

bool SFactor(istream& in, int& line){
	int sign = 0;
	LexItem tok = Parser::GetNextToken(in, line);
	bool status;

	if(tok == PLUS) sign = 1;
	else if(tok == MINUS) sign = -1;
	else Parser::PushBackToken(tok);

	status = Factor(in, line, sign);


	return status;
}

bool Factor(istream& in, int& line, int sign){
	LexItem tok = Parser::GetNextToken(in, line);
	bool status = false;

	switch ( tok.GetToken() )
	{

	case LPAREN:
		status = Expr(in, line);
		tok = Parser::GetNextToken(in, line);
		if(status && (tok == RPAREN)) return true;
		break;
	default:
		ParseError(line, "Unrecognized Symbol");
		break;
	case IDENT:
	if (SymTable.find(tok.GetLexeme()) != SymTable.end()) status = true;
	if (status) return true;
	ParseError(line, "Undefined Variable");
	break;
	case ICONST:
	case RCONST:
	case SCONST:
		return true;
	}
	return false;
}