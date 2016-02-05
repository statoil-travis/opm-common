/*
  Copyright 2016 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SIMULATION_DATA_CONTAINER_TESTS
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include <opm/common/data/SimulationDataContainer.hpp>

using namespace Opm;


BOOST_AUTO_TEST_CASE(TestCreate) {
    SimulationDataContainer container(1000 , 10 , 2);

    BOOST_CHECK_EQUAL( 2U    , container.numPhases() );
    BOOST_CHECK_EQUAL( 1000U , container.numCells() );
    BOOST_CHECK_EQUAL( 10U   , container.numFaces() );
}




/*
  This test verifies that the default fields are correctly registered;
  this special behavior is deprecated - and the test should die; along
  with the behavior.
*/

BOOST_AUTO_TEST_CASE(TestRegisterDefaults) {
    SimulationDataContainer container(1000 , 10 , 2);

    BOOST_CHECK( container.hasCellData("PRESSURE") );
    BOOST_CHECK( container.hasCellData("SATURATION") );

    {
        auto pressure = container.getCellData("PRESSURE");
        BOOST_CHECK_EQUAL( pressure.size() , 1000U );

        auto sat = container.getCellData("SATURATION");
        BOOST_CHECK_EQUAL( sat.size() , 1000U*2 );
    }

    {
        auto pressure = container.pressure();
        BOOST_CHECK_EQUAL( pressure.size() , 1000U );

        auto sat = container.saturation();
        BOOST_CHECK_EQUAL( sat.size() , 1000U*2 );
    }

    BOOST_CHECK( container.hasFaceData("FACEPRESSURE") );
    BOOST_CHECK( container.hasFaceData("FACEFLUX") );
}




BOOST_AUTO_TEST_CASE(TestRegisterFaceData) {
    SimulationDataContainer container(100 , 10 , 2);
    BOOST_CHECK( !container.hasFaceData("FLUX"));
    BOOST_CHECK_THROW( container.getFaceData("FLUX") , std::invalid_argument );

    container.registerFaceData("FLUX" , 1 , 99 );
    auto& flux = container.getFaceData("FLUX");
    BOOST_CHECK_EQUAL( flux.size() , 10U );
    BOOST_CHECK_EQUAL( flux[0] , 99 );
}



BOOST_AUTO_TEST_CASE(TestRegisterCellData) {

    SimulationDataContainer container(100 , 10 , 2);
    BOOST_CHECK( !container.hasCellData("FIELDX"));
    BOOST_CHECK_THROW( container.getCellData("FIELDX") , std::invalid_argument );

    container.registerCellData("FIELDX" , 1 , 123 );
    {
        auto& fieldx = container.getCellData("FIELDX");
        BOOST_CHECK_EQUAL( fieldx.size() , 100U );
        for (auto v : fieldx)
            BOOST_CHECK_EQUAL( v , 123 );

        fieldx[0] *= 2;
    }

    {
        auto fieldx = container.getCellData("FIELDX");
        BOOST_CHECK_EQUAL( fieldx[0] , 246 );
        BOOST_CHECK_EQUAL( fieldx[1] , 123 );
    }

}


