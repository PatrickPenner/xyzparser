#pragma once

#include <string>

#include "XYZStructs.hpp"
#include "XYZGrammar.hpp"
#include "XYZGenerator.hpp"

/// XYZ parser collection class that handles parsing from and to the XYZ format
class XYZParser {
public:
    /**
     * Parse an XYZ molecule from a string
     * @param xyz_molecule_entry
     * @return XYZMolecule
     */
    static XYZMolecule parse(const std::string &xyz_molecule_entry) {
        using Iterator = std::string::const_iterator;
        XYZGrammar<Iterator> xyz_grammar;
        Iterator begin = xyz_molecule_entry.cbegin();
        Iterator end = xyz_molecule_entry.cend();
        XYZMolecule xyz_molecule{};
        bool success = boost::spirit::qi::parse(begin, end, xyz_grammar, xyz_molecule);
        if (!success || begin != end) {
            throw std::runtime_error("Failed to parse entry");
        }
        if (xyz_molecule.header.nof_atoms > 0 && xyz_molecule.atoms.size() != xyz_molecule.header.nof_atoms) {
            std::cerr << "XYZ header atom count and number of atoms parsed do not agree\n";
        }
        return xyz_molecule;
    }

    /**
     * Generate an XYZ string from an XYZ molecule
     * @param xyz_molecule
     * @return xyz string
     */
    static std::string generate(const XYZMolecule &xyz_molecule) {
        if (xyz_molecule.atoms.empty()) {
            std::cerr << "Skipping empty molecule passed to XYZParser\n";
            return "";
        }
        std::string xyz_molecule_entry{};
        using Iterator = std::back_insert_iterator<std::string>;
        XYZGenerator<Iterator> xyz_generator;
        Iterator sink(xyz_molecule_entry);
        bool success = boost::spirit::karma::generate(sink, xyz_generator, xyz_molecule);
        if (!success) {
            throw std::runtime_error("Failed to generate entry");
        }
        return xyz_molecule_entry;
    }
};
