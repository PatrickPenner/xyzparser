#pragma once

#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>

/// XYZ coordinate
struct XYZCoordinate {
    /// x coordinate value
    double x;
    /// x coordinate value
    double y;
    /// x coordinate value
    double z;
};

/// XYZ atom with an element symbol and a coordinate
struct XYZAtom {
    /// Element symbol of the atom
    std::string symbol;
    /// XYZ coordinate of the atom
    XYZCoordinate coordinate;
};

/// Optional XYZ header with the number of atoms and a name/comment
struct XYZHeader {
    /// write a header for the molecule
    bool has_header;
    /// Number of atoms in the file
    int nof_atoms;
    /// name of /comment about the entity in the file
    std::string name;
};

/// XYZ molecule with an optional header and a list of atoms
struct XYZMolecule {
    /// Optional header of the XYZ file
    XYZHeader header;
    /// Atoms of the XYZ molecule
    std::vector<XYZAtom> atoms;
};

BOOST_FUSION_ADAPT_STRUCT(
        XYZCoordinate,
        (double, x)
        (double, y)
        (double, z)
)

BOOST_FUSION_ADAPT_STRUCT(
        XYZAtom,
        (std::string, symbol)
        (XYZCoordinate, coordinate)
)

BOOST_FUSION_ADAPT_STRUCT(
        XYZHeader,
        (bool, has_header)
        (int, nof_atoms)
        (std::string, name)
)

BOOST_FUSION_ADAPT_STRUCT(
        XYZMolecule,
        (XYZHeader, header)
        (std::vector<XYZAtom>, atoms)
)
