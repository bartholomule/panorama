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
#line 210 "parser.y"
    {
			    report_reduction("everything <-- everything expression ';'");
			    magic_pointer<TAttribObject> ptobj = get_object(semantic_stack_[1].ptAttribute);
			    if( !!ptobj )
			    {
			      magic_pointer<TObject> obj = ptobj->tValue;
			      if( !!obj )
			      {
				if( !WORLD->containsObject( obj ) )
				{
				  //				  GOM.debug() << "Adding instance of " << obj->className() << " to world." << endl;
				  WORLD->add ( obj );
				}
			      }
			    }
			    else
			    {
			      magic_pointer<TProcedural> proc = get_procedural_var(semantic_stack_[1].ptAttribute, false);
			      if( !!proc )
			      {
				FIXME("Potentially add instance (" + semantic_stack_[1].ptAttribute->toString() + " to the global scene");
			      }
			    }			      
			  }
    break;

  case 5:
#line 237 "parser.y"
    {
			    report_reduction("statement <-- definition");
			  }
    break;

  case 6:
#line 241 "parser.y"
    {
			    report_reduction("statement <-- simple_if_statement");
			  }
    break;

  case 7:
#line 248 "parser.y"
    {
			   report_reduction("statement_list <-- statement");
			 }
    break;

  case 8:
#line 252 "parser.y"
    {
			   report_reduction("statement_list <-- statement_list statement");
			 }
    break;

  case 9:
#line 258 "parser.y"
    {
			    report_reduction("if_head (start) <-- if ( expression )");
			    
			    bool b = check_get_bool(semantic_stack_[1].ptAttribute);
			    rt_enter_condition(b);
			  }
    break;

  case 10:
#line 265 "parser.y"
    {
			    report_reduction("if_head (cont) <-- if ( expression ) simple_if_body");
			    rt_leave_condition();
			    yyval.gValue = check_get_bool(semantic_stack_[3].ptAttribute);
                          }
    break;

  case 11:
#line 272 "parser.y"
    {
			    /* Nothing to do... */			    
			    report_reduction("simple_if_statement <-- if_head");
			  }
    break;

  case 12:
#line 277 "parser.y"
    {
			    report_reduction("simple_if_statement (start) <-- if_head ELSE");
			    rt_enter_condition(!semantic_stack_[1].gValue);
                          }
    break;

  case 13:
#line 282 "parser.y"
    {
			    report_reduction("simple_if_statement (start) <-- if_head ELSE simple_if_body");
			    rt_leave_condition();
                          }
    break;

  case 14:
#line 289 "parser.y"
    {
			   report_reduction("simple_if_body <-- definition");
			 }
    break;

  case 15:
#line 294 "parser.y"
    {
			   report_reduction("simple_if_body <-- { }");
			 }
    break;

  case 16:
#line 298 "parser.y"
    {
			   report_reduction("simple_if_body <-- { statement_list }");
			 }
    break;

  case 17:
#line 305 "parser.y"
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
			    }
			  }
    break;

  case 18:
#line 327 "parser.y"
    {
			    report_reduction("definition <-- DEFINE reserved_words name instance");
			    cerr << "Warning: definition on line "
			         << TSceneRT::_dwLineNumber
				 << " should not have \"" << semantic_stack_[3].sIdent << "\" anymore"
				 << endl;

			    if( rt_exec_ok() )
			    {
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
			    }
			  }
    break;

  case 19:
#line 351 "parser.y"
    {
			    report_reduction("instance <-- name");
			    report_reduction(string("instance <-- ") + semantic_stack_[0].sIdent);			    
			    yyval.ptAttribute = Instance(semantic_stack_[0].sIdent);
                          }
    break;

  case 20:
#line 357 "parser.y"
    {
			    //			    GOM.debug() << "Creating object..." << endl;
			    CreateObject(semantic_stack_[0].sIdent,"");
                          }
    break;

  case 21:
