#pragma once

#include <boost/phoenix.hpp>
#include <boost/spirit/include/karma.hpp>

#include "XYZStructs.hpp"

/**
 * XYZ file are generated with a header containing the number of atoms followed by a name/comment line for the file.
 * The rest of the file is a space delimited list of the atom elements and their coordinates.
 */
template<typename OutputIterator>
struct XYZGenerator : boost::spirit::karma::grammar<OutputIterator, XYZMolecule()> {
    XYZGenerator() : XYZGenerator::base_type(xyz_molecule) {
        using namespace boost::spirit;
        using karma::string;
        using karma::eol;
        using karma::int_;
        using karma::lit;
        using karma::eps;
        using karma::omit;
        // using karma::debug;
        using ascii::space;

        xyz_header = eps(at_c<0>(_val)) << omit[bool_] << int_ << eol << string << eol;
        xyz_header.name("xyz_header");
        // debug(xyz_header);

        xyz_coordinate = double_ << lit(' ') << double_ << lit(' ') << double_;
        xyz_coordinate.name("xyz_coordinate");
        // debug(xyz_coordinate);

        xyz_atom = string << lit(' ') << xyz_coordinate << eol;
        xyz_atom.name("xyz_atom");
        // debug(xyz_atom);

        xyz_molecule = -(xyz_header) << +xyz_atom;
        xyz_molecule.name("xyz_molecule");
        // debug(xyz_molecule);
    }

    /// XYZ header generator. The number of atoms on one line and a name/comment on the second line.
    boost::spirit::karma::rule<OutputIterator, XYZHeader()> xyz_header;
    /// XYZ coordinate generator. Three doubles separated by spaces.
    boost::spirit::karma::rule<OutputIterator, XYZCoordinate()> xyz_coordinate;
    /// XYZ atom generator. An element symbol and an XYZ coordinate separated by spaces.
    boost::spirit::karma::rule<OutputIterator, XYZAtom()> xyz_atom;
    /// XYZ molecule generator. A header followed by lines of atom records.
    boost::spirit::karma::rule<OutputIterator, XYZMolecule()> xyz_molecule;
};
