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
      for (unsigned short i = prhs_[n_];
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
        case 2:
#line 202 "parser.y"
    {
			    report_reduction("everything <-- nothing");
			  }
    break;

  case 3:
#line 206 "parser.y"
    {
			    report_reduction("everything <-- everything definition");
			  }
    break;

  case 4:
#line 212 "parser.y"
    {
			    report_reduction("statement <-- definition");
			  }
    break;

  case 5:
#line 216 "parser.y"
    {
			    report_reduction("statement <-- expression ';'");
			    if( rt_exec_ok() )
			    {
			      magic_pointer<TAttribObject> ptobj = get_object(semantic_stack_[1].ptAttribute);
			      if( !!ptobj )
			      {
				magic_pointer<TObject> obj = ptobj->tValue;
				if( !!obj )
				{
				  if( !WORLD->containsObject( obj ) )
				  {
				    GOM.debug() << "Adding instance of " << obj->className() << " to world." << endl;
				    WORLD->add ( obj );
				  }
				}
			      }
			      else
			      {
				magic_pointer<TProcedural> proc = get_procedural_var(semantic_stack_[1].ptAttribute, false);
				if( !!proc )
				{
				  FIXME("Potentially add procedural variable instance (" + semantic_stack_[1].ptAttribute->toString() + " to the global scene");
				}
			      }			      
			    } // exec ok.
			  }
    break;

  case 6:
#line 244 "parser.y"
    {
			    report_reduction("statement <-- simple_if_statement");
			  }
    break;

  case 7:
#line 250 "parser.y"
    {
			   report_reduction("statement_list <-- statement");
			 }
    break;

  case 8:
#line 254 "parser.y"
    {
			   report_reduction("statement_list <-- statement_list statement");
			 }
    break;

  case 9:
#line 261 "parser.y"
    {
			    report_reduction("if_head (start) <-- if ( expression )");

			    if( rt_exec_ok() )
			    {			    
			      bool b = check_get_bool(semantic_stack_[1].ptAttribute);
			      rt_enter_condition(b);
			    }
			    else
			    {
			      rt_enter_condition(false);
			    }
			  }
    break;

  case 10:
#line 275 "parser.y"
    {
			    report_reduction("if_head (cont) <-- if ( expression ) simple_if_body");
			    rt_leave_condition();
			    if( rt_exec_ok() )
			    {			    
			      yyval.gValue = check_get_bool(semantic_stack_[3].ptAttribute);
			    }
			    else
			    {
			      yyval.gValue = true; // Forces any else clause to be false.
			    }
                          }
    break;

  case 11:
#line 290 "parser.y"
    {
			    /* Nothing to do... */			    
			    report_reduction("simple_if_statement <-- if_head");
			  }
    break;

  case 12:
#line 295 "parser.y"
    {
			    report_reduction("simple_if_statement (start) <-- if_head ELSE");
			    rt_enter_condition(!semantic_stack_[1].gValue);
                          }
    break;

  case 13:
#line 300 "parser.y"
    {
			    report_reduction("simple_if_statement (start) <-- if_head ELSE simple_if_body");
			    rt_leave_condition();
                          }
    break;

  case 14:
#line 307 "parser.y"
    {
			   report_reduction("simple_if_body <-- definition");
			 }
    break;

  case 15:
#line 311 "parser.y"
    {
			   report_reduction("simple_if_body <-- { }");
			 }
    break;

  case 16:
#line 315 "parser.y"
    {
			   report_reduction("simple_if_body <-- { statement_list }");
			 }
    break;

  case 17:
#line 319 "parser.y"
    {
			   report_reduction("simple_if_body <-- { error }");
			   rt_error("expected statement list or nothing");
                         }
    break;

  case 18:
#line 327 "parser.y"
    {
			    report_reduction("definition <-- DEFINE name expression ;");
			    report_reduction(string("definition <-- DEFINE ") +
					     semantic_stack_[2].sIdent + " " + semantic_stack_[1].ptAttribute->toString());

			    if( rt_exec_ok() )
			    {
			      if( DATAMAP.find(semantic_stack_[2].sIdent) != DATAMAP.end() )
			      {
				rt_warning(string(semantic_stack_[2].sIdent) + " redefined here");
				rt_warning("previously defined here: " + DATAMAP[semantic_stack_[2].sIdent].first);
			      }
			      GOM.debug() << "Defining \"" << string(semantic_stack_[2].sIdent) << "\"" << endl;
			      
			      char buffer[1024];
			      sprintf(buffer,"%s line %d",
				      TSceneRT::_tInputFileName.c_str(),
				      int(TSceneRT::_dwLineNumber));
			      DATAMAP[semantic_stack_[2].sIdent] = pair<string,attrib_type>(string(buffer),semantic_stack_[1].ptAttribute);
			    } // exec ok.
			  }
    break;

  case 19:
#line 349 "parser.y"
    {
			    report_reduction("definition <-- REDEFINE name expression ;");
			    report_reduction(string("definition <-- DEFINE ") +
					     semantic_stack_[2].sIdent + " " + semantic_stack_[1].ptAttribute->toString());

			    if( rt_exec_ok() )
			    {
			      // Uncomment the below (and modify) to display
			      // warnings (invert the comparision). 
			      /*
			      if( DATAMAP.find($2) != DATAMAP.end() )
			      {
				rt_warning(string($2) + " redefined here");
				rt_warning("previously defined here: " + DATAMAP[$2].first);
			      }
			      */
			      GOM.debug() << "Defining \"" << string(semantic_stack_[2].sIdent) << "\"" << endl;
			      
			      char buffer[1024];
			      sprintf(buffer,"%s line %d",
				      TSceneRT::_tInputFileName.c_str(),
				      int(TSceneRT::_dwLineNumber));
			      DATAMAP[semantic_stack_[2].sIdent] = pair<string,attrib_type>(string(buffer),semantic_stack_[1].ptAttribute);
			    } // exec ok.
			  }
    break;

  case 20:
#line 375 "parser.y"
    {
			    report_reduction("definition <-- DEFINE reserved_words name instance");
			    if( rt_exec_ok() )
			    {
			      cerr << "Warning: definition on line "
				   << TSceneRT::_dwLineNumber
				   << " should not have \"" << semantic_stack_[3].sIdent << "\" anymore"
				   << endl;
			      
			      if( DATAMAP.find(semantic_stack_[2].sIdent) != DATAMAP.end() )
			      {
				rt_warning(string(semantic_stack_[2].sIdent) + " redefined here");
				rt_warning("previously defined here: " + DATAMAP[semantic_stack_[2].sIdent].first);
			      }
			      char buffer[1024];
			      sprintf(buffer,"%s line %d",
				      TSceneRT::_tInputFileName.c_str(),
				      int(TSceneRT::_dwLineNumber));
			      DATAMAP[semantic_stack_[3].sIdent] = pair<string,attrib_type>(string(buffer),semantic_stack_[1].ptAttribute);
			    } // exec ok.
			  }
    break;

  case 21:
#line 399 "parser.y"
    {
			    report_reduction("instance <-- name");
			    report_reduction(string("instance <-- ") + semantic_stack_[0].sIdent);			    
			    yyval.ptAttribute = Instance(semantic_stack_[0].sIdent);
                          }
    break;

  case 22:
#line 405 "parser.y"
    {
			    //			    GOM.debug() << "Creating object..." << endl;
			    CreateObject(semantic_stack_[0].sIdent,"");
                          }
    break;

  case 23:
#line 410 "parser.y"
    {
			    report_reduction("instance <--  class { params }");
			    report_reduction(string("instance <-- ") + DATA->toString());
			    
			    //			    GOM.debug() << "Type is " << DATA->AttributeName() << endl;
			    yyval.ptAttribute = DATASTACK.POP();
			  }
    break;

  case 24:
#line 420 "parser.y"
    {
			    report_reduction("param_block <-- { params }");
			  }
    break;

  case 25:
#line 424 "parser.y"
    {
			    report_reduction("param_block <-- { }");
			  }
    break;

  case 26:
#line 431 "parser.y"
    {
			    yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			    report_reduction("expression <-- prec_8");
			    report_reduction("expression <-- " + semantic_stack_[0].ptAttribute->toString());
                          }
    break;

  case 27:
#line 437 "parser.y"
    {
			   report_reduction("expression <-- error");
			   if( rt_exec_ok() )
			   {			   
			     rt_error("expected expression");
			   }
			   yyval.ptAttribute = (user_arg_type)new TAttribute();
                         }
    break;

  case 28:
#line 449 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 29:
#line 455 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_8 OR prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[2].ptAttribute->toString() + " OR " + semantic_stack_[0].ptAttribute->toString());
			  if( rt_exec_ok() )
			  {			  
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) ||
								check_get_bool(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 30:
#line 472 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 31:
#line 478 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_7 AND prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[2].ptAttribute->toString() + " AND " + semantic_stack_[0].ptAttribute->toString());
			  if( rt_exec_ok() )
			  {			  			  
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) &&
								check_get_bool(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 32:
#line 496 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_5");
			  report_reduction("prec_6 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 33:
#line 502 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_6 EQUAL prec_5");
			  if( rt_exec_ok() )
			  {			  			  
			    if( !types_match(semantic_stack_[2].ptAttribute, semantic_stack_[0].ptAttribute ) )
			    {
			      rt_error( ("Cannot convert " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) +
					 " to " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType)) );
			    }
			    if( semantic_stack_[2].ptAttribute->eType == FX_REAL )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) == check_get_real(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_BOOL )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) ==
								  check_get_bool(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_VECTOR )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector(semantic_stack_[2].ptAttribute)->tValue ==
								  get_vector(semantic_stack_[0].ptAttribute)->tValue);
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_VECTOR2 )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector2(semantic_stack_[2].ptAttribute)->tValue ==
								  get_vector2(semantic_stack_[0].ptAttribute)->tValue);
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_STRING || semantic_stack_[2].ptAttribute->eType == FX_STRING_LIST )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_string(semantic_stack_[2].ptAttribute) ==
								  check_get_string(semantic_stack_[0].ptAttribute));	  
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_INTEGER )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_int(semantic_stack_[2].ptAttribute)->tValue ==
								  get_int(semantic_stack_[0].ptAttribute)->tValue);	  
			    }			  
			    else
			    {
			      rt_error("I can't compare a " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) + " and a " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType));
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 34:
#line 551 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_6 NOT_EQ prec_5");
			  if( rt_exec_ok() )
			  {			  			  
			    if( !types_match(semantic_stack_[2].ptAttribute, semantic_stack_[0].ptAttribute ) )
			    {
			      rt_error( ("Cannot convert " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) +
					 " to " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType)) );
			    }
			    if( semantic_stack_[2].ptAttribute->eType == FX_REAL )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) !=
								  check_get_real(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_BOOL )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) !=
								  check_get_bool(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_VECTOR )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector(semantic_stack_[2].ptAttribute) != get_vector(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_VECTOR2 )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector2(semantic_stack_[2].ptAttribute) != get_vector2(semantic_stack_[0].ptAttribute));
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_STRING || semantic_stack_[2].ptAttribute->eType == FX_STRING_LIST )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_string(semantic_stack_[2].ptAttribute) != check_get_string(semantic_stack_[0].ptAttribute));	  
			    }
			    else if( semantic_stack_[2].ptAttribute->eType == FX_INTEGER )
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribBool(get_int(semantic_stack_[2].ptAttribute)->tValue == get_int(semantic_stack_[0].ptAttribute)->tValue);	  
			    }
			    else
			    {
			      rt_error("I can't compare a " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType));
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 35:
#line 600 "parser.y"
    {
			  report_reduction("prec_5 <-- prec_4");
			  report_reduction("prec_5 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 36:
#line 607 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 >= prec_5");
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) >= check_get_real(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 37:
#line 619 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 > prec_5");
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) > check_get_real(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 38:
#line 631 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 <= prec_5");
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) <= check_get_real(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 39:
#line 643 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 < prec_5");
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) < check_get_real(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 40:
#line 658 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 41:
#line 664 "parser.y"
    {

			  report_reduction("prec_4 <-- prec_4 + prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " + " + semantic_stack_[0].ptAttribute->toString());
			  if( rt_exec_ok() )
			  { 
			    yyval.ptAttribute = add(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			    if( !yyval.ptAttribute )
			    {
			      rt_error("addition of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				       " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(0);
			  }
			}
    break;

  case 42:
#line 683 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_4 - prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " - " + semantic_stack_[0].ptAttribute->toString());			  
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = sub(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			    if( !yyval.ptAttribute )
			    {
			      rt_error("subtraction of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				       " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(0);
			  }
			}
    break;

  case 43:
#line 704 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_2");
			  report_reduction("prec_3 <-- " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 44:
#line 710 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_3 * prec_2");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " * " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = mul(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			    if( !yyval.ptAttribute )
			    {
			      rt_error("multiplication of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				       " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(0);
			  }
			}
    break;

  case 45:
#line 729 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_3 / prec_2");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " / " + semantic_stack_[0].ptAttribute->toString());			  

			  if( rt_exec_ok() )
			  {			  
			    yyval.ptAttribute = div(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			    if( !yyval.ptAttribute )
			    {
			      rt_error("division of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				       " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(0);
			  }
			}
    break;

  case 46:
#line 751 "parser.y"
    {
			  report_reduction("prec_2 <-- prec_1");
			  report_reduction("prec_2 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 47:
#line 757 "parser.y"
    {
			  report_reduction("prec_2 <-- ! prec_2");
			  report_reduction("prec_2 <-- ! " + semantic_stack_[0].ptAttribute->toString());
			  if( rt_exec_ok() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(!check_get_bool(semantic_stack_[0].ptAttribute));
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 48:
#line 770 "parser.y"
    {
			  report_reduction("prec_2 <-- + prec_2");
			  report_reduction("prec_2 <-- + " + semantic_stack_[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 49:
#line 777 "parser.y"
    {
			  report_reduction("prec_2 <-- - prec_2");
			  report_reduction("prec_2 <-- - " + semantic_stack_[0].ptAttribute->toString());

			  if( rt_exec_ok() )
			  {			  
			    if( semantic_stack_[0].ptAttribute->eType != FX_ARRAY )
			    {
			      yyval.ptAttribute = sub((user_arg_type)new TAttribInt(0), semantic_stack_[0].ptAttribute);
			      if( !yyval.ptAttribute )
			      {
				rt_error("negation of " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			      }
			    }
			    else
			    {
			      magic_pointer<TAttribArray> tar = rcp_static_cast<TAttribArray>(semantic_stack_[0].ptAttribute);
			      vector<TScalar> barf(tar->tValue);
			      
			      for(unsigned i = 0; i < barf.size(); ++i)
			      {
				barf[i] = -barf[i];
			      }
			      yyval.ptAttribute = (user_arg_type)new TAttribArray(barf);
			    }
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(0);
			  }
			}
    break;

  case 50:
#line 813 "parser.y"
    {
			  report_reduction("prec_1 <-- quoted_string");
			  report_reduction("prec_1 <-- \"" + string(semantic_stack_[0].sIdent) + "\"");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribString(semantic_stack_[0].sIdent);
			}
    break;

  case 51:
#line 820 "parser.y"
    {
			  report_reduction("prec_1 <-- PARAM prec_1");
			  
			  FIXME("recovering a command line paramater (how?)");
			}
    break;

  case 52:
#line 826 "parser.y"
    {
			  report_reduction("prec_1 <-- DEFINED name");

			  if( DATAMAP.find(semantic_stack_[0].sIdent) != DATAMAP.end() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(true);
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			}
    break;

  case 53:
#line 839 "parser.y"
    {
			  report_reduction("prec_1 <-- BOOL");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(semantic_stack_[0].gValue);
			}
    break;

  case 54:
#line 845 "parser.y"
    {
			  report_reduction("prec_1 <-- INTEGER");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribInt(semantic_stack_[0].iValue);
			}
    break;

  case 55:
#line 851 "parser.y"
    {
			    report_reduction("prec_1 <-- REAL");
			    
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(semantic_stack_[0].dValue);
                          }
    break;

  case 56:
#line 858 "parser.y"
    {
			  report_reduction("prec_1 <-- ( expression )");
			  report_reduction("prec_1 <-- ( " + semantic_stack_[1].ptAttribute->toString() + " )");

			  yyval.ptAttribute = semantic_stack_[1].ptAttribute;
			}
    break;

  case 57:
#line 865 "parser.y"
    {
			  report_reduction("prec_1 <-- color");
			  yyval.ptAttribute = (user_arg_type)new TAttribColor(*semantic_stack_[0].ptColor);
			}
    break;

  case 58:
#line 870 "parser.y"
    {
			  report_reduction("prec_1 <-- THIS");
			  yyval.ptAttribute = DATA;
			}
    break;

  case 59:
#line 875 "parser.y"
    {
			  report_reduction("prec_1 <-- instance");
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;			  
                        }
    break;

  case 60:
#line 880 "parser.y"
    {
			  report_reduction("prec_1 <-- function_call");
                        }
    break;

  case 61:
#line 884 "parser.y"
    {
			  report_reduction("prec_1 <-- any_vector");
                        }
    break;

  case 62:
#line 892 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( )");
			  report_reduction("(detail) function_call <-- " + string(semantic_stack_[2].sIdent) +  "( )");
			    
			  if( rt_exec_ok() )
			  {
			    
#if defined(DEBUG_IT)
			    rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			    
			    // Lookup using all objects in the current stack,
			    // then check the global table... 
			    TUserFunctionMap functions = all_user_functions();
			    
			    if( functions.find(semantic_stack_[2].sIdent) != functions.end() )
			    {
			      user_arg_vector empty_args;
			      yyval.ptAttribute = functions[semantic_stack_[2].sIdent]->call(empty_args);
			    }
			    else
			    {
			      rt_error("function " + string(semantic_stack_[2].sIdent) + " does not exist");
			      yyval.ptAttribute = (user_arg_type)new TAttribute();
			    }
			  } // exec ok
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }
			}
    break;

  case 63:
#line 924 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression )");
			  report_reduction("(detail) function_call <-- " + string(semantic_stack_[3].sIdent) + "( " + semantic_stack_[1].ptAttribute->toString() + " )");
			  
			  if( rt_exec_ok() )
			  {			    
#if defined(DEBUG_IT)
			    rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			    
			    // Lookup using all objects in the current stack,
			    // then check the global table...
			    TUserFunctionMap functions = all_user_functions();
			    
			    if( functions.find(semantic_stack_[3].sIdent) != functions.end() )
			    {
			      user_arg_vector args;
			      args.push_back(semantic_stack_[1].ptAttribute);
			      yyval.ptAttribute = functions[semantic_stack_[3].sIdent]->call(args);
			      
			    }
			    else
			    {
			      rt_error("function " + string(semantic_stack_[3].sIdent) + " does not exist");
			      yyval.ptAttribute = (user_arg_type)new TAttribute();
			    }			    
			  } // exec ok.
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }			  
			}
    break;

  case 64:
#line 957 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression , expression )");
			  report_reduction("(detail) function_call <-- " + string(semantic_stack_[5].sIdent) + "( " + semantic_stack_[3].ptAttribute->toString() + "," + semantic_stack_[1].ptAttribute->toString() + " )");
			    
			  if( rt_exec_ok() )
			  {
#if defined(DEBUG_IT)
			    rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			    
			    // Lookup using all objects in the current stack,
			    // then check the global table...
			    TUserFunctionMap functions = all_user_functions();
			    
			    if( functions.find(semantic_stack_[5].sIdent) != functions.end() )
			    {
			      user_arg_vector args;
			      args.push_back(semantic_stack_[3].ptAttribute);
			      args.push_back(semantic_stack_[1].ptAttribute);			    
			      yyval.ptAttribute = functions[semantic_stack_[5].sIdent]->call(args);
			      
			    }
			    else
			    {
			      rt_error("function " + string(semantic_stack_[5].sIdent) + " does not exist");
			      yyval.ptAttribute = (user_arg_type)new TAttribute();
			    }			    
			  } // exec ok.
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }			  
			}
    break;

  case 65:
#line 991 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression , expression , expression )");
			  report_reduction("(detail) function_call <-- " + string(semantic_stack_[7].sIdent) + "( " + semantic_stack_[5].ptAttribute->toString() + "," + semantic_stack_[3].ptAttribute->toString() + "," + semantic_stack_[1].ptAttribute->toString() + " )");
			  
			  if( rt_exec_ok() )
			  {
#if defined(DEBUG_IT)
			    rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			    
			    // Lookup using all objects in the current stack,
			    // then check the global table...
			    TUserFunctionMap functions = all_user_functions();
			    
			    if( functions.find(semantic_stack_[7].sIdent) != functions.end() )
			    {
			      user_arg_vector args;
			      args.push_back(semantic_stack_[5].ptAttribute);
			      args.push_back(semantic_stack_[3].ptAttribute);
			      args.push_back(semantic_stack_[1].ptAttribute);			      
			      yyval.ptAttribute = functions[semantic_stack_[7].sIdent]->call(args);		      
			    }
			    else
			    {
			      rt_error("function " + string(semantic_stack_[7].sIdent) + " does not exist");
			      yyval.ptAttribute = (user_arg_type)new TAttribute();
			    }			    
			  } // exec ok.
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }			  
			}
    break;

  case 66:
#line 1027 "parser.y"
    {
			    report_reduction("color <-- { RED expression GREEN expression BLUE expression }");
			    report_reduction("color <-- { RED " + semantic_stack_[5].ptAttribute->toString() +
					     " GREEN " + semantic_stack_[3].ptAttribute->toString() +
					     " BLUE " + semantic_stack_[1].ptAttribute->toString() + " }");
			    if( rt_exec_ok() )
			    {
			      double r = check_get_real(semantic_stack_[5].ptAttribute);
			      double g = check_get_real(semantic_stack_[3].ptAttribute);
			      double b = check_get_real(semantic_stack_[1].ptAttribute);
			      
			      GOM.debug() << "r=" << r << " g=" << g << " b=" << b << endl;
			      TColor* c = new TColor(r,g,b);
			      GOM.debug() << "Here's what was really created: ";
			      c->printDebug(""); cerr << endl;
			      
			      yyval.ptColor = magic_pointer<TColor>(c);
			    }
			    else
			    {
			      yyval.ptColor = magic_pointer<TColor>(new TColor());
			    }
			  }
    break;

  case 67:
#line 1053 "parser.y"
    {
			    report_reduction("any_vector <-- < vector_insides >");
			    yyval.ptAttribute = semantic_stack_[1].ptAttribute;
                          }
    break;

  case 68:
#line 1066 "parser.y"
    {
			    report_reduction("vector_insides <-- expression");
			    if( rt_exec_ok() )
			    {			    
			      double e = check_get_real(semantic_stack_[0].ptAttribute);
			      yyval.ptAttribute = (user_arg_type)new TAttribArray(e);
			    }
			    else
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribArray(double(0));
			    }
			  }
    break;

  case 69:
#line 1079 "parser.y"
    {
			    report_reduction("vector_insides <-- vector_insides ',' expression");
			    if( rt_exec_ok() )
			    {			    
			      if( semantic_stack_[2].ptAttribute->eType == FX_ARRAY )
			      {
				double e = check_get_real(semantic_stack_[0].ptAttribute);
				rcp_static_cast<TAttribArray>(semantic_stack_[2].ptAttribute)->tValue.push_back(e);
				yyval.ptAttribute = semantic_stack_[2].ptAttribute;
			      }
			      else
			      {
				rt_error("lhs of ',' was not part of an array.");
			      }
			    }
			    else
			    {
			      yyval.ptAttribute = (user_arg_type)new TAttribArray(0);
			    }
			  }
    break;

  case 70:
#line 1110 "parser.y"
    {
			    report_reduction("name <-- IDENTIFIER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 71:
#line 1124 "parser.y"
    {
			    report_reduction("class <-- : EXTENDS IDENTIFIER");

			    if( rt_exec_ok() )
			    {			    
			      if ( DATAMAP.find (semantic_stack_[0].sIdent) == DATAMAP.end() )
			      {
				rt_error ("trying to extend from non existing object");
				exit (1);
			      }
			      
			      // GOM.debug() << "the type of the parent is " << DATAMAP [$1].second->AttributeName() << endl;
			      PARENT_OBJECT = attr_to_base(DATAMAP [semantic_stack_[0].sIdent].second);
			      // GOM.debug() << "the parent's classname is " << PARENT_OBJECT->className() << endl;
			      yyval.sIdent = PARENT_OBJECT->className();
			    }
			    else
			    {
			      yyval.sIdent = "none";
			    }
			  }
    break;

  case 72:
#line 1146 "parser.y"
    {
			    report_reduction("class <-- : CLASS IDENTIFIER");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 73:
#line 1152 "parser.y"
    {
			    report_reduction("class <-- : CLASS string_math");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 74:
#line 1161 "parser.y"
    {
			    report_reduction("string_math <-- : QUOTED_STRING");
			    yyval.sIdent = semantic_stack_[0].sIdent;
                          }
    break;

  case 75:
#line 1166 "parser.y"
    {
			    report_reduction("string_math <-- : function_call");
			    if( rt_exec_ok() )
			    {			    
			      yyval.sIdent = check_get_string(semantic_stack_[0].ptAttribute);
			    }
			    else
			    {
			      yyval.sIdent = "";
			    }
			  }
    break;

  case 76:
#line 1178 "parser.y"
    {
			    report_reduction("string_math <-- : string_math + QUOTED_STRING");
			    yyval.sIdent = semantic_stack_[2].sIdent + semantic_stack_[0].sIdent;
			  }
    break;

  case 77:
#line 1183 "parser.y"
    {
			    report_reduction("string_math <-- : string_math + function_call");
			    if( rt_exec_ok() )
			    {			    
			      yyval.sIdent = semantic_stack_[2].sIdent + check_get_string(semantic_stack_[0].ptAttribute);
			    }
			    else
			    {
			      yyval.sIdent = "";
			    }
			  }
    break;

  case 78:
#line 1202 "parser.y"
    {
			  report_reduction("params <-- param ;");
                        }
    break;

  case 79:
#line 1206 "parser.y"
    {
			  report_reduction("params <-- param_if_statement");
                        }
    break;

  case 80:
#line 1210 "parser.y"
    {
			  report_reduction("params <-- params param ;");
			}
    break;

  case 81:
#line 1214 "parser.y"
    {
			  report_reduction("params <-- params param_if_statement");
                        }
    break;

  case 82:
#line 1220 "parser.y"
    {
			  report_reduction("param <-- IDENTIFIER = expression");
			  if( rt_exec_ok() )
			  {
			    SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);
			  } // exec ok.
			}
    break;

  case 83:
#line 1228 "parser.y"
    {
			  report_reduction("param <-- expression");

			  if( rt_exec_ok() )
			  {
			    magic_pointer<TAttribObject> ptobj = get_object(semantic_stack_[0].ptAttribute);
			    
			    // If it is an object, check to see if there is an
			    // 'addObject' function in the current object. 
			    if( !!ptobj  && !!ptobj->tValue )
			    {
			      
			      magic_pointer<TAttribute> attr = DATASTACK.top();
			      if( !!attr )
			      {
				magic_pointer<TProcedural> proc = get_procedural_var(attr);
				
				if( !!proc )
				{
				  TUserFunctionMap functions = proc->getUserFunctions();
				  if( functions.find("addObject") !=
				      functions.end() )
				  {
				    user_arg_vector args;
				    args.push_back (semantic_stack_[0].ptAttribute);
				    
				    functions["addObject"]->call(args);
				    
				    static bool warned = false;
				    if( !warned )
				    {
				      rt_warning("DEPRECATION: adding instance of " +
						 ptobj->tValue->className() +
						 " to the current object (likely aggregate or CSG) instead of ignoring it.  This feature may soon be removed.");
				      warned = true;
				    }
				  }
				}
			      }
			    }
			    else
			    {
			      magic_pointer<TProcedural> proc = get_procedural_var(semantic_stack_[0].ptAttribute, false);
			      if( !!proc )
			      {
				FIXME("Potentially do something with the procedural variable (" + semantic_stack_[0].ptAttribute->toString() + ") in the current object");
			      }
			    }
			  } // exec ok
			}
    break;

  case 84:
#line 1279 "parser.y"
    {
			  report_reduction("param <-- reserved_words = expression");
			  if( rt_exec_ok() )
			  {
			    SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);
			  } // exec ok.
			}
    break;

  case 85:
#line 1287 "parser.y"
    {
			  report_reduction("param <-- object_param");
			}
    break;

  case 86:
#line 1291 "parser.y"
    {
			  report_reduction("param <-- scene_param");
			}
    break;

  case 87:
#line 1297 "parser.y"
    {
			  // If an object, object->addFilter.
			  // If a scene, scene->addImageFilter
			  report_reduction("object_param <-- FILTER = instance");

			  if( rt_exec_ok() )
			  {
			    // The object will clone this filter (a good idea?)
			    // The alternative was to either:
			    // 1) Use a magic pointer for the filter.
			    // 2) Maintain a list of all object filters for
			    //    proper deletion/deallocation. 
			    //			    OBJECT->addFilter ($2.get_pointer());
			    
			    magic_pointer<TObject> obj = check_get_object(DATASTACK.top());
			    magic_pointer<TScene> scene = check_get_scene(DATASTACK.top());
			    if( !!obj )
			    {
			      // Do it (obj->addFilter)
			      FIXME("object filters need work");
			    }
			    else if ( scene )
			    {
			      // Do it (scene->addImageFilter)
			      FIXME("image filters need work");
			    }
			    else
			    {
			      SetParameter(semantic_stack_[2].sIdent,semantic_stack_[0].ptAttribute);
			    }
			  } // exec ok.
			}
    break;

  case 88:
#line 1333 "parser.y"
    {
			  report_reduction("scene_param <-- LIGHT = instance");
			  if( rt_exec_ok() )
			  {
			    // This is no longer needed, as there are special
			    // cases for this in the light_instance rule.
			    if( !!semantic_stack_[0].ptAttribute )
			    {
			      static bool gave_warning = false;
			      
			      if(!gave_warning)
			      {
				GOM.error() << "Note for light instance on line "
					    << TSceneRT::_dwLineNumber
					    << endl;
				GOM.error() << "  Usage of lights in the 'scene' section is no longer required" << endl;
				GOM.error() << "  They may now be added to aggregates, csg, etc., or used "
					    << endl
					    << "  external to the scene section (same syntax)." 
					    << endl;
				gave_warning = true;
			      }
			      
			      magic_pointer<TObject> obj = check_get_object(semantic_stack_[0].ptAttribute);
			      if( !!obj )
			      {
				if( !WORLD->containsObject( obj ) )
				{
				  WORLD->add ( obj );
				}
				// The following does not work anymore, as lights
				// added in this manor do not go through the
				// re-translation process.  Check to see if it
				// breaks anything!
				// SCENE->addLight (rcp_static_cast<TLight>(obj)->clone_new());
			      }
			      else
			      {
				rt_error("NULL light given (BUG?)");
			      }
			    }
			  } // exec ok.
			}
    break;

  case 89:
#line 1377 "parser.y"
    {
			  report_reduction("scene_param <-- OUTPUT = instance");
			  if( rt_exec_ok() )
			  {
			    FIXME("Image output");
			    magic_pointer<TAttribScene> pscene = get_scene(DATA);
			    if( !!pscene )
			    {
			      //			    magic_pointer<TScene> scene = pscene->tValue;
			      GOM.error() << "Warning: Ignoring locally defined scene" << endl;
			      magic_pointer<TScene> scene = TSceneRT::_ptParsedScene;
			      if( !!scene )
			      {
				magic_pointer<TAttribImageIO> io = get_imageio(semantic_stack_[0].ptAttribute);
				if( !!io )
				{
				  //				GOM.debug() << "Setting image IO to " << io->toString() << endl;
				  scene->setImageOutput (io->tValue);
				}
				else
				{
				  rt_error("Not an image io");
				}
			      }
			      else
			      {
				rt_error("internal: scene is NULL");
			      }
			    }
			    else
			    {
			      SetParameter(semantic_stack_[2].sIdent,semantic_stack_[0].ptAttribute);
			    }
			  } // exec ok.
			}
    break;

  case 90:
#line 1415 "parser.y"
    {
			    /* Nothing to do... */			    
			    report_reduction("param_if_statement <-- if_head");
			  }
    break;

  case 91:
#line 1420 "parser.y"
    {
			    report_reduction("param_if_statement (start) <-- if_head ELSE");
			    rt_enter_condition(!semantic_stack_[1].gValue);
                          }
    break;

  case 92:
#line 1425 "parser.y"
    {
			    report_reduction("param_if_statement (start) <-- if_head ELSE param_if_body");
			    rt_leave_condition();
                          }
    break;

  case 93:
#line 1432 "parser.y"
    {
			    report_reduction("param_if_head (start) <-- if ( expression )");

			    if( rt_exec_ok() )
			    {			    
			      bool b = check_get_bool(semantic_stack_[1].ptAttribute);
			      rt_enter_condition(b);
			    }
			    else
			    {
			      rt_enter_condition(false);
			    }
			  }
    break;

  case 94:
#line 1446 "parser.y"
    {
			    report_reduction("param_if_head (cont) <-- if ( expression ) param_if_body");
			    rt_leave_condition();
			    if( rt_exec_ok() )
			    {			    
			      yyval.gValue = check_get_bool(semantic_stack_[3].ptAttribute);
			    }
			    else
			    {
			      yyval.gValue = true; // Forces any else clause to be false
			    }
                          }
    break;

  case 95:
#line 1461 "parser.y"
    {
			   report_reduction("param_if_body <-- { }");
			 }
    break;

  case 96:
#line 1465 "parser.y"
    {
			   report_reduction("param_if_body <-- { params }");
			 }
    break;

  case 97:
#line 1469 "parser.y"
    {
			   report_reduction("param_if_body <-- { error }");
			   rt_error("expected parameter list or nothing");
                         }
    break;

  case 98:
#line 1476 "parser.y"
    {
			  report_reduction("potential_name <-- name");
			}
    break;

  case 99:
#line 1480 "parser.y"
    {
			  report_reduction("potential_name <-- reserved_words");
			}
    break;

  case 100:
#line 1487 "parser.y"
    {
			    report_reduction("reserved_words <-- BLUE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 101:
#line 1492 "parser.y"
    {
			    report_reduction("reserved_words <-- CLASS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 102:
#line 1497 "parser.y"
    {
			    report_reduction("reserved_words <-- DEFINE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 103:
#line 1502 "parser.y"
    {
			    report_reduction("reserved_words <-- EXTENDS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 104:
#line 1507 "parser.y"
    {
			    report_reduction("reserved_words <-- GREEN");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 105:
#line 1512 "parser.y"
    {
			    report_reduction("reserved_words <-- RED");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 106:
#line 1517 "parser.y"
    {
			    report_reduction("reserved_words <-- RENDERER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;


    }

/* Line 446 of lalr1.cc.  */
#line 1702 "parser.cpp"

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
const short yy::Parser::pact_ninf_ = -127;
const short
yy::Parser::pact_[] =
{
    -127,   175,  -127,  -127,  -127,  -127,  -127,   -32,  -127,  -127,
      20,   117,  -127,  -127,  -127,  -127,   585,    13,    13,  -127,
      -2,   544,   544,   503,    26,   544,   503,  -127,    17,  -127,
    -127,  -127,    14,    38,    47,    49,  -127,    29,    40,  -127,
    -127,  -127,  -127,  -127,    34,  -127,    39,  -127,    45,  -127,
    -127,  -127,  -127,  -127,    46,  -127,   503,    13,  -127,  -127,
     503,   503,  -127,  -127,    62,   503,  -127,  -127,    -3,  -127,
    -127,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,    63,   462,    79,    65,    12,    67,    66,
    -127,    92,   503,  -127,     4,    47,    49,  -127,  -127,    61,
      61,    61,    61,    40,    40,  -127,  -127,   216,  -127,  -127,
     -18,  -127,  -127,  -127,    20,    71,  -127,  -127,  -127,   503,
    -127,   117,   380,  -127,  -127,   -22,    69,    70,    72,    73,
    -127,  -127,   257,    76,  -127,  -127,  -127,    77,    74,  -127,
     503,  -127,     4,   108,    80,  -127,  -127,   421,   503,    12,
      12,    12,   503,  -127,    88,  -127,  -127,  -127,   503,    -4,
    -127,   503,  -127,  -127,  -127,  -127,  -127,  -127,  -127,    91,
    -127,    93,  -127,  -127,   503,    95,  -127,   298,  -127,    98,
    -127,    93,    97,  -127,   339,  -127,  -127,  -127,  -127
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
const unsigned char
yy::Parser::defact_[] =
{
       2,     0,     1,    27,    53,    55,    54,    70,    50,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     3,    11,     6,
       4,    59,     0,    26,    28,    30,    32,    35,    40,    43,
      46,    60,    57,    61,    21,    22,     0,    99,    70,    74,
     101,   102,    75,    98,    73,    70,     0,     0,    51,    52,
       0,     0,    48,    49,     0,     0,    47,    68,     0,    12,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,    67,     0,    29,    31,    33,    34,    37,
      36,    39,    38,    41,    42,    44,    45,     0,    23,    62,
       0,    76,    77,    18,     0,     0,    21,    19,     9,     0,
      69,     0,     0,    13,    14,    70,     0,     0,     0,     0,
      25,    83,     0,     0,    85,    86,    79,    90,    99,    63,
       0,    20,     0,     0,    27,    15,     7,     0,     0,     0,
       0,     0,     0,    24,     0,    81,    78,    91,     0,     0,
      10,     0,    17,    16,     8,    82,    87,    88,    89,     0,
      80,     0,    84,    64,     0,     0,    93,     0,    92,     0,
      66,     0,    27,    95,     0,    65,    94,    97,    96
};

/* YYPGOTO[NTERM-NUM].  */
const signed char
yy::Parser::pgoto_[] =
{
    -127,  -127,  -107,  -127,  -127,  -127,  -127,  -127,   -11,   -86,
     -83,  -127,  -127,    -1,  -127,    78,    68,     8,   -31,    19,
      -9,   122,    -5,  -127,  -127,  -127,    -8,  -127,  -127,   -33,
    -126,  -127,  -127,  -121,  -127,  -127,  -127,   -36,  -127,   -10
};

/* YYDEFGOTO[NTERM-NUM].  */
const short
yy::Parser::defgoto_[] =
{
      -1,     1,    27,   147,    28,   142,    29,    94,   123,    30,
      31,    83,   108,   131,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    68,    44,    45,    54,   132,
     133,   134,   135,   136,   171,   137,   181,   178,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
const short yy::Parser::table_ninf_ = -99;
const short
yy::Parser::table_[] =
{
      32,    57,    53,    56,   115,    52,   154,   -71,   124,    59,
      60,   155,    62,    63,   121,   146,    66,   -71,     7,    55,
     139,   114,    64,   148,   140,    67,    48,    49,     9,    50,
      51,    12,    18,    13,   173,    61,    14,    15,   174,    92,
     164,    93,    65,   122,    99,   100,   101,   102,    69,    87,
      70,    75,    76,    77,    78,    86,   124,    71,   154,    88,
      89,    79,    80,   155,    91,    72,   166,   167,   168,    73,
      74,   -98,   105,   106,    81,    82,    84,    53,    85,   116,
     112,    97,    98,   110,   -72,    55,   111,     9,    50,    51,
      12,   120,    13,    79,    80,    14,    15,   138,   103,   104,
      90,   113,   107,   117,   118,   119,    53,   141,   157,    52,
     152,    57,   156,    56,   149,   150,   161,   151,   143,   158,
     162,    32,   138,    55,   170,     9,    50,    51,    12,   176,
      13,   160,   177,    14,    15,   180,   185,   187,    58,   159,
      96,   116,   116,   116,   184,   186,    32,   165,     0,    95,
       0,   169,     0,     0,     0,     0,     0,   172,     0,     0,
     175,     0,     0,     0,     0,     0,     0,   138,     0,     0,
       0,     0,     0,   179,   138,     2,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     0,    13,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    20,     0,    21,    22,     0,
       0,     0,    23,     0,    24,     0,    25,     3,    26,     4,
       5,     6,   125,     8,     9,    10,    51,    12,   126,    13,
     127,   128,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    17,     0,    19,   129,     0,    21,    22,
       0,     0,     0,    23,     0,    24,   130,    25,     3,    26,
       4,     5,     6,   125,     8,     9,    10,    51,    12,   126,
      13,   127,   128,    14,    15,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    17,     0,    19,   129,     0,    21,
      22,     0,     0,     0,    23,     0,    24,   153,    25,   182,
      26,     4,     5,     6,   125,     8,     9,    10,    51,    12,
     126,    13,   127,   128,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,     0,    19,   129,     0,
      21,    22,     0,     0,     0,    23,     0,    24,   183,    25,
       3,    26,     4,     5,     6,   125,     8,     9,    10,    51,
      12,   126,    13,   127,   128,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    17,     0,    19,   129,
       0,    21,    22,     0,     0,     0,    23,     0,    24,   188,
      25,   144,    26,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,    13,     0,     0,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,     0,    21,    22,     0,     0,     0,    23,     0,    24,
     145,    25,     3,    26,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,    13,     0,     0,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,     0,    21,    22,     0,     0,     0,    23,     0,
      24,   163,    25,     3,    26,     4,     5,     6,     7,     8,
       9,    10,    51,    12,     0,    13,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    17,
       0,    19,     0,     0,    21,    22,     0,     0,     0,    23,
     109,    24,     0,    25,     3,    26,     4,     5,     6,     7,
       8,     9,    10,    51,    12,     0,    13,     0,     0,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      17,     0,    19,     0,     0,    21,    22,     0,     0,     0,
      23,     0,    24,     0,    25,     0,    26,     4,     5,     6,
       7,     8,     9,    10,    51,    12,     0,    13,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      16,    17,     0,    19,     0,     0,    21,    22,     0,     0,
       0,    23,     0,    24,     0,    25,     0,    26,     4,     5,
       6,     7,     8,     9,    10,    51,    12,     0,    13,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    16,    17,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    23,     0,    24,     0,     0,     0,    26
};

/* YYCHECK.  */
const short
yy::Parser::check_[] =
{
       1,    11,    10,    11,    87,    10,   132,    39,    94,    17,
      18,   132,    21,    22,    10,   122,    25,    39,     6,     6,
      38,     9,    23,    45,    42,    26,     6,     7,     8,     9,
      10,    11,    28,    13,    38,    37,    16,    17,    42,    42,
     147,    44,    16,    39,    75,    76,    77,    78,    31,    57,
      36,    22,    23,    24,    25,    56,   142,    19,   184,    60,
      61,    32,    33,   184,    65,    18,   149,   150,   151,    20,
      21,    37,    81,    82,    34,    35,    37,    85,    32,    87,
      85,    73,    74,    84,    39,     6,     7,     8,     9,    10,
      11,    92,    13,    32,    33,    16,    17,   107,    79,    80,
      38,    36,    39,    36,    38,    13,   114,    36,    31,   114,
      37,   121,    36,   121,    45,    45,     8,    45,   119,    45,
      40,   122,   132,     6,    36,     8,     9,    10,    11,    38,
      13,   142,    39,    16,    17,    40,    38,    40,    16,   140,
      72,   149,   150,   151,   177,   181,   147,   148,    -1,    71,
      -1,   152,    -1,    -1,    -1,    -1,    -1,   158,    -1,    -1,
     161,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,   174,   184,     0,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    32,    33,    -1,
      -1,    -1,    37,    -1,    39,    -1,    41,     1,    43,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    29,    30,    -1,    32,    33,
      -1,    -1,    -1,    37,    -1,    39,    40,    41,     1,    43,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    29,    30,    -1,    32,
      33,    -1,    -1,    -1,    37,    -1,    39,    40,    41,     1,
      43,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    29,    30,    -1,
      32,    33,    -1,    -1,    -1,    37,    -1,    39,    40,    41,
       1,    43,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    29,    30,
      -1,    32,    33,    -1,    -1,    -1,    37,    -1,    39,    40,
      41,     1,    43,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    -1,    32,    33,    -1,    -1,    -1,    37,    -1,    39,
      40,    41,     1,    43,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    32,    33,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,     1,    43,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    29,    -1,    -1,    32,    33,    -1,    -1,    -1,    37,
      38,    39,    -1,    41,     1,    43,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    -1,    29,    -1,    -1,    32,    33,    -1,    -1,    -1,
      37,    -1,    39,    -1,    41,    -1,    43,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    29,    -1,    -1,    32,    33,    -1,    -1,
      -1,    37,    -1,    39,    -1,    41,    -1,    43,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,    -1,    -1,    -1,    43
};

#if YYDEBUG
/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
yy::Parser::stos_[] =
{
       0,    47,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    13,    16,    17,    26,    27,    28,    29,
      30,    32,    33,    37,    39,    41,    43,    48,    50,    52,
      55,    56,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    72,    73,    84,    85,     6,     7,
       9,    10,    68,    72,    74,     6,    72,    85,    67,    72,
      72,    37,    66,    66,    59,    16,    66,    59,    71,    31,
      36,    19,    18,    20,    21,    22,    23,    24,    25,    32,
      33,    34,    35,    57,    37,    32,    59,    72,    59,    59,
      38,    59,    42,    44,    53,    61,    62,    63,    63,    64,
      64,    64,    64,    65,    65,    66,    66,    39,    58,    38,
      59,     7,    68,    36,     9,    56,    72,    36,    38,    13,
      59,    10,    39,    54,    55,     6,    12,    14,    15,    30,
      40,    59,    75,    76,    77,    78,    79,    81,    85,    38,
      42,    36,    51,    59,     1,    40,    48,    49,    45,    45,
      45,    45,    37,    40,    76,    79,    36,    31,    45,    59,
      54,     8,    40,    40,    48,    59,    56,    56,    56,    59,
      36,    80,    59,    38,    42,    59,    38,    39,    83,    59,
      40,    82,     1,    40,    75,    38,    83,    40,    40
};

/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal token number corresponding
   to YYLEX-NUM.  */
const unsigned short
yy::Parser::token_number_[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    43,    45,    42,    47,    59,    40,    41,   123,
     125,    33,    44,    60,    62,    61
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
yy::Parser::r1_[] =
{
       0,    46,    47,    47,    48,    48,    48,    49,    49,    51,
      50,    52,    53,    52,    54,    54,    54,    54,    55,    55,
      55,    56,    57,    56,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    64,    65,    65,    65,    66,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    68,    69,    70,    71,    71,
      72,    73,    73,    73,    74,    74,    74,    74,    75,    75,
      75,    75,    76,    76,    76,    76,    76,    77,    78,    78,
      79,    80,    79,    82,    81,    83,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
yy::Parser::r2_[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     2,     0,
       6,     1,     0,     4,     1,     2,     3,     3,     4,     4,
       5,     1,     0,     3,     3,     2,     1,     1,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     2,     2,     2,
       1,     2,     2,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     4,     6,     8,     8,     3,     1,     3,
       1,     1,     2,     2,     1,     1,     3,     3,     2,     1,
       3,     2,     3,     1,     3,     1,     1,     3,     3,     3,
       1,     0,     4,     0,     6,     2,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
const char*
const yy::Parser::name_[] =
{
  "$end", "error", "$undefined", "T_BOOL", "T_REAL", "T_INTEGER", 
  "T_IDENTIFIER", "T_QUOTED_STRING", "T_BLUE", "T_CLASS", "T_DEFINE", 
  "T_EXTENDS", "T_FILTER", "T_GREEN", "T_LIGHT", "T_OUTPUT", "T_RED", 
  "T_RENDERER", "AND_L", "OR_L", "EQUAL", "NOT_EQ", "GREATER", 
  "GREATER_EQ", "LESS", "LESS_EQ", "PARAM", "T_DEFINED", "T_REDEFINE", 
  "THIS", "T_IF", "T_ELSE", "'+'", "'-'", "'*'", "'/'", "';'", "'('", 
  "')'", "'{'", "'}'", "'!'", "','", "'<'", "'>'", "'='", "$accept", 
  "everything", "statement", "statement_list", "if_head", "@1", 
  "simple_if_statement", "@2", "simple_if_body", "definition", "instance", 
  "@3", "param_block", "expression", "prec_8", "prec_7", "prec_6", 
  "prec_5", "prec_4", "prec_3", "prec_2", "prec_1", "function_call", 
  "color", "any_vector", "vector_insides", "name", "class", "string_math", 
  "params", "param", "object_param", "scene_param", "param_if_statement", 
  "@4", "param_if_head", "@5", "param_if_body", "potential_name", 
  "reserved_words", 0
};
#endif

#if YYDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS. */
const yy::Parser::RhsNumberType
yy::Parser::rhs_[] =
{
      47,     0,    -1,    -1,    47,    48,    -1,    55,    -1,    59,
      36,    -1,    52,    -1,    48,    -1,    49,    48,    -1,    -1,
      30,    37,    59,    38,    51,    54,    -1,    50,    -1,    -1,
      50,    31,    53,    54,    -1,    55,    -1,    39,    40,    -1,
      39,    49,    40,    -1,    39,     1,    40,    -1,    10,    72,
      59,    36,    -1,    28,    72,    59,    36,    -1,    10,    85,
      72,    56,    36,    -1,    72,    -1,    -1,    73,    57,    58,
      -1,    39,    75,    40,    -1,    39,    40,    -1,    60,    -1,
       1,    -1,    61,    -1,    60,    19,    61,    -1,    62,    -1,
      61,    18,    62,    -1,    63,    -1,    62,    20,    63,    -1,
      62,    21,    63,    -1,    64,    -1,    64,    23,    64,    -1,
      64,    22,    64,    -1,    64,    25,    64,    -1,    64,    24,
      64,    -1,    65,    -1,    64,    32,    65,    -1,    64,    33,
      65,    -1,    66,    -1,    65,    34,    66,    -1,    65,    35,
      66,    -1,    67,    -1,    41,    66,    -1,    32,    66,    -1,
      33,    66,    -1,     7,    -1,    26,    67,    -1,    27,    72,
      -1,     3,    -1,     5,    -1,     4,    -1,    37,    59,    38,
      -1,    69,    -1,    29,    -1,    56,    -1,    68,    -1,    70,
      -1,    84,    37,    38,    -1,    84,    37,    59,    38,    -1,
      84,    37,    59,    42,    59,    38,    -1,    84,    37,    59,
      42,    59,    42,    59,    38,    -1,    39,    16,    59,    13,
      59,     8,    59,    40,    -1,    43,    71,    44,    -1,    59,
      -1,    71,    42,    59,    -1,     6,    -1,     6,    -1,     9,
       6,    -1,     9,    74,    -1,     7,    -1,    68,    -1,    74,
      32,     7,    -1,    74,    32,    68,    -1,    76,    36,    -1,
      79,    -1,    75,    76,    36,    -1,    75,    79,    -1,     6,
      45,    59,    -1,    59,    -1,    85,    45,    59,    -1,    77,
      -1,    78,    -1,    12,    45,    56,    -1,    14,    45,    56,
      -1,    15,    45,    56,    -1,    81,    -1,    -1,    81,    31,
      80,    83,    -1,    -1,    30,    37,    59,    38,    82,    83,
      -1,    39,    40,    -1,    39,    75,    40,    -1,    39,     1,
      40,    -1,    72,    -1,    85,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    13,    -1,    16,    -1,    17,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned short
yy::Parser::prhs_[] =
{
       0,     0,     3,     4,     7,     9,    12,    14,    16,    19,
      20,    27,    29,    30,    35,    37,    40,    44,    48,    53,
      58,    64,    66,    67,    71,    75,    78,    80,    82,    84,
      88,    90,    94,    96,   100,   104,   106,   110,   114,   118,
     122,   124,   128,   132,   134,   138,   142,   144,   147,   150,
     153,   155,   158,   161,   163,   165,   167,   171,   173,   175,
     177,   179,   181,   185,   190,   197,   206,   215,   219,   221,
     225,   227,   229,   232,   235,   237,   239,   243,   247,   250,
     252,   256,   259,   263,   265,   269,   271,   273,   277,   281,
     285,   287,   288,   293,   294,   301,   304,   308,   312,   314,
     316,   318,   320,   322,   324,   326,   328
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
const unsigned short
yy::Parser::rline_[] =
{
       0,   202,   202,   205,   211,   215,   243,   249,   253,   261,
     260,   289,   295,   294,   306,   310,   314,   318,   326,   348,
     374,   398,   405,   404,   419,   423,   430,   436,   448,   454,
     471,   477,   495,   501,   550,   599,   606,   618,   630,   642,
     657,   663,   682,   703,   709,   728,   750,   756,   769,   776,
     812,   819,   825,   838,   844,   850,   857,   864,   869,   874,
     879,   883,   891,   923,   956,   990,  1026,  1052,  1065,  1078,
    1109,  1123,  1145,  1151,  1160,  1165,  1177,  1182,  1201,  1205,
    1209,  1213,  1219,  1227,  1278,  1286,  1290,  1296,  1332,  1376,
    1414,  1420,  1419,  1432,  1431,  1460,  1464,  1468,  1475,  1479,
    1486,  1491,  1496,  1501,  1506,  1511,  1516
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
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      37,    38,    34,    32,    42,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      43,    45,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
  };
  if ((unsigned) token <= user_token_number_max_)
    return translate_[token];
  else
    return undef_token_;
}

const int yy::Parser::eof_ = 0;
const int yy::Parser::last_ = 628;
const int yy::Parser::nnts_ = 40;
const int yy::Parser::empty_ = -2;
const int yy::Parser::final_ = 2;
const int yy::Parser::terror_ = 1;
const int yy::Parser::errcode_ = 256;
const int yy::Parser::ntokens_ = 46;
const int yy::Parser::initdepth_ = 200;

const unsigned yy::Parser::user_token_number_max_ = 286;
const yy::Parser::TokenNumberType yy::Parser::undef_token_ = 2;

#line 1523 "parser.y"


void rt_error (const char* pkcTEXT)
{

  GOM.error() << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */

void rt_error (const string& rksTEXT)
{

  GOM.error() << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << rksTEXT << endl;

}  /* rt_error() */

void rt_warning (const string& rksTEXT)
{

  GOM.error() << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Warning: " << rksTEXT << endl;

}  /* rt_error() */


void RT_InitParser (void)
{

  InitObjects();
  GlobalInitFunctions();

  while(!DATASTACK.empty()) DATASTACK.pop();

  WORLD = (magic_pointer<TAggregate>)new TAggregate();
  PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
  
  TSceneRT::_ptParsedScene->setWorld (rcp_static_cast<TObject>(WORLD));

  // Set the globalmost object to be the scene.  This allows operation on the
  // scene without the need for a dedicated scene section.
  DATASTACK.push ((user_arg_type)new TAttribScene(TSceneRT::_ptParsedScene));
  
}  /* RT_InitParser() */


void RT_CloseParser (void)
{

  DATAMAP.clear();

}  /* RT_CloseParser() */




void InitObjects (void)
{
  DATAMAP.clear();
}  /* InitObjects() */


magic_pointer<TBaseClass> NewObject (const string& rktCLASS,
				     const magic_pointer<TBaseClass>& pktParent)
{
  TBaseClass* ptChild = TClassManager::_newObject (rktCLASS,
						   pktParent.get_pointer());

  if ( !ptChild )
  {
    string   tMessage = string ("class ") + rktCLASS + " does not exist";
    rt_error (tMessage.c_str());
    exit (1);
  }

  return magic_pointer<TBaseClass>(ptChild);

}  /* NewObject() */

void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS)
{
  //  GOM.debug() << "Attempting to create instance of " << rktCLASS << endl;
  magic_pointer<TBaseClass> ptData;
  if ( rktCLASS == "" )
  {
    ptData = NewObject (rktDEF_CLASS, PARENT_OBJECT);
  }
  else
  {
    ptData = NewObject (rktCLASS, PARENT_OBJECT);
  }
  //  GOM.debug() << "Instance created... " << ptData->className() << endl;
  
  DATASTACK.push (base_to_attr(ptData));
  PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;

}  /* CreateObject() */



void report_reduction(const string& s)
{
  if( reduction_reporting )
  {
    GOM.out() << s << std::endl;
  }
}

magic_pointer<TAttribute> Instance(const string& s)
{
  if( s == "" )
  {
    rt_error ("instanced object cannot be unnamed");
    exit (1);
  }

  if ( DATAMAP.find (s) == DATAMAP.end() )
  {
    rt_error ("\"" + s + "\" is not defined");
    exit (1);
  }

  magic_pointer<TAttribute> attr = DATAMAP [s].second;

  if( !!attr )
  {
    return attr;
  }
  else
  {
    rt_error("\"" + s + "\" is defined as NULL");
    exit(1);
  }
}

namespace yy
{
  void Parser::error_()
  {
    rt_error(message);
  }
  void Parser::print_()
  {
    rt_warning("Parser::print_() called... What is it?  message(" + message + ")");
  }  
  // The stupid bison appears to be ignoring the yyprefix
  int yylex(yystype *p)
  {
    return rt_lex(p);
  }
}



