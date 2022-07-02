#include <boost/test/included/unit_test.hpp>
#include "XYZParser.hpp"

BOOST_AUTO_TEST_SUITE(XYZParserTester);

    BOOST_AUTO_TEST_CASE(parses_and_generates_xyz_strings) {
        std::string xyz_string =
                "3\n"
                "water\n"
                "H        0.000  -0.417   0.538\n"
                "O        0.000   0.000  -0.270\n"
                "H        0.000   0.417   0.538";
        XYZMolecule molecule = XYZParser::parse(xyz_string);
        BOOST_TEST(molecule.atoms.size() > 0);
        BOOST_TEST(molecule.header.nof_atoms == molecule.atoms.size());
        XYZMolecule generated_molecule = XYZParser::parse(XYZParser::generate(molecule));
        BOOST_TEST(molecule.atoms.size() == generated_molecule.atoms.size());
    };

    BOOST_AUTO_TEST_CASE(parses_and_generates_xyz_strings_without_headers) {
        std::string xyz_string =
                "H        0.000  -0.417   0.538\n"
                "O        0.000   0.000  -0.270\n"
                "H        0.000   0.417   0.538";
        XYZMolecule molecule = XYZParser::parse(xyz_string);
        BOOST_TEST(molecule.atoms.size() > 0);
        BOOST_TEST(molecule.header.has_header == false);
        XYZMolecule generated_molecule = XYZParser::parse(XYZParser::generate(molecule));
        BOOST_TEST(generated_molecule.header.has_header == false);
        BOOST_TEST(molecule.atoms.size() == generated_molecule.atoms.size());
    };

    BOOST_AUTO_TEST_CASE(throws_exception_on_parsing_failure) {
        std::string invalid_xyz_string = "invalid";
        BOOST_CHECK_THROW(XYZParser::parse(invalid_xyz_string), std::runtime_error);
    };

    BOOST_AUTO_TEST_CASE(generates_empty_strings_for_empty_molecules) {
        XYZMolecule molecule;
        std::string xyz_entry = XYZParser::generate(molecule);
        BOOST_TEST(xyz_entry == "");
    }

BOOST_AUTO_TEST_SUITE_END();
