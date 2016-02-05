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

#ifndef SIMULATION_DATA_CONTAINER_HPP
#define SIMULATION_DATA_CONTAINER_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace Opm {

    class SimulationDataContainer {
    public:
        SimulationDataContainer(size_t num_cells, size_t num_faces , size_t num_phases);

        size_t numPhases() const;
        size_t numFaces() const;
        size_t numCells() const;

        bool hasCellData( const std::string& name ) const;
        void registerCellData( const std::string& name , size_t components , double initialValue = 0.0 );
        std::vector<double>& getCellData( const std::string& name );

        bool hasFaceData( const std::string& name ) const;
        void registerFaceData( const std::string& name , size_t components , double initialValue = 0.0 );
        std::vector<double>& getFaceData( const std::string& name );


        /* Old deprecated */
        std::vector<double>& pressure    ();
        std::vector<double>& temperature ();
        std::vector<double>& saturation  ();

        std::vector<double>& facepressure();
        std::vector<double>& faceflux    ();

    private:
        void  addDefaultFields();

        size_t m_num_cells;
        size_t m_num_faces;
        size_t m_num_phases;

        std::unordered_map< std::string , std::vector<double> > m_cell_data;
        std::unordered_map< std::string , std::vector<double> > m_face_data;
    };
}

#endif
