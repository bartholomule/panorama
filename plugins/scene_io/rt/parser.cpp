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
        case 2:
#line 197 "parser.y"
    {
			    report_reduction("everything <-- nothing");
			  }
    break;

  case 3:
#line 201 "parser.y"
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
				  //				  cout << "Adding instance of " << obj->className() << " to world." << endl;
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

  case 4:
#line 226 "parser.y"
    {
			    report_reduction("everything <-- everything definition");
			  }
    break;

  case 5:
#line 232 "parser.y"
    {
			    report_reduction("definition <-- DEFINE name expression ;");
			    report_reduction(string("definition <-- DEFINE ") +
					     semantic_stack_[2].sIdent + " " + semantic_stack_[1].ptAttribute->toString());

			    if( DATAMAP.find(semantic_stack_[2].sIdent) != DATAMAP.end() )
			    {
			      rt_warning(string(semantic_stack_[2].sIdent) + " redefined here");
			      rt_warning("previously defined here: " + DATAMAP[semantic_stack_[2].sIdent].first);
			    }
			    cout << "Defining \"" << string(semantic_stack_[2].sIdent) << "\"" << endl;
			    
			    char buffer[1024];
			    sprintf(buffer,"%s line %d",
				    TSceneRT::_tInputFileName.c_str(),
				    int(TSceneRT::_dwLineNumber));
			    DATAMAP[semantic_stack_[2].sIdent] = pair<string,attrib_type>(string(buffer),semantic_stack_[1].ptAttribute);
			  }
    break;

  case 6:
#line 251 "parser.y"
    {
			    report_reduction("definition <-- DEFINE reserved_words name instance");
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
			  }
    break;

  case 7:
#line 272 "parser.y"
    {
			    report_reduction("instance <-- name");
			    report_reduction(string("instance <-- ") + semantic_stack_[0].sIdent);			    
			    yyval.ptAttribute = Instance(semantic_stack_[0].sIdent);
                          }
    break;

  case 8:
#line 278 "parser.y"
    {
			    //			    cout << "Creating object..." << endl;
			    CreateObject(semantic_stack_[0].sIdent,"");
                          }
    break;

  case 9:
#line 283 "parser.y"
    {
			    report_reduction("instance <--  class { params }");
			    report_reduction(string("instance <-- ") + DATA->toString());
			    
			    //			    cout << "Type is " << DATA->AttributeName() << endl;
			    yyval.ptAttribute = DATASTACK.POP();
			  }
    break;

  case 10:
#line 293 "parser.y"
    {
			    report_reduction("param_block <-- { params }");
			  }
    break;

  case 11:
#line 297 "parser.y"
    {
			    report_reduction("param_block <-- { }");
			  }
    break;

  case 12:
#line 304 "parser.y"
    {
			    yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			    report_reduction("expression <-- prec_8");
			    report_reduction("expression <-- " + semantic_stack_[0].ptAttribute->toString());
                          }
    break;

  case 13:
