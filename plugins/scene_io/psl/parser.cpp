/* A Bison parser, made by GNU Bison 1.875.  */

/* C++ Skeleton parser for LALR(1) parsing with Bison,
   Copyright (C) 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include "parser.hpp"

/* Enable debugging if requested.  */
#if YYDEBUG
# define YYCDEBUG    if (debug_) cdebug_
#else /* !YYDEBUG */
# define YYCDEBUG    if (0) cdebug_
#endif /* !YYDEBUG */

int
yy::Parser::parse ()
{
  int nerrs = 0;
  int errstatus = 0;

  /* Initialize stack.  */
  state_stack_ = StateStack (0);
  semantic_stack_ = SemanticStack (1);
  location_stack_ = LocationStack (1);

  /* Start.  */
  state_ = 0;
  looka_ = empty_;
#if YYLSP_NEEDED
  location = initlocation_;
#endif
  YYCDEBUG << "Starting parse" << std::endl;

  /* New state.  */
 yynewstate:
  state_stack_.push (state_);
  YYCDEBUG << "Entering state " << state_ << std::endl;
  goto yybackup;

  /* Backup.  */
 yybackup:

  /* Try to take a decision without lookahead.  */
  n_ = pact_[state_];
  if (n_ == pact_ninf_)
    goto yydefault;

  /* Read a lookahead token.  */
  if (looka_ == empty_)
    {
      YYCDEBUG << "Reading a token: ";
      lex_ ();
    }

  /* Convert token to internal form.  */
  if (looka_ <= 0)
    {
      looka_ = eof_;
      ilooka_ = 0;
      YYCDEBUG << "Now at end of input." << std::endl;
    }
  else
    {
      ilooka_ = translate_ (looka_);
#if YYDEBUG
      if (debug_)
	{
	  YYCDEBUG << "Next token is " << looka_
		 << " (" << name_[ilooka_];
	  print_ ();
	  YYCDEBUG << ')' << std::endl;
	}
#endif
    }

  n_ += ilooka_;
  if (n_ < 0 || last_ < n_ || check_[n_] != ilooka_)
    goto yydefault;

  /* Reduce or error.  */
  n_ = table_[n_];
  if (n_ < 0)
    {
      if (n_ == table_ninf_)
	goto yyerrlab;
      else
	{
	  n_ = -n_;
	  goto yyreduce;
	}
    }
  else if (n_ == 0)
    goto yyerrlab;

  /* Accept?  */
  if (n_ == final_)
    goto yyacceptlab;

  /* Shift the lookahead token.  */
  YYCDEBUG << "Shifting token " << looka_
	 << " (" << name_[ilooka_] << "), ";

  /* Discard the token being shifted unless it is eof.  */
  if (looka_ != eof_)
    looka_ = empty_;

  semantic_stack_.push (value);
  location_stack_.push (location);

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (errstatus)
    --errstatus;

  state_ = n_;
  goto yynewstate;

  /* Default action.  */
 yydefault:
  n_ = defact_[state_];
  if (n_ == 0)
    goto yyerrlab;
  goto yyreduce;

  /* Reduce.  */
 yyreduce:
  len_ = r2_[n_];
  if (len_)
    {
      yyval = semantic_stack_[len_ - 1];
      yyloc = location_stack_[len_ - 1];
    }
  else
    {
      yyval = semantic_stack_[0];
      yyloc = location_stack_[0];
    }

#if YYDEBUG
  if (debug_)
    {
      YYCDEBUG << "Reducing via rule " << n_ - 1
	     << " (line " << rline_[n_] << "), ";
      for (unsigned char i = prhs_[n_];
	   0 <= rhs_[i]; ++i)
	YYCDEBUG << name_[rhs_[i]] << ' ';
      YYCDEBUG << "-> " << name_[r1_[n_]] << std::endl;
    }
#endif

  if (len_)
    {
      Slice< LocationType, LocationStack > slice (location_stack_, len_);
      YYLLOC_DEFAULT (yyloc, slice, len_);
    }

  switch (n_)
    {
        case 3:
#line 162 "parser.y"
    {}
    break;

  case 4:
#line 164 "parser.y"
    {}
    break;

  case 5:
#line 166 "parser.y"
    {}
    break;

  case 6:
#line 170 "parser.y"
    {}
    break;

  case 7:
#line 172 "parser.y"
    {}
    break;

  case 8:
#line 176 "parser.y"
    {
                            WRITE_CODE ("\ndefine ");
                          }
    break;

  case 9:
#line 180 "parser.y"
    {}
    break;

  case 10:
#line 182 "parser.y"
    {
                            WRITE_CODE ("\ndefine ");
                          }
    break;

  case 11:
#line 186 "parser.y"
    {}
    break;

  case 12:
#line 190 "parser.y"
    {
			    strcpy (yyval.acString, semantic_stack_[0].acString);
			  }
    break;

  case 13:
#line 196 "parser.y"
    {
                            strcpy (yyval.acString, "");
                          }
    break;

  case 14:
#line 200 "parser.y"
    {
                            if ( _tObjectMap.find (semantic_stack_[0].acString) == _tObjectMap.end() )
                            {
			      psl_error ("trying to extend from non existing object");
			      exit (1);
                            }
                            _ptParent = _tObjectMap [semantic_stack_[0].acString];
			    strcpy (yyval.acString, _ptParent->className().c_str());
			  }
    break;

  case 15:
#line 210 "parser.y"
    {
			    _ptParent = NULL;
			    strcpy (yyval.acString, semantic_stack_[0].acString);
			  }
    break;

  case 16:
#line 217 "parser.y"
    {
                            WRITE_CODE ("Scene\n");
			    DefineObject (semantic_stack_[2].acString, semantic_stack_[1].acString, "Scene");
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
    break;

  case 17:
#line 223 "parser.y"
    {
			    UpdateObject (semantic_stack_[5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  }
    break;

  case 18:
#line 230 "parser.y"
    {
			    _ptData = TScenePsl::_ptParsedScene;
			    _tDataStack.push (_ptData);
                            _eVarScope = FX_OBJECT_SCOPE;

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->program();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  }
    break;

  case 19:
#line 240 "parser.y"
    {
			    _tDataStack.pop();
                            TScenePsl::_ptParsedScene->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

                            TScenePsl::_ptParsedScene->program()->printDebug();

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  }
    break;

  case 20:
#line 254 "parser.y"
    {
                            if ( strcmp (semantic_stack_[2].acString, "Object") && strcmp (semantic_stack_[2].acString, "Aggregate") )
                            {
                              psl_error ("only objects and scene can be instanced");
                              exit (1);
                            }
			    CreateObject (semantic_stack_[1].acString, "");
                            _eVarScope = FX_OBJECT_SCOPE;

                            _ptCurrentProgram = _ptData->program();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  }
    break;

  case 21:
#line 268 "parser.y"
    {
                            _tDataStack.top()->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

                            _tDataStack.top()->program()->printDebug();
			    _tDataStack.pop();

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  }
    break;

  case 22:
#line 282 "parser.y"
    {
                            WRITE_CODE (semantic_stack_[3].acString << std::endl);
			    DefineObject (semantic_stack_[2].acString, semantic_stack_[1].acString, DefaultClass (semantic_stack_[3].acString));
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
    break;

  case 23:
#line 288 "parser.y"
    {
			    UpdateObject (semantic_stack_[5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  }
    break;

  case 24:
#line 299 "parser.y"
    {
                            yyval.tExpressionData.eType         = FX_REAL;
                            yyval.tExpressionData.nValue.dValue = semantic_stack_[0].dValue;
                          }
    break;

  case 25:
#line 306 "parser.y"
    {
                            yyval.tExpressionData.eType         = FX_BOOL;
                            yyval.tExpressionData.nValue.gValue = semantic_stack_[0].gValue;
                          }
    break;

  case 26:
#line 313 "parser.y"
    {
                            if ( ( semantic_stack_[5].tExpressionData.eType != FX_REAL ) || ( semantic_stack_[3].tExpressionData.eType != FX_REAL ) || ( semantic_stack_[1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_COLOR;
                          }
    break;

  case 27:
#line 324 "parser.y"
    {
                            if ( ( semantic_stack_[5].tExpressionData.eType != FX_REAL ) || ( semantic_stack_[3].tExpressionData.eType != FX_REAL ) || ( semantic_stack_[1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_VECTOR;
                          }
    break;

  case 28:
#line 335 "parser.y"
    {
                            if ( ( semantic_stack_[3].tExpressionData.eType != FX_REAL ) || ( semantic_stack_[1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_VECTOR2;
                          }
    break;

  case 29:
#line 346 "parser.y"
    {
                            yyval.tExpressionData.eType = FX_STRING;
                          }
    break;

  case 30:
#line 352 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_real " << semantic_stack_[0].tExpressionData.nValue.dValue << std::endl);
                          }
    break;

  case 31:
#line 357 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_bool " << semantic_stack_[0].tExpressionData.nValue.gValue << std::endl);
                          }
    break;

  case 32:
#line 362 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_color ...\n");
                          }
    break;

  case 33:
#line 367 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_vector ...\n");
                          }
    break;

  case 34:
#line 372 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_vector2 ...\n");
                          }
    break;

  case 35:
#line 377 "parser.y"
    {
                            yyval.tExpressionData = semantic_stack_[0].tExpressionData;
                            WRITE_CODE ("push_string ...\n");
                          }
    break;

  case 36:
#line 382 "parser.y"
    {}
    break;

  case 37:
#line 384 "parser.y"
    {
                            yyval.tExpressionData.eType = GetTypeCode (semantic_stack_[0].acString);
                          }
    break;

  case 38:
#line 388 "parser.y"
    {}
    break;

  case 39:
#line 392 "parser.y"
    {
                            WRITE_CODE ("call " << semantic_stack_[3].acString << std::endl);
                          }
    break;

  case 41:
#line 399 "parser.y"
    {}
    break;

  case 42:
#line 403 "parser.y"
    {}
    break;

  case 43:
#line 405 "parser.y"
    {}
    break;

  case 44:
#line 409 "parser.y"
    {}
    break;

  case 45:
#line 417 "parser.y"
    {}
    break;

  case 46:
#line 419 "parser.y"
    {}
    break;

  case 47:
#line 423 "parser.y"
    {
                            _eVarType = FX_REAL;
                          }
    break;

  case 49:
#line 428 "parser.y"
    {
                            _eVarType = FX_BOOL;
                          }
    break;

  case 51:
#line 433 "parser.y"
    {
                            _eVarType = FX_STRING;
                          }
    break;

  case 53:
#line 438 "parser.y"
    {
                            _eVarType = FX_COLOR;
                          }
    break;

  case 55:
#line 443 "parser.y"
    {
                            _eVarType = FX_VECTOR;
                          }
    break;

  case 57:
#line 448 "parser.y"
    {
                            _eVarType = FX_VECTOR2;
                          }
    break;

  case 59:
#line 453 "parser.y"
    {
                            _eVarType = FX_IMAGE;
                          }
    break;

  case 61:
#line 458 "parser.y"
    {
                            if ( _eVarScope == FX_GLOBAL_SCOPE )
                            {
                              psl_error ("cannot use a complex type for a global variable");
                              exit (1);
                            }
                            _eVarType = GetTypeCode (semantic_stack_[0].acString);
                          }
    break;

  case 63:
#line 468 "parser.y"
    {
                            psl_error ("unknown type");
                            exit (1);
                          }
    break;

  case 65:
#line 476 "parser.y"
    {}
    break;

  case 66:
#line 478 "parser.y"
    {}
    break;

  case 67:
#line 482 "parser.y"
    {
                            AddVariable (semantic_stack_[0].acString);
                          }
    break;

  case 68:
#line 486 "parser.y"
    {
                            if ( _eVarType != semantic_stack_[0].tExpressionData.eType )
                            {
                              psl_error ("wrong type in assignment");
                              GOM.error() << "left = " << (int) _eVarType << ", right = " << (int) semantic_stack_[0].tExpressionData.eType << std::endl;
                              exit (1);
                            }
                            AddVariable (semantic_stack_[2].acString);
                          }
    break;

  case 69:
#line 502 "parser.y"
    {}
    break;

  case 70:
#line 504 "parser.y"
    {}
    break;

  case 71:
#line 508 "parser.y"
    {}
    break;

  case 72:
#line 510 "parser.y"
    {}
    break;

  case 73:
#line 514 "parser.y"
    {
                            /*
                            if ( $1 != $3.eType )
                            {
                              psl_error ("wrong type in assignment");
                              exit (1);
                            }
                            */
                            WRITE_CODE ("pop " << _lvalueName << std::endl);
                          }
    break;

  case 74:
#line 527 "parser.y"
    {
                            yyval.eType = FX_NONE;
                            _lvalueName = semantic_stack_[0].acString;
                          }
    break;

  case 75:
#line 532 "parser.y"
    {
                            yyval.eType = FX_NONE;
                            _lvalueName += std::string (".") + semantic_stack_[0].acString;
                          }
    break;

  case 77:
#line 544 "parser.y"
    {}
    break;

  case 78:
#line 548 "parser.y"
    {}
    break;

  case 79:
#line 550 "parser.y"
    {}
    break;

  case 80:
#line 554 "parser.y"
    {
                            _tCurrentEvent = semantic_stack_[1].acString;
                            SET_CURRENT_CODE();
                            WRITE_CODE ("\nevent " << semantic_stack_[1].acString << std::endl);
                          }
    break;

  case 81:
#line 560 "parser.y"
    {
                            _eVarScope = FX_EVENT_SCOPE;
                          }
    break;

  case 82:
#line 564 "parser.y"
    {
                            _tCurrentEvent = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
                          }
    break;

  case 83:
#line 571 "parser.y"
    {}
    break;


    }

/* Line 446 of lalr1.cc.  */
#line 710 "parser.cpp"

  state_stack_.pop (len_);
  semantic_stack_.pop (len_);
  location_stack_.pop (len_);

#if YYDEBUG
  if (debug_)
    {
      YYCDEBUG << "state stack now";
      for (StateStack::ConstIterator i = state_stack_.begin ();
	   i != state_stack_.end (); ++i)
	YYCDEBUG << ' ' << *i;
      YYCDEBUG << std::endl;
    }
#endif

  semantic_stack_.push (yyval);
  location_stack_.push (yyloc);

  /* Shift the result of the reduction.  */
  n_ = r1_[n_];
  state_ = pgoto_[n_ - ntokens_] + state_stack_[0];
  if (0 <= state_ && state_ <= last_ && check_[state_] == state_stack_[0])
    state_ = table_[state_];
  else
    state_ = defgoto_[n_ - ntokens_];
  goto yynewstate;

  /* Report and recover from errors.  This is very incomplete.  */
 yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!errstatus)
    {
      ++nerrs;

#if YYERROR_VERBOSE
      n_ = pact_[state_];
      if (pact_ninf_ < n_ && n_ < last_)
	{
	  message = "syntax error, unexpected ";
	  message += name_[ilooka_];
	  {
	    int count = 0;
	    for (int x = (n_ < 0 ? -n_ : 0); x < ntokens_ + nnts_; ++x)
	      if (check_[x + n_] == x && x != terror_)
		++count;
	    if (count < 5)
	      {
		count = 0;
		for (int x = (n_ < 0 ? -n_ : 0); x < ntokens_ + nnts_; ++x)
		  if (check_[x + n_] == x && x != terror_)
		    {
		      message += (!count++) ? ", expecting " : " or ";
		      message += name_[x];
		    }
	      }
	  }
	}
      else
#endif
	message = "syntax error";
      error_ ();
    }
  goto yyerrlab1;

  /* Error raised explicitly by an action.  */
 yyerrlab1:
  if (errstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (looka_ == eof_)
	goto yyabortlab;
      YYCDEBUG << "Discarding token " << looka_
	     << " (" << name_[ilooka_] << ")." << std::endl;
      looka_ = empty_;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  errstatus = 3;

  for (;;)
    {
      n_ = pact_[state_];
      if (n_ != pact_ninf_)
	{
	  n_ += terror_;
	  if (0 <= n_ && n_ <= last_ && check_[n_] == terror_)
	    {
	      n_ = table_[n_];
	      if (0 < n_)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (!state_stack_.height ())
	goto yyabortlab;

#if YYDEBUG
      if (debug_)
	{
	  if (stos_[state_] < ntokens_)
	    {
	      YYCDEBUG << "Error: popping token "
		     << token_number_[stos_[state_]]
		     << " (" << name_[stos_[state_]];
# ifdef YYPRINT
	      YYPRINT (stderr, token_number_[stos_[state_]],
		       semantic_stack_.top ());
# endif
	      YYCDEBUG << ')' << std::endl;
	    }
	  else
	    {
	      YYCDEBUG << "Error: popping nonterminal ("
		     << name_[stos_[state_]] << ')' << std::endl;
	    }
	}
#endif

      state_ = (state_stack_.pop (), state_stack_[0]);
      semantic_stack_.pop ();
      location_stack_.pop ();;

#if YYDEBUG
      if (debug_)
	{
	  YYCDEBUG << "Error: state stack now";
	  for (StateStack::ConstIterator i = state_stack_.begin ();
	       i != state_stack_.end (); ++i)
	    YYCDEBUG << ' ' << *i;
	  YYCDEBUG << std::endl;
	}
#endif
    }

  if (n_ == final_)
    goto yyacceptlab;

  YYCDEBUG << "Shifting error token, ";

  semantic_stack_.push (value);
  location_stack_.push (location);

  state_ = n_;
  goto yynewstate;

  /* Accept.  */
 yyacceptlab:
  return 0;

  /* Abort.  */
 yyabortlab:
  return 1;
}

void
yy::Parser::lex_ ()
{
#if YYLSP_NEEDED
  looka_ = yylex (&value, &location);
#else
  looka_ = yylex (&value);
#endif
}

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
const short yy::Parser::pact_ninf_ = -133;
const short
yy::Parser::pact_[] =
{
    -133,     4,  -133,    -4,  -133,   -28,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,   -19,  -133,  -133,  -133,  -133,  -133,    33,
     -11,    47,    47,    57,    31,    47,    47,    47,    47,    47,
      47,    47,    50,    94,    96,  -133,    48,   -46,  -133,   -34,
      98,  -133,    98,  -133,     2,     3,    11,    19,    20,    23,
      24,  -133,  -133,  -133,    56,    10,    47,  -133,  -133,  -133,
     -19,   -19,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    56,
      55,    58,  -133,  -133,    54,  -133,   101,    59,    60,    61,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    65,
      66,    63,  -133,    67,  -133,   103,  -133,  -133,    10,  -133,
      10,    10,    10,  -133,  -133,  -133,  -133,    67,  -133,  -133,
       6,  -133,  -133,    68,    69,    70,    56,    56,    10,    10,
    -133,    10,    10,    10,    73,    74,    36,  -133,    75,    76,
      72,  -133,  -133,    77,    10,    10,  -133,  -133,    78,    79,
    -133,  -133,  -133,    64,    80,     1,    62,   111,  -133,    81,
      42,  -133,  -133,    54,  -133,  -133,    10,   113,  -133,  -133
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
const unsigned char
yy::Parser::defact_[] =
{
       2,     0,     1,    13,    63,     8,    47,    49,    51,    53,
      55,    57,    59,    13,     4,     5,     6,     7,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    67,     0,    65,     0,
       0,     9,     0,    11,     0,     0,     0,     0,     0,     0,
       0,    18,    15,    14,    45,     0,     0,    62,    64,    12,
      13,    13,    48,    50,    52,    54,    56,    58,    60,    45,
       0,     0,    24,    25,    36,    29,     0,     0,     0,     0,
      30,    31,    32,    33,    34,    35,    68,    38,    66,     0,
       0,     0,    61,    63,    46,    77,    78,    21,    40,    37,
       0,     0,     0,    22,    16,    19,    80,     0,    79,    44,
       0,    41,    42,     0,     0,     0,    45,    45,    40,     0,
      39,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,    23,    17,     0,     0,     0,    28,    81,     0,     0,
      45,    26,    27,     0,     0,    74,     0,    83,    69,     0,
       0,    82,    72,    74,    70,    71,     0,     0,    73,    75
};

/* YYPGOTO[NTERM-NUM].  */
const short
yy::Parser::pgoto_[] =
{
    -133,  -133,  -133,  -133,  -133,  -133,    87,   -12,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,   -55,  -132,    15,  -133,    17,    -6,   136,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    -3,    82,
    -133,    -8,  -133,  -133,   -66,  -133,    45,  -133,  -133,  -133
};

/* YYDEFGOTO[NTERM-NUM].  */
const short
yy::Parser::defgoto_[] =
{
      -1,     1,    14,    15,    23,    24,    60,    20,    43,   117,
      16,    69,    17,    54,    41,   116,    80,    81,    82,    83,
      84,    85,   109,    87,   110,   111,   112,    70,    94,    25,
      26,    27,    28,    29,    30,    31,    21,    22,    37,    38,
     147,   148,   149,   150,    71,    95,    96,   118,   140,   144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
const short yy::Parser::table_ninf_ = -77;
const short
yy::Parser::table_[] =
{
      86,    32,   -61,    91,     2,   -10,    56,   -63,    57,     3,
       4,   146,     5,    72,    73,   146,    74,    75,    56,    39,
      58,    76,    44,    45,    46,    47,    48,    49,    50,    19,
       6,     7,     8,     9,    10,    11,    12,    13,    35,    77,
      78,    79,    33,    34,    19,   113,   114,   115,    89,    90,
     124,   125,    98,    36,    56,    56,    62,    63,   119,   120,
      92,    93,    40,    56,    42,    64,   128,   129,   130,    92,
     145,    56,    56,    65,    66,    56,    56,    67,    68,   138,
     139,     6,     7,     8,     9,    10,    11,    12,   119,   133,
       6,     7,     8,     9,    10,    11,    12,   156,   157,    51,
      52,   158,    53,    55,    59,    98,   -76,    99,    97,   107,
     100,   101,   102,   105,   103,   104,   152,   153,   106,   159,
     121,   122,   123,   131,   132,   136,   137,   134,   135,    61,
     151,   141,   142,   126,   143,   155,   127,    18,    88,   154,
     108
};

/* YYCHECK.  */
const unsigned char
yy::Parser::check_[] =
{
      55,    13,     6,    69,     0,    33,    52,     6,    54,     5,
       6,   143,     8,     3,     4,   147,     6,     7,    52,    22,
      54,    11,    25,    26,    27,    28,    29,    30,    31,    48,
      26,    27,    28,    29,    30,    31,    32,    33,    49,    29,
      30,    31,     9,    10,    48,   100,   101,   102,    60,    61,
     116,   117,    51,     6,    52,    52,    54,    54,    52,    53,
       5,     6,     5,    52,    33,    54,   121,   122,   123,     5,
       6,    52,    52,    54,    54,    52,    52,    54,    54,   134,
     135,    26,    27,    28,    29,    30,    31,    32,    52,    53,
      26,    27,    28,    29,    30,    31,    32,    55,    56,    49,
       6,   156,     6,    55,     6,    51,    50,     6,    50,     6,
      51,    51,    51,    50,    49,    49,    54,     6,    51,     6,
      52,    52,    52,    50,    50,    53,    49,    52,    52,    42,
      50,    53,    53,   118,   140,    54,   119,     1,    56,   147,
      95
};

#if YYDEBUG
/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
yy::Parser::stos_[] =
{
       0,    58,     0,     5,     6,     8,    26,    27,    28,    29,
      30,    31,    32,    33,    59,    60,    67,    69,    85,    48,
      64,    93,    94,    61,    62,    86,    87,    88,    89,    90,
      91,    92,    64,     9,    10,    49,     6,    95,    96,    95,
       5,    71,    33,    65,    95,    95,    95,    95,    95,    95,
      95,    49,     6,     6,    70,    55,    52,    54,    54,     6,
      63,    63,    54,    54,    54,    54,    54,    54,    54,    68,
      84,   101,     3,     4,     6,     7,    11,    29,    30,    31,
      73,    74,    75,    76,    77,    78,    79,    80,    96,    64,
      64,   101,     5,     6,    85,   102,   103,    50,    51,     6,
      51,    51,    51,    49,    49,    50,    51,     6,   103,    79,
      81,    82,    83,    79,    79,    79,    72,    66,   104,    52,
      53,    52,    52,    52,   101,   101,    81,    83,    79,    79,
      79,    50,    50,    53,    52,    52,    53,    49,    79,    79,
     105,    53,    53,    84,   106,     6,    80,    97,    98,    99,
     100,    50,    54,     6,    98,    54,    55,    56,    79,     6
};

/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal token number corresponding
   to YYLEX-NUM.  */
const unsigned short
yy::Parser::token_number_[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    43,    45,    42,    47,   298,    58,   123,
     125,    40,    44,    41,    59,    61,    46
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
yy::Parser::r1_[] =
{
       0,    57,    58,    58,    58,    58,    59,    59,    61,    60,
      62,    60,    63,    64,    64,    64,    66,    65,    68,    67,
      70,    69,    72,    71,    73,    74,    75,    76,    77,    78,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      81,    81,    82,    82,    83,    84,    84,    86,    85,    87,
      85,    88,    85,    89,    85,    90,    85,    91,    85,    92,
      85,    93,    85,    94,    85,    95,    95,    96,    96,    97,
      97,    98,    98,    99,   100,   100,   101,   101,   102,   102,
     104,   105,   103,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
yy::Parser::r2_[] =
{
       0,     2,     0,     2,     2,     2,     1,     1,     0,     3,
       0,     3,     1,     0,     3,     3,     0,     7,     0,     6,
       0,     6,     0,     7,     1,     1,     8,     8,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     4,
       0,     1,     1,     3,     1,     0,     2,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     3,     1,     3,     1,
       2,     2,     2,     3,     1,     3,     0,     2,     1,     2,
       0,     0,     9,     2
};

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
const char*
const yy::Parser::name_[] =
{
  "$end", "error", "$undefined", "T_REAL", "T_BOOL", "T_COMPLEX_TYPE", 
  "T_IDENTIFIER", "T_QUOTED_STRING", "T_DEFINE", "T_CLASS", "T_EXTENDS", 
  "T_NEW", "T_BOX", "T_CIRCLE", "T_CONE", "T_CYLINDER", "T_DIFFERENCE", 
  "T_FILTER", "T_INTERSECTION", "T_MESH", "T_PHONG_TRIANGLE", "T_PLANE", 
  "T_RECTANGLE", "T_SPHERE", "T_TRIANGLE", "T_UNION", "T_TYPE_REAL", 
  "T_TYPE_BOOL", "T_TYPE_STRING", "T_TYPE_COLOR", "T_TYPE_VECTOR", 
  "T_TYPE_VECTOR2", "T_TYPE_IMAGE", "T_TYPE_SCENE", "T_TYPE_BSDF", 
  "T_TYPE_CAMERA", "T_TYPE_LIGHT", "T_TYPE_MATERIAL", "T_TYPE_RENDERER", 
  "T_TYPE_OBJECT", "T_TYPE_AGGREGATE", "T_TYPE_OBJECT_FILTER", 
  "T_TYPE_IMAGE_FILTER", "'+'", "'-'", "'*'", "'/'", "UNARY_MINUS", "':'", 
  "'{'", "'}'", "'('", "','", "')'", "';'", "'='", "'.'", "$accept", 
  "everything", "instance", "definition", "@1", "@2", "name", "class", 
  "scene_def", "@3", "scene_instance", "@4", "object_instance", "@5", 
  "any_def", "@6", "real_expression", "bool_expression", 
  "color_expression", "vector_expression", "vector2_expression", 
  "string_expression", "expression", "function_call", "function_params", 
  "function_params1", "function_param", "variables", "variable", "@7", 
  "@8", "@9", "@10", "@11", "@12", "@13", "@14", "@15", "var_list", "var", 
  "sentences", "sentence", "assignment", "lvalue", "program", 
  "event_list", "event", "@16", "@17", "code", 0
};
#endif

#if YYDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS. */
const yy::Parser::RhsNumberType
yy::Parser::rhs_[] =
{
      58,     0,    -1,    -1,    58,    85,    -1,    58,    59,    -1,
      58,    60,    -1,    67,    -1,    69,    -1,    -1,     8,    61,
      71,    -1,    -1,     8,    62,    65,    -1,     6,    -1,    -1,
      48,    10,     6,    -1,    48,     9,     6,    -1,    -1,    33,
      63,    64,    49,    66,   101,    50,    -1,    -1,    33,    64,
      49,    68,   101,    50,    -1,    -1,     5,    64,    49,    70,
     101,    50,    -1,    -1,     5,    63,    64,    49,    72,   101,
      50,    -1,     3,    -1,     4,    -1,    29,    51,    79,    52,
      79,    52,    79,    53,    -1,    30,    51,    79,    52,    79,
      52,    79,    53,    -1,    31,    51,    79,    52,    79,    53,
      -1,     7,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    77,    -1,    78,    -1,     6,    -1,    11,     6,    -1,
      80,    -1,     6,    51,    81,    53,    -1,    -1,    82,    -1,
      83,    -1,    81,    52,    83,    -1,    79,    -1,    -1,    84,
      85,    -1,    -1,    26,    86,    95,    54,    -1,    -1,    27,
      87,    95,    54,    -1,    -1,    28,    88,    95,    54,    -1,
      -1,    29,    89,    95,    54,    -1,    -1,    30,    90,    95,
      54,    -1,    -1,    31,    91,    95,    54,    -1,    -1,    32,
      92,    95,    54,    -1,    -1,     5,    93,    95,    54,    -1,
      -1,     6,    94,    95,    54,    -1,    96,    -1,    95,    52,
      96,    -1,     6,    -1,     6,    55,    79,    -1,    98,    -1,
      97,    98,    -1,    99,    54,    -1,    80,    54,    -1,   100,
      55,    79,    -1,     6,    -1,   100,    56,     6,    -1,    -1,
      84,   102,    -1,   103,    -1,   102,   103,    -1,    -1,    -1,
       6,    51,   104,    81,    53,    49,   105,   106,    50,    -1,
      84,    97,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned char
yy::Parser::prhs_[] =
{
       0,     0,     3,     4,     7,    10,    13,    15,    17,    18,
      22,    23,    27,    29,    30,    34,    38,    39,    47,    48,
      55,    56,    63,    64,    72,    74,    76,    85,    94,   101,
     103,   105,   107,   109,   111,   113,   115,   117,   120,   122,
     127,   128,   130,   132,   136,   138,   139,   142,   143,   148,
     149,   154,   155,   160,   161,   166,   167,   172,   173,   178,
     179,   184,   185,   190,   191,   196,   198,   202,   204,   208,
     210,   213,   216,   219,   223,   225,   229,   230,   233,   235,
     238,   239,   240,   250
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
const unsigned short
yy::Parser::rline_[] =
{
       0,   160,   160,   161,   163,   165,   169,   171,   176,   175,
     182,   181,   189,   196,   199,   209,   217,   216,   230,   229,
     254,   253,   282,   281,   298,   305,   312,   323,   334,   345,
     351,   356,   361,   366,   371,   376,   381,   383,   387,   391,
     397,   398,   402,   404,   408,   417,   418,   423,   422,   428,
     427,   433,   432,   438,   437,   443,   442,   448,   447,   453,
     452,   458,   457,   468,   467,   475,   477,   481,   485,   501,
     503,   507,   509,   513,   526,   531,   542,   543,   547,   549,
     554,   560,   553,   570
};
#endif

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
yy::Parser::TokenNumberType
yy::Parser::translate_ (int token)
{
  static
  const TokenNumberType
  translate_[] =
  {
         0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    53,    45,    43,    52,    44,    56,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    54,
       2,    55,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    47
  };
  if ((unsigned) token <= user_token_number_max_)
    return translate_[token];
  else
    return undef_token_;
}

const int yy::Parser::eof_ = 0;
const int yy::Parser::last_ = 140;
const int yy::Parser::nnts_ = 50;
const int yy::Parser::empty_ = -2;
const int yy::Parser::final_ = 2;
const int yy::Parser::terror_ = 1;
const int yy::Parser::errcode_ = 256;
const int yy::Parser::ntokens_ = 57;
const int yy::Parser::initdepth_ = 200;

const unsigned yy::Parser::user_token_number_max_ = 298;
const yy::Parser::TokenNumberType yy::Parser::undef_token_ = 2;

#line 574 "parser.y"


void psl_error (const char* pkcTEXT)
{

  GOM.error() << std::endl << TScenePsl::_tInputFileName << "(" << TScenePsl::_dwLineNumber << ") Error: " << pkcTEXT << std::endl;

}  /* psl_error() */


void PSL_InitParser (void)
{

  if ( DEBUG_CODE )
  {
    _tDebugCodeFile.open ((TScenePsl::_tInputFileName + ".code").c_str());
  }

  InitObjects();

  _ptWorld = new TAggregate();

  TScenePsl::_ptParsedScene->setWorld (_ptWorld);

  _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
  _tCurrentEvent    = EVENT_INIT_VARIABLES;
  SET_CURRENT_CODE();
  
}  /* PSL_InitParser() */


void PSL_CloseParser (void)
{

  if ( DEBUG_CODE )
  {
    _tDebugCodeFile.close();
  }

  TScenePsl::_ptParsedScene->globalData()->printDebug();

  _tObjectMap.clear();

}  /* PSL_CloseParser() */


void InitObjects (void)
{
}  /* InitObjects() */


void AddVariable (const std::string& rktNAME)
{

  TVarReference   tRef;

  if ( _eVarScope == FX_GLOBAL_SCOPE )
  {
    tRef = tHeapManager.addVariable (_eVarType);
    
    TScenePsl::_ptParsedScene->globalData()->addVariable (rktNAME, tRef);
  }
  else if ( _eVarScope == FX_OBJECT_SCOPE )
  {
  }
  else
  {
  }

}  /* AddVariable() */


void AddInstruction (EInstructionCode eCODE)
{

  /*
  TInstruction   tInst;

  tInst.eCode  = eCODE;
  tInst.eType  = eTYPE;
  tInst.nParam = nPARAM;

  _ptCurrentEvent->push_back (tInst);
  */
  
}  /* AddInstruction() */


string DefaultClass (const std::string& rktTYPE)
{

  if ( rktTYPE == "Renderer" )
  {
    return "Raytracer";
  }
  else if ( rktTYPE == "ObjectFilter" )
  {
    return "";
  }
  else if ( rktTYPE == "ImageFilter" )
  {
    return "";
  }
  else if ( rktTYPE == "Material" )
  {
    return "Material";
  }
  else if ( rktTYPE == "Bsdf" )
  {
    return "BsdfPhong";
  }
  else if ( rktTYPE == "Light" )
  {
    return "PointLight";
  }
  else if ( rktTYPE == "Camera" )
  {
    return "PinholeCamera";
  }
  else if ( rktTYPE == "Object" )
  {
    return "";
  }
  else if ( rktTYPE == "Aggregate" )
  {
    return "Aggregate";
  }
  else
  {
    psl_error ("cannot use a simple type in define");
    exit (1);
  }

}  /* DefaultClass */


TProcedural* NewObject (const std::string& rktCLASS, const TProcedural* pktPARENT)
{

  TProcedural*   ptChild;

//  GOM.debug() << "New object : \"" << rktCLASS << "\"" << std::endl;
  
  ptChild = (TProcedural*) TClassManager::_newObject (rktCLASS, pktPARENT);
  if ( !ptChild )
  {
    std::string   tMessage = std::string ("class ") + rktCLASS + " does not exist";
    psl_error (tMessage.c_str());
    exit (1);
  }

  return ptChild;

}  /* NewObject() */


void* UpdateObject (const std::string& rktNAME)
{

  TProcedural*   ptObject = _tDataStack.POP();

  _tObjectMap [rktNAME] = ptObject;

  return ptObject;

}  /* UpdateObject() */


void DefineObject (const std::string& rktNAME, const std::string& rktCLASS, const std::string& rktDEF_CLASS)
{

//  GOM.debug() << "Defining object : \"" << rktNAME << "\", \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << std::endl;

  if ( rktNAME == "" )
  {
    psl_error ("defined object cannot be unnamed");
    exit (1);
  }

  if ( _tObjectMap.find (rktNAME) != _tObjectMap.end() )
  {
    psl_error ("cannot redefine an existing object");
    exit (1);
  }

  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* DefineObject() */


void CreateObject (const std::string& rktCLASS, const std::string& rktDEF_CLASS)
{

//  GOM.debug() << "Creating object : \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << std::endl;
  
  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* CreateObject() */


EAttribType GetTypeCode (const std::string& rktNAME)
{

  if ( rktNAME == "Real" )
  {
    return FX_REAL;
  }
  else if ( rktNAME == "Bool" )
  {
    return FX_BOOL;
  }
  else if ( rktNAME == "String" )
  {
    return FX_STRING;
  }
  else if ( rktNAME == "Color" )
  {
    return FX_COLOR;
  }
  else if ( rktNAME == "Vector" )
  {
    return FX_VECTOR;
  }
  else if ( rktNAME == "Vector2" )
  {
    return FX_VECTOR2;
  }
  else if ( rktNAME == "Image" )
  {
    return FX_IMAGE;
  }
  else if ( rktNAME == "Bsdf" )
  {
    return FX_BSDF;
  }
  else if ( rktNAME == "Camera" )
  {
    return FX_CAMERA;
  }
  else if ( rktNAME == "Light" )
  {
    return FX_LIGHT;
  }
  else if ( rktNAME == "Material" )
  {
    return FX_MATERIAL;
  }
  else if ( rktNAME == "Renderer" )
  {
    return FX_RENDERER;
  }
  else if ( rktNAME == "Object" )
  {
    return FX_OBJECT;
  }
  else if ( rktNAME == "Aggregate" )
  {
    return FX_AGGREGATE;
  }
  else if ( rktNAME == "ObjectFilter" )
  {
    return FX_OBJECT_FILTER;
  }
  else if ( rktNAME == "ImageFilter" )
  {
    return FX_IMAGE_FILTER;
  }

  return FX_NONE;

}  /* GetTypeCode() */

