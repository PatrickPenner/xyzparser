#pragma once

#include <boost/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

#include "XYZStructs.hpp"

/**
 * XYZ files are a mostly informal standard of an optional header and a list of atoms with coordinates. Whitespace
 * is parsed very flexibly. The hardest constraint is probably that element symbols have to start with an uppercase
 * character and, if they have a second character, it must be lowercase. This is in line with basic notation in the
 * periodic table.
 */
template<typename Iterator>
struct XYZGrammar : boost::spirit::qi::grammar<Iterator, XYZMolecule()> {
    XYZGrammar() : XYZGrammar::base_type(xyz_molecule) {
        using namespace boost::spirit;
        using namespace boost::phoenix;

        using qi::double_;
        using qi::_val;
        using qi::_1;
        using ascii::char_;
        using qi::int_;
        using qi::upper;
        using qi::lower;
        using qi::space;
        // using qi::debug;

        xyz_header = eps[at_c<0>(_val) = true] >> int_[at_c<1>(_val) = _1] >> +space >> *(char_[at_c<2>(_val) += _1] - space);
        xyz_header.name("xyz_header");
        // debug(xyz_header);

        xyz_coordinate = double_[at_c<0>(_val) = _1]
                >> +space
                >> double_[at_c<1>(_val) = _1]
                >> +space
                >> double_[at_c<2>(_val) = _1]
                >> *space;
        xyz_coordinate.name("xyz_coordinate");
        // debug(xyz_coordinate);

        xyz_atom = upper[push_back(at_c<0>(_val), _1)]
                >> -(lower[push_back(at_c<0>(_val), _1)])
                >> +space
                >> xyz_coordinate[at_c<1>(_val) = _1];
        xyz_atom.name("xyz_atom");
        // debug(xyz_atom);

        xyz_molecule = -(xyz_header[at_c<0>(_val) = _1])
                >> *space >> *(xyz_atom[push_back(at_c<1>(_val), _1)]);
        xyz_molecule.name("xyz_molecule");
        // debug(xyz_molecule);
    }

    /// XYZ header rule. The number of atoms on one line and a name/comment on the second line.
    boost::spirit::qi::rule<Iterator, XYZHeader()> xyz_header;
    /// XYZ coordinate rule. Three doubles separated by variable whitespace
    boost::spirit::qi::rule<Iterator, XYZCoordinate()> xyz_coordinate;
    /// XYZ atom rule. Element symbol and coordinate separated by variable whitespace
    boost::spirit::qi::rule<Iterator, XYZAtom()> xyz_atom;
    /// XYZ molecule rule. An optional header followed by lines of atoms.
    boost::spirit::qi::rule<Iterator, XYZMolecule()> xyz_molecule;
};