#line 362 "parser.y"
    {
			    report_reduction("instance <--  class { params }");
			    report_reduction(string("instance <-- ") + DATA->toString());
			    
			    //			    GOM.debug() << "Type is " << DATA->AttributeName() << endl;
			    yyval.ptAttribute = DATASTACK.POP();
			  }
    break;

  case 22:
#line 372 "parser.y"
    {
			    report_reduction("param_block <-- { params }");
			  }
    break;

  case 23:
#line 376 "parser.y"
    {
			    report_reduction("param_block <-- { }");
			  }
    break;

  case 24:
#line 383 "parser.y"
    {
			    yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			    report_reduction("expression <-- prec_8");
			    report_reduction("expression <-- " + semantic_stack_[0].ptAttribute->toString());
                          }
    break;

  case 25:
#line 392 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 26:
#line 398 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_8 OR prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[2].ptAttribute->toString() + " OR " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) ||
					       check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 27:
#line 408 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 28:
#line 414 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_7 AND prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[2].ptAttribute->toString() + " AND " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) &&
					       check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 29:
#line 425 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_5");
			  report_reduction("prec_6 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 30:
#line 431 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_6 EQUAL prec_5");
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
			    rt_error("I can't compare a " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType));
			  }
			}
    break;

  case 31:
#line 473 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_6 NOT_EQ prec_5");
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
    break;

  case 32:
