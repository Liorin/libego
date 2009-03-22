/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                           *
 *  This file is part of Library of Effective GO routines - EGO library      *
 *                                                                           *
 *  Copyright 2006 and onwards, Lukasz Lew                                   *
 *                                                                           *
 *  EGO library is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation; either version 2 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  EGO library is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with EGO library; if not, write to the Free Software               *
 *  Foundation, Inc., 51 Franklin St, Fifth Floor,                           *
 *  Boston, MA  02110-1301  USA                                              *
 *                                                                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cctype>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <map>
#include <list>
#include <stack>

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include "ego.h"

#include "uct.cpp"

#include "gtp.cpp"
#include "gtp_board.cpp"
#include "gtp_sgf.cpp"
#include "gtp_genmove.cpp"

#include "experiments.cpp"


// goes through GTP files given in command line
void process_command_line (Gtp& gtp, int argc, char** argv) {
  if (argc == 1) {
    if (gtp.run_file ("automagic.gtp") == false) 
      cerr << "GTP file not found: automagic.gtp" << endl;
  }

  rep (arg_i, argc) {
    if (arg_i > 0) {
      if (gtp.run_file (argv [arg_i]) == false)
        cerr << "GTP file not found: " << argv [arg_i] << endl;
    }
  }
}


// main

int main () { 
  // to work well with gogui
  setvbuf (stdout, (char *)NULL, _IONBF, 0);
  setvbuf (stderr, (char *)NULL, _IONBF, 0);

  Gtp      gtp;
  Board    board;
  SgfTree  sgf_tree;

  GtpBoard    gtp_board (gtp, board);
  GtpSgf      gtp_sgf (gtp, sgf_tree, board);
  AllAsFirst  aaf (gtp, board);

  Uct uct (board);
  GtpGenmove<Uct>  gtp_genmove (gtp, board, uct);
  
  // command-answer GTP loop
  Benchmark::run (&board, 200000, cout, false);
  Benchmark::run (&board, 200000, cout, false);
  Benchmark::run (&board, 200000, cout, false);
  Benchmark::run (&board, 500000, cout, false);
  Benchmark::run (&board, 1000000, cout, false);
  return 0;
}