// $Id$
//
//  Copyright (C) 2003-2010  Rational Discovery LLC
//
//   @@ All Rights Reserved  @@
//
#define NO_IMPORT_ARRAY
#include <boost/python.hpp>
#include <string>

//ours
#include <GraphMol/FileParsers/MolWriters.h>
#include <GraphMol/RDKitBase.h>
#include "rdchem.h"
#include <RDBoost/PySequenceHolder.h>

namespace python = boost::python;

namespace RDKit {
  void SetSmiWriterProps(SmilesWriter &writer, python::object props) {
    // convert the python list to a STR_VECT
    STR_VECT propNames;

    PySequenceHolder<std::string> seq(props);
    for (unsigned int i = 0; i < seq.size(); i++) {
      propNames.push_back(seq[i]);
    }
    writer.setProps(propNames);
  }
  std::string swDocStr="Constructor.\n\n"
  "   ARGUMENTS:\n\n"
  "     - fileName: name of the output file.\n"
  "     - delimiter: (optional) delimiter to be used to separate entries on each line.\n"
  "     - nameHeader: (optional) text to use for the name column in the header line.\n"
  "                   If this is blank, names will not be dumped.\n"
  "     - includeHeader: (optional) toggles inclusion of a header line in the output file.\n"
  "     - isomericSmiles: (optional) toggles output of isomeric smiles (includes stereochem information).\n"
  "     - includeHeader: (optional) toggles output of kekule smiles (no aromatic bonds for molecules that have been kekulized).\n\n";
  struct smiwriter_wrap {
    static void wrap() {
      python::class_<SmilesWriter>("SmilesWriter",
				   "A class for writing molecules to text files.",
				   python::init<std::string,std::string,std::string,bool,bool,bool>((python::arg("fileName"),
											   python::arg("delimiter")=" ",
											   python::arg("nameHeader")="Name",
											   python::arg("includeHeader")=true,
                                                                                           python::arg("isomericSmiles")=false,
                                                                                           python::arg("kekuleSmiles")=false),
											  swDocStr.c_str()))
	.def("SetProps", SetSmiWriterProps,
	     "Sets the properties to be written to the output file\n\n"
	     "  ARGUMENTS:\n\n"
	     "    - props: a list or tuple of property names\n\n" )
	.def("write", &SmilesWriter::write,
             (python::arg("self"), python::arg("mol"), python::arg("confId")=-1),
	     "Writes a molecule to the output file.\n\n"
	     "  ARGUMENTS:\n\n"
	     "    - mol: the Mol to be written\n"
	     "    - confId: (optional) ignored \n\n")
	.def("flush", &SmilesWriter::flush,
	     "Flushes the output file (forces the disk file to be updated).\n\n"
	     )
	.def("close", &SmilesWriter::close,
	     "Flushes the output file and closes it. The Writer cannot be used after this.\n\n"
	     )
	.def("NumMols", &SmilesWriter::numMols,
	     "Returns the number of molecules written so far.\n\n"
	     )
	;
    };
  };
}

void wrap_smiwriter() {
  RDKit::smiwriter_wrap::wrap();
}