#line 515 "parser.y"
    {
			  report_reduction("prec_5 <-- prec_4");
			  report_reduction("prec_5 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 33:
#line 522 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 >= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) >= check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 34:
#line 527 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 > prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) > check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 35:
#line 532 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 <= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) <= check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 36:
#line 537 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 < prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) < check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 37:
#line 545 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 38:
#line 551 "parser.y"
    {

			  report_reduction("prec_4 <-- prec_4 + prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " + " + semantic_stack_[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = add(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("addition of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			  }
			}
    break;

  case 39:
#line 564 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_4 - prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " - " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = sub(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("subtraction of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			  }
			}
    break;

  case 40:
#line 578 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_2");
			  report_reduction("prec_3 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 41:
#line 584 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_3 * prec_2");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " * " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = mul(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("multiplication of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			  }
			}
    break;

  case 42:
#line 596 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_3 / prec_2");
			  report_reduction("prec_4 <-- " + semantic_stack_[2].ptAttribute->toString() + " / " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = div(semantic_stack_[2].ptAttribute,semantic_stack_[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("division of " + EAttribType_to_str(semantic_stack_[2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(semantic_stack_[0].ptAttribute->eType) + " failed");
			  }
			}
    break;

  case 43:
#line 611 "parser.y"
    {
			  report_reduction("prec_2 <-- prec_1");
			  report_reduction("prec_2 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 44:
#line 617 "parser.y"
    {
			  report_reduction("prec_2 <-- ! prec_2");
			  report_reduction("prec_2 <-- ! " + semantic_stack_[0].ptAttribute->toString());

			  yyval.ptAttribute = (user_arg_type)new TAttribBool(!check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 45:
#line 624 "parser.y"
    {
			  report_reduction("prec_2 <-- + prec_2");
			  report_reduction("prec_2 <-- + " + semantic_stack_[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 46:
#line 631 "parser.y"
    {
			  report_reduction("prec_2 <-- - prec_2");
			  report_reduction("prec_2 <-- - " + semantic_stack_[0].ptAttribute->toString());

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
    break;

  case 47:
#line 660 "parser.y"
    {
			  report_reduction("prec_1 <-- quoted_string");
			  report_reduction("prec_1 <-- \"" + string(semantic_stack_[0].sIdent) + "\"");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribString(semantic_stack_[0].sIdent);
			}
    break;

  case 48:
#line 667 "parser.y"
    {
			  report_reduction("prec_1 <-- PARAM prec_1");
			  
			  FIXME("recovering a paramater (how?)");
			}
    break;

  case 49:
#line 673 "parser.y"
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

  case 50:
#line 686 "parser.y"
    {
			  report_reduction("prec_1 <-- BOOL");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(semantic_stack_[0].gValue);
			}
    break;

  case 51:
#line 692 "parser.y"
    {
			  report_reduction("prec_1 <-- INTEGER");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribInt(semantic_stack_[0].iValue);
			}
    break;

  case 52:
#line 698 "parser.y"
    {
			    report_reduction("prec_1 <-- REAL");
			    
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(semantic_stack_[0].dValue);
                          }
    break;

  case 53:
#line 705 "parser.y"
    {
			  report_reduction("prec_1 <-- ( expression )");
			  report_reduction("prec_1 <-- ( " + semantic_stack_[1].ptAttribute->toString() + " )");

			  yyval.ptAttribute = semantic_stack_[1].ptAttribute;
			}
    break;

  case 54:
#line 712 "parser.y"
    {
			  report_reduction("prec_1 <-- color");
			  yyval.ptAttribute = (user_arg_type)new TAttribColor(*semantic_stack_[0].ptColor);
			}
    break;

  case 55:
#line 717 "parser.y"
    {
			  report_reduction("prec_1 <-- THIS");
			  yyval.ptAttribute = DATA;
			}
    break;

  case 56:
#line 722 "parser.y"
    {
			  report_reduction("prec_1 <-- instance");
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;			  
                        }
    break;

  case 57:
#line 727 "parser.y"
    {
			  report_reduction("prec_1 <-- function_call");
                        }
    break;

  case 58:
#line 731 "parser.y"
    {
			  report_reduction("prec_1 <-- any_vector");
                        }
    break;

  case 59:
#line 739 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( )");
			  if( rt_exec_ok() )
			  {
			    report_reduction("(detail) function_call <-- " + string(semantic_stack_[2].sIdent) +  "( )");
			    
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
			  }
			}
    break;

  case 60:
#line 766 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression )");
			  if( rt_exec_ok() )
			  {
			    report_reduction("(detail) function_call <-- " + string(semantic_stack_[3].sIdent) + "( " + semantic_stack_[1].ptAttribute->toString() + " )");
			    
			    
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
			  }
			}
    break;

  case 61:
#line 796 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression , expression )");
			  if( rt_exec_ok() )
			  {
			    report_reduction("(detail) function_call <-- " + string(semantic_stack_[5].sIdent) + "( " + semantic_stack_[3].ptAttribute->toString() + "," + semantic_stack_[1].ptAttribute->toString() + " )");
			    
			    
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
			  }
			}
    break;

  case 62:
#line 830 "parser.y"
    {
			    report_reduction("color <-- { RED expression GREEN expression BLUE expression }");
			    report_reduction("color <-- { RED " + semantic_stack_[5].ptAttribute->toString() +
					     " GREEN " + semantic_stack_[3].ptAttribute->toString() +
					     " BLUE " + semantic_stack_[1].ptAttribute->toString() + " }");

			    double r = check_get_real(semantic_stack_[5].ptAttribute);
			    double g = check_get_real(semantic_stack_[3].ptAttribute);
			    double b = check_get_real(semantic_stack_[1].ptAttribute);

			    GOM.debug() << "r=" << r << " g=" << g << " b=" << b << endl;
			    TColor* c = new TColor(r,g,b);
			    GOM.debug() << "Here's what was really created: ";
			    c->printDebug(""); cerr << endl;
			    
			    yyval.ptColor = magic_pointer<TColor>(c);
			  }
    break;

  case 63:
#line 850 "parser.y"
    {
			    report_reduction("any_vector <-- '<' vector_insides '>'");
			    yyval.ptAttribute = semantic_stack_[1].ptAttribute;
                          }
    break;

  case 64:
#line 863 "parser.y"
    {
			    report_reduction("vector_insides <-- expression");
			    double e = check_get_real(semantic_stack_[0].ptAttribute);
			    yyval.ptAttribute = (user_arg_type)new TAttribArray(e);
			  }
    break;

  case 65:
#line 869 "parser.y"
    {
			    report_reduction("vector_insides <-- vector_insides ',' expression");
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
    break;

  case 66:
#line 893 "parser.y"
    {
			    report_reduction("name <-- IDENTIFIER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 67:
#line 907 "parser.y"
    {
			    report_reduction("class <-- : EXTENDS IDENTIFIER");
                            if ( DATAMAP.find (semantic_stack_[0].sIdent) == DATAMAP.end() )
                            {
			      rt_error ("trying to extend from non existing object");
			      exit (1);
                            }

			    //			    GOM.debug() << "the type of the parent is " << DATAMAP [$1].second->AttributeName() << endl;
                            PARENT_OBJECT = attr_to_base(DATAMAP [semantic_stack_[0].sIdent].second);
			    //			    GOM.debug() << "the parent's classname is " << PARENT_OBJECT->className() << endl;
			    yyval.sIdent = PARENT_OBJECT->className();
			  }
    break;

  case 68:
#line 921 "parser.y"
    {
			    report_reduction("class <-- : CLASS IDENTIFIER");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 69:
#line 927 "parser.y"
    {
			    report_reduction("class <-- : CLASS string_math");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 70:
#line 936 "parser.y"
    {
			    report_reduction("string_math <-- : QUOTED_STRING");
			    yyval.sIdent = semantic_stack_[0].sIdent;
                          }
    break;

  case 71:
#line 941 "parser.y"
    {
			    report_reduction("string_math <-- : function_call");
			    yyval.sIdent = check_get_string(semantic_stack_[0].ptAttribute);
			  }
    break;

  case 72:
#line 946 "parser.y"
    {
			    report_reduction("string_math <-- : string_math + QUOTED_STRING");
			    yyval.sIdent = semantic_stack_[2].sIdent + semantic_stack_[0].sIdent;
			  }
    break;

  case 73:
#line 951 "parser.y"
    {
			    report_reduction("string_math <-- : string_math + function_call");
			    yyval.sIdent = semantic_stack_[2].sIdent + check_get_string(semantic_stack_[0].ptAttribute);
			  }
    break;

  case 74:
#line 963 "parser.y"
    {
			  report_reduction("params <-- param ;");
                        }
    break;

  case 75:
#line 967 "parser.y"
    {
			  report_reduction("params <-- error ;");
			  rt_error("expected parameter expression");
                        }
    break;

  case 76:
#line 972 "parser.y"
    {
			  report_reduction("params <-- params param ;");
			}
    break;

  case 77:
#line 976 "parser.y"
    {
			  report_reduction("params <-- params error ;");
			  rt_error("expected parameter expression");
			}
    break;

  case 78:
#line 983 "parser.y"
    {
			  report_reduction("param <-- IDENTIFIER = expression");
			  if( rt_exec_ok() )
			  {
			    SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);
			  }
			}
    break;

  case 79:
#line 991 "parser.y"
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
				FIXME("Potentially do something with (" + semantic_stack_[0].ptAttribute->toString() + ") in the current object");
			      }
			    }
			  }
			}
    break;

  case 80:
#line 1042 "parser.y"
    {
			  report_reduction("param <-- reserved_words = expression");
			  if( rt_exec_ok() )
			  {
			    SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);
			  }
			}
    break;

  case 81:
#line 1050 "parser.y"
    {
			  report_reduction("param <-- object_param");
			}
    break;

  case 82:
#line 1054 "parser.y"
    {
			  report_reduction("param <-- scene_param");
			}
    break;

  case 83:
#line 1060 "parser.y"
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
			  }
			}
    break;

  case 84:
#line 1096 "parser.y"
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
			  }
			}
    break;

  case 85:
#line 1140 "parser.y"
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
			  }
			}
    break;

  case 86:
#line 1178 "parser.y"
    {
			  report_reduction("potential_name <-- name");
			}
    break;

  case 87:
#line 1182 "parser.y"
    {
			  report_reduction("potential_name <-- reserved_words");
			}
    break;

  case 88:
#line 1189 "parser.y"
    {
			    report_reduction("reserved_words <-- BLUE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 89:
#line 1194 "parser.y"
    {
			    report_reduction("reserved_words <-- CLASS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 90:
#line 1199 "parser.y"
    {
			    report_reduction("reserved_words <-- DEFINE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 91:
#line 1204 "parser.y"
    {
			    report_reduction("reserved_words <-- EXTENDS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 92:
#line 1209 "parser.y"
    {
			    report_reduction("reserved_words <-- GREEN");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 93:
#line 1214 "parser.y"
    {
			    report_reduction("reserved_words <-- RED");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 94:
#line 1219 "parser.y"
    {
			    report_reduction("reserved_words <-- RENDERER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;


    }

/* Line 446 of lalr1.cc.  */
#line 1373 "parser.cpp"

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
const short yy::Parser::pact_ninf_ = -85;
const short
yy::Parser::pact_[] =
{
     -85,   149,   -85,   -85,   -85,   -85,    24,   -85,   -85,    75,
     333,   -85,   -85,   -85,   -85,   309,    31,   -85,    37,   269,
     269,   269,    59,   269,   269,   -85,    60,   -85,   -85,   -85,
      58,    70,    76,    22,   -85,   106,    33,   -85,   -85,   -85,
     -85,   -85,    65,   -85,    67,   -85,    57,   -85,   -85,   -85,
     -85,   -85,    73,   -85,   269,    31,   -85,   -85,   269,   -85,
     -85,    69,   269,   -85,   -85,    15,   -85,   -85,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
      72,     8,   108,    77,    54,    74,   -85,    94,   269,   -85,
      16,    76,    22,   -85,   -85,    -3,    -3,    -3,    -3,    33,
      33,   -85,   -85,   189,   -85,   -85,   -10,   -85,   -85,   -85,
      75,    87,   -85,   -85,   269,   -85,   333,    12,   -85,   -85,
      88,    -6,    82,    83,    89,   -85,   -85,   229,   104,   -85,
     -85,    97,   -85,   269,   -85,    16,   134,   -85,   -85,    20,
     -85,   269,    54,    54,    54,   109,   -85,   110,   -85,   269,
     113,   -85,   269,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   107,   -85
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
const unsigned char
yy::Parser::defact_[] =
{
       2,     0,     1,    50,    52,    51,    66,    47,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     3,    11,     6,     5,    56,
       0,    24,    25,    27,    29,    32,    37,    40,    43,    57,
      54,    58,    19,    20,     0,    87,    66,    70,    89,    90,
      71,    86,    69,    66,     0,     0,    48,    49,     0,    45,
      46,     0,     0,    44,    64,     0,    12,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,    63,
       0,    26,    28,    30,    31,    34,    33,    36,    35,    38,
      39,    41,    42,     0,    21,    59,     0,    72,    73,    17,
       0,     0,    19,     9,     0,    65,     0,     0,    13,    14,
       0,    66,     0,     0,     0,    23,    79,     0,     0,    81,
      82,    87,    60,     0,    18,     0,     0,    15,     7,     0,
      75,     0,     0,     0,     0,     0,    22,     0,    74,     0,
       0,    10,     0,    16,     8,    78,    83,    84,    85,    77,
      76,    80,    61,     0,    62
};

/* YYPGOTO[NTERM-NUM].  */
const short
yy::Parser::pgoto_[] =
{
     -85,   -85,   -84,   -85,   -85,   -85,   -85,   -85,    26,   -83,
     -74,   -85,   -85,    -1,   -85,    79,    95,     1,    25,     2,
     -14,   128,    -5,   -85,   -85,   -85,    -8,   -85,   -85,   -85,
      36,   -85,   -85,   -85,    -7
};

/* YYDEFGOTO[NTERM-NUM].  */
const short
yy::Parser::defgoto_[] =
{
      -1,     1,    25,   139,    26,   135,    27,    90,   118,    28,
      29,    80,   104,   126,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    65,    42,    43,    52,   127,
     128,   129,   130,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
const short yy::Parser::table_ninf_ = -87;
const short
yy::Parser::table_[] =
{
      30,    51,    54,    55,    50,    59,    60,   119,    57,    63,
     111,     3,     4,     5,     6,     7,     8,     9,    49,    11,
      61,    12,   116,    64,    13,    14,   116,   132,    76,    77,
     116,   133,   -67,   138,    15,    16,    17,    53,   141,    19,
      20,    18,    70,    71,    21,   105,    22,    84,    23,    18,
      24,   137,   119,    83,   117,   154,    88,    85,    89,   153,
       6,    87,   -67,   110,   101,   102,    78,    79,   156,   157,
     158,    93,    94,    58,    51,    62,   112,   108,    99,   100,
     106,    46,    47,     8,    48,    49,    11,   115,    12,    68,
      66,    13,    14,    67,    69,   -68,   131,    95,    96,    97,
      98,   -86,    51,    81,    82,    50,    86,   114,    54,    55,
     103,   113,   109,   136,    53,   107,     8,    48,    49,    11,
     131,    12,   134,   140,    13,    14,   142,   143,    72,    73,
      74,    75,   150,   144,   112,   112,   112,    76,    77,   148,
     155,   149,   152,    56,   159,   160,   164,    91,   161,     2,
     162,   163,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   151,    12,   147,    92,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,     0,
      19,    20,     0,     0,     0,    21,     0,    22,     0,    23,
     120,    24,     3,     4,     5,   121,     7,     8,     9,    49,
      11,   122,    12,   123,   124,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,     0,     0,
      19,    20,     0,     0,     0,    21,     0,    22,   125,    23,
     145,    24,     3,     4,     5,   121,     7,     8,     9,    49,
      11,   122,    12,   123,   124,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,     0,     0,
      19,    20,     0,     0,     0,    21,     0,    22,   146,    23,
       0,    24,     3,     4,     5,     6,     7,     8,     9,    49,
      11,     0,    12,     0,     0,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,     0,     0,
      19,    20,     0,     0,     0,    21,     0,    22,     0,    23,
       0,    24,     3,     4,     5,     6,     7,     8,     9,    49,
      11,     0,    12,     0,     0,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,     0,    53,
       0,     8,    48,    49,    11,    21,    12,    22,     0,    13,
      14,    24
};

/* YYCHECK.  */
const short
yy::Parser::check_[] =
{
       1,     9,    10,    10,     9,    19,    20,    90,    16,    23,
      84,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      21,    13,    10,    24,    16,    17,    10,    37,    31,    32,
      10,    41,    38,   117,    26,    27,    28,     6,    44,    31,
      32,    29,    20,    21,    36,    37,    38,    55,    40,    29,
      42,    39,   135,    54,    38,   139,    41,    58,    43,    39,
       6,    62,    38,     9,    78,    79,    33,    34,   142,   143,
     144,    70,    71,    36,    82,    16,    84,    82,    76,    77,
      81,     6,     7,     8,     9,    10,    11,    88,    13,    19,
      30,    16,    17,    35,    18,    38,   103,    72,    73,    74,
      75,    36,   110,    36,    31,   110,    37,    13,   116,   116,
      38,    37,    35,   114,     6,     7,     8,     9,    10,    11,
     127,    13,    35,    35,    16,    17,    44,    44,    22,    23,
      24,    25,   133,    44,   142,   143,   144,    31,    32,    35,
     141,    44,     8,    15,    35,    35,    39,    68,   149,     0,
      37,   152,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   135,    13,   127,    69,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,
       1,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    39,    40,
       1,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    39,    40,
      -1,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,
      -1,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,     6,
      -1,     8,     9,    10,    11,    36,    13,    38,    -1,    16,
      17,    42
};

#if YYDEBUG
/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
yy::Parser::stos_[] =
{
       0,    46,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    13,    16,    17,    26,    27,    28,    29,    31,
      32,    36,    38,    40,    42,    47,    49,    51,    54,    55,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    71,    72,    78,    79,     6,     7,     9,    10,
      67,    71,    73,     6,    71,    79,    66,    71,    36,    65,
      65,    58,    16,    65,    58,    70,    30,    35,    19,    18,
      20,    21,    22,    23,    24,    25,    31,    32,    33,    34,
      56,    36,    31,    58,    71,    58,    37,    58,    41,    43,
      52,    60,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    65,    65,    38,    57,    37,    58,     7,    67,    35,
       9,    55,    71,    37,    13,    58,    10,    38,    53,    54,
       1,     6,    12,    14,    15,    39,    58,    74,    75,    76,
      77,    79,    37,    41,    35,    50,    58,    39,    47,    48,
      35,    44,    44,    44,    44,     1,    39,    75,    35,    44,
      58,    53,     8,    39,    47,    58,    55,    55,    55,    35,
      35,    58,    37,    58,    39
};

/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal token number corresponding
   to YYLEX-NUM.  */
const unsigned short
yy::Parser::token_number_[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    43,    45,    42,    47,    59,    40,    41,   123,   125,
      33,    44,    60,    62,    61
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
yy::Parser::r1_[] =
{
       0,    45,    46,    46,    46,    47,    47,    48,    48,    50,
      49,    51,    52,    51,    53,    53,    53,    54,    54,    55,
      56,    55,    57,    57,    58,    59,    59,    60,    60,    61,
      61,    61,    62,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    67,    68,    69,    70,    70,    71,    72,    72,    72,
      73,    73,    73,    73,    74,    74,    74,    74,    75,    75,
      75,    75,    75,    76,    77,    77,    78,    78,    79,    79,
      79,    79,    79,    79,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
yy::Parser::r2_[] =
{
       0,     2,     0,     2,     3,     1,     1,     1,     2,     0,
       6,     1,     0,     4,     1,     2,     3,     4,     5,     1,
       0,     3,     3,     2,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     2,     2,     2,     1,     2,     2,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       4,     6,     8,     3,     1,     3,     1,     1,     2,     2,
       1,     1,     3,     3,     2,     2,     3,     3,     3,     1,
       3,     1,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1
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
  "GREATER_EQ", "LESS", "LESS_EQ", "PARAM", "DEFINED", "THIS", "T_IF", 
  "T_ELSE", "'+'", "'-'", "'*'", "'/'", "';'", "'('", "')'", "'{'", "'}'", 
  "'!'", "','", "'<'", "'>'", "'='", "$accept", "everything", "statement", 
  "statement_list", "if_head", "@1", "simple_if_statement", "@2", 
  "simple_if_body", "definition", "instance", "@3", "param_block", 
  "expression", "prec_8", "prec_7", "prec_6", "prec_5", "prec_4", 
  "prec_3", "prec_2", "prec_1", "function_call", "color", "any_vector", 
  "vector_insides", "name", "class", "string_math", "params", "param", 
  "object_param", "scene_param", "potential_name", "reserved_words", 0
};
#endif

#if YYDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS. */
const yy::Parser::RhsNumberType
yy::Parser::rhs_[] =
{
      46,     0,    -1,    -1,    46,    47,    -1,    46,    58,    35,
      -1,    54,    -1,    51,    -1,    47,    -1,    48,    47,    -1,
      -1,    29,    36,    58,    37,    50,    53,    -1,    49,    -1,
      -1,    49,    30,    52,    53,    -1,    54,    -1,    38,    39,
      -1,    38,    48,    39,    -1,    10,    71,    58,    35,    -1,
      10,    79,    71,    55,    35,    -1,    71,    -1,    -1,    72,
      56,    57,    -1,    38,    74,    39,    -1,    38,    39,    -1,
      59,    -1,    60,    -1,    59,    19,    60,    -1,    61,    -1,
      60,    18,    61,    -1,    62,    -1,    61,    20,    62,    -1,
      61,    21,    62,    -1,    63,    -1,    63,    23,    63,    -1,
      63,    22,    63,    -1,    63,    25,    63,    -1,    63,    24,
      63,    -1,    64,    -1,    63,    31,    64,    -1,    63,    32,
      64,    -1,    65,    -1,    64,    33,    65,    -1,    64,    34,
      65,    -1,    66,    -1,    40,    65,    -1,    31,    65,    -1,
      32,    65,    -1,     7,    -1,    26,    66,    -1,    27,    71,
      -1,     3,    -1,     5,    -1,     4,    -1,    36,    58,    37,
      -1,    68,    -1,    28,    -1,    55,    -1,    67,    -1,    69,
      -1,    78,    36,    37,    -1,    78,    36,    58,    37,    -1,
      78,    36,    58,    41,    58,    37,    -1,    38,    16,    58,
      13,    58,     8,    58,    39,    -1,    42,    70,    43,    -1,
      58,    -1,    70,    41,    58,    -1,     6,    -1,     6,    -1,
       9,     6,    -1,     9,    73,    -1,     7,    -1,    67,    -1,
      73,    31,     7,    -1,    73,    31,    67,    -1,    75,    35,
      -1,     1,    35,    -1,    74,    75,    35,    -1,    74,     1,
      35,    -1,     6,    44,    58,    -1,    58,    -1,    79,    44,
      58,    -1,    76,    -1,    77,    -1,    12,    44,    55,    -1,
      14,    44,    55,    -1,    15,    44,    55,    -1,    71,    -1,
      79,    -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,
      13,    -1,    16,    -1,    17,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned short
yy::Parser::prhs_[] =
{
       0,     0,     3,     4,     7,    11,    13,    15,    17,    20,
      21,    28,    30,    31,    36,    38,    41,    45,    50,    56,
      58,    59,    63,    67,    70,    72,    74,    78,    80,    84,
      86,    90,    94,    96,   100,   104,   108,   112,   114,   118,
     122,   124,   128,   132,   134,   137,   140,   143,   145,   148,
     151,   153,   155,   157,   161,   163,   165,   167,   169,   171,
     175,   180,   187,   196,   200,   202,   206,   208,   210,   213,
     216,   218,   220,   224,   228,   231,   234,   238,   242,   246,
     248,   252,   254,   256,   260,   264,   268,   270,   272,   274,
     276,   278,   280,   282,   284
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
const unsigned short
yy::Parser::rline_[] =
{
       0,   202,   202,   205,   209,   236,   240,   247,   251,   258,
     257,   271,   277,   276,   288,   293,   297,   304,   326,   350,
     357,   356,   371,   375,   382,   391,   397,   407,   413,   424,
     430,   472,   514,   521,   526,   531,   536,   544,   550,   563,
     577,   583,   595,   610,   616,   623,   630,   659,   666,   672,
     685,   691,   697,   704,   711,   716,   721,   726,   730,   738,
     765,   795,   829,   849,   862,   868,   892,   906,   920,   926,
     935,   940,   945,   950,   962,   966,   971,   975,   982,   990,
    1041,  1049,  1053,  1059,  1095,  1139,  1177,  1181,  1188,  1193,
    1198,  1203,  1208,  1213,  1218
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
       2,     2,     2,    40,     2,     2,     2,     2,     2,     2,
      36,    37,    33,    31,    41,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      42,    44,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
  };
  if ((unsigned) token <= user_token_number_max_)
    return translate_[token];
  else
    return undef_token_;
}

const int yy::Parser::eof_ = 0;
const int yy::Parser::last_ = 351;
const int yy::Parser::nnts_ = 35;
const int yy::Parser::empty_ = -2;
const int yy::Parser::final_ = 2;
const int yy::Parser::terror_ = 1;
const int yy::Parser::errcode_ = 256;
const int yy::Parser::ntokens_ = 45;
const int yy::Parser::initdepth_ = 200;

const unsigned yy::Parser::user_token_number_max_ = 285;
const yy::Parser::TokenNumberType yy::Parser::undef_token_ = 2;

#line 1225 "parser.y"


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
    rt_error("Unknown parser error occurred (it called error_())");
  }
  void Parser::print_()
  {
    //    rt_warning("Parser::print_() called... What is it?");
  }  
  // The stupid bison appears to be ignoring the yyprefix
  int yylex(yystype *p)
  {
    return rt_lex(p);
  }
}