#line 313 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 14:
#line 319 "parser.y"
    {
			  report_reduction("prec_8 <-- prec_8 OR prec_7");
			  report_reduction("prec_8 <-- " + semantic_stack_[2].ptAttribute->toString() + " OR " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) ||
					       check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 15:
#line 329 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 16:
#line 335 "parser.y"
    {
			  report_reduction("prec_7 <-- prec_7 AND prec_6");
			  report_reduction("prec_7 <-- " + semantic_stack_[2].ptAttribute->toString() + " AND " + semantic_stack_[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(semantic_stack_[2].ptAttribute) &&
					       check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 17:
#line 346 "parser.y"
    {
			  report_reduction("prec_6 <-- prec_5");
			  report_reduction("prec_6 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 18:
#line 352 "parser.y"
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

  case 19:
#line 394 "parser.y"
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

  case 20:
#line 436 "parser.y"
    {
			  report_reduction("prec_5 <-- prec_4");
			  report_reduction("prec_5 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 21:
#line 443 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 >= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) >= check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 22:
#line 448 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 > prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) > check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 23:
#line 453 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 <= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) <= check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 24:
#line 458 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_6 < prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(semantic_stack_[2].ptAttribute) < check_get_real(semantic_stack_[0].ptAttribute));
			}
    break;

  case 25:
#line 466 "parser.y"
    {
			  report_reduction("prec_4 <-- prec_3");
			  report_reduction("prec_4 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 26:
#line 472 "parser.y"
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

  case 27:
#line 485 "parser.y"
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

  case 28:
#line 499 "parser.y"
    {
			  report_reduction("prec_3 <-- prec_2");
			  report_reduction("prec_3 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 29:
#line 505 "parser.y"
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

  case 30:
#line 517 "parser.y"
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

  case 31:
#line 532 "parser.y"
    {
			  report_reduction("prec_2 <-- prec_1");
			  report_reduction("prec_2 <-- " + semantic_stack_[0].ptAttribute->toString());			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 32:
#line 538 "parser.y"
    {
			  report_reduction("prec_2 <-- ! prec_2");
			  report_reduction("prec_2 <-- ! " + semantic_stack_[0].ptAttribute->toString());

			  yyval.ptAttribute = (user_arg_type)new TAttribBool(!check_get_bool(semantic_stack_[0].ptAttribute));
			}
    break;

  case 33:
#line 545 "parser.y"
    {
			  report_reduction("prec_2 <-- + prec_2");
			  report_reduction("prec_2 <-- + " + semantic_stack_[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;
			}
    break;

  case 34:
#line 552 "parser.y"
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

  case 35:
#line 581 "parser.y"
    {
			  report_reduction("prec_1 <-- quoted_string");
			  report_reduction("prec_1 <-- " + string(semantic_stack_[0].sIdent));
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribString(semantic_stack_[0].sIdent);
			}
    break;

  case 36:
#line 588 "parser.y"
    {
			  report_reduction("prec_1 <-- PARAM prec_1");
			  
			  FIXME("recovering a paramater (how?)");
			}
    break;

  case 37:
#line 594 "parser.y"
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

  case 38:
#line 607 "parser.y"
    {
			  report_reduction("prec_1 <-- BOOL");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(semantic_stack_[0].gValue);
			}
    break;

  case 39:
#line 613 "parser.y"
    {
			  report_reduction("prec_1 <-- INTEGER");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribInt(semantic_stack_[0].iValue);
			}
    break;

  case 40:
#line 619 "parser.y"
    {
			    report_reduction("prec_1 <-- REAL");
			    
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(semantic_stack_[0].dValue);
                          }
    break;

  case 41:
#line 626 "parser.y"
    {
			  report_reduction("prec_1 <-- ( expression )");
			  report_reduction("prec_1 <-- ( " + semantic_stack_[1].ptAttribute->toString() + " )");

			  yyval.ptAttribute = semantic_stack_[1].ptAttribute;
			}
    break;

  case 42:
#line 633 "parser.y"
    {
			  report_reduction("prec_1 <-- color");
			  yyval.ptAttribute = (user_arg_type)new TAttribColor(*semantic_stack_[0].ptColor);
			}
    break;

  case 43:
#line 638 "parser.y"
    {
			  report_reduction("prec_1 <-- THIS");
			  yyval.ptAttribute = DATA;
			}
    break;

  case 44:
#line 643 "parser.y"
    {
			  report_reduction("prec_1 <-- instance");
			  yyval.ptAttribute = semantic_stack_[0].ptAttribute;			  
                        }
    break;

  case 46:
#line 649 "parser.y"
    {
			  report_reduction("prec_1 <-- any_vector");
                        }
    break;

  case 47:
#line 657 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( )");
			  report_reduction("function_call <-- " + string(semantic_stack_[2].sIdent) +  "( )");

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
    break;

  case 48:
#line 681 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression )");
			  report_reduction("function_call <-- " + string(semantic_stack_[3].sIdent) + "( " + semantic_stack_[1].ptAttribute->toString() + " )");
			  
			  
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
    break;

  case 49:
#line 708 "parser.y"
    {
			  report_reduction("function_call <-- potential_name ( expression , expression )");
			  report_reduction("function_call <-- " + string(semantic_stack_[5].sIdent) + "( " + semantic_stack_[3].ptAttribute->toString() + "," + semantic_stack_[1].ptAttribute->toString() + " )");
			  
			  
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
    break;

  case 50:
#line 739 "parser.y"
    {
			    report_reduction("color <-- { RED expression GREEN expression BLUE expression }");
			    report_reduction("color <-- { RED " + semantic_stack_[5].ptAttribute->toString() +
					     " GREEN " + semantic_stack_[3].ptAttribute->toString() +
					     " BLUE " + semantic_stack_[1].ptAttribute->toString() + " }");

			    double r = check_get_real(semantic_stack_[5].ptAttribute);
			    double g = check_get_real(semantic_stack_[3].ptAttribute);
			    double b = check_get_real(semantic_stack_[1].ptAttribute);

			    cout << "r=" << r << " g=" << g << " b=" << b << endl;
			    TColor* c = new TColor(r,g,b);
			    cout << "Here's what was really created: ";
			    c->printDebug(""); cerr << endl;
			    
			    yyval.ptColor = magic_pointer<TColor>(c);
			  }
    break;

  case 51:
#line 759 "parser.y"
    {
			    report_reduction("any_vector <-- '<' vector_insides '>'");
			    yyval.ptAttribute = semantic_stack_[1].ptAttribute;
                          }
    break;

  case 52:
#line 772 "parser.y"
    {
			    report_reduction("vector_insides <-- expression");
			    double e = check_get_real(semantic_stack_[0].ptAttribute);
			    yyval.ptAttribute = (user_arg_type)new TAttribArray(e);
			  }
    break;

  case 53:
#line 778 "parser.y"
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

  case 54:
#line 802 "parser.y"
    {
			    report_reduction("name <-- IDENTIFIER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 55:
#line 816 "parser.y"
    {
			    report_reduction("class <-- : EXTENDS IDENTIFIER");
                            if ( DATAMAP.find (semantic_stack_[0].sIdent) == DATAMAP.end() )
                            {
			      rt_error ("trying to extend from non existing object");
			      exit (1);
                            }

			    //			    cout << "the type of the parent is " << DATAMAP [$1].second->AttributeName() << endl;
                            PARENT_OBJECT = attr_to_base(DATAMAP [semantic_stack_[0].sIdent].second);
			    //			    cout << "the parent's classname is " << PARENT_OBJECT->className() << endl;
			    yyval.sIdent = PARENT_OBJECT->className();
			  }
    break;

  case 56:
#line 830 "parser.y"
    {
			    report_reduction("class <-- : CLASS IDENTIFIER");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 57:
#line 843 "parser.y"
    {
			  report_reduction("params <-- param ;");
                        }
    break;

  case 58:
#line 847 "parser.y"
    {
			  report_reduction("params <-- error ;");
			  rt_error("expected parameter expression");
                        }
    break;

  case 59:
#line 852 "parser.y"
    {
			  report_reduction("params <-- params param ;");
			}
    break;

  case 60:
#line 856 "parser.y"
    {
			  report_reduction("params <-- params error ;");
			  rt_error("expected parameter expression");
			}
    break;

  case 61:
#line 863 "parser.y"
    {
			  report_reduction("param <-- IDENTIFIER = expression");
			  SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);
			}
    break;

  case 62:
#line 868 "parser.y"
    {
			  report_reduction("param <-- expression");
			  
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
    break;

  case 63:
#line 916 "parser.y"
    {
			  report_reduction("param <-- reserved_words = expression");
			  SetParameter (semantic_stack_[2].sIdent, semantic_stack_[0].ptAttribute);			    
			}
    break;

  case 64:
#line 921 "parser.y"
    {
			  report_reduction("param <-- object_param");
			}
    break;

  case 65:
#line 925 "parser.y"
    {
			  report_reduction("param <-- scene_param");
			}
    break;

  case 66:
#line 931 "parser.y"
    {
			  // If an object, object->addFilter.
			  // If a scene, scene->addImageFilter
			  report_reduction("object_param <-- FILTER = instance");
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
    break;

  case 67:
#line 963 "parser.y"
    {
			  report_reduction("scene_param <-- LIGHT = instance");
			  // This is no longer needed, as there are special
			  // cases for this in the light_instance rule.
			  if( !!semantic_stack_[0].ptAttribute )
			  {
			    static bool gave_warning = false;
			    
			    if(!gave_warning)
			    {
			      cout << "Note for light instance on line "
				   << TSceneRT::_dwLineNumber
				   << endl;
			      cout << "  Usage of lights in the 'scene' section is no longer required" << endl;
			      cout << "  They may now be added to aggregates, csg, etc., or used "
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
    break;

  case 68:
#line 1004 "parser.y"
    {
			  report_reduction("scene_param <-- OUTPUT = instance");
			  FIXME("Image output");
			  magic_pointer<TAttribScene> pscene = get_scene(DATA);
			  if( !!pscene )
			  {
			    //			    magic_pointer<TScene> scene = pscene->tValue;
			    cout << "Warning: Ignoring locally defined scene" << endl;
			    magic_pointer<TScene> scene = TSceneRT::_ptParsedScene;
			    if( !!scene )
			    {
			      magic_pointer<TAttribImageIO> io = get_imageio(semantic_stack_[0].ptAttribute);
			      if( !!io )
			      {
				//				cout << "Setting image IO to " << io->toString() << endl;
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
    break;

  case 69:
#line 1039 "parser.y"
    {
			  report_reduction("potential_name <-- name");
			}
    break;

  case 70:
#line 1043 "parser.y"
    {
			  report_reduction("potential_name <-- reserved_words");
			}
    break;

  case 71:
#line 1050 "parser.y"
    {
			    report_reduction("reserved_words <-- BLUE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 72:
#line 1055 "parser.y"
    {
			    report_reduction("reserved_words <-- CLASS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 73:
#line 1060 "parser.y"
    {
			    report_reduction("reserved_words <-- DEFINE");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 74:
#line 1065 "parser.y"
    {
			    report_reduction("reserved_words <-- EXTENDS");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 75:
#line 1070 "parser.y"
    {
			    report_reduction("reserved_words <-- GREEN");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 76:
#line 1075 "parser.y"
    {
			    report_reduction("reserved_words <-- RED");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;

  case 77:
#line 1080 "parser.y"
    {
			    report_reduction("reserved_words <-- RENDERER");
			    yyval.sIdent = semantic_stack_[0].sIdent;
			  }
    break;


    }

/* Line 446 of lalr1.cc.  */
#line 1199 "parser.cpp"

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
const short yy::Parser::pact_ninf_ = -64;
const short
yy::Parser::pact_[] =
{
     -64,   125,   -64,   -64,   -64,   -64,   -29,   -64,   -64,     2,
       3,   -64,   -64,   -64,   -64,   315,    11,   -64,   277,   277,
      21,   277,   277,   277,   -64,   -64,    19,    31,    40,     8,
     -64,     1,    12,   -64,   -64,   -64,   -64,   -64,    22,   -64,
      23,   -64,   -64,   -64,   -64,   -64,   277,    11,   -64,   -64,
     -64,   -64,   277,   -64,    27,   -64,    -5,   -64,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
      32,   239,    28,     9,    54,   -64,   277,   -64,    40,     8,
     -64,   -64,    17,    17,    17,    17,    12,    12,   -64,   -64,
     163,   -64,   -64,    -6,   -64,     2,    35,   -64,   277,   -64,
      36,    -7,    29,    30,    34,   -64,   -64,   201,    41,   -64,
     -64,    37,   -64,   277,   -64,    65,   -64,   277,     9,     9,
       9,    44,   -64,    45,   -64,   277,    42,   277,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,    46,   -64
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
const unsigned char
yy::Parser::defact_[] =
{
       2,     0,     1,    38,    40,    39,    54,    35,    71,    72,
      73,    74,    75,    76,    77,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     4,    44,     0,    12,    13,    15,
      17,    20,    25,    28,    31,    45,    42,    46,     7,     8,
       0,    70,    56,    54,    72,    73,     0,     0,    36,    37,
      33,    34,     0,    32,     0,    52,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,    51,    14,    16,
      18,    19,    22,    21,    24,    23,    26,    27,    29,    30,
       0,     9,    47,     0,     5,     0,     0,     7,     0,    53,
       0,    54,     0,     0,     0,    11,    62,     0,     0,    64,
      65,    70,    48,     0,     6,     0,    58,     0,     0,     0,
       0,     0,    10,     0,    57,     0,     0,     0,    61,    66,
      67,    68,    60,    59,    63,    49,     0,    50
};

/* YYPGOTO[NTERM-NUM].  */
const signed char
yy::Parser::pgoto_[] =
{
     -64,   -64,   -64,   -63,   -64,   -64,    -1,   -64,    25,    26,
     -12,   -23,    -4,   -15,    69,   -64,   -64,   -64,   -64,    -9,
     -64,   -64,   -21,   -64,   -64,   -64,    -8
};

/* YYDEFGOTO[NTERM-NUM].  */
const signed char
yy::Parser::defgoto_[] =
{
      -1,     1,    24,    25,    70,    91,   106,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    56,    38,
      39,   107,   108,   109,   110,    40,    41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
const short yy::Parser::table_ninf_ = -70;
const short
yy::Parser::table_[] =
{
      26,    46,    47,    50,    51,   -55,    53,    49,    42,    43,
      96,     8,    44,    45,    11,     6,    12,    43,    95,    13,
      14,    54,    55,    62,    63,    64,    65,   -55,    60,    61,
      66,    67,   112,   113,    76,   117,    77,    52,    73,    82,
      83,    84,    85,    68,    69,    72,    66,    67,    80,    81,
      58,    74,    57,    88,    89,   129,   130,   131,    59,   -69,
      71,    94,    86,    87,    97,    75,    90,    98,   114,   116,
      93,   118,   119,   127,   124,    99,   120,   132,   133,   125,
     135,   137,   111,    78,    48,    79,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      97,    97,   126,     0,     0,     0,   128,     0,     0,     0,
       0,     0,     0,     0,   134,     2,   136,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,     0,    12,     0,
       0,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    18,    19,     0,     0,     0,    20,
       0,    21,    22,     0,   100,    23,     3,     4,     5,   101,
       7,     8,     9,    45,    11,   102,    12,   103,   104,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,    19,     0,     0,     0,    20,   105,    21,
      22,     0,   121,    23,     3,     4,     5,   101,     7,     8,
       9,    45,    11,   102,    12,   103,   104,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,     0,    20,   122,    21,    22,     0,
       0,    23,     3,     4,     5,     6,     7,     8,     9,    45,
      11,     0,    12,     0,     0,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,    19,
       0,     0,     0,    20,     0,    21,    22,    92,     0,    23,
       3,     4,     5,     6,     7,     8,     9,    45,    11,     0,
      12,     0,     0,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,     0,     0,
       0,    20,     0,    21,    22,     0,     0,    23,     3,     4,
       5,     6,     7,     8,     9,    45,    11,     0,    12,     0,
       0,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,     0,     0,     0,     0,     0,    20,
       0,     0,    22,     0,     0,    23
};

/* YYCHECK.  */
const signed char
yy::Parser::check_[] =
{
       1,    10,    10,    18,    19,    34,    21,    16,     6,     6,
      73,     8,     9,    10,    11,     6,    13,     6,     9,    16,
      17,    22,    23,    22,    23,    24,    25,    34,    20,    21,
      29,    30,    38,    39,    39,    42,    41,    16,    47,    62,
      63,    64,    65,    31,    32,    46,    29,    30,    60,    61,
      19,    52,    33,    68,    69,   118,   119,   120,    18,    37,
      37,    33,    66,    67,    73,    38,    34,    13,    33,    33,
      71,    42,    42,     8,    33,    76,    42,    33,    33,    42,
      38,    35,    90,    58,    15,    59,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   107,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,     0,   127,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    -1,    -1,    34,
      -1,    36,    37,    -1,     1,    40,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,     1,    40,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    40,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    34,    -1,    36,    37,    38,    -1,    40,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    34,    -1,    36,    37,    -1,    -1,    40,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    40
};

#if YYDEBUG
/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
yy::Parser::stos_[] =
{
       0,    44,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    13,    16,    17,    26,    27,    28,    29,    30,
      34,    36,    37,    40,    45,    46,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    62,    63,
      68,    69,     6,     6,     9,    10,    62,    69,    57,    62,
      56,    56,    16,    56,    49,    49,    61,    33,    19,    18,
      20,    21,    22,    23,    24,    25,    29,    30,    31,    32,
      47,    37,    49,    62,    49,    38,    39,    41,    51,    52,
      53,    53,    54,    54,    54,    54,    55,    55,    56,    56,
      34,    48,    38,    49,    33,     9,    46,    62,    13,    49,
       1,     6,    12,    14,    15,    35,    49,    64,    65,    66,
      67,    69,    38,    39,    33,    49,    33,    42,    42,    42,
      42,     1,    35,    65,    33,    42,    49,     8,    49,    46,
      46,    46,    33,    33,    49,    38,    49,    35
};

/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal token number corresponding
   to YYLEX-NUM.  */
const unsigned short
yy::Parser::token_number_[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    43,
      45,    42,    47,    59,   123,   125,    33,    40,    41,    44,
      60,    62,    61
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
yy::Parser::r1_[] =
{
       0,    43,    44,    44,    44,    45,    45,    46,    47,    46,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      53,    53,    53,    53,    53,    54,    54,    54,    55,    55,
      55,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    60,    61,    61,    62,    63,    63,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    66,    67,    67,    68,
      68,    69,    69,    69,    69,    69,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
yy::Parser::r2_[] =
{
       0,     2,     0,     3,     2,     4,     5,     1,     0,     3,
       3,     2,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     4,     6,
       8,     3,     1,     3,     1,     1,     2,     2,     2,     3,
       3,     3,     1,     3,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
  "GREATER_EQ", "LESS", "LESS_EQ", "PARAM", "DEFINED", "THIS", "'+'", 
  "'-'", "'*'", "'/'", "';'", "'{'", "'}'", "'!'", "'('", "')'", "','", 
  "'<'", "'>'", "'='", "$accept", "everything", "definition", "instance", 
  "@1", "param_block", "expression", "prec_8", "prec_7", "prec_6", 
  "prec_5", "prec_4", "prec_3", "prec_2", "prec_1", "function_call", 
  "color", "any_vector", "vector_insides", "name", "class", "params", 
  "param", "object_param", "scene_param", "potential_name", 
  "reserved_words", 0
};
#endif

#if YYDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS. */
const yy::Parser::RhsNumberType
yy::Parser::rhs_[] =
{
      44,     0,    -1,    -1,    44,    49,    33,    -1,    44,    45,
      -1,    10,    62,    49,    33,    -1,    10,    69,    62,    46,
      33,    -1,    62,    -1,    -1,    63,    47,    48,    -1,    34,
      64,    35,    -1,    34,    35,    -1,    50,    -1,    51,    -1,
      50,    19,    51,    -1,    52,    -1,    51,    18,    52,    -1,
      53,    -1,    52,    20,    53,    -1,    52,    21,    53,    -1,
      54,    -1,    54,    23,    54,    -1,    54,    22,    54,    -1,
      54,    25,    54,    -1,    54,    24,    54,    -1,    55,    -1,
      54,    29,    55,    -1,    54,    30,    55,    -1,    56,    -1,
      55,    31,    56,    -1,    55,    32,    56,    -1,    57,    -1,
      36,    56,    -1,    29,    56,    -1,    30,    56,    -1,     7,
      -1,    26,    57,    -1,    27,    62,    -1,     3,    -1,     5,
      -1,     4,    -1,    37,    49,    38,    -1,    59,    -1,    28,
      -1,    46,    -1,    58,    -1,    60,    -1,    68,    37,    38,
      -1,    68,    37,    49,    38,    -1,    68,    37,    49,    39,
      49,    38,    -1,    34,    16,    49,    13,    49,     8,    49,
      35,    -1,    40,    61,    41,    -1,    49,    -1,    61,    39,
      49,    -1,     6,    -1,     6,    -1,     9,     6,    -1,    65,
      33,    -1,     1,    33,    -1,    64,    65,    33,    -1,    64,
       1,    33,    -1,     6,    42,    49,    -1,    49,    -1,    69,
      42,    49,    -1,    66,    -1,    67,    -1,    12,    42,    46,
      -1,    14,    42,    46,    -1,    15,    42,    46,    -1,    62,
      -1,    69,    -1,     8,    -1,     9,    -1,    10,    -1,    11,
      -1,    13,    -1,    16,    -1,    17,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned char
yy::Parser::prhs_[] =
{
       0,     0,     3,     4,     8,    11,    16,    22,    24,    25,
      29,    33,    36,    38,    40,    44,    46,    50,    52,    56,
      60,    62,    66,    70,    74,    78,    80,    84,    88,    90,
      94,    98,   100,   103,   106,   109,   111,   114,   117,   119,
     121,   123,   127,   129,   131,   133,   135,   137,   141,   146,
     153,   162,   166,   168,   172,   174,   176,   179,   182,   185,
     189,   193,   197,   199,   203,   205,   207,   211,   215,   219,
     221,   223,   225,   227,   229,   231,   233,   235
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
const unsigned short
yy::Parser::rline_[] =
{
       0,   197,   197,   200,   225,   231,   250,   271,   278,   277,
     292,   296,   303,   312,   318,   328,   334,   345,   351,   393,
     435,   442,   447,   452,   457,   465,   471,   484,   498,   504,
     516,   531,   537,   544,   551,   580,   587,   593,   606,   612,
     618,   625,   632,   637,   642,   647,   648,   656,   680,   707,
     738,   758,   771,   777,   801,   815,   829,   842,   846,   851,
     855,   862,   867,   915,   920,   924,   930,   962,  1003,  1038,
    1042,  1049,  1054,  1059,  1064,  1069,  1074,  1079
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
       2,     2,     2,    36,     2,     2,     2,     2,     2,     2,
      37,    38,    31,    29,    39,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
      40,    42,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28
  };
  if ((unsigned) token <= user_token_number_max_)
    return translate_[token];
  else
    return undef_token_;
}

const int yy::Parser::eof_ = 0;
const int yy::Parser::last_ = 355;
const int yy::Parser::nnts_ = 27;
const int yy::Parser::empty_ = -2;
const int yy::Parser::final_ = 2;
const int yy::Parser::terror_ = 1;
const int yy::Parser::errcode_ = 256;
const int yy::Parser::ntokens_ = 43;
const int yy::Parser::initdepth_ = 200;

const unsigned yy::Parser::user_token_number_max_ = 283;
const yy::Parser::TokenNumberType yy::Parser::undef_token_ = 2;

#line 1086 "parser.y"


void rt_error (const char* pkcTEXT)
{

  cout << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */

void rt_error (const string& rksTEXT)
{

  cout << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << rksTEXT << endl;

}  /* rt_error() */

void rt_warning (const string& rksTEXT)
{

  cout << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Warning: " << rksTEXT << endl;

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
  //  cout << "Attempting to create instance of " << rktCLASS << endl;
  magic_pointer<TBaseClass> ptData;
  if ( rktCLASS == "" )
  {
    ptData = NewObject (rktDEF_CLASS, PARENT_OBJECT);
  }
  else
  {
    ptData = NewObject (rktCLASS, PARENT_OBJECT);
  }
  //  cout << "Instance created... " << ptData->className() << endl;
  
  DATASTACK.push (base_to_attr(ptData));
  PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;

}  /* CreateObject() */



void report_reduction(const string& s)
{
#if defined(REDUCTION_REPORTING)
  cout << s << endl;
#endif
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



